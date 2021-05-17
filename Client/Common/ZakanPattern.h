#pragma once
#include "EnemyState.h"
class ZakanPattern :
	public EnemyState
{
public:
	ZakanPattern();
	~ZakanPattern();

	// EnemyState을(를) 통해 상속됨
	virtual void Initialize() override;
	virtual void EnterState() override;
	virtual void UpdateState() override;
	virtual void ExitState() override;
private:
	vector<wstring> m_patternList[ZAKAN_PATTERN_MAX];
	UINT m_patternIndex;
	UINT m_phaseIndex;
};

