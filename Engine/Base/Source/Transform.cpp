#include "Transform.h"
#include "RenderManager.h"

USING(Nalmak)


Transform::Transform(Desc * _desc)
{
	fixRotationX = false;
	fixRotationY = false;
	fixRotationZ = false;
}


Transform::~Transform()
{

}

void Transform::Initialize()
{
	m_renderManager = RenderManager::GetInstance();

	D3DXMatrixIdentity(&worldMatrix);
	UpdateMatrix();
}

void Transform::Update()
{
}

void Transform::LateUpdate()
{
}

void Transform::Release()
{
	if (m_parents)
	{
		m_parents = nullptr;
	}


	for (auto& child : m_childs)
	{
		child->m_parents = nullptr;
	}
}

void Transform::UpdateMatrix()
{
	{
		//Matrix matTrans, matRot, matScale;
		//D3DXMatrixTranslation(&matTrans, position.x, position.y, position.z);
		//D3DXMatrixRotationQuaternion(&matRot, &rotation);
		//D3DXMatrixScaling(&matScale, scale.x, scale.y, scale.z);

		//if (m_parents)
		//	worldMatrix = matScale * matRot * matTrans * m_parents->GetNoneScaleWorldMatrix();
		//else
		//	worldMatrix = matScale * matRot * matTrans;
		//
	}

	Vector3 right = { 1.f,0.f,0.f };
	Vector3 up = { 0.f,1.f,0.f };
	Vector3 look = { 0.f,0.f,1.f };


	/* scale */
	right.x *= scale.x;
	up.y *= scale.y;
	look.z *= scale.z;

	/* rotate */
	GetRotationX(&right, right);
	GetRotationY(&right, right);
	GetRotationZ(&right, right);

	GetRotationX(&up, up);
	GetRotationY(&up, up);
	GetRotationZ(&up, up);

	GetRotationX(&look, look);
	GetRotationY(&look, look);
	GetRotationZ(&look, look);

	D3DXMatrixIdentity(&worldMatrix);
	memcpy(&worldMatrix.m[0][0], &right, sizeof(Vector3));
	memcpy(&worldMatrix.m[1][0], &up, sizeof(Vector3));
	memcpy(&worldMatrix.m[2][0], &look, sizeof(Vector3));
	memcpy(&worldMatrix.m[3][0], &position, sizeof(Vector3));

	if (m_parents)
		worldMatrix = worldMatrix * m_parents->GetNoneScaleWorldMatrix();
}

void Transform::UpdateUIMatrix()
{
	float wincx = (float)m_renderManager->GetWindowWidth();
	float wincy = (float)m_renderManager->GetWindowHeight();
	float halfWincx = wincx * 0.5f;
	float halfWincy = wincy * 0.5f;

	Vector3 correctScale = { scale.x / halfWincx, scale.y / halfWincy, scale.z };

	Vector3 right = { 1.f,0.f,0.f };
	Vector3 up = { 0.f,1.f,0.f };
	Vector3 look = { 0.f,0.f,1.f };

	/* scale */
	right.x *= correctScale.x;
	up.y *= correctScale.y;
	look.z *= correctScale.z;

	/* rotate */
	GetRotationX(&right, right);
	GetRotationY(&right, right);
	GetRotationZ(&right, right);

	GetRotationX(&up, up);
	GetRotationY(&up, up);
	GetRotationZ(&up, up);

	GetRotationX(&look, look);
	GetRotationY(&look, look);
	GetRotationZ(&look, look);

	D3DXMatrixIdentity(&worldMatrix);
	memcpy(&worldMatrix.m[0][0], &right, sizeof(Vector3));
	memcpy(&worldMatrix.m[1][0], &up, sizeof(Vector3));
	memcpy(&worldMatrix.m[2][0], &look, sizeof(Vector3));
	memcpy(&worldMatrix.m[3][0], &position, sizeof(Vector3));

	if (m_parents)
		worldMatrix = worldMatrix * m_parents->GetUINoneScaleWorldMatrix();


	// position translate (0,0 ~ wincx, wincy) -> (-1,1 ~ 1,-1)

	Vector3 correctPos = {
		(worldMatrix.m[3][0] - halfWincx) / halfWincx,
		(halfWincy - worldMatrix.m[3][1]) / halfWincy,
		worldMatrix.m[3][2] };

	memcpy(&worldMatrix.m[3][0], &correctPos, sizeof(Vector3));
}

