#pragma once

#ifndef  __RENDERMANAGER_H__
#define __RENDERMANAGER_H__

#include "Nalmak_Include.h"
#include "Camera.h"

class IRenderer;
class GameObject;
class Material;
class Shader;
class VIBuffer;
class Text;
class Camera;
class DebugManager;
class MeshRenderer;
class LightManager;
class DepthStencil;
BEGIN(Nalmak)



// ���� ��� 
// IRenderer�� ��ӹ��� ������Ʈ���� �� �Ŵ������� ���������� �Ѱ��ְ�
// �Ŵ����� ������ �������� �������� �ǽ��Ѵ�

// ������ �� �� ������ ��ȭ�� ������ ��ȭ�� �ִٸ� ����̽��� ������ �ٲ��ش�

// �ΰ� ���� . ȭ���ػ� ����, ī�޶� ����Ʈ


// ������ ������ ���׸��󿡼� ���� ���� �ϴ� (0 ~ 5000)������ ���� 
// �⺻ ���� 
//#define RENDER_QUEUE_BACKGROUND 1000
//#define RENDER_QUEUE_GEOMETRY 2000
//#define RENDER_QUEUE_TRANSPARENT 3000
//#define RENDER_QUEUE_OVERLAY 4000


//http://ozlael.egloos.com/2423070 ���۵� ������ �ڷ�
//https://portsnake.tistory.com/253

//https://lindenreid.wordpress.com/2017/12/15/simple-water-shader-in-unity/ �� ī�� ������

//https://aker.tistory.com/549 ����ȭ ���߿� �����غ���
//https://www.slideshare.net/cagetu/kgc2012-deferred-forward �����ÿ����� �����ڷ� 
// Texture coverage 

//http://ogldev.atspace.co.uk/www/tutorial21/tutorial21.html  deferred ����!


// PBR ����  ggx
// http://filmicworlds.com/blog/optimizing-ggx-shaders-with-dotlh/ // PBR 

// https://holdimprovae.blogspot.com/2019/01/unityshaderstudy.html dissolve 

//https://catlikecoding.com/unity/tutorials/flow/texture-distortion/ water

//https://cescg.org/wp-content/uploads/2020/03/Fridvalszky-Optimizing-multisample-anti-aliasing-for-deferred-renderers-1.pdf // deferred & msaa
//https://scahp.tistory.com/4 msaa

// https://cybershin.tistory.com/category/API.%20Programming/DirectX9?page=7 grass

//https://superrealizm.tistory.com/entry/HDR-Bloom hdr 

// poisson filter -> shadow 
class RenderManager
{
	DECLARE_SINGLETON(RenderManager)

	typedef int RenderQueue;
public:
	RenderManager();
	~RenderManager();

public:
	void Release();
	void Initialize();
	void Render();
	void Render(Camera* _cam);
	void Reset();
private:
	void SkyboxPass(ConstantBuffer& _cBuffer);
	void DeferredRender(Camera* _cam, ConstantBuffer& _cBuffer);
	void LightDepthPass(ConstantBuffer& _cBuffer);
	void ShadowPass(ConstantBuffer& _cBuffer, DirectionalLightInfo& _info);
	void GBufferPass(Camera* _cam, ConstantBuffer& _cBuffer);
	void DebugPass(ConstantBuffer& _cBuffer);
	void LightPass(Camera* _cam, ConstantBuffer& _cBuffer);
	void PointLightPass(Camera* _cam, ConstantBuffer& _cBuffer);
	void PointLightPass(const Matrix& _matWorld, PointLightInfo _lightInfo, Mesh* _mesh, Shader* _mtrlStencilLight, Shader* _mtrlLight);
	void DirectionalLightPass(ConstantBuffer& _cBuffer);
	void TransparentPass(Camera* _cam, ConstantBuffer& _cBuffer);
	void PostProcessPass(Camera* _cam, ConstantBuffer& _cBuffer);
	void UIPass(Camera* _cam, ConstantBuffer& _cBuffer);
	void BlurPass(RenderTarget* _inRT, RenderTarget* _middleRT, RenderTarget* _outRT, float _rtSizeX, float _rtSizeY);
private:
	void RenderNoneAlpha(Camera * _cam, ConstantBuffer& _cBuffer, RENDERING_MODE _mode);
private:
	void RenderByShaderToScreen(Shader* _shader, ConstantBuffer& _cBuffer, BLENDING_MODE _blendMode);
private:
	ConstantBuffer GetConstantBufferByCam(Camera* _cam);
private:
	Mesh* m_screenImageMesh;
private:
	map<RenderQueue, vector<RenderInfo>> m_renderLists[RENDERING_MODE::RENDERING_MODE_MAX];
	vector<IRenderer*> m_renderUILists;

