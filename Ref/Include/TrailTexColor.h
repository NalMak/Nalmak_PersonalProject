#pragma once
#include "VIBuffer.h"
class TrailTexColor :
	public VIBuffer
{
public:
	TrailTexColor();
	~TrailTexColor();

	// VIBuffer��(��) ���� ��ӵ�
	virtual void Initialize(wstring _fp = L"") override;
};

