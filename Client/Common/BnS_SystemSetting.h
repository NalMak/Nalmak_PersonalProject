#pragma once
#include "Component.h"
class BnS_SystemSetting :
	public Component
{
public:
	struct Desc
	{

	};
public:
	BnS_SystemSetting(Desc* _desc);
	~BnS_SystemSetting();

	// Component��(��) ���� ��ӵ�
	virtual void Initialize() override;
	virtual void Update() override;
private:
	bool m_rockMouse;
};

