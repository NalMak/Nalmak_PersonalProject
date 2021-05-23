#include "RenderManager.h"
#include "ResourceManager.h"
#include "DeviceManager.h"
#include "IRenderer.h"
#include "Camera.h"
#include "Transform.h"
#include "Material.h"
#include "RenderTarget.h"
#include "Shader.h"
#include "VIBuffer.h"
#include "GameObject.h"
#include "Text.h"
#include "DebugManager.h"
#include "MeshRenderer.h"
#include "LightManager.h"
#include "PointLight.h"
#include "Transform.h"
#include "DepthStencil.h"
#include "PhysicsManager.h"
#include "FrustumCulling.h"
#include "LightManager.h"
#include "DirectionalLight.h"
#include "XFileMesh.h"
#include "SkinnedMeshRenderer.h"

USING(Nalmak)
IMPLEMENT_SINGLETON(RenderManager)
RenderManager::RenderManager()
{
}


RenderManager::~RenderManager()
{
	Release();
}

void RenderManager::Release()
{
	m_device = nullptr;
	m_cameraList.clear();
}

void RenderManager::Initialize()
{
	m_device = DeviceManager::GetInstance()->GetDevice();
	m_debugManager = DebugManager::GetInstance();
	m_lightManager = LightManager::GetInstance();
	m_resourceManager = ResourceManager::GetInstance();

	m_blendingMode = BLENDING_MODE_MAX;

	m_currentMaterial = nullptr;
	m_currentShader = nullptr;

	m_cameraList.clear();

	for (int i = 0; i < 4; ++i)
		m_currentRenderTarget[i] = nullptr;

	D3DVIEWPORT9 vp = { 0,0,m_wincx,m_wincy,0,1 };
	m_device->SetViewport(&vp);


	m_GBuffer_Diffuse = ResourceManager::GetInstance()->GetResource<RenderTarget>(L"GBuffer_Diffuse");
	m_GBuffer_Normal = ResourceManager::GetInstance()->GetResource<RenderTarget>(L"GBuffer_Normal");
	m_GBuffer_Depth_CookTorrance = ResourceManager::GetInstance()->GetResource<RenderTarget>(L"GBuffer_Depth_CookTorrance");
	m_GBuffer_Light = ResourceManager::GetInstance()->GetResource<RenderTarget>(L"GBuffer_Light");
	m_GBuffer_Debug = ResourceManager::GetInstance()->GetResource<RenderTarget>(L"GBuffer_Debug");
	m_GBuffer_Final = ResourceManager::GetInstance()->GetResource<RenderTarget>(L"GBuffer_Final");
	m_GBuffer_Emission = ResourceManager::GetInstance()->GetResource<RenderTarget>(L"GBuffer_Emission");
	m_GBuffer_Specular = ResourceManager::GetInstance()->GetResource<RenderTarget>(L"GBuffer_Specular");
	m_GBuffer_Shadow = ResourceManager::GetInstance()->GetResource<RenderTarget>(L"GBuffer_Shadow");
	m_GBuffer_LightDepth = ResourceManager::GetInstance()->GetResource<RenderTarget>(L"GBuffer_LightDepth");
	
	m_GBuffer_Emission_blur_div4 = ResourceManager::GetInstance()->GetResource<RenderTarget>(L"GBuffer_Emission_blur_div4");
	m_GBuffer_Emission_blur_div4_out = ResourceManager::GetInstance()->GetResource<RenderTarget>(L"GBuffer_Emission_blur_div4_out");
	m_GBuffer_Emission_blur_div2 = ResourceManager::GetInstance()->GetResource<RenderTarget>(L"GBuffer_Emission_blur_div2");
	m_GBuffer_Emission_blur_div2_out = ResourceManager::GetInstance()->GetResource<RenderTarget>(L"GBuffer_Emission_blur_div2_out");

	m_GBuffer_Specular_blur_div4 = ResourceManager::GetInstance()->GetResource<RenderTarget>(L"GBuffer_Specular_blur_div4");
	m_GBuffer_Specular_blur_div4_out = ResourceManager::GetInstance()->GetResource<RenderTarget>(L"GBuffer_Specular_blur_div4_out");

	m_GBuffer_Final_div4 = ResourceManager::GetInstance()->GetResource<RenderTarget>(L"GBuffer_Final_div4");
	m_GBuffer_Final_div4_out = ResourceManager::GetInstance()->GetResource<RenderTarget>(L"GBuffer_Final_div4_out");




	m_screenImageMesh = ResourceManager::GetInstance()->GetResource<Mesh>(L"screenQuad");
	m_sphere = ResourceManager::GetInstance()->GetResource<Mesh>(L"sphere");

	m_SCR_Geometry_Pass = ResourceManager::GetInstance()->GetResource<Shader>(L"SCR_Geometry_Pass");
	m_SCR_Emission_Pass = ResourceManager::GetInstance()->GetResource<Shader>(L"SCR_Emission_Pass");
	m_SCR_Final_Pass = ResourceManager::GetInstance()->GetResource<Shader>(L"SCR_Final_Pass");

	m_SCR_DownSampling_Pass = ResourceManager::GetInstance()->GetResource<Shader>(L"SCR_DownSampling_Pass");

	m_SCR_Shadow_Pass = ResourceManager::GetInstance()->GetResource<Shader>(L"SCR_Shadow_Pass");
	m_SCR_Debug_Pass = ResourceManager::GetInstance()->GetResource<Shader>(L"SCR_Debug_Pass");
	m_SCR_DirectionalLight = ResourceManager::GetInstance()->GetResource<Shader>(L"SCR_DirectionalLight");
	m_SCR_PointLight_Stencil = ResourceManager::GetInstance()->GetResource<Shader>(L"SCR_PointLight_Stencil");
	m_SCR_PointLight = ResourceManager::GetInstance()->GetResource<Shader>(L"SCR_PointLight");
	m_SYS_LightDepth = ResourceManager::GetInstance()->GetResource<Shader>(L"SYS_LightDepth");
	m_SYS_LightDepth_Animation = ResourceManager::GetInstance()->GetResource<Shader>(L"SYS_LightDepth_Animation");
	m_SCR_GaussianBlur = ResourceManager::GetInstance()->GetResource<Shader>(L"SCR_GaussianBlur");
	m_SYS_PhysX = ResourceManager::GetInstance()->GetResource<Shader>(L"SYS_PhysX");

	m_DepthStencil_Shadow = ResourceManager::GetInstance()->GetResource<DepthStencil>(L"DepthStencil_Shadow");



	//m_device->SetSamplerState(0, D3DSAMP_MAXANISOTROPY, 16);

}

