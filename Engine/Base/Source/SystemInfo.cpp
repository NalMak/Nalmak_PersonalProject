#include "..\Include\SystemInfo.h"
#include "Text.h"
#include "SystemManager.h"
#include "DebugManager.h"
#include "Transform.h"
#include "RenderManager.h"
#include "CanvasRenderer.h"
SystemInfo::SystemInfo(Desc* _desc)
{
	m_fontSize = _desc->fontSize;
}


SystemInfo::~SystemInfo()
{
}

void SystemInfo::Initialize()
{

	Text::Desc text;
	text.width = (UINT)m_fontSize.x;
	text.height = (UINT)m_fontSize.y;
	text.option = DT_LEFT | DT_NOCLIP;
	text.color = D3DXCOLOR(0, 1, 0, 1);
	m_gameObject->AddComponent<Text>(&text);
	m_gameObject->AddComponent<CanvasRenderer>();
	m_text = GetComponent<Text>();
	assert(m_text && L"Must have text Component!");


	m_systemInfo = SystemManager::GetInstance();
	m_debugLog = DebugManager::GetInstance();
}

void SystemInfo::PreRender()
{
	m_info = m_systemInfo->GetFPS() + m_debugLog->GetDebugLog() + L"\n-----------------------------------";
	m_text->SetText(m_info);
}

void SystemInfo::Update()
{
}

