#pragma once
#include "Scene.h"
class homeworkScene :
	public Scene
{
public:
	homeworkScene();
	~homeworkScene();

private:
	// Scene��(��) ���� ��ӵ�
	virtual void Initialize() override;
};

