#include "XFileMesh.h"
#include "MeshHierarchy.h"
#include "AnimationController.h"
#include "Shader.h"

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

	ThrowIfFailed(D3DXLoadMeshHierarchyFromX(_fp.c_str(), D3DXMESH_32BIT | D3DXMESH_MANAGED, m_device, m_hierarchy, nullptr, &m_root, &m_animController));

	Matrix base = { 1,0,0,0,0,1,0,0,0,0,1,0,0,0,0,1 };
	AnimationController::UpdateBoneMatrix((Nalmak_Frame*)m_root,base);
	TraverseBone((Nalmak_Frame*)m_root);

	m_isRenderHW = true;
	for (auto& meshContainer : m_meshContainerList)
	{
		if (!meshContainer->pSkinInfo)
		{
			m_isRenderHW = false;
			break;
		}
	}
	if (m_isRenderHW)
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

		DWORD FVF = meshContainer->MeshData.pMesh->GetFVF();
		m_stride = D3DXGetFVFVertexSize(FVF);
	}

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
			m_vertexPositionData[vertexIndex] = *((Vector3*)(((unsigned char*)vertexMem) + (m_stride * i + offset)));
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

		DWORD boneCombinationCount = 0;
		SAFE_RELEASE(mesh);

		ThrowIfFailed(newMeshContainer->pSkinInfo->ConvertToIndexedBlendedMesh(
			newMeshContainer->originalMesh,
			D3DXMESH_MANAGED | D3DXMESH_WRITEONLY,
			100,
			nullptr,
			nullptr,
			nullptr,
			nullptr,
			&newMeshContainer->maxVertexInfl,
			&boneCombinationCount,
			&newMeshContainer->boneCombinationTable,
			&mesh
		));

		mesh->GetAttributeTable(nullptr, &newMeshContainer->attributeTableCount);
	
		D3DXATTRIBUTERANGE* attributeTable = new D3DXATTRIBUTERANGE[newMeshContainer->attributeTableCount];
		mesh->GetAttributeTable(attributeTable, &newMeshContainer->attributeTableCount);
		SAFE_DELETE_ARR(attributeTable);
		
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

		DWORD FVF = meshContainer->MeshData.pMesh->GetFVF();
		m_stride = D3DXGetFVFVertexSize(FVF);
	}
}

void XFileMesh::Release()
{
	m_hierarchy->DestroyFrame(m_root);

	SAFE_DELETE(m_hierarchy);
	SAFE_DELETE(m_vertexPositionData);
	SAFE_DELETE(m_indexData);
	SAFE_RELEASE(m_animController);
}



void XFileMesh::Draw(UINT subset)
{
}

void XFileMesh::Draw(Shader* _shader)
{
	if (m_isRenderHW)
	{
		for (auto& meshContainer : m_meshContainerList)
		{
			UINT subsetCount = 0;


			UINT boneCount = 50;

			if(meshContainer->boneCount < boneCount)
			{
				boneCount = meshContainer->boneCount;
			}

			LPD3DXBONECOMBINATION boneCombination = (LPD3DXBONECOMBINATION)meshContainer->boneCombinationTable->GetBufferPointer();
			for (UINT palette = 0; palette < boneCount; ++palette)
			{
				int matrixIndex = boneCombination[subsetCount].BoneId[palette];
				if (matrixIndex != UINT_MAX)
				{
					meshContainer->renderingMatrices[palette] = meshContainer->offsetMatrices[matrixIndex] * (*meshContainer->boneCombinedMatrices[matrixIndex]);
				}
			}
			_shader->SetInt("g_bone", meshContainer->maxVertexInfl);
			_shader->SetMatrixArray("g_paletteMatricies", meshContainer->renderingMatrices, boneCount);
			_shader->CommitChanges();

			for (unsigned long i = 0; i < meshContainer->NumMaterials; ++i)
			{
				meshContainer->MeshData.pMesh->DrawSubset(i);
			}
		}
	}
	else
	{
		for (auto& meshContainer : m_meshContainerList)
		{
			LPD3DXSKININFO skin = meshContainer->pSkinInfo;
			if (skin)
			{
				void* srcVtx = nullptr;
				void* dstVtx = nullptr;

				meshContainer->originalMesh->LockVertexBuffer(0, &srcVtx);
				meshContainer->MeshData.pMesh->LockVertexBuffer(0, &dstVtx);

				for (unsigned long i = 0; i < meshContainer->boneCount; ++i)
					meshContainer->renderingMatrices[i] = meshContainer->offsetMatrices[i] * (*meshContainer->boneCombinedMatrices[i]);

				skin->UpdateSkinnedMesh(
					meshContainer->renderingMatrices,
					NULL, // 원상복귀 행렬
					srcVtx,
					dstVtx);

				// shader 처리 
				// commit change

				for (unsigned long i = 0; i < meshContainer->NumMaterials; ++i)
				{
					meshContainer->MeshData.pMesh->DrawSubset(i);
				}

				meshContainer->originalMesh->UnlockVertexBuffer();
				meshContainer->MeshData.pMesh->UnlockVertexBuffer();
			}
			else
			{
				for (unsigned long i = 0; i < meshContainer->NumMaterials; ++i)
				{
					meshContainer->MeshData.pMesh->DrawSubset(i);
				}
			}
		}
	}
	
}

void XFileMesh::DrawHW()
{



}

bool XFileMesh::IsRenderHW()
{
	return m_isRenderHW;
}

void XFileMesh::BindingStreamSource(unsigned int _inputLayoutSize)
{
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
			meshContainer->boneCombinedMatrices[i] = &frame->boneWorldMatrix;
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




