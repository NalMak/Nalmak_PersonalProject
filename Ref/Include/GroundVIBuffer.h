#pragma once
#include "VIBuffer.h"
class GroundVIBuffer :
	public VIBuffer
{
	// VIBuffer을(를) 통해 상속됨
	virtual void Initialize(wstring _fp = L"") override;


private:
	virtual void CreateVertexBuffer();
	virtual void CreateIndexBuffer();
};

