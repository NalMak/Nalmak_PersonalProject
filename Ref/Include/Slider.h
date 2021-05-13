#pragma once
#ifndef __SLIDER_H__
#define __SLIDER_H__

#include "Component.h"

class EventHandler;
class Transform;
class NALMAK_DLL Slider :
	public Component
{
public:
	struct Desc
	{
		Transform* background = nullptr;
		Transform* fill = nullptr;

		float minValue = 0.f;
		float maxValue = 100.f;
	};

public:
	Slider(Desc* _desc);

	virtual void Initialize() override;
	virtual void Update() override;

	void UpdateFillAmount(SetFloatFunc _setValueFunc, GetFloatFunc _getValueFunc);

public:
	void SetCurrentValue(float _value) { m_curValue = _value; }
	void SetMinValue(float _value) { m_minValue = _value; }
	void SetMaxValue(float _value) { m_maxValue = _value; }

	float GetCurrentValue() { return m_curValue; }
	float GetMinValue() { return m_minValue; }
	float GetMaxValue() { return m_maxValue; }

		
private:
	Transform* m_background;
	Transform* m_fill;
	float m_fillWidthOrigin;

	float m_curValue;

	float m_minValue;
	float m_maxValue;
};


#endif // !__SLIDER_H__

