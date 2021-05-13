#include "stdafx.h"
#include "LynSkillController.h"
#include "LynInfo.h"
#include "LynStateControl.h"
#include "UIManager.h"
#include "BnS_Skill.h"


LynSkillController::LynSkillController(Desc * _desc)
{
	CreateSkill(L"thunderSlash", BNS_SKILL_SLOT_X, L"skill_Icon85", 4.f, KEY_STATE_X, true,true, [](LynInfo* _info)->bool {
		if (_info->GetTarget())
		{
			if(BETWEEN(_info->GetDistanceToTarget(),0,16))
				return true;
		}
		return false;
	});

	CreateSkill(L"backStep", BNS_SKILL_SLOT_SS, L"skill_Icon46", 2.f, KEY_STATE_S, true,false, [](LynInfo* _info)->bool {
		if (_info->m_sKeyTimer > 0)
		{
			_info->m_sKeyTimer = 0;
			return true;
		}
		return false;
	});

	CreateSkill(L"baldo", BNS_SKILL_SLOT_LB, L"skill_Icon69", 0.f, KEY_STATE_LEFT_MOUSE, false, true,[](LynInfo* _info)->bool {
		if (_info->m_target)
		{
			if (_info->GetInnerPower() > 0)
			{
				if (BETWEEN(_info->GetDistanceToTarget(), 0, 3))
					return true;
			}
		}
		return false;
	});

	CreateSkill(L"slash1", BNS_SKILL_SLOT_LB, L"skill_Icon00", 0.f, KEY_STATE_LEFT_MOUSE, true,true, [](LynInfo* _info)->bool {
		return true;
	});

	
	CreateSkill(L"verticalCut_l0", BNS_SKILL_SLOT_RB, L"skill_Icon83", 0.f, KEY_STATE_RIGHT_MOUSE, false, true, [](LynInfo* _info)->bool {
		if (_info->GetInnerPower() >= 2)
			return true;
		return false;
	});
	
	CreateSkill(L"sideDashQ", BNS_SKILL_SLOT_Q, L"skill_Icon76", 6.f, KEY_STATE_Q, true,false, [](LynInfo* _info)->bool {
		if (_info->m_target)
		{
			if (BETWEEN(_info->GetDistanceToTarget(), 0, 3))
			{
				return true;
			}
		}
		return false;
	});

	CreateSkill(L"sideDashE", BNS_SKILL_SLOT_E, L"skill_Icon27", 6.f, KEY_STATE_E, true,false, [](LynInfo* _info)->bool {
		if (_info->m_target)
		{
			if (BETWEEN(_info->GetDistanceToTarget(), 0, 3))
			{
				return true;
			}
		}
		return false;
	});

	CreateSkill(L"spinSlash_start", BNS_SKILL_SLOT_TAB, L"skill_Icon96", 0.f, KEY_STATE_TAB, true, true, [](LynInfo* _info)->bool {
		if (_info->GetInnerPower() >= 2)
			return true;
		return false;
	});

	CreateSkill(L"lightningSlash", BNS_SKILL_SLOT_C, L"skill_Icon20", 20.f, KEY_STATE_C, false, true, [](LynInfo* _info)->bool {
		return true;
	});

	CreateSkill(L"chamWall", BNS_SKILL_SLOT_V, L"skill_Icon77", 12.f, KEY_STATE_V, true, true, [](LynInfo* _info)->bool {
		if (_info->GetTarget())
		{
			if (_info->GetInnerPower() >= 3)
			{
				if (BETWEEN(_info->GetDistanceToTarget(), 0, 3))
				{
					return true;
				}
			}
		}
		return false;
	});

	CreateSkill(L"frontKick", BNS_SKILL_SLOT_1, L"skill_Icon34", 6.f, KEY_STATE_1, true, true, [](LynInfo* _info)->bool {
		if (_info->GetTarget())
		{
			if (_info->GetInnerPower() >= 1)
			{
				if (BETWEEN(_info->GetDistanceToTarget(), 0, 3))
				{
					return true;
				}
			}
		}
		return false;
	});

	CreateSkill(L"frontDash", BNS_SKILL_SLOT_2, L"skill_Icon22", 8.f, KEY_STATE_2, true, true, [](LynInfo* _info)->bool {
		if (_info->GetTarget())
		{
			if (BETWEEN(_info->GetDistanceToTarget(), 0, 16))
			{
				return true;

			}
		}
		return false;
	});

	CreateSkill(L"lowerSlash", BNS_SKILL_SLOT_3, L"skill_Icon08", 4.f, KEY_STATE_3, false, true, [](LynInfo* _info)->bool {
		if (_info->GetInnerPower() >= 2)
		{
			return true;
		}
		return false;
	});

	CreateSkill(L"hold", BNS_SKILL_SLOT_4, L"skill_Icon95", 16.f, KEY_STATE_4, false, true, [](LynInfo* _info)->bool {
		if (_info->GetTarget())
		{
			if (_info->GetInnerPower() >= 1)
			{
				if (BETWEEN(_info->GetDistanceToTarget(), 0, 8))
				{
					return true;
				}
			}
		}
		return false;
	});

	CreateSkill(L"rotateSoulBlade", BNS_SKILL_SLOT_Z, L"skill_Icon75", 16.f, KEY_STATE_Z, true,true, [](LynInfo* _info)->bool {
		return true;
	});


	CreateSkill(L"throwSoulBlade", BNS_SKILL_SLOT_1, L"skill_Icon04", 5.f, KEY_STATE_1, false,true, [](LynInfo* _info)->bool {
		if (_info->GetTarget())
		{
			if (BETWEEN(_info->GetDistanceToTarget(), 4,16))
			{
				return true;
			}
		}
		return false;
	});
}

