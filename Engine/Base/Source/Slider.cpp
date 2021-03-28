#include "..\Include\Slider.h"

#include "Transform.h"
#include "SingleImage.h"
#include "EventHandler.h"


Slider::Slider(Desc * _desc)
{
	m_background = _desc->background;
	m_fill = _desc->fill;
	
	m_minValue = _desc->minValue;
	m_maxValue = _desc->maxValue;

	m_curValue = _desc->maxValue;
}

void Slider::Initialize()
{
	m_fillWidthOrigin = m_fill->scale.x;
}

void Slider::Update()
{
}

void Slider::UpdateFillAmount(SetFloatFunc _setValueFunc, GetFloatFunc _getValueFunc)
{
	float targetValue = 0.f;
	_setValueFunc(&targetValue, _getValueFunc);

	if (m_curValue != targetValue)
	{
		if (targetValue > m_maxValue)
			m_maxValue = targetValue;

		float fillRatio = targetValue / m_maxValue;
		float newWidth = m_fillWidthOrigin * fillRatio;
		float widthDifference = m_fill->scale.x - newWidth;
		m_fill->position.x = -m_fillWidthOrigin * 0.5f;
		m_fill->position.x += newWidth * 0.5f;
		m_fill->scale.x = newWidth;

		m_curValue = targetValue;
	}
}
