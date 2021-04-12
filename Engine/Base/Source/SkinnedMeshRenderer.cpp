#include "SkinnedMeshRenderer.h"
#include "ResourceManager.h"
#include "Transform.h"
#include "Animator.h"
#include "IRenderer.h"
#include "RenderManager.h"
#include "InputManager.h"
#include "XFileMesh.h"
#include "AnimationController.h"


SkinnedMeshRenderer::SkinnedMeshRenderer(Desc * _desc)
{
	if (!_desc->mtrl)
	{
		m_materials.emplace_back(ResourceManager::GetInstance()->GetResource<Material>(_desc->mtrlName));
	}
	else
	{
		m_materials.emplace_back(_desc->mtrl);
	}

	m_mesh = ResourceManager::GetInstance()->GetResource<Mesh>(_desc->meshName);

	m_type = RENDERER_TYPE_MESH;

	m_isCastShadow = true;
}

void SkinnedMeshRenderer::Initialize()
{
	//m_mesh->SetAnimation(m_index);
}

void SkinnedMeshRenderer::Update()
{
	
	/*m_mesh->UpdateAnimationController();
	m_mesh->UpdateBoneMatrix();

	if (InputManager::GetInstance()->GetKeyDown(KEY_STATE_RIGHT_MOUSE))
	{
		++m_index;
		m_mesh->SetAnimation(m_index);
	}*/
}

void SkinnedMeshRenderer::LateUpdate()
{
}

void SkinnedMeshRenderer::Release()
{
}

void SkinnedMeshRenderer::Render(ConstantBuffer & _cBuffer)
{
	BindingStreamSource();


	Shader* currentShader = nullptr;
	Material* currentMaterial = nullptr;

	currentMaterial = m_materials[0];
	m_renderManager->UpdateMaterial(currentMaterial, _cBuffer);
	m_renderManager->UpdateRenderTarget();

	Shader* shader = currentMaterial->GetShader();
	assert("Current Shader is nullptr! " && shader);

	if (currentShader != shader)
	{
		currentShader = shader;

		currentShader->SetMatrix("g_world", m_transform->GetWorldMatrix());

		currentShader->CommitChanges();
	}

	m_mesh->Draw();
}

void SkinnedMeshRenderer::RenderPure()
{
	BindingStreamSource();

	for (UINT i = 0; i < m_mesh->GetSubsetCount(); ++i)
	{
		m_mesh->Draw(i);
	}
}

void SkinnedMeshRenderer::BindingStreamSource()
{
	m_mesh->BindingStreamSource(m_materials[0]->GetShader()->GetInputLayoutSize());
}

int SkinnedMeshRenderer::GetMaterialCount()
{
	return (int)m_materials.size();
}

Material * SkinnedMeshRenderer::GetMaterial(int _index)
{
#ifdef _DEBUG
	if (_index >= m_materials.size())
	{
		assert(L"Index out of range! " && 0);
	}
#endif // _DEBUG

	return m_materials[_index];
}

void SkinnedMeshRenderer::SetMaterial(Material * _material, int _index)
{
#ifdef _DEBUG
	if (_index >= m_materials.size())
	{
		assert(L"Index out of range! " && 0);
	}
#endif // _DEBUG
	m_materials[_index] = _material;
}

void SkinnedMeshRenderer::SetMaterial(const wstring & _mtrlName, int _index)
{
#ifdef _DEBUG
	if (_index >= m_materials.size())
	{
		assert(L"Index out of range! " && 0);
	}
#endif // _DEBUG
	m_materials[_index] = ResourceManager::GetInstance()->GetResource<Material>(_mtrlName);
}

Mesh * SkinnedMeshRenderer::GetMesh()
{
	return m_mesh;
}

DWORD SkinnedMeshRenderer::GetSubsetCount()
{
	return m_mesh->GetSubsetCount();
}
