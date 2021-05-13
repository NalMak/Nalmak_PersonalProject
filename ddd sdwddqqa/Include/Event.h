#pragma once

#ifndef __EVENT_H__
#define __EVENT_H__

#include "EventHandler.h"

// Please Call Release!
class NALMAK_DLL Event
{
public:
	const EventHandler* GetHandler(const int& _index);
	void AddHandler(const EventHandler& _handler);
	void AddHandler(const int& _index, const EventHandler& _handler);
	void RemoveHandler(const EventHandler& _handler);
	void RemoveHandler(const int& _index);
	void Release();
	void operator[](int _index);
	void operator()();
	Event &operator+=(const EventHandler& _handler);
	Event &operator-=(const EventHandler& _handler);

private:
	vector<EventHandler*> m_handlers;
public:
	void NotifyHandlers();
	void DoEvent(size_t _num);
};



#endif // !__EVENT_H__
