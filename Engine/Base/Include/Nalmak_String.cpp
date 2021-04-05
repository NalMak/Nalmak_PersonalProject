#include "Nalmak_String.h"

bool Nalmak_String::IsDigitString(int * _digit, wstring _string)
{
	int num = _wtoi(_string.c_str());

	if (num != 0)
	{
		*_digit = num;
		return true;
	}
	else if (_string.compare(L"0") == 0)
	{
		*_digit = num;
		return true;
	}
	else if (_string.compare(L"00") == 0)
	{
		*_digit = num;
		return true;
	}

	return false;
}

bool Nalmak_String::IsDigitString(int * _digit, string _string)
{
	int num = atoi(_string.c_str());

	if (num != 0)
	{
		*_digit = num;
		return true;
	}
	else if (_string.compare("0") == 0)
	{
		*_digit = num;
		return true;
	}
	else if (_string.compare("00") == 0)
	{
		*_digit = num;
		return true;
	}

	return false;
}

wstring Nalmak_String::ReadWString_ReadEachCharacter_FromFile(HANDLE _handle)
{
	DWORD byte = 0;
	DWORD nameLength = 0;
	wstring result;
	ReadFile(_handle, &nameLength, sizeof(DWORD), &byte, nullptr);
	TCHAR* nameBuffer = new TCHAR[nameLength + 1];
	for (DWORD i = 0; i < nameLength; ++i)
		ReadFile(_handle, &nameBuffer[i], sizeof(wchar_t), &byte, nullptr);
	nameBuffer[nameLength] = '\0';
	result = nameBuffer;

	SAFE_DELETE(nameBuffer);

	return result;
}

