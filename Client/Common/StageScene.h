#pragma once
#include "Scene.h"
class StageScene :
	public Scene
{
public:
	StageScene();
	~StageScene();

	// Scene��(��) ���� ��ӵ�
	virtual void Initialize() override;
};

