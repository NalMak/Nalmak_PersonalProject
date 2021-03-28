#pragma once
#ifndef __NUMBER_H__
#define __NUMBER_H__

#include "Text.h"

class NALMAK_DLL Number :
	public Text
{
public:
	enum PRINTTYPE { NUMBER, TIME_H_M_S, TIME_M, TIME_M_S_MS };

	struct Desc
	{
		Text::Desc text_desc = Text::Desc();

		PRINTTYPE printType = NUMBER;
		float defaultValue = 0.f;
	};

public:
	Number(Desc* _desc);

public:
	void UpdateValue(SetFloatFunc _setValueFunc, GetFloatFunc _getValueFunc);

	void PrintNumber();
	void PrintTime_H_M_S();
	void PrintTime_M_S_MS();

private:
	float m_curValue;

	PRINTTYPE m_printType;
};

#endif // !__NUMBER_H__
