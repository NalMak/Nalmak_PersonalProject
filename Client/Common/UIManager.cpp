#include "stdafx.h"
#include "UIManager.h"
#include "BnS_SkillSlot.h"
#include "BnS_Skill.h"
#include "BnS_Enemy.h"
#include "LynInfo.h"
#include "BnS_Buff.h"
#include "BnS_InnerForceAnimation.h"
IMPLEMENT_SINGLETON(UIManager)

UIManager::UIManager()
{
}


UIManager::~UIManager()
{
}

void UIManager::CreateMainUI()
{
	{
		SingleImage::Desc image;
		image.textureName = L"bns_bossHP_outLine";
		INSTANTIATE()->AddComponent<CanvasRenderer>()->AddComponent<SingleImage>(&image)->SetScale(450, 18)->SetPosition(HALF_WINCX, 120);
	}
	{
		SingleImage::Desc image;
		image.textureName = L"bns_bossHp";
		CanvasRenderer::Desc canvas;
		canvas.mtrlName = L"UI_BossHp";
		auto obj = INSTANTIATE()->AddComponent<CanvasRenderer>(&canvas)->AddComponent<SingleImage>(&image)->SetScale(442, 14)->SetPosition(HALF_WINCX, 120);
		m_bossHpBar = obj->GetComponent<CanvasRenderer>()->GetMaterial();
	}
	{
		SingleImage::Desc image;
		image.textureName = L"bns_bossHp_deco";
		INSTANTIATE()->AddComponent<CanvasRenderer>()->AddComponent<SingleImage>(&image)->SetScale(115, 50)->SetPosition(HALF_WINCX - 253, 112);
	}
	{
		SingleImage::Desc image;
		image.textureName = L"bns_bossRegistance";
		INSTANTIATE()->AddComponent<CanvasRenderer>()->AddComponent<SingleImage>(&image)->SetScale(40, 10)->SetPosition(HALF_WINCX - 200, 140);
	}
	{
		SingleImage::Desc image;
		image.textureName = L"bns_bossRegistanceInner";
		INSTANTIATE()->AddComponent<CanvasRenderer>()->AddComponent<SingleImage>(&image)->SetScale(38, 8)->SetPosition(HALF_WINCX - 200, 140);
	}



	{
		SingleImage::Desc image;
		image.textureName = L"GameUI_gauge_outLine";
		INSTANTIATE()->AddComponent<CanvasRenderer>()->AddComponent<SingleImage>(&image)->SetScale(340, 17)->SetPosition(HALF_WINCX , WINCY - 230);
	}
	{
		SingleImage::Desc image;
		image.textureName = L"GameUI_hp";
		CanvasRenderer::Desc canvas;
		canvas.mtrlName = L"UI_Hp";
		auto obj = INSTANTIATE()->AddComponent<CanvasRenderer>(&canvas)->AddComponent<SingleImage>(&image)->SetScale(336, 13)->SetPosition(HALF_WINCX , WINCY - 230);
		m_hpBar = obj->GetComponent<CanvasRenderer>()->GetMaterial();
	}

	{
		SingleImage::Desc image;
		image.textureName = L"GameUI_energyGauge";
		
		INSTANTIATE()->AddComponent<CanvasRenderer>()->AddComponent<SingleImage>(&image)->SetScale(340, 28)->SetPosition(HALF_WINCX, WINCY - 205);

		for (int i = 0; i < 10; ++i)
		{
			BnS_InnerForceAnimation::Desc image;
			image.texName = L"GameUI_energyIcon";
			CanvasRenderer::Desc canvas;
			canvas.mtrlName = L"UI_InnerForce";
			auto innerPower = INSTANTIATE()->AddComponent<CanvasRenderer>(&canvas)->AddComponent<BnS_InnerForceAnimation>(&image)->SetScale(24.f,24.f)->SetPosition((float)(HALF_WINCX - 145 + 32.1f * i), (float)(WINCY - 205));
			m_innerPowerIcon[i] = innerPower->GetComponent<CanvasRenderer>();

		}
	}


	{
		SingleImage::Desc image;
		image.textureName = L"GameUI_gauge_outLine";
		INSTANTIATE()->AddComponent<CanvasRenderer>()->AddComponent<SingleImage>(&image)->SetScale(340, 17)->SetPosition(HALF_WINCX, WINCY - 180);
	}
	{
		SingleImage::Desc image;
		image.textureName = L"GameUI_energy";
		CanvasRenderer::Desc canvas;
		canvas.mtrlName = L"UI_Energy";
		auto obj = INSTANTIATE()->AddComponent<CanvasRenderer>(&canvas)->AddComponent<SingleImage>(&image)->SetScale(336, 13)->SetPosition(HALF_WINCX, WINCY - 180);
		m_energyBarRenderer = obj->GetComponent<CanvasRenderer>();
		m_energyBarImage = obj->GetComponent<SingleImage>();
	}

	//for (int i = 0; i < 10; ++i)
	//{
	//	m_subSkillSlot[BNS_SKILL_SLOT_Q] = CreateSkillIcon(BNS_SKILL_SLOT_Q, HALF_WINCX - 360, WINCY - 510); // ÁúÇ³
	//}

	//m_skillSlot[BNS_SKILL_SLOT_Q] = CreateSkillIcon(BNS_SKILL_SLOT_Q, HALF_WINCX - 360, WINCY - 510); // ÁúÇ³
	//m_skillSlot[BNS_SKILL_SLOT_E] = CreateSkillIcon(BNS_SKILL_SLOT_E, HALF_WINCX - 420, WINCY - 510); // ÁúÇ³
	//m_skillSlot[BNS_SKILL_SLOT_SS] = CreateSkillIcon(BNS_SKILL_SLOT_SS, HALF_WINCX - 480, WINCY - 510); // ÁúÇ³

	m_skillSlot[BNS_SKILL_SLOT_LB] = CreateSkillIcon(BNS_SKILL_SLOT_LB, HALF_WINCX + 210, WINCY - 210); // ÁúÇ³
	m_skillSlot[BNS_SKILL_SLOT_RB] = CreateSkillIcon(BNS_SKILL_SLOT_RB, HALF_WINCX + 270, WINCY - 210); // °¡¸£±â
	m_skillSlot[BNS_SKILL_SLOT_TAB] = CreateSkillIcon(BNS_SKILL_SLOT_TAB, HALF_WINCX - 210, WINCY - 210); // Å»Ãâ tab
	m_skillSlot[BNS_SKILL_SLOT_F] = CreateSkillIcon(BNS_SKILL_SLOT_F, HALF_WINCX - 270, WINCY - 210); // ³ú¿¬¼¶ f

	// ¹Ù¶÷°³ºñ Èí°ø 
	m_skillSlot[BNS_SKILL_SLOT_1] = CreateSkillIcon(BNS_SKILL_SLOT_1, HALF_WINCX - 220, WINCY - 90); // 1
	m_skillSlot[BNS_SKILL_SLOT_2] = CreateSkillIcon(BNS_SKILL_SLOT_2, HALF_WINCX - 160, WINCY - 90); // 2
	m_skillSlot[BNS_SKILL_SLOT_3] = CreateSkillIcon(BNS_SKILL_SLOT_3, HALF_WINCX - 100, WINCY - 90); // 3
	m_skillSlot[BNS_SKILL_SLOT_4] = CreateSkillIcon(BNS_SKILL_SLOT_4, HALF_WINCX - 40, WINCY - 90); // 4
	m_skillSlot[BNS_SKILL_SLOT_Z] = CreateSkillIcon(BNS_SKILL_SLOT_Z, HALF_WINCX + 40, WINCY - 90); // ±Í°Ë·É
	m_skillSlot[BNS_SKILL_SLOT_X] = CreateSkillIcon(BNS_SKILL_SLOT_X, HALF_WINCX + 100, WINCY - 90); // x
	m_skillSlot[BNS_SKILL_SLOT_C] = CreateSkillIcon(BNS_SKILL_SLOT_C, HALF_WINCX + 160, WINCY - 90); // c ÃµµÕº£±â
	m_skillSlot[BNS_SKILL_SLOT_V] = CreateSkillIcon(BNS_SKILL_SLOT_V, HALF_WINCX + 220, WINCY - 90); // v Âü¿ù


	//CreateSkillIcon(L"skill_Icon46", 1000, 600); // ss
	//CreateSkillIcon(L"skill_Icon76", 1000, 600); // q
	//CreateSkillIcon(L"skill_Icon27", 1000, 600); // e


	//skill_Icon64 µÚ±¸¸£±â

	
	


	{
		SingleImage::Desc image;
		image.textureName = L"GameUI_HUDIcon_over";
		INSTANTIATE()->AddComponent<CanvasRenderer>()->AddComponent<SingleImage>(&image)->SetScale(60, 60)->SetPosition(WINCX - 40, WINCY - 50);
	}
	{
		SingleImage::Desc image;
		image.textureName = L"GameUI_GoodsStore_over";
		INSTANTIATE()->AddComponent<CanvasRenderer>()->AddComponent<SingleImage>(&image)->SetScale(60, 60)->SetPosition(WINCX - 120, WINCY - 50);
	}
	{
		SingleImage::Desc image;
		image.textureName = L"GameUI_NShop_over";
		INSTANTIATE()->AddComponent<CanvasRenderer>()->AddComponent<SingleImage>(&image)->SetScale(60, 60)->SetPosition(WINCX -200 ,WINCY - 50);
	}
	{
		SingleImage::Desc image;
		image.textureName = L"GameUI_Lv";
		INSTANTIATE()->AddComponent<CanvasRenderer>()->AddComponent<SingleImage>(&image)->SetPosition(75,WINCY - 34)->SetScale(150,75);
	}
	{
		SingleImage::Desc image;
		image.color = Vector4(1, 1, 1, 0.2f);
		image.textureName = L"TargetGuide";
		INSTANTIATE()->AddComponent<CanvasRenderer>()->AddComponent<SingleImage>(&image)->SetPosition(HALF_WINCX, HALF_WINCY)->SetScale(128, 128);
	}
	{
		SingleImage::Desc image;
		image.color = Vector4(1, 1, 1, 0.5f);
		Text::Desc text;
		text.boundary = { 20,0,200,30 };
		text.option = DT_LEFT;
		text.color = D3DXCOLOR(1, 1, 1, 0.5f);
		image.textureName = L"GameUI_LeftBottom";
		m_targetOutLine[0] = INSTANTIATE()->AddComponent<CanvasRenderer>()->AddComponent<SingleImage>(&image)->SetPosition(HALF_WINCX, HALF_WINCY)->SetScale(10, 10);
		m_targetOutLine[0]->SetActive(false);

		image.textureName = L"GameUI_LeftTop";
		m_targetOutLine[1] = INSTANTIATE()->AddComponent<CanvasRenderer>()->AddComponent<SingleImage>(&image)->SetPosition(HALF_WINCX, HALF_WINCY)->SetScale(10, 10);
		m_targetOutLine[1]->SetActive(false);

		image.textureName = L"GameUI_RightTop";
		m_targetOutLine[2] = INSTANTIATE()->AddComponent<CanvasRenderer>()->AddComponent<SingleImage>(&image)->SetPosition(HALF_WINCX, HALF_WINCY)->SetScale(10, 10);
		m_targetOutLine[2]->SetActive(false);

		image.textureName = L"GameUI_RightBottom";
		m_targetOutLine[3] = INSTANTIATE()->AddComponent<CanvasRenderer>()->AddComponent<SingleImage>(&image)->AddComponent<Text>(&text)->SetPosition(HALF_WINCX, HALF_WINCY)->SetScale(10, 10);
		m_targetOutLine[3]->SetActive(false);
		 

	}
}

