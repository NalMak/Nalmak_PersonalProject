#include "stdafx.h"
#include "LynSkillController.h"
#include "LynInfo.h"
#include "LynStateControl.h"
#include "UIManager.h"
#include "BnS_Skill.h"
#include "EnemyState.h"


LynSkillController::LynSkillController(Desc * _desc)
{
	CreateSkill(L"thunderSlash", L"천둥베기", BNS_SKILL_SLOT_X, L"skill_Icon85", 4.f, KEY_STATE_X, true,true,0,16,0,[](LynInfo* _info)->bool {
		return true;
	});

	CreateSkill(L"backStep", L"백스텝", BNS_SKILL_SLOT_SS, L"skill_Icon46", 9.f, KEY_STATE_S, true,false, 0, 0, 0, [=](LynInfo* _info)->bool {
		if (_info->GetBattleState() == BATTLE_STATE_DOWN || _info->GetBattleState() == BATTLE_STATE_KNOCKBACK || _info->GetBattleState() == BATTLE_STATE_GROGY)
			return false;

		if (m_sKeyTimer > 0)
		{
			m_sKeyTimer = 0;
			return true;
		}
		return false;
	});


	CreateSkill(L"backRoll", L"뒤구르기", BNS_SKILL_SLOT_F, L"skill_Icon64", 9.f, KEY_STATE_F, true, true,0,0,0, [](LynInfo* _info)->bool {
		return true;
	});


	CreateSkill(L"baldo", L"발도", BNS_SKILL_SLOT_LB, L"skill_Icon69", 0.2f, KEY_STATE_LEFT_MOUSE, false, true,0,4,1,[](LynInfo* _info)->bool {
			if(_info->GetTarget())
				return true;
			return false;
	});

	CreateSkill(L"slash1", L"질풍", BNS_SKILL_SLOT_LB, L"skill_Icon00", 0.f, KEY_STATE_LEFT_MOUSE, true,true,0,0,0, [](LynInfo* _info)->bool {
		return true;
	});

	
	CreateSkill(L"verticalCut_l0", L"가르기", BNS_SKILL_SLOT_RB, L"skill_Icon83", 0.3f, KEY_STATE_RIGHT_MOUSE, false, true, 0,0,1,[](LynInfo* _info)->bool {
		if (_info->GetInnerPower() > 1)
			return true;
		else
			return false;
	});
	
	CreateSkill(L"sideDashQ", L"횡이동", BNS_SKILL_SLOT_Q, L"skill_Icon76", 6.f, KEY_STATE_Q, true,false, 0,3,0,[](LynInfo* _info)->bool {
		if (_info->GetBattleState() == BATTLE_STATE_DOWN || _info->GetBattleState() == BATTLE_STATE_KNOCKBACK || _info->GetBattleState() == BATTLE_STATE_GROGY)
			return false;

		if (_info->GetTarget())
			return true;
		return false;
	});

	CreateSkill(L"sideDashE", L"횡이동", BNS_SKILL_SLOT_E, L"skill_Icon27", 6.f, KEY_STATE_E, true,false,0,3,0, [](LynInfo* _info)->bool {
		if (_info->GetBattleState() == BATTLE_STATE_DOWN || _info->GetBattleState() == BATTLE_STATE_KNOCKBACK || _info->GetBattleState() == BATTLE_STATE_GROGY)
			return false;

		if (_info->GetTarget())
			return true;
		return false;
	});

	CreateSkill(L"spinSlash_start", L"바람개비", BNS_SKILL_SLOT_TAB, L"skill_Icon96", 0.5f, KEY_STATE_TAB, true, true,0,0,2, [](LynInfo* _info)->bool {
		return true;
	});

	CreateSkill(L"lightningSlash", L"번개베기", BNS_SKILL_SLOT_C, L"skill_Icon20", 20.f, KEY_STATE_C, false, true,0,0,0, [](LynInfo* _info)->bool {
		return true;
	});

	CreateSkill(L"chamWall", L"참월", BNS_SKILL_SLOT_V, L"skill_Icon77", 12.f, KEY_STATE_V, true, true,0,3,3, [](LynInfo* _info)->bool {
		if (_info->GetTarget())
			return true;
		return false;
	});

	CreateSkill(L"frontKick", L"발차기", BNS_SKILL_SLOT_1, L"skill_Icon34", 6.f, KEY_STATE_1, true, true,0,3,1, [](LynInfo* _info)->bool {
		if (_info->GetTarget())
			return true;
		return false;
	});

	CreateSkill(L"frontDash", L"돌진", BNS_SKILL_SLOT_2, L"skill_Icon22", 8.f, KEY_STATE_2, true, true,0,16,0, [](LynInfo* _info)->bool {
		return true;
	});

	CreateSkill(L"lowerSlash", L"하단베기", BNS_SKILL_SLOT_3, L"skill_Icon08", 4.f, KEY_STATE_3, false, true,0,0,2, [](LynInfo* _info)->bool {
		return true;
	});

	CreateSkill(L"hold", L"흡공", BNS_SKILL_SLOT_4, L"skill_Icon95", 16.f, KEY_STATE_4, false, true, 0,8,2,[](LynInfo* _info)->bool {
		if (_info->GetTarget())
		{
			auto battleState = _info->GetTarget()->GetComponent<BnS_Enemy>()->GetBattleState();
			if(battleState == BATTLE_STATE_DOWN || battleState == BATTLE_STATE_GROGY || battleState == BATTLE_STATE_STUN)
				return true;
			return false;
		}
		return false;
	});

	CreateSkill(L"rotateSoulBlade", L"귀검령", BNS_SKILL_SLOT_Z, L"skill_Icon75", 24.f, KEY_STATE_Z, true,true,0,0,0, [](LynInfo* _info)->bool {
		return true;
	});


	CreateSkill(L"throwSoulBlade", L"비연검", BNS_SKILL_SLOT_1, L"skill_Icon04", 5.f, KEY_STATE_1, false,true, 3, 16, 0, [](LynInfo* _info)->bool {
		if (_info->GetTarget())
			return true;
		return false;
	});

	CreateSkill(L"upperSlash", L"올려베기", BNS_SKILL_SLOT_F, L"skill_Icon09", 16.f, KEY_STATE_F, true, true, 0, 5, 0, [](LynInfo* _info)->bool {
		if (_info->GetTarget())
			return true;
		return false;
	});

	CreateSkill(L"thunderbolt", L"벼락", BNS_SKILL_SLOT_F, L"skill_Icon29", 8.f, KEY_STATE_F, true, true, 0, 4, 0, [](LynInfo* _info)->bool {
		if (_info->GetTarget())
			return true;
		return false;
	});

	CreateSkill(L"starAttack",L"비상", BNS_SKILL_SLOT_LB, L"skill_Icon16", 0.f, KEY_STATE_LEFT_MOUSE, true, true, 0, 5, 1, [](LynInfo* _info)->bool {
		if (_info->GetTarget())
			return true;
		return false;
	});

	CreateSkill(L"lightningCombo", L"뇌연섬", BNS_SKILL_SLOT_F, L"skill_Icon80", 0.2f, KEY_STATE_F, false, true, 0, 4, 0, [](LynInfo* _info)->bool {
		return _info->UseLightningSpirit();
	});

	CreateSkill(L"excape", L"탈출", BNS_SKILL_SLOT_TAB, L"skill_Icon10", 15.f, KEY_STATE_TAB, true, true, 0, 0, 0, [](LynInfo* _info)->bool {
		return true;
	});

	CreateSkill(L"ilsum", L"일섬", BNS_SKILL_SLOT_RB, L"skill_Icon81", 12.f, KEY_STATE_RIGHT_MOUSE, true, true, 0, 0, 0, [](LynInfo* _info)->bool {
		return true;
	});

	CreateSkill(L"atkBuff", L"공버프", BNS_SKILL_SLOT_BUFF, L"skill_Icon97", 0.f, KEY_STATE_RIGHT_MOUSE, true, true, 0, 0, 0, [](LynInfo* _info)->bool {
		return true;
	});

	CreateSkill(L"crash", L"추락", BNS_SKILL_SLOT_RB, L"skill_Icon17", 0.f, KEY_STATE_RIGHT_MOUSE, true, true, 0, 0, 0, [](LynInfo* _info)->bool {
		if (_info->GetTarget())
			return true;
		return false;
	});

}

LynSkillController::~LynSkillController()
{
}

void LynSkillController::Initialize()
{
	m_sKeyTimer = 0.f;

	m_info = GetComponent<LynInfo>();
	m_audio = Core::GetInstance()->GetMainCamera()->GetComponent<AudioSource>();
	m_skillRockTex = ResourceManager::GetInstance()->GetResource<Texture>(L"skill_Icon98");

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
	//SetSkillSlot(L"throwSoulBlade");


}

void LynSkillController::Update()
{
}

void LynSkillController::LateUpdate()
{
	
}

void LynSkillController::PreRender()
{
	UpdateSkill();

	if (m_info->m_isProgressSkill)
		return;

	ActiveSkill();

	if (InputManager::GetInstance()->GetKeyDown(KEY_STATE_S))
	{
		m_sKeyTimer = 0.3f;
	}
	m_sKeyTimer -= dTime;

}

void LynSkillController::UpdateSkill()
{
	auto uiMgr = UIManager::GetInstance();
	for (auto& skill : m_baseSkill)
	{
		if (!skill)
			continue;
		if (skill->m_isRenderSlot)
		{
			float coolTimeRatio = skill->m_remainCoolTime / skill->m_coolTime;
			uiMgr->UpdateSkillCoolTime(skill->m_skillSlot, coolTimeRatio);
		}
		
		skill->UpdateAvailableSkill(m_info);

	}
}