LynSkillController::~LynSkillController()
{
}

void LynSkillController::Initialize()
{
	m_info = GetComponent<LynInfo>();


	SetSkillSlot(L"thunderSlash");
	SetSkillSlot(L"backStep");
	SetSkillSlot(L"baldo");
	SetSkillSlot(L"slash1");

	SetSkillSlot(L"verticalCut_l0");
	SetSkillSlot(L"sideDashQ");
	SetSkillSlot(L"sideDashE");
	SetSkillSlot(L"spinSlash_start");
	SetSkillSlot(L"lightningSlash");
	SetSkillSlot(L"chamWall");
	SetSkillSlot(L"frontKick");
	SetSkillSlot(L"frontDash");
	SetSkillSlot(L"lowerSlash");
	SetSkillSlot(L"hold");
	SetSkillSlot(L"rotateSoulBlade");
	SetSkillSlot(L"throwSoulBlade");


}

void LynSkillController::Update()
{
	auto uiMgr = UIManager::GetInstance();
	for (auto& skill : m_baseSkill)
	{
		if(!skill)
			continue;
		if(skill->m_coolTime == 0)
			continue;
		if(!skill->m_isRenderSlot)
			continue;

		float coolTimeRatio = skill->m_remainCoolTime / skill->m_coolTime;
		
		uiMgr->UpdateSkillCoolTime(skill->m_skillSlot, coolTimeRatio);
		
	}
}

void LynSkillController::CreateSkill(const wstring & _stateName, BNS_SKILL_SLOT _skillSlot, const wstring & _skillIcon, float _coolTime, __int64 _actionKey, bool _isCombined, bool _isRenderSlot, activationCondition _condition)
{
	auto obj = INSTANTIATE()->AddComponent<BnS_Skill>();
	auto skill = obj->GetComponent<BnS_Skill>();
	skill->CreateSkill(_stateName, _skillSlot, _skillIcon, _coolTime, _actionKey, _isCombined, _condition,_isRenderSlot);
	m_allSkill[_stateName] = skill;
}

void LynSkillController::SetSkillSlot(const wstring & _name)
{
	auto skill = m_allSkill[_name];
	if(skill->m_isRenderSlot)
		UIManager::GetInstance()->SetSkillSlot(skill);
	m_baseSkill[skill->m_skillSlot] = skill;
}

void LynSkillController::ChangeSkillSlot(const wstring & _name)
{
	auto skill = m_allSkill[_name];
	UIManager::GetInstance()->ChangeSkillSlot(skill);
	m_baseSkill[skill->m_skillSlot] = skill;
}

void LynSkillController::ReleaseSkill(BNS_SKILL_SLOT _slot)
{
	UIManager::GetInstance()->ReleaseSkillSlot(_slot);
}

void LynSkillController::ActiveSkill()
{
	float deltaTime = dTime;

	for (int i = 0; i < BNS_SKILL_SLOT_MAX; ++i)
	{
		if(!m_baseSkill[i])
			continue;

		if (InputManager::GetInstance()->GetKeyDown(m_baseSkill[i]->m_actionKey))
		{
			if (m_baseSkill[i]->m_remainCoolTime <= 0.f)
			{
				if (m_baseSkill[i]->m_activationCondition(m_info))
				{
					m_baseSkill[i]->m_remainCoolTime = m_baseSkill[i]->m_coolTime;
					if (m_baseSkill[i]->m_isCombined)
					{
						m_info->m_stateControl_upper->SetState(m_baseSkill[i]->m_stateName);
						m_info->m_stateControl_lower->SetState(m_baseSkill[i]->m_stateName);
					}
					else
					{
						m_info->m_stateControl_upper->SetState(m_baseSkill[i]->m_stateName);
						if (m_info->m_dirState == LYN_MOVE_DIR_STATE_NONE)
							m_info->m_stateControl_lower->SetState(m_baseSkill[i]->m_stateName);
					}
					return;
				}
			}
		}
	}

}
