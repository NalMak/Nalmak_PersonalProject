#pragma once

#ifndef __DEVICE_MANAGER_H__
#define __DEVICE_MANAGER_H__

#include "Nalmak_Include.h"

//가상함수와 가상소멸자의 차이 


BEGIN(Nalmak)

class DeviceManager
{
	DECLARE_SINGLETON(DeviceManager)
public:
	DeviceManager();
	~DeviceManager();
public:
	HRESULT Initialize(UINT _wincx, UINT _wincy, HWND _handle, bool _windowMode);
private:
	void Check_SDKVersion();
	void CheckMultiSample();
	void CreateSwapChain(D3DPRESENT_PARAMETERS* _desc,UINT _wincx,UINT _wincy, HWND _handle);
	void CreateDevice(D3DPRESENT_PARAMETERS* _desc, HWND _handle);
	void Release();
public:
	PDIRECT3DDEVICE9 GetDevice() { assert("Can't find device" && m_device); return m_device; }
	HWND GetHWND() { return m_hwnd; }
private:
	PDIRECT3D9 m_SDK = nullptr;
	PDIRECT3DDEVICE9 m_device = nullptr;
	DWORD m_msQualityLev;
	DWORD m_behaviourFlag;
	bool m_displayMode;

	HWND m_hwnd;
};

END


#endif
