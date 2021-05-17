#include "Transform.h"
#include "RenderManager.h"
#include "SkinnedMeshRenderer.h"

USING(Nalmak)


Transform::Transform(Desc * _desc)
{
	position = _desc->position;
	rotation = _desc->rotation;
	scale = _desc->scale;
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

void Transform::PreRender()
{
	UpdateMatrix();
}

void Transform::Release()
{
	if (m_parents)
	{
		m_parents->DeleteChild(this);
		m_parents = nullptr;
	}
	if (m_boneParents)
	{
		m_boneParents = nullptr;
	}

	for (auto& child : m_childs)
	{
		child->m_parents = nullptr;
		child->m_boneParents = nullptr;
	}


}

void Transform::UpdateMatrix()
{
	Matrix matTrans, matRot, matScale;
	D3DXMatrixTranslation(&matTrans, position.x, position.y, position.z);
	D3DXMatrixRotationQuaternion(&matRot, &rotation);
	D3DXMatrixScaling(&matScale, scale.x, scale.y, scale.z);
	worldMatrix = matScale * matRot * matTrans;

	if (m_parents)
	{
		if (m_boneParents)
		{
			worldMatrix = worldMatrix * *m_boneParents * m_parents->GetWorldMatrix();
		}
		else
		{
			worldMatrix = worldMatrix * m_parents->GetNoneScaleWorldMatrix();
		}
	}
	
}



const Matrix & Transform::GetWorldMatrix()
{
	return worldMatrix;
}

Matrix Transform::GetWorldUIMatrix()
{
	Matrix uiMatrix;
	Matrix matTrans, matRot, matScale;

	float halfWincx = (float)m_renderManager->GetWindowWidth() * 0.5f;
	float halfWincy = (float)m_renderManager->GetWindowHeight() * 0.5f;
	Vector3 screenPos = { (position.x - halfWincx) / halfWincx, ( halfWincy - position.y) / halfWincy ,0 };

	D3DXMatrixTranslation(&matTrans, screenPos.x, screenPos.y, 0);
	D3DXMatrixRotationQuaternion(&matRot, &rotation);
	D3DXMatrixScaling(&matScale, scale.x / halfWincx, scale.y / halfWincy, 0);
	uiMatrix = matScale * matRot * matTrans;

	if (m_parents)
	{
		uiMatrix = uiMatrix * m_parents->GetUINoneScaleWorldMatrix();
	}
	return uiMatrix;
	
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

Matrix Transform::GetNoneScaleWorldMatrix()
{
	Matrix noneScaleWorld;
	Matrix matTrans, matRot;
	D3DXMatrixTranslation(&matTrans, position.x, position.y, position.z);
	D3DXMatrixRotationQuaternion(&matRot, &rotation);
	noneScaleWorld = matRot * matTrans;

	if (m_parents)
	{
		if (m_boneParents)
		{
			noneScaleWorld = noneScaleWorld * *m_boneParents * m_parents->GetNoneScaleWorldMatrix();
		}
		else
		{
			noneScaleWorld = noneScaleWorld * m_parents->GetNoneScaleWorldMatrix();
		}
	}

	return noneScaleWorld;
}

Matrix Transform::GetUINoneScaleWorldMatrix()
{
	float halfWincx = (float)m_renderManager->GetWindowWidth() * 0.5f;
	float halfWincy = (float)m_renderManager->GetWindowHeight() * 0.5f;
	Vector3 screenPos = { (position.x ) / halfWincx, ( - position.y) / halfWincy ,0 };


	Matrix noneScaleWorld;
	Matrix matTrans, matRot;
	D3DXMatrixTranslation(&matTrans, screenPos.x, screenPos.y, 0);
	D3DXMatrixRotationQuaternion(&matRot, &rotation);
	noneScaleWorld = matRot * matTrans;

	if (m_parents)
	{
		noneScaleWorld = noneScaleWorld * m_parents->GetNoneScaleWorldMatrix();
	}

	return noneScaleWorld;

}

Vector3 Transform::GetWorldPosition()
{
	return Vector3(worldMatrix._41, worldMatrix._42, worldMatrix._43);
}

Quaternion Transform::GetWorldRotation()
{
	if (m_parents)
	{
		if (m_boneParents)
		{
			Quaternion bone;
			D3DXQuaternionRotationMatrix(&bone, m_boneParents);
			return rotation  * bone * m_parents->GetWorldRotation();
		}
		else
		{
			return rotation * m_parents->GetWorldRotation();
		}
	}
	else
		return rotation;
}

Vector3 Transform::GetForward()
{
	Vector3 dir = Nalmak_Math::Normalize(Vector3(worldMatrix._31, worldMatrix._32, worldMatrix._33));
	return dir;

}

Vector3 Transform::GetRight()
{
	Vector3 dir = Nalmak_Math::Normalize(Vector3(worldMatrix._11, worldMatrix._12, worldMatrix._13));
	return dir;
}

Vector3 Transform::GetUp()
{
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

void Transform::LookAt_RotYAxis(const Vector3& _dir)
{
	auto dir = _dir;
	dir.y = 0;

	float angle = acosf(Nalmak_Math::Dot(dir, Vector3(0, 0, 1)));


	Quaternion rot;
	if (Nalmak_Math::Cross(dir, Vector3(0, 0, 1)).y > 0)
		D3DXQuaternionRotationYawPitchRoll(&rot, -angle, 0, 0);
	else
		D3DXQuaternionRotationYawPitchRoll(&rot, angle, 0, 0);

	m_transform->rotation = rot;
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

void Transform::SetParents(Transform * _parents, const string & _boneName)
{
	auto skin = _parents->GetComponent<SkinnedMeshRenderer>();
	assert("parents don't have bones" && skin);

	if (_parents == this)
		assert("parents are themselves" && 0);

	if (m_parents)
		m_parents->DeleteChild(this);

	m_parents = _parents;
	_parents->AddChild(this);

	m_boneParents = skin->GetBoneCombinedMatrix(_boneName);
}

void Transform::SetParents(Transform * _parents, Matrix * _bone)
{
	if(_parents == this)
		assert("parents are themselves" && 0);

	if (m_parents)
		m_parents->DeleteChild(this);

	m_parents = _parents;
	_parents->AddChild(this);

	m_boneParents = _bone;
}


void Transform::SetParents(Transform * _parents)
{
	assert("parents is nullptr" && _parents);
	if (_parents == this)
		assert("parents are themselves" && 0);
	if (m_boneParents)
		m_boneParents = nullptr;

	if (m_parents)
		m_parents->DeleteChild(this);


	m_parents = _parents;
	_parents->AddChild(this);
}

void Transform::SetParents(GameObject * _parents)
{
	Transform* parents = _parents->GetTransform();
	assert("parent is nullptr" && parents);
	assert("parents are themselves" && !(parents == this));
	if (m_boneParents)
		m_boneParents = nullptr;


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
		/*	_child->position = _child->GetWorldPosition();
			_child->rotation = _child->GetWorldRotation();*/
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
	m_boneParents = nullptr;
}

Transform * Transform::GetParents()
{
	return m_parents;
}

void Transform::SetTransform(Transform * _transform)
{
	m_transform = this;
}
