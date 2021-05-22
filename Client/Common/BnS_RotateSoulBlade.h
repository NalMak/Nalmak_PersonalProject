#pragma once
#include "Component.h"
class BnS_RotateSoulBlade :
	public Component
{
public:
	struct Desc {

	};
public:
	BnS_RotateSoulBlade(Desc* _desc);
	~BnS_RotateSoulBlade();

	// Component을(를) 통해 상속됨
	virtual void Initialize() override;
	virtual void Update() override;
	virtual void Release()override;
private:
	TrailRenderer* m_soulBlade[2];

	GameObject* m_trailFollowObj[2];
};

