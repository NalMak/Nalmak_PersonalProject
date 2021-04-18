#pragma once
#include "Nalmak_Include.h"
#include "AnimationTransition.h"

class NALMAK_DLL AnimationClip
{
public:
	AnimationClip();
	~AnimationClip();
public:
	void Release();
public:
	string animationName = "";
	float speed = 1;
	vector<AnimationTransition*> transtionInfos;
	bool reverse = false;
	bool loop = false;

	LPD3DXANIMATIONSET animationSet = nullptr;
};

