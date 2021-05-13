#pragma once

#ifndef __LINEVI_H__
#define __LINEVI_H__


#include "Nalmak_Include.h"
#include "VIBuffer.h"
class LineVI :
	public VIBuffer
{
public:
	virtual void Initialize(wstring _fp = L"") override;
private:
	virtual void CreateVertexBuffer();
	virtual void CreateIndexBuffer();
};

#endif // !__LINEVI_H__