const Matrix & Transform::GetWorldMatrix()
{
	//if (!m_gameObject->IsStatic())
	//	UpdateMatrix();
	return worldMatrix;
}

const Matrix & Transform::GetUIWorldMatrix()
{
	if (!m_gameObject->IsStatic())
		UpdateUIMatrix();

	return worldMatrix;
}

void Transform::GetRotationX(Vector3 * _out, Vector3 _in)
{
	// roll (x-axis rotation)
	double sinR_cosP = 2 * (rotation.w * rotation.x + rotation.y * rotation.z);
	double cosR_cosP = 1 - 2 * (rotation.x * rotation.x + rotation.y * rotation.y);
	float radian = (float)atan2(sinR_cosP, cosR_cosP);

	/*
	1	0	0	0
	0	c	s	0
	0	-s	c	0
	0	0	0	1
	*/

	_out->y = _in.y * cosf(radian) - _in.z * sinf(radian);
	_out->z = _in.y * sinf(radian) + _in.z * cosf(radian);
}

void Transform::GetRotationY(Vector3 * _out, Vector3 _in)
{
	// pitch (y-axis rotation)
	double sinP = 2 * (rotation.w * rotation.y - rotation.z * rotation.x);
	float radian = 0.f;
	if (std::abs(sinP) >= 1)
		radian = (float)copysign(D3DX_PI * 0.5f, sinP);	// use 90 degrees if out of range
	else
		radian = (float)asin(sinP);

	/*
	c	0	-s	0
	0	1	0	0
	s	0	c	0
	0	0	0	1
	*/


	_out->x = _in.x * cosf(radian) + _in.z * sinf(radian);
	_out->z = _in.x * -sinf(radian) + _in.z * cosf(radian);
}

void Transform::GetRotationZ(Vector3 * _out, Vector3 _in)
{
	// yaw (z-axis rotation)
	double sinY_cosP = 2 * (rotation.w * rotation.z + rotation.x * rotation.y);
	double cosY_cosP = 1 - 2 * (rotation.y * rotation.y + rotation.z * rotation.z);
	float radian = (float)atan2(sinY_cosP, cosY_cosP);

	/*
	c	s	0	0
	-s	c	0	0
	0	0	1	0
	0	0	0	1
	*/


	_out->x = _in.x * cosf(radian) - _in.y * sinf(radian);
	_out->y = _in.x * sinf(radian) + _in.y * cosf(radian);
}

const Matrix & Transform::GetNoneScaleWorldMatrix()
{
	D3DXMatrixIdentity(&noneScaleWorldMatrix);

	Vector3 right = { 1.f,0.f,0.f };
	Vector3 up = { 0.f,1.f,0.f };
	Vector3 look = { 0.f,0.f,1.f };


	/* rotate */
	GetRotationX(&right, right);
	GetRotationY(&right, right);
	GetRotationZ(&right, right);

	GetRotationX(&up, up);
	GetRotationY(&up, up);
	GetRotationZ(&up, up);

	GetRotationX(&look, look);
	GetRotationY(&look, look);
	GetRotationZ(&look, look);

	memcpy(&noneScaleWorldMatrix.m[0][0], &right, sizeof(Vector3));
	memcpy(&noneScaleWorldMatrix.m[1][0], &up, sizeof(Vector3));
	memcpy(&noneScaleWorldMatrix.m[2][0], &look, sizeof(Vector3));
	memcpy(&noneScaleWorldMatrix.m[3][0], &position, sizeof(Vector3));


	if (m_parents)
		noneScaleWorldMatrix = noneScaleWorldMatrix * m_parents->GetNoneScaleWorldMatrix();

	return noneScaleWorldMatrix;
}

const Matrix & Transform::GetUINoneScaleWorldMatrix()
{
	D3DXMatrixIdentity(&noneScaleWorldMatrix);

	Vector3 right = { 1.f,0.f,0.f };
	Vector3 up = { 0.f,1.f,0.f };
	Vector3 look = { 0.f,0.f,1.f };


	/* rotate */
	GetRotationX(&right, right);
	GetRotationY(&right, right);
	GetRotationZ(&right, right);

	GetRotationX(&up, up);
	GetRotationY(&up, up);
	GetRotationZ(&up, up);

	GetRotationX(&look, look);
	GetRotationY(&look, look);
	GetRotationZ(&look, look);

	memcpy(&noneScaleWorldMatrix.m[0][0], &right, sizeof(Vector3));
	memcpy(&noneScaleWorldMatrix.m[1][0], &up, sizeof(Vector3));
	memcpy(&noneScaleWorldMatrix.m[2][0], &look, sizeof(Vector3));
	memcpy(&noneScaleWorldMatrix.m[3][0], &position, sizeof(Vector3));


	if (m_parents)
		noneScaleWorldMatrix = noneScaleWorldMatrix * m_parents->GetUINoneScaleWorldMatrix();

	return noneScaleWorldMatrix;
}

Vector3 Transform::GetWorldPosition()
{
	if (!m_gameObject->IsStatic())
		UpdateMatrix();

	return Vector3(worldMatrix._41, worldMatrix._42, worldMatrix._43);
}

Quaternion Transform::GetWorldRotation()
{
	if (m_parents)
		return rotation * m_parents->GetWorldRotation();
	else
		return rotation;
}

Vector3 Transform::GetForward()
{
	if (!m_gameObject->IsStatic())
		UpdateMatrix();
	Vector3 dir = Nalmak_Math::Normalize(Vector3(worldMatrix._31, worldMatrix._32, worldMatrix._33));
	return dir;

}

Vector3 Transform::GetRight()
{
	if (!m_gameObject->IsStatic())
		UpdateMatrix();
	Vector3 dir = Nalmak_Math::Normalize(Vector3(worldMatrix._11, worldMatrix._12, worldMatrix._13));
	return dir;
}

Vector3 Transform::GetUp()
{
	if (!m_gameObject->IsStatic())
		UpdateMatrix();
	Vector3 dir = Nalmak_Math::Normalize(Vector3(worldMatrix._21, worldMatrix._22, worldMatrix._23));
	return dir;
}


void Transform::SetRotation(float _ex, float _ey, float _ez)
{
	D3DXQuaternionRotationYawPitchRoll(&rotation, Deg2Rad *_ey, Deg2Rad * _ex, Deg2Rad * _ez);

	//D3DXQuaternionIdentity(&rotation);
	//RotateX(_ex);
	//RotateY(_ey);
	//RotateZ(_ez);
}

void Transform::SetRotationX(float _ex)
{
	Vector3 CurrentAngle = Nalmak_Math::QuaternionToEuler(rotation);
	RotateX(-CurrentAngle.x);
	RotateX(_ex);
}

void Transform::SetRotationY(float _ey)
{
	Vector3 CurrentAngle = Nalmak_Math::QuaternionToEuler(rotation);
	RotateY(-CurrentAngle.y);
	RotateY(_ey);
}

void Transform::SetRotationZ(float _ez)
{
	Vector3 CurrentAngle = Nalmak_Math::QuaternionToEuler(rotation);
	RotateZ(-CurrentAngle.z);
	RotateZ(_ez);
}

void Transform::RotateX(float _ex)
{
	Quaternion rot;
	D3DXQuaternionIdentity(&rot);
	D3DXQuaternionRotationAxis(&rot, &Vector3(1.f, 0.f, 0.f), Deg2Rad * _ex); // radian

	rotation *= rot;
}

void Transform::RotateY(float _ey)
{
	//D3DXQuaternionRotationAxis(&rotation, &GetUp(), _ey);
	Quaternion rot;
	D3DXQuaternionIdentity(&rot);
	D3DXQuaternionRotationAxis(&rot, &Vector3(0.f, 1.f, 0.f), Deg2Rad * _ey); // radian

	rotation *= rot;

}

void Transform::RotateZ(float _ez)
{
	//D3DXQuaternionRotationAxis(&rotation, &GetForward(), _ez);
	Quaternion rot;
	D3DXQuaternionIdentity(&rot);
	D3DXQuaternionRotationAxis(&rot, &Vector3(0.f, 0.f, 1.f), Deg2Rad * _ez); // radian

	rotation *= rot;
}


Vector3 Transform::GetEulerRotation()
{
	return Nalmak_Math::QuaternionToEuler(rotation);
}

void Transform::RotateRollPitchYaw(float _x, float _y, float _z)
{
	Quaternion rot;
	D3DXQuaternionRotationYawPitchRoll(&rot, _y, _x, _z);
	m_transform->rotation *= rot;
}

void Transform::RotateAxis(const Vector3 & _axis, float _angle)
{
	Quaternion rot;
	D3DXQuaternionRotationAxis(&rot, &_axis, _angle);
	m_transform->rotation *= rot;
}

