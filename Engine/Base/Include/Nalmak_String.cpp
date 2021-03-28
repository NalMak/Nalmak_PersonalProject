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
