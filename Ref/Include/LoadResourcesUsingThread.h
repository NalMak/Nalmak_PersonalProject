#pragma once
#include "Component.h"
class NALMAK_DLL LoadResourcesUsingThread :
	public Component
{
public:
	struct Desc
	{
		wstring directionPath;
	};
public:
	LoadResourcesUsingThread(Desc* _desc);
	~LoadResourcesUsingThread();

private:
	virtual void Initialize() override;
	virtual void Update() override;
	virtual void Release() override;
private:
	HANDLE m_thread;
	wstring m_directoryPath;
	bool m_isThreadEnd;
	CRITICAL_SECTION m_crt;
public:
	bool IsThreadDone();
	CRITICAL_SECTION GetCRT();
private:
	static unsigned __stdcall DoThreadFunc(LPVOID pArg);
};