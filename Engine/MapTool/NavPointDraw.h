#pragma once
#include "Component.h"

class NavPoint;


class NavPointDraw :
	public Component
{
public:
	struct Desc
	{
		NavPoint* navPoint = nullptr;
		NavCell* navCell = nullptr;
	};
public:
	NavPointDraw(Desc* _desc);
	~NavPointDraw();
private:
	// Component을(를) 통해 상속됨
	virtual void Initialize() override;
	virtual void Update() override;

private:
	NavPoint* m_point = nullptr;
	NavCell* m_cell = nullptr;
public:
	void SetPoint(NavPoint* _point);
	void ReverseCell();
	
};

