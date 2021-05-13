#pragma once
#include "VIBuffer.h"
class Box :
	public VIBuffer
{
public:
	Box();
	~Box();

	// VIBuffer을(를) 통해 상속됨
	virtual void Initialize(wstring _fp = L"") override;
private:
	virtual void CreateVertexBuffer();
	virtual void CreateIndexBuffer();
};

