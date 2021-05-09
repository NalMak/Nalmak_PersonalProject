#include "DebugObject.h"
#include "LineManager.h"
#include "Transform.h"
#include "MeshRenderer.h"
#include "PhysicsManager.h"

DebugObject::DebugObject(Desc * _desc)
{

}

DebugObject::~DebugObject()
{
}

void DebugObject::Initialize()
{
	m_line = LineManager::GetInstance();


}

void DebugObject::Update()
{
	
}

void DebugObject::LateUpdate()
{
	DEBUG_LOG(m_gameObject->GetName(), m_transform);
}




