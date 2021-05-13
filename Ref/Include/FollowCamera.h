#pragma once
#include "Component.h"
class NALMAK_DLL FollowCamera :
	public Component
{
public:
	struct Desc
	{

	};
public:
	FollowCamera(Desc* _desc);
	~FollowCamera();
private:
	// Component을(를) 통해 상속됨
	virtual void Initialize() override;

	virtual void Update() override;
private:
	class Transform* m_camTrans;
};

