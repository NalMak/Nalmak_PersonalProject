#include "Camera.h"
#include "Transform.h"
#include "ResourceManager.h"
#include "IRenderer.h"
#include "DepthStencil.h"
#include "CanvasRenderer.h"

#include "MeshRenderer.h"
USING(Nalmak)

Camera::Camera(Desc * _desc)
{
	m_fovY = _desc->fovY;
	
	m_zNear = _desc->zNear;
	m_zFar = _desc->zFar;
	m_mode = _desc->mode;
	
	
	if (_desc->width == 0)
		m_width = (float)RenderManager::GetInstance()->GetWindowWidth();
	else
		m_width = (float)_desc->width;
	if(_desc->height == 0)
		m_height = (float)RenderManager::GetInstance()->GetWindowHeight();
	else
		m_height = (float)_desc->height;
	
	if (_desc->aspect == 0)
		m_aspect = m_width / m_height;
	else
		m_aspect = _desc->aspect;
	m_renderingMode = _desc->renderMode;
	if (m_renderingMode == CAMERA_RENDERING_MODE_DEFERRED)
	{
			
	}

	RenderManager::GetInstance()->AddCamera(this);
	
	UpdateProjMatrix();
}

void Camera::Initialize()
{
	//UpdateProjMatrix();
	
	m_handle = DeviceManager::GetInstance()->GetHWND();
}

void Camera::Update()
{
	//UpdateProjMatrix();
}

void Camera::LateUpdate()
{
}

void Camera::Release()
{
	RenderManager::GetInstance()->DeleteCamera(this);
}

void Camera::PreRender()
{
	UpdateViewMatrix();
	UpdateFrustumPlane();
}

void Camera::UpdateViewMatrix()
{
	Vector3 worldPos = m_transform->GetWorldPosition();
	if (m_mode == CAMERA_PROJECTION_MODE_PERSPECTIVE)
	{
		Quaternion rot = m_transform->GetWorldRotation();
		Matrix rotMatrix;
		D3DXMatrixRotationQuaternion(&rotMatrix, &rot);
		Vector3 eye = worldPos;
		Vector3 at = Vector3(0, 0, 1);
		D3DXVec3TransformCoord(&at, &at, &rotMatrix);
		at += worldPos;
		Vector3 up = Vector3(0, 1, 0);
		D3DXVec3TransformCoord(&up, &up, &rotMatrix);

		/*	Vector3 eye = worldPos;
		Vector3 at = worldPos + Vector3(0, 0, 1);
		Vector3 up = Vector3(0, 1, 0);*/

		D3DXMatrixLookAtLH(&m_viewMatrix, &eye, &at, &up);
	}
	else if (m_mode == CAMERA_PROJECTION_MODE_ORTHOGRAPHIC)
	{
		Vector3 eye = worldPos;
		Vector3 at = worldPos + Vector3(0, 0, 1);
		Vector3 up = Vector3(0, 1, 0);

		D3DXMatrixLookAtLH(&m_viewMatrix, &eye, &at, &up);
	}
}

const Matrix Camera::GetViewMatrix() const
{
	return m_viewMatrix;
}

const Matrix Camera::GetViewportMatrix() const
{
	float halfWincx = RenderManager::GetInstance()->GetWindowWidth() * 0.5f;
	float halfWincy = RenderManager::GetInstance()->GetWindowHeight() * 0.5f;

	return Matrix
	{
		halfWincx, 0.f        , 0.f             , 0.f,
		0.f       , -halfWincy, 0.f             , 0.f,
		0.f       , 0.f        , m_zFar - m_zNear, 0.f,
		halfWincx, halfWincy , m_zNear         , 1.f
	};
}

Vector2 Camera::WorldToScreenPos(const Vector3 & _pos)
{
	float halfWincx = RenderManager::GetInstance()->GetWindowWidth() * 0.5f;
	float halfWincy = RenderManager::GetInstance()->GetWindowHeight() * 0.5f;

	Vector3 temp;
	D3DXVec3TransformCoord(&temp, &_pos, &GetViewMatrix());
	D3DXVec3TransformCoord(&temp, &temp, &GetProjMatrix());
	D3DXVec3TransformCoord(&temp, &temp, &GetViewportMatrix());

	return Vector2(temp.x , temp.y);
}

