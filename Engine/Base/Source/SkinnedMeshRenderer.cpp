#include "SkinnedMeshRenderer.h"
#include "ResourceManager.h"
#include "Transform.h"
#include "Animator.h"
#include "IRenderer.h"
#include "RenderManager.h"
#include "InputManager.h"
#include "XFileMesh.h"
#include "AnimationController.h"
#include "Nalmak_Animation.h"


SkinnedMeshRenderer::SkinnedMeshRenderer(Desc * _desc)
{

	if (!_desc->mtrl)
		m_materials.emplace_back(ResourceManager::GetInstance()->GetResource<Material>(_desc->mtrlName));
	else
		m_materials.emplace_back(_desc->mtrl);

	

	for (int i = 0; i < m_materials.size(); ++i)
	{
		if (m_materials[i]->GetShader()->GetInputLayout() != VERTEX_INPUT_LAYOUT_POSITION_NORMAL_UV_ANIMATIONBLENDING)
			assert(L"Skinned Mesh Renderer Must have animation blending Shader!" && 0);
	}



	SetMesh(_desc->meshName);
	UINT  meshContainerSize = m_mesh->GetMeshContainerSize();

	m_meshContainerSize = m_mesh->GetMeshContainerSize();
	m_boneWorldMatrices = new D3DXMATRIX*[m_meshContainerSize];

	for (UINT i = 0; i < m_meshContainerSize; ++i)
	{
		m_textureCount += m_mesh->GetMeshContainer(i)->NumMaterials;
		m_boneWorldMatrices[i] = new D3DXMATRIX[m_mesh->GetMeshContainer(i)->boneCount];
	}

	m_fetchTexture = new LPDIRECT3DTEXTURE9[m_textureCount];
	for (UINT i = 0; i < m_textureCount; ++i)
		ThrowIfFailed(D3DXCreateTexture(m_device, 64, 64, 0, 0, D3DFMT_A32B32G32R32F, D3DPOOL_MANAGED, &m_fetchTexture[i]));

	m_type = RENDERER_TYPE_SKINNED_MESH;

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
	for (UINT i = 0; i < m_textureCount; ++i)
	{
		m_fetchTexture[i]->Release();
	}
	SAFE_DELETE_ARR(m_fetchTexture);

	for (UINT i = 0; i < m_meshContainerSize; ++i)
	{
		SAFE_DELETE_ARR(m_boneWorldMatrices[i]);
	}
	SAFE_DELETE_ARR(m_boneWorldMatrices);
}

void SkinnedMeshRenderer::Render(Shader* _shader, ConstantBuffer& _cBuffer, UINT _containerIndex, UINT _subsetIndex)
{

	UINT texIndex = 0;
	for (UINT i = 0; i < _containerIndex; ++i)
	{
		Nalmak_MeshContainer* meshContainer = m_mesh->GetMeshContainer(i);
		UINT maxSubsetCount = meshContainer->NumMaterials;

		texIndex += maxSubsetCount;
	}
	texIndex += _subsetIndex;

	Nalmak_MeshContainer* meshContainer = m_mesh->GetMeshContainer(_containerIndex);
	UINT boneCount = meshContainer->boneCount;

	LPD3DXBONECOMBINATION boneCombination = (LPD3DXBONECOMBINATION)meshContainer->boneCombinationTable->GetBufferPointer();

	for (UINT palette = 0; palette < boneCount; ++palette)
	{
		int matrixIndex = boneCombination[_subsetIndex].BoneId[palette];
		if (matrixIndex != UINT_MAX)
		{
			m_boneWorldMatrices[_containerIndex][palette] = meshContainer->offsetMatrices[matrixIndex] * (*meshContainer->boneCombinedMatrices[matrixIndex]);
		}
	}

	D3DLOCKED_RECT lockRect;
	m_fetchTexture[texIndex]->LockRect(0, &lockRect, 0, D3DLOCK_DISCARD);
	LPDWORD texElements = (LPDWORD)lockRect.pBits;
	memcpy(texElements, m_boneWorldMatrices[_containerIndex], sizeof(Matrix)* boneCount);
	m_fetchTexture[texIndex]->UnlockRect(0);

	
	_shader->SetMatrix("g_world", m_transform->GetWorldMatrix());
	_shader->SetTexture("g_fetchTex", m_fetchTexture[texIndex]);
	_shader->SetInt("g_bone", meshContainer->maxVertexInfl - 1);
	//currentShader->SetMatrixArray("g_paletteMatricies", meshContainer->renderingMatrices, boneCount);
	_shader->CommitChanges();
	meshContainer->MeshData.pMesh->DrawSubset(_subsetIndex);
}


