#pragma once
#include "Scene.h"
class TitleScene :
	public Scene
{
public:
	TitleScene();
	~TitleScene();

	// Scene을(를) 통해 상속됨
	virtual void Initialize() override;
};

