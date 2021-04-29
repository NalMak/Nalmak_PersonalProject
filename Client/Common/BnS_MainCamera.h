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
		float maxDistance = 25.f;
		float mouseSensitive = 10.f;
		float wheelSensitive = 0.5f;
	};
public:
	BnS_MainCamera(Desc* _desc);
	~BnS_MainCamera();

	// Component을(를) 통해 상속됨
	virtual void Initialize() override;
	virtual void Update() override;
	virtual void OnTriggerEnter(Collisions& _col) override;
	virtual void OnTriggerStay(Collisions& _col) override;
	virtual void OnTriggerExit(Collisions& _col) override;
private:
	GameObject* m_player;
	float m_distance;
	float m_minDistance;
	float m_maxDistance;
	Vector2 m_mouseAngle;
	Vector3 m_offset;
	float m_mouseSensitive;
	float m_wheelSensitive;
	bool m_triggerOn;
};

