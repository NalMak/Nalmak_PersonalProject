#include "EnemyState.h"

class ZakanSmash :
	public EnemyState
{
public:
	ZakanSmash();
	~ZakanSmash();

	// EnemyState��(��) ���� ��ӵ�
	virtual void Initialize() override;
	virtual void EnterState() override;
	virtual void UpdateState() override;
	virtual void ExitState() override;
};
