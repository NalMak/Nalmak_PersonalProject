#pragma once

#ifndef __IRENDERER_H__
#define __IRENDERER_H__

#include "Nalmak_Include.h"
#include "RenderInfo.h"
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
	void OnRender(Shader* _shader, ConstantBuffer& _cBuffer,UINT _containerIndex, UINT _subsetIndex);
protected:
	virtual void Render(Shader* _shader, ConstantBuffer& _cBuffer, UINT _containerIndex, UINT _subsetIndex) = 0;
public:
	virtual void RenderForShadow(Shader* _shader);
	virtual void BindingStreamSource() = 0;
public:
	void RenderRequest();
public:
	// Only _index parameter is Valid in MeshRenderer 
	virtual int GetMaterialCount()  = 0;
	virtual Material* GetMaterial(UINT _containerIndex = 0, UINT _subsetIndex = 0) = 0;
	virtual void SetMaterial(Material* _material, int _index = 0) = 0;
	virtual void SetMaterial(const wstring& _mtrlName, int _index = 0) = 0;
	
protected:
	PDIRECT3DDEVICE9 m_device;
	RENDERER_TYPE  m_type;
	FRUSTUM_CULLING_STATE m_frustumculling = FRUSTUM_CULLING_STATE_READY;
	bool m_isPicking = true;
	bool m_isCastShadow = false;
public:
	virtual float GetBoundingRadius();
	virtual Vector3 GetBoundingCenter();
public:
	bool IsPickingEnable() { return m_isPicking; }
	FRUSTUM_CULLING_STATE GetFrustumCullingState() { return m_frustumculling; }
	bool IsCastShadow() { return m_isCastShadow; }
public:
	const RENDERER_TYPE& GetType() { return m_type; }
public:
	void SetFrustumCullingState(FRUSTUM_CULLING_STATE _culling) { m_frustumculling = _culling; }
	void ResetFrustumCulling();
	void SetPickingEnable(bool _pick) { m_isPicking = _pick; }
	void SetCastShadow(bool _isCast) { m_isCastShadow = _isCast; }
protected:
	class RenderManager* m_renderManager = nullptr;
};

END
#endif
