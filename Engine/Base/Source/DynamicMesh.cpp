#include "DynamicMesh.h"
#include "DynamicMeshHierarchy.h"


DynamicMesh::DynamicMesh()
{
}


DynamicMesh::~DynamicMesh()
{
}

void DynamicMesh::Initialize(wstring _fp)
{
	m_hierarchy = new DynamicMeshHierarchy;

	DynamicMeshHierarchy hierarchy; // 입력값  ( 뼈를 생성 -> 피부 생성 -> 피부 삭제 -> 뼈 삭제 )
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
	

	D3DXLoadMeshHierarchyFromX(_fp.c_str(), D3DXMESH_32BIT | D3DXMESH_MANAGED, m_device, m_hierarchy,nullptr,&m_root, nullptr);
}

void DynamicMesh::Release()
{
	SAFE_DELETE(m_hierarchy);
}

void DynamicMesh::Draw(UINT subset)
{
}

void DynamicMesh::BindingStreamSource(unsigned int _inputLayoutSize)
{
}
