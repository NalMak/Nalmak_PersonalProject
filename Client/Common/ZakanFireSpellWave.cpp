#include "stdafx.h"
#include "ZakanFireSpellWave.h"
#include "ZakanFloorAttack.h"
#include "UIManager.h"


ZakanFireSpellWave::ZakanFireSpellWave()
{
}


ZakanFireSpellWave::~ZakanFireSpellWave()
{
}

void ZakanFireSpellWave::Initialize()
{
	m_patterIndex = 0;
}

void ZakanFireSpellWave::EnterState()
{
	m_info->SetBattleState(BATTLE_STATE_ABNORMALSTATE_RESISTANCE);

	m_animController->Play("Zakan_FireSpellWave_Cast");
}

void ZakanFireSpellWave::UpdateState()
{

	if (m_animController->IsOverTime(2.5f))
	{
		CreateFloorAttack();
	}
	if (!m_animController->IsPlay("Zakan_FireSpellWave_Cast"))
	{
		m_animController->Play("Zakan_FireSpellWave_Exec");
	}
	if (!m_animController->IsPlay("Zakan_FireSpellWave_Exec"))
	{
		SetState(L"battle_idle");
		return;
	}
}

void ZakanFireSpellWave::ExitState()
{
}

void ZakanFireSpellWave::CreateFloorAttack()
{
	if (m_patterIndex > 2)
		m_patterIndex = 0;


	switch (m_patterIndex)
	{
	case 0:
	{
		float interval = 17.f;
		CreateFloorAttack(0, 0);
		CreateFloorAttack(1.717f * interval, 1.f * interval);
		CreateFloorAttack(1.717f * interval, -1.f * interval);
		CreateFloorAttack(-1.717f * interval, 1.f  * interval);
		CreateFloorAttack(-1.717f * interval, -1.f * interval);
		CreateFloorAttack(0, 2 * interval);
		CreateFloorAttack(0, -2 * interval);
		break;
	}
	case 1:
	{
		float interval = 23.f;
		CreateFloorAttack(0, 0);
		CreateFloorAttack(1 * interval, 1 * interval);
		CreateFloorAttack(-1 * interval, 1 * interval);
		CreateFloorAttack(1 * interval, -1 * interval);
		CreateFloorAttack(-1 * interval, -1 * interval);
		CreateFloorAttack(2.71f * interval, 0);
		CreateFloorAttack(-2.71f * interval, 0);
		CreateFloorAttack(0, 2.71f * interval);
		CreateFloorAttack(0, -2.71f * interval);
		break;
	}
	case 2:
	{
		float interval = 17.f;
		CreateFloorAttack(0, 0);
		CreateFloorAttack(1.717f * interval, 1.f * interval);
		CreateFloorAttack(1.717f * interval, -1.f * interval);
		CreateFloorAttack(-1.717f * interval, 1.f  * interval);
		CreateFloorAttack(-1.717f * interval, -1.f * interval);
		CreateFloorAttack(0, 2 * interval);
		CreateFloorAttack(0, -2 * interval);
		break;
		break;
	}
	default:
		break;
	}

	++m_patterIndex;
}

void ZakanFireSpellWave::CreateFloorAttack(float _x ,float _z)
{
	Vector3 currentPos = m_transform->GetWorldPosition() + Vector3(_x,0,_z);

	MeshRenderer::Desc meshRenderer;
	meshRenderer.mtrlName = L"zakan_floor_attack";
	INSTANTIATE()->SetPosition(currentPos)->AddComponent<ZakanFloorAttack>()->AddComponent<MeshRenderer>(&meshRenderer)->SetScale(20.f,5.f,20.f);
}
