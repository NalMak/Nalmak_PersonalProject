#include "DebugManager.h"
#include "MeshRenderer.h"

IMPLEMENT_SINGLETON(DebugManager)

#include "Transform.h"
#include "Camera.h"
#include "PhysicsManager.h"

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
	m_debugLog += L"\n   position    " + Nalmak_String::GetVectorToWstring(_trs->GetWorldPosition());
	m_debugLog += L"\n   rotation    " + Nalmak_String::GetVectorToWstring(Nalmak_Math::QuaternionToEuler(_trs->GetWorldRotation()));
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

void DebugManager::DebugLog(const wstring & _name, const string & _string)
{
;
	m_debugLog += L"\n-----------------------------------";
	m_debugLog += L"\n   " + _name;
	m_debugLog += L"\n   " + Nalmak_String::StringToWString(_string);
}

void DebugManager::EraseTheRecord()
{
	m_debugLog = L"";
}

