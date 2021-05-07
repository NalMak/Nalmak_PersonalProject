#include "AnimationController.h"
#include "TimeManager.h"
#include "DebugManager.h"
#include "AnimationController.h"
#include "XFileMesh.h"
#include "SkinnedMeshRenderer.h"
#include "AnimationTransition.h"
#include "AnimationController.h"
#include "Transform.h"

AnimationController::AnimationController(Desc * _desc)
{
	m_currentTrack = 0;
	m_nextTrack = 1;
	m_currentPlayTime = 0.f;
	m_prePlayTime = 0.f;
	m_totalPlayTime = 0.0;
	m_transitionTime = 1.f;
	m_blendWeight = 1.f;
	m_transtionType = D3DXTRANSITION_TYPE::D3DXTRANSITION_LINEAR;
	m_isStop = false;
	m_currentAnimationClip = nullptr;
	m_isRootAnimation = false;
	m_fixedBone = nullptr;

	LPD3DXANIMATIONCONTROLLER originController;
	if (_desc->cloneAnimationController)
	{
		m_rootMatrix = _desc->cloneAnimationController->m_rootMatrix;
		m_root = _desc->cloneAnimationController->m_root;
		originController = _desc->cloneAnimationController->m_animController;
		m_isSeparte = true;
		_desc->cloneAnimationController->m_isSeparte = true;
		m_subRoot = _desc->cloneAnimationController->m_subRoot;

		m_isSub = true;
		m_mesh = _desc->cloneAnimationController->m_mesh;
		_desc->cloneAnimationController->m_isSub = false;

		LPD3DXANIMATIONCONTROLLER clone;
		originController->CloneAnimationController(
			originController->GetMaxNumAnimationOutputs(),
			originController->GetMaxNumAnimationSets(),
			originController->GetMaxNumTracks(),
			originController->GetMaxNumEvents(),
			&clone
		);

		m_animController = clone;
		int i = 0;
		for (auto& clip : _desc->cloneAnimationController->m_animationClips)
		{

			m_animationClips.emplace_back(clip);
			//m_animController->RegisterAnimationSet(clip->animationSet);

			LPD3DXANIMATIONSET animSet;
			_desc->cloneAnimationController->m_animController->GetAnimationSet(i, &animSet);
			m_animController->RegisterAnimationSet(animSet);

			/*AnimationClip* clip = new AnimationClip();
			clip->animationName = animSet->GetName();
			clip->speed = _speed;
			clip->loop = _loop;

			clip->animationSet = animSet;*/

			animSet->Release();
			++i;
		}
	
	}
	else
	{
		m_rootMatrix = _desc->rootMatrix;
		Mesh* mesh = ResourceManager::GetInstance()->GetResource<Mesh>(_desc->meshName);

		if (mesh->GetMeshType() != MESH_TYPE_ANIMATION)
			assert(L"This Animation Controller mesh must be of animation type!" && 0);
		XFileMesh* xMesh = (XFileMesh*)mesh;
		m_root = xMesh->GetRoot();
		m_mesh = xMesh;
		originController = xMesh->GetAnimationController();

		if (!originController)
			return;

		m_isSeparte = false;
		m_subRoot = nullptr;

		LPD3DXANIMATIONCONTROLLER clone;
		originController->CloneAnimationController(
			originController->GetMaxNumAnimationOutputs(),
			originController->GetMaxNumAnimationSets(),
			originController->GetMaxNumTracks(),
			originController->GetMaxNumEvents(),
			&clone
		);

		m_animController = clone;
	}
	
	

}

AnimationController::~AnimationController()
{

}

void AnimationController::Initialize()
{
	
}


void AnimationController::Update()
{
	if (m_useCurve)
	{
		if (m_bezierCurrentTime <= m_bezierTotalTime)
		{
			float ratio = m_bezier.GetYvalue(m_bezierCurrentTime / m_bezierTotalTime);
			m_curretOffset = Nalmak_Math::Lerp(m_startOffset, m_endOffset, ratio);
			m_bezierCurrentTime += dTime;
		}
		else
		{
			m_useCurve = false;
		}
	}
}

