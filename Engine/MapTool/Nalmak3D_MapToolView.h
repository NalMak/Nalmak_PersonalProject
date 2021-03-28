
// Nalmak3D_MapToolView.h : CNalmak3D_MapToolView Ŭ������ �������̽�
//

#pragma once
#include "Nalmak3D_MapToolDoc.h"


class CNalmak3D_MapToolView : public CView
{
protected: // serialization������ ��������ϴ�.
	CNalmak3D_MapToolView();
	DECLARE_DYNCREATE(CNalmak3D_MapToolView)

// Ư���Դϴ�.
public:
	CNalmak3D_MapToolDoc* GetDocument() const;

// �۾��Դϴ�.
public:

// �������Դϴ�.
public:
	virtual void OnDraw(CDC* pDC);  // �� �並 �׸��� ���� �����ǵǾ����ϴ�.
	virtual BOOL PreCreateWindow(CREATESTRUCT& cs);
protected:
	virtual BOOL OnPreparePrinting(CPrintInfo* pInfo);
	virtual void OnBeginPrinting(CDC* pDC, CPrintInfo* pInfo);
	virtual void OnEndPrinting(CDC* pDC, CPrintInfo* pInfo);

// �����Դϴ�.
public:
	virtual ~CNalmak3D_MapToolView();
#ifdef _DEBUG
	virtual void AssertValid() const;
	virtual void Dump(CDumpContext& dc) const;
#endif

protected:

// ������ �޽��� �� �Լ�
protected:
	DECLARE_MESSAGE_MAP()
public:
	virtual void OnInitialUpdate();
	afx_msg void OnTimer(UINT_PTR nIDEvent);
};

#ifndef _DEBUG  // Nalmak3D_MapToolView.cpp�� ����� ����
inline CNalmak3D_MapToolDoc* CNalmak3D_MapToolView::GetDocument() const
   { return reinterpret_cast<CNalmak3D_MapToolDoc*>(m_pDocument); }
#endif

