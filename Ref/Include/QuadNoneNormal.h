#pragma once

#ifndef __QUAD_NONENORMAL_H__
#define __QUAD_NONENORMAL_H__

#include "VIBuffer.h"
class QuadNoneNormal :
	public VIBuffer
{
public:
	QuadNoneNormal();
	~QuadNoneNormal();

	// VIBuffer을(를) 통해 상속됨
	virtual void Initialize(wstring _fp = L"") override;
private:
	virtual void CreateVertexBuffer();
	virtual void CreateIndexBuffer();
};

#endif
