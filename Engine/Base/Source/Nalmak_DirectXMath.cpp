#include "Nalmak_DirectXMath.h"

namespace Vector
{
	const Vector3 Zero()
	{
		return Vector3();
	}

	const Vector3 Cross(const Vector3& _v1, const Vector3 & _v2)
	{
		if (_v1 == _v2)
			return Vector3(0, 0, 0);

		return Vector3(_v1.y * _v2.z - _v1.z * _v2.y,
			_v1.z * _v2.x - _v1.x * _v2.z,
			_v1.x * _v2.y - _v1.y * _v2.x);
	}

	const Vector2 Cross(float _a, const Vector2& _v1)
	{
		return Vector2(-_a * _v1.y, _a * _v1.x);
	}

	const Vector2 Cross(const Vector2& _v1, float _a)
	{
		return Vector2(-_a * _v1.y, _a * _v1.x);
	}

	const float Cross(const Vector2& _v1, const Vector2& _v2)
	{
		return _v1.x * _v2.y - _v1.y * _v2.x;
	}

	string ToString(const Vector3 _vec)
	{
		std::ostringstream oss;
		oss << "[" << std::setw(8) << _vec.x << " , " << std::setw(8) << _vec.y << " , " << std::setw(8) << _vec.z << "]";

		return oss.str();

	}

	string ToString(const Vector2 _vec)
	{
		std::ostringstream oss;
		oss << "[" << std::setw(8) << _vec.x << " , " << std::setw(8) << _vec.y << "]";

		return oss.str();
	}



	const float Dot(const Vector2& _v1, const Vector2& _v2)
	{
		return _v1.x * _v2.x + _v1.y * _v2.y;
	}

	const float Dot(const Vector3& _v1, const Vector3& _v2)
	{
		return _v1.x * _v2.x + _v1.y * _v2.y + _v1.z * _v2.z;
	}


	const float Magnitude(const Vector3 & _value)
	{
		return sqrtf(_value.x * _value.x + _value.y * _value.y + _value.z * _value.z);
	}

	Vector3 Normalize(const Vector3& _v)
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

	Vector2 Normalize(const Vector2& _v)
	{
		float vl = Length(_v);
		if (vl == 0)
			return Vector2(0, 0);

		Vector2 vec;
		vec.x = _v.x / vl;
		vec.y = _v.y / vl;

		return vec;
	}

	const Vector3 Direction(const Vector3& _v1, const Vector3& _v2)
	{
		Vector3 temp = _v2 - _v1;
		Vector3 dir = Vector::Normalize(temp);

		return dir;
	}

	const float Distance(const Vector3& _v1, const Vector3& _v2)
	{
		Vector3 value = _v1 - _v2;

		return Vector::Length(value);
	}

	const float Distance(const Vector2& _v1, const  Vector2& _v2)
	{
		Vector2 value = _v1 - _v2;

		return Vector::Length(value);
	}

	const float DistanceSq(const Vector3& _v1, const  Vector3& _v2)
	{
		Vector3 value = _v1 - _v2;

		return value.x * value.x + value.y * value.y + value.z * value.z;
	}

	const float DistanceSq(const Vector2& _v1, const  Vector2& _v2)
	{
		Vector2 value = _v1 - _v2;

		return value.x * value.x + value.y * value.y;
	}

	float Length(const Vector3& _v)
	{
		return sqrt(_v.x * _v.x + _v.y * _v.y + _v.z * _v.z);
	}

	float LengthSq(const Vector2& _v)
	{
		return (_v.x * _v.x + _v.y * _v.y);
	}

	float Length(const Vector2& _v)
	{
		return sqrt(_v.x * _v.x + _v.y * _v.y);
	}

	float LengthSq(const Vector3& _v)
	{
		return (_v.x * _v.x + _v.y * _v.y + _v.z * _v.z);
	}

}



//
//namespace Matrix
//{
//	const DirectX::XMFLOAT4X4 Matrix::Identity()
//	{
//		DirectX::XMFLOAT4X4 I(
//			1.0f, 0.0f, 0.0f, 0.0f,
//			0.0f, 1.0f, 0.0f, 0.0f,
//			0.0f, 0.0f, 1.0f, 0.0f,
//			0.0f, 0.0f, 0.0f, 1.0f);
//
//		return I;
//	}
//	const XMFLOAT4X4 ScailingMatrix(Vector3 _scale)
//	{
//		XMMATRIX v = XMMatrixScaling(_scale.x, _scale.y, _scale.z);
//
//		XMFLOAT4X4 result;
//		XMStoreFloat4x4(&result, v);
//
//		return result;
//	}
//	const XMFLOAT4X4 TransformMatrix(Vector3 _transform)
//	{
//		XMMATRIX v = XMMatrixTranslation(_transform.x, _transform.y, _transform.z);
//
//		XMFLOAT4X4 result;
//		XMStoreFloat4x4(&result, v);
//
//		return result;
//	}
//	const XMFLOAT4X4 RotationMatrix(XMFLOAT4 _quaternion)
//	{
//		XMMATRIX v = XMMatrixRotationQuaternion(XMVectorSet(_quaternion.x, _quaternion.y, _quaternion.z, _quaternion.w));
//
//		XMFLOAT4X4 result;
//		XMStoreFloat4x4(&result, v);
//
//		return result;
//	}
//}

//namespace Quaternion
//{
//	const XMQUATERNION Quaternion_Multiply_Quaternion(XMQUATERNION _q1, XMQUATERNION _q2)
//	{
//		XMMATRIX m1 = XMMatrixRotationQuaternion(_q1);
//		XMMATRIX m2 = XMMatrixRotationQuaternion(_q2);
//
//		XMMATRIX mResult = m1 * m2;
//
//		XMQUATERNION qResult = XMQuaternionRotationMatrix(mResult);
//
//		return qResult;
//	}
//
//	const XMQUATERNION GetQuaternionByRollPitchYawDegree(float _x, float _y, float _z)
//	{
//		XMQUATERNION result = XMQuaternionRotationRollPitchYaw(XM_PI / 180 * _x, XM_PI / 180 * _y, XM_PI / 180 * _z);
//		return result;
//	}
//	const XMQUATERNION GetQuaternionByRollPitchYawDegree(Vector3 _rot)
//	{
//		XMQUATERNION result = XMQuaternionRotationRollPitchYaw(XM_PI / 180 * _rot.x, XM_PI / 180 * _rot.y, XM_PI / 180 * _rot.z);
//		return result;
//	}
//}

