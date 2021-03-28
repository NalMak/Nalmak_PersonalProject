#pragma once
#include "Scene.h"

class BaseScene :
	public Scene
{
public:
	BaseScene();
	~BaseScene();

	// Scene을(를) 통해 상속됨
	virtual void Initialize() override;
};