Vector3 Camera::ScreenPosToWorld(const Vector2 & _screenPos, float Distance_FromCam)
{
	float wincx = (float)RenderManager::GetInstance()->GetWindowWidth();
	float wincy = (float)RenderManager::GetInstance()->GetWindowHeight();

	Vector2 screenPos = _screenPos;

	Vector3 ViewSpace;
	Vector3 WorldSpace;
	Matrix invView;
	ViewSpace.x = (((2.0f * screenPos.x) / wincx) - 1.0f) / GetProjMatrix()._11;
	ViewSpace.y = (((-2.0f * screenPos.y) / wincy) + 1.0f) / GetProjMatrix()._22;
	ViewSpace.z = 1.0f;

	D3DXMatrixInverse(&invView, 0, &GetViewMatrix());

	D3DXVec3TransformCoord(&WorldSpace, &ViewSpace, &invView);
	
	//D3DXVec3Normalize(&WorldSpace, &WorldSpace);
	//Vector3 Result_World = m_transform->position + WorldSpace * Distance_FromCam;
	//return Result_World;

	return WorldSpace;
}



bool Camera::IsInFrustumCulling(IRenderer * _renderer)
{
	FRUSTUM_CULLING_STATE state = _renderer->GetFrustumCullingState();
	switch (state)
	{
	case FRUSTUM_CULLING_STATE_FREE_PASS:
		return true;
	case FRUSTUM_CULLING_STATE_SUCCESS:
		return true;
	case FRUSTUM_CULLING_STATE_FAIL:
		return false;
	default:
		break;
	}

	RENDERER_TYPE type = _renderer->GetType();
	switch (type)
	{
	case RENDERER_TYPE_SKINNED_MESH:
	case RENDERER_TYPE_MESH:
	{
		Transform* trs = _renderer->GetTransform();
		float scale = max(trs->scale.z, max(trs->scale.x, trs->scale.y));
		float radius = (_renderer->GetBoundingRadius() + Nalmak_Math::Length(_renderer->GetBoundingCenter()))* scale;
		Vector3 Center = trs->GetWorldPosition();
		float distance = 0.f;
		for (unsigned int i = 0; i < 6; ++i)
		{
			distance = D3DXPlaneDotCoord(&m_frustumPlane[i], &Center);

			if (distance > radius)
			{
				_renderer->SetFrustumCullingState(FRUSTUM_CULLING_STATE_FAIL);
				
				return false;
			}
		}
		break;
	}
	case RENDERER_TYPE_PARTICLE:
	case RENDERER_TYPE_TRAIL:
		break;
	case RENDERER_TYPE_CANVAS:
		RECT* boundary = ((CanvasRenderer*)_renderer)->GetBoundary();
		if (boundary->left >= (LONG)RenderManager::GetInstance()->GetWindowWidth() ||
			boundary->right <= 0 ||
			boundary->top >= (LONG)RenderManager::GetInstance()->GetWindowHeight() ||
			boundary->bottom <= 0)
		{
			_renderer->SetFrustumCullingState(FRUSTUM_CULLING_STATE_FAIL);
			return false;
		}
		break;
	}

	_renderer->SetFrustumCullingState(FRUSTUM_CULLING_STATE_SUCCESS);
	return true;
}

bool Camera::IsInFrustumCulling(const Vector3 & _pos, float _radius)
{
	if (m_mode != CAMERA_PROJECTION_MODE_PERSPECTIVE)
		return true;

	float radius = _radius;
	Vector3 Center = _pos;
	float distance = 0.f;
	for (unsigned int i = 0; i < 6; ++i)
	{
		distance = D3DXPlaneDotCoord(&m_frustumPlane[i], &Center);

		if (distance > radius)
			return false;
	}
	return true;
}

