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
	// Component��(��) ���� ��ӵ�
	virtual void Initialize() override;

	virtual void Update() override;
private:
	class Transform* m_camTrans;
};

