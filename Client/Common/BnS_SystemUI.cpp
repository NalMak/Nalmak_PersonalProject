#include "stdafx.h"
#include "BnS_SystemUI.h"



BnS_SystemUI::BnS_SystemUI(Desc * _desc)
{
}

BnS_SystemUI::~BnS_SystemUI()
{
}

void BnS_SystemUI::Initialize()
{
	m_notifyTimer = 0;
	m_text = GetComponent<Text>();
	m_gameObject->SetPosition(HALF_WINCX, 200);
	m_alpha = 1.f;
}

void BnS_SystemUI::Update()
{
	if (m_notifyTimer > 0)
	{
		m_notifyTimer -= dTime;
		
		if (m_notifyTimer < 2)
		{
			m_alpha = m_notifyTimer * 0.5f;
		}
		else
		{
			m_alpha = 1;
		}
			
		m_text->SetColor(D3DCOLOR_RGBA(255, 255, 255, (int)(m_alpha * 235)));
	}
	else
	{
		m_text->GetGameObject()->SetActive(false);
	}
}

void BnS_SystemUI::Notify(const wstring & _text)
{
	m_notifyTimer = 5.f;
	m_text->SetText(_text);
}
