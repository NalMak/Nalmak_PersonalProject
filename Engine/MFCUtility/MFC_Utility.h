#pragma once


#include <afxwin.h>         // MFC �ٽ� �� ǥ�� ���� ����Դϴ�.
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
	
	 
};

#define GetFloatByEditBox(num , id) { CString value; \
		 GetDlgItem(id)->GetWindowTextW(value);\
			num = (float)_tstof(value);\
}
