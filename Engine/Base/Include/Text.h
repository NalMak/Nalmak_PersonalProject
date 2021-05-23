#pragma once

#ifndef __TEXT_H__
#define __TEXT_H__


#include "Component.h"
#include "UIComponent.h"

class CanvasRenderer;
class NALMAK_DLL Text :
	public UIComponent
{
	friend class RenderManager;
public:
	struct Desc
	{
		UINT width;
		UINT height = 21;
		UINT weight = 500; // 0 ~ 1000
		DWORD option = DT_CENTER | DT_WORDBREAK;
		const TCHAR* fontName = L"";
		wstring text = L"default";
		RECT boundary = { 0,0,200,50 };
		D3DCOLOR color = D3DCOLOR_RGBA(255, 255, 255, 255);
		bool	isKorean = true;
	};
	Text(Desc* _desc);
private:
	virtual void Initialize() override;
	virtual void Update() override;
	virtual void LateUpdate() override;
	virtual void PreRender() override;
	virtual void Release() override;
	virtual void Render(Shader * _shader, Mesh * _mesh) override;
public:

	void SetText(wstring _text) { m_text = _text; }
	void SetColor(const D3DXCOLOR& _color) { m_color = _color; }
	void SetAlpha(float _alpha) { m_color.a = _alpha; }
	void SetBoundary(RECT* _rc);


private:
	LPD3DXFONT m_font = nullptr;
	PDIRECT3DDEVICE9 m_device = nullptr;
	RenderManager* m_render = nullptr;

private:
	RECT m_boundary;
	UINT m_width;
	UINT m_height;
	UINT m_weight;
	DWORD m_option;
	D3DXCOLOR m_color;
	const TCHAR* m_fontName;
	wstring m_text;
	bool	m_isKorean;


};

#endif // !__TEXT_H__
