#pragma once
#include "Component.h"
class BnS_AttackArea :
	public Component
{
public:
	struct Desc
	{
		wstring mtrlName = L"";
		float timer = 3.f;
	};
public:
	BnS_AttackArea(Desc* _desc);
	~BnS_AttackArea();

	// Component을(를) 통해 상속됨
	virtual void Initialize() override;
	virtual void Update() override;
	virtual void EachRender() override;
private:
	Material* m_attackAreaMtrl;
	float m_timer;
	float m_totalTimer;
};

