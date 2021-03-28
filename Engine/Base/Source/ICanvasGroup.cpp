#include "ICanvasGroup.h"

ICanvasGroup::ICanvasGroup()
	:m_fade(1.f)
	, m_interactive(true)
	, m_pickingBlocked(false)
	, m_group(0)
{

}

void ICanvasGroup::SetFade(float _alpha)
{
	m_fade = _alpha;
}

void ICanvasGroup::SetInteractive(bool _value)
{
	m_interactive = _value;
}

void ICanvasGroup::SetBlockPicking(bool _value)
{
	m_pickingBlocked = _value;
}