void Transform::ResetRelative()
{
	m_parents = nullptr;
	m_childs.clear();
}

void Transform::LookAt(GameObject * _Target, float _Spd, Quaternion * _qOut)
{
	Vector3 vDir = _Target->GetTransform()->position - m_transform->position;
	D3DXVec3Normalize(&vDir, &vDir);

	Vector3 look = m_transform->GetForward();

	if (Nalmak_Math::Dot(vDir, look) > 0.999f)
	{
		return;
	}

	Vector3 vAxis = { 0.f, 0.f, 0.f };
	D3DXVec3Cross(&vAxis, &look, &vDir);
	D3DXVec3Normalize(&vAxis, &vAxis);

	RotateAxis(vAxis, dTime*_Spd);

	
}

void Transform::LookAt(const Vector3& _pos, float _Spd, Quaternion * _qOut)
{
	Vector3 vDir = _pos - m_transform->position;
	D3DXVec3Normalize(&vDir, &vDir);

	Vector3 look = m_transform->GetForward();
	if (Nalmak_Math::Dot(vDir, look) > 0.999f)
	{
		return;
	}

	Vector3 vAxis = { 0.f, 0.f, 0.f };
	D3DXVec3Cross(&vAxis, &look, &vDir);
	D3DXVec3Normalize(&vAxis, &vAxis);

	RotateAxis(vAxis, dTime*_Spd);
	
}

void Transform::LookAt(const Vector3 & _dest, Quaternion * _qOut)
{
	Vector3 vDir = _dest - m_transform->position;
	D3DXVec3Normalize(&vDir, &vDir);

	Vector3 look = m_transform->GetForward();
	float fDot = Nalmak_Math::Dot(vDir, look);
	if (fDot > 0.999f)
	{
		return;
	}

	Vector3 vAxis = { 0.f, 0.f, 0.f };
	D3DXVec3Cross(&vAxis, &look, &vDir);
	D3DXVec3Normalize(&vAxis, &vAxis);

	RotateAxis(vAxis, acosf(fDot));

	
}








Transform * Transform::GetChild(int _index)
{
	int i = 0;
	for (auto iter = m_childs.begin(); iter != m_childs.end(); ++iter, ++i)
	{
		if (i == _index)
			return *iter;
	}

	return nullptr;
}

size_t Transform::GetChildCount()
{
	return m_childs.size();
}


void Transform::SetParents(Transform * _parents)
{
	assert("parents is nullptr" && _parents);
	assert("parents are themselves" && !(_parents == this));

	if (m_parents)
		m_parents->DeleteChild(this);

	Matrix childMat;
	D3DXMatrixInverse(&childMat, nullptr, &_parents->GetWorldMatrix());
	childMat = GetWorldMatrix() * childMat;

	m_transform->position = Vector3(childMat._41, childMat._42, childMat._43);
	D3DXQuaternionRotationMatrix(&m_transform->rotation, &childMat);

	m_parents = _parents;
	_parents->AddChild(this);
}

void Transform::SetParents(GameObject * _parents)
{
	Transform* parents = _parents->GetTransform();
	assert("parent is nullptr" && parents);
	assert("parents are themselves" && !(parents == this));

	if (m_parents)
		m_parents->DeleteChild(this);

	/*Matrix childMat;
	D3DXMatrixInverse(&childMat, nullptr, &parents->GetWorldMatrix());
	childMat = GetWorldMatrix() * childMat;

	m_transform->position = Vector3(childMat._41, childMat._42, childMat._43);
	D3DXQuaternionRotationMatrix(&m_transform->rotation, &childMat);*/

	m_parents = _parents->GetTransform();
	_parents->GetTransform()->AddChild(this);
}

void Transform::AddChild(Transform * _child)
{
	m_childs.emplace_back(_child);
}

void Transform::DeleteChild(Transform * _child)
{
	for (auto iter = m_childs.begin(); iter != m_childs.end(); ++iter)
	{
		if ((*iter) == _child)
		{
			_child->position = _child->GetWorldPosition();
			_child->rotation = _child->GetWorldRotation();
			m_childs.erase(iter);
			return;
		}
	}
}

void Transform::DeleteParent()
{
	if (!m_parents)
		return;
	m_parents->DeleteChild(this);

	m_parents = nullptr;
}

Transform * Transform::GetParents()
{
	return m_parents;
}

void Transform::SetTransform(Transform * _transform)
{
	m_transform = this;
}
