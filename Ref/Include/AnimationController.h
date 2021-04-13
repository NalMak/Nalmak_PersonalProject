#pragma once

#include "Nalmak_Include.h"

class XFileMesh;

class AnimationController
{
public:
	static void UpdateBoneMatrix(Nalmak_Frame * _bone, const Matrix & _parent);

private:
	AnimationController(LPD3DXANIMATIONCONTROLLER _animController, LPD3DXFRAME _rootFrame);
	~AnimationController();
public:
	static AnimationController* CloneAnimationController(LPD3DXANIMATIONCONTROLLER _animControl, LPD3DXFRAME _root);
	void Release();
public:
	void SetAnimation(UINT _index);
	void SetAnimation(UINT _index, float _keySpeed, float _transitionTime);
	void Update();
private:
	void PlayAnimation();
	void UpdateBoneMatrix();

private:
	LPD3DXANIMATIONCONTROLLER m_animController;
	LPD3DXFRAME m_root;
	vector<Nalmak_MeshContainer*>		m_meshContainerList;

	UINT m_currentTrack;
	UINT m_nextTrack;
	UINT m_preAnimIndex;

	double m_totalTime;
	double m_animPlayTime;
	double m_preTrackPos;
	double m_preSaturPos;

	bool m_isReverse;
};