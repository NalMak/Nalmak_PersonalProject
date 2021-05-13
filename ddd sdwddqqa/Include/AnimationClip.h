#pragma once
#include "Nalmak_Include.h"
#include "AnimationTransition.h"
#include "IResource.h"

class NALMAK_DLL AnimationClip : public IResource
{
public:
	AnimationClip();
	~AnimationClip();
public:
	virtual void Initialize(wstring _fp) override;
	virtual void Release() override;
public:
	string animationName = "";
	float speed = 1;
	bool reverse = false;
	bool loop = false;

	LPD3DXANIMATIONSET animationSet = nullptr;


};