void RenderManager::Render()
{
	assert(L"Please Set Camera at least one" &&m_cameraList.size());



	for (auto& cam : m_cameraList)
	{
		if (cam->IsActive())
		{
			Render(cam);
		}
	}
	ThrowIfFailed(m_device->Present(nullptr, nullptr, 0, nullptr));


	Reset();
}

void RenderManager::Render(Camera * _cam)
{
	ThrowIfFailed(m_device->Clear(0, NULL, D3DCLEAR_ZBUFFER | D3DCLEAR_STENCIL, 0, 1, 0));



	m_GBuffer_Diffuse->Clear();
	m_GBuffer_Normal->Clear();
	m_GBuffer_Depth_CookTorrance->Clear();
	m_GBuffer_Light->Clear();
	m_GBuffer_Debug->Clear();
	m_GBuffer_Emission->Clear();
	m_GBuffer_Specular->Clear();
	m_GBuffer_Shadow->Clear();

	m_GBuffer_Final->Clear();
	//m_GBuffer_Final_div4->Clear();
	//m_GBuffer_Final_div4_out->Clear();


	m_GBuffer_Emission_blur_div4->Clear();
	m_GBuffer_Emission_blur_div4_out->Clear();
	m_GBuffer_Emission_blur_div2->Clear();
	m_GBuffer_Emission_blur_div2_out->Clear();

	m_GBuffer_Specular_blur_div4->Clear();
	m_GBuffer_Specular_blur_div4_out->Clear();

	//ClearRenderTarget(L"GBuffer_Shadow_blur128");
	//ClearRenderTarget(L"GBuffer_Shadow_blur128_out");
	//ClearRenderTarget(L"GBuffer_Shadow_blur512");
	//ClearRenderTarget(L"GBuffer_Shadow_blur512_out");

	
	///////////////////////////////////////////////////////
	// public const buffer
	ConstantBuffer cBuffer = GetConstantBufferByCam(_cam);


	ThrowIfFailed(m_device->BeginScene());
	DeferredRender(_cam, cBuffer);
	ThrowIfFailed(m_device->EndScene());


}

void RenderManager::DeferredRender(Camera* _cam, ConstantBuffer& _cBuffer)
{

	SkyboxPass(_cBuffer);

	GBufferPass(_cam, _cBuffer);


	LightDepthPass(_cBuffer);


	// 라이트연산
	LightPass(_cam, _cBuffer);

	// 요기
	RenderByShaderToScreen(m_SCR_Geometry_Pass, _cBuffer, BLENDING_MODE_DEFAULT);

	// 투명객체 그리기
	TransparentPass(_cam, _cBuffer); // transparent object

	BlurPass(m_GBuffer_Specular, m_GBuffer_Specular_blur_div4, m_GBuffer_Specular_blur_div4_out, 480, 270);

	BlurPass(m_GBuffer_Emission, m_GBuffer_Emission_blur_div2, m_GBuffer_Emission_blur_div2_out, 960, 540);
	BlurPass(m_GBuffer_Emission_blur_div2_out, m_GBuffer_Emission_blur_div4, m_GBuffer_Emission_blur_div4_out, 480, 270);

	RenderByShaderToScreen(m_SCR_Emission_Pass, _cBuffer, BLENDING_MODE_DEFAULT);

	//BlurPass(m_GBuffer_Final, m_GBuffer_Final_div4, m_GBuffer_Final_div4_out, 480, 270);

	//RenderByShaderToScreen(m_SCR_DownSampling_Pass, _cBuffer, BLENDING_MODE_DEFAULT);// emission target color + basic color
	

	DebugPass(_cBuffer);

	//RenderByMaterialToScreen(L"GBuffer_Debug", _cBuffer);

	//ClearRenderTarget(L"GBuffer_Bright");
	//ClearRenderTarget(L"Bright_HorizontalBlur");
	


	//RenderByMaterialToScreen(L"GBuffer_Bloom", _cBuffer); // bloom ( blur + basic color)

	PostProcessPass(_cam, _cBuffer);

	EndRenderTarget();

	RenderByShaderToScreen(m_SCR_Final_Pass, _cBuffer, BLENDING_MODE_DEFAULT);

	UIPass(_cam, _cBuffer);

}



void RenderManager::SkyboxPass(ConstantBuffer & _cBuffer)
{
	if (!m_lightManager->IsSkyBoxRender())
		return;


	m_currentShader = nullptr;
	m_currentMaterial = nullptr;

	auto viBuffer = m_lightManager->GetSkyboxMesh();

	UpdateMaterial(m_lightManager->GetSkyboxMaterial(), _cBuffer);
	m_currentMaterial->SetDataToShader();
	UpdateRenderTarget();
	viBuffer->BindingStreamSource(sizeof(INPUT_LAYOUT_SKYBOX));

	DirectionalLightInfo info;
	if (m_lightManager->IsExistDirectionalLight())
		info  = m_lightManager->GetDirectionalLightInfo();
	m_currentShader->SetValue("g_directionalLight", &info, sizeof(DirectionalLightInfo));
	m_currentShader->CommitChanges();

	viBuffer->Draw();

	if (m_currentShader)
	{
		m_currentShader->EndPass();
		EndRenderTarget();
	}
}

