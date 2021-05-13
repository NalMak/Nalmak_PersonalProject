#pragma once



#ifndef __EXCEPTION_H__
#define __EXCEPTION_H__

#include <comdef.h>
#include <iostream>
#include <string>
#include "Nalmak_Include.h"

BEGIN(Nalmak)

class NALMAK_DLL Exception
{
public:
	Exception() = default;
	Exception(HRESULT hr, const std::wstring& functionName, const std::wstring& filename, int lineNumber);

	std::wstring ToString()const;

	HRESULT ErrorCode = S_OK;
	std::wstring FunctionName;
	std::wstring Filename;
	int LineNumber = -1;


};

inline std::wstring AnsiToWString(const std::string& str)
{
	WCHAR buffer[512];
	MultiByteToWideChar(CP_ACP, 0, str.c_str(), -1, buffer, 512);
	return std::wstring(buffer);
}

#ifdef _DEBUG

#ifndef ThrowIfFailed
#define ThrowIfFailed(x)                                              \
{                                                                     \
    HRESULT hr__ = (x);                                               \
																	  \
    if(FAILED(hr__)) { assert(0);									  \
	std::wstring wfn = AnsiToWString(__FILE__);                       \
    throw Exception(hr__, L#x, wfn, __LINE__); }					  \
}
#endif

#endif

#ifndef _DEBUG

#define ThrowIfFailed(x)   x                                      

#endif

END
#endif