void LynSkillController::CreateSkill(const wstring & _stateName, const wstring & _skillName, BNS_SKILL_SLOT _skillSlot, const wstring & _skillIcon,
	float _coolTime, __int64 _actionKey, bool _isCombined, bool _isRenderSlot, float _minDistance, float _maxDistance, 
	UINT _innerForce, activationCondition _condition)
{
	auto obj = INSTANTIATE()->AddComponent<BnS_Skill>();
	auto skill = obj->GetComponent<BnS_Skill>();
	skill->CreateSkill(_stateName, _skillName, _skillSlot, _skillIcon, _coolTime, _actionKey, _isCombined, _condition,_isRenderSlot, _minDistance, _maxDistance, _innerForce);
	m_allSkill[_stateName] = skill;
}

void LynSkillController::SetSkillSlot(const wstring & _name)
{
	auto skill = m_allSkill[_name];

	if (m_baseSkill[skill->m_skillSlot] == skill)
		return;
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

void LynSkillController::RockSkillSlot(BNS_SKILL_SLOT _slot)
{
	UIManager::GetInstance()->RockSkillSlot(_slot, m_skillRockTex, L"잠김");

	m_baseSkill[_slot] = nullptr;
}

void LynSkillController::ChangeSkillSlotByAnimation(const wstring & _name)
{
	auto skill = m_allSkill[_name];
	UIManager::GetInstance()->SetSkillSlot(skill);
	m_baseSkill[skill->m_skillSlot] = skill;
}

void LynSkillController::ReleaseSkill(BNS_SKILL_SLOT _slot)
{
	UIManager::GetInstance()->ReleaseSkillSlot(_slot);
	m_baseSkill[_slot] = nullptr;
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
			
			if (!m_baseSkill[i]->GetAvailable(BNS_SKILL_CONDITION_DISTANCE))
				continue;

			if (!m_baseSkill[i]->GetAvailable(BNS_SKILL_CONDITION_INNERFORCE))
			{
				if (!m_audio->IsPlay())
				{
					m_audio->SetAudioClip(L"sys_notenoughInnerForce");
					m_audio->Play();
				}
				continue;
			}
			if (!m_baseSkill[i]->GetAvailable(BNS_SKILL_CONDITION_EVENT))
				continue;

			if (!m_baseSkill[i]->IsValidEvent(m_info))
				continue;
		

			if (m_baseSkill[i]->GetCoolTime() > 0)
			{
				if (!m_audio->IsPlay())
				{
					m_audio->SetAudioClip(L"sys_cannotUse");
					m_audio->Play();
				}
				continue;
			}
		


			m_baseSkill[i]->ActiveSkill(m_info);

			wstring nextState = m_baseSkill[i]->m_stateName;
			if (m_baseSkill[i]->m_isCombined)
			{
				m_info->m_stateControl_upper->SetState(nextState);
				m_info->m_stateControl_lower->SetState(nextState);
			}
			else
			{
				m_info->m_stateControl_upper->SetState(nextState);
				if(!InputManager::GetInstance()->GetKeyPress(KEY_STATE_W) && 
					!InputManager::GetInstance()->GetKeyPress(KEY_STATE_A) && 
					!InputManager::GetInstance()->GetKeyPress(KEY_STATE_S) && 
					!InputManager::GetInstance()->GetKeyPress(KEY_STATE_D))
					m_info->m_stateControl_lower->SetState(nextState);
			}
			return;
		
		}
	}

}

bool LynSkillController::ActiveSkill(BNS_SKILL_SLOT _slot)
{
	float deltaTime = dTime;

	int i = _slot;
	
	if (!m_baseSkill[i])
		return false;

	if (InputManager::GetInstance()->GetKeyDown(m_baseSkill[i]->m_actionKey))
	{

		if (!m_baseSkill[i]->GetAvailable(BNS_SKILL_CONDITION_DISTANCE))
			return false;

		if (!m_baseSkill[i]->GetAvailable(BNS_SKILL_CONDITION_INNERFORCE))
			return false;

		if (!m_baseSkill[i]->GetAvailable(BNS_SKILL_CONDITION_EVENT))
			return false;

		if (m_baseSkill[i]->GetCoolTime() > 0)
		{
			if (!m_audio->IsPlay())
			{
				m_audio->SetAudioClip(L"sys_cannotUse");
				m_audio->Play();
			}

			return false;
		}


		if (!m_baseSkill[i]->IsValidEvent(m_info))
			return false;

		m_baseSkill[i]->ActiveSkill(m_info);

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
		return true;

	}
	return false;
}

BnS_Skill * LynSkillController::GetSkill(const wstring & _skillName)
{
	return m_allSkill[_skillName];
}