void RenderManager::LightDepthPass(ConstantBuffer & _cBuffer)
{

	if (!m_lightManager->IsExistDirectionalLight())
		return;

	m_GBuffer_LightDepth->Clear();
	Camera* lightCam = m_lightManager->GetLightCamera();
	DirectionalLightInfo info = m_lightManager->GetDirectionalLightInfo();

	// cast depth from light

	Shader* currentShader = nullptr;
	Shader* shader[2] = { nullptr,nullptr };

	shader[0] = m_SYS_LightDepth;
	shader[0]->SetValue("g_cBuffer", &_cBuffer, sizeof(ConstantBuffer));
	shader[0]->SetValue("g_directionalLight", &info, sizeof(DirectionalLightInfo));
	shader[1] = m_SYS_LightDepth_Animation;
	shader[1]->SetValue("g_cBuffer", &_cBuffer, sizeof(ConstantBuffer));
	shader[1]->SetValue("g_directionalLight", &info, sizeof(DirectionalLightInfo));
	
	currentShader = shader[0];

	UpdateRenderTarget(currentShader);
	currentShader->BeginPass();


	m_DepthStencil_Shadow->StartRecord();
	ThrowIfFailed(m_device->Clear(0, NULL, D3DCLEAR_ZBUFFER, 0, 1, 0));

	for (auto& renderList : m_renderLists[RENDERING_MODE_OPAQUE])
	{
		for (auto& renderInfo : renderList.second)
		{
			if (!renderInfo.renderer->IsCastShadow())
				continue;

			if (lightCam->IsInFrustumCulling(renderInfo.renderer))
			{
				Shader* newShader = renderInfo.renderer->GetType() == RENDERER_TYPE_SKINNED_MESH ? shader[1] : shader[0];
				if (currentShader != newShader)
				{
					currentShader->EndPass();
					currentShader = newShader;
					currentShader->BeginPass();
				}

				ThrowIfFailed(m_device->SetVertexDeclaration(renderInfo.renderer->GetMaterial()->GetShader()->GetDeclartion()));
				currentShader->SetMatrix("g_world", renderInfo.renderer->GetTransform()->GetWorldMatrix());
				currentShader->CommitChanges();
				renderInfo.renderer->RenderForShadow(currentShader);
			}
		
		}
	}
	for (auto& renderList : m_renderLists[RENDERING_MODE_CUTOUT])
	{
		for (auto& renderInfo : renderList.second)
		{
			if (!renderInfo.renderer->IsCastShadow())
				continue;

			if (lightCam->IsInFrustumCulling(renderInfo.renderer))
			{
				Shader* newShader = renderInfo.renderer->GetType() == RENDERER_TYPE_SKINNED_MESH ? shader[1] : shader[0];
				if (currentShader != newShader)
				{
					currentShader->EndPass();
					currentShader = newShader;
					currentShader->BeginPass();
				}

				ThrowIfFailed(m_device->SetVertexDeclaration(renderInfo.renderer->GetMaterial()->GetShader()->GetDeclartion()));
				currentShader->SetMatrix("g_world", renderInfo.renderer->GetTransform()->GetWorldMatrix());
				currentShader->CommitChanges();
				renderInfo.renderer->RenderForShadow(currentShader);
			}

		}
	}
	EndRenderTarget();
	currentShader->EndPass();
	
	m_DepthStencil_Shadow->EndRecord();

}

void RenderManager::ShadowPass(ConstantBuffer & _cBuffer, DirectionalLightInfo& _info)
{
	
	m_SCR_Shadow_Pass->SetValue("g_directionalLight", &_info, sizeof(DirectionalLightInfo));
	RenderByShaderToScreen(m_SCR_Shadow_Pass, _cBuffer, BLENDING_MODE_DEFAULT);

	//BlurPass(L"GBuffer_Shadow", L"GBuffer_Shadow_blur512", L"GBuffer_Shadow_blur512_out", 512, 512);
	//BlurPass(L"GBuffer_Shadow", L"GBuffer_Shadow_blur128", L"GBuffer_Shadow_blur128_out", 128, 128);
}

void RenderManager::GBufferPass(Camera * _cam, ConstantBuffer& _cBuffer)
{
	ThrowIfFailed(m_device->SetRenderState(D3DRS_ZWRITEENABLE, false));

	RenderNoneAlpha(_cam, _cBuffer, RENDERING_MODE_BACKGROUND);

	ThrowIfFailed(m_device->SetRenderState(D3DRS_ZWRITEENABLE, true));

	RenderNoneAlpha(_cam, _cBuffer, RENDERING_MODE_OPAQUE);


	ThrowIfFailed(m_device->SetRenderState(D3DRS_ALPHATESTENABLE, true));
	ThrowIfFailed(m_device->SetRenderState(D3DRS_ALPHAREF, 100));
	ThrowIfFailed(m_device->SetRenderState(D3DRS_ALPHAFUNC, D3DCMP_GREATER));

	RenderNoneAlpha(_cam, _cBuffer, RENDERING_MODE_CUTOUT);

	ThrowIfFailed(m_device->SetRenderState(D3DRS_ALPHATESTENABLE, false));


	EndRenderTarget();
}


void RenderManager::LightPass(Camera* _cam, ConstantBuffer& _cBuffer)
{
	DirectionalLightPass(_cBuffer);
	
	PointLightPass(_cam, _cBuffer);
}

