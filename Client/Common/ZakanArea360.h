
#include "EnemyState.h"
class ZakanArea360 :
	public EnemyState
{
public:
	ZakanArea360();
	~ZakanArea360();

	// EnemyState��(��) ���� ��ӵ�
	virtual void Initialize() override;
	virtual void EnterState() override;
	virtual void UpdateState() override;
	virtual void ExitState() override;
};
