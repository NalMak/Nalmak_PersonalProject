#include "..\Include\Toggle.h"
#include "SingleImage.h"
#include "CanvasRenderer.h"
#include "Transform.h"

Toggle::Toggle(Desc * _desc)
	:Button(_desc->desc_button)
{
	ChangeAllTexture(_desc->offImage);

	// dont switch two code lines
	if (_desc->offEventFunc != nullptr)
	m_changeEvent += _desc->offEventFunc;
	if (_desc->onEventFunc != nullptr)
	m_changeEvent += _desc->onEventFunc;
	// dont switch two code lines


	m_waitSprite = ResourceManager::GetInstance()->
		GetResource<Texture>(_desc->onImage)->GetTexure(0);
}

void Toggle::SelectToggle()
{
	if (m_isOn)
		return;

	// 1. value change event
	m_changeEvent[(int)true];

	// 2. button event
	m_event.NotifyHandlers();

	m_isOn = true;

	IDirect3DBaseTexture9* swap = m_normalImage;
	ChangeAllTexture(m_waitSprite);
	m_waitSprite = swap;

	ChangeState(BUTTON_STATE_PRESSED);
}

void Toggle::UnselectToggle()
{
	if (!m_isOn)
		return;

	// 1. value change event
	m_changeEvent[(int)false];

	// 2. button event
	m_event.NotifyHandlers();

	m_isOn = false;

	IDirect3DBaseTexture9* swap = m_normalImage;
	ChangeAllTexture(m_waitSprite);
	m_waitSprite = swap;

	ChangeState(BUTTON_STATE_NORMAL);
}

void Toggle::Initialize()
{
	Button::Initialize();

	m_isOn = false;

}

void Toggle::Update()
{
	Button::Update();
}

void Toggle::LateUpdate()
{
	// click operation
	if (m_renderer->IsPickingBlocked())
		return;

	if (m_renderer->MouseClickUp_InRect())
	{
		if (m_renderer->IsInteractive())
		{
			// 1. value change event
			m_changeEvent[(int)!m_isOn];

			// 2. button event
			m_event.NotifyHandlers();

			m_isOn = !m_isOn;

			IDirect3DBaseTexture9* swap = m_normalImage;
			ChangeAllTexture(m_waitSprite);
			m_waitSprite = swap;

		}

		if(m_isOn)
			ChangeState(BUTTON_STATE_PRESSED);
		else
			ChangeState(BUTTON_STATE_NORMAL);
	}
	else if (m_renderer->MouseClickDown() && !m_isOn)
	{
		ChangeState(BUTTON_STATE_PRESSED);
	}
	else if (m_renderer->MouseClickUp_OutRect() && !m_isOn)
	{
		ChangeState(BUTTON_STATE_NORMAL);
	}
}

void Toggle::Release()
{
	Button::Release();
	m_changeEvent.Release();
}
