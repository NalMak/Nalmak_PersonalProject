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

	DynamicMeshHierarchy hierarchy; // �Է°�  ( ���� ���� -> �Ǻ� ���� -> �Ǻ� ���� -> �� ���� )
	// create frame -> �� ���� 
	// �� �Ѱ��� ���� ����
	// ���� �ٸ����� ���� �װ� ����..

	// ���������� -> �׳� �� ������, first child �� ��ȿ 
	//typedef struct _D3DXFRAME
	//{
	//	LPSTR                   Name;
	//	D3DXMATRIX              TransformationMatrix; // ���

	//	LPD3DXMESHCONTAINER     pMeshContainer; // ��κ��� null , ù��° ���� ������ ����

	//	struct _D3DXFRAME       *pFrameSibling; // ���� ��..  
	//	struct _D3DXFRAME       *pFrameFirstChild; // �ڽ�  ���� -> 4�� 
	//} D3DXFRAME, *LPD3DXFRAME;


	// create meshContainer -> �޽� ����

	// �� -> ������ -> ����� -> �޽������̳� (���� �� �޽�) -> �ִϸ��̼� �޽�
	

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
