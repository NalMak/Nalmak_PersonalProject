#include "..\Include\Event.h"
#include "Nalmak_Include.h"



const EventHandler * Event::GetHandler(const int & _index)
{
	if (_index < 0 && m_handlers.size() == 0 &&
		_index >= m_handlers.size())
		return nullptr;

	return m_handlers[_index];
}

void Event::AddHandler(const EventHandler& _handler)
{
	m_handlers.emplace_back(new EventHandler{ _handler });
}

void Event::AddHandler(const int & _index, const EventHandler & _handler)
{
	if (_index < 0 && m_handlers.size() == 0 &&
		_index >= m_handlers.size())
		return;

	m_handlers.insert(m_handlers.begin() + _index, new EventHandler{ _handler });
}

void Event::RemoveHandler(const EventHandler& _handler)
{
	for (vector<EventHandler*>::iterator to_remove = m_handlers.begin();
		to_remove != m_handlers.end();
		++to_remove)
	{
		if (*(*to_remove) == _handler)
		{
			m_handlers.erase(to_remove);
			SAFE_DELETE(*to_remove);
			break;
		}
	}
}

void Event::RemoveHandler(const int & _index)
{
	if (_index < 0 && m_handlers.size() == 0 &&
		_index >= m_handlers.size())
		return;

	m_handlers.erase(m_handlers.begin() + _index);
	SAFE_DELETE(*(m_handlers.begin() + _index));
}

void Event::Release()
{
	for (auto& handler : m_handlers)
		SAFE_DELETE(handler);

	m_handlers.clear();
}

void Event::operator[](int _index)
{
	if (_index < 0 && m_handlers.size() == 0 &&
		_index >= m_handlers.size())
		return;

	(*m_handlers[_index])();
}

void Event::operator()()
{
	NotifyHandlers();
}

Event &Event::operator+=(const EventHandler& _handler)
{
	AddHandler(_handler);

	return *this;
}

Event &Event::operator-=(const EventHandler& _handler)
{
	RemoveHandler(_handler);

	return *this;
}

void Event::NotifyHandlers()
{
	for (vector<EventHandler*>::iterator func = m_handlers.begin();
		func != m_handlers.end();
		++func)
	{
		if (*func != nullptr)
			(*(*func))();
	}
}

void Event::DoEvent(size_t _num)
{
	(*m_handlers[_num])();
}
