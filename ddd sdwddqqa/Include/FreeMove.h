#pragma once

#ifndef __FREEMOVE_H__
#define __FREEMOVE_H__
#include "Component.h"

#pragma region Readme
// ---- ���콺 ��Ŭ��
// object �����ε� ����,
// + Alt
// �¿� �̵��� ���� roll, pitch ȸ�� ( ���콺 ��Ŭ�� )

// ---- ���콺 ��Ŭ��
// �¿� �̵��� ���� roll, pitch ȸ��
// + Alt
// ȭ�� �� ��, �ƿ� (���̶� ����)

// ---- ���콺 ��
// �� ���� �� ��, �� �Ʒ� �� �ƿ�
// ---- ���콺 �� Ŭ�� �̵�
// ���� ���� ���� ���� x, y�� ��鿡�� �̵�

// ---- Ű���� ȭ��ǥ
// ���� ���� ���� ���� x, z�� ��鿡�� �̵� (Lerp �̵�)

// ---- 2��
// perspective, orthogonal ��ȯ


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
	// Component��(��) ���� ��ӵ�
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
