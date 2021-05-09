#pragma once
#include "LynState.h"
class LynSideDashE :
	public LynState
{
public:
	LynSideDashE();
	~LynSideDashE();

	// LynState��(��) ���� ��ӵ�
	virtual void Initialize() override;
	virtual void EnterState() override;
	virtual void UpdateState() override;
	virtual void ExitState() override;
private:
	Vector3 m_targetPos1;
	Vector3 m_targetPos2;
};

