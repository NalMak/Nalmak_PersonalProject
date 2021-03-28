// Nalmak3D_BoneAnimFormView.cpp : 구현 파일입니다.
//

#include "stdafx.h"
#include "Nalmak3D_BoneAnimationTool.h"
#include "Nalmak3D_BoneAnimFormView.h"


// Nalmak3D_BoneAnimFormView

IMPLEMENT_DYNCREATE(Nalmak3D_BoneAnimFormView, CFormView)

Nalmak3D_BoneAnimFormView::Nalmak3D_BoneAnimFormView()
	: CFormView(IDD_NALMAK3D_BONEANIMFORMVIEW)
{

}

Nalmak3D_BoneAnimFormView::~Nalmak3D_BoneAnimFormView()
{
}

void Nalmak3D_BoneAnimFormView::DoDataExchange(CDataExchange* pDX)
{
	CFormView::DoDataExchange(pDX);
}

BEGIN_MESSAGE_MAP(Nalmak3D_BoneAnimFormView, CFormView)
END_MESSAGE_MAP()


// Nalmak3D_BoneAnimFormView 진단입니다.

#ifdef _DEBUG
void Nalmak3D_BoneAnimFormView::AssertValid() const
{
	CFormView::AssertValid();
}

#ifndef _WIN32_WCE
void Nalmak3D_BoneAnimFormView::Dump(CDumpContext& dc) const
{
	CFormView::Dump(dc);
}
#endif
#endif //_DEBUG


// Nalmak3D_BoneAnimFormView 메시지 처리기입니다.