	vector<Text*> m_textRenderList;
public:
	void RenderRequest(IRenderer* _render);
	void RenderRequest(Text* _text);
public:
	void AddCamera(Camera* _cam);
	void AddCamera(GameObject* _cam);

private:
	list<Camera*> m_cameraList;
	PDIRECT3DDEVICE9 m_device = nullptr;

private:
	Material* m_currentMaterial; // ����ȭ.. Material���� �׸��� ������ �ּ�ȭ
	Shader* m_currentShader; // Shader���� �׸��� ���� �ּ�ȭ
	RenderTarget* m_currentRenderTarget[4]; // RenderTarget ���� �׸��� ���� �ּ�ȭ

	BLENDING_MODE m_blendingMode;
	FILL_MODE m_fillMode;

private:
	Shader* m_screenImageShader;
public:
	void UpdateMaterial(Material* _material, ConstantBuffer& _cBuffer);
	void UpdateRenderTarget();
private:
	void UpdateRenderTarget(Shader* _shader);
	void UpdateRenderTarget(RenderTarget* _rt1, RenderTarget* _rt2 = nullptr, RenderTarget* _rt3 = nullptr, RenderTarget* _rt4 = nullptr);
	void UpdateNoneAlphaMaterial(Material* _material, ConstantBuffer& _cBuffer);
	void UpdateBlendingMode(Material * _material);
	void UpdateBlendingMode(BLENDING_MODE _blending);

	void UpdateFillMode(Material* _material);
	void UpdateFillMode(FILL_MODE _fillMode);

	void EndRenderTarget();
	void UpdateShader(Shader* _shader, ConstantBuffer& _cBuffer);
private:
	void RenderPhysX(ConstantBuffer& _cBuffer);
	void RenderPhysXTriangle();
	void RenderPhysXLine();
private:
	/*void RecordRenderTarget(UINT _index, const wstring& _name);
	void EndRenderTarget(const wstring& _name);
	void RecordDepthStencil(const wstring& _name);
	void EndDepthStencil(const wstring& _name);*/
public:
	void SetWindowSize(UINT _x, UINT _y);
public:
	UINT GetWindowWidth() { return m_wincx; }
	UINT GetWindowHeight() { return m_wincy; }

public:
	Camera* GetMainCamera();
	void DeleteCamera(Camera* _cam);

private:
	UINT m_wincx;
	UINT m_wincy;
	UINT m_halfWincx;
	UINT m_halfWincy;
private:
	DebugManager* m_debugManager;
	LightManager* m_lightManager;
	ResourceManager* m_resourceManager;

public:
	void SetDebugRender(bool _render);
	void SetColliderRender(bool _render);
private:
	bool m_isRenderDebug = true;
	bool m_isRenderCollider = false;
private:
	RenderTarget* m_GBuffer_Diffuse;
	RenderTarget* m_GBuffer_Normal;
	RenderTarget* m_GBuffer_Depth_CookTorrance;
	RenderTarget* m_GBuffer_Light;
	RenderTarget* m_GBuffer_Debug;
	RenderTarget* m_GBuffer_Shadow;
	RenderTarget* m_GBuffer_LightDepth;

	RenderTarget* m_GBuffer_Emission;
	RenderTarget* m_GBuffer_Emission_blur_div2;
	RenderTarget* m_GBuffer_Emission_blur_div2_out;
	RenderTarget* m_GBuffer_Emission_blur_div4;
	RenderTarget* m_GBuffer_Emission_blur_div4_out;



	RenderTarget* m_GBuffer_Specular;
	RenderTarget* m_GBuffer_Specular_blur_div4;
	RenderTarget* m_GBuffer_Specular_blur_div4_out;

	RenderTarget* m_GBuffer_Final;
	RenderTarget* m_GBuffer_Final_div4;
	RenderTarget* m_GBuffer_Final_div4_out;



private:
	Shader* m_SCR_Geometry_Pass;
	Shader* m_SCR_Emission_Pass;
	Shader* m_SCR_Final_Pass;
	Shader* m_SCR_Shadow_Pass;
	Shader* m_SCR_Debug_Pass;
	Shader* m_SCR_DirectionalLight;
	Shader* m_SCR_GaussianBlur;
	Shader* m_SCR_DownSampling_Pass;

private:
	Mesh* m_sphere;
	Shader* m_SCR_PointLight_Stencil;
	Shader* m_SCR_PointLight;
	Shader* m_SYS_LightDepth;
	Shader* m_SYS_LightDepth_Animation;
	Shader* m_SYS_PhysX;

	DepthStencil* m_DepthStencil_Shadow;
};

END
#endif // ! __RENDERMANAGER_H__
