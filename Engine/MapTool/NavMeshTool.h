#pragma once


// NavMeshTool 대화 상자입니다.

class NavMeshTool : public CDialogEx
{
	DECLARE_DYNAMIC(NavMeshTool)

public:
	NavMeshTool(CWnd* pParent = NULL);   // 표준 생성자입니다.
	virtual ~NavMeshTool();

// 대화 상자 데이터입니다.
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_DIALOG2 };
#endif

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 지원입니다.

	DECLARE_MESSAGE_MAP()
public:
	afx_msg void OnBnClickedStartPosition();
	afx_msg void OnBnClickedEndPosition();
	afx_msg void OnBnClickedButtonSaveNav();
	afx_msg void OnBnClickedButtonLoadNav();
};
