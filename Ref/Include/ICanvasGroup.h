#pragma once
#ifndef __ICANVASGROUP_H__
#define __ICANVASGROUP_H__

#include "Nalmak_Include.h"

class NALMAK_DLL ICanvasGroup
{
public:
	ICanvasGroup();
	virtual ~ICanvasGroup() = default;
public:
	virtual void SetFade(float _alpha) = 0;
	virtual void SetInteractive(bool _value) = 0;
	virtual void SetBlockPicking(bool _value) = 0;

	const float& GetFade() { return m_fade; }
	const bool& IsInteractive() { return m_interactive; }
	const bool& IsPickingBlocked() { return m_pickingBlocked; }

protected:
	float m_fade;
	bool m_interactive;
	bool m_pickingBlocked;
	_CANVAS_GROUP m_group;
};

#endif // !__ICANVASGROUP_H__