//void SkinnedMeshRenderer::RenderSW(ConstantBuffer & _cBuffer)
//{
//	Shader* currentShader = nullptr;
//	Material* currentMaterial = nullptr;
//
//	UINT meshContainerSize = (UINT)m_mesh->GetMeshContainerSize();
//	for (UINT i = 0; i < meshContainerSize; ++i)
//	{
//		Nalmak_MeshContainer* meshContainer = m_mesh->GetMeshContainer(i);
//		LPD3DXSKININFO skin = meshContainer->pSkinInfo;
//		if (skin)
//		{
//			void* srcVtx = nullptr;
//			void* dstVtx = nullptr;
//
//			meshContainer->originalMesh->LockVertexBuffer(0, &srcVtx);
//			meshContainer->MeshData.pMesh->LockVertexBuffer(0, &dstVtx);
//
//			for (DWORD j = 0; j < meshContainer->boneCount; ++j)
//				m_boneWorldMatrices[i][j] = meshContainer->offsetMatrices[j] * (*meshContainer->boneCombinedMatrices[j]);
//
//			skin->UpdateSkinnedMesh(
//				m_boneWorldMatrices[i],
//				NULL, // 원상복귀 행렬
//				srcVtx,
//				dstVtx);
//
//			meshContainer->originalMesh->UnlockVertexBuffer();
//			meshContainer->MeshData.pMesh->UnlockVertexBuffer();
//		}
//
//		UINT subsetCount = meshContainer->NumMaterials;
//
//		for (UINT j = 0; j < subsetCount; ++j)
//		{
//			UINT materialIndex = i * meshContainerSize + j;
//
//			Material* newMaterial;
//			if (m_materials.size() > materialIndex)
//				newMaterial = m_materials[materialIndex];
//			else
//				newMaterial = m_materials.back();
//
//			if (currentMaterial != newMaterial)
//			{
//				currentMaterial = newMaterial;
//				m_renderManager->UpdateMaterial(currentMaterial, _cBuffer);
//				m_renderManager->UpdateRenderTarget();
//
//				Shader* shader = currentMaterial->GetShader();
//				assert("Current Shader is nullptr! " && shader);
//
//				if (currentShader != shader)
//				{
//					currentShader = shader;
//
//					currentShader->SetMatrix("g_world", m_transform->GetWorldMatrix());
//
//					currentShader->CommitChanges();
//				}
//			}
//			m_mesh->Draw(i, j);
//		}
//	}
//}

