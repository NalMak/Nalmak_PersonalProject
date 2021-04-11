#include "AnimationController.h"
#include "TimeManager.h"


AnimationController::AnimationController(LPD3DXANIMATIONCONTROLLER _controller)
{
	m_currentTrack = 0;
	m_newTrack = 1;
	m_totalTime = 0.f;
	m_preAnimIndex = INFINITE;
	m_period = 0.0;
	m_isReverse = false;

	m_animController = _controller;
}

AnimationController::~AnimationController()
{
	SAFE_RELEASE(m_animController);
}

//1. 애니메이션컨트롤러로 부터 애니메이션셋을 받아와야한다.
//2. 애니메이션셋을 트랙에 셋팅해야 한다.
//3. 애니메이션 트랙을 활성화시킨다.
//4. 애니메이션 컨트롤러로 애니메이션을 진행시킨다.

void AnimationController::SetAnimation(UINT _index)
{
	
	LPD3DXANIMATIONSET anim = nullptr;

	// 1번
	m_animController->GetAnimationSet(_index, &anim); 


	m_period = anim->GetPeriod();

	// 2번
	m_animController->SetTrackAnimationSet(m_currentTrack, anim);
	m_animController->UnkeyAllTrackEvents(m_currentTrack);

	// 3번
	m_animController->SetTrackEnable(m_currentTrack, true);
	m_animController->KeyTrackSpeed(m_currentTrack, 1.f, m_totalTime, 0.25, D3DXTRANSITION_LINEAR);
	m_animController->KeyTrackWeight(m_currentTrack, 1.f, m_totalTime, 0.25, D3DXTRANSITION_LINEAR);

	// 4번
	m_animController->ResetTime();
	m_totalTime = 0.0;
	m_animController->SetTrackPosition(m_currentTrack, 0.0);

	m_preAnimIndex = _index;
}

void AnimationController::PlayAnimation()
{
	D3DXTRACK_DESC trackInfo;
	ZeroMemory(&trackInfo, sizeof(D3DXTRACK_DESC));

	m_animController->GetTrackDesc(m_currentTrack, &trackInfo);
	m_preTrackPos = trackInfo.Position;
	m_preSaturPos = m_preTrackPos;

	if (m_period > 0.f)
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
			while (m_preSaturPos > m_period)
			{
				m_preSaturPos -= m_period;
			}
		}
	}

	double time = (double)TimeManager::GetInstance()->GetdeltaTime();
	m_animController->AdvanceTime(time, NULL);	// 내부적으로 카운딩되는 시간 값(애니메이션 동작에 따른 사운드나 이펙트에 대한 처리를 담당하는 객체 주소)
	m_totalTime += time;
}
