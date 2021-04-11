#pragma once

#include "Nalmak_Include.h"

class AnimationController
{
public:
	AnimationController(LPD3DXANIMATIONCONTROLLER _controller);
	~AnimationController();
public:
	void SetAnimation(unsigned int _index);
	void PlayAnimation();
private:
	LPD3DXANIMATIONCONTROLLER m_animController;

	unsigned int m_currentTrack;
	unsigned int m_newTrack;
	unsigned int m_preAnimIndex;

	double m_totalTime;
	double m_period;
	double m_preTrackPos;
	double m_preSaturPos;

	bool m_isReverse;
};