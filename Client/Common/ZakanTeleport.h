
#include "EnemyState.h"
class ZakanTeleport :
	public EnemyState
{
public:
	ZakanTeleport();
	~ZakanTeleport();

	// EnemyState��(��) ���� ��ӵ�
	virtual void Initialize() override;
	virtual void EnterState() override;
	virtual void UpdateState() override;
	virtual void ExitState() override;
private:
	Vector3 m_landingTarget;
	Vector3 m_jumpPos;
	Vector3 m_flyVelocity;
	float m_flyLength;
	float m_flyTime;

	float m_exceptTime;
};