void AnimationController::EachRender()
{
	if (m_isStop)
		return;
	if (!m_currentAnimationClip)
		return;
	m_prePlayTime = m_currentPlayTime;
	D3DXTRACK_DESC desc;
	m_animController->GetTrackDesc(m_currentTrack, &desc);
	m_currentPlayTime = desc.Position;

	double time = (double)TimeManager::GetInstance()->GetdeltaTime() * m_currentAnimationClip->speed;

	//m_animController->AdvanceTime(time, NULL);	// 내부적으로 카운딩되는 시간 값(애니메이션 동작에 따른 사운드나 이펙트에 대한 처리를 담당하는 객체 주소)
	//UpdateBoneMatrix();
	
	if (m_currentPlayTime + time + 0.0001 < m_totalPlayTime)
	{
		m_animController->AdvanceTime(time, NULL);	// 내부적으로 카운딩되는 시간 값(애니메이션 동작에 따른 사운드나 이펙트에 대한 처리를 담당하는 객체 주소)
		UpdateBoneMatrix();
	}
	else if (m_currentAnimationClip->loop)
	{
		m_animController->AdvanceTime(m_totalPlayTime - m_currentPlayTime, NULL);
		UpdateBoneMatrix();
		m_currentPlayTime = 0;
		m_animController->ResetTime();
		m_animController->SetTrackPosition(m_currentTrack, 0);
	}
	else
	{
		m_animController->AdvanceTime(0, NULL);
		m_animController->SetTrackPosition(m_currentTrack, m_totalPlayTime - 0.0001);
		m_animController->ResetTime();
		m_currentPlayTime = m_totalPlayTime - 0.0001;
		m_isStop = true;
		UpdateBoneMatrix();
	}


}



//1. 애니메이션컨트롤러로 부터 애니메이션셋을 받아와야한다.
//2. 애니메이션셋을 트랙에 셋팅해야 한다.
//3. 애니메이션 트랙을 활성화시킨다.
//4. 애니메이션 컨트롤러로 애니메이션을 진행시킨다.

void AnimationController::AddAnimationClip(const string & _animName, float _speed, bool _loop)
{
	Mesh* mesh = ResourceManager::GetInstance()->GetResource<Mesh>(Nalmak_String::StringToWString(_animName));
	if (mesh->GetMeshType() != MESH_TYPE_ANIMATION)
		assert(L"No animation data in mesh File! " && 0);
	XFileMesh* xMesh = (XFileMesh*)mesh;

	LPD3DXANIMATIONCONTROLLER mixedAnimController;
	LPD3DXANIMATIONCONTROLLER animController = xMesh->GetAnimationController();
	UINT newAnimationCount = animController->GetNumAnimationSets();

	if (m_animController)
	{
		ThrowIfFailed(m_animController->CloneAnimationController(
			m_animController->GetMaxNumAnimationOutputs(),
			m_animController->GetMaxNumAnimationSets() + newAnimationCount,
			m_animController->GetMaxNumTracks(),
			m_animController->GetMaxNumEvents(),
			&mixedAnimController));

		m_animController->Release();
	}
	else
	{
		ThrowIfFailed(animController->CloneAnimationController(
			animController->GetMaxNumAnimationOutputs(),
			animController->GetMaxNumAnimationSets(),
			animController->GetMaxNumTracks(),
			animController->GetMaxNumEvents(),
			&mixedAnimController));
	}


	m_animController = mixedAnimController;
	LPD3DXANIMATIONSET animSet;
	for (UINT animCount = 0; animCount < newAnimationCount; ++animCount)
	{
		animController->GetAnimationSet(animCount, &animSet);
		m_animController->RegisterAnimationSet(animSet);

		wstring animName = Nalmak_String::StringToWString(animSet->GetName());
		
		AnimationClip* clip = ResourceManager::GetInstance()->GetResourceIfExist<AnimationClip>(animName);
		if (!clip)
			clip = ResourceManager::GetInstance()->AddResource<AnimationClip, AnimationClip>(animName);
		clip->animationName = animSet->GetName();
		clip->speed = _speed;
		clip->loop = _loop;

		clip->animationSet = animSet;

		m_animationClips.emplace_back(clip);

		animSet->Release();

	}
}