Vector3 Camera::GetCamToMouseWorldDirection()
{
	float wincx = (float)RenderManager::GetInstance()->GetWindowWidth();
	float wincy = (float)RenderManager::GetInstance()->GetWindowHeight();

	POINT point = {};
	GetCursorPos(&point);
	ScreenToClient(m_handle, &point);

	Vector2 screenPos;
	screenPos.x = (float)point.x;
	screenPos.y = (float)point.y;


	Vector3 camToScreenDirection_ViewSpace;
	Vector3 camToScreenDirection_WorldSpace;
	Matrix invView;
	camToScreenDirection_ViewSpace.x = (((2.0f * screenPos.x) / wincx) - 1.0f) / GetProjMatrix()._11;
	camToScreenDirection_ViewSpace.y = (((-2.0f * screenPos.y) / wincy) + 1.0f) / GetProjMatrix()._22;
	camToScreenDirection_ViewSpace.z = 1.0f;

	D3DXMatrixInverse(&invView, nullptr, &GetViewMatrix());

	D3DXVec3TransformCoord(&camToScreenDirection_WorldSpace, &camToScreenDirection_ViewSpace, &invView);
	return Vector::Normalize(camToScreenDirection_WorldSpace - m_transform->GetWorldPosition());

	
}

void Camera::ClearRenderTarget()
{
	if (m_renderTarget)
		m_renderTarget->Clear();
}

void Camera::RecordRenderTarget()
{
	if(m_renderTarget)
		m_renderTarget->StartRecord(0);
}

void Camera::EndRenderTarget()
{
	if (m_renderTarget)
		m_renderTarget->EndRecord();
}

void Camera::SetRenderTarget(const wstring & _rtName)
{
	m_renderTarget = ResourceManager::GetInstance()->GetResource<RenderTarget>(_rtName);
}

void Camera::AllOnLayer()
{
	m_layer.AllOn();
}

void Camera::AllOffLayer()
{
	m_layer.AllOff();
}

void Camera::OnLayer(_RENDER_LAYER _layer)
{
	m_layer.On(_layer);
}

void Camera::OffLayer(_RENDER_LAYER _layer)
{
	m_layer.Off(_layer);
}

void Camera::UpdateFrustumPlane()
{
	Vector3 point[8];
	D3DXPLANE plane[6];

	point[0] = Vector3(-1.f, 1.f, 0.f);
	point[1] = Vector3(1.f, 1.f, 0.f);
	point[2] = Vector3(1.f, -1.f, 0.f);
	point[3] = Vector3(-1.f, -1.f, 0.f);
	point[4] = Vector3(-1.f, 1.f, 1.f);
	point[5] = Vector3(1.f, 1.f, 1.f);
	point[6] = Vector3(1.f, -1.f, 1.f);
	point[7] = Vector3(-1.f, -1.f, 1.f);

	Matrix invView, invProj;

	D3DXMatrixInverse(&invProj, nullptr, &m_projMatrix);
	D3DXMatrixInverse(&invView, nullptr, &m_viewMatrix);

	for (unsigned int i = 0; i < 8; ++i)
	{
		D3DXVec3TransformCoord(&point[i], &point[i], &invProj);
		D3DXVec3TransformCoord(&point[i], &point[i], &invView);
	}

	// 월드 상태에서 각자의 평면을 만들어 준다.
	// x+
	D3DXPlaneFromPoints(&m_frustumPlane[0], &point[1], &point[5], &point[6]);

	// x-
	D3DXPlaneFromPoints(&m_frustumPlane[1], &point[4], &point[0], &point[3]);

	// y+
	D3DXPlaneFromPoints(&m_frustumPlane[2], &point[4], &point[5], &point[1]);

	// y-
	D3DXPlaneFromPoints(&m_frustumPlane[3], &point[3], &point[2], &point[6]);

	// z+
	D3DXPlaneFromPoints(&m_frustumPlane[4], &point[7], &point[6], &point[5]);

	// z-
	D3DXPlaneFromPoints(&m_frustumPlane[5], &point[0], &point[1], &point[2]);
}

void Camera::UpdateProjMatrix()
{
	if (m_mode == CAMERA_PROJECTION_MODE_PERSPECTIVE)
	{
		D3DXMatrixPerspectiveFovLH(
			&m_projMatrix,
			m_fovY,
			m_aspect,
			m_zNear,
			m_zFar);
	}
	else if (m_mode == CAMERA_PROJECTION_MODE_ORTHOGRAPHIC)
	{
		D3DXMatrixOrthoLH(
			&m_projMatrix,
			m_width,
			m_height,
			m_zNear,
			m_zFar
		);
	}
}

