#pragma once

#ifndef __IRENDERER_H__
#define __IRENDERER_H__

#include "Nalmak_Include.h"
#include "Component.h"
#include "Material.h"
#include "VIBuffer.h"
BEGIN(Nalmak)

class NALMAK_DLL IRenderer :
	public Component
{
public:
	IRenderer();
	virtual ~IRenderer() = default;
protected:
	virtual void Initialize() override;
private:
	// Component을(를) 통해 상속됨
	virtual void Update() override = 0;
	virtual void LateUpdate() override = 0;
	virtual void PreRender() override;
	virtual void Release() override = 0;
public:
	virtual void Render(ConstantBuffer& _cBuffer) = 0;
	virtual void RenderForShadow();
	virtual void BindingStreamSource() = 0;
public:
	void RenderRequest();
public:
	// Only _index parameter is Valid in MeshRenderer 
	virtual int GetMaterialCount()  = 0;
	virtual Material* GetMaterial(int _index = 0) = 0;
	virtual void SetMaterial(Material* _material, int _index = 0) = 0;
	virtual void SetMaterial(const wstring& _mtrlName, int _index = 0) = 0;
	
protected:
	PDIRECT3DDEVICE9 m_device;
	RENDERER_TYPE  m_type;
	bool m_isFrustumCulling = true;
	bool m_isPicking = true;
	bool m_isCastShadow = false;
public:
	virtual float GetBoundingRadius();
	virtual Vector3 GetBoundingCenter();
public:
	bool IsPickingEnable() { return m_isPicking; }
	bool IsFrustumCulling() { return m_isFrustumCulling; }
	bool IsCastShadow() { return m_isCastShadow; }
public:
	const RENDERER_TYPE& GetType() { return m_type; }
public:
	void SetFrustumCulling(bool _culling) { m_isFrustumCulling = _culling; }
	void SetPickingEnable(bool _pick) { m_isPicking = _pick; }
	void SetCastShadow(bool _isCast) { m_isCastShadow = _isCast; }
	void UpdateEachAnimation();
public:
	class Animator* GetAnimator();
protected:
	class RenderManager* m_renderManager = nullptr;
	class Animator* m_animator = nullptr;
};

END
#endif
