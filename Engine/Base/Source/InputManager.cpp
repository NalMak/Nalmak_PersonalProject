#include "InputManager.h"
#include "DeviceManager.h"
#include "RenderManager.h"

IMPLEMENT_SINGLETON(InputManager)

InputManager::InputManager()
{
}


InputManager::~InputManager()
{
	Release();
}

void InputManager::Initialize(HINSTANCE _hinstance, HWND _hwnd)
{
	ThrowIfFailed(DirectInput8Create(_hinstance, DIRECTINPUT_VERSION, IID_IDirectInput8, (void**)&m_inputSDK, NULL));

	ThrowIfFailed(m_inputSDK->CreateDevice(GUID_SysKeyboard, &m_keyBoard, nullptr));

	ThrowIfFailed(m_keyBoard->SetDataFormat(&c_dfDIKeyboard));

	ThrowIfFailed(m_keyBoard->SetCooperativeLevel(_hwnd, DISCL_BACKGROUND | DISCL_NONEXCLUSIVE));

	ThrowIfFailed(m_keyBoard->Acquire());

	ThrowIfFailed(m_inputSDK->CreateDevice(GUID_SysMouse, &m_mouse, nullptr));

	ThrowIfFailed(m_mouse->SetDataFormat(&c_dfDIMouse));

	ThrowIfFailed(m_mouse->SetCooperativeLevel(_hwnd, DISCL_BACKGROUND | DISCL_NONEXCLUSIVE));

	ThrowIfFailed(m_mouse->Acquire());
	
}

void InputManager::Update()
{
	if (WA_INACTIVE == GetActiveWindow())
		return;

	m_keyBoard->GetDeviceState(256, m_keyState);
	m_mouse->GetDeviceState(sizeof(m_mouseState), &m_mouseState);


	ProcessKeyState();

}

void InputManager::Release()
{
}

LONG InputManager::GetMouseDT(MOUSE_MOVE_STATE _ms)
{
	return *(((LONG*)&m_mouseState) + _ms);
}

bool InputManager::GetKeyDown(KEY_STATE _ks)
{
	return (m_down & _ks) != 0;
}

bool InputManager::GetKeyPress(KEY_STATE _ks)
{
	return (m_press & _ks) != 0;
}

bool InputManager::GetKeyUp(KEY_STATE _ks)
{
	return (m_up & _ks) != 0;
}

Vector2 InputManager::GetMouseMoveDir()
{
	return Vector2((float)GetMouseDT(MOUSE_MOVE_STATE_X), (float)GetMouseDT(MOUSE_MOVE_STATE_Y));
}

Vector2 InputManager::GetMousePosition()
{
	POINT point = {};
	GetCursorPos(&point);
	ScreenToClient(DeviceManager::GetInstance()->GetHWND(), &point);
	return Vector2(float(point.x),float(point.y));
}

