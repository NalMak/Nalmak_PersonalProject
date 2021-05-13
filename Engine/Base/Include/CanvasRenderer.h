#pragma once
#ifndef __CANVASRENDERER_H__
#define __CANVASRENDERER_H__


#include "IRenderer.h"
class UIComponent;
class Texture;
class Animator;
class RenderManager;
class NALMAK_DLL CanvasRenderer :
	public IRenderer
{
public:
	struct Desc
	{
		_CANVAS_GROUP group = 0;
		wstring mtrlName = L"SYS_UI";
		RENDERER_TYPE type = RENDERER_TYPE_CANVAS;
	};
	CanvasRenderer();
	CanvasRenderer(Desc* _desc);

private:
	virtual void Initialize() override;
	virtual void Update() override;
	virtual void LateUpdate() override;
	virtual void Release() override;
public:
	void AddUIComponent(UIComponent* _ui);
	void DeleteUIComponent(UIComponent* _ui);
	virtual void Render(Shader* _shader, ConstantBuffer& _cBuffer, UINT _containerIndex, UINT _subsetIndex) override;
private:
	virtual void BindingStreamSource() override;
private:
	Mesh* m_mesh;
	Material* m_material;
	vector<UIComponent*> m_uiComponents;
public:	// IRenderer을(를) 통해 상속됨
	virtual int GetMaterialCount() override;
	virtual Material * GetMaterial(UINT _containerIndex = 0, UINT _subsetIndex = 0) override;
	virtual void SetMaterial(Material * _material, int _index = 0) override;
	virtual void SetMaterial(const wstring& _mtrlName, int _index = 0) override;

public:
	void UpdateBoundary();
	bool IsCursorOnRect();


	RECT* GetBoundary() { return &m_boundary; }

public:
	const bool& IsInteractive() { return m_interactive; }
	const bool& IsPickingBlocked() { return m_pickingBlocked; }
	virtual void SetInteractive(bool _value);
	virtual void SetBlockPicking(bool _value);


	bool MouseClickDown();
	bool MouseClickPress();
	bool MouseClickUp_InRect();
	bool MouseClickUp_OutRect();

private:
	class InputManager* m_input;
	RenderManager* m_renderManager;

private:
	RECT m_boundary;

	bool m_interactive;
	bool m_pickingBlocked;
};



#endif // !__CANVASRENDERER_H__

