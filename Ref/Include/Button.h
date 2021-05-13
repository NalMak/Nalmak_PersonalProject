#pragma once

#ifndef __BUTTON_H__
#define __BUTTON_H__

#include "Component.h"
#include "EventHandler.h"
#include "Event.h"
#include "Nalmak_Include.h"


class Text;
class Texture;
class CanvasRenderer;
class ResourceManager;
class  NALMAK_DLL Button :
	public Component
{
public:
	struct Desc
	{
		GameObject* targetText = nullptr;
		EventHandler eventFunc = nullptr;

		wstring allImage = L"";
		wstring normalImage = L"UIWhite";
		wstring highlightImage = L"UIRed";
		wstring pressedImage = L"UIBlue";
		wstring disableImage = L"UIGrey";
	};
	Button(Desc* _desc);
protected:
	virtual void Initialize() override;
	virtual void Update() override;
	virtual void LateUpdate() override;
	virtual void Release() override;
	virtual void OnEnable() override;

public:
	void ChangeTransition(BUTTON_TRANSITION _transition);
	void ChangeState(BUTTON_STATE _state);

	void ChangeAllColor(Vector4 _color);
	void ChangeNormalColor(Vector4 _color) { m_normalColor = _color; }
	void ChangeNormalColor(float _r, float _g, float _b, float _a) { m_normalColor = Vector4(_r,_g,_b,_a); }
	void ChangeHighlightColor(Vector4 _color) { m_highlightColor = _color; }
	void ChangeHighlightColor(float _r, float _g, float _b, float _a) { m_highlightColor = Vector4(_r, _g, _b, _a); }
	void ChangePressedColor(Vector4 _color) { m_pressedColor = _color; }
	void ChangePressedColor(float _r, float _g, float _b, float _a) { m_pressedColor = Vector4(_r, _g, _b, _a); }
	void ChangeDisableColor(Vector4 _color) { m_disableColor = _color; }
	void ChangeDisableColor(float _r, float _g, float _b, float _a) { m_disableColor = Vector4(_r, _g, _b, _a); }

	void ChangeAllTexture(IDirect3DBaseTexture9* _tex);
	void ChangeAllTexture(wstring _name);
	void ChangeNormalTexture(wstring _name);
	void ChangeHighlightTexture(wstring _name);
	void ChangePressedTexture(wstring _name);
	void ChangeDisableTexture(wstring _name);
	
public:
	const Vector4* GetCurrentColor() { return m_targetColor; }
	BUTTON_TRANSITION GetTransition() { return m_currentTransition; }

	void SetTransition(BUTTON_TRANSITION _tr) { m_currentTransition = _tr; }
	void SetText(const wstring& _text);
	void SetTextObject(GameObject* _text);
public:
	void AddEventHandler(EventHandler _eventFunc);

	void GetEventHandler(int _index);
	void RemoveEventHandler(EventHandler _eventFunc);
	void RemoveEventHandler(int _index);

	void ResetEvent();
	void ResetEvent(EventHandler _eventFunc);

protected:
	Event m_event;


	ResourceManager* m_resource;
	CanvasRenderer* m_renderer;
	GameObject* m_text;

protected:
	BUTTON_TRANSITION m_currentTransition;
	BUTTON_STATE m_currentState;

	IDirect3DBaseTexture9** m_targetImage = nullptr;
	Vector4* m_targetColor = nullptr;

	Vector4 m_normalColor;
	Vector4 m_highlightColor;
	Vector4 m_pressedColor;
	Vector4 m_disableColor;

	IDirect3DBaseTexture9* m_normalImage = nullptr;
	IDirect3DBaseTexture9* m_highlightImage = nullptr;
	IDirect3DBaseTexture9* m_pressedImage = nullptr;
	IDirect3DBaseTexture9* m_disableImage = nullptr;
};

#endif