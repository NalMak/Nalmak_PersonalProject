#pragma once

#ifndef  __QUAD_H__
#define __QUAD_H__

#include "Nalmak_Include.h"
#include "VIBuffer.h"
class Quad :
	public VIBuffer
{
public:
	virtual void Initialize(wstring _fp = L"") override;

private:
	virtual void CreateVertexBuffer();
	virtual void CreateIndexBuffer();
};

#endif // ! __QUAD_H__

