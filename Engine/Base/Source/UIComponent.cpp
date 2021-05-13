#include "UIComponent.h"
#include "CanvasRenderer.h"


UIComponent::UIComponent()
{
}


UIComponent::~UIComponent()
{
}

void UIComponent::Initialize()
{
	auto canvas = GetComponent<CanvasRenderer>();
	assert(L"UI Component must have Canvas Renderer!" && canvas);
	canvas->AddUIComponent(this);
}

void UIComponent::Update()
{
}

void UIComponent::Release()
{
	auto canvas = GetComponent<CanvasRenderer>();
	if(canvas)
		canvas->DeleteUIComponent(this);
}