AnimationClip* AnimationController::GetAnimationClip(const string & _clipName)
{
	for (auto& clip : m_animationClips)
	{
		if (clip->animationName == _clipName)
		{
			return clip;
		}
	}
	assert(L"Can't find animation clip!" && 0);
	return nullptr;
}

void AnimationController::SetAnimatinoOffsetByBeizer(const Vector3 & _startOffset, const Vector3 & _endOffset, float _time, const Vector2 & _p1, const Vector2 & _p2, const Vector2 & _p3, const Vector2 & _p4)
{
	m_useCurve = true;

	m_curretOffset.x = _startOffset.x / m_transform->scale.x;
	m_curretOffset.y = _startOffset.y / m_transform->scale.y;
	m_curretOffset.z = _startOffset.z / m_transform->scale.z;

	m_startOffset = m_curretOffset;

	m_endOffset.x = _endOffset.x / m_transform->scale.x;
	m_endOffset.y = _endOffset.y / m_transform->scale.y;
	m_endOffset.z = _endOffset.z / m_transform->scale.z;

	m_bezierTotalTime = _time;
	m_bezierCurrentTime = 0.f;

	m_bezier.SetPoint(0, _p1);
	m_bezier.SetPoint(1, _p2);
	m_bezier.SetPoint(2, _p3);
	m_bezier.SetPoint(3, _p4);

}

void AnimationController::UpdateBoneMatrix(Nalmak_Frame * _bone, const Matrix & _parent)
{
	_bone->boneCombinedMatrix = _bone->TransformationMatrix * _parent;

	if (_bone->pFrameFirstChild)
		UpdateBoneMatrix((Nalmak_Frame*)_bone->pFrameFirstChild, _bone->boneCombinedMatrix);

	if (_bone->pFrameSibling)
		UpdateBoneMatrix((Nalmak_Frame*)_bone->pFrameSibling, _parent);
}




void AnimationController::Play(AnimationClip * _clip, double _startTime)
{
	LPD3DXANIMATIONSET anim = _clip->animationSet;

	m_isStop = false;

	m_currentAnimationClip = _clip;
	m_animController->SetTrackEnable(m_nextTrack, false);

	m_animController->UnkeyAllTrackEvents(m_currentTrack);
	m_animController->UnkeyAllTrackEvents(m_nextTrack);

	m_animController->SetTrackAnimationSet(m_currentTrack, anim);

	m_animController->SetTrackEnable(m_currentTrack, true);
	m_animController->SetTrackSpeed(m_currentTrack, 1);
	m_animController->SetTrackPosition(m_currentTrack, _startTime);

	m_animController->ResetTime();
	m_totalPlayTime = anim->GetPeriod();


	D3DXTRACK_DESC trackInfo;
	m_animController->GetTrackDesc(m_currentTrack, &trackInfo);
	m_currentPlayTime = trackInfo.Position;

}

void AnimationController::Play(const string & _animName, double _otherTime)
{
	Play(GetAnimationClip(_animName),_otherTime);
}

