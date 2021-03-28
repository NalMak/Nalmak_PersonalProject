#pragma once



// Nalmak3D_BoneAnimFormView 폼 뷰입니다.

class Nalmak3D_BoneAnimFormView : public CFormView
{
	DECLARE_DYNCREATE(Nalmak3D_BoneAnimFormView)

protected:
	Nalmak3D_BoneAnimFormView();           // 동적 만들기에 사용되는 protected 생성자입니다.
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
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 지원입니다.

	DECLARE_MESSAGE_MAP()
};


