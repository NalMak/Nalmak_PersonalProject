#include "..\Include\DebugManager.h"

IMPLEMENT_SINGLETON(DebugManager)

#include "Transform.h"
DebugManager::DebugManager()
{
}


DebugManager::~DebugManager()
{
}

void DebugManager::DebugLog(const wstring&  _name, Transform * _trs)
{
	m_debugLog += L"\n-----------------------------------";
	m_debugLog += L"\n   " + _name;
	m_debugLog += L"\n   position    " + Nalmak_String::GetVectorToWstring(_trs->position);
	m_debugLog += L"\n   rotation    " + Nalmak_String::GetVectorToWstring(Nalmak_Math::QuaternionToEuler(_trs->rotation));
	m_debugLog += L"\n   scale       " + Nalmak_String::GetVectorToWstring(_trs->scale);
}

void DebugManager::DebugLog(const wstring&  _name, GameObject * _obj)
{
	m_debugLog += L"\n-----------------------------------";
	m_debugLog += L"\n   " + _name;
	m_debugLog += L"\n   name        " + _obj->GetName();
	m_debugLog += L"\n   position    " + Nalmak_String::GetVectorToWstring(_obj->GetTransform()->position);
	m_debugLog += L"\n   rotation    " + Nalmak_String::GetVectorToWstring(Nalmak_Math::QuaternionToEuler(_obj->GetTransform()->rotation));
	m_debugLog += L"\n   scale       " + Nalmak_String::GetVectorToWstring(_obj->GetTransform()->scale);
}

void DebugManager::DebugLog(const wstring & _name, const wstring& _string)
{
	m_debugLog += L"\n-----------------------------------";
	m_debugLog += L"\n   " + _name;
	m_debugLog += L"\n   " + _string;
}

void DebugManager::EraseTheRecord()
{
	m_debugLog = L"";
}
