#include "stdafx.h"
#include "BnS_MainCamera.h"



BnS_MainCamera::BnS_MainCamera(Desc * _desc)
{
	m_mouseSensitive = _desc->MouseSensitive;
	m_player = _desc->player;

	m_distance = 20;
	m_mouseAngle = { 30.f,0 };
	m_offset = { 0,2,0 };

	m_triggerOn = false;
}

BnS_MainCamera::~BnS_MainCamera()
{
}

void BnS_MainCamera::Initialize()
{
}

void BnS_MainCamera::Update()
{
	Vector2 mouseDT = InputManager::GetInstance()->GetMouseMoveDir();
	m_mouseAngle += Vector2(mouseDT.y, mouseDT.x) * dTime * m_mouseSensitive;


	Vector3 dir = { 0,0,1 };
	Matrix rot;
	Quaternion qRot, characterRot;
	D3DXMatrixRotationYawPitchRoll(&rot, m_mouseAngle.y * Deg2Rad, m_mouseAngle.x * Deg2Rad, 0);
	D3DXQuaternionRotationYawPitchRoll(&characterRot, m_mouseAngle.y * Deg2Rad, 0, 0);

	D3DXVec3TransformNormal(&dir, &dir, &rot);
	D3DXQuaternionRotationMatrix(&qRot, &rot);
	m_transform->position = m_player->GetTransform()->GetWorldPosition() - dir * m_distance + m_offset;
	m_transform->rotation = qRot;
	m_player->GetTransform()->rotation = characterRot;

	if (m_triggerOn)
	{
		m_distance -= dTime * 15.f;
	}
	else
	{
		m_distance = Nalmak_Math::Lerp(m_distance, 20.f, dTime);
	}
}

void BnS_MainCamera::OnTriggerEnter(Collisions & _col)
{
	m_triggerOn = true;
}

void BnS_MainCamera::OnTriggerStay(Collisions & _col)
{
}

void BnS_MainCamera::OnTriggerExit(Collisions & _col)
{
	m_triggerOn = false;
}
