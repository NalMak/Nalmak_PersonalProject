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

	m_screenImageMesh = ResourceManager::GetInstance()->GetResource<Mesh>(L"screenQuad");
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

	ClearRenderTarget(L"GBuffer_Diffuse");
	ClearRenderTarget(L"GBuffer_Normal");
	ClearRenderTarget(L"GBuffer_Depth");
	ClearRenderTarget(L"GBuffer_CookTorrance");
	ClearRenderTarget(L"GBuffer_Light");
	ClearRenderTarget(L"GBuffer_Debug");
	ClearRenderTarget(L"GBuffer_Final");
	ClearRenderTarget(L"GBuffer_Emission");
	ClearRenderTarget(L"GBuffer_Shadow");


	
	///////////////////////////////////////////////////////
	// public const buffer
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



	ThrowIfFailed(m_device->BeginScene());
	DeferredRender(_cam, cBuffer);
	ThrowIfFailed(m_device->EndScene());


}

void RenderManager::DeferredRender(Camera* _cam, ConstantBuffer& _cBuffer)
{

	SkyboxPass(_cBuffer);

	GBufferPass(_cam, _cBuffer);

	LightPass(_cam, _cBuffer);

	RenderByShaderToScreen(L"SCR_Shadow_Pass", _cBuffer, BLENDING_MODE_DEFAULT);

	RenderByShaderToScreen(L"SCR_Geometry_Pass", _cBuffer, BLENDING_MODE_DEFAULT);

	TransparentPass(_cam, _cBuffer); // transparent object

	RenderByShaderToScreen(L"SCR_Emission_Pass", _cBuffer, BLENDING_MODE_DEFAULT);// emission target color + basic color
	
	DebugPass(_cBuffer);

	//RenderByMaterialToScreen(L"GBuffer_Debug", _cBuffer);

	//ClearRenderTarget(L"GBuffer_Bright");
	//ClearRenderTarget(L"Bright_HorizontalBlur");
	//RenderByMaterialToScreen(L"GBuffer_Bright", _cBuffer); // bright filter by basic color
	//RenderByMaterialToScreen(L"brightHorizontalBlur", _cBuffer); // blur by basic color
	//RenderByMaterialToScreen(L"brightVerticalBlur", _cBuffer);// Draw to GBuffer_Bright blur by basic color
	//RenderByMaterialToScreen(L"GBuffer_Bloom", _cBuffer); // bloom ( blur + basic color)

	PostProcessPass(_cam, _cBuffer);

	EndRenderTarget();

	RenderByShaderToScreen(L"SCR_Final_Pass", _cBuffer, BLENDING_MODE_DEFAULT);

	UIPass(_cam, _cBuffer);

}

void RenderManager::SkyboxPass(ConstantBuffer & _cBuffer)
{
	if (!m_lightManager->IsSkyBoxRender())
		return;

	ThrowIfFailed(m_device->SetRenderState(D3DRS_ALPHABLENDENABLE, false));
	ThrowIfFailed(m_device->SetRenderState(D3DRS_ALPHATESTENABLE, false));

	m_currentShader = nullptr;
	m_currentMaterial = nullptr;

	auto viBuffer = m_lightManager->GetSkyboxMesh();

	UpdateMaterial(m_lightManager->GetSkyboxMaterial(), _cBuffer);
	UpdateRenderTarget();

	viBuffer->BindingStreamSource(sizeof(INPUT_LAYOUT_SKYBOX));

	DirectionalLightInfo info;
	if (m_lightManager->GetDirectionalLightInfo(info))
	{
		m_currentShader->SetValue("g_directionalLight", &info, sizeof(DirectionalLightInfo));
	}
	else
	{
		m_currentShader->SetValue("g_directionalLight", &DirectionalLightInfo(), sizeof(DirectionalLightInfo));
	}

	m_currentShader->CommitChanges();
	viBuffer->Draw();

	if (m_currentShader)
	{
		m_currentShader->EndPass();
		EndRenderTarget();
	}
}

void RenderManager::GBufferPass(Camera * _cam, ConstantBuffer& _cBuffer)
{
	ThrowIfFailed(m_device->SetRenderState(D3DRS_ZWRITEENABLE, false));

	RenderNoneAlpha(_cam, _cBuffer, RENDERING_MODE_BACKGROUND);

	ThrowIfFailed(m_device->SetRenderState(D3DRS_ZWRITEENABLE, true));

	RenderNoneAlpha(_cam, _cBuffer, RENDERING_MODE_OPAQUE);


	ThrowIfFailed(m_device->SetRenderState(D3DRS_ALPHATESTENABLE, true));
	ThrowIfFailed(m_device->SetRenderState(D3DRS_ALPHAREF, 50));
	ThrowIfFailed(m_device->SetRenderState(D3DRS_ALPHAFUNC, D3DCMP_GREATER));

	RenderNoneAlpha(_cam, _cBuffer, RENDERING_MODE_CUTOUT);

	ThrowIfFailed(m_device->SetRenderState(D3DRS_ALPHATESTENABLE, false));


	EndRenderTarget();
}

void RenderManager::ShadowPass(Camera * _cam, ConstantBuffer & _cBuffer)
{
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

	Mesh* mesh = m_resourceManager->GetResource<Mesh>(L"sphere");
	Shader* mtrlStencilLight = m_resourceManager->GetResource<Shader>(L"SCR_PointLight_Stencil");
	Shader* mtrlLight = m_resourceManager->GetResource<Shader>(L"SCR_PointLight");


	ThrowIfFailed(m_device->SetRenderState(D3DRS_STENCILENABLE, true));
	ThrowIfFailed(m_device->SetRenderState(D3DRS_STENCILPASS, D3DSTENCILOP::D3DSTENCILOP_KEEP));
	ThrowIfFailed(m_device->SetRenderState(D3DRS_STENCILZFAIL, D3DSTENCILOP::D3DSTENCILOP_DECR));
	ThrowIfFailed(m_device->SetRenderState(D3DRS_CCW_STENCILPASS, D3DSTENCILOP::D3DSTENCILOP_KEEP));
	ThrowIfFailed(m_device->SetRenderState(D3DRS_CCW_STENCILZFAIL, D3DSTENCILOP::D3DSTENCILOP_INCR));

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

		Matrix world;
		Vector3 pos = pointLight->GetTransform()->GetWorldPosition();
		float scale = pointLight->GetRadius() * 2;
		pointLight->SetLightPosition(pos);

		Matrix matTrs, matScale;
		D3DXMatrixTranslation(&matTrs, pos.x, pos.y, pos.z);
		D3DXMatrixScaling(&matScale, scale, scale, scale);
		world = matScale * matTrs;

		if (_cam->IsInFrustumCulling(pos, scale))
		{
			PointLightPass(world, pointLight->GetLightInfo(), mesh, _cBuffer, mtrlStencilLight, mtrlLight);
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

void RenderManager::PointLightPass(const Matrix& _matWorld, PointLightInfo _lightInfo, Mesh* _mesh, ConstantBuffer & _cBuffer, Shader* _mtrlStencilLight, Shader* _mtrlLight)
{
	ThrowIfFailed(m_device->SetRenderState(D3DRS_ALPHABLENDENABLE, false));

	UpdateShader(_mtrlStencilLight, _cBuffer);
	UpdateRenderTarget();

	m_device->SetRenderState(D3DRS_ZENABLE, true);
	m_device->SetRenderState(D3DRS_ZWRITEENABLE, false);
	m_device->SetRenderState(D3DRS_CULLMODE, D3DCULL_NONE);
	m_device->SetRenderState(D3DRS_STENCILFUNC, D3DCMP_ALWAYS);
	m_device->SetRenderState(D3DRS_TWOSIDEDSTENCILMODE, true);

	m_currentShader->SetMatrix("g_world", _matWorld);
	m_currentShader->CommitChanges();
	_mesh->Draw();

	EndRenderTarget();

	///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

	ThrowIfFailed(m_device->SetRenderState(D3DRS_ALPHABLENDENABLE, true));

	UpdateShader(_mtrlLight, _cBuffer);
	UpdateRenderTarget();

	m_device->SetRenderState(D3DRS_ZENABLE, false);
	m_device->SetRenderState(D3DRS_ZWRITEENABLE, true);
	m_device->SetRenderState(D3DRS_CULLMODE, D3DCULL_CW);
	m_device->SetRenderState(D3DRS_STENCILFUNC, D3DCMP_NOTEQUAL);
	m_device->SetRenderState(D3DRS_STENCILREF, 0);

	m_device->SetRenderState(D3DRS_TWOSIDEDSTENCILMODE, false);

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
		RenderByShaderToScreen(L"SCR_Debug_Pass", _cBuffer, BLENDING_MODE_DEFAULT);
	}
}


void RenderManager::DirectionalLightPass(ConstantBuffer& _cBuffer)
{
	DirectionalLightInfo info;
	if (!m_lightManager->GetDirectionalLightInfo(info))
		return;

	Shader* shader = m_resourceManager->GetResource<Shader>(L"SCR_DirectionalLight");
	shader->SetValue("g_directionalLight", &info, sizeof(DirectionalLightInfo));


	RenderByShaderToScreen(L"SCR_DirectionalLight", _cBuffer, BLENDING_MODE_ADDITIVE);
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
		for (auto& renderer : renderList.second)
		{
			if (_cam->CompareLayer(renderer->GetGameObject()->GetLayer()))
			{
				if (_cam->IsInFrustumCulling(renderer))
				{
					renderer->Render(_cBuffer);
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
		for (auto& renderer : MeshRendererList.second)
		{
			if (_cam->CompareLayer(renderer->GetGameObject()->GetLayer()))
			{
				if (_cam->IsInFrustumCulling(renderer))
				{
					renderer->Render(_cBuffer);
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


	for (auto& renderer : m_renderUILists)
	{
		if (_cam->CompareLayer(renderer->GetGameObject()->GetLayer()))
		{
			if (_cam->IsInFrustumCulling(renderer))
			{
				renderer->Render(_cBuffer);
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

void RenderManager::RenderNoneAlpha(Camera * _cam, ConstantBuffer & _cBuffer, RENDERING_MODE _mode)
{
	m_currentShader = nullptr;
	m_currentMaterial = nullptr;

	for (auto& MeshRendererList : m_renderLists[_mode])
	{
		for (auto& renderer : MeshRendererList.second)
		{
			if (_cam->CompareLayer(renderer->GetGameObject()->GetLayer()))
			{
				if (_cam->IsInFrustumCulling(renderer))
				{
					renderer->Render(_cBuffer);
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
		for (auto& renderList : m_renderLists[i])
		{
			renderList.second.clear();
		}
	m_renderUILists.clear();

	m_debugManager->EraseTheRecord();
}

void RenderManager::RenderByShaderToScreen(const wstring & _shaderName, ConstantBuffer& _cBuffer,BLENDING_MODE _blendMode)
{
	Shader* shader = ResourceManager::GetInstance()->GetResource<Shader>(_shaderName);
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






void RenderManager::RenderRequest(IRenderer * _render)
{
	auto mtrl = _render->GetMaterial();
	if (_render->GetType() == RENDERER_TYPE::RENDERER_TYPE_CANVAS)
		m_renderUILists.emplace_back(_render);
	else
		m_renderLists[mtrl->GetRenderingMode()][mtrl->GetRenderQueue()].emplace_back(_render);

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
		_material->SetDataToShader();

		UpdateShader(m_currentMaterial->GetShader(), _cBuffer);
	}

}

void RenderManager::UpdateNoneAlphaMaterial(Material * _material, ConstantBuffer & _cBuffer)
{
	if (m_currentMaterial != _material)
	{
		m_currentMaterial = _material;

		UpdateFillMode(_material);
		_material->SetDataToShader();

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

	Shader* shader = m_resourceManager->GetResource<Shader>(L"SYS_PhysX");
	
	UpdateBlendingMode(BLENDING_MODE_DEFAULT);
	UpdateFillMode(FILL_MODE_WIREFRAME);
	UpdateShader(shader, _cBuffer);
	UpdateRenderTarget(shader);


	RenderPhysXLine();
	RenderPhysXTriangle();

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
			vertex[vertexIndex].color = DWORD_TO_COLOR3(triangles->color0);
			++vertexIndex;

			vertex[vertexIndex].position = { triangles->pos1.x,triangles->pos1.y, triangles->pos1.z };
			vertex[vertexIndex].color = DWORD_TO_COLOR3(triangles->color1);
			++vertexIndex;

			vertex[vertexIndex].position = { triangles->pos2.x,triangles->pos2.y, triangles->pos2.z };
			vertex[vertexIndex].color = DWORD_TO_COLOR3(triangles->color2);
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
			vertex[vertexIndex].color = DWORD_TO_COLOR3(lines->color0);
			++vertexIndex;

			vertex[vertexIndex].position = { lines->pos1.x,lines->pos1.y, lines->pos1.z };
			vertex[vertexIndex].color = DWORD_TO_COLOR3(lines->color1);
			++vertexIndex;

			++lines;
		}

		m_device->DrawPrimitiveUP(D3DPT_LINELIST, renderData.getNbLines(), vertex, sizeof(INPUT_LAYOUT_POSITION_COLOR));
		SAFE_DELETE_ARR(vertex);
	}
}

void RenderManager::RecordRenderTarget(UINT _index, const wstring & _name)
{
	m_resourceManager->GetResource<RenderTarget>(_name)->StartRecord(_index);
}

void RenderManager::EndRenderTarget(const wstring & _name)
{
	m_resourceManager->GetResource<RenderTarget>(_name)->EndRecord();
}

void RenderManager::RecordDepthStencil(const wstring & _name)
{
	m_resourceManager->GetResource<DepthStencil>(_name)->StartRecord();
}

void RenderManager::EndDepthStencil(const wstring & _name)
{
	m_resourceManager->GetResource<DepthStencil>(_name)->EndRecord();
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
		if (cam->GetGameObject()->IsActive())
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

void RenderManager::ClearRenderTarget(const wstring & _targetName)
{
	m_resourceManager->GetResource<RenderTarget>(_targetName)->Clear();
}

void RenderManager::ClearDepthStencil(const wstring & _targetName)
{
	m_resourceManager->GetResource<DepthStencil>(_targetName)->Clear();
}

void RenderManager::SetDebugRender(bool _render)
{
	m_isRenderDebug = _render;
}

void RenderManager::SetColliderRender(bool _render)
{
	m_isRenderCollider = _render;
}

