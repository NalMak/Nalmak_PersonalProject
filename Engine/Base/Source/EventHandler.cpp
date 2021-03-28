#include "..\Include\EventHandler.h"
#include "Nalmak_Include.h"


EventHandler::EventHandler() : id{ 0 } { }
int EventHandler::counter = 0;

EventHandler::EventHandler(const Func& _func) : m_func{ _func }
{
	id = ++EventHandler::counter;
}


void EventHandler::operator()()
{
	m_func();
}

void EventHandler::operator=(const EventHandler& _func)
{
	if (m_func == nullptr)
	{
		m_func = _func;
		id = ++EventHandler::counter;
	}
	else
		assert("Fail to event Copy!" && 0);
}

bool EventHandler::operator==(const EventHandler& _del)
{
	return id == _del.id;
}

bool EventHandler::operator!=(nullptr_t)
{
	return m_func != nullptr;
}

