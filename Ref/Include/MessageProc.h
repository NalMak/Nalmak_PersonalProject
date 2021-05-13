#pragma once
#include "Nalmak_Include.h"


class NALMAK_DLL MessageProc
{
public:
	MessageProc();
	~MessageProc();
protected:
	virtual LRESULT MsgProc(HWND hwnd, UINT msg, WPARAM wParam, LPARAM lParam);
};

