#pragma once
#include "Nalmak_Define.h"

// T -> Component or GameObject
template <typename T>
bool NALMAK_DLL IsValid(T*& _instance)
{
	if (_instance)
	{
		if (_instance->IsAlive())
		{
			return true;
		}
		else
		{
			_instance = nullptr;
			return false;
		}
	}
	return false;
}


