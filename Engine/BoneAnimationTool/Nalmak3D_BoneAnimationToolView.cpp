
// Nalmak3D_BoneAnimationToolView.cpp : CNalmak3D_BoneAnimationToolView Ŭ������ ����
//

#include "stdafx.h"
// SHARED_HANDLERS�� �̸� ����, ����� �׸� �� �˻� ���� ó���⸦ �����ϴ� ATL ������Ʈ���� ������ �� ������
// �ش� ������Ʈ�� ���� �ڵ带 �����ϵ��� �� �ݴϴ�.
#ifndef SHARED_HANDLERS
#include "Nalmak3D_BoneAnimationTool.h"
#endif

#include "Nalmak3D_BoneAnimationToolDoc.h"
#include "Nalmak3D_BoneAnimationToolView.h"
#include "MainFrm.h"
#include "BaseScene.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif

HWND g_hWnd;
HINSTANCE g_hInst;

IMPLEMENT_DYNCREATE(CNalmak3D_BoneAnimationToolView, CView)

BEGIN_MESSAGE_MAP(CNalmak3D_BoneAnimationToolView, CView)
	// ǥ�� �μ� ����Դϴ�.
	ON_COMMAND(ID_FILE_PRINT, &CView::OnFilePrint)
	ON_COMMAND(ID_FILE_PRINT_DIRECT, &CView::OnFilePrint)
	ON_COMMAND(ID_FILE_PRINT_PREVIEW, &CView::OnFilePrintPreview)
	ON_WM_TIMER()
END_MESSAGE_MAP()

// CNalmak3D_BoneAnimationToolView ����/�Ҹ�

CNalmak3D_BoneAnimationToolView::CNalmak3D_BoneAnimationToolView()
{
	// TODO: ���⿡ ���� �ڵ带 �߰��մϴ�.

}

CNalmak3D_BoneAnimationToolView::~CNalmak3D_BoneAnimationToolView()
{
	Core::DestroyInstance();
}

BOOL CNalmak3D_BoneAnimationToolView::PreCreateWindow(CREATESTRUCT& cs)
{
	// TODO: CREATESTRUCT cs�� �����Ͽ� ���⿡��
	//  Window Ŭ���� �Ǵ� ��Ÿ���� �����մϴ�.

	return CView::PreCreateWindow(cs);
}

// CNalmak3D_BoneAnimationToolView �׸���

void CNalmak3D_BoneAnimationToolView::OnDraw(CDC* /*pDC*/)
{
	CNalmak3D_BoneAnimationToolDoc* pDoc = GetDocument();
	ASSERT_VALID(pDoc);
	if (!pDoc)
		return;

	Core::GetInstance()->Run();
	// TODO: ���⿡ ���� �����Ϳ� ���� �׸��� �ڵ带 �߰��մϴ�.
}


// CNalmak3D_BoneAnimationToolView �μ�

BOOL CNalmak3D_BoneAnimationToolView::OnPreparePrinting(CPrintInfo* pInfo)
{
	// �⺻���� �غ�
	return DoPreparePrinting(pInfo);
}

void CNalmak3D_BoneAnimationToolView::OnBeginPrinting(CDC* /*pDC*/, CPrintInfo* /*pInfo*/)
{
	// TODO: �μ��ϱ� ���� �߰� �ʱ�ȭ �۾��� �߰��մϴ�.
}

void CNalmak3D_BoneAnimationToolView::OnEndPrinting(CDC* /*pDC*/, CPrintInfo* /*pInfo*/)
{
	// TODO: �μ� �� ���� �۾��� �߰��մϴ�.
}


// CNalmak3D_BoneAnimationToolView ����

#ifdef _DEBUG
void CNalmak3D_BoneAnimationToolView::AssertValid() const
{
	CView::AssertValid();
}

void CNalmak3D_BoneAnimationToolView::Dump(CDumpContext& dc) const
{
	CView::Dump(dc);
}

CNalmak3D_BoneAnimationToolDoc* CNalmak3D_BoneAnimationToolView::GetDocument() const // ����׵��� ���� ������ �ζ������� �����˴ϴ�.
{
	ASSERT(m_pDocument->IsKindOf(RUNTIME_CLASS(CNalmak3D_BoneAnimationToolDoc)));
	return (CNalmak3D_BoneAnimationToolDoc*)m_pDocument;
}
#endif //_DEBUG


// CNalmak3D_BoneAnimationToolView �޽��� ó����


void CNalmak3D_BoneAnimationToolView::OnInitialUpdate()
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
	core.LoadAllResource_OnAwake = true;
	core.resourceDirectoryPath = L"../Resource";
	Core::GetInstance()->Initialize(g_hInst, g_hWnd, &core, AfxGetMainWnd()->m_hWnd);
	Core::GetInstance()->AddScene(L"scene", Scene::Instantiate<BaseScene>());
	Core::GetInstance()->SetStartScene(L"scene");

	SetTimer(1, 16, NULL);
}


void CNalmak3D_BoneAnimationToolView::OnTimer(UINT_PTR nIDEvent)
{
	// TODO: ���⿡ �޽��� ó���� �ڵ带 �߰� ��/�Ǵ� �⺻���� ȣ���մϴ�.
	Invalidate(false);

	CView::OnTimer(nIDEvent);
}
