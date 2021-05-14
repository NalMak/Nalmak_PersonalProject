#pragma once
#include "Component.h"
class LynInfo;
class BnS_Skill;
class BnS_SkillSlot;
class BnS_Buff :
	public Component
{
	using BuffEvent = function<void(LynInfo* _lynInfo)>;
public:
	struct Desc
	{
		float buffTimer;
		BnS_Skill* skill;
		wstring key;
	};
public:
	BnS_Buff(Desc* _desc);
	~BnS_Buff();

	// Component을(를) 통해 상속됨
	virtual void Initialize() override;
	virtual void Update() override;
	virtual void Release() override;

	void BuffOff();
	void SetSkillSlot(BnS_SkillSlot* _slot);
	void AddBuffEvent(BuffEvent _buff, float interval, LynInfo* lynInfo);
private:
	float m_buffTimer;
	float m_timeRemaining;
	float m_eventTimer;
	float m_interval;
	BuffEvent* m_buffEvent;
	LynInfo* m_info;
	BnS_SkillSlot* m_skillSlot;
};