void UIManager::SetLynInfo(LynInfo * _info)
{
	m_lynInfo = _info;
}

void UIManager::UpdateEnergyUI(float _ratio, LYN_STATE _state)
{
	if(_state  == LYN_STATE_PEACE_STANDARD)
		m_energyBarImage->SetColor(Vector4(1.f,1.f,1.f,1.f));
	else
		m_energyBarImage->SetColor(Vector4(0.3f, 0.25f, 0.25f, 1.f));

	m_energyBarRenderer->GetMaterial()->SetFloat("g_outputRatio",_ratio);
}

void UIManager::UpdateHpUI(float _ratio)
{
	m_hpBar->SetFloat("g_outputRatio", _ratio);
}

void UIManager::UpdateEnemyHpUI(float _ratio)
{
	m_bossHpBar->SetFloat("g_outputRatio", _ratio);
}

void UIManager::UpdateTarget(GameObject * _target)
{
	if (_target)
	{
		for(int i = 0;  i <4; ++i)
			m_targetOutLine[i]->SetActive(true);
	}
	else
	{
		for (int i = 0; i < 4; ++i)
			m_targetOutLine[i]->SetActive(false);
	}
}

void UIManager::UpdateTargetBoundaryBox(GameObject * _target)
{

	auto enemy = _target->GetComponent<BnS_Enemy>();
	auto worldVolume = enemy->GetScreenVolume();
	auto volume = enemy->GetVolume();

	//Vector2 screenPos = Vector2((worldVolume.right + worldVolume.left) * 0.5f, (worldVolume.bottom + worldVolume.top) * 0.5f);
	//m_targetOutLine->SetScale((float)(worldVolume.right - worldVolume.left) * 2, (float)(worldVolume.bottom - worldVolume.top) * 2);
	//m_targetOutLine->SetScale(200,200);
	float distance = m_lynInfo->GetDistanceToTarget();
	

	m_targetOutLine[0]->SetPosition((float)worldVolume.left, (float)worldVolume.bottom);
	m_targetOutLine[1]->SetPosition((float)worldVolume.left, (float)worldVolume.top);
	m_targetOutLine[2]->SetPosition((float)worldVolume.right,(float)worldVolume.top);
	m_targetOutLine[3]->SetPosition((float)worldVolume.right,(float)worldVolume.bottom);



	auto text = m_targetOutLine[3]->GetComponent<Text>();

	double dDistance = int(distance * 10) / 10.0;
	wstring strDistance = to_wstring(dDistance);
	size_t targetNum = strDistance.find_last_of(L".");
	strDistance = strDistance.substr(0, targetNum + 2);
	text->SetText(strDistance + L"m");
}

