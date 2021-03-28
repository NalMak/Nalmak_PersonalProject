#include "..\Include\UIInteractor.h"


UIInteractor::UIInteractor(Desc * _desc)
{
}

void UIInteractor::Initialize()
{
}

void UIInteractor::Update()
{
	m_event.NotifyHandlers();
}

void UIInteractor::Release()
{
	m_event.Release();
}

void UIInteractor::AddEventHandler(EventHandler _eventFunc)
{
	m_event += _eventFunc;
}
