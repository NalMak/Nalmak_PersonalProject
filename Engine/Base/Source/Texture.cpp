#include "..\Include\Texture.h"



USING(Nalmak)

Texture::Texture()
{
}


Texture::~Texture()
{
	Release();
}

void Texture::Initialize(wstring _fp)
{
	IDirect3DBaseTexture9* tex = nullptr;
	D3DXIMAGE_INFO info;

	ThrowIfFailed(D3DXGetImageInfoFromFile(_fp.c_str(), &info));
	if (info.ResourceType == D3DRTYPE_CUBETEXTURE)
	{
		ThrowIfFailed(D3DXCreateCubeTextureFromFile(
			m_device,
			_fp.c_str(),
			(LPDIRECT3DCUBETEXTURE9*)&tex
		));
	}
	else if (info.ResourceType == D3DRTYPE_TEXTURE)
	{
		ThrowIfFailed(D3DXCreateTextureFromFileEx(
			m_device,
			_fp.c_str(),
			info.Width,
			info.Height,
			info.MipLevels,
			0,
			info.Format,
			D3DPOOL_MANAGED,
			D3DX_FILTER_LINEAR,
			D3DX_DEFAULT,
			0,
			nullptr,
			nullptr,
			(LPDIRECT3DTEXTURE9*)&tex));
	}
	
	m_textures.emplace_back(tex);
}

void Texture::Release()
{
	for (auto& tex : m_textures)
	{
		SAFE_RELEASE(tex);
	}
	m_textures.clear();
	m_textures.shrink_to_fit();
}

void Texture::SetTexture(IDirect3DBaseTexture9 * _image)
{
	m_textures[0] = _image;
}

IDirect3DBaseTexture9* Texture::GetTexure(size_t _index)
{
	IDirect3DBaseTexture9* tex = nullptr;
	if (_index < m_textures.size())
		tex = m_textures[_index];
	else
		tex = m_textures.back();
	return tex;
}
