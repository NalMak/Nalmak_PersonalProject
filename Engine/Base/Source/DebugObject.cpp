#include "DebugObject.h"
#include "LineManager.h"
#include "Transform.h"
#include "MeshRenderer.h"
#include "..\..\..\Ref\Include\PhysicsManager.h"

DebugObject::DebugObject(Desc * _desc)
{
}

DebugObject::~DebugObject()
{
}

void DebugObject::Initialize()
{
	m_line = LineManager::GetInstance();

	auto obj0 = INSTANTIATE()->AddComponent<MeshRenderer>();
	m_pickingObject[0] = obj0->GetComponent<MeshRenderer>();


	auto obj1 = INSTANTIATE()->AddComponent<MeshRenderer>();
	m_pickingObject[1] = obj1->GetComponent<MeshRenderer>();


	auto obj2 = INSTANTIATE()->AddComponent<MeshRenderer>();
	m_pickingObject[2] = obj2->GetComponent<MeshRenderer>();

}

void DebugObject::Update()
{
	
}

void DebugObject::LateUpdate()
{
	DEBUG_LOG(m_gameObject->GetName(), m_transform);

	Matrix world = m_transform->GetWorldMatrix();
	Vector3 worldPos = { world._41,world._42 ,world._43 };
	m_line->DrawLine(worldPos, worldPos + Nalmak_Math::Normalize(Vector3(world._11, world._12, world._13)), DEBUG_COLOR_RED);	// right
	m_line->DrawLine(worldPos, worldPos + Nalmak_Math::Normalize(Vector3(world._21, world._22, world._23)), DEBUG_COLOR_GREEN);	// up
	m_line->DrawLine(worldPos, worldPos + Nalmak_Math::Normalize(Vector3(world._31, world._32, world._33)), DEBUG_COLOR_BLUE);	// forward
}

bool DebugObject::IsPickingSuccess()
{
	PhysicsManager::GetInstance()->Raycast()


	return false;
}
