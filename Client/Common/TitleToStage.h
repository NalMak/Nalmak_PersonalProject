#pragma once
#include "Component.h"
class TitleToStage :
	public Component
{
public:
	struct Desc
	{

	};
public:
	TitleToStage(Desc* _desc);
	~TitleToStage();

	// Component��(��) ���� ��ӵ�
	virtual void Initialize() override;
	virtual void Update() override;
};

