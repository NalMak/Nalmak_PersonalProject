#pragma once

#ifndef __CAMERA_H__
#define __CAMERA_H__

#include "Nalmak_Include.h"
#include "Component.h"
#include "RenderManager.h"

BEGIN(Nalmak)
class RenderTarget;
class IRenderer;
class DepthStencil;

class NALMAK_DLL Camera :
	public Component
{
	friend class RenderManager;
public:
	struct Desc
	{
		// for perspective
		float fovY = D3DX_PI * 0.3f;
		float aspect = 0;
		// 변경시 common shader 상수 값도 바꿔주기!
		float zNear = 0.1f;
		float zFar = 400.f; 
		// for orthographic
		UINT width = 0;
		UINT height = 0; 
		// for common
		CAMERA_PROJECTION_MODE  mode = CAMERA_PROJECTION_MODE_PERSPECTIVE;
		CAMERA_RENDERING_MODE renderMode = CAMERA_RENDERING_MODE_FORWARD;
		// for clear solidColor
		wstring skyBoxName = L"";
	};
public:
	Camera(Desc* _desc);
private:
	// Component을(를) 통해 상속됨
	virtual void Initialize() override;
	virtual void Update() override;
	virtual void LateUpdate() override;
	virtual void Release() override;
	virtual void PreRender() override;
private:
	float m_fovY;
	float m_aspect;
	float m_zNear;
	float m_zFar;
	float m_width;
	float m_height;
	Matrix m_projMatrix;


	CAMERA_PROJECTION_MODE m_mode;
	CAMERA_RENDERING_MODE m_renderingMode;
	BitFlag<_RENDER_LAYER> m_layer;
public:
	float GetNear() { return m_zNear; }
	float GetFar() { return m_zFar; }
	const Matrix GetViewMatrix() const;
	const Matrix& GetProjMatrix() { return m_projMatrix; }
	const Matrix GetViewportMatrix() const;
	
	Vector2 WorldToScreenPos(const Vector3& _pos);
	Vector3 ScreenPosToWorld(const Vector2& _screenPos, float Distance_FromCam);

	
	bool CompareLayer(_RENDER_LAYER _layer) { return m_layer.Check(_layer); }
	bool IsInFrustumCulling(IRenderer* _transform);
	bool IsInFrustumCulling(const Vector3& _pos,float _radius);

	const float GetFovY() const { return m_fovY; }
	Vector3 GetCamToMouseWorldDirection();

public:
	void ClearRenderTarget();
	void RecordRenderTarget();
	void EndRenderTarget();	
	void SetRenderTarget(const wstring& _rtName);
	CAMERA_RENDERING_MODE GetRenderingMode() { return m_renderingMode; }
public:
	void AllOnLayer();
	void AllOffLayer();
	void OnLayer(_RENDER_LAYER _layer);
	void OffLayer(_RENDER_LAYER _layer);
private:
	RenderTarget* m_renderTarget;
	D3DXPLANE m_frustumPlane[6];
private:
	void UpdateFrustumPlane();
	void UpdateProjMatrix();

private:
	HWND m_handle;
	// Component을(를) 통해 상속됨
};
END
#endif // !__CAMERA_H__
