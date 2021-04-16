#pragma once
#include "afxcmn.h"


#include "ObjectInstallTool.h"
#include "NavMeshTool.h"
#include "AnimationTool.h"

// MainTabFormView 폼 뷰입니다.

class MainTabFormView : public CFormView
{
	DECLARE_DYNCREATE(MainTabFormView)

protected:
	MainTabFormView();           // 동적 만들기에 사용되는 protected 생성자입니다.
	virtual ~MainTabFormView();

public:
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_MAINTABFORMVIEW };
#endif
#ifdef _DEBUG
	virtual void AssertValid() const;
#ifndef _WIN32_WCE
	virtual void Dump(CDumpContext& dc) const;
#endif
#endif

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 지원입니다.

	DECLARE_MESSAGE_MAP()
public:
	virtual void OnInitialUpdate();
	virtual void OnDraw(CDC* /*pDC*/);
	afx_msg void OnTimer(UINT_PTR nIDEvent);
	CTabCtrl m_mainTab;

	ObjectInstallTool m_objectTab;
	NavMeshTool m_navTab;
	AnimationTool m_aniTab;
	afx_msg void OnTcnSelchangeMainTab(NMHDR *pNMHDR, LRESULT *pResult);
};


