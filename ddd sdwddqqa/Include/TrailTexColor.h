#pragma once
#include "VIBuffer.h"
class TrailTexColor :
	public VIBuffer
{
public:
	TrailTexColor();
	~TrailTexColor();

	// VIBuffer을(를) 통해 상속됨
	virtual void Initialize(wstring _fp = L"") override;
};