//void SkinnedMeshRenderer::RenderHW_ConstantBuffer(ConstantBuffer & _cBuffer)
//{
//	Shader* currentShader = nullptr;
//	Material* currentMaterial = nullptr;
//	currentMaterial = ResourceManager::GetInstance()->GetResource<Material>(L"SYS_Standard_HWSkinning_ConstantBuffer");
//	UINT meshContainerSize = m_mesh->GetMeshContainerSize();
//	for (UINT i = 0; i < meshContainerSize; ++i)
//	{
//		Nalmak_MeshContainer* meshContainer = m_mesh->GetMeshContainer(i);
//		LPD3DXBONECOMBINATION boneCombination = (LPD3DXBONECOMBINATION)meshContainer->boneCombinationTable->GetBufferPointer();
//
//		UINT boneCount = HARDWARE_SKINNING_BONE_COUNT_MAX;
//		if (meshContainer->boneCount <= boneCount)
//			boneCount = meshContainer->boneCount;
//
//
//		m_renderManager->UpdateMaterial(currentMaterial, _cBuffer);
//		m_renderManager->UpdateRenderTarget();
//
//		UINT maxSubsetCount = meshContainer->NumMaterials;
//
//		for (UINT attribute = 0; attribute < meshContainer->attributeTableCount; ++attribute)
//		{
//			for (UINT palette = 0; palette < boneCount; ++palette)
//			{
//				int matrixIndex = boneCombination[attribute].BoneId[palette];
//				if (matrixIndex != UINT_MAX)
//				{
//					m_boneWorldMatrices[i][palette] = meshContainer->offsetMatrices[matrixIndex] * (*meshContainer->boneCombinedMatrices[matrixIndex]);
//				}
//			}
//
//			for (UINT j = 0; j < maxSubsetCount; ++j)
//			{
//				Shader* shader = currentMaterial->GetShader();
//				assert("Current Shader is nullptr! " && shader);
//
//				if (currentShader != shader)
//				{
//					currentShader = shader;
//
//					currentShader->SetMatrix("g_world", m_transform->GetWorldMatrix());
//					currentShader->SetInt("g_bone", meshContainer->maxVertexInfl - 1);
//					currentShader->SetMatrixArray("g_palette", m_boneWorldMatrices[i], boneCount);
//					currentShader->CommitChanges();
//				}
//				meshContainer->MeshData.pMesh->DrawSubset(j);
//			}
//		}
//		
//
//	}
//}

void SkinnedMeshRenderer::RenderHW_FetchTex(ConstantBuffer& _cBuffer, UINT _containerIndex, UINT _subsetIndex)
{
	

}


void SkinnedMeshRenderer::RenderForShadow(Shader* _shader)
{
	BindingStreamSource();

	UINT texIndex = 0;
	UINT meshContainerSize = m_mesh->GetMeshContainerSize();
	for (UINT i = 0; i < meshContainerSize; ++i)
	{
		Nalmak_MeshContainer* meshContainer = m_mesh->GetMeshContainer(i);
		UINT subsetCount = meshContainer->NumMaterials;

		_shader->SetInt("g_bone", meshContainer->maxVertexInfl - 1);

		for (UINT j = 0; j < subsetCount; ++j)
		{
			_shader->SetTexture("g_fetchTex", m_fetchTexture[texIndex]);
			_shader->CommitChanges();
			meshContainer->MeshData.pMesh->DrawSubset(j);
			++texIndex;
		}
	}
}

void SkinnedMeshRenderer::BindingStreamSource()
{
	//m_mesh->BindingStreamSource(m_materials[0]->GetShader()->GetInputLayoutSize());
}


void SkinnedMeshRenderer::AddMaterial(const wstring & _mtrl)
{
	m_materials.emplace_back(ResourceManager::GetInstance()->GetResource<Material>(_mtrl));
}

void SkinnedMeshRenderer::AddMaterial(Material * _mtrl)
{
	m_materials.emplace_back(_mtrl);
}

int SkinnedMeshRenderer::GetMaterialCount()
{
	return (int)m_materials.size();
}

Material * SkinnedMeshRenderer::GetMaterial(UINT _containerIndex, UINT _subsetIndex)
{
	UINT mtrlIndex = 0;
	for (UINT i = 0; i < _containerIndex; ++i)
	{
		mtrlIndex += m_mesh->GetMeshContainer(i)->NumMaterials;
	}
	mtrlIndex += _subsetIndex;

	return m_materials[mtrlIndex];
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

void SkinnedMeshRenderer::SetMesh(const wstring & _meshName)
{
	auto mesh = ResourceManager::GetInstance()->GetResource<Mesh>(_meshName);
	if (mesh->GetMeshType() != MESH_TYPE_ANIMATION)
		assert(L"Skinned Mesh Renderer must have animation Mesh!" && 0);

	m_mesh = (XFileMesh*)mesh;

}

Matrix * SkinnedMeshRenderer::GetBoneWorldMatrix(const string & _boneName)
{
	LPD3DXFRAME frame = D3DXFrameFind(m_mesh->GetRoot(), _boneName.c_str());
	assert(L"Can't find bone!" && frame);

	return &((Nalmak_Frame*)frame)->boneCombinedMatrix;
}


DWORD SkinnedMeshRenderer::GetSubsetCount()
{
	return m_mesh->GetSubsetCount();
}
