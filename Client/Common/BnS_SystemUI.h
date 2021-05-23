#pragma once
#include "Component.h"
class BnS_SystemUI :
	public Component
{
public:
	struct Desc {

	};
public:
	BnS_SystemUI(Desc* _desc);
	~BnS_SystemUI();

	// Component��(��) ���� ��ӵ�
	virtual void Initialize() override;
	virtual void Update() override;

private:
	Text* m_text;
	float m_notifyTimer;
	float m_alpha;
public:
	void Notify(const wstring& _text);
};

