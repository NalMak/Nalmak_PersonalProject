#pragma once



// Nalmak3D_BoneAnimFormView �� ���Դϴ�.

class Nalmak3D_BoneAnimFormView : public CFormView
{
	DECLARE_DYNCREATE(Nalmak3D_BoneAnimFormView)

protected:
	Nalmak3D_BoneAnimFormView();           // ���� ����⿡ ���Ǵ� protected �������Դϴ�.
	virtual ~Nalmak3D_BoneAnimFormView();

public:
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_NALMAK3D_BONEANIMFORMVIEW };
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
};


