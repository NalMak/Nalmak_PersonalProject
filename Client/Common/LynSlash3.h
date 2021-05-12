#pragma once
#include "LynState.h"
class LynSlash3 :
	public LynState
{
public:
	LynSlash3();
	~LynSlash3();

	// LynState��(��) ���� ��ӵ�
	virtual void Initialize() override;
	virtual void EnterState() override;
	virtual void UpdateState() override;
	virtual void ExitState() override;
private:
	bool m_isCombo;
	Texture* m_slash1Tex;
};

