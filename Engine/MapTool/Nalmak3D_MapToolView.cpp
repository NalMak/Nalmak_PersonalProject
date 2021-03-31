
// Nalmak3D_MapToolView.cpp : CNalmak3D_MapToolView Ŭ������ ����
//

#include "stdafx.h"
// SHARED_HANDLERS�� �̸� ����, ����� �׸� �� �˻� ���� ó���⸦ �����ϴ� ATL ������Ʈ���� ������ �� ������
// �ش� ������Ʈ�� ���� �ڵ带 �����ϵ��� �� �ݴϴ�.
#ifndef SHARED_HANDLERS
#include "Nalmak3D_MapTool.h"
#endif

#include "Nalmak3D_MapToolDoc.h"
#include "Nalmak3D_MapToolView.h"
#include "MainFrm.h"
#include "BaseScene.h"
#include "MFC_Utility.h"
#include "MapToolManager.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif

HWND g_hWnd;
HINSTANCE g_hInst;
IMPLEMENT_DYNCREATE(CNalmak3D_MapToolView, CView)

BEGIN_MESSAGE_MAP(CNalmak3D_MapToolView, CView)
	// ǥ�� �μ� ����Դϴ�.
	ON_COMMAND(ID_FILE_PRINT, &CView::OnFilePrint)
	ON_COMMAND(ID_FILE_PRINT_DIRECT, &CView::OnFilePrint)
	ON_COMMAND(ID_FILE_PRINT_PREVIEW, &CView::OnFilePrintPreview)
	ON_WM_TIMER()
END_MESSAGE_MAP()

// CNalmak3D_MapToolView ����/�Ҹ�

CNalmak3D_MapToolView::CNalmak3D_MapToolView()
{
	// TODO: ���⿡ ���� �ڵ带 �߰��մϴ�.

}

CNalmak3D_MapToolView::~CNalmak3D_MapToolView()
{
	Core::DestroyInstance();
	MapToolManager::DestroyInstance();
}

BOOL CNalmak3D_MapToolView::PreCreateWindow(CREATESTRUCT& cs)
{
	// TODO: CREATESTRUCT cs�� �����Ͽ� ���⿡��
	//  Window Ŭ���� �Ǵ� ��Ÿ���� �����մϴ�.

	return CView::PreCreateWindow(cs);
}

// CNalmak3D_MapToolView �׸���

void CNalmak3D_MapToolView::OnDraw(CDC* /*pDC*/)
{
	CNalmak3D_MapToolDoc* pDoc = GetDocument();
	ASSERT_VALID(pDoc);
	if (!pDoc)
		return;

	if (m_myView)
	{
		Vector2 window = MFC_Utility::GetMFCWindowSize(m_myView);
		Core::GetInstance()->SetWindowSize((UINT)window.x, (UINT)window.y);
	}
	Core::GetInstance()->Run();
}


// CNalmak3D_MapToolView �μ�

BOOL CNalmak3D_MapToolView::OnPreparePrinting(CPrintInfo* pInfo)
{
	// �⺻���� �غ�
	return DoPreparePrinting(pInfo);
}

void CNalmak3D_MapToolView::OnBeginPrinting(CDC* /*pDC*/, CPrintInfo* /*pInfo*/)
{
	// TODO: �μ��ϱ� ���� �߰� �ʱ�ȭ �۾��� �߰��մϴ�.
}

void CNalmak3D_MapToolView::OnEndPrinting(CDC* /*pDC*/, CPrintInfo* /*pInfo*/)
{
	// TODO: �μ� �� ���� �۾��� �߰��մϴ�.
}


// CNalmak3D_MapToolView ����

#ifdef _DEBUG
void CNalmak3D_MapToolView::AssertValid() const
{
	CView::AssertValid();
}

void CNalmak3D_MapToolView::Dump(CDumpContext& dc) const
{
	CView::Dump(dc);
}

CNalmak3D_MapToolDoc* CNalmak3D_MapToolView::GetDocument() const // ����׵��� ���� ������ �ζ������� �����˴ϴ�.
{
	ASSERT(m_pDocument->IsKindOf(RUNTIME_CLASS(CNalmak3D_MapToolDoc)));
	return (CNalmak3D_MapToolDoc*)m_pDocument;
}
#endif //_DEBUG


// CNalmak3D_MapToolView �޽��� ó����


void CNalmak3D_MapToolView::OnInitialUpdate()
{
	CView::OnInitialUpdate();

	CMainFrame* mainFrame = (CMainFrame*)::AfxGetApp()->GetMainWnd();
	RECT frameRect = {};
	RECT thisRect = {};
	mainFrame->GetWindowRect(&frameRect);
	GetClientRect(&thisRect);

	mainFrame->SetWindowPos(nullptr,
		0, 0,
		WINCX + frameRect.right - frameRect.left - thisRect.right,
		WINCY + frameRect.bottom - frameRect.top - thisRect.bottom,
		SWP_NOSIZE | SWP_NOMOVE);


	g_hWnd = m_hWnd;
	g_hInst = AfxGetInstanceHandle();
	Core::Desc core;
	core.wincx = WINCX;
	core.wincy = WINCY;
	core.OBJECT_TAG_COUNT = OBJECT_TAG_MAX;
	core.LoadAllResource_OnAwake = true;
	core.resourceDirectoryPath = L"../../Client/Resource";
	Core::GetInstance()->Initialize(g_hInst, g_hWnd, &core, AfxGetMainWnd()->m_hWnd);
	Core::GetInstance()->AddScene(L"scene", Scene::Instantiate<BaseScene>());
	Core::GetInstance()->SetStartScene(L"scene");

	m_myView = this;

	SetTimer(1, 10, NULL);

	// TODO: ���⿡ Ư��ȭ�� �ڵ带 �߰� ��/�Ǵ� �⺻ Ŭ������ ȣ���մϴ�.
}


void CNalmak3D_MapToolView::OnTimer(UINT_PTR nIDEvent)
{
	// TODO: ���⿡ �޽��� ó���� �ڵ带 �߰� ��/�Ǵ� �⺻���� ȣ���մϴ�.
	Invalidate(false);

	CView::OnTimer(nIDEvent);
}
