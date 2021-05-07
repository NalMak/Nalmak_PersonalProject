#include "CanvasRenderer.h"

#include "RenderManager.h"
#include "ResourceManager.h"
#include "Transform.h"
#include "Animator.h"
#include "SingleImage.h"
#include "Texture.h"
#include "Text.h"
#include "Number.h"
#include "InputManager.h"
CanvasRenderer::CanvasRenderer()
{
}
CanvasRenderer::CanvasRenderer(Desc * _desc)
{
	m_mesh = ResourceManager::GetInstance()->GetResource<Mesh>(L"quadNoneNormal");

	m_material = ResourceManager::GetInstance()->GetResource<Material>(_desc->mtrlName);

	m_type = _desc->type;

}

void CanvasRenderer::Initialize()
{
	IRenderer::Initialize();

	m_renderManager = RenderManager::GetInstance();
	m_input = InputManager::GetInstance();

	if (m_transform->scale.x == 1.f)
		m_transform->scale.x = 100.f;
	if (m_transform->scale.y == 1.f)
		m_transform->scale.y = 100.f;

	m_transform->scale.z = 0.f;

	UpdateBoundary();

}

void CanvasRenderer::Update()
{
	UpdateBoundary();
	if (m_observedPosition != m_transform->position)
	{
		UpdateBoundary();
		m_observedPosition = m_transform->position;
	}
	if (m_observedScale != m_transform->scale)
	{
		UpdateBoundary();
		m_observedScale = m_transform->scale;
	}
}

void CanvasRenderer::LateUpdate()
{
}

void CanvasRenderer::Release()
{
	
}

void CanvasRenderer::Render(Shader* _shader, ConstantBuffer& _cBuffer, UINT _containerIndex, UINT _subsetIndex)
{
	_shader->SetMatrix("g_world", m_transform->GetWorldUIMatrix());

	auto images = GetComponents<SingleImage>();

	for (int i = 0; i < images.size(); ++i)
	{
		_shader->SetTexture("g_mainTex", images[i]->GetTexture());
		_shader->SetVector("g_mainTexColor", images[i]->GetColor());

		_shader->CommitChanges();

		m_mesh->Draw();
	}

	auto texts = GetComponents<Text>();
	for (int i = 0; i < texts.size(); ++i)
	{
		texts[i]->RenderText();
	}
	
}

void CanvasRenderer::BindingStreamSource()
{
	m_mesh->BindingStreamSource(m_material->GetShader()->GetInputLayoutSize());
}



void CanvasRenderer::Render_Text()
{
	Text* text = GetComponent<Text>();

	if (text)
	{
		text->RenderText();
	}
}

void CanvasRenderer::Render_Number()
{
	Number* number = GetComponent<Number>();

	if (number)
	{
		number->RenderText();
	}
}

void CanvasRenderer::UpdateBoundary()
{
	Vector3 position = m_transform->GetWorldPosition();
	m_boundary.left = LONG(position.x - m_transform->scale.x * 0.5f);
	m_boundary.top = LONG(position.y - m_transform->scale.y * 0.5f);
	m_boundary.right = LONG(position.x + m_transform->scale.x * 0.5f);
	m_boundary.bottom = LONG(position.y + m_transform->scale.y * 0.5f);
}

bool CanvasRenderer::IsCursorOnRect()
{
	Vector2 mousePos = m_input->GetMousePosition();

	if (m_boundary.left < mousePos.x &&
		m_boundary.right > mousePos.x &&
		m_boundary.top < mousePos.y &&
		m_boundary.bottom > mousePos.y)
	{
		return true;
	}
	return false;
}



void CanvasRenderer::SetInteractive(bool _value)
{
	m_interactive = _value;
}

void CanvasRenderer::SetBlockPicking(bool _value)
{
	m_pickingBlocked = _value;
}


bool CanvasRenderer::MouseClickDown()
{
	if (!m_interactive)
		return false;

	if (m_input->GetKeyDown(KEY_STATE_LEFT_MOUSE))
	{
		if (IsCursorOnRect())
			return true;
	}

	return false;
}

bool CanvasRenderer::MouseClickPress()
{
	if (!m_interactive)
		return false;

	if (m_input->GetKeyPress(KEY_STATE_LEFT_MOUSE))
	{
		if (IsCursorOnRect())
			return true;
	}

	return false;
}

bool CanvasRenderer::MouseClickUp_InRect()
{
	if (!m_interactive)
		return false;

	if (m_input->GetKeyUp(KEY_STATE_LEFT_MOUSE))
	{
		if (IsCursorOnRect())
			return true;
	}

	return false;
}

bool CanvasRenderer::MouseClickUp_OutRect()
{
	if (!m_interactive)
		return false;

	if (m_input->GetKeyUp(KEY_STATE_LEFT_MOUSE))
	{
		if (!IsCursorOnRect())
			return true;
	}

	return false;
}


int CanvasRenderer::GetMaterialCount()
{
	return 1;
}

Material * CanvasRenderer::GetMaterial(UINT _containerIndex , UINT _subsetIndex )
{
	return m_material;
}

void CanvasRenderer::SetMaterial(Material * _material, int _index)
{
	m_material = _material;
}

void CanvasRenderer::SetMaterial(const wstring& _mtrlName, int _index)
{
	m_material = ResourceManager::GetInstance()->GetResource<Material>(_mtrlName);
}
