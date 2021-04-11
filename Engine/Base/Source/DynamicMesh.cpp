#include "DynamicMesh.h"
#include "DynamicMeshHierarchy.h"
#include "AnimationController.h"



void DynamicMesh::Initialize(wstring _fp)
{
	// 뼈의 상태를 담고있는 행렬 
	// 뼈의 행렬을 로컬로 담아야함 -> 스킨인포가 해줌
	// offsetmatrix-> 담겨져있음
	// hardware skinning 

	m_hierarchy = new DynamicMeshHierarchy;

	// 입력값  ( 뼈를 생성 -> 피부 생성 -> 피부 삭제 -> 뼈 삭제 )
	// create frame -> 뼈 생성 
	// 뼈 한개에 대한 정보
	// 보통 다리부터 시작 그게 좋음..

	// 시작프레임 -> 그냥 빈 껍데기, first child 만 유효 
	//typedef struct _D3DXFRAME
	//{
	//	LPSTR                   Name;
	//	D3DXMATRIX              TransformationMatrix; // 행렬

	//	LPD3DXMESHCONTAINER     pMeshContainer; // 대부분은 null , 첫번째 뼈만 가지고 있음

	//	struct _D3DXFRAME       *pFrameSibling; // 형제 뼈..  
	//	struct _D3DXFRAME       *pFrameFirstChild; // 자식  몸통 -> 4개 
	//} D3DXFRAME, *LPD3DXFRAME;


	// create meshContainer -> 메시 생성

	// 점 -> 폴리곤 -> 서브셋 -> 메시컨테이너 (파츠 별 메시) -> 애니메이션 메시
	LPD3DXANIMATIONCONTROLLER controller = nullptr;

	ThrowIfFailed(D3DXLoadMeshHierarchyFromX(_fp.c_str(), D3DXMESH_32BIT | D3DXMESH_MANAGED, m_device, m_hierarchy, nullptr, &m_root, &controller));
	controller->GetMaxNumAnimationSets();
	m_animController =  new AnimationController(controller);

	UpdateBoneMatrix();

	TraverseBone((Nalmak_Frame*)m_root);


	for (auto& meshContainer : m_meshContainerList)
	{
		m_vertexCount += meshContainer->MeshData.pMesh->GetNumVertices();
		m_figureCount += meshContainer->MeshData.pMesh->GetNumFaces();
	}

	m_vertexPositionData = new Vector3[m_vertexCount];
	m_indexData = new INDEX32[m_figureCount * 3];

	DWORD vertexIndex = 0;
	DWORD figureIndex = 0;

	for (auto& meshContainer : m_meshContainerList)
	{
		D3DVERTEXELEMENT9 decl[MAX_FVF_DECL_SIZE];
		ZeroMemory(decl, sizeof(D3DVERTEXELEMENT9) * MAX_FVF_DECL_SIZE);

		meshContainer->MeshData.pMesh->GetDeclaration(decl);

		WORD offset = 0;

		for (int i = 0; i < MAX_FVF_DECL_SIZE; ++i)
		{
			if (decl[i].Usage == D3DDECLUSAGE_POSITION)
			{
				offset = decl[i].Offset;
				break;
			}
		}

		DWORD FVF = meshContainer->MeshData.pMesh->GetFVF();
		m_stride = D3DXGetFVFVertexSize(FVF);


		///////////////////////////////////////////
		void* vertexMem = nullptr;
		meshContainer->MeshData.pMesh->LockVertexBuffer(0, &vertexMem);
		for (DWORD i = 0; i < meshContainer->MeshData.pMesh->GetNumVertices(); ++i)
		{
			m_vertexPositionData[vertexIndex] = ((INPUT_LAYOUT_POSITION_NORMAL_UV*)vertexMem)[i].position;
			++vertexIndex;
		}
		meshContainer->MeshData.pMesh->UnlockVertexBuffer();
		///////////////////////////////////////////

		void* indexMem = nullptr;
		meshContainer->MeshData.pMesh->LockIndexBuffer(0, &indexMem);
		DWORD currentFigureCount = meshContainer->MeshData.pMesh->GetNumFaces() * 3;
		//memcpy(&m_indexData[figureIndex], indexMem, sizeof(INDEX32) * currentFigureCount);
		figureIndex += currentFigureCount;
		meshContainer->MeshData.pMesh->UnlockIndexBuffer();


	}

}

void DynamicMesh::Release()
{
	m_hierarchy->DestroyFrame(m_root);

	SAFE_DELETE(m_hierarchy);
	SAFE_DELETE(m_vertexPositionData);
	SAFE_DELETE(m_indexData);
	SAFE_DELETE(m_animController);
}

void DynamicMesh::Draw(UINT subset)
{

	for (auto& meshContainer : m_meshContainerList)
	{
		void* srcVtx = nullptr;
		void* dstVtx = nullptr;

		meshContainer->originalMesh->LockVertexBuffer(0, &srcVtx);
		meshContainer->MeshData.pMesh->LockVertexBuffer(0, &dstVtx);

		for (unsigned long i = 0; i < meshContainer->boneCount; ++i)
			meshContainer->renderingMatrices[i] = meshContainer->offsetMatrices[i] * (*meshContainer->boneWorldMatrices[i]);

		meshContainer->pSkinInfo->UpdateSkinnedMesh(
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
}

void DynamicMesh::BindingStreamSource(unsigned int _inputLayoutSize)
{
	
}

void DynamicMesh::UpdateBoneMatrix(Nalmak_Frame * _bone, const Matrix & _parentMatrix)
{
	_bone->boneWorldMatrix = _bone->TransformationMatrix * _parentMatrix;

	if (_bone->pFrameFirstChild)
		UpdateBoneMatrix((Nalmak_Frame*)_bone->pFrameFirstChild, _bone->boneWorldMatrix);

	if (_bone->pFrameSibling)
		UpdateBoneMatrix((Nalmak_Frame*)_bone->pFrameSibling, _parentMatrix);

}
void DynamicMesh::TraverseBone(Nalmak_Frame * _frame)
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
			if(!frame)
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

void DynamicMesh::SetAnimation(UINT _index)
{
	m_animController->SetAnimation(_index,1.f,1.f);
}

void DynamicMesh::UpdateBoneMatrix()
{
	Matrix mat;
	UpdateBoneMatrix((Nalmak_Frame*)m_root, *D3DXMatrixIdentity(&mat));
}

void DynamicMesh::UpdateAnimationController()
{
	m_animController->PlayAnimation();
}



