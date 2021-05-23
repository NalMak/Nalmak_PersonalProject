#pragma once
#include "Component.h"
class LynAttachedEffect :
	public Component
{
public:
	struct Desc
	{
		Vector3 scaleAnimation = { 0,0,0 };
		Vector3 rotateAxis = { 0,1,0 };
		float rotateSpeed = 0;

		float lifeTime = 1;
		float emissionPower = 1;
		float yAxisAngle = 0;
		Bezier emissionBezier = Bezier({ 0,1 }, { 0,1 }, { 1,1 }, { 1,1 });

	};
public:
	LynAttachedEffect(Desc* _desc);
	~LynAttachedEffect();

	// Component을(를) 통해 상속됨
	virtual void Initialize() override;
	virtual void Update() override;
	virtual void EachRender() override;

public:
	float Get_LifeTime_Ratio() { return m_lifeTimeRatio; }

private:
	Vector3 m_scaleAnimation;

	Vector3 m_rotateAxis;
	float m_rotateSpeed;
	float m_yAxisAngle;

	float m_lifeTimeRatio;
	float m_currentLifeTime;
	float m_totalLifeTime;

	float m_emissionPower;
	float m_currentEmissionPower;
	Bezier m_emissionBezier;

	Material* m_material;
};

