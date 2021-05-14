#include "..\Include\SingleImage.h"
#include "ResourceManager.h"
#include "CanvasRenderer.h"
#include "Transform.h"

SingleImage::SingleImage(Desc * _desc)
{
	m_image =
		ResourceManager::GetInstance()->
		GetResource<Texture>(_desc->textureName)->GetTexure(0);
	m_color = _desc->color;
}

void SingleImage::Initialize()
{
	UIComponent::Initialize();
}

void SingleImage::Update()
{

}

void SingleImage::EachRender()
{
}

void SingleImage::Release()
{
	UIComponent::Release();
}

void SingleImage::SetTexture(wstring _name)
{
	m_image = ResourceManager::GetInstance()->GetResource<Texture>(_name)->GetTexure(0);

}

void SingleImage::SetTexture(IDirect3DBaseTexture9 * _tex)
{
	m_image = _tex;
}


IDirect3DBaseTexture9* SingleImage::GetTexture()
{
	return m_image;
}

void SingleImage::Render(Shader* _shader, Mesh* _mesh)
{
	_shader->SetTexture("g_mainTex", m_image);
	_shader->SetVector("g_mainTexColor", m_color);

	_shader->SetMatrix("g_world", m_transform->GetWorldUIMatrix());

	_shader->CommitChanges();
	_mesh->Draw();
}
