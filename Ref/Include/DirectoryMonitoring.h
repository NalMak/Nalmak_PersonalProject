#pragma once
#include "Component.h"
class DirectoryMonitoring :
	public Component
{
public:
	struct Desc
	{
		wstring directoryPath = L"../Resource/";
	};
public:
	DirectoryMonitoring(Desc* _desc);
	~DirectoryMonitoring();

private:
	virtual void Initialize() override;
	virtual void Update() override;
	virtual void Release() override;
public:
	void StopMonitoring();
	void ResumeMonitorion();
private:
	CRITICAL_SECTION m_crt;
	HANDLE m_thread;
	HANDLE m_eventHandle;
	wstring m_directoryPath;
	bool m_isThreadDone;
private:
	static unsigned __stdcall DoThreadFunc(LPVOID pArg);
};

