#include "stdafx.h"
#include "BnS_MainCamera.h"
#include "BnS_Enemy.h"
#include "LynInfo.h"


BnS_MainCamera::BnS_MainCamera(Desc * _desc)
{
	m_mouseSensitive = _desc->mouseSensitive;
	m_wheelSensitive = _desc->wheelSensitive;
	m_minDistance = _desc->minDistance;
	m_maxDistance = _desc->maxDistance;

	m_player = _desc->player->GetComponent<LynInfo>();

	m_distance = 25.f;
	m_targetDisance = 25.f;
	m_mouseAngle = { 30.f,0 };
	m_offsetY = 10.f;

	m_triggerOn = false;
	m_targetVolume = { HALF_WINCX - 50, HALF_WINCY - 50, HALF_WINCX + 50, HALF_WINCY - 50 };
	m_isControlingPlayer = true;
}

BnS_MainCamera::~BnS_MainCamera()
{
}

void BnS_MainCamera::Initialize()
{
	//m_targetOutline = INSTANTIATE()->AddComponent<SkinnedMeshRenderer>();

	//m_cam = m_transform->GetChild(0)->GetComponent<Camera>();
	m_cam = GetComponent<Camera>();

	auto audio = GetComponents<AudioSource>();

	audio[1]->Play(L"bossRoom_ambient");
	audio[2]->Play(L"bossRoom_bgm");


}

void BnS_MainCamera::Update()
{
	Move();
}

void BnS_MainCamera::LateUpdate()
{
	m_player->SetTarget(CheckTarget());
}

void BnS_MainCamera::OnTriggerEnter(Collision & _col)
{
	m_triggerOn = true;
}

void BnS_MainCamera::OnTriggerStay(Collision & _col)
{
}

void BnS_MainCamera::OnTriggerExit(Collision & _col)
{
	m_triggerOn = false;
}

void BnS_MainCamera::LockTarget()
{
	m_isControlingPlayer = true;
}

void BnS_MainCamera::UnLockTarget()
{
	m_isControlingPlayer = false;
}

void BnS_MainCamera::TurnCamera(float _angle, bool _dir, float _time)
{
	m_turnTimer = _time;
	if (_dir)
		m_turnAngle = (180 - _angle) / _time;
	else
		m_turnAngle = -(180 - _angle) / _time;
}


void BnS_MainCamera::Move()
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

	if (m_turnTimer > 0)
	{
		m_turnTimer -= dTime;
		m_mouseAngle.y += m_turnAngle * dTime;
	}


	Vector3 dir = { 0,0,1 };
	Matrix rot;
	Quaternion qRot, characterRot;
	D3DXMatrixRotationYawPitchRoll(&rot, m_mouseAngle.y * Deg2Rad, m_mouseAngle.x * Deg2Rad, 0);
	D3DXQuaternionRotationYawPitchRoll(&characterRot, m_mouseAngle.y * Deg2Rad, 0, 0);

	D3DXVec3TransformNormal(&dir, &dir, &rot);
	D3DXQuaternionRotationMatrix(&qRot, &rot);
	float offsetY = m_offsetY * (m_distance / m_maxDistance);
	offsetY = Nalmak_Math::Clamp(offsetY, 1.5f, 10.f);
	m_transform->position = m_player->GetTransform()->GetWorldPosition() - dir * m_distance + Vector3(0, offsetY, 0);
	m_transform->rotation = qRot;


	
	if (m_isControlingPlayer)
	{
		if (!InputManager::GetInstance()->GetKeyPress(KEY_STATE_WHEEL_MOUSE))
		{
			m_player->GetTransform()->rotation = characterRot;
		}
	}

}

GameObject* BnS_MainCamera::CheckTarget()
{
	Vector3 pickingPoint;
	auto objList = Core::GetInstance()->GetObjectList(OBJECT_TAG_ENEMY);

	// 앞뒤 판별
	for (auto iter = objList.begin(); iter != objList.end(); )
	{
		if ((*iter)->GetComponent<BnS_Enemy>()->GetBattleState() == BATTLE_STATE_DEAD)
		{
			iter = objList.erase(iter);
			continue;
		}

		Vector3 dir1 = Nalmak_Math::Normalize((*iter)->GetTransform()->GetWorldPosition()- m_player->GetTransform()->GetWorldPosition());
		if (Nalmak_Math::Dot(dir1, m_player->GetTransform()->GetForward()) > 0)
		{
			++iter;
		}
		else
		{
			iter = objList.erase(iter);
		}
	}

	Line line;
	line.start = m_transform->GetWorldPosition();
	line.end = m_transform->GetWorldPosition() + m_transform->GetForward() * 400;

	objList.sort([=](GameObject* _obj1, GameObject* _obj2)->bool
	{
		float dis1 = Nalmak_Math::DistanceSq(line.start, _obj1->GetTransform()->GetWorldPosition());
		float dis2 = Nalmak_Math::DistanceSq(line.start, _obj2->GetTransform()->GetWorldPosition());

		return dis1 < dis2;
	}
	);
	
	for (auto& obj : objList)
	{
		auto enemy = obj->GetComponent<BnS_Enemy>();
		RECT volumeRect = enemy->GetScreenVolume();

		if (Nalmak_Math::IsInPointInRect(Vector2(m_targetVolume.x, m_targetVolume.y), volumeRect))
		{
			return obj;
		}
		if (Nalmak_Math::IsInPointInRect(Vector2(m_targetVolume.x, m_targetVolume.w), volumeRect))
		{
			return obj;
		}
		if (Nalmak_Math::IsInPointInRect(Vector2(m_targetVolume.z, m_targetVolume.y), volumeRect))
		{
			return obj;
		}
		if (Nalmak_Math::IsInPointInRect(Vector2(m_targetVolume.z, m_targetVolume.w), volumeRect))
		{
			return obj;
		}
	}
	return nullptr;

}
