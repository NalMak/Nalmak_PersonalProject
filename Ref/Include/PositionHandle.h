#pragma once

#ifndef __POSITIONHANDLE_H__
#define __POSITIONHANDLE_H__

#include "Component.h"
class Camera;
class Transform;
class InputManager;
class NALMAK_DLL PositionHandle :
	public Component
{
public:
	enum DIR { RIGHT, UP, FORWARD };
public:
	struct Desc
	{
		DIR dir;
	};
	PositionHandle(Desc* _desc);


public:
	virtual void Initialize() override;
	virtual void Update() override;

public:
	void MoveTarget();
	void PickHandle(bool _value) { m_isPick = _value; }
	bool CheckPicked() { return m_isPick; }

public:
	Transform* m_target;
	InputManager* m_input;
	Camera* m_camera;
	DIR m_moveDir;

	bool m_isPick;
};



#endif // !__POSITIONHANDLE_H__