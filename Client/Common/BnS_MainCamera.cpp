#include "stdafx.h"
#include "BnS_MainCamera.h"



BnS_MainCamera::BnS_MainCamera(Desc * _desc)
{
	m_mouseSensitive = _desc->mouseSensitive;
	m_wheelSensitive = _desc->wheelSensitive;
	m_minDistance = _desc->minDistance;
	m_maxDistance = _desc->maxDistance;

	m_player = _desc->player;

	m_distance = 25.f;
	m_targetDisance = 25.f;
	m_mouseAngle = { 30.f,0 };
	m_offsetY = 12.f;

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

	m_targetDisance -= InputManager::GetInstance()->GetMouseDT(MOUSE_MOVE_STATE_Z) *  dTime * m_wheelSensitive;
	if (m_triggerOn)
	{
		m_targetDisance -= dTime * 15.f;
	}
	
	m_targetDisance = Nalmak_Math::Clamp(m_targetDisance, m_minDistance, m_maxDistance);
	m_distance = Nalmak_Math::Lerp(m_distance, m_targetDisance, dTime * 2);
	
	Vector2 mouseDT = InputManager::GetInstance()->GetMouseMoveDir();
	m_mouseAngle += Vector2(mouseDT.y, mouseDT.x) * dTime * m_mouseSensitive;


	Vector3 dir = { 0,0,1 };
	Matrix rot;
	Quaternion qRot, characterRot;
	D3DXMatrixRotationYawPitchRoll(&rot, m_mouseAngle.y * Deg2Rad, m_mouseAngle.x * Deg2Rad, 0);
	D3DXQuaternionRotationYawPitchRoll(&characterRot, m_mouseAngle.y * Deg2Rad, 0, 0);

	D3DXVec3TransformNormal(&dir, &dir, &rot);
	D3DXQuaternionRotationMatrix(&qRot, &rot);
	float offsetY =  m_offsetY * (m_distance / m_maxDistance);
	offsetY = Nalmak_Math::Clamp(offsetY, 3.f, 12.f);
	m_transform->position = m_player->GetTransform()->GetWorldPosition() - dir * m_distance + Vector3(0,offsetY,0);
	m_transform->rotation = qRot;

	if (!InputManager::GetInstance()->GetKeyPress(KEY_STATE_WHEEL_MOUSE))
	{
		m_player->GetTransform()->rotation = characterRot;
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
