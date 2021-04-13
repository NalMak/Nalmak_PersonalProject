#include "SkinnedMeshRenderer.h"
#include "ResourceManager.h"
#include "Transform.h"
#include "Animator.h"
#include "IRenderer.h"
#include "RenderManager.h"
#include "InputManager.h"
#include "XFileMesh.h"
#include "AnimationController.h"

LPDIRECT3DTEXTURE9 SkinnedMeshRenderer::m_fetchTexture = nullptr;
bool SkinnedMeshRenderer::m_onceInit = false;

SkinnedMeshRenderer::SkinnedMeshRenderer(Desc * _desc)
{
	if (!m_onceInit)
	{
		m_onceInit = true;
		ThrowIfFailed(D3DXCreateTexture(m_device, 64, 64, 0, 0, D3DFMT_A32B32G32R32F, D3DPOOL_MANAGED, &m_fetchTexture));
	}

	if (!_desc->mtrl)
		m_materials.emplace_back(ResourceManager::GetInstance()->GetResource<Material>(_desc->mtrlName));
	else
		m_materials.emplace_back(_desc->mtrl);


	auto mesh = ResourceManager::GetInstance()->GetResource<Mesh>(_desc->meshName);
	if (mesh->GetMeshType() != MESH_TYPE_ANIMATION)
		assert(L"Skinned Mesh Renderer Must have animation Mesh!" && 0);

	m_mesh = (XFileMesh*)mesh;
	m_type = RENDERER_TYPE_MESH;

	m_isCastShadow = true;
}

void SkinnedMeshRenderer::Initialize()
{
	IRenderer::Initialize();
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

	//RenderSW(_cBuffer);
	if (m_mesh->IsRenderHW())
	{
		//RenderHW_FetchTex(_cBuffer);
		RenderHW_ConstanceBuffer(_cBuffer);
	}
		
	else
		RenderSW(_cBuffer);
}


void SkinnedMeshRenderer::RenderSW(ConstantBuffer & _cBuffer)
{
	Shader* currentShader = nullptr;
	Material* currentMaterial = nullptr;


	UINT meshContainerSize = m_mesh->GetMeshContainerSize();
	for (UINT i = 0; i < meshContainerSize; ++i)
	{
		Nalmak_MeshContainer* meshContainer = m_mesh->GetMeshContainer(i);
		LPD3DXSKININFO skin = meshContainer->pSkinInfo;
		if (skin)
		{
			void* srcVtx = nullptr;
			void* dstVtx = nullptr;

			meshContainer->originalMesh->LockVertexBuffer(0, &srcVtx);
			meshContainer->MeshData.pMesh->LockVertexBuffer(0, &dstVtx);

			for (DWORD j = 0; j < meshContainer->boneCount; ++j)
				meshContainer->renderingMatrices[j] = meshContainer->offsetMatrices[j] * (*meshContainer->boneCombinedMatrices[j]);

			skin->UpdateSkinnedMesh(
				meshContainer->renderingMatrices,
				NULL, // 원상복귀 행렬
				srcVtx,
				dstVtx);

			meshContainer->originalMesh->UnlockVertexBuffer();
			meshContainer->MeshData.pMesh->UnlockVertexBuffer();
		}

		UINT subsetCount = meshContainer->NumMaterials;

		for (UINT j = 0; j < subsetCount; ++j)
		{
			UINT materialIndex = i * meshContainerSize + j;

			Material* newMaterial;
			if (m_materials.size() > materialIndex)
				newMaterial = m_materials[materialIndex];
			else
				newMaterial = m_materials.back();

			if (currentMaterial != newMaterial)
			{
				currentMaterial = newMaterial;
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
			}
			m_mesh->Draw(i, j);
		}
	}
}

