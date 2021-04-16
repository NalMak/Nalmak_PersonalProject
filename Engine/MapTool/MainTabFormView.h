#pragma once
#include "afxcmn.h"


#include "ObjectInstallTool.h"
#include "NavMeshTool.h"
#include "AnimationTool.h"

// MainTabFormView �� ���Դϴ�.

class MainTabFormView : public CFormView
{
	DECLARE_DYNCREATE(MainTabFormView)

protected:
	MainTabFormView();           // ���� ����⿡ ���Ǵ� protected �������Դϴ�.
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
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV �����Դϴ�.

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


