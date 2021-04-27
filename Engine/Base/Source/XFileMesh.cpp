#include "XFileMesh.h"
#include "MeshHierarchy.h"
#include "AnimationController.h"
#include "Shader.h"
#include "SkinnedMeshRenderer.h"

XFileMesh::XFileMesh()
{
	m_root = nullptr;
	m_hierarchy = nullptr;
	m_animController = nullptr;
}


XFileMesh::~XFileMesh()
{
}

void XFileMesh::Initialize(wstring _fp)
{
	m_hierarchy = new MeshHierarchy;

	if (_fp == L"../Resource/title/Gwimyeon/GW_innerRoof.X")
	{
		int a = 5;
	}
	ThrowIfFailed(D3DXLoadMeshHierarchyFromX(_fp.c_str(), D3DXMESH_32BIT | D3DXMESH_MANAGED, m_device, m_hierarchy, nullptr, &m_root, &m_animController));
	Matrix base = { 1,0,0,0,0,1,0,0,0,0,1,0,0,0,0,1 };
	AnimationController::UpdateBoneMatrix((Nalmak_Frame*)m_root, base);
	TraverseBone((Nalmak_Frame*)m_root);
	m_stride = sizeof(INPUT_LAYOUT_POSITION_NORMAL_BINORMAL_TANGENT_UV);


	for (auto& meshContainer : m_meshContainerList)
	{
		m_subsetCounts.emplace_back(meshContainer->NumMaterials);
	}
	bool isRenderHW = true;
	for (auto& meshContainer : m_meshContainerList)
	{
		if (!meshContainer->pSkinInfo)
		{
			isRenderHW = false;
			break;
		}
	}

	if (isRenderHW)
	{
		m_meshType = MESH_TYPE_ANIMATION;
		InitializeHW();
	}
	else
	{
		m_meshType = MESH_TYPE_STATIC;
		InitializeSW();

	}




}

void XFileMesh::InitializeSW()
{
	for (auto& meshContainer : m_meshContainerList)
	{
		m_vertexCount += meshContainer->MeshData.pMesh->GetNumVertices();
		m_figureCount += meshContainer->MeshData.pMesh->GetNumFaces();
	}

	StoreVertexIndexData();

	D3DXComputeBoundingSphere(m_vertexPositionData,
		m_vertexCount,
		sizeof(Vector3),
		&m_boundingSphereCenter,
		&m_boundingSphereRadius);
}

void XFileMesh::InitializeHW()
{
	Nalmak_MeshContainer* newMeshContainer = nullptr;

	vector<Nalmak_MeshContainer*> newMeshContainerList;

	for (auto& meshContainer : m_meshContainerList)
	{
		auto mesh = meshContainer->MeshData.pMesh;
		newMeshContainer = meshContainer;

		//DWORD boneCombinationCount = 0;
		SAFE_RELEASE(mesh);

		ThrowIfFailed(newMeshContainer->pSkinInfo->ConvertToIndexedBlendedMesh(
			newMeshContainer->originalMesh,
			D3DXMESH_MANAGED | D3DXMESH_WRITEONLY,
			HARDWARE_SKINNING_BONE_COUNT_MAX,
			nullptr,
			nullptr,
			nullptr,
			nullptr,
			&newMeshContainer->maxVertexInfl,
			&newMeshContainer->attributeTableCount,
			&newMeshContainer->boneCombinationTable,
			&mesh
		));

	/*	mesh->GetAttributeTable(nullptr, &newMeshContainer->attributeTableCount);
		D3DXATTRIBUTERANGE* attributeTable = new D3DXATTRIBUTERANGE[newMeshContainer->attributeTableCount];
		mesh->GetAttributeTable(newMeshContainer->attributeTable, &newMeshContainer->attributeTableCount);
		SAFE_DELETE_ARR(newMeshContainer->attributeTable);*/


		newMeshContainer->MeshData.pMesh = mesh;
		newMeshContainerList.emplace_back(newMeshContainer);
	}

	m_meshContainerList.clear();

	for (auto& newMeshContainer : newMeshContainerList)
	{
		m_meshContainerList.emplace_back(newMeshContainer);
	}

	for (auto& meshContainer : m_meshContainerList)
	{
		m_vertexCount += meshContainer->MeshData.pMesh->GetNumVertices();
		m_figureCount += meshContainer->MeshData.pMesh->GetNumFaces();


		if (meshContainer->boneCount > HARDWARE_SKINNING_BONE_COUNT_MAX)
		{
			assert(L"Please Increase fetchTexture resolution!" && 0);
		}
	}

	StoreVertexIndexData();

	D3DXFrameCalculateBoundingSphere(m_root, &m_boundingSphereCenter, &m_boundingSphereRadius);

	if (m_boundingSphereRadius == 0)
	{
		D3DXComputeBoundingSphere(m_vertexPositionData,
			m_vertexCount,
			sizeof(Vector3),
			&m_boundingSphereCenter,
			&m_boundingSphereRadius);
	}

}

