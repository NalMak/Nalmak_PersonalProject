#include "stdafx.h"
#include "TestEffectMesh.h"

#include "MeshEffect_Slash.h"

CTestEffectMesh::CTestEffectMesh(Desc * _desc)
	: m_iIndex(0), m_pObj(nullptr), m_fSpeed_size(0.f)
{
}

CTestEffectMesh::~CTestEffectMesh()
{
}

void CTestEffectMesh::Initialize()
{
	

	m_fSpeed_size = 0.05f;

	for (int i = 0; i < 5; ++i)
	{
		wstring szName = L"";
		switch (i)
		{
		case 0:
			szName = L"zakan_trail001";
			break;
		case 1:
			szName = L"zakan_trail001a";
			break;
		case 2:
			szName = L"zakan_trail001b";
			break;
		case 3:
			szName = L"zakan_traill001c";
			break;
		case 4:
			szName = L"zakan_projectile002";
			break;
		}

		Mesh* pMesh = ResourceManager::GetInstance()->GetResource<Mesh>(szName);
		m_vecMesh.emplace_back(pMesh);
	}

	for (int i = 0; i < 65; ++i)
	{
		wstring szName = L"";
		switch (i)
		{
#pragma region 0~9

		case 0:
			szName = L"AttackArea_LargeRect";
			break;
		case 1:
			szName = L"AuraTrail_000";
			break;
		case 2:
			szName = L"AuraTrail_Half";
			break;
		case 3:
			szName = L"AuraTrail_Half2";
			break;
		case 4:
			szName = L"CineFX_HarfTornado";
			break;
		case 5:
			szName = L"CineFX_helixTornado";
			break;
		case 6:
			szName = L"Circle001";
			break;
		case 7:
			szName = L"Circle005";
			break;
		case 8:
			szName = L"Circle006";
			break;
		case 9:
			szName = L"Circle006_Left";
			break;

#pragma endregion
#pragma region 10~19

		case 10:
			szName = L"Circle007";
			break;
		case 11:
			szName = L"Circle007_Inverse";
			break;
		case 12:
			szName = L"Coil_Rotation_D";
			break;
		case 13:
			szName = L"Coil_Rotation_Left";
			break;
		case 14:
			szName = L"Coil_Rotation_Thick";
			break;
		case 15:
			szName = L"Coil004";
			break;
		case 16:
			szName = L"Cylinder_Defualt001";
			break;
		case 17:
			szName = L"Cylinder_Defualt003";
			break;
		case 18:
			szName = L"Cylinder_Defualt004";
			break;
		case 19:
			szName = L"Cylinder_uv001";
			break;

#pragma endregion
#pragma region 20~29

		case 20:
			szName = L"Cylinder_wave";
			break;
		case 21:
			szName = L"DonutCircle";
			break;
		case 22:
			szName = L"Electronic01";
			break;
		case 23:
			szName = L"Electronic02";
			break;
		case 24:
			szName = L"Electronic03";
			break;
		case 25:
			szName = L"Electronic04";
			break;
		case 26:
			szName = L"Electronic05";
			break;
		case 27:
			szName = L"Electronic06";
			break;
		case 28:
			szName = L"Flat_HalfCircle";
			break;
		case 29:
			szName = L"FlatCircle";
			break;

#pragma endregion
#pragma region 30~39

		case 30:
			szName = L"Ink_Trail";
			break;
		case 31:
			szName = L"InkSplatter000";
			break;
		case 32:
			szName = L"InkSplatter001";
			break;
		case 33:
			szName = L"InkSplatter002";
			break;
		case 34:
			szName = L"Jangpan_Twist_Middle";
			break;
		case 35:
			szName = L"Jangpan_Twist_Revers";
			break;
		case 36:
			szName = L"Jangpan_Twist_Thick";
			break;
		case 37:
			szName = L"Jangpan_Twist_Thin";
			break;
		case 38:
			szName = L"Jangpan_Twist_Thin2";
			break;
		case 39:
			szName = L"Lyn_Attack_Vertical";
			break;

#pragma endregion
#pragma region 40~49

		case 40:
			szName = L"MeshTrail001";
			break;
		case 41:
			szName = L"MeshTrail002";
			break;
		case 42:
			szName = L"RisingForce";
			break;
		case 43:
			szName = L"ShokWave_Default";
			break;
		case 44:
			szName = L"ShokWave_ToCenter";
			break;
		case 45:
			szName = L"SM_Hex";
			break;
		case 46:
			szName = L"Sphere_Default";
			break;
		case 47:
			szName = L"StaticMesh_Trail";
			break;
		case 48:
			szName = L"SwordTrail_Expand";
			break;
		case 49:
			szName = L"SwordTrail000";
			break;

#pragma endregion
#pragma region 50~59

		case 50:
			szName = L"SwordTrail001";
			break;
		case 51:
			szName = L"SwordTrail001_120";
			break;
		case 52:
			szName = L"SwordTrail002";
			break;
		case 53:
			szName = L"SwordTrail003";
			break;
		case 54:
			szName = L"Targeting_Loop_UV";
			break;
		case 55:
			szName = L"Tornado01";
			break;
		case 56:
			szName = L"Tornado02";
			break;
		case 57:
			szName = L"Torus004";
			break;
		case 58:
			szName = L"TrailGumiho000";
			break;
		case 59:
			szName = L"TrailGumiho001";
			break;

#pragma endregion
#pragma region 60~65

		case 60:
			szName = L"TrailMesh006";
			break;
		case 61:
			szName = L"Twiri_Rotation";
			break;
		case 62:
			szName = L"Twiri_Wave";
			break;
		case 63:
			szName = L"Wave_Cylinder000";
			break;
		case 64:
			szName = L"Coil_Center000";
			break;

#pragma endregion
		}

		Mesh* pMesh = ResourceManager::GetInstance()->GetResource<Mesh>(szName);
		m_vecMesh.emplace_back(pMesh);
	}


	MeshRenderer::Desc mesh;
	mesh.mtrlName = L"zakan_floorAttack2";
	mesh.meshName = m_vecMesh.front()->GetName();

	m_pObj = INSTANTIATE()->AddComponent<MeshRenderer>(&mesh)
		->SetPosition(0, 20, 30)->SetScale(0.05f, 0.05f, 0.05f);
}

void CTestEffectMesh::Update()
{
	if (InputManager::GetInstance()->GetKeyDown(KEY_STATE_1))
	{
		--m_iIndex;
		if (m_iIndex < 0)
			m_iIndex = (int)m_vecMesh.size() - 1;

		m_pObj->GetComponent<MeshRenderer>()->SetMesh(m_vecMesh[m_iIndex]);
	}
	if (InputManager::GetInstance()->GetKeyDown(KEY_STATE_2))
	{
		++m_iIndex;
		if (m_iIndex >= m_vecMesh.size())
			m_iIndex = 0;

		m_pObj->GetComponent<MeshRenderer>()->SetMesh(m_vecMesh[m_iIndex]);
	}
	if (InputManager::GetInstance()->GetKeyPress(KEY_STATE_3))
	{
		m_pObj->GetTransform()->scale.x += m_fSpeed_size * dTime;
		m_pObj->GetTransform()->scale.y += m_fSpeed_size * dTime;
		m_pObj->GetTransform()->scale.z += m_fSpeed_size * dTime;
	}
	if (InputManager::GetInstance()->GetKeyPress(KEY_STATE_4))
	{
		m_pObj->GetTransform()->scale.x -= m_fSpeed_size * dTime;
		m_pObj->GetTransform()->scale.y -= m_fSpeed_size * dTime;
		m_pObj->GetTransform()->scale.z -= m_fSpeed_size * dTime;
	}

	DEBUG_LOG(L"Mesh Name : ", m_vecMesh[m_iIndex]->GetName());
}

GameObject * CTestEffectMesh::GetEffectObject()
{
	int a = 5;
	return m_pObj;
}
