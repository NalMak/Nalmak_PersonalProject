
#include "EnemyState.h"
class ZakanPowerATK :
	public EnemyState
{
public:
	ZakanPowerATK();
	~ZakanPowerATK();

	// EnemyState��(��) ���� ��ӵ�
	virtual void Initialize() override;
	virtual void EnterState() override;
	virtual void UpdateState() override;
	virtual void ExitState() override;
};