void InputManager::ProcessKeyState()
{
	m_press = 0;

	if (m_mouseState.rgbButtons[MOUSE_STATE_LEFT])
		m_press |= KEY_STATE_LEFT_MOUSE;

	if (m_mouseState.rgbButtons[MOUSE_STATE_RIGHT])
		m_press |= KEY_STATE_RIGHT_MOUSE;

	if (m_mouseState.rgbButtons[MOUSE_STATE_WHEEL])
		m_press |= KEY_STATE_WHEEL_MOUSE;

	if (m_keyState[DIK_LEFT])
		m_press |= KEY_STATE_LEFT_ARROW;

	if (m_keyState[DIK_RIGHT])
		m_press |= KEY_STATE_RIGHT_ARROW;

	if (m_keyState[DIK_UP])
		m_press |= KEY_STATE_UP_ARROW;

	if (m_keyState[DIK_DOWN])
		m_press |= KEY_STATE_DOWN_ARROW;

	if (m_keyState[DIK_SPACE])
		m_press |= KEY_STATE_SPACE;

	if (m_keyState[DIK_RETURN])
		m_press |= KEY_STATE_ENTER;

	if (m_keyState[DIK_TAB])
		m_press |= KEY_STATE_TAB;

	if (m_keyState[DIK_LCONTROL])
		m_press |= KEY_STATE_CONTROL;

	if (m_keyState[DIK_RCONTROL])
		m_press |= KEY_STATE_CONTROL;

	if (m_keyState[DIK_BACKSPACE])
		m_press |= KEY_STATE_BACKSPACE;

	if (m_keyState[DIK_ESCAPE])
		m_press |= KEY_STATE_ESCAPE;

	if (m_keyState[DIK_LALT])
		m_press |= KEY_STATE_ALT;
	
	if (m_keyState[DIK_RALT])
		m_press |= KEY_STATE_ALT;

	if (m_keyState[DIK_F1])
		m_press |= KEY_STATE_F1;

	if (m_keyState[DIK_F2])
		m_press |= KEY_STATE_F2;

	if (m_keyState[DIK_F3])
		m_press |= KEY_STATE_F3;

	if (m_keyState[DIK_F4])
		m_press |= KEY_STATE_F4;

	if (m_keyState[DIK_F5])
		m_press |= KEY_STATE_F5;

	if (m_keyState[DIK_F6])
		m_press |= KEY_STATE_F6;

	if (m_keyState[DIK_F7])
		m_press |= KEY_STATE_F7;

	if (m_keyState[DIK_F8])
		m_press |= KEY_STATE_F8;

	if (m_keyState[DIK_F9])
		m_press |= KEY_STATE_F9;

	if (m_keyState[DIK_F10])
		m_press |= KEY_STATE_F10;

	if (m_keyState[DIK_F11])
		m_press |= KEY_STATE_F11;

	if (m_keyState[DIK_F12])
		m_press |= KEY_STATE_F12;

	if (m_keyState[DIK_LSHIFT])
		m_press |= KEY_STATE_SHIFT;

	if (m_keyState[DIK_A])
		m_press |= KEY_STATE_A;

	if (m_keyState[DIK_B])
		m_press |= KEY_STATE_B;

	if (m_keyState[DIK_C])
		m_press |= KEY_STATE_C;

	if (m_keyState[DIK_D])
		m_press |= KEY_STATE_D;

	if (m_keyState[DIK_E])
		m_press |= KEY_STATE_E;

	if (m_keyState[DIK_F])
		m_press |= KEY_STATE_F;

	if (m_keyState[DIK_G])
		m_press |= KEY_STATE_G;

	if (m_keyState[DIK_H])
		m_press |= KEY_STATE_H;

	if (m_keyState[DIK_I])
		m_press |= KEY_STATE_I;

	if (m_keyState[DIK_J])
		m_press |= KEY_STATE_J;

	if (m_keyState[DIK_K])
		m_press |= KEY_STATE_K;

	if (m_keyState[DIK_L])
		m_press |= KEY_STATE_L;

	if (m_keyState[DIK_M])
		m_press |= KEY_STATE_M;

	if (m_keyState[DIK_N])
		m_press |= KEY_STATE_N;

	if (m_keyState[DIK_O])
		m_press |= KEY_STATE_O;

	if (m_keyState[DIK_P])
		m_press |= KEY_STATE_P;

	if (m_keyState[DIK_Q])
		m_press |= KEY_STATE_Q;

	if (m_keyState[DIK_R])
		m_press |= KEY_STATE_R;

	if (m_keyState[DIK_S])
		m_press |= KEY_STATE_S;

	if (m_keyState[DIK_T])
		m_press |= KEY_STATE_T;

	if (m_keyState[DIK_U])
		m_press |= KEY_STATE_U;

	if (m_keyState[DIK_V])
		m_press |= KEY_STATE_V;

	if (m_keyState[DIK_W])
		m_press |= KEY_STATE_W;

	if (m_keyState[DIK_X])
		m_press |= KEY_STATE_X;

	if (m_keyState[DIK_Y])
		m_press |= KEY_STATE_Y;

	if (m_keyState[DIK_Z])
		m_press |= KEY_STATE_Z;

	if (m_keyState[DIK_0])
		m_press |= KEY_STATE_0;

	if (m_keyState[DIK_1])
		m_press |= KEY_STATE_1;

	if (m_keyState[DIK_2])
		m_press |= KEY_STATE_2;

	if (m_keyState[DIK_3])
		m_press |= KEY_STATE_3;

	if (m_keyState[DIK_4])
		m_press |= KEY_STATE_4;

	if (m_keyState[DIK_5])
		m_press |= KEY_STATE_5;

	if (m_keyState[DIK_6])
		m_press |= KEY_STATE_6;

	if (m_keyState[DIK_7])
		m_press |= KEY_STATE_7;

	if (m_keyState[DIK_8])
		m_press |= KEY_STATE_8;

	if (m_keyState[DIK_9])
		m_press |= KEY_STATE_9;


	m_changed = (m_pressed^m_press);		// 0101 ^ 0011 = 0110	// 변화된 부위를 나타냄 
	m_down = (m_press & m_changed);			// 0011 & 0110	= 0010			// 1로 변화된 곳은 Down 스위치를 켜기
	m_up = ((~m_press)&m_changed);			// 1100 & 0110	= 0100		// 0으로 변화된 곳은 Up 스위치를 켜기
	m_pressed = m_press;					// 다음 프레임 준비
}
