#pragma once

#ifndef __IRESOURCE_H__
#define __IRESOURCE_H__ 	

#include "Nalmak_Include.h"

BEGIN(Nalmak)

class NALMAK_DLL IResource
{
	friend class ResourceManager;
protected:
	explicit IResource();
	virtual ~IResource() = default;
protected:
	virtual void Initialize(wstring _fp) = 0;
	virtual void Release() = 0;
public:
	const wstring& GetName() { return m_name; }
	void SetStatic(bool _static) { m_isStatic = _static; }
protected:
	PDIRECT3DDEVICE9 m_device;
	wstring m_name;
	bool m_isStatic;
};

END
#endif // !__IRESOURCE_H__
