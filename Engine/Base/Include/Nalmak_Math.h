#pragma once

#ifndef  __NALMAK_MATH_H__
#define __NALMAK_MATH_H__

#include "Nalmak_Include.h"

#define SMALL_NUM  0.00000001

struct Line
{
	Vector3 start, end;
};

class NALMAK_DLL Nalmak_Math
{
public:
	template<typename T>
	constexpr static T Lerp(T _src, T _dst, float _t)
	{
		return _src + _t * (_dst - _src);
	}

	inline static Vector3 SLerp(Vector3 _src, Vector3 _dst, float _t)
	{
		// 1. dot = _src * _dst.
		float dot = Nalmak_Math::Dot(_src, _dst);


		// 2.dot min max
		float curDot = Nalmak_Math::Clamp(dot, -1.0f, 1.0f);
		// 3. acos 세타 
		float theta = acosf(curDot) * _t; // 증감값
		// 4. end - start * dot
		Vector3 TemporyAxisDir = _dst - _src * curDot;

		// 5. num4 Normal
		Vector3 NormalizeDir = Nalmak_Math::Normalize(TemporyAxisDir);

		// _src * cosf(theta) + normal * sinf(theta);

		return (_src * cosf(theta)) + (NormalizeDir * sinf(theta));
	}

	inline static int Rand(const int _min, const int _max)
	{
		return _min + rand() % ((_max - _min) + 1);
	}
	inline static UINT Rand(const UINT _min, const UINT _max)
	{
		return _min + rand() % ((_max - _min) + 1);
	}
	inline static Vector2 Rand(const Vector2 _min, const Vector2 _max)
	{
		return Vector2(Rand(_min.x, _max.x), Rand(_min.y, _max.y));
	}
	inline static Vector3 Rand(const Vector3 _min, const Vector3 _max)
	{
		return Vector3(Rand(_min.x, _max.x), Rand(_min.y, _max.y), Rand(_min.z, _max.z));
	}
	inline static Vector4 Rand(const Vector4 _min, const Vector4 _max)
	{
		return Vector4(Rand(_min.x, _max.x), Rand(_min.y, _max.y), Rand(_min.z, _max.z),Rand(_min.w,_max.w));
	}
	inline static float Rand(const float _min, const float _max)
	{
		return _min + (float)(rand()) / (float)RAND_MAX * (_max - _min);
	}
	inline static Vector3 RandDirection()
	{
		return Nalmak_Math::Normalize(Vector3(Rand(-1.f, 1.f), Rand(-1.f, 1.f), Rand(-1.f, 1.f)));
	}
	inline static Vector3 RandColor()
	{
		return Vector3(Nalmak_Math::Rand(0.f, 1.f), Nalmak_Math::Rand(0.f, 1.f), Nalmak_Math::Rand(0.f, 1.f));
	}
	inline static bool Equal(const float& _a, const float& _b)
	{
		return abs(_a - _b) <= EPSILON;
	}
	inline static float Sqr(const float& _a)
	{
		return _a * _a;
	}
	template <typename T>
	static T GetRandom(int _count, T _arg)
	{
		return _arg;
	}
	template <typename T, typename... Arg>
	static T GetRandom(int _count, T _arg, Arg..._args)
	{
		if (_count == 0)
			return _arg;
		else
		{
			--_count;
			return GetRandom<T>(_count, _args...);
		}
	}
public:
	template <typename T, typename... Arg>
	static T Random(Arg..._args)
	{
		int count = sizeof...(Arg);

		return GetRandom<T>(rand() % count, _args...);
	}


