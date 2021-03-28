#include "SphereCollider.h"
#include "RigidBody.h"
#include "MeshRenderer.h"


SphereCollider::SphereCollider(Desc * _desc)
	: Collider(_desc->isTrigger)
{
	m_radius = _desc->radius;
}

SphereCollider::~SphereCollider()
{
}

void SphereCollider::Initialize()
{
	m_rigid = GetComponent<RigidBody>();
	assert(L"Can't find RigidBody Component!" && m_rigid);
	m_rigid->SetRigidBody(PhysicsManager::GetInstance()->CreateSphereCollider(this,m_rigid,m_radius));

	//MeshRenderer::Desc vi;
	//vi.mtrlName = L"debug";
	//vi.meshName = L"sphere";
	//m_debugCollider = INSTANTIATE()->AddComponent<MeshRenderer>(&vi)->SetScale(m_radius * 2, m_radius * 2, m_radius * 2);
	//m_debugCollider->SetParents(m_gameObject);
}

void SphereCollider::Update()
{
}