void RenderManager::PointLightPass(Camera* _cam, ConstantBuffer & _cBuffer)
{
	int count = (int)m_lightManager->GetPointLightCount();
	if (count == 0)
		return;

	m_SCR_PointLight_Stencil->SetValue("g_cBuffer", &_cBuffer, sizeof(ConstantBuffer));
	m_SCR_PointLight->SetValue("g_cBuffer", &_cBuffer, sizeof(ConstantBuffer));

	ThrowIfFailed(m_device->SetRenderState(D3DRS_STENCILENABLE, true));
	ThrowIfFailed(m_device->SetRenderState(D3DRS_STENCILPASS, D3DSTENCILOP::D3DSTENCILOP_KEEP));
	ThrowIfFailed(m_device->SetRenderState(D3DRS_STENCILZFAIL, D3DSTENCILOP::D3DSTENCILOP_DECR));
	ThrowIfFailed(m_device->SetRenderState(D3DRS_CCW_STENCILPASS, D3DSTENCILOP::D3DSTENCILOP_KEEP));
	ThrowIfFailed(m_device->SetRenderState(D3DRS_CCW_STENCILZFAIL, D3DSTENCILOP::D3DSTENCILOP_INCR));

	m_blendingMode = BLENDING_MODE_ADDITIVE;
	ThrowIfFailed(m_device->SetRenderState(D3DRS_BLENDOP, D3DBLENDOP::D3DBLENDOP_ADD));
	ThrowIfFailed(m_device->SetRenderState(D3DRS_SRCBLEND, D3DBLEND::D3DBLEND_ONE));
	ThrowIfFailed(m_device->SetRenderState(D3DRS_DESTBLEND, D3DBLEND::D3DBLEND_ONE));

	ThrowIfFailed(m_device->SetRenderState(D3DRS_FILLMODE, D3DFILLMODE::D3DFILL_SOLID));

	//ThrowIfFailed(m_device->SetStreamSource(0, viBuffer->GetVertexBuffer(), 0, sizeof(INPUT_LAYOUT_POSITION_NORMAL_UV)));
	//ThrowIfFailed(m_device->SetIndices(viBuffer->GetIndexBuffer()));
	


	m_currentShader = nullptr;
	m_currentMaterial = nullptr;

	for (int i = 0; i < count; ++i)
	{
		auto pointLight = m_lightManager->GetPointLight(i);

		if(!pointLight->GetGameObject()->IsActive())
			continue;

		if (!pointLight->IsActive())
			continue;

		Vector3 pos = pointLight->GetTransform()->GetWorldPosition();
		float scale = pointLight->GetRadius() * 2;
		pointLight->SetLightPosition(pos);

		if (_cam->IsInFrustumCulling(pos, scale))
		{
			Matrix world =
			{
				scale,0,0,0,
				0,scale,0,0,
				0,0,scale,0,
				pos.x, pos.y, pos.z,1
			};
			PointLightPass(world, pointLight->GetLightInfo(), m_sphere, m_SCR_PointLight_Stencil, m_SCR_PointLight);
			m_device->Clear(0, nullptr, D3DCLEAR_STENCIL, 0, 1, 0);
		}
	}
	if (m_currentShader)
		m_currentShader->EndPass();


	ThrowIfFailed(m_device->SetRenderState(D3DRS_ALPHABLENDENABLE, false));
	ThrowIfFailed(m_device->SetRenderState(D3DRS_STENCILENABLE, false));
	ThrowIfFailed(m_device->SetRenderState(D3DRS_ZENABLE, true));
	ThrowIfFailed(m_device->SetRenderState(D3DRS_CULLMODE, D3DCULL_CCW));
}

void RenderManager::PointLightPass(const Matrix& _matWorld, PointLightInfo _lightInfo, Mesh* _mesh,  Shader* _mtrlStencilLight, Shader* _mtrlLight)
{

	if(m_currentShader)
		m_currentShader->EndPass();
	m_currentShader = _mtrlStencilLight;
	m_currentShader->BeginPass();

	ThrowIfFailed(m_device->SetVertexDeclaration(m_currentShader->GetDeclartion()));
	UpdateRenderTarget();

	m_currentShader->SetMatrix("g_world", _matWorld);
	m_currentShader->CommitChanges();
	_mesh->Draw();

	EndRenderTarget();

	///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

	m_currentShader->EndPass();
	m_currentShader = _mtrlLight;
	m_currentShader->BeginPass();

	ThrowIfFailed(m_device->SetVertexDeclaration(m_currentShader->GetDeclartion()));
	UpdateRenderTarget();

	m_currentShader->SetValue("g_pointLight", &_lightInfo, sizeof(PointLightInfo));
	m_currentShader->SetMatrix("g_world", _matWorld);

	m_currentShader->CommitChanges();
	_mesh->Draw();


	EndRenderTarget();


}


void RenderManager::DebugPass(ConstantBuffer & _cBuffer)
{
	if(m_isRenderCollider)
		RenderPhysX(_cBuffer);

	if (m_isRenderDebug)
	{
		UpdateBlendingMode(BLENDING_MODE_DEFAULT);
		RenderByShaderToScreen(m_SCR_Debug_Pass, _cBuffer, BLENDING_MODE_DEFAULT);
	}
}


void RenderManager::DirectionalLightPass(ConstantBuffer& _cBuffer)
{
	if (!m_lightManager->IsExistDirectionalLight())
		return;

	DirectionalLightInfo info = m_lightManager->GetDirectionalLightInfo();

	m_SCR_DirectionalLight->SetValue("g_directionalLight", &info, sizeof(DirectionalLightInfo));

	RenderByShaderToScreen(m_SCR_DirectionalLight, _cBuffer, BLENDING_MODE_ADDITIVE);

	ShadowPass(_cBuffer, info);
}

void RenderManager::TransparentPass(Camera* _cam, ConstantBuffer& _cBuffer)
{
	m_currentShader = nullptr;
	m_currentMaterial = nullptr;

	ThrowIfFailed(m_device->SetRenderState(D3DRS_ALPHABLENDENABLE, true));
	ThrowIfFailed(m_device->SetRenderState(D3DRS_ZWRITEENABLE, false));
	ThrowIfFailed(m_device->SetRenderState(D3DRS_ZENABLE, true));


	for (auto& renderList : m_renderLists[RENDERING_MODE_TRANSPARENT])
	{
		for (auto& renderInfo : renderList.second)
		{
			if (_cam->CompareLayer(renderInfo.renderer->GetGameObject()->GetLayer()))
			{
				if (_cam->IsInFrustumCulling(renderInfo.renderer))
				{
					renderInfo.renderer->BindingStreamSource();
					UpdateMaterial(renderInfo.renderer->GetMaterial(renderInfo.containerNum, renderInfo.subsetNum), _cBuffer);
					UpdateRenderTarget();
					renderInfo.renderer->OnRender(m_currentMaterial, _cBuffer, renderInfo.containerNum, renderInfo.subsetNum);
				}
			}
		}
	}

	if (m_currentShader)
	{
		m_currentShader->EndPass();
	}

	ThrowIfFailed(m_device->SetRenderState(D3DRS_ALPHABLENDENABLE, false));
	ThrowIfFailed(m_device->SetRenderState(D3DRS_ZWRITEENABLE, true));

}

