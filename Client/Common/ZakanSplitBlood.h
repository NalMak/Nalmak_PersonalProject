#include "EnemyState.h"

class ZakanSplitBlood :
	public EnemyState
{
public:
	ZakanSplitBlood();
	~ZakanSplitBlood();

	// EnemyState��(��) ���� ��ӵ�
	virtual void Initialize() override;
	virtual void EnterState() override;
	virtual void UpdateState() override;
	virtual void ExitState() override;
};
