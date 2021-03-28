#pragma once
#include "Nalmak_Include.h"

class ShaderCompileInclude :public ID3DXInclude
{
public:
	ShaderCompileInclude();
	~ShaderCompileInclude();

	// ID3DXInclude을(를) 통해 상속됨
	virtual HRESULT Open(D3DXINCLUDE_TYPE IncludeType, LPCSTR pFileName, LPCVOID pParentData, LPCVOID * ppData, UINT * pBytes) override;
	virtual HRESULT Close(LPCVOID pData) override;
};

