#include "..\Include\IAnimation.h"
#include "TimeManager.h"

IAnimation::IAnimation()
{
	m_timeManager = TimeManager::GetInstance();

	m_isPlay = false;
	m_playTimer = 0.f;
	m_playDuration = 1.f;

	m_currentAnimation = LERP;
}

void IAnimation::Start_Animation()
{
	m_playTimer = 0.f;
	m_isPlay = true;
}

bool IAnimation::Play_CurrentAnimation()
{
	if (!m_isPlay)
		return false;

	m_playTimer += m_timeManager->GetdeltaTime();

	if (m_playTimer < m_startDelay)
		return false;

	if (m_playTimer - m_startDelay >  m_playDuration)
	{
		End_Animation();
		return false;
	}

	switch (m_currentAnimation)
	{
	case IAnimation::LERP:
		Play_Lerp();
		break;
	case IAnimation::CUSTOM:
		Play_Custom();
		break;
	}

	return true;
}

void IAnimation::End_Animation()
{
	m_isPlay = false;
}
