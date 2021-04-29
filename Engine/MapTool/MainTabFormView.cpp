// MainTabFormView.cpp : 구현 파일입니다.
//

#include "stdafx.h"
#include "Nalmak3D_MapTool.h"
#include "MainTabFormView.h"
#include "MapToolManager.h"


// MainTabFormView

IMPLEMENT_DYNCREATE(MainTabFormView, CFormView)

MainTabFormView::MainTabFormView()
	: CFormView(IDD_MAINTABFORMVIEW)
{

}

MainTabFormView::~MainTabFormView()
{
}

void MainTabFormView::DoDataExchange(CDataExchange* pDX)
{
	CFormView::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_TAB1, m_mainTab);
}

BEGIN_MESSAGE_MAP(MainTabFormView, CFormView)
	ON_WM_TIMER()
	ON_NOTIFY(TCN_SELCHANGE, IDC_TAB1, &MainTabFormView::OnTcnSelchangeMainTab)
END_MESSAGE_MAP()


// MainTabFormView 진단입니다.

#ifdef _DEBUG
void MainTabFormView::AssertValid() const
{
	CFormView::AssertValid();
}

#ifndef _WIN32_WCE
void MainTabFormView::Dump(CDumpContext& dc) const
{
	CFormView::Dump(dc);
}
#endif
#endif //_DEBUG


// MainTabFormView 메시지 처리기입니다.


void MainTabFormView::OnInitialUpdate()
{
	CFormView::OnInitialUpdate();

//#if defined(DEBUG) | defined(_DEBUG)
//	_CrtSetDbgFlag(_CRTDBG_ALLOC_MEM_DF | _CRTDBG_LEAK_CHECK_DF);
//#endif
//	_CrtSetBreakAlloc(288803);

	m_mainTab.InsertItem(1, L"Object");
	m_mainTab.InsertItem(2, L"Nav Mesh");
	m_mainTab.InsertItem(3, L"Animation");


	CRect rt;
	m_mainTab.GetClientRect(&rt);

	m_objectTab.Create(IDD_DIALOG1, &m_mainTab);
	m_objectTab.SetWindowPos(NULL, 4, 25, rt.Width(), rt.Height() - 30, SWP_SHOWWINDOW | SWP_NOZORDER);
	m_objectTab.ShowWindow(SW_SHOW);

	m_navTab.Create(IDD_DIALOG2, &m_mainTab);
	m_navTab.SetWindowPos(NULL, 4, 25, rt.Width(), rt.Height() - 30, SWP_SHOWWINDOW | SWP_NOZORDER);
	m_navTab.ShowWindow(SW_HIDE);

	m_aniTab.Create(IDD_DIALOG3, &m_mainTab);
	m_aniTab.SetWindowPos(NULL, 4, 25, rt.Width(), rt.Height() - 30, SWP_SHOWWINDOW | SWP_NOZORDER);
	m_aniTab.ShowWindow(SW_HIDE);

	// TODO: 여기에 특수화된 코드를 추가 및/또는 기본 클래스를 호출합니다.
}


void MainTabFormView::OnDraw(CDC* /*pDC*/)
{
	// TODO: 여기에 특수화된 코드를 추가 및/또는 기본 클래스를 호출합니다.
}


void MainTabFormView::OnTimer(UINT_PTR nIDEvent)
{
	// TODO: 여기에 메시지 처리기 코드를 추가 및/또는 기본값을 호출합니다.

	CFormView::OnTimer(nIDEvent);
}



void MainTabFormView::OnTcnSelchangeMainTab(NMHDR *pNMHDR, LRESULT *pResult)
{
	m_objectTab.ShowWindow(SW_HIDE);
	m_navTab.ShowWindow(SW_HIDE);
	m_aniTab.ShowWindow(SW_HIDE);

	int index = m_mainTab.GetCurSel();

	switch (index)
	{
	case 0:
		MapToolManager::GetInstance()->SetToolState(L"object");
		m_objectTab.ShowWindow(SW_SHOW);
		break;
	case 1:
		MapToolManager::GetInstance()->SetToolState(L"navMesh");
		m_navTab.ShowWindow(SW_SHOW);
		break;
	case 2:
		MapToolManager::GetInstance()->SetToolState(L"animation");
		m_aniTab.ShowWindow(SW_SHOW);
		break;
	default:
		break;
	}


	*pResult = 0;
}
