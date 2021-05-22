#pragma once
#include "LynState.h"
class LynStateThunderbolt :
	public LynState
{
public:
	LynStateThunderbolt();
	~LynStateThunderbolt();

	// LynState��(��) ���� ��ӵ�
	virtual void Initialize() override;
	virtual void EnterState() override;
	virtual void UpdateState() override;
	virtual void ExitState() override;
private:
	Vector3 m_direction;
	Vector3 m_startPos;
	float m_targetDistance;
	float m_traveledDistance;
};