void UIManager::SetSkillSlot(BnS_Skill* _skill)
{
	auto curSkill = m_skillSlot[_skill->GetSkillSlotIndex()];
	curSkill->GetTransform()->GetChild(0)->GetGameObject()->SetActive(true);
	curSkill->GetComponent<CanvasRenderer>()->SetActive(true);
	curSkill->GetComponent<BnS_SkillSlot>()->SetSkill(_skill);
}

void UIManager::UpdateSkillCoolTime(BNS_SKILL_SLOT _slot, float _ratio)
{
	m_skillSlot[_slot]->GetComponent<BnS_SkillSlot>()->SetCoolTimeRatio(_ratio);
}

void UIManager::SetDamageFont()
{
	for (int i = 0; i < 10; ++i)
	{
		m_damageFont[i] = ResourceManager::GetInstance()->GetResource<Texture>(L"UI_DamageFont" + to_wstring(i));
		m_criticalDamageFont[i] = ResourceManager::GetInstance()->GetResource<Texture>(L"UI_CriticalDamageFont" + to_wstring(i));
	}
}

GameObject* UIManager::CreateSkillIcon(BNS_SKILL_SLOT _skillSlot, UINT _x, UINT _y)
{
	Text::Desc text;
	switch (_skillSlot)
	{
	case BNS_SKILL_SLOT_Q:
		text.text = L"Q";
		break;
	case BNS_SKILL_SLOT_E:
		text.text = L"E";
		break;
	case BNS_SKILL_SLOT_SS:
		text.text = L"SS";
		break;
	case BNS_SKILL_SLOT_LB:
		text.text = L"LB";
		break;
	case BNS_SKILL_SLOT_RB:
		text.text = L"RB";
		break;
	case BNS_SKILL_SLOT_TAB:
		text.text = L"TAB";
		break;
	case BNS_SKILL_SLOT_F:
		text.text = L"F";
		break;
	case BNS_SKILL_SLOT_1:
		text.text = L"1";
		break;
	case BNS_SKILL_SLOT_2:
		text.text = L"2";
		break;
	case BNS_SKILL_SLOT_3:
		text.text = L"3";
		break;
	case BNS_SKILL_SLOT_4:
		text.text = L"4";
		break;
	case BNS_SKILL_SLOT_Z:
		text.text = L"Z";
		break;
	case BNS_SKILL_SLOT_X:
		text.text = L"X";
		break;
	case BNS_SKILL_SLOT_C:
		text.text = L"C";
		break;
	case BNS_SKILL_SLOT_V:
		text.text = L"V";
		break;
	default:
		break;
	}
	text.boundary = { -20,-23,200,200 };
	text.option = DT_LEFT;
	text.height = 18;
	text.weight = 700;
	text.color = D3DXCOLOR(0.95f, 0.95f, 0.95f, 0.9f);
	CanvasRenderer::Desc canvas;
	canvas.mtrlName = L"UI_Skill";
	auto obj = INSTANTIATE()->AddComponent<CanvasRenderer>(&canvas)
		->AddComponent<BnS_SkillSlot>()->AddComponent<Text>(&text)
		->SetScale(46, 46)->SetPosition((float)_x, (float)_y);
	obj->GetComponent<CanvasRenderer>()->SetActive(false);

	SingleImage::Desc image;
	image.textureName = L"GameUI_IconOutLine";
	auto frame = INSTANTIATE()->AddComponent<CanvasRenderer>()->AddComponent<SingleImage>(&image)->SetScale(50, 50);
	frame->SetParents(obj);
	frame->SetActive(false);

	return obj;

}

