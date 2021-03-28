#include "ShaderCompileInclude.h"
#include <fstream>




ShaderCompileInclude::ShaderCompileInclude()
{
}


ShaderCompileInclude::~ShaderCompileInclude()
{
}

HRESULT ShaderCompileInclude::Open(D3DXINCLUDE_TYPE IncludeType, LPCSTR pFileName, LPCVOID pParentData, LPCVOID * ppData, UINT * pBytes)
{
	std::ifstream f;
	f.open(pFileName);
	if (!f)
		return D3DXERR_INVALIDDATA;
	f.seekg(0, std::ios::end);//파일포인터 끝으로 이동
	int size = (int)f.tellg();
	f.seekg(0, std::ios::beg);//파일포인터 처음으로 이동
	char* buffer = new char[size + 1];
	f.get(buffer, size, '\0');
	buffer[size] = 0;
	f.close();
	*ppData = buffer;
	*pBytes = size;
	return D3D_OK;
}

HRESULT ShaderCompileInclude::Close(LPCVOID pData)
{
	delete[](char*)pData;
	return D3D_OK;
}
