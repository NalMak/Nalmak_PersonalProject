
#pragma once
#include "Component.h"
class LynInfo;

class BnS_MainCamera :
	public Component
{
public:
	struct Desc
	{
		GameObject* player = nullptr;

		float minDistance = 2.f;
		float maxDistance = 60.f;
		float mouseSensitive = 10.f;
		float wheelSensitive = 4.f;
	};
public:
	BnS_MainCamera(Desc* _desc);
	~BnS_MainCamera();

	// Component을(를) 통해 상속됨
	virtual void Initialize() override;
	virtual void Update() override;
	virtual void LateUpdate() override;
	virtual void OnTriggerEnter(Collision& _col) override;
	virtual void OnTriggerStay(Collision& _col) override;
	virtual void OnTriggerExit(Collision& _col) override;
public:
	void LockTarget();
	void UnLockTarget();
	void TurnCamera(float _angle, bool _dir, float _time);
private:
	void Move();
	GameObject* CheckTarget();
private:
	LynInfo* m_player;
	GameObject* m_targetOutline;
	GameObject* m_target;
	Camera* m_cam;
	float m_targetTimer;
private:
	float m_turnTimer;
	float m_turnAngle;
	bool m_isControlingPlayer;
	float m_distance;
	float m_targetDisance;
	float m_minDistance;
	float m_maxDistance;
	Vector2 m_mouseAngle;
	float m_offsetY;
	float m_mouseSensitive;
	float m_wheelSensitive;
	bool m_triggerOn;
	Vector4 m_targetVolume;
};

