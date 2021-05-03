#pragma once
#include "Component.h"
class BnS_MainCamera :
	public Component
{
public:
	struct Desc
	{
		GameObject* player = nullptr;

		float minDistance = 5.f;
		float maxDistance = 45.f;
		float mouseSensitive = 10.f;
		float wheelSensitive = 4.f;
	};
public:
	BnS_MainCamera(Desc* _desc);
	~BnS_MainCamera();

	// Component을(를) 통해 상속됨
	virtual void Initialize() override;
	virtual void Update() override;
	virtual void OnTriggerEnter(Collision& _col) override;
	virtual void OnTriggerStay(Collision& _col) override;
	virtual void OnTriggerExit(Collision& _col) override;
private:
	GameObject* m_player;
	float m_distance;
	float m_targetDisance;
	float m_minDistance;
	float m_maxDistance;
	Vector2 m_mouseAngle;
	float m_offsetY;
	float m_mouseSensitive;
	float m_wheelSensitive;
	bool m_triggerOn;
};

