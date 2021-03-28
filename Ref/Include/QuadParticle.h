#pragma once

#ifndef __QUAD_PARTICLE__H__
#define __QUAD_PARTICLE__H__

#include "VIBuffer.h"
class QuadParticle :
	public VIBuffer
{
public:
	QuadParticle();
	~QuadParticle();

	// VIBuffer을(를) 통해 상속됨
	virtual void Initialize(wstring _fp = L"") override;
private:
	virtual void CreateVertexBuffer();
	virtual void CreateIndexBuffer();
};

#endif