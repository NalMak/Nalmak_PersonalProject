
#include "EnemyState.h"
class ZakanPowerATK :
	public EnemyState
{
public:
	ZakanPowerATK();
	~ZakanPowerATK();
	
	// EnemyState을(를) 통해 상속됨
	virtual void Initialize() override;
	virtual void EnterState() override;
	virtual void UpdateState() override;
	virtual void ExitState() override;

private:
	Vector3 m_jumpTargetPos;
	Vector3 m_landingTargetPos;
	void CreateAttack();
};
