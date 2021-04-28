#pragma once
#include "Component.h"
class BnS_MainCamera :
	public Component
{
public:
	struct Desc
	{

	};
public:
	BnS_MainCamera(Desc* _desc);
	~BnS_MainCamera();

	// Component을(를) 통해 상속됨
	virtual void Initialize() override;
	virtual void Update() override;
	virtual void OnTriggerEnter(Collisions& _col) override;
	virtual void OnTriggerStay(Collisions& _col) override;
	virtual void OnTriggerExit(Collisions& _col) override;
private:

};

