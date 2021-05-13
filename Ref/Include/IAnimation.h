#pragma once
#ifndef __IANIMATION_H__
#define __IANIMATION_H__

#include "Nalmak_Include.h"

class GameObject;
class TimeManager;
class NALMAK_DLL IAnimation
{
public:
	enum ANIMATION { LERP, CUSTOM };

public:
	IAnimation();
	virtual ~IAnimation() = default;

public:
	virtual void Start_Animation() = 0;
	virtual bool Play_CurrentAnimation() = 0;
	virtual void End_Animation() = 0;

	void SetActor(GameObject* _actor) { m_actor = _actor; }
	void SetAnimation(ANIMATION _animation) { m_currentAnimation = _animation; }
	void SetPlayDuration(float _duration) { m_playDuration = _duration; }
	void SetStartDelay(float _delay) { m_startDelay = _delay; }

	const bool& IsPlay() { return m_isPlay; }
public:
	virtual void Play_Lerp() = 0;
	virtual void Play_Custom() = 0;


protected:
	TimeManager* m_timeManager;

	GameObject* m_actor;
	ANIMATION m_currentAnimation;
	bool m_isPlay;
	float m_playTimer;
	float m_playDuration;
	float m_startDelay;

};
#endif // !__IANIMATION_H__



