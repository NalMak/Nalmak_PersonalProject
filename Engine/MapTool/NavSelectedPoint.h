#pragma once
#include "Component.h"
class NavSelectedPoint :
	public Component
{
public:
	struct Desc
	{

	};
public:
	NavSelectedPoint(Desc* _desc);
	~NavSelectedPoint();

	// Component��(��) ���� ��ӵ�
	virtual void Initialize() override;
	virtual void Update() override;
};

