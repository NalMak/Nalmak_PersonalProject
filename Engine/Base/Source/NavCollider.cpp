#include "NavCollider.h"
#include "NavMeshData.h"



NavCollider::NavCollider(Desc * _desc)
	: Collider(false, { 0,0,0 })
{
	m_navData = ResourceManager::GetInstance()->GetResource<NavMeshData>(_desc->navName);
}

NavCollider::~NavCollider()
{
}

void NavCollider::Initialize()
{
	PhysicsManager::GetInstance()->CreateStaticMeshCollider(
		this,
		false,
		m_navData->GetVertexCount(),
		m_navData->GetVertexPositionData(),
		m_navData->GetFigureCount(),
		m_navData->GetIndexData()
		);
}

void NavCollider::Update()
{
}
