#pragma once
#include "VIBuffer.h"
class GroundVIBuffer :
	public VIBuffer
{
	// VIBuffer��(��) ���� ��ӵ�
	virtual void Initialize(wstring _fp = L"") override;


private:
	virtual void CreateVertexBuffer();
	virtual void CreateIndexBuffer();
};

