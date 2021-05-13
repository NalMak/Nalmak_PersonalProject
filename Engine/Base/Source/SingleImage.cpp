#include "..\Include\SingleImage.h"
#include "ResourceManager.h"
#include "CanvasRenderer.h"

SingleImage::SingleImage(Desc * _desc)
{
	m_image =
		ResourceManager::GetInstance()->
		GetResource<Texture>(_desc->textureName)->GetTexure(0);
	m_color = _desc->color;
}

void SingleImage::Initialize()
{
	m_material = GetComponent<CanvasRenderer>()->GetMaterial();
}

void SingleImage::Update()
{

}

void SingleImage::EachRender()
{
	m_material->SetTexture("g_mainTex", m_image);
	m_material->SetVector("g_mainTexColor", m_color);
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
