#pragma once
#include "Component.h"
class LynAttachedEffect;
class LynSpinSlashEffect :
	public Component
{
public:
	struct Desc
	{
		GameObject* host;
		string boneName;
	};
public:
	LynSpinSlashEffect(Desc* _desc);
	~LynSpinSlashEffect();

	// Component��(��) ���� ��ӵ�
	virtual void Initialize() override;
	virtual void Update() override;
private:
	Matrix* m_boneMatrix;
	Transform* m_host;

	LynAttachedEffect* m_lynAttachedEffect;
	//Bezier m_lotateSpeedBezier;

	Material* m_mtrl;
};

