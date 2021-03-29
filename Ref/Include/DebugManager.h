#pragma once
#ifndef __DEBUGMANAGER_H__
#define __DEBUGMANAGER_H__

//#define DEBUG_LOG(e)  DebugManager::GetInstance()->DebugLog((#e),e)
#ifdef  _DEBUG
#define DEBUG_LOG(name, e)  DebugManager::GetInstance()->DebugLog(name,e)
#else
#define DEBUG_LOG(name, e)
#endif //  _DEBUG

#include "Nalmak_Include.h"
class Transform;
class GameObject;
class NALMAK_DLL DebugManager
{
	DECLARE_SINGLETON(DebugManager)
public:

private:
	DebugManager();
	~DebugManager();
public:
	wstring GetDebugLog() { return m_debugLog; }
	void DebugLog(const wstring&  _name, const Vector4& _log)
	{
		wstring type = L"Vector4";
		wstring value = to_wstring(_log.x) + L", " + to_wstring(_log.y) + L", " + to_wstring(_log.z) + L", " + to_wstring(_log.w);

		m_debugLog += L"\n-----------------------------------";
		m_debugLog += L"\n   " + _name;
		m_debugLog += L"\n   " + type;
		m_debugLog += L"\n   " + value;
	}
	void DebugLog(const wstring&  _name, const Vector3& _log)
	{
		wstring type = L"Vector3";
		wstring value = to_wstring(_log.x) + L", " + to_wstring(_log.y) + L", " + to_wstring(_log.z);

		m_debugLog += L"\n-----------------------------------";
		m_debugLog += L"\n   " + _name;
		m_debugLog += L"\n   " + type;
		m_debugLog += L"\n   " + value;
	}
	void DebugLog(const wstring&  _name, const Vector2& _log)
	{
		wstring type = L"Vector2";
		wstring value = to_wstring(_log.x) + L", " + to_wstring(_log.y);

		m_debugLog += L"\n-----------------------------------";
		m_debugLog += L"\n   " + _name;
		m_debugLog += L"\n   " + type;
		m_debugLog += L"\n   " + value;
	}
	void DebugLog(const wstring&  _name, const TCHAR* _log)
	{
		wstring value = _log;

		m_debugLog += L"\n-----------------------------------";
		m_debugLog += L"\n   " + _name;
		m_debugLog += L"\n   " + value;

	}
	void DebugLog(const wstring&  _name, Transform* _trs);
	void DebugLog(const wstring&  _name, GameObject* _obj);
	void DebugLog(const wstring&  _name, const wstring& _string);

	template <typename T>
	void DebugLog(const wstring&  _name, const T& _log)
	{
		wstring type = Nalmak_String::StringToWString(typeid(T).name());
		wstring value = to_wstring(_log);

		m_debugLog += L"\n-----------------------------------";
		m_debugLog += L"\n   " + _name;
		m_debugLog += L"\n   " + type;
		m_debugLog += L"\n   " + value;

	}

	void EraseTheRecord();
private:
	wstring m_debugLog;



};

#endif
