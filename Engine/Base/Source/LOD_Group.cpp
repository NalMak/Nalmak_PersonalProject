#include "LOD_Group.h"
#include "MeshRenderer.h"
#include "RenderManager.h"
#include "Transform.h"
#include "Mesh.h"
#include "ResourceManager.h"

LOD_Group::LOD_Group(Desc * _desc)
{
}

LOD_Group::~LOD_Group()
{
}

void LOD_Group::Initialize()
{
	m_staticMeshRenderer = GetComponent<MeshRenderer>();

	m_renderManager = RenderManager::GetInstance();
	assert(L"LOD_Group must have mesh renderer class!");
}

void LOD_Group::Update()
{
}

void LOD_Group::EachRender()
{
	Camera* cam = m_renderManager->GetMainCamera();
	Vector3 camPos = cam->GetTransform()->GetWorldPosition();
	float distance = Nalmak_Math::Distance(camPos, m_transform->GetWorldPosition());
	float distanceRatio = distance / cam->GetFar();

	for (auto lod : m_lodGroup)
	{
		if (lod.second >= distanceRatio)
		{
			m_staticMeshRenderer->SetMesh(lod.first);
			return;
		}
	}
}

void LOD_Group::AddLODMesh(Mesh * _mesh, float _distanceRatio)
{
	if (_distanceRatio < 0 || _distanceRatio > 1)
		assert(L"Invalid distanceRatio value!" && 0);

	m_lodGroup.emplace_back(LOD(_mesh, _distanceRatio));

	sort(m_lodGroup.begin(), m_lodGroup.end(), [](LOD a, LOD b)->bool
	{
		return a.second < b.second;
	});
}

void LOD_Group::AddLODMesh(const wstring & _meshName, float _distanceRatio)
{
	if (_distanceRatio < 0 || _distanceRatio > 1)
		assert(L"Invalid distanceRatio value!" && 0);
	Mesh* mesh = ResourceManager::GetInstance()->GetResource<Mesh>(_meshName);

	m_lodGroup.emplace_back(LOD(mesh, _distanceRatio));

	sort(m_lodGroup.begin(), m_lodGroup.end(), [](LOD a, LOD b)->bool
	{
		return a.second < b.second;
	});
}
