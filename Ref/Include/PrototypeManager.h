#pragma once

#ifndef  __PROTOTYPE_MANAGER_H__
#define __PROTOTYPE_MANAGER_H__

#include "Nalmak_Include.h"
#include "GameObject.h"
class PrototypeManager
{
	DECLARE_SINGLETON(PrototypeManager)
private:
	PrototypeManager();
	~PrototypeManager();
public:
	void AddPrototype(const wstring&  _protoTypeName, GameObject* _obj);
	GameObject* GetPrototype(const wstring&  _prototypeName);
	void Release();
private:
	unordered_map<wstring, GameObject*> m_prototypeList;
};

#endif // ! __PROTOTYPE_MANAGER_H__