void RenderManager::PostProcessPass(Camera * _cam, ConstantBuffer & _cBuffer)
{
	m_currentShader = nullptr;
	m_currentMaterial = nullptr;

	ThrowIfFailed(m_device->SetRenderState(D3DRS_ALPHABLENDENABLE, true));
	ThrowIfFailed(m_device->SetRenderState(D3DRS_ZWRITEENABLE, false));
	ThrowIfFailed(m_device->SetRenderState(D3DRS_ZENABLE, false));

	for (auto& MeshRendererList : m_renderLists[RENDERING_MODE_OVERLAY])
	{
		for (auto& renderInfo : MeshRendererList.second)
		{
			if (_cam->CompareLayer(renderInfo.renderer->GetGameObject()->GetLayer()))
			{
				if (_cam->IsInFrustumCulling(renderInfo.renderer))
				{
					renderInfo.renderer->BindingStreamSource();
					UpdateMaterial(renderInfo.renderer->GetMaterial(renderInfo.containerNum, renderInfo.subsetNum), _cBuffer);
					UpdateRenderTarget();
					renderInfo.renderer->OnRender(m_currentMaterial, _cBuffer, renderInfo.containerNum, renderInfo.subsetNum);
				}
			}
		}
	}

	if (m_currentShader)
	{
		m_currentShader->EndPass();
	}

	ThrowIfFailed(m_device->SetRenderState(D3DRS_ALPHABLENDENABLE, false));
	ThrowIfFailed(m_device->SetRenderState(D3DRS_ZWRITEENABLE, true));
	ThrowIfFailed(m_device->SetRenderState(D3DRS_ZENABLE, true));
}

void RenderManager::UIPass(Camera * _cam, ConstantBuffer & _cBuffer)
{

	m_currentShader = nullptr;
	m_currentMaterial = nullptr;

	ThrowIfFailed(m_device->SetRenderState(D3DRS_ZENABLE, false));
	ThrowIfFailed(m_device->SetRenderState(D3DRS_ALPHABLENDENABLE, true));

	ThrowIfFailed(m_device->SetRenderState(D3DRS_BLENDOP, D3DBLENDOP::D3DBLENDOP_ADD));
	ThrowIfFailed(m_device->SetRenderState(D3DRS_SRCBLEND, D3DBLEND::D3DBLEND_SRCALPHA));
	ThrowIfFailed(m_device->SetRenderState(D3DRS_DESTBLEND, D3DBLEND::D3DBLEND_INVSRCALPHA));
	for (auto& renderer : m_renderUILists)
	{
		if (_cam->CompareLayer(renderer->GetGameObject()->GetLayer()))
		{
			if (_cam->IsInFrustumCulling(renderer))
			{
				renderer->BindingStreamSource();
				UpdateMaterial(renderer->GetMaterial(), _cBuffer);
				UpdateRenderTarget();
				renderer->OnRender(m_currentMaterial, _cBuffer,0,0);
			}
		}
	}

	if (m_currentShader)
	{
		m_currentShader->EndPass();
	}

	ThrowIfFailed(m_device->SetRenderState(D3DRS_ALPHABLENDENABLE, false));
	ThrowIfFailed(m_device->SetRenderState(D3DRS_ZENABLE, true));
}

void RenderManager::BlurPass(RenderTarget* _inRT, RenderTarget* _middleRT, RenderTarget* _outRT, float _rtSizeX, float _rtSizeY)
{
	ThrowIfFailed(m_device->SetRenderState(D3DRS_ZWRITEENABLE, false));

	m_currentShader = m_SCR_GaussianBlur;


	ThrowIfFailed(m_device->SetVertexDeclaration(m_currentShader->GetDeclartion()));
	m_screenImageMesh->BindingStreamSource(sizeof(INPUT_LAYOUT_POSITION_UV));

	m_currentShader->BeginPass(0);
	UpdateRenderTarget(_middleRT);
	m_currentShader->SetTexture("g_mainTex", _inRT->GetTexture());
	m_currentShader->SetFloat("g_RTperPixelX", 0.5f / _rtSizeX);
	m_currentShader->SetFloat("g_RTperPixelY", 0.5f / _rtSizeY);
	m_currentShader->CommitChanges();
	m_screenImageMesh->Draw();
	m_currentShader->EndPass();
	EndRenderTarget();


	////////////////////////////////////////////////////////////////////////////
	m_currentShader->BeginPass(1);
	UpdateRenderTarget(_outRT);
	m_currentShader->SetTexture("g_mainTex", _middleRT->GetTexture());
	m_currentShader->CommitChanges();
	m_screenImageMesh->Draw();
	m_currentShader->EndPass();
	EndRenderTarget();

	ThrowIfFailed(m_device->SetRenderState(D3DRS_ZWRITEENABLE, true));

}

void RenderManager::RenderNoneAlpha(Camera * _cam, ConstantBuffer & _cBuffer, RENDERING_MODE _mode)
{
	m_currentShader = nullptr;
	m_currentMaterial = nullptr;

	for (auto& MeshRendererList : m_renderLists[_mode])
	{
		for (auto& renderInfo : MeshRendererList.second)
		{
			if (_cam->CompareLayer(renderInfo.renderer->GetGameObject()->GetLayer()))
			{
				if (_cam->IsInFrustumCulling(renderInfo.renderer))
				{
					renderInfo.renderer->BindingStreamSource();
					UpdateMaterial(renderInfo.renderer->GetMaterial(renderInfo.containerNum, renderInfo.subsetNum), _cBuffer);
					UpdateRenderTarget();
					renderInfo.renderer->OnRender(m_currentMaterial, _cBuffer, renderInfo.containerNum, renderInfo.subsetNum);
				}
			}
		}
	}

	if (m_currentShader)
	{
		m_currentShader->EndPass();
	}
}

void RenderManager::Reset()
{
	m_currentMaterial = nullptr;

	for (int i = 0; i < RENDERING_MODE_MAX; ++i)
	{
		for (auto& renderList : m_renderLists[i])
		{
			for (auto& renderInfo : renderList.second)
			{
				renderInfo.renderer->ResetFrustumCulling();
				renderInfo.renderer->GetGameObject()->ResetRender();
			}
			renderList.second.clear();
		}
	}
	for (auto& ui : m_renderUILists)
	{
		ui->ResetFrustumCulling();
		ui->GetGameObject()->ResetRender();
	}
	m_renderUILists.clear();

	m_debugManager->EraseTheRecord();
}

void RenderManager::RenderByShaderToScreen(Shader * _shader, ConstantBuffer & _cBuffer, BLENDING_MODE _blendMode)
{
	Shader* shader = _shader;
	shader->SetValue("g_cBuffer", &_cBuffer, sizeof(ConstantBuffer));
	shader->BeginPass();
	UpdateRenderTarget(shader);
	UpdateBlendingMode(_blendMode);
	UpdateFillMode(FILL_MODE_SOLID);

	ThrowIfFailed(m_device->SetVertexDeclaration(shader->GetDeclartion()));
	ThrowIfFailed(m_device->SetRenderState(D3DRS_ZWRITEENABLE, false));

	m_screenImageMesh->BindingStreamSource(sizeof(INPUT_LAYOUT_POSITION_UV));

	shader->CommitChanges();
	m_screenImageMesh->Draw();

	ThrowIfFailed(m_device->SetRenderState(D3DRS_ZWRITEENABLE, true));

	shader->EndPass();
	EndRenderTarget();
}


ConstantBuffer RenderManager::GetConstantBufferByCam(Camera * _cam)
{
	ConstantBuffer cBuffer;

	Matrix view = _cam->GetViewMatrix();
	Matrix proj = _cam->GetProjMatrix();
	Matrix invView;
	D3DXMatrixInverse(&invView, nullptr, &view);
	Matrix invProj;
	D3DXMatrixInverse(&invProj, nullptr, &proj);

	Matrix worldCamMatrix = _cam->GetTransform()->GetWorldMatrix();
	cBuffer.viewProj = view * proj;
	cBuffer.worldCamPos = Vector3(worldCamMatrix._41, worldCamMatrix._42, worldCamMatrix._43);
	cBuffer.worldCamLook = Vector3(worldCamMatrix._31, worldCamMatrix._32, worldCamMatrix._33);

	cBuffer.invView = invView;
	cBuffer.invProj = invProj;
	cBuffer.time = TimeManager::GetInstance()->GetTotalTime();
	////////////////////////////////////////////////////////
	return cBuffer;
}






void RenderManager::RenderRequest(IRenderer * _render)
{
	switch (_render->GetType())
	{
	case RENDERER_TYPE::RENDERER_TYPE_CANVAS:
		m_renderUILists.emplace_back(_render);
		break;
	case RENDERER_TYPE::RENDERER_TYPE_MESH:
	{
		Mesh* mesh = ((MeshRenderer*)_render)->GetMesh();
		UINT containerCount = mesh->GetMeshContainerSize();
		UINT mtrlIndex = 0;
		for (UINT i = 0; i < containerCount; ++i)
		{
			UINT mtrlCount = mesh->GetSubsetCount(i);
			for (UINT j = 0; j < mtrlCount; ++j)
			{

				auto mtrl = _render->GetMaterial(mtrlIndex);
				RenderInfo renderInfo;
				renderInfo.renderer = _render;
				renderInfo.containerNum = i;
				renderInfo.subsetNum = j;
				m_renderLists[mtrl->GetRenderingMode()][mtrl->GetRenderQueue()].emplace_back(renderInfo);
				++mtrlIndex;
			}
		}
		break;
	}
	case RENDERER_TYPE::RENDERER_TYPE_SKINNED_MESH:
	{
		XFileMesh* mesh = ((SkinnedMeshRenderer*)_render)->GetMesh();
		UINT containerCount = mesh->GetMeshContainerSize();
		UINT mtrlIndex = 0;
		for (UINT i = 0; i < containerCount; ++i)
		{
			UINT mtrlCount = mesh->GetSubsetCount(i);
			for (UINT j = 0; j < mtrlCount; ++j)
			{
			
				auto mtrl = _render->GetMaterial(mtrlIndex);
				RenderInfo renderInfo;
				renderInfo.renderer = _render;
				renderInfo.containerNum = i;
				renderInfo.subsetNum = j;
				m_renderLists[mtrl->GetRenderingMode()][mtrl->GetRenderQueue()].emplace_back(renderInfo);
				++mtrlIndex;
			}
		}
		break;
	}
	case RENDERER_TYPE::RENDERER_TYPE_PARTICLE:
	case RENDERER_TYPE::RENDERER_TYPE_TRAIL:
	{
		auto mtrl = _render->GetMaterial();
		RenderInfo renderInfo;
		renderInfo.renderer = _render;
		m_renderLists[mtrl->GetRenderingMode()][mtrl->GetRenderQueue()].emplace_back(renderInfo);
		break;
	}
	default:
		break;
	}


}

void RenderManager::RenderRequest(Text * _text)
{
	assert("text is nullptr!" && _text);
	m_textRenderList.emplace_back(_text);
}

void RenderManager::AddCamera(Camera * _cam)
{
	assert("Camera is nullptr " && _cam);
	m_cameraList.emplace_back(_cam);
}

void RenderManager::AddCamera(GameObject * _cam)
{
	AddCamera(_cam->GetComponent<Camera>());
}


void RenderManager::UpdateMaterial(Material * _material, ConstantBuffer & _cBuffer)
{
	if (m_currentMaterial != _material)
	{
		m_currentMaterial = _material;
		UpdateBlendingMode(_material);
		UpdateFillMode(_material);
		UpdateShader(m_currentMaterial->GetShader(), _cBuffer);
	}

}

void RenderManager::UpdateBlendingMode(Material * _material)
{

	auto mode = _material->GetBlendingMode();
	if (m_blendingMode != mode)
	{
		m_blendingMode = mode;
		switch (mode)
		{
		case BLENDING_MODE_DEFAULT:
			ThrowIfFailed(m_device->SetRenderState(D3DRS_BLENDOP, D3DBLENDOP::D3DBLENDOP_ADD));
			ThrowIfFailed(m_device->SetRenderState(D3DRS_SRCBLEND, D3DBLEND::D3DBLEND_SRCALPHA));
			ThrowIfFailed(m_device->SetRenderState(D3DRS_DESTBLEND, D3DBLEND::D3DBLEND_INVSRCALPHA));

			break;
		case BLENDING_MODE_ADDITIVE:
			ThrowIfFailed(m_device->SetRenderState(D3DRS_BLENDOP, D3DBLENDOP::D3DBLENDOP_ADD));
			ThrowIfFailed(m_device->SetRenderState(D3DRS_SRCBLEND, D3DBLEND::D3DBLEND_ONE));
			ThrowIfFailed(m_device->SetRenderState(D3DRS_DESTBLEND, D3DBLEND::D3DBLEND_ONE));
			break;
		case BLENDING_MODE_SUBTRACTIVE:
			ThrowIfFailed(m_device->SetRenderState(D3DRS_BLENDOP, D3DBLENDOP::D3DBLENDOP_REVSUBTRACT));
			ThrowIfFailed(m_device->SetRenderState(D3DRS_SRCBLEND, D3DBLEND::D3DBLEND_ONE));
			ThrowIfFailed(m_device->SetRenderState(D3DRS_DESTBLEND, D3DBLEND::D3DBLEND_ONE));
			break;
		case BLENDING_MODE_MULTIPLY:
			ThrowIfFailed(m_device->SetRenderState(D3DRS_BLENDOP, D3DBLENDOP::D3DBLENDOP_ADD));
			ThrowIfFailed(m_device->SetRenderState(D3DRS_SRCBLEND, D3DBLEND::D3DBLEND_SRCCOLOR));
			ThrowIfFailed(m_device->SetRenderState(D3DRS_DESTBLEND, D3DBLEND::D3DBLEND_DESTCOLOR));
			break;
		default:
			break;
		}
	}
}

void RenderManager::UpdateBlendingMode(BLENDING_MODE _blending)
{
	if (m_blendingMode != _blending)
	{
		m_blendingMode = _blending;
		switch (m_blendingMode)
		{
		case BLENDING_MODE_DEFAULT:
			ThrowIfFailed(m_device->SetRenderState(D3DRS_BLENDOP, D3DBLENDOP::D3DBLENDOP_ADD));
			ThrowIfFailed(m_device->SetRenderState(D3DRS_SRCBLEND, D3DBLEND::D3DBLEND_SRCALPHA));
			ThrowIfFailed(m_device->SetRenderState(D3DRS_DESTBLEND, D3DBLEND::D3DBLEND_INVSRCALPHA));

			break;
		case BLENDING_MODE_ADDITIVE:
			ThrowIfFailed(m_device->SetRenderState(D3DRS_BLENDOP, D3DBLENDOP::D3DBLENDOP_ADD));
			ThrowIfFailed(m_device->SetRenderState(D3DRS_SRCBLEND, D3DBLEND::D3DBLEND_ONE));
			ThrowIfFailed(m_device->SetRenderState(D3DRS_DESTBLEND, D3DBLEND::D3DBLEND_ONE));
			break;
		case BLENDING_MODE_SUBTRACTIVE:
			ThrowIfFailed(m_device->SetRenderState(D3DRS_BLENDOP, D3DBLENDOP::D3DBLENDOP_REVSUBTRACT));
			ThrowIfFailed(m_device->SetRenderState(D3DRS_SRCBLEND, D3DBLEND::D3DBLEND_ONE));
			ThrowIfFailed(m_device->SetRenderState(D3DRS_DESTBLEND, D3DBLEND::D3DBLEND_ONE));
			break;
		case BLENDING_MODE_MULTIPLY:
			ThrowIfFailed(m_device->SetRenderState(D3DRS_BLENDOP, D3DBLENDOP::D3DBLENDOP_ADD));
			ThrowIfFailed(m_device->SetRenderState(D3DRS_SRCBLEND, D3DBLEND::D3DBLEND_SRCCOLOR));
			ThrowIfFailed(m_device->SetRenderState(D3DRS_DESTBLEND, D3DBLEND::D3DBLEND_DESTCOLOR));
			break;
		default:
			break;
		}
	}
}

void RenderManager::UpdateFillMode(Material * _material)
{
	auto fillMode = _material->GetFillMode();
	if (m_fillMode != fillMode)
	{
		m_fillMode = fillMode;

		switch (m_fillMode)
		{
		case FILL_MODE_SOLID:
			ThrowIfFailed(m_device->SetRenderState(D3DRS_FILLMODE, D3DFILLMODE::D3DFILL_SOLID));
			break;
		case FILL_MODE_WIREFRAME:
			ThrowIfFailed(m_device->SetRenderState(D3DRS_FILLMODE, D3DFILLMODE::D3DFILL_WIREFRAME));
			break;
		case FILL_MODE_POINT:
			ThrowIfFailed(m_device->SetRenderState(D3DRS_FILLMODE, D3DFILLMODE::D3DFILL_POINT));

			break;
		default:
			break;
		}
	}

}

void RenderManager::UpdateFillMode(FILL_MODE _fillMode)
{
	if (m_fillMode != _fillMode)
	{
		m_fillMode = _fillMode;

		switch (m_fillMode)
		{
		case FILL_MODE_SOLID:
			ThrowIfFailed(m_device->SetRenderState(D3DRS_FILLMODE, D3DFILLMODE::D3DFILL_SOLID));
			break;
		case FILL_MODE_WIREFRAME:
			ThrowIfFailed(m_device->SetRenderState(D3DRS_FILLMODE, D3DFILLMODE::D3DFILL_WIREFRAME));
			break;
		case FILL_MODE_POINT:
			ThrowIfFailed(m_device->SetRenderState(D3DRS_FILLMODE, D3DFILLMODE::D3DFILL_POINT));

			break;
		default:
			break;
		}
	}
}



void RenderManager::UpdateRenderTarget()
{
	for (int i = 0; i < 4; ++i)
	{
		RenderTarget* newRendertarget = m_currentShader->GetRenderTarget(i);

		if (m_currentRenderTarget[i] != newRendertarget)
		{
			if (m_currentRenderTarget[i])
				m_currentRenderTarget[i]->EndRecord();

			m_currentRenderTarget[i] = newRendertarget;
			if (!newRendertarget)
				continue;

			m_currentRenderTarget[i]->StartRecord(i);
		}
	}
}

void RenderManager::UpdateRenderTarget(Shader * _shader)
{
	for (int i = 0; i < 4; ++i)
	{
		RenderTarget* newRendertarget = _shader->GetRenderTarget(i);

		if (m_currentRenderTarget[i] != newRendertarget)
		{
			if (m_currentRenderTarget[i])
				m_currentRenderTarget[i]->EndRecord();

			m_currentRenderTarget[i] = newRendertarget;
			if (!newRendertarget)
				continue;

			m_currentRenderTarget[i]->StartRecord(i);
		}
	}
}

void RenderManager::UpdateRenderTarget(RenderTarget * _rt1, RenderTarget * _rt2, RenderTarget * _rt3, RenderTarget * _rt4)
{
	RenderTarget* newRendertargets[4] = { _rt1,_rt2,_rt3,_rt4 };
	RenderTarget* newRendertarget = nullptr;
	for (int i = 0; i < 4; ++i)
	{
		newRendertarget = newRendertargets[i];

		if (m_currentRenderTarget[i] != newRendertarget)
		{
			if (m_currentRenderTarget[i])
				m_currentRenderTarget[i]->EndRecord();

			m_currentRenderTarget[i] = newRendertarget;
			if (!newRendertarget)
				continue;

			m_currentRenderTarget[i]->StartRecord(i);
		}
	}
}



void RenderManager::EndRenderTarget()
{
	for (int i = 0; i < 4; ++i)
	{
		if (m_currentRenderTarget[i])
		{
			m_currentRenderTarget[i]->EndRecord();
			m_currentRenderTarget[i] = nullptr;
		}
	}
}

void RenderManager::UpdateShader(Shader * _shader, ConstantBuffer& _cBuffer)
{
	if (m_currentShader != _shader)
	{
		if (m_currentShader)
			m_currentShader->EndPass();

		m_currentShader = _shader;

		m_currentShader->SetValue("g_cBuffer", &_cBuffer, sizeof(ConstantBuffer));
		m_currentShader->BeginPass();

		ThrowIfFailed(m_device->SetVertexDeclaration(m_currentShader->GetDeclartion()));
	}
}

void RenderManager::RenderPhysX(ConstantBuffer& _cBuffer)
{
	m_currentShader = nullptr;
	m_currentMaterial = nullptr;

	UpdateBlendingMode(BLENDING_MODE_DEFAULT);
	UpdateFillMode(FILL_MODE_WIREFRAME);
	UpdateShader(m_SYS_PhysX, _cBuffer);
	UpdateRenderTarget(m_SYS_PhysX);
	m_currentShader->CommitChanges();

	RenderPhysXLine();
	RenderPhysXTriangle();

	EndRenderTarget();

	if (m_currentShader)
	{
		m_currentShader->EndPass();
	}
}

void RenderManager::RenderPhysXTriangle()
{
	const PxRenderBuffer& renderData = PhysicsManager::GetInstance()->GetDebugRenderBuffer();
	unsigned int nbTriangleCount = renderData.getNbTriangles();

	if (nbTriangleCount)
	{
		INPUT_LAYOUT_POSITION_COLOR* vertex = new INPUT_LAYOUT_POSITION_COLOR[nbTriangleCount * 3];

		const PxDebugTriangle* triangles = renderData.getTriangles();

		unsigned int vertexIndex = 0;
		while (nbTriangleCount--)
		{
			vertex[vertexIndex].position = { triangles->pos0.x,triangles->pos0.y, triangles->pos0.z };
			vertex[vertexIndex].color = { 255,0,255 };
			++vertexIndex;

			vertex[vertexIndex].position = { triangles->pos1.x,triangles->pos1.y, triangles->pos1.z };
			vertex[vertexIndex].color = { 255,0,255 };
			++vertexIndex;

			vertex[vertexIndex].position = { triangles->pos2.x,triangles->pos2.y, triangles->pos2.z };
			vertex[vertexIndex].color = { 255,0,255 };
			++vertexIndex;

			++triangles;
		}

		m_device->DrawPrimitiveUP(D3DPT_TRIANGLELIST, renderData.getNbTriangles(), vertex, sizeof(INPUT_LAYOUT_POSITION_COLOR));
		SAFE_DELETE_ARR(vertex);
	}
}

void RenderManager::RenderPhysXLine()
{

	const PxRenderBuffer& renderData = PhysicsManager::GetInstance()->GetDebugRenderBuffer();
	unsigned int nbLineCount = renderData.getNbLines();

	if (nbLineCount)
	{
		INPUT_LAYOUT_POSITION_COLOR* vertex = new INPUT_LAYOUT_POSITION_COLOR[nbLineCount * 2];

		const PxDebugLine* lines = renderData.getLines();

		unsigned int vertexIndex = 0;
		while (nbLineCount--)
		{
			vertex[vertexIndex].position = { lines->pos0.x,lines->pos0.y, lines->pos0.z };
			vertex[vertexIndex].color = { 255,0,255 };

			++vertexIndex;

			vertex[vertexIndex].position = { lines->pos1.x,lines->pos1.y, lines->pos1.z };
			vertex[vertexIndex].color = { 255,0,255 };

			++vertexIndex;

			++lines;

		}

		m_device->DrawPrimitiveUP(D3DPT_LINELIST, renderData.getNbLines(), vertex, sizeof(INPUT_LAYOUT_POSITION_COLOR));
		SAFE_DELETE_ARR(vertex);
	}
}

void RenderManager::SetWindowSize(UINT _x, UINT _y)
{
	m_wincx = _x;
	m_wincy = _y;

	m_halfWincx = (UINT)(m_wincx * 0.5f);
	m_halfWincy = (UINT)(m_wincy * 0.5f);

	for (auto& cam : m_cameraList)
	{
		cam->UpdateProjMatrix();
	}
}

Camera * RenderManager::GetMainCamera()
{
	for (auto& cam : m_cameraList)
	{
		if (cam->IsActive())
		{
			return cam;
		}
	}

	return nullptr;
}

void RenderManager::DeleteCamera(Camera * _cam)
{
	if (!m_device)
		return;

	if (m_cameraList.size() == 0)
		return;

	for (auto iter = m_cameraList.begin(); iter != m_cameraList.end(); ++iter)
	{
		if ((*iter) == _cam)
		{
			//(*iter) = nullptr;
			m_cameraList.erase(iter);
			return;
		}
	}
}

void RenderManager::SetDebugRender(bool _render)
{
	m_isRenderDebug = _render;
}

void RenderManager::SetColliderRender(bool _render)
{
	m_isRenderCollider = _render;
}

