#include "MeshCollider.h"
#include "Mesh.h"
#include "MeshRenderer.h"
#include "RigidBody.h"



MeshCollider::MeshCollider(Desc * _desc)
	: Collider(_desc->isTrigger)
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

	PhysicsManager::GetInstance()->CreateStaticMeshCollider(this,rigid, meshRenderer->GetMesh(), false);
}

void MeshCollider::Update()
{
}
