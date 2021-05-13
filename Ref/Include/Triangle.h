#pragma once


#ifndef __TRIANGLE_H__
#define  __TRIANGLE_H__

#include "VIBuffer.h"
class Triangle :
	public VIBuffer
{
public:
	// VIBuffer을(를) 통해 상속됨
	virtual void Initialize(wstring _fp = L"") override;
private:
	virtual void CreateVertexBuffer();
	virtual void CreateIndexBuffer();
};

#endif // !__TRIANGLE_H__
