#pragma once
#include "VIBuffer.h"
class SkyBox :
	public VIBuffer
{
public:
	SkyBox();
	~SkyBox();

	// VIBuffer��(��) ���� ��ӵ�
	virtual void Initialize(wstring _fp = L"") override;
private:
	virtual void CreateVertexBuffer();
	virtual void CreateIndexBuffer();
};

