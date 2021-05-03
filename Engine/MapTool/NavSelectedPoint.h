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

	// Component을(를) 통해 상속됨
	virtual void Initialize() override;
	virtual void Update() override;
};

