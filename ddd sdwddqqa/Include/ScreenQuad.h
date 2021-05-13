#pragma once
#include "VIBuffer.h"
class ScreenQuad :
	public VIBuffer
{
public:
	ScreenQuad();
	~ScreenQuad();

	// VIBuffer을(를) 통해 상속됨
	virtual void Initialize(wstring _fp = L"") override;
private:
	virtual void CreateVertexBuffer();
	virtual void CreateIndexBuffer();
};

