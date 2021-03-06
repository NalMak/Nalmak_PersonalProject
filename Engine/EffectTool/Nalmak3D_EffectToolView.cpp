
// Nalmak3D_EffectToolView.cpp : CNalmak3D_EffectToolView 클래스의 구현
//

#include "stdafx.h"
// SHARED_HANDLERS는 미리 보기, 축소판 그림 및 검색 필터 처리기를 구현하는 ATL 프로젝트에서 정의할 수 있으며
// 해당 프로젝트와 문서 코드를 공유하도록 해 줍니다.
#ifndef SHARED_HANDLERS
#include "Nalmak3D_EffectTool.h"
#endif

#include "Nalmak3D_EffectToolDoc.h"
#include "Nalmak3D_EffectToolView.h"
#include "MainFrm.h"
#include "BaseScene.h"
#include "ParticleObjectManager.h"
#ifdef _DEBUG
#define new DEBUG_NEW
#endif

HWND g_hWnd;
HINSTANCE g_hInst;

IMPLEMENT_DYNCREATE(CNalmak3D_EffectToolView, CView)

BEGIN_MESSAGE_MAP(CNalmak3D_EffectToolView, CView)
	// 표준 인쇄 명령입니다.
	ON_COMMAND(ID_FILE_PRINT, &CView::OnFilePrint)
	ON_COMMAND(ID_FILE_PRINT_DIRECT, &CView::OnFilePrint)
	ON_COMMAND(ID_FILE_PRINT_PREVIEW, &CView::OnFilePrintPreview)
	ON_WM_TIMER()
END_MESSAGE_MAP()

// CNalmak3D_EffectToolView 생성/소멸

CNalmak3D_EffectToolView::CNalmak3D_EffectToolView()
{
	// TODO: 여기에 생성 코드를 추가합니다.

}

CNalmak3D_EffectToolView::~CNalmak3D_EffectToolView()
{
	
	Core::DestroyInstance();
}

BOOL CNalmak3D_EffectToolView::PreCreateWindow(CREATESTRUCT& cs)
{
	// TODO: CREATESTRUCT cs를 수정하여 여기에서
	//  Window 클래스 또는 스타일을 수정합니다.

	return CView::PreCreateWindow(cs);
}

// CNalmak3D_EffectToolView 그리기

void CNalmak3D_EffectToolView::OnDraw(CDC* /*pDC*/)
{
	CNalmak3D_EffectToolDoc* pDoc = GetDocument();
	ASSERT_VALID(pDoc);
	if (!pDoc)
		return;

	Core::GetInstance()->Run();
	// TODO: 여기에 원시 데이터에 대한 그리기 코드를 추가합니다.
}


// CNalmak3D_EffectToolView 인쇄

BOOL CNalmak3D_EffectToolView::OnPreparePrinting(CPrintInfo* pInfo)
{
	// 기본적인 준비
	return DoPreparePrinting(pInfo);
}

void CNalmak3D_EffectToolView::OnBeginPrinting(CDC* /*pDC*/, CPrintInfo* /*pInfo*/)
{
	// TODO: 인쇄하기 전에 추가 초기화 작업을 추가합니다.
}

void CNalmak3D_EffectToolView::OnEndPrinting(CDC* /*pDC*/, CPrintInfo* /*pInfo*/)
{
	// TODO: 인쇄 후 정리 작업을 추가합니다.
}


// CNalmak3D_EffectToolView 진단

#ifdef _DEBUG
void CNalmak3D_EffectToolView::AssertValid() const
{
	CView::AssertValid();
}

void CNalmak3D_EffectToolView::Dump(CDumpContext& dc) const
{
	CView::Dump(dc);
}

CNalmak3D_EffectToolDoc* CNalmak3D_EffectToolView::GetDocument() const // 디버그되지 않은 버전은 인라인으로 지정됩니다.
{
	ASSERT(m_pDocument->IsKindOf(RUNTIME_CLASS(CNalmak3D_EffectToolDoc)));
	return (CNalmak3D_EffectToolDoc*)m_pDocument;
}
#endif //_DEBUG


// CNalmak3D_EffectToolView 메시지 처리기


void CNalmak3D_EffectToolView::OnInitialUpdate()
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
	core.LoadAllResource_OnAwake = false;
	core.resourceDirectoryPath = L"../Resource";
	Core::GetInstance()->Initialize(g_hInst, g_hWnd, &core, AfxGetMainWnd()->m_hWnd);
	Core::GetInstance()->AddScene(L"scene", Scene::Instantiate<BaseScene>());
	Core::GetInstance()->SetStartScene(L"scene");

	SetTimer(1, 16, NULL);

	// TODO: 여기에 특수화된 코드를 추가 및/또는 기본 클래스를 호출합니다.
}


void CNalmak3D_EffectToolView::OnTimer(UINT_PTR nIDEvent)
{
	// TODO: 여기에 메시지 처리기 코드를 추가 및/또는 기본값을 호출합니다.
	Invalidate(false);
	
	CView::OnTimer(nIDEvent);
}
