#pragma once
#include "VIBuffer.h"
class TBox :
	public VIBuffer
{
public:
	TBox();
	~TBox();
private:
	// VIBuffer��(��) ���� ��ӵ�
	virtual void Initialize(wstring _fp = L"") override;
private:
	virtual void CreateVertexBuffer();
	virtual void CreateIndexBuffer();
};