	template<class T>
	constexpr static  const T& Clamp(const T& _v, const T& _min, const T& _max)
	{
		return (_v < _min) ? _min : (_max < _v) ? _max : _v;
	}


	
	static float GetDistance_LineToLine(Line& result,const Line& L1, const Line& L2)
	{
		Vector3   u = L1.end - L1.start;
		Vector3   v = L2.end - L2.start;
		Vector3   w = L1.start - L2.start;


		float    a = Nalmak_Math::Dot(u, u);        // 항상 >= 0
		float    b = Nalmak_Math::Dot(u, v);
		float    c = Nalmak_Math::Dot(v, v);          // 항상 >= 0
		float    d = Nalmak_Math::Dot(u, w);
		float    e = Nalmak_Math::Dot(v, w);
		float    D = a*c - b*b;       // 항상 >= 0
		float    sc, tc;

		// 이렇게 작은 값보다 작으면 거의 평행이라고 본다
		if (D < SMALL_NUM)
		{
			sc = 0.0;
			tc = (b > c ? d / b : e / c);   // 큰 값을 취함
		}
		else
		{
			sc = (b*e - c*d) / D;
			tc = (a*e - b*d) / D;
		}

		// 두 점 사이 크기    // = L1(sc) - L2(tc)
		Vector3   dP = w + (sc * u) - (tc * v);
		result.start = L1.start + (sc * u);
		result.end = L2.start + (tc * v);

		return sqrtf(Nalmak_Math::Dot(dP, dP));
	}

	static bool IsInPointInRect(const Vector2& _point, const Vector4& _rect)
	{
		if (_point.x >= _rect.x && _point.x <= _rect.z && _point.y >= _rect.y && _point.y <= _rect.w)
			return true;
		return false;
	}

	static float GetDistance_PointToInfinityLine(const Vector3& P1, const Line& L1)
	{
		Vector3 AB = L1.end - L1.start;
		Vector3 AP = P1 - L1.start;

		float area = Nalmak_Math::Magnitude(Nalmak_Math::Cross(AB, AP));
		float CD = area / Nalmak_Math::Magnitude(AB);

		return CD;
	}
	/*inline static bool GetInterSection2D_LineToLine(const Vector2& _p0, const Vector2& _p1,
	const Vector2& _q0, const Vector2& _q1)
	{
	float t;
	float s;
	const Vector2& AP1 = _p0;
	const Vector2& AP2 = _p1;
	const Vector2& BP1 = _q0;
	const Vector2& BP2 = _q1;

	float under = (BP2.y - BP1.y)*(AP2.x - AP1.x) - (BP2.x - BP1.x)*(AP2.y - AP1.y);
	if (under == 0)
	return false;

	float _t = (BP2.x - BP1.x)*(AP1.y - BP1.y) - (BP2.y - BP1.y)*(AP1.x - BP1.x);
	float _s = (AP2.x - AP1.x)*(AP1.y - BP1.y) - (AP2.y - AP1.y)*(AP1.x - BP1.x);

	t = _t / under;
	s = _s / under;

	if (t<0.0 || t>1.0 || s<0.0 || s>1.0)
	return false;

	return true;
	}*/
public:
	template<typename T>
	static const int Sign(const T& _v)
	{
		return (_v > 0) - (_v < 0);
	}


	static const float Magnitude(const Vector3& _value)
	{
		return sqrtf(_value.x * _value.x + _value.y * _value.y + _value.z * _value.z);
	}

	static const float Dot(const Vector3& _v1, const Vector3& _v2)
	{
		return _v1.x * _v2.x + _v1.y * _v2.y + _v1.z * _v2.z;
	}
	static const float Dot(const Vector2& _v1, const Vector2& _v2)
	{
		return _v1.x * _v2.x + _v1.y * _v2.y;
	}

	static Quaternion Normalize(const Quaternion& _v)
	{
		float vl = Length(_v);
		if (vl == 0)
			return Quaternion(0, 0, 0, 1);

		Quaternion vec;
		vec.x = _v.x / vl;
		vec.y = _v.y / vl;
		vec.z = _v.z / vl;
		vec.w = _v.w / vl;

		return vec;
	}

	static Vector3 Normalize(const Vector3& _v)
	{
		float vl = Length(_v);
		if (vl == 0)
			return Vector3(0, 0, 0);

		Vector3 vec;
		vec.x = _v.x / vl;
		vec.y = _v.y / vl;
		vec.z = _v.z / vl;

		return vec;
	}
	static Vector2 Normalize(const Vector2& _v)
	{
		float vl = Length(_v);
		if (vl == 0)
			return Vector2(0, 0);

		Vector2 vec;
		vec.x = _v.x / vl;
		vec.y = _v.y / vl;

		return vec;
	}

