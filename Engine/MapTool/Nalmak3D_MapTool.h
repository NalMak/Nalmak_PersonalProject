
// Nalmak3D_MapTool.h : Nalmak3D_MapTool ���� ���α׷��� ���� �� ��� ����
//
#pragma once

#ifndef __AFXWIN_H__
	#error "PCH�� ���� �� ������ �����ϱ� ���� 'stdafx.h'�� �����մϴ�."
#endif

#include "resource.h"       // �� ��ȣ�Դϴ�.


// CNalmak3D_MapToolApp:
// �� Ŭ������ ������ ���ؼ��� Nalmak3D_MapTool.cpp�� �����Ͻʽÿ�.
//

class CNalmak3D_MapToolApp : public CWinAppEx
{
public:
	CNalmak3D_MapToolApp();


// �������Դϴ�.
public:
	virtual BOOL InitInstance();
	virtual int ExitInstance();

// �����Դϴ�.
	afx_msg void OnAppAbout();
	DECLARE_MESSAGE_MAP()
};

extern CNalmak3D_MapToolApp theApp;
