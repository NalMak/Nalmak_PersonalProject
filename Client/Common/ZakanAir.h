
#include "EnemyState.h"
class ZakanAir :
	public EnemyState
{
public:
	ZakanAir();
	~ZakanAir();

	// EnemyState��(��) ���� ��ӵ�
	virtual void Initialize() override;
	virtual void EnterState() override;
	virtual void UpdateState() override;
	virtual void ExitState() override;
private:
	float m_flyTime;
};
