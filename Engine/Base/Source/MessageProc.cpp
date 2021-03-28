#include "..\Include\MessageProc.h"



MessageProc::MessageProc()
{
}


MessageProc::~MessageProc()
{
}

LRESULT MessageProc::MsgProc(HWND hwnd, UINT msg, WPARAM wParam, LPARAM lParam)
{
	switch (msg)
	{
		case WM_DESTROY:
		{
			//delete Debug;
			PostQuitMessage(0);
			return 0;
		}
		case WM_MOUSEHWHEEL:
		{

			break;
		}
	}
}