void AnimationController::PlayBlending(AnimationClip * _clip, double _otherTime)
{
	if (!m_currentAnimationClip)
	{
		Play(_clip);
		return;
	}
	m_isStop = false;

	AnimationClip* nextClip = _clip;

	m_nextTrack = (m_currentTrack == 0 ? 1 : 0); // 0이면 시작

	LPD3DXANIMATIONSET anim = nextClip->animationSet;

	m_animController->SetTrackAnimationSet(m_nextTrack, anim);

	m_animController->UnkeyAllTrackEvents(m_currentTrack);
	m_animController->UnkeyAllTrackEvents(m_nextTrack);

	double transitionTime;
	if (m_currentPlayTime + m_transitionTime > m_totalPlayTime)
		transitionTime = m_totalPlayTime - m_currentPlayTime - 0.001;
	else
		transitionTime = m_transitionTime;

	m_animController->KeyTrackEnable(m_currentTrack, false, m_currentPlayTime + transitionTime);
	//m_animController->SetTrackSpeed(m_currentTrack, m_currentAnimationClip->speed);
	m_animController->KeyTrackSpeed(m_currentTrack, 1, m_currentPlayTime, transitionTime, m_transtionType); // 속도를 0으로 보간
	m_animController->KeyTrackWeight(m_currentTrack, 1 - m_blendWeight, m_currentPlayTime, transitionTime, m_transtionType);

	m_animController->SetTrackEnable(m_nextTrack, true);
	//m_animController->SetTrackSpeed(m_nextTrack, nextClip->speed);
	m_animController->KeyTrackSpeed(m_nextTrack, 1, m_currentPlayTime, transitionTime, m_transtionType);
	m_animController->KeyTrackWeight(m_nextTrack, m_blendWeight, m_currentPlayTime, transitionTime, m_transtionType);

	m_totalPlayTime = anim->GetPeriod();

	// 내부에 누적된 시간값 초기화
	m_animController->ResetTime();
	m_animController->SetTrackPosition(m_nextTrack, _otherTime);
	m_currentPlayTime = _otherTime;

	m_currentTrack = m_nextTrack;
	m_currentAnimationClip = nextClip;
}

void AnimationController::PlayBlending(const string & _clipName, double _otherTime)
{
	PlayBlending(GetAnimationClip(_clipName),_otherTime);
}

void AnimationController::PlayBlendingOrigin(AnimationClip * _clip, double _otherTime)
{
	if (!m_currentAnimationClip)
	{
		Play(_clip);
		return;
	}
	m_isStop = false;

	AnimationClip* nextClip = _clip;

	m_nextTrack = (m_currentTrack == 0 ? 1 : 0); // 0이면 시작

	LPD3DXANIMATIONSET anim = nextClip->animationSet;

	m_animController->SetTrackAnimationSet(m_nextTrack, anim);

	m_animController->UnkeyAllTrackEvents(m_currentTrack);
	m_animController->UnkeyAllTrackEvents(m_nextTrack);

	double transitionTime;
	if (m_currentPlayTime + m_transitionTime > m_totalPlayTime)
		transitionTime = m_totalPlayTime - m_currentPlayTime - 0.001;
	else
		transitionTime = m_transitionTime;

	m_animController->KeyTrackEnable(m_currentTrack, false, m_currentPlayTime + transitionTime);
	m_animController->SetTrackSpeed(m_currentTrack, m_currentAnimationClip->speed);
	//m_animController->KeyTrackSpeed(m_currentTrack, m_currentAnimationClip->speed, m_currentPlayTime, m_transitionTime, m_transtionType); // 속도를 0으로 보간
	m_animController->KeyTrackWeight(m_currentTrack, 1 - m_blendWeight, m_currentPlayTime, transitionTime, m_transtionType);

	m_animController->SetTrackEnable(m_nextTrack, true);
	m_animController->SetTrackSpeed(m_nextTrack, nextClip->speed);
	//m_animController->KeyTrackSpeed(m_nextTrack, nextClip->speed, _otherTime, m_transitionTime, m_transtionType);
	m_animController->KeyTrackWeight(m_nextTrack, m_blendWeight, _otherTime, transitionTime, m_transtionType);

	// 내부에 누적된 시간값 초기화
	m_totalPlayTime = anim->GetPeriod();

	m_animController->ResetTime();
	m_animController->SetTrackPosition(m_nextTrack, _otherTime);
	m_currentPlayTime = _otherTime;

	m_currentTrack = m_nextTrack;
	m_currentAnimationClip = nextClip;

}

void AnimationController::PlayBlendingOrigin(const string & _clipName, double _otherTime)
{
	PlayBlendingOrigin(GetAnimationClip(_clipName), _otherTime);
}


