#pragma once
#include "VIBuffer.h"
class ScreenQuad :
	public VIBuffer
{
public:
	ScreenQuad();
	~ScreenQuad();

	// VIBuffer��(��) ���� ��ӵ�
	virtual void Initialize(wstring _fp = L"") override;
private:
	virtual void CreateVertexBuffer();
	virtual void CreateIndexBuffer();
};

