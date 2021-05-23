#pragma once
#include "Component.h"
class BnS_AttackArea_ScaleAnim :
	public Component
{
public:
	struct Desc
	{
		float lifeTime;
		Vector3 targetScale;
		Vector3 startScale;
	};
public:
	BnS_AttackArea_ScaleAnim(Desc* _desc);
	~BnS_AttackArea_ScaleAnim();

	// Component을(를) 통해 상속됨
	virtual void Initialize() override;
	virtual void Update() override;
private:
	float m_lifeTime;
	float m_totalLifeTime;

	Vector3 m_targetScale;
	Vector3 m_startScale;
};