void AnimationController::PlayBlending(AnimationClip * _clip0, AnimationClip * _clip1, float _weight)
{
	m_totalPlayTime = _clip0->animationSet->GetPeriod();
	m_currentAnimationClip = _clip0;

	m_currentTrack = 0;
	m_nextTrack = 1;

	m_animController->SetTrackAnimationSet(0, _clip0->animationSet);
	m_animController->SetTrackAnimationSet(1, _clip1->animationSet);

	m_animController->KeyTrackWeight(0, _weight, m_currentPlayTime, m_totalPlayTime, D3DXTRANSITION_LINEAR);
	m_animController->KeyTrackWeight(1, 1 - _weight, m_currentPlayTime, m_totalPlayTime, D3DXTRANSITION_LINEAR);

	m_animController->SetTrackEnable(0, true);
	m_animController->SetTrackEnable(1, true);

	
}

void AnimationController::PlayBlending(const string & _clip1, const string & _clip2, float _weight)
{
	PlayBlending(GetAnimationClip(_clip1), GetAnimationClip(_clip2),_weight);
}

void AnimationController::Stop()
{
	m_isStop = true;
}

bool AnimationController::IsPlay()
{
	return !m_isStop;
}

double AnimationController::GetPlayTime()
{
	return m_currentPlayTime;
}

double AnimationController::GetTotalPlayTime()
{
	return m_totalPlayTime;
}

double AnimationController::GetPlayRemainTime()
{
	return m_totalPlayTime - m_currentPlayTime;
}

float AnimationController::GetPlayRatio()
{
	return (float)(m_currentPlayTime / m_totalPlayTime);
}

bool AnimationController::IsOverTime(double _time)
{
	if (m_prePlayTime < _time && m_currentPlayTime >= _time)
		return true;

	return false;
}

void AnimationController::SetFixedAnimationBoneName(string _boneName, bool _xAxis, bool _yAxis, bool _zAxis)
{
	m_fixedBone = D3DXFrameFind(m_root, _boneName.c_str());
	assert(L"Can't find bone! " && m_fixedBone);

	m_rootMotion_fixXAxis = _xAxis;
	m_rootMotion_fixYAxis = _yAxis;
	m_rootMotion_fixZAxis = _zAxis;
}


void AnimationController::SetRootMotion(bool _isRootAnim)
{
	m_isRootAnimation = _isRootAnim;
}

const string & AnimationController::GetCurrentPlayAnimationName()
{
	return m_currentAnimationClip->animationName;
}

AnimationClip * AnimationController::GetCurrentPlayAnimation()
{
	return m_currentAnimationClip;
}

void AnimationController::SetBlendOption(float _blendTime, float _weight, D3DXTRANSITION_TYPE _type)
{
	m_transitionTime = _blendTime;
	m_blendWeight = _weight;
	m_transtionType = _type;
}

void AnimationController::SeparateBone(const string & _refBone)
{
	m_isSeparte = true;

	m_subRoot = D3DXFrameFind(m_root, _refBone.c_str());
	assert(L"Can't find separte bone!" && m_subRoot);
}
void AnimationController::SetSeparate(bool _separate)
{
	m_isSeparte = _separate;
}
void AnimationController::UpdateBoneMatrix()
{
	Matrix root = m_rootMatrix;
	if (m_useCurve)
	{
		memcpy(&root._41, m_curretOffset, sizeof(Vector3));
	}

	if (m_isSeparte)
	{
		if (m_isRootAnimation)
		{
			assert(L"Please set bone to fix pos!" && m_fixedBone);
			UpdateFixedBoneSeparationMatrix((Nalmak_Frame*)m_root, root, m_isSub);
		}
		else
			UpdateBoneSeparationMatrix((Nalmak_Frame*)m_root, root, m_isSub);
	}
	else
	{
		if (m_isRootAnimation)
		{
			assert(L"Please set bone to fix pos!" && m_fixedBone);
			UpdateFixedBoneMatrix((Nalmak_Frame*)m_root, root);
		}
		else
			UpdateBoneMatrix((Nalmak_Frame*)m_root, root);
	}
	
}


