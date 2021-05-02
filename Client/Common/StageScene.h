#pragma once
#include "Scene.h"
class StageScene :
	public Scene
{
public:
	StageScene();
	~StageScene();

	// Scene을(를) 통해 상속됨
	virtual void Initialize() override;
};

