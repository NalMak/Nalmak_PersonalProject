#pragma once
#include "Scene.h"
class TitleScene :
	public Scene
{
public:
	TitleScene();
	~TitleScene();

	// Scene��(��) ���� ��ӵ�
	virtual void Initialize() override;
};

