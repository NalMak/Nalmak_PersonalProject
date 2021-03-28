#include "..\Include\Text.h"
#include "RenderManager.h"
#include "Transform.h"
#include "CanvasRenderer.h"

Text::Text(Desc * _desc)
{
	m_width = _desc->width;
	m_height = _desc->height;
	m_weight = _desc->weight;
	m_weight = Nalmak_Math::Clamp<UINT>(m_weight, 0, 1000);
	m_fontName = _desc->fontName;
	m_option = _desc->option;
	m_text = _desc->text;
	m_color = _desc->color;
	m_Hangul = _desc->Hangul;
	m_boundary = _desc->boundary;
}

void Text::Initialize()
{
	
	m_renderer = GetComponent<CanvasRenderer>();

	m_render = RenderManager::GetInstance();
	m_device = DeviceManager::GetInstance()->GetDevice();

	D3DXFONT_DESCW fontDesc;
	ZeroMemory(&fontDesc, sizeof(D3DXFONT_DESCW));
	fontDesc.Width = m_width;
	fontDesc.Height = m_height;
	fontDesc.Weight = m_weight;
	if(m_Hangul)
	{fontDesc.CharSet = HANGUL_CHARSET;}
	lstrcpy(fontDesc.FaceName, m_fontName);
	ThrowIfFailed(D3DXCreateFontIndirect(m_device, &fontDesc, &m_font));

}

void Text::Update()
{
}

void Text::LateUpdate()
{
}

void Text::PreRender()
{
}

void Text::RenderText()
{
	auto pos = m_transform->GetWorldPosition();
	RECT rc = {
		(LONG)pos.x + m_boundary.left,
		(LONG)pos.y + m_boundary.top,
		(LONG)pos.x + m_boundary.right,
		(LONG)pos.y + m_boundary.bottom
	};
	m_font->DrawTextW(
		nullptr,
		m_text.c_str(),
		-1,
		&rc,
		m_option,
		m_color
	);
}



void Text::Release()
{
	if (m_font)
	{
		m_font->Release();
		m_font = nullptr;
	}
}

