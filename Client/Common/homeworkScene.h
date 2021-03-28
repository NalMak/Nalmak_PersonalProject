#pragma once
#include "Scene.h"
class homeworkScene :
	public Scene
{
public:
	homeworkScene();
	~homeworkScene();

private:
	// Scene을(를) 통해 상속됨
	virtual void Initialize() override;
};

