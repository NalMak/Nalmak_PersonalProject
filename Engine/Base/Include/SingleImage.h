#pragma once

#ifndef __SINGLEIMAGE_H__
#define __SINGLEIMAGE_H__

#include "IRenderer.h"

class Texture;
class CanvasRenderer;

class NALMAK_DLL SingleImage :
	public Component
{
public:
	struct Desc
	{
		Vector4 color = { 1,1,1,1 };
		wstring textureName = L"default";
	};
	SingleImage(Desc* _desc);

protected:
	virtual void Initialize() override;
	virtual void Update() override;
	virtual void EachRender() override;

public:
	void SetTexture(wstring _name);
	void SetTexture(IDirect3DBaseTexture9* _tex);
	void SetColor(const Vector4& _color) { m_color = _color; }
	const Vector4& GetColor() { return m_color; }
public:
	IDirect3DBaseTexture9* GetTexture();
	
private:
	Material* m_material;
	IDirect3DBaseTexture9* m_image;
	CanvasRenderer* m_renderer;
	Vector4 m_color;
};



#endif // !__CANVASRENDERER_H__



//canvas -> localface
