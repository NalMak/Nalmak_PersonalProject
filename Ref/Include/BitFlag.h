#pragma once

#ifndef __BITFLAG_H__
#define __BITFLAG_H__

#include "Nalmak_Include.h"

template <typename Enum>
class NALMAK_DLL BitFlag
{
public:
	BitFlag() = default;
	BitFlag(int _num)
	{
		m_flag = _num;
	}

	void AllOff() // Set bit 0
	{
		m_flag = 0;
	}
	void AllOn() // Set bit 1
	{
		m_flag = UINT32_MAX;
	}

	void On(Enum _flag) // bit On
	{
		m_flag |= (1 << _flag);
	}
	template <typename Enum, typename... Enums>
	void On(Enum _flag, Enums... _flags)
	{
		m_flag |= (1 << _flag);

		On(_flags...);
	}
	void Off(Enum _flag) // bit Off
	{
		m_flag &= ~(1 << _flag);
	}
	template <typename Enum, typename... Enums>
	void Off(Enum _flag, Enums... _flags)
	{
		m_flag &= ~(1 << _flag);

		On(_flags...);
	}

	bool Check(Enum _flag) // 0 -> false  1 -> true
	{

		return ((m_flag & (1 << _flag)) != 0);
	}
	template <typename Enum, typename... Enums>
	bool Check(Enum _flag, Enums... _flags) // 모든 매개변수가 true일 때 true반환
	{
		return (((m_flag & (1 << _flag)) & Check(_flags...)) != 0);
	}

private:
	unsigned int m_flag = UINT32_MAX; // Maximum flag Count = 32
};


#endif // !__BITFLAG_H__
