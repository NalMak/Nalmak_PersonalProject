#include "..\Include\Tex2D.h"



Tex2D::Tex2D(wstring _name, Vector4 _color, Vector2 _uvScale)
{
	m_tex = ResourceManager::GetInstance()->GetResource<Texture>(_name)->GetTexure(0);
	m_color = _color;
	m_uvScaling = _uvScale;
}

Tex2D::~Tex2D()
{
}
