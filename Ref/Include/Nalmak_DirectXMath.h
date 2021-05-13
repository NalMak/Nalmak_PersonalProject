#pragma once


#ifndef __NALMAK_DIRECTXMATH_H__
#define __NALMAK_DIRECTXMATH_H__

#include "Nalmak_Include.h"


class Matrix3x3
{
public:
	Matrix3x3(float _e00, float _e01, float _e02,
		float _e10, float _e11, float _e12,
		float _e20, float _e21, float _e22)
		:x1(_e00), x2(_e01), x3(_e02), y1(_e10), y2(_e11), y3(_e12), z1(_e20), z2(_e21), z3(_e22) {}
	Matrix3x3()
	{
		x1 = 0, x2 = 0, x3 = 0;
		y1 = 0, y2 = 0, y3 = 0;
		z1 = 0, z2 = 0, z3 = 0;
	}
	~Matrix3x3() = default;
public:
	union
	{
		struct
		{
			float x1, x2, x3;
			float y1, y2, y3;
			float z1, z2, z3;
		};
		float e[3][3];
	};
	inline const static Matrix3x3 Identity()
	{
		return Matrix3x3(1, 0, 0, 0, 1, 0, 0, 0, 1);
	}
	inline const Matrix3x3& Transpose();

public:
	inline const Matrix3x3 operator*(const Matrix3x3& _dst)
	{
		Matrix3x3 temp;
		for (int i = 0; i < 3; ++i)
		{
			for (int j = 0; j < 3; ++j)
			{
				for (int k = 0; k < 3; k++)
					temp.e[i][j] += e[i][k] * _dst.e[k][j];
			}
		}
		return temp;
	}
};

class Matrix2x2
{
public:
	Matrix2x2(float _m00, float _m01, float _m10, float _m11) : m00(_m00), m01(_m01), m10(_m10), m11(_m11) {}
	Matrix2x2(float _angle)
	{
		float rad = _angle * Deg2Rad;

		float c = cos(rad);
		float s = sin(rad);

		m00 = c; m01 = -s;
		m10 = s; m11 = c;
	}
	Matrix2x2()
	{
		m00 = 1; m01 = 0;
		m10 = 0; m11 = 1;
	}
	~Matrix2x2() = default;
public:
	union
	{
		struct
		{
			float m00, m01;
			float m10, m11;

		};
		float v[2][2];
		float e[4];
	};

public:
	inline const static Matrix2x2 Identity()
	{
		return Matrix2x2(1, 0, 0, 1);
	}
	inline const Matrix2x2 Transpose() const
	{
		return Matrix2x2(m00, m10, m01, m11);
	}
	inline void  SetAngle(float _angle)
	{
		float rad = _angle * Deg2Rad;

		float c = cos(rad);
		float s = sin(rad);

		m00 = c; m01 = -s;
		m10 = s; m11 = c;
	}
public:
	inline const Matrix2x2 operator*(const Matrix2x2& _rhs) const
	{
		return Matrix2x2(
			v[0][0] * _rhs.v[0][0] + v[0][1] * _rhs.v[1][0],
			v[0][0] * _rhs.v[0][1] + v[0][1] * _rhs.v[1][1],
			v[1][0] * _rhs.v[0][0] + v[1][1] * _rhs.v[1][0],
			v[1][0] * _rhs.v[0][1] + v[1][1] * _rhs.v[1][1]
		);
	}
	inline Vector2 operator*(const Vector2& _rhs) const
	{
		return Vector2(m00 * _rhs.x + m01 * _rhs.y, m10 * _rhs.x + m11 * _rhs.y);
	}
};



namespace Vector
{
	const float Magnitude(const Vector3&);

	const float Dot(const Vector3&, const Vector3&);
	const float Dot(const Vector2&, const Vector2&);

	Vector3 Normalize(const Vector3&);
	Vector2 Normalize(const Vector2&);

	const Vector3 Direction(const Vector3&, const Vector3&);
	const float Distance(const Vector3&, const Vector3&);
	const float Distance(const Vector2&, const Vector2&);
	const float DistanceSq(const Vector3&, const Vector3&);
	const float DistanceSq(const Vector2&, const Vector2&);

	float Length(const Vector2&);
	float LengthSq(const Vector2&);
	float Length(const Vector3&);
	float LengthSq(const Vector3&);


	const Vector3 Cross(const Vector3&, const Vector3&);
	const Vector2 Cross(float _a, const Vector2&);
	const Vector2 Cross(const Vector2&, float _a);
	const float Cross(const Vector2&, const Vector2&);



	string ToString(const Vector3);
	string ToString(const Vector2);
}

typedef  XMVECTOR XMQUATERNION;


//namespace Quaternion
//{
//	const XMQUATERNION Quaternion_Multiply_Quaternion(XMQUATERNION _q1, XMQUATERNION _q2);
//	const XMQUATERNION GetQuaternionByRollPitchYawDegree(float _x, float _y, float _z);
//	const XMQUATERNION GetQuaternionByRollPitchYawDegree(Vector3 _rot);
//}

//namespace Matrix
//{
//	const XMFLOAT4X4 Identity();
//	const XMFLOAT4X4 ScailingMatrix(Vector3 _scale);
//	const XMFLOAT4X4 TransformMatrix(Vector3 _transform);
//	const XMFLOAT4X4 RotationMatrix(XMFLOAT4 _quaternion);
//}





#endif // !__NALMAK_DIRECTXMATH_H__