void XFileMesh::StoreVertexIndexData()
{
	m_vertexPositionData = new Vector3[m_vertexCount];
	m_indexData = new INDEX32[m_figureCount];

	DWORD vertexIndex = 0;
	DWORD figureIndex = 0;

	for (auto& meshContainer : m_meshContainerList)
	{
		LPD3DXMESH mesh = meshContainer->MeshData.pMesh;

		D3DVERTEXELEMENT9			decl[MAX_FVF_DECL_SIZE];
		ZeroMemory(decl, sizeof(D3DVERTEXELEMENT9) * MAX_FVF_DECL_SIZE);
		mesh->GetDeclaration(decl);
		DWORD offset = 0;

		for (DWORD i = 0; i < MAX_FVF_DECL_SIZE; ++i)
		{
			if (decl[i].Usage == D3DDECLUSAGE_POSITION)
			{
				offset = (unsigned char)decl[i].Offset;
				break;
			}
		}

		void* vertexMem = nullptr;
		mesh->LockVertexBuffer(0, &vertexMem);
		DWORD currentVertexCount = mesh->GetNumVertices();
		for (DWORD i = 0; i < currentVertexCount; ++i)
		{
			m_vertexPositionData[vertexIndex] = *((Vector3*)(((char*)vertexMem) + (m_stride * i + offset)));
			++vertexIndex;
		}
		mesh->UnlockVertexBuffer();


		void* indexMem = nullptr;
		mesh->LockIndexBuffer(0, &indexMem);
		DWORD currentFigureCount = mesh->GetNumFaces();
		for (DWORD i = 0; i < currentFigureCount; ++i)
		{
			m_indexData[figureIndex] = ((INDEX32*)indexMem)[i];
			++figureIndex;
		}
		//memcpy(&m_indexData[figureIndex], indexMem, sizeof(INDEX32) * currentFigureCount);
		mesh->UnlockIndexBuffer();
	}
}

void XFileMesh::Release()
{
	m_hierarchy->DestroyFrame(m_root);

	SAFE_DELETE(m_hierarchy);
	SAFE_DELETE_ARR(m_vertexPositionData);
	SAFE_DELETE_ARR(m_indexData);
	SAFE_RELEASE(m_animController);
}


void XFileMesh::Draw(UINT meshContainerIndex, UINT subset)
{
	m_meshContainerList[meshContainerIndex]->MeshData.pMesh->DrawSubset(subset);
}


void XFileMesh::BindingStreamSource(unsigned int _inputLayoutSize)
{
}

Nalmak_MeshContainer * XFileMesh::GetMeshContainer(UINT _index)
{
	return m_meshContainerList[_index];
}

void XFileMesh::TraverseBone(Nalmak_Frame * _frame)
{
	Nalmak_MeshContainer* meshContainer = (Nalmak_MeshContainer*)_frame->pMeshContainer;
	Nalmak_Frame* firstChildFrame = (Nalmak_Frame*)_frame->pFrameFirstChild;
	Nalmak_Frame* siblingFrame = (Nalmak_Frame*)_frame->pFrameSibling;

	if (meshContainer)
	{
		for (UINT i = 0; i < meshContainer->boneCount; ++i)
		{
			const char* boneName = meshContainer->pSkinInfo->GetBoneName(i);

			Nalmak_Frame* frame = (Nalmak_Frame*)D3DXFrameFind(m_root, boneName);
			if (!frame)
				continue;
			meshContainer->boneCombinedMatrices[i] = &frame->boneCombinedMatrix;
		}

		m_meshContainerList.emplace_back(meshContainer);
	}

	if (firstChildFrame)
		TraverseBone(firstChildFrame);

	if (siblingFrame)
		TraverseBone(siblingFrame);
}



LPD3DXANIMATIONCONTROLLER  XFileMesh::GetAnimationController()
{
	return m_animController;
}

LPD3DXFRAME XFileMesh::GetRoot()
{
	return m_root;
}






