#pragma once


// NavMeshTool ��ȭ �����Դϴ�.

class NavMeshTool : public CDialogEx
{
	DECLARE_DYNAMIC(NavMeshTool)

public:
	NavMeshTool(CWnd* pParent = NULL);   // ǥ�� �������Դϴ�.
	virtual ~NavMeshTool();

// ��ȭ ���� �������Դϴ�.
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_DIALOG2 };
#endif

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV �����Դϴ�.

	DECLARE_MESSAGE_MAP()
};