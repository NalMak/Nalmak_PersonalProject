#pragma once
#include "LynState.h"
class LynSlash2 :
	public LynState
{
public:
	LynSlash2();
	~LynSlash2();

	// LynState��(��) ���� ��ӵ�
	virtual void Initialize() override;
	virtual void EnterState() override;
	virtual void UpdateState() override;
	virtual void ExitState() override;
private:
	bool m_isCombo;
	Texture* m_slash3Tex;
	Texture* m_slash1Tex;
};

