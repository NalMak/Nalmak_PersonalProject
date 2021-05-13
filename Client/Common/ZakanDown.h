
#include "EnemyState.h"
class ZakanDown :
	public EnemyState
{
public:
	ZakanDown();
	~ZakanDown();

	// EnemyState을(를) 통해 상속됨
	virtual void Initialize() override;
	virtual void EnterState() override;
	virtual void UpdateState() override;
	virtual void ExitState() override;
private:
	float m_downTimer;
};
