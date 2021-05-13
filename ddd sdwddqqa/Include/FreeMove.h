#pragma once

#ifndef __FREEMOVE_H__
#define __FREEMOVE_H__
#include "Component.h"

#pragma region Readme
// ---- 마우스 좌클릭
// object 선택인데 보류,
// + Alt
// 좌우 이동에 따라 roll, pitch 회전 ( 마우스 우클릭 )

// ---- 마우스 우클릭
// 좌우 이동에 따라 roll, pitch 회전
// + Alt
// 화면 줌 인, 아웃 (휠이랑 같음)

// ---- 마우스 휠
// 휠 위로 줌 인, 휠 아래 줌 아웃
// ---- 마우스 휠 클릭 이동
// 현재 보는 방향 기준 x, y축 평면에서 이동

// ---- 키보드 화살표
// 현재 보는 방향 기준 x, z축 평면에서 이동 (Lerp 이동)

// ---- 2번
// perspective, orthogonal 전환


#pragma endregion

class InputManager;
class Camera;

class NALMAK_DLL FreeMove :
	public Component
{
public:
	struct	Desc
	{
		float keyMoveSpeed = 15.f;
		float wheelMoveSpeed = 3.f;
		float mouseSensitive = 0.15f;
		float scrollSpeed = 1.5f;
	};
	FreeMove(Desc* _desc);
private:
	float m_keyMoveSpeed = 0;
	float m_wheelMoveSpeed = 0;
	float m_mouseSensitive = 0;
	float m_scrollSpeed = 0;
public:
	// Component을(를) 통해 상속됨
	virtual void Initialize() override;
	virtual void Update() override;

private:
	void MouseInput();
	void MouseInput_Alt();
	void WheelInput();
	void ArrowInput();

	void Move(Vector3 _dir);
	void Rotate(Vector2 _dir);
	void Zoom(float _dir);
private:
	class InputManager* m_input;
	Camera* m_camera;

	Vector2 m_prevCursorPosition;
	float m_xRot = 0;
	float m_yRot = 0;
};

#endif
