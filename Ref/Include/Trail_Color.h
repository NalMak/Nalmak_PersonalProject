#pragma once
#include "VIBuffer.h"
class Trail_Color :
	public VIBuffer
{
public:
	Trail_Color();
	~Trail_Color();

	// VIBuffer��(��) ���� ��ӵ�
	virtual void Initialize(wstring _fp = L"") override;
};