void AnimationController::UpdateBoneSeparationMatrix(Nalmak_Frame * _bone, const Matrix & _parent, bool _isSub)
{
	_bone->boneCombinedMatrix = _bone->TransformationMatrix * _parent;

	if (_bone == m_subRoot)
	{
		if (_isSub)
		{

			if (_bone->pFrameFirstChild)
				UpdateBoneSeparationMatrix((Nalmak_Frame*)_bone->pFrameFirstChild, _bone->boneCombinedMatrix, _isSub);
		}
		else
		{
			if (_bone->pFrameSibling)
				UpdateBoneSeparationMatrix((Nalmak_Frame*)_bone->pFrameSibling, _parent, _isSub);
		}
		return;
	}

	if (_bone->pFrameFirstChild)
		UpdateBoneSeparationMatrix((Nalmak_Frame*)_bone->pFrameFirstChild, _bone->boneCombinedMatrix, _isSub);

	if (_bone->pFrameSibling)
		UpdateBoneSeparationMatrix((Nalmak_Frame*)_bone->pFrameSibling, _parent, _isSub);
}

void AnimationController::UpdateFixedBoneSeparationMatrix(Nalmak_Frame * _bone, const Matrix & _parent, bool _isSub)
{
	
	_bone->boneCombinedMatrix = _bone->TransformationMatrix * _parent;
	if (_bone == m_fixedBone)
	{
		if (m_rootMotion_fixXAxis)
			_bone->boneCombinedMatrix._41 = 0;
		if (m_rootMotion_fixYAxis)
			_bone->boneCombinedMatrix._42 = 0;
		if (m_rootMotion_fixZAxis)
			_bone->boneCombinedMatrix._43 = 0;
	}
	if (_bone == m_subRoot)
	{
		if (_isSub)
		{

			if (_bone->pFrameFirstChild)
				UpdateFixedBoneSeparationMatrix((Nalmak_Frame*)_bone->pFrameFirstChild, _bone->boneCombinedMatrix, _isSub);
		}
		else
		{
			if (_bone->pFrameSibling)
				UpdateFixedBoneSeparationMatrix((Nalmak_Frame*)_bone->pFrameSibling, _parent, _isSub);
		}
		return;
	}

	if (_bone->pFrameFirstChild)
		UpdateFixedBoneSeparationMatrix((Nalmak_Frame*)_bone->pFrameFirstChild, _bone->boneCombinedMatrix, _isSub);

	if (_bone->pFrameSibling)
		UpdateFixedBoneSeparationMatrix((Nalmak_Frame*)_bone->pFrameSibling, _parent, _isSub);
}

void AnimationController::UpdateFixedBoneMatrix(Nalmak_Frame * _bone, const Matrix & _parent)
{
	_bone->boneCombinedMatrix = _bone->TransformationMatrix * _parent;
	if (_bone == m_fixedBone)
	{
		if(m_rootMotion_fixXAxis)
			_bone->boneCombinedMatrix._41 = 0;
		if (m_rootMotion_fixYAxis)
			_bone->boneCombinedMatrix._42 = 0;
		if (m_rootMotion_fixZAxis)
			_bone->boneCombinedMatrix._43 = 0;
	}

	if (_bone->pFrameFirstChild)
		UpdateFixedBoneMatrix((Nalmak_Frame*)_bone->pFrameFirstChild, _bone->boneCombinedMatrix);

	if (_bone->pFrameSibling)
		UpdateFixedBoneMatrix((Nalmak_Frame*)_bone->pFrameSibling, _parent);
}

const Matrix & AnimationController::GetRootMatrix()
{
	return ((Nalmak_Frame*)m_root->pFrameFirstChild)->boneCombinedMatrix;
}

void AnimationController::PlayBlending(AnimationController * _otherController)
{
	PlayBlending(_otherController->GetCurrentPlayAnimation(), _otherController->m_currentPlayTime);
}

void AnimationController::Release()
{
	m_animationClips.clear();

	SAFE_RELEASE(m_animController);
}


