#include "Nalmak_Include.h"
#include "Bezier.h"

Bezier::Bezier()
{
	m_bezierPoints[0].x = 0;
	m_bezierPoints[0].y = 0;
	m_bezierPoints[1].x = 0.5f;
	m_bezierPoints[1].y = 0;
	m_bezierPoints[2].x = 0.5f;
	m_bezierPoints[2].y = 1;
	m_bezierPoints[3].x = 1;
	m_bezierPoints[3].y = 1;

}



Bezier::Bezier(const float & _x1, const float & _y1, const float & _x2, const float & _y2, const float & _x3, const float & _y3, const float & _x4, const float & _y4)
{
	m_bezierPoints[0].x = _x1;
	m_bezierPoints[0].y = _y1;
	m_bezierPoints[1].x = _x2;
	m_bezierPoints[1].y = _y2;
	m_bezierPoints[2].x = _x3;
	m_bezierPoints[2].y = _y3;
	m_bezierPoints[3].x = _x4;
	m_bezierPoints[3].y = _y4;


}

Bezier::Bezier(const Vector2 & _p1, const Vector2 & _p2, const Vector2 & _p3, const Vector2 & _p4)
{
	m_bezierPoints[0] = _p1;
	m_bezierPoints[1] = _p2;
	m_bezierPoints[2] = _p3;
	m_bezierPoints[3] = _p4;

}

Bezier::~Bezier()
{

}

void Bezier::SetInterpolationType(INTERPOLATION_TYPE _type)
{
	switch (_type)
	{
	case INTERPOLATION_TYPE_ACCELERATE_DECELERTAE:
		m_bezierPoints[0] = Vector2(0, 0);
		m_bezierPoints[1] = Vector2(0.7f, 0);
		m_bezierPoints[2] = Vector2(0.3f, 1);
		m_bezierPoints[3] = Vector2(1, 1);
		break;
	case INTERPOLATION_TYPE_ACCELERATE:
		m_bezierPoints[0] = Vector2(0, 0);
		m_bezierPoints[1] = Vector2(0.8f, 0);
		m_bezierPoints[2] = Vector2(1, 0.2f);
		m_bezierPoints[3] = Vector2(1, 1);
		break;
	case INTERPOLATION_TYPE_DECELERATE:
		m_bezierPoints[0] = Vector2(0, 0);
		m_bezierPoints[1] = Vector2(0, 0.8f);
		m_bezierPoints[2] = Vector2(0.2f, 1);
		m_bezierPoints[3] = Vector2(1, 1);
		break;
	case INTERPOLATION_TYPE_LINEAR:
		m_bezierPoints[0] = Vector2(0, 0);
		m_bezierPoints[1] = Vector2(0.1666f, 0.1666f);
		m_bezierPoints[2] = Vector2(0.8333f, 0.8333f);
		m_bezierPoints[3] = Vector2(1, 1);
		break;
	case INTERPOLATION_TYPE_ANTICIPATE:
		m_bezierPoints[0] = Vector2(0, 0);
		m_bezierPoints[1] = Vector2(0.59f, -0.53f);
		m_bezierPoints[2] = Vector2(0.89f, 0.43f);
		m_bezierPoints[3] = Vector2(1, 1);
		break;
	case INTERPOLATION_TYPE_OVERSHOOT:
		m_bezierPoints[0] = Vector2(0, 0);
		m_bezierPoints[1] = Vector2(0.115f, 0.53f);
		m_bezierPoints[2] = Vector2(0.336f, 1.396f);
		m_bezierPoints[3] = Vector2(1, 1);
		break;
	case INTERPOLATION_TYPE_DECELERATE_ACCELERATE:
		m_bezierPoints[0] = Vector2(0, 0);
		m_bezierPoints[1] = Vector2(0.f, 0.99f);
		m_bezierPoints[2] = Vector2(1.f, 0.01f);
		m_bezierPoints[3] = Vector2(1, 1);
		break;
	default:
		break;
	}


}

Vector2 Bezier::GetPoint(float _t) const
{
	Vector2 result;

	float ax, bx, cx;
	float ay, by, cy;
	float tSquared, tCubed;
	float t = Nalmak_Math::Clamp(_t, 0.f, 1.f);

	cx = 3.0f * (m_bezierPoints[1].x - m_bezierPoints[0].x);
	bx = 3.0f * (m_bezierPoints[2].x - m_bezierPoints[1].x) - cx;
	ax = m_bezierPoints[3].x - m_bezierPoints[0].x - cx - bx;

	cy = 3.0f * (m_bezierPoints[1].y - m_bezierPoints[0].y);
	by = 3.0f * (m_bezierPoints[2].y - m_bezierPoints[1].y) - cy;
	ay = m_bezierPoints[3].y - m_bezierPoints[0].y - cy - by;

	// 매개변수 값 t에서 곡선 점을 계산
	tSquared = t * t;
	tCubed = tSquared * t;

	result.x = (ax * tCubed) + (bx * tSquared) + (cx * t) +
		m_bezierPoints[0].x;
	result.y = (ay * tCubed) + (by * tSquared) + (cy * t) +
		m_bezierPoints[0].y;

	return result;
}

float Bezier::GetYvalue(float _t) const
{
	float result;

	float ay, by, cy;
	float tSquared, tCubed;
	float t = Nalmak_Math::Clamp(_t, 0.f, 1.f);

	cy = 3.0f * (m_bezierPoints[1].y - m_bezierPoints[0].y);
	by = 3.0f * (m_bezierPoints[2].y - m_bezierPoints[1].y) - cy;
	ay = m_bezierPoints[3].y - m_bezierPoints[0].y - cy - by;

	// 매개변수 값 t에서 곡선 점을 계산
	tSquared = t * t;
	tCubed = tSquared * t;

	result = (ay * tCubed) + (by * tSquared) + (cy * t) +
		m_bezierPoints[0].y;

	return result;
}

