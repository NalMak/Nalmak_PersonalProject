
// Nalmak3D_BoneAnimationTool.h : Nalmak3D_BoneAnimationTool ���� ���α׷��� ���� �� ��� ����
//
#pragma once

#ifndef __AFXWIN_H__
	#error "PCH�� ���� �� ������ �����ϱ� ���� 'stdafx.h'�� �����մϴ�."
#endif

#include "resource.h"       // �� ��ȣ�Դϴ�.


// CNalmak3D_BoneAnimationToolApp:
// �� Ŭ������ ������ ���ؼ��� Nalmak3D_BoneAnimationTool.cpp�� �����Ͻʽÿ�.
//

class CNalmak3D_BoneAnimationToolApp : public CWinApp
{
public:
	CNalmak3D_BoneAnimationToolApp();


// �������Դϴ�.
public:
	virtual BOOL InitInstance();
	virtual int ExitInstance();

// �����Դϴ�.
	afx_msg void OnAppAbout();
	DECLARE_MESSAGE_MAP()
};

extern CNalmak3D_BoneAnimationToolApp theApp;
