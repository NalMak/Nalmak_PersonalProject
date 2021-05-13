#include "stdafx.h"
#include "UIManager.h"
#include "BnS_SkillSlot.h"
#include "BnS_Skill.h"
#include "BnS_Enemy.h"
#include "LynInfo.h"

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
			SingleImage::Desc image;
			image.textureName = L"UI_CriticalDamageFont0";
			auto innerPower = INSTANTIATE()->AddComponent<CanvasRenderer>()->AddComponent<SingleImage>(&image)->SetScale(30.f,30.f)->SetPosition((float)(HALF_WINCX - 143 + 32 * i), (float)(WINCY - 205));
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
		m_energyBar = obj->GetComponent<CanvasRenderer>()->GetMaterial();

	}
	CreateSkillIcon(BNS_SKILL_SLOT_Q, HALF_WINCX - 360, WINCY - 510); // ÁúÇ³
	CreateSkillIcon(BNS_SKILL_SLOT_E, HALF_WINCX - 420, WINCY - 510); // ÁúÇ³
	CreateSkillIcon(BNS_SKILL_SLOT_SS, HALF_WINCX - 480, WINCY - 510); // ÁúÇ³

	CreateSkillIcon(BNS_SKILL_SLOT_LB, HALF_WINCX + 210, WINCY - 210); // ÁúÇ³
	CreateSkillIcon(BNS_SKILL_SLOT_RB, HALF_WINCX + 270, WINCY - 210); // °¡¸£±â
	CreateSkillIcon(BNS_SKILL_SLOT_TAB, HALF_WINCX - 210, WINCY - 210); // Å»Ãâ tab
	CreateSkillIcon(BNS_SKILL_SLOT_F, HALF_WINCX - 270, WINCY - 210); // ³ú¿¬¼¶ f

	// ¹Ù¶÷°³ºñ Èí°ø 
	CreateSkillIcon(BNS_SKILL_SLOT_1, HALF_WINCX - 220, WINCY - 90); // 1
	CreateSkillIcon(BNS_SKILL_SLOT_2, HALF_WINCX - 160, WINCY - 90); // 2
	CreateSkillIcon(BNS_SKILL_SLOT_3, HALF_WINCX - 100, WINCY - 90); // 3
	CreateSkillIcon(BNS_SKILL_SLOT_4, HALF_WINCX - 40,  WINCY - 90); // 4
	CreateSkillIcon(BNS_SKILL_SLOT_Z, HALF_WINCX + 40,  WINCY - 90); // ±Í°Ë·É
	CreateSkillIcon(BNS_SKILL_SLOT_X, HALF_WINCX + 100, WINCY - 90); // x
	CreateSkillIcon(BNS_SKILL_SLOT_C, HALF_WINCX + 160, WINCY - 90); // c ÃµµÕº£±â
	CreateSkillIcon(BNS_SKILL_SLOT_V, HALF_WINCX + 220, WINCY - 90); // v Âü¿ù


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
		image.color = Vector4(1, 1, 1, 0.3f);
		image.textureName = L"TargetGuide";
		Text::Desc text;
		text.color = D3DXCOLOR(1, 1, 1, 0.5f);
		m_targetOutLine = INSTANTIATE()->AddComponent<CanvasRenderer>()->AddComponent<SingleImage>(&image)->AddComponent<Text>(&text)->SetPosition(HALF_WINCX, HALF_WINCY)->SetScale(256, 256);
		m_targetOutLine->SetActive(false);


	

		 
	}
}

void UIManager::SetLynInfo(LynInfo * _info)
{
	m_lynInfo = _info;
}

void UIManager::UpdateEnergyUI(float _ratio)
{
	m_energyBar->SetFloat("g_outputRatio",_ratio);
}

void UIManager::UpdateHpUI(float _ratio)
{
	m_hpBar->SetFloat("g_outputRatio", _ratio);
}