void UIManager::ChangeSkillSlot(BnS_Skill* _skill)
{
	auto curSkill = m_skillSlot[_skill->GetSkillSlotIndex()];
	curSkill->GetTransform()->GetChild(0)->GetGameObject()->SetActive(true);
	curSkill->GetComponent<CanvasRenderer>()->SetActive(true);
	curSkill->GetComponent<BnS_SkillSlot>()->ChangeSkillTex(_skill->GetSkillIconTexture());
}

void UIManager::ChangeSkillSlotByAnimation(BnS_Skill * _skill)
{
	auto curSkill = m_skillSlot[_skill->GetSkillSlotIndex()];
	curSkill->GetTransform()->GetChild(0)->GetGameObject()->SetActive(true);
	curSkill->GetComponent<CanvasRenderer>()->SetActive(true);
	curSkill->GetComponent<BnS_SkillSlot>()->ChangeSkillTex(_skill->GetSkillIconTexture());
}

void UIManager::ChangeSkillSlotTexture(BNS_SKILL_SLOT _slot, Texture* _tex)
{
	auto curSkill = m_skillSlot[_slot];
	curSkill->GetComponent<BnS_SkillSlot>()->ChangeSkillTex(_tex);
}


void UIManager::ReleaseSkillSlot(BNS_SKILL_SLOT _slot)
{
	auto curSkill = m_skillSlot[_slot];
	if (!curSkill)
		return;
	curSkill->GetComponent<CanvasRenderer>()->SetActive(false);
	curSkill->GetTransform()->GetChild(0)->GetGameObject()->SetActive(false);
}

void UIManager::SetSkillSlotColor(BNS_SKILL_SLOT _slot, const Vector4 & _color)
{
	auto curSkill = m_skillSlot[_slot];
	if (!curSkill)
		return;
	curSkill->GetComponent<BnS_SkillSlot>()->SetColor(_color);
}


void UIManager::AddBuff(BnS_Buff * _buff, BnS_Skill * _skill, const wstring & _key)
{
	size_t index = m_buffSlot.size();

	Text::Desc text;
	text.boundary = { -20,-23,200,200 };
	text.option = DT_LEFT;
	text.height = 18;
	text.weight = 700;
	text.text = _key;
	text.color = D3DXCOLOR(0.95f, 0.95f, 0.95f, 0.9f);
	CanvasRenderer::Desc canvas;
	canvas.mtrlName = L"UI_Skill";
	BnS_SkillSlot::Desc skill;
	skill._skill = _skill;
	auto obj = INSTANTIATE()->AddComponent<CanvasRenderer>(&canvas)
		->AddComponent<BnS_SkillSlot>(&skill)->AddComponent<Text>(&text)
		->SetScale(46, 46)->SetPosition((float)(HALF_WINCX - 460 + 60 * index), (float)WINCY - 510);

	SingleImage::Desc image;
	image.textureName = L"GameUI_IconOutLine";
	auto frame = INSTANTIATE()->AddComponent<CanvasRenderer>()->AddComponent<SingleImage>(&image)->SetScale(50, 50);
	frame->SetParents(obj);
	_buff->SetSkillSlot(obj->GetComponent<BnS_SkillSlot>());

	m_buffSlot.emplace_back(pair<GameObject*,BnS_Buff*>(obj, _buff));
}

void UIManager::ReleaseBuff(BnS_Buff * _buff)
{
	GameObject* slot = nullptr;
	for (auto iter = m_buffSlot.begin(); iter != m_buffSlot.end(); ++iter)
	{
		if ((*iter).second == _buff)
		{
			slot = (*iter).first;
			m_buffSlot.erase(iter);
			break;
		}
	}

	if (slot)
	{
		DESTROY(slot->GetTransform()->GetChild(0)->GetGameObject());
		DESTROY(slot);
	}

	int index = 0;
	for (auto& slot : m_buffSlot)
	{
		slot.first->SetPosition((float)(HALF_WINCX - 460 + 60 * index), (float)WINCY - 510);
		++index;
	}

}

void UIManager::AddInnerPower(int _index)
{
	m_innerPowerIcon[_index]->GetComponent<BnS_InnerForceAnimation>()->SetTargetRatio(1.f);
}

void UIManager::FullInnerPower()
{
	for (int i = 0; i < 10; ++i)
	{
		auto innerForce = m_innerPowerIcon[i]->GetComponent<BnS_InnerForceAnimation>();
		innerForce->SetTargetRatio(1.f);
		innerForce->SetCurrentRatio(0.4f);
	}
}

void UIManager::ReduceInnerPower(int _index)
{
	m_innerPowerIcon[_index]->GetComponent<BnS_InnerForceAnimation>()->SetTargetRatio(0.f);
}
