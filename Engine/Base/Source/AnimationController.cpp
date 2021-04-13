#include "AnimationController.h"
#include "TimeManager.h"
#include "DebugManager.h"
#include "AnimationController.h"
#include "XFileMesh.h"


AnimationController::AnimationController(LPD3DXANIMATIONCONTROLLER _animController, LPD3DXFRAME _rootFrame)
{
	m_currentTrack = 0;
	m_nextTrack = 1;
	m_totalTime = 0.f;
	m_preAnimIndex = INFINITE;
	m_animPlayTime = 0.0;
	m_isReverse = false;

	m_animController = _animController;
	m_root = _rootFrame;
}

AnimationController::~AnimationController()
{
	
}


void AnimationController::Update()
{
	PlayAnimation();
	UpdateBoneMatrix();
}


void AnimationController::UpdateBoneMatrix(Nalmak_Frame * _bone, const Matrix & _parent)
{
	_bone->boneWorldMatrix = _bone->TransformationMatrix * _parent;

	if (_bone->pFrameFirstChild)
		UpdateBoneMatrix((Nalmak_Frame*)_bone->pFrameFirstChild, _bone->boneWorldMatrix);

	if (_bone->pFrameSibling)
		UpdateBoneMatrix((Nalmak_Frame*)_bone->pFrameSibling, _parent);

}

void AnimationController::UpdateBoneMatrix()
{
	Matrix mat = { 1,0,0,0,0,1,0,0,0,0,1,0,0,0,0,1 };
	UpdateBoneMatrix((Nalmak_Frame*)m_root, mat);
}


//1. �ִϸ��̼���Ʈ�ѷ��� ���� �ִϸ��̼Ǽ��� �޾ƿ;��Ѵ�.
//2. �ִϸ��̼Ǽ��� Ʈ���� �����ؾ� �Ѵ�.
//3. �ִϸ��̼� Ʈ���� Ȱ��ȭ��Ų��.
//4. �ִϸ��̼� ��Ʈ�ѷ��� �ִϸ��̼��� �����Ų��.

void AnimationController::SetAnimation(UINT _index)
{
	
	
	LPD3DXANIMATIONSET anim = nullptr;

	// 1��
	m_animController->GetAnimationSet(_index, &anim); 


	m_animPlayTime = anim->GetPeriod();

	// 2��
	m_animController->SetTrackAnimationSet(m_currentTrack, anim);
	m_animController->UnkeyAllTrackEvents(m_currentTrack);

	// 3��
	m_animController->SetTrackEnable(m_currentTrack, true);
	m_animController->KeyTrackSpeed(m_currentTrack, 1.f, m_totalTime, 0.25, D3DXTRANSITION_LINEAR);
	m_animController->KeyTrackWeight(m_currentTrack, 1.f, m_totalTime, 0.25, D3DXTRANSITION_LINEAR);

	// 4��
	m_animController->ResetTime();
	m_totalTime = 0.0;
	m_animController->SetTrackPosition(m_currentTrack, 0.0);

	m_preAnimIndex = _index;
}

void AnimationController::SetAnimation(UINT _index, float _keySpeed, float _transitionTime)
{
	// ? 
	m_nextTrack = (m_currentTrack == 0 ? 1 : 0); // 0�̸� ����

	LPD3DXANIMATIONSET anim = nullptr;

	m_animController->GetAnimationSet(_index, &anim);

	m_animPlayTime = anim->GetPeriod();

	m_animController->SetTrackAnimationSet(m_nextTrack, anim);

	m_animController->UnkeyAllTrackEvents(m_currentTrack);
	m_animController->UnkeyAllTrackEvents(m_nextTrack);

	m_animController->KeyTrackEnable(m_currentTrack, false, m_totalTime + _transitionTime);
	m_animController->KeyTrackSpeed(m_currentTrack, _keySpeed, m_totalTime, _transitionTime, D3DXTRANSITION_LINEAR);

	m_animController->KeyTrackWeight(m_currentTrack, 0.1f, m_totalTime, _transitionTime, D3DXTRANSITION_LINEAR);

	m_animController->SetTrackEnable(m_nextTrack, true);
	m_animController->KeyTrackSpeed(m_nextTrack, _keySpeed, m_totalTime, _transitionTime, D3DXTRANSITION_LINEAR);
	m_animController->KeyTrackWeight(m_nextTrack, 0.9f, m_totalTime, _transitionTime, D3DXTRANSITION_LINEAR);

	m_animController->ResetTime(); 
	m_totalTime = 0.0;

	m_animController->SetTrackPosition(m_nextTrack, 0.0);

	m_preAnimIndex = _index;

	m_currentTrack = m_nextTrack;

}

void AnimationController::PlayAnimation()
{
	D3DXTRACK_DESC trackInfo;
	ZeroMemory(&trackInfo, sizeof(D3DXTRACK_DESC));

	m_animController->GetTrackDesc(m_currentTrack, &trackInfo);
	m_preTrackPos = trackInfo.Position;
	m_preSaturPos = m_preTrackPos;

	if (m_animPlayTime > 0.f)
	{
		/*	if (m_bReverse)
			{
				while (m_dOldSaturPos < 0.f)
				{
					m_dOldSaturPos += m_dPeriod;
				}
			}
			else*/
		{
			while (m_preSaturPos > m_animPlayTime)
			{
				m_preSaturPos -= m_animPlayTime;
			}
		}
	}

	double time = (double)TimeManager::GetInstance()->GetdeltaTime();
	m_animController->AdvanceTime(time, NULL);	// ���������� ī����Ǵ� �ð� ��(�ִϸ��̼� ���ۿ� ���� ���峪 ����Ʈ�� ���� ó���� ����ϴ� ��ü �ּ�)
	m_totalTime += time;
}

AnimationController * AnimationController::CloneAnimationController(LPD3DXANIMATIONCONTROLLER _animControl, LPD3DXFRAME _root)
{
	AnimationController* animController = nullptr;

	LPD3DXANIMATIONCONTROLLER originController = _animControl;
	LPD3DXANIMATIONCONTROLLER clone;
	originController->CloneAnimationController(
		originController->GetMaxNumAnimationOutputs(),
		originController->GetMaxNumAnimationSets(),
		originController->GetMaxNumTracks(),
		originController->GetMaxNumEvents(),
		&clone
	);

	animController = new AnimationController(clone, _root);

	return animController;
}

void AnimationController::Release()
{
	SAFE_RELEASE(m_animController);
	delete this;
}


