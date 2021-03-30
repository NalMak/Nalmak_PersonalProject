#pragma once


#include <afxwin.h>         // MFC 핵심 및 표준 구성 요소입니다.
#include <afxocc.h>
class CEdit;
class MFC_Utility
{
public:
	static void SetEditBoxFloat(CEdit* _edit, float _value)
	{
		CString str;
		str.Format(L"%f", _value);
		_edit->SetWindowTextW(str);
	}
	static void SetEditBoxInt(CEdit* _edit, int _value)
	{
		CString str;
		str.Format(L"%d", _value);
		_edit->SetWindowTextW(str);
	}
	static Vector2 GetMFCWindowSize(CView* _view)
	{
		RECT rcView = {};
		_view->GetWindowRect(&rcView);
		SetRect(&rcView, 0, 0, rcView.right - rcView.left, rcView.bottom - rcView.top);
		
		Vector2 windowSize = { (float)rcView.right, (float)rcView.bottom };

		return windowSize;
	}
	 
};

#define GetFloatByEditBox(num , id) { CString value; \
		 GetDlgItem(id)->GetWindowTextW(value);\
			num = (float)_tstof(value);\
}
