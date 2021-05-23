
#include "EnemyState.h"
class ZakanStun :
	public EnemyState
{
public:
	ZakanStun();
	~ZakanStun();

	// EnemyState을(를) 통해 상속됨
	virtual void Initialize() override;
	virtual void EnterState() override;
	virtual void UpdateState() override;
	virtual void ExitState() override;
private:
	float m_stunTimer;
};
