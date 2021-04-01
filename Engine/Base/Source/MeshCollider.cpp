#include "MeshCollider.h"
#include "Mesh.h"
#include "MeshRenderer.h"
#include "RigidBody.h"



MeshCollider::MeshCollider(Desc * _desc)
	: Collider(_desc->isTrigger, { 0,0,0 })
{
}

MeshCollider::~MeshCollider()
{
}

void MeshCollider::Initialize()
{
	auto meshRenderer = GetComponent<MeshRenderer>();
	auto rigid = GetComponent<RigidBody>();
	assert(L"Mesh Collider Must have MeshRenderer!" && meshRenderer);

	if (rigid)
	{
		PhysicsManager::GetInstance()->CreateConvexMeshCollider(this, rigid, meshRenderer->GetMesh(), false, 16);
	}
	else
		PhysicsManager::GetInstance()->CreateStaticMeshCollider(this, meshRenderer->GetMesh(), false);
}

void MeshCollider::Update()
{
}
