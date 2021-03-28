#pragma once
#include "VIBuffer.h"
class TestVI :
	public VIBuffer
{
public:
	TestVI();
	~TestVI();
public:
	virtual void Initialize(wstring _fp = L"") override;
private:
	virtual void CreateVertexBuffer() override;
	virtual void CreateIndexBuffer() override;
};