void UIManager::UpdateTarget(GameObject * _target)
{
	if (_target)
	{
		m_targetOutLine->SetActive(true);
	}
	else
	{
		m_targetOutLine->SetActive(false);
	}
}

void UIManager::UpdateTargetBoundaryBox(GameObject * _target)
{

	auto enemy = _target->GetComponent<BnS_Enemy>();
	auto worldVolume = enemy->GetScreenVolume();
	auto volume = enemy->GetVolume();

	float averageX = (volume.z - volume.x) * 0.5f;
	float averageY = (volume.w - volume.y) * 0.5f;

	Vector2 screenPos = Core::GetInstance()->GetMainCamera()->WorldToScreenPos(_target->GetTransform()->GetWorldPosition() + Vector3(averageX, -averageY, 0));
	m_targetOutLine->SetPosition(screenPos);
	m_targetOutLine->SetScale((float)(worldVolume.right - worldVolume.left) * 2, (float)(worldVolume.bottom - worldVolume.top) * 2);
	//m_targetOutLine->SetScale(200,200);
	float distance = m_lynInfo->GetDistanceToTarget();
	
	auto text = m_targetOutLine->GetComponent<Text>();
	RECT rc;
	UINT right = UINT((worldVolume.right - worldVolume.left) * 0.5f);
	UINT bottom = UINT((worldVolume.bottom - worldVolume.top) * 0.5f);
	rc.left = right + 10;
	rc.top = bottom + 10;
	rc.right = right + 150;
	rc.bottom = bottom + 30;

	double dDistance = int(distance * 10) / 10.0;
	wstring strDistance = to_wstring(dDistance);
	size_t targetNum = strDistance.find_last_of(L".");
	strDistance = strDistance.substr(0, targetNum + 2);
	/*std::sstream
	string num_str = sstream.str();*/

	text->SetBoundary(&rc);
	text->SetText(strDistance + L"m");
}

void UIManager::SetSkillSlot(BnS_Skill* _skill)
{
	m_skillSlot[_skill->GetSkillSlotIndex()]->GetComponent<SingleImage>()->SetTexture(_skill->GetSkillIconTexture()->GetTexure(0));
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

void UIManager::CreateSkillIcon(BNS_SKILL_SLOT _skillSlot, UINT _x, UINT _y)
{
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
		m_skillSlot[_skillSlot] = INSTANTIATE()->AddComponent<CanvasRenderer>(&canvas)
			->AddComponent<SingleImage>()->AddComponent<BnS_SkillSlot>()->AddComponent<Text>(&text)
			->SetScale(46, 46)->SetPosition((float)_x, (float)_y);
	}
	{
	
	
		SingleImage::Desc image;
		image.textureName = L"GameUI_IconOutLine";
		auto frame = INSTANTIATE()->AddComponent<CanvasRenderer>()->AddComponent<SingleImage>(&image)->SetScale(50, 50);
		frame->SetParents(m_skillSlot[_skillSlot]);
	}
}

void UIManager::ChangeSkillSlot(BnS_Skill* _skill)
{
	m_skillSlot[_skill->GetSkillSlotIndex()]->GetTransform()->GetChild(0)->GetGameObject()->SetActive(true);
	m_skillSlot[_skill->GetSkillSlotIndex()]->GetComponent<CanvasRenderer>()->SetActive(true);
}

void UIManager::ReleaseSkillSlot(BNS_SKILL_SLOT _slot)
{
	m_skillSlot[_slot]->GetComponent<CanvasRenderer>()->SetActive(false);
	m_skillSlot[_slot]->GetTransform()->GetChild(0)->GetGameObject()->SetActive(false);
}

void UIManager::AddInnerPower(UINT _index)
{
	m_innerPowerIcon[_index]->SetActive(true);
}

void UIManager::ReduceInnerPower(UINT _index)
{
	m_innerPowerIcon[_index]->SetActive(false);
}