void SkinnedMeshRenderer::RenderHW_ConstanceBuffer(ConstantBuffer & _cBuffer)
{
	Shader* currentShader = nullptr;
	Material* currentMaterial = nullptr;
	currentMaterial = ResourceManager::GetInstance()->GetResource<Material>(L"SYS_Standard_HWSkinning_ConstantBuffer");

	UINT meshContainerSize = m_mesh->GetMeshContainerSize();
	for (UINT i = 0; i < meshContainerSize; ++i)
	{
		Nalmak_MeshContainer* meshContainer = m_mesh->GetMeshContainer(i);

		UINT boneCount = 50;

		if (meshContainer->boneCount < boneCount)
		{
			boneCount = meshContainer->boneCount;
		}
		LPD3DXBONECOMBINATION boneCombination = (LPD3DXBONECOMBINATION)meshContainer->boneCombinationTable->GetBufferPointer();


		m_renderManager->UpdateMaterial(currentMaterial, _cBuffer);
		m_renderManager->UpdateRenderTarget();

		UINT maxSubsetCount = meshContainer->NumMaterials;

		for (UINT j = 0; j < maxSubsetCount; ++j)
		{
			for (UINT palette = 0; palette < boneCount; ++palette)
			{
				int matrixIndex = boneCombination[j].BoneId[palette];
				if (matrixIndex != UINT_MAX)
				{
					meshContainer->renderingMatrices[palette] = meshContainer->offsetMatrices[matrixIndex] * (*meshContainer->boneCombinedMatrices[matrixIndex]);
				}
			}

			Shader* shader = currentMaterial->GetShader();
			assert("Current Shader is nullptr! " && shader);

			if (currentShader != shader)
			{
				currentShader = shader;

				currentShader->SetMatrix("g_world", m_transform->GetWorldMatrix());
				currentShader->SetInt("g_bone", meshContainer->maxVertexInfl);
				currentShader->SetMatrixArray("g_palette", meshContainer->renderingMatrices, boneCount);
				currentShader->CommitChanges();
			}
			meshContainer->MeshData.pMesh->DrawSubset(j);
		}

	}
}

void SkinnedMeshRenderer::RenderHW_FetchTex(ConstantBuffer & _cBuffer)
{
	Shader* currentShader = nullptr;
	Material* currentMaterial = nullptr;
	currentMaterial = ResourceManager::GetInstance()->GetResource<Material>(L"SYS_Standard_HWSkinning_FetchTex");

	UINT meshContainerSize = m_mesh->GetMeshContainerSize();
	for (UINT i = 0; i < meshContainerSize; ++i)
	{
		Nalmak_MeshContainer* meshContainer = m_mesh->GetMeshContainer(i);

		UINT boneCount = 100;

		if (meshContainer->boneCount < boneCount)
		{
			boneCount = meshContainer->boneCount;
		}
		LPD3DXBONECOMBINATION boneCombination = (LPD3DXBONECOMBINATION)meshContainer->boneCombinationTable->GetBufferPointer();

		
		m_renderManager->UpdateMaterial(currentMaterial, _cBuffer);
		m_renderManager->UpdateRenderTarget();
		
		UINT maxSubsetCount = meshContainer->NumMaterials;

		for (UINT j = 0; j < maxSubsetCount; ++j)
		{
			for (UINT palette = 0; palette < boneCount; ++palette)
			{
				int matrixIndex = boneCombination[j].BoneId[palette];
				if (matrixIndex != UINT_MAX)
				{
					meshContainer->renderingMatrices[palette] = meshContainer->offsetMatrices[matrixIndex] * (*meshContainer->boneCombinedMatrices[matrixIndex]);
				}
			}


			D3DLOCKED_RECT lockRect;

			m_fetchTexture->LockRect(0, &lockRect, 0, D3DLOCK_DISCARD);

			LPDWORD texElements = (LPDWORD)lockRect.pBits;

			memcpy(texElements, meshContainer->renderingMatrices, sizeof(Matrix)* boneCount);

			m_fetchTexture->UnlockRect(0);



			Shader* shader = currentMaterial->GetShader();
			assert("Current Shader is nullptr! " && shader);

			if (currentShader != shader)
			{
				currentShader = shader;

				currentShader->SetTexture("g_fetchTex", m_fetchTexture);
				currentShader->SetMatrix("g_world", m_transform->GetWorldMatrix());
				currentShader->SetInt("g_bone", meshContainer->maxVertexInfl);
				//currentShader->SetMatrixArray("g_paletteMatricies", meshContainer->renderingMatrices, boneCount);
				currentShader->CommitChanges();
			}
			meshContainer->MeshData.pMesh->DrawSubset(j);
		}
		
	}
}


void SkinnedMeshRenderer::RenderPure()
{
	BindingStreamSource();

	UINT meshContainerSize = m_mesh->GetMeshContainerSize();
	for (UINT i = 0; i < meshContainerSize; ++i)
	{
		Nalmak_MeshContainer* meshContainer = m_mesh->GetMeshContainer(i);
		UINT subsetCount = meshContainer->NumMaterials;
		for (UINT j = 0; j < subsetCount; ++j)
		{
			meshContainer->MeshData.pMesh->DrawSubset(j);
		}
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

XFileMesh * SkinnedMeshRenderer::GetMesh()
{
	return m_mesh;
}

DWORD SkinnedMeshRenderer::GetSubsetCount()
{
	return m_mesh->GetSubsetCount();
}
