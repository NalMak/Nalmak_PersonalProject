#pragma once
#ifndef  __EVENTHANDLER_H__
#define __EVENTHANDLER_H__

#include "Nalmak_Include.h"

class NALMAK_DLL EventHandler
{
public:
	using Func = function<void(void)>;

private:
	Func m_func;

public:
	int id;
	static int counter;

	EventHandler();
	EventHandler(const Func& _func);
	void operator()();
	void operator=(const EventHandler& _func);
	bool operator==(const EventHandler& _del);
	bool operator!=(nullptr_t);
};

#endif // ! __EVENTHANDLER_H__
