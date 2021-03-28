#pragma once
#ifndef __BEZIER_H__
#define __BEZIER_H__

#include "Nalmak_Include.h"

// Cubic Bezier Curve (3차)
// 4개의 점을 주고 Bezier 곡선을 만들고, 
// 그 중 GetBezierPoint함수를 통해 점4개로 만들어진 곡선에서 x비율(t)에 따라 해당하는 y값을 얻어옴 ( t  = [0 ~ 1] )
// SetPoint함수를 통해 시작점에서 끝점으로 이루어진 곡선을 만들 수 있음
class NALMAK_DLL Bezier
{
	/////////////////////////////////
	//                             // 
	//    (0,1) *-------* (1,1)	   //
	//          |       |		   //
	//          |	    |		   //
	//          |       |		   //
	//    (0,0) *-------* (1,0)	   //
	//							   //
	/////////////////////////////////
public:
	Bezier();
	explicit Bezier(const float& _x1, const float& _y1, const float& _x2, const float& _y2, const float& _x3, const float& _y3, const float& _x4, const float& _y4);
	explicit Bezier(const Vector2& _p1, const Vector2& _p2, const Vector2& _p3, const Vector2& _p4);
	~Bezier();
public:
	void SetInterpolationType(INTERPOLATION_TYPE _type);
	Vector2 GetPoint(float _t) const;
	float GetYvalue(float _t) const;

private:
	Vector2 m_bezierPoints[4]; // 베지어 곡선 점 (비율)
};

#endif // !__BEZIER_H__
