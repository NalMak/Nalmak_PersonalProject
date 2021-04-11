#pragma once

#include "Nalmak_Include.h"

class AnimationController
{
public:
	AnimationController(LPD3DXANIMATIONCONTROLLER _controller);
	~AnimationController();
public:
	void SetAnimation(UINT _index);
	void SetAnimation(UINT _index, float _keySpeed, float _transitionTime);
	void PlayAnimation();
private:
	// 
	LPD3DXANIMATIONCONTROLLER m_animController;

	UINT m_currentTrack;
	UINT m_nextTrack;
	UINT m_preAnimIndex;

	double m_totalTime;
	double m_animPlayTime;
	double m_preTrackPos;
	double m_preSaturPos;

	bool m_isReverse;
};