#include "stdafx.h"
#include "LynSkillController.h"
#include "LynInfo.h"
#include "LynStateControl.h"



LynSkillController::LynSkillController(Desc * _desc)
{
	auto thunderCut = BnS_Skill(L"thunderSlash",BNS_SKILL_SLOT_X , L"skill_Icon85", 12.f, KEY_STATE_X, true, [](LynInfo* _info)->bool {
		if (_info->m_target)
			return true;
		return false;
	});
	m_skillInfo.emplace_back(thunderCut);

	auto backStep = BnS_Skill(L"backStep", BNS_SKILL_SLOT_SS, L"skill_Icon46", 2.f, KEY_STATE_S, true, [](LynInfo* _info)->bool {
		if (_info->m_sKeyTimer > 0)
		{
			_info->m_sKeyTimer = 0;
			return true;
		}
		return false;
	});
	m_skillInfo.emplace_back(backStep);

	auto baldo = BnS_Skill(L"baldo", BNS_SKILL_SLOT_LB, L"skill_Icon69", 0.f, KEY_STATE_LEFT_MOUSE, false, [](LynInfo* _info)->bool {
		if(_info->GetEnergy() >= 1 && _info->m_state == LYN_STATE_BATTLE_HIDEBLADE && _info->m_target)
			return true;
		return false;
	});
	m_skillInfo.emplace_back(baldo);

	auto slash1 = BnS_Skill(L"slash1", BNS_SKILL_SLOT_LB, L"skill_Icon00", 0.f, KEY_STATE_LEFT_MOUSE, true, [](LynInfo* _info)->bool {
		if(_info->m_state != LYN_STATE_BATTLE_HIDEBLADE)
			return true;
		return false;
	});
	m_skillInfo.emplace_back(slash1);

	auto verticalCut = BnS_Skill(L"verticalCut_l0", BNS_SKILL_SLOT_RB, L"skill_Icon83", 0.f, KEY_STATE_RIGHT_MOUSE,false, [](LynInfo* _info)->bool {
		if (_info->GetEnergy() >= 2 && _info->m_state != LYN_STATE_BATTLE_HIDEBLADE)
			return true;
		return false;
	});
	m_skillInfo.emplace_back(verticalCut);

	auto sideDashQ = BnS_Skill(L"sideDashQ", BNS_SKILL_SLOT_Q, L"skill_Icon76", 2.f, KEY_STATE_Q, true, [](LynInfo* _info)->bool {
		if(_info->m_target)
			return true;
		return false;
	});
	m_skillInfo.emplace_back(sideDashQ);

	auto sideDashE = BnS_Skill(L"sideDashE", BNS_SKILL_SLOT_E, L"skill_Icon27", 2.f, KEY_STATE_E,true, [](LynInfo* _info)->bool {
		if (_info->m_target)
			return true;
		return false;

	});
	m_skillInfo.emplace_back(sideDashE);

	auto spinSlash = BnS_Skill(L"spinSlash_start", BNS_SKILL_SLOT_TAB, L"skill_Icon96", 0.f, KEY_STATE_TAB, true, [](LynInfo* _info)->bool {
		if (_info->GetEnergy() >= 2)
			return true;
		return false;
	});
	m_skillInfo.emplace_back(spinSlash);

	auto lightningSlash = BnS_Skill(L"lightningSlash", BNS_SKILL_SLOT_C, L"skill_Icon20", 2.f, KEY_STATE_C,false, [](LynInfo* _info)->bool {
		return true;
	});
	m_skillInfo.emplace_back(lightningSlash);
}

LynSkillController::~LynSkillController()
{
}

void LynSkillController::Initialize()
{
	m_info = GetComponent<LynInfo>();
}

void LynSkillController::Update()
{

}

void LynSkillController::ActiveSkill()
{
	float deltaTime = dTime;
	for (auto& skill : m_skillInfo)
	{
		if (InputManager::GetInstance()->GetKeyDown(skill.m_actionKey))
		{
			if (skill.m_remainTime <= 0.f)
			{
				if (skill.m_activationCondition(m_info))
				{
					skill.m_remainTime = skill.m_coolTime;
					if (skill.m_isCombined)
					{
						m_info->m_stateControl_upper->SetState(skill.m_stateName);
						m_info->m_stateControl_lower->SetState(skill.m_stateName);
					}
					else
					{
						m_info->m_stateControl_upper->SetState(skill.m_stateName);
						if(m_info->m_dirState == LYN_MOVE_DIR_STATE_NONE)
							m_info->m_stateControl_lower->SetState(skill.m_stateName);
					}
					return;
				}
			}
		}

		if (skill.m_remainTime > 0)
			skill.m_remainTime -= deltaTime;
	}
}
