#pragma once
#include "VIBuffer.h"
class Trail_Color :
	public VIBuffer
{
public:
	Trail_Color();
	~Trail_Color();

	// VIBuffer을(를) 통해 상속됨
	virtual void Initialize(wstring _fp = L"") override;
};

