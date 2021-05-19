#include "stdafx.h"
#include "BnS_SystemSetting.h"



BnS_SystemSetting::BnS_SystemSetting(Desc * _desc)
{
}

BnS_SystemSetting::~BnS_SystemSetting()
{
}

void BnS_SystemSetting::Initialize()
{
	m_rockMouse = true;
	Core::GetInstance()->SetSkyBox(L"cubeTex_nightFall");

#pragma region Light Setting
	DirectionalLight::Desc light;
	light.diffuseIntensity = 0.35f;
	light.ambientIntensity = 0.1f;
	light.color = { 1.f,0.9f,0.88f };
	INSTANTIATE()->AddComponent<DirectionalLight>(&light)->SetRotation(90, 0, 0);
#pragma endregion Light Setting


	ShowCursor(false);
}

void BnS_SystemSetting::Update()
{
	if(m_rockMouse)
		SetCursorPos(HALF_WINCX, HALF_WINCY);

	if (InputManager::GetInstance()->GetKeyDown(KEY_STATE_R))
	{
		m_rockMouse ^= true;
		ShowCursor(!m_rockMouse);
	}
}
