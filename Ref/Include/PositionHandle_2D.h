#pragma once

#ifndef __POSITIONHANDLE2D_H__
#define __POSITIONHANDLE2D_H__

#include "Component.h"
class Transform;
class InputManager;
class PositionHandle_2D :
	public Component
{
public:
	enum DIR { RIGHT, UP };

public:
	struct Desc
	{
		DIR dir;
		Transform* target = nullptr;
	};
	PositionHandle_2D(Desc* _desc);


public:
	virtual void Initialize() override;
	virtual void Update() override;

public:
	void MoveTarget();
	void ResetingPosition();
	void PickHandle(bool _value) { m_isPick = _value; }
	bool CheckPicked();

public:
	Transform* m_target;
	InputManager* m_input;
	DIR m_moveDir;

	bool m_isPick;
};



#endif // !__POSITIONHANDLE2D_H__
