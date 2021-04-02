// NavMeshTool.cpp : ���� �����Դϴ�.
//

#include "stdafx.h"
#include "Nalmak3D_MapTool.h"
#include "NavMeshTool.h"
#include "afxdialogex.h"
#include "MapToolManager.h"
#include "MapTool_NavMeshState.h"


// NavMeshTool ��ȭ �����Դϴ�.

IMPLEMENT_DYNAMIC(NavMeshTool, CDialogEx)

NavMeshTool::NavMeshTool(CWnd* pParent /*=NULL*/)
	: CDialogEx(IDD_DIALOG2, pParent)
{

}

NavMeshTool::~NavMeshTool()
{
}

void NavMeshTool::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
}


BEGIN_MESSAGE_MAP(NavMeshTool, CDialogEx)
	ON_BN_CLICKED(IDC_BUTTON1, &NavMeshTool::OnBnClickedStartPosition)
	ON_BN_CLICKED(IDC_BUTTON2, &NavMeshTool::OnBnClickedEndPosition)
END_MESSAGE_MAP()


// NavMeshTool �޽��� ó�����Դϴ�.


void NavMeshTool::OnBnClickedStartPosition()
{
	MapTool_NavMeshState* nav = MapToolManager::GetInstance()->GetToolState()->GetState<MapTool_NavMeshState>(L"navMesh");
	nav->SetNavMeshToolMode(MapTool_NavMeshState::NAVMESH_TOOL_MODE_SET_START_POINT);
	// TODO: ���⿡ ��Ʈ�� �˸� ó���� �ڵ带 �߰��մϴ�.
}


void NavMeshTool::OnBnClickedEndPosition()
{
	MapTool_NavMeshState* nav = MapToolManager::GetInstance()->GetToolState()->GetState<MapTool_NavMeshState>(L"navMesh");
	nav->SetNavMeshToolMode(MapTool_NavMeshState::NAVMESH_TOOL_MODE_SET_END_POINT);
	// TODO: ���⿡ ��Ʈ�� �˸� ó���� �ڵ带 �߰��մϴ�.
}
