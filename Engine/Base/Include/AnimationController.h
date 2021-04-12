#pragma once

#include "Nalmak_Include.h"
class XFileMesh;

class AnimationController
{
public:
	AnimationController(XFileMesh* _originMesh);
	~AnimationController();
public:
	void SetAnimation(UINT _index);
	void SetAnimation(UINT _index, float _keySpeed, float _transitionTime);
	void PlayAnimation();
	AnimationController* CloneAnimationController();
	void Update();
	XFileMesh* GetOriginMesh();
private:
	LPD3DXANIMATIONCONTROLLER m_animController;
	XFileMesh* m_originMesh;

	UINT m_currentTrack;
	UINT m_nextTrack;
	UINT m_preAnimIndex;

	double m_totalTime;
	double m_animPlayTime;
	double m_preTrackPos;
	double m_preSaturPos;

	bool m_isReverse;
};