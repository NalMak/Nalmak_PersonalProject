#pragma once
#include "IResource.h"
class DepthStencil :
	public IResource
{
public:
	DepthStencil();
	DepthStencil(UINT _width, UINT _height, D3DFORMAT _format);
	~DepthStencil();

	// IResource을(를) 통해 상속됨
	virtual void Initialize(wstring _fp) override;
	virtual void Release() override;
public:
	PDIRECT3DTEXTURE9 GetTexture() const { assert("Render Texture is nullptr!" && m_texture); return m_texture; }
	void StartRecord();
	void EndRecord();
	void Clear();
private:
	PDIRECT3DTEXTURE9 m_texture = nullptr;
	LPDIRECT3DSURFACE9 m_captureSurface = nullptr; // 밉맵 하나당 하나의 서피스
	LPDIRECT3DSURFACE9 m_originSurface = nullptr;
};