	static const Vector3 Direction(const Vector3& _v1, const Vector3& _v2)
	{
		Vector3 temp = _v2 - _v1;
		Vector3 dir = Nalmak_Math::Normalize(temp);

		return dir;
	}
	static const float Distance(const Vector3& _v1, const Vector3& _v2)
	{
		Vector3 value = _v1 - _v2;

		return Nalmak_Math::Length(value);
	}
	static const float Distance(const Vector2& _v1, const Vector2& _v2)
	{
		Vector2 value = _v1 - _v2;

		return Nalmak_Math::Length(value);
	}
	static const float DistanceSq(const Vector3& _v1, const Vector3& _v2)
	{
		Vector3 value = _v1 - _v2;

		return value.x * value.x + value.y * value.y + value.z * value.z;
	}
	static const float DistanceSq(const Vector2& _v1, const Vector2& _v2)
	{
		Vector2 value = _v1 - _v2;

		return value.x * value.x + value.y * value.y;
	}

	static float Length(const Vector2& _v)
	{
		return sqrt(_v.x * _v.x + _v.y * _v.y);

	}
	static float LengthSq(const Vector2& _v)
	{
		return (_v.x * _v.x + _v.y * _v.y);
	}
	static float Length(const Vector3& _v)
	{
		return sqrt(_v.x * _v.x + _v.y * _v.y + _v.z * _v.z);
	}
	static float LengthSq(const Vector3& _v)
	{
		return (_v.x * _v.x + _v.y * _v.y + _v.z * _v.z);
	}
	static float Length(const Quaternion& _v)
	{
		return sqrt(_v.x * _v.x + _v.y * _v.y + _v.z * _v.z + _v.w * + _v.w);
	}

	static const Vector3 Cross(const Vector3& _v1, const Vector3& _v2)
	{
		if (_v1 == _v2)
			return Vector3(0, 0, 0);

		return Vector3(_v1.y * _v2.z - _v1.z * _v2.y,
			_v1.z * _v2.x - _v1.x * _v2.z,
			_v1.x * _v2.y - _v1.y * _v2.x);
	}
	static const Vector2 Cross(float _a, const Vector2& _v1)
	{
		return Vector2(-_a * _v1.y, _a * _v1.x);
	}
	static const Vector2 Cross(const Vector2& _v1, float _a)
	{
		return Vector2(-_a * _v1.y, _a * _v1.x);
	}
	static const float Cross(const Vector2& _v1, const Vector2& _v2)
	{
		return _v1.x * _v2.y - _v1.y * _v2.x;
	}
	
	static const void GetMatrixRotateAtoB(Matrix* _out, const Vector3& _v1, const Vector3& _v2)
	{
		Vector3 d1 = Nalmak_Math::Normalize(_v1);
		Vector3 d2 = Nalmak_Math::Normalize(_v2);

		float angle = Nalmak_Math::Dot(d1, d2);

		Vector3 axis;
		D3DXVec3Cross(&axis, &d1, &d2);
		D3DXMatrixRotationAxis(_out, &axis, acos(angle));

	}

	static const void GetMatrixRotateACoordtoBCoord(Matrix* _out,
		const Vector3& _rightA, const Vector3& _upA, const Vector3& _lookA,
		const Vector3& _rightB, const Vector3& _upB, const Vector3& _lookB)
	{
		Matrix A, B;
		ZeroMemory(_out, sizeof(Matrix));
		ZeroMemory(&A, sizeof(Matrix));
		ZeroMemory(&B, sizeof(Matrix));

		memcpy(&A._11, &_rightA, sizeof(Vector3));
		memcpy(&A._21, &_upA, sizeof(Vector3));
		memcpy(&A._31, &_lookA, sizeof(Vector3));

		memcpy(&B._11, &_rightB, sizeof(Vector3));
		memcpy(&B._21, &_upB, sizeof(Vector3));
		memcpy(&B._31, &_lookB, sizeof(Vector3));

		D3DXMatrixTranspose(&A, &A);

		_out->_44 = 1;

		*_out = A * B;
	}

