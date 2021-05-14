#pragma once

#ifndef __SINGLEIMAGE_H__
#define __SINGLEIMAGE_H__

#include "IRenderer.h"
#include "UIComponent.h"

class Texture;
class CanvasRenderer;

class NALMAK_DLL SingleImage :
	public UIComponent
{
public:
	struct Desc
	{
		Desc()
		{

		};
		Desc(Vector4 _color, wstring _name)
		{
			color = _color;
			textureName = _name;
		};
		Vector4 color = { 1,1,1,1 };
		wstring textureName = L"default";
	};
	SingleImage(Desc* _desc);

protected:
	virtual void Initialize() override;
	virtual void Update() override;
	virtual void EachRender() override;
	virtual void Release() override;
	virtual void Render(Shader* _shader, Mesh* _mesh) override;
public:
	void SetTexture(wstring _name);
	void SetTexture(IDirect3DBaseTexture9* _tex);
	void SetColor(const Vector4& _color) { m_color = _color; }
	const Vector4& GetColor() { return m_color; }
public:
	IDirect3DBaseTexture9* GetTexture();
	
protected:
	IDirect3DBaseTexture9* m_image;
	CanvasRenderer* m_renderer;
	Vector4 m_color;


};



#endif // !__CANVASRENDERER_H__



//canvas -> localface
