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

	// Component��(��) ���� ��ӵ�
	virtual void Initialize() override;
	virtual void Update() override;
	virtual void Release()override;
private:
	GameObject* m_soulBlade[2];
};