	static const Vector3 QuaternionToEuler(Quaternion _q)
	{
		double roll, pitch, yaw;

		// roll (x-axis rotation)
		double sinR_cosP = 2 * (_q.w * _q.x + _q.y * _q.z);
		double cosR_cosP = 1 - 2 * (_q.x * _q.x + _q.y * _q.y);
		roll = atan2(sinR_cosP, cosR_cosP);

		// pitch (y-axis rotation)
		double sinP = 2 * (_q.w * _q.y - _q.z * _q.x);
		if (std::abs(sinP) >= 1)
			pitch = copysign(D3DX_PI * 0.5f, sinP);	// use 90 degrees if out of range
		else
			pitch = asin(sinP);

		// yaw (z-axis rotation)
		double sinY_cosP = 2 * (_q.w * _q.z + _q.x * _q.y);
		double cosY_cosP = 1 - 2 * (_q.y * _q.y + _q.z * _q.z);
		yaw = atan2(sinY_cosP, cosY_cosP);

		return Vector3((FLOAT)roll * Rad2Deg, (FLOAT)pitch* Rad2Deg, (FLOAT)yaw* Rad2Deg);
	}




	static const bool IsIntersectTriangle(
		const Vector3&  _rayPoint,
		const Vector3&  _rayDirection, 
		const Vector3& v0, 
		const Vector3& v1, 
		const Vector3& v2,
		Vector3* _point) 
	{
		Vector3 e1, e2, h, s, q;

		float a, f, u, v, t;
		e1 = v1 - v0;
		e2 = v2 - v0;
		h = Nalmak_Math::Cross(_rayDirection, e2);
		a = Nalmak_Math::Dot(e1, h);

		if (a > -0.00001 && a < 0.00001)
			return false;

		f = 1 / a;
		s = _rayPoint - v0;
		u = f *  Nalmak_Math::Dot(s, h);

		if (u < 0.0 || u > 1.0)
			return false;
		q = Nalmak_Math::Cross(s, e1);
		v = f * Nalmak_Math::Dot(_rayDirection, q);
		if (v < 0.0 || u + v > 1.0) 
			return false;

		// at this stage we can compute t to find out where 
		// the intersection point is on the line
		t = f * Nalmak_Math::Dot(e2, q);
		if (t > 0.00001) // ray intersection
		{
			*_point = _rayPoint + _rayDirection* t;
			return true;
		}
		else // this means that there is line intersection but not ray intersection
			return false;
	}

	static const bool IsIntersectLineToLineOn2D(const Vector3& _p0, const Vector3& _p1, const Vector3& _q0, const Vector3& _q1)
	{
		float t;
		float s;
		Vector2 AP1 = { _p0.x,_p0.z};
		Vector2 AP2 = { _p1.x,_p1.z };
		Vector2 BP1 = { _q0.x,_q0.z };
		Vector2 BP2 = { _q1.x,_q1.z };

		float under = (BP2.y - BP1.y)*(AP2.x - AP1.x) - (BP2.x - BP1.x)*(AP2.y - AP1.y);
		if (under == 0)
			return false;

		float _t = (BP2.x - BP1.x)*(AP1.y - BP1.y) - (BP2.y - BP1.y)*(AP1.x - BP1.x);
		t = _t / under;

		if (t <= 0.0 || t >= 1.0)
			return false;
		float _s = (AP2.x - AP1.x)*(AP1.y - BP1.y) - (AP2.y - AP1.y)*(AP1.x - BP1.x);
		s = _s / under;

		if (s <= 0.0 || s >= 1.0)
			return false;

		return true;
	}
	
	static const bool IsExistPointInTriangleInOn2D(Vector3 _point, Vector3 _p1, Vector3 _p2, Vector3 _p3)
	{
		Vector2 p, p1, p2, p3;
		p = { _point.x,_point.z };
		p1 = {_p1.x,_p1.z};
		p2 = {_p2.x,_p2.z};
		p3 = {_p3.x,_p3.z};

		float alpha = ((p2.y - p3.y)*(p.x - p3.x) + (p3.x - p2.x)*(p.y - p3.y)) /
			((p2.y - p3.y)*(p1.x - p3.x) + (p3.x - p2.x)*(p1.y - p3.y));
		float beta = ((p3.y - p1.y)*(p.x - p3.x) + (p1.x - p3.x)*(p.y - p3.y)) /
			((p2.y - p3.y)*(p1.x - p3.x) + (p3.x - p2.x)*(p1.y - p3.y));
		float gamma = 1.0f - alpha - beta;

		if (alpha > 0 && beta > 0 && gamma > 0)
			return true;
		else
			return false;
	}
};


#endif // ! __NALMAK_MATH_H__

