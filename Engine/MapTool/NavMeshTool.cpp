// NavMeshTool.cpp : 구현 파일입니다.
//

#include "stdafx.h"
#include "Nalmak3D_MapTool.h"
#include "NavMeshTool.h"
#include "afxdialogex.h"


// NavMeshTool 대화 상자입니다.

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
END_MESSAGE_MAP()


// NavMeshTool 메시지 처리기입니다.
