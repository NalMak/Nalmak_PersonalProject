#include "XFileMesh.h"
#include "DynamicMeshHierarchy.h"
#include "AnimationController.h"


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
	m_hierarchy = new DynamicMeshHierarchy;

	ThrowIfFailed(D3DXLoadMeshHierarchyFromX(_fp.c_str(), D3DXMESH_32BIT | D3DXMESH_MANAGED, m_device, m_hierarchy, nullptr, &m_root, &m_animController));

	UpdateBoneMatrix();
	TraverseBone((Nalmak_Frame*)m_root);

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


		void* vertexMem = nullptr;
		mesh->LockVertexBuffer(0, &vertexMem);
		DWORD currentVertexCount = mesh->GetNumVertices();
		for (DWORD i = 0; i < currentVertexCount; ++i)
		{
			m_vertexPositionData[vertexIndex] = ((INPUT_LAYOUT_POSITION_NORMAL_UV*)vertexMem)[i].position;
			++vertexIndex;
		}
		mesh->UnlockVertexBuffer();


		vector<INDEX32> test2;
		void* indexMem = nullptr;
		mesh->LockIndexBuffer(0, &indexMem);
		DWORD currentFigureCount = mesh->GetNumFaces();
		for (DWORD i = 0; i < currentFigureCount; ++i)
		{
			m_indexData[figureIndex] = ((INDEX32*)indexMem)[i];
			++figureIndex;
			test2.emplace_back(((INDEX32*)indexMem)[i]);
		}
		//memcpy(&m_indexData[figureIndex], indexMem, sizeof(INDEX32) * currentFigureCount);
		mesh->UnlockIndexBuffer();
	}
	
	
	
	if (m_animController)
	{
		m_meshType = MESH_TYPE_ANIMATION;
	}
	else 
	{
		m_meshType = MESH_TYPE_STATIC;
		D3DXComputeBoundingSphere((Vector3*)m_vertexPositionData,
			m_vertexCount,
			sizeof(INPUT_LAYOUT_POSITION_NORMAL_UV),
			&m_boundingSphereCenter,
			&m_boundingSphereRadius);
	}

}

void XFileMesh::Release()
{
	m_hierarchy->DestroyFrame(m_root);

	SAFE_DELETE(m_hierarchy);
	SAFE_DELETE(m_vertexPositionData);
	SAFE_DELETE(m_indexData);
	SAFE_DELETE(m_animController);
}

void XFileMesh::Draw(UINT subset)
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
				meshContainer->renderingMatrices[i] = meshContainer->offsetMatrices[i] * (*meshContainer->boneWorldMatrices[i]);

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
			meshContainer->boneWorldMatrices[i] = &frame->boneWorldMatrix;
		}

		m_meshContainerList.emplace_back(meshContainer);
	}

	if (firstChildFrame)
		TraverseBone(firstChildFrame);

	if (siblingFrame)
		TraverseBone(siblingFrame);
}

void XFileMesh::UpdateBoneMatrix(Nalmak_Frame * _bone, const Matrix & _parent)
{
	_bone->boneWorldMatrix = _bone->TransformationMatrix * _parent;

	if (_bone->pFrameFirstChild)
		UpdateBoneMatrix((Nalmak_Frame*)_bone->pFrameFirstChild, _bone->boneWorldMatrix);

	if (_bone->pFrameSibling)
		UpdateBoneMatrix((Nalmak_Frame*)_bone->pFrameSibling, _parent);

}


LPD3DXANIMATIONCONTROLLER  XFileMesh::GetAnimationController()
{
	return m_animController;
}

