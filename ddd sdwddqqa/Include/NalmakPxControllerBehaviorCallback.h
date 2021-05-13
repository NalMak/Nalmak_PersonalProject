#pragma once
#include "PxPhysicsAPI.h"
using namespace physx;

class NalmakPxControllerBehaviorCallback : public PxControllerBehaviorCallback
{
public:
	NalmakPxControllerBehaviorCallback();
	~NalmakPxControllerBehaviorCallback();

	// PxControllerBehaviorCallback을(를) 통해 상속됨
	virtual PxControllerBehaviorFlags getBehaviorFlags(const PxShape & shape, const PxActor & actor) override;
	virtual PxControllerBehaviorFlags getBehaviorFlags(const PxController & controller) override;
	virtual PxControllerBehaviorFlags getBehaviorFlags(const PxObstacle & obstacle) override;
};

