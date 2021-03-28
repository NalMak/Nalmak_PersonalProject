#include "..\Include\PrototypeManager.h"

IMPLEMENT_SINGLETON(PrototypeManager)

PrototypeManager::PrototypeManager()
{
}


PrototypeManager::~PrototypeManager()
{
	Release();
}

void PrototypeManager::AddPrototype(const wstring&  _protoTypeName, GameObject * _obj)
{
	if (m_prototypeList.end() != m_prototypeList.find(_protoTypeName))
	{
		assert(0 && "Prototype is Already exist ");
	}
	m_prototypeList[_protoTypeName] = _obj;

}

GameObject * PrototypeManager::GetPrototype(const wstring&  _prototypeName)
{
	if (m_prototypeList.end() == m_prototypeList.find(_prototypeName))
	{
		assert(0 && "Can't find prototype!");
	}

	return m_prototypeList[_prototypeName];
}

void PrototypeManager::Release()
{
	for (auto& obj : m_prototypeList)
	{
		obj.second->Release();
		SAFE_DELETE(obj.second);
	}
	m_prototypeList.clear();
}
