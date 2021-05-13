#pragma once

#ifndef __RENDERTARGET_H__
#define __RENDERTARGET_H__

#include "IResource.h"

//https://m.blog.naver.com/PostView.nhn?blogId=sorkelf&logNo=40156769867&proxyReferer=https:%2F%2Fwww.google.com%2F
// 멀티패스 렌더링 설명

BEGIN(Nalmak)
class NALMAK_DLL RenderTarget :
	public IResource
{
	friend class ResourceManager;
public:
	RenderTarget();
	~RenderTarget();
private:
	RenderTarget(UINT _width, UINT _height, D3DFORMAT _format, const D3DCOLOR& _color);
private:
	// IResource을(를) 통해 상속됨
	virtual void Initialize(wstring _fp) override;
	virtual void Release() override;

public:
	PDIRECT3DTEXTURE9 GetTexture() const { assert("Render Texture is nullptr!" && m_texture); return m_texture; }
	void Clear();
	void StartRecord(UINT _index);
	void EndRecord();
	UINT GetTargetIndex() { return m_targetIndex; }
	D3DCOLOR GetColor() { return m_color; }
private:
	PDIRECT3DTEXTURE9 m_texture = nullptr;
	LPDIRECT3DSURFACE9 m_captureSurface = nullptr; // 밉맵 하나당 하나의 서피스
	LPDIRECT3DSURFACE9 m_originSurface = nullptr;
	UINT m_targetIndex;
	D3DCOLOR m_color;
};
END
#endif // !__RENDERTARGET_H__
