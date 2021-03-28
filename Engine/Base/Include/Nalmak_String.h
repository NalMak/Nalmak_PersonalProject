#pragma once

#ifndef __NALMAK_STRING_H__
#define  __NALMAK_STRING_H__

#include <string.h>
#include "Nalmak_Include.h"
using namespace std;

class NALMAK_DLL Nalmak_String
{
public:
	inline static wstring StringToWString(const string& _value)
	{
		wstring value = L"";
		value.assign(_value.begin(), _value.end());

		return value;
	}
	inline static wstring GetVectorToWstring(const Vector3& _vec)
	{
		wstring value = to_wstring(_vec.x) + L", " + to_wstring(_vec.y) + L", " + to_wstring(_vec.z);
		return value;
	}
	inline static wstring GetVectorToWstring(const Vector4& _vec)
	{
		wstring value = to_wstring(_vec.x) + L", " + to_wstring(_vec.y) + L", " + to_wstring(_vec.z) + L", " + to_wstring(_vec.w);
		return value;

	}
	static bool IsDigitString(int* _digit, wstring _string);
	static bool IsDigitString(int* _digit, string _string);

};



#endif