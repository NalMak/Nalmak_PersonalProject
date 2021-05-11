#include "NalmakPxControllerBehaviorCallback.h"
#include "GameObject.h"


NalmakPxControllerBehaviorCallback::NalmakPxControllerBehaviorCallback()
{
}


NalmakPxControllerBehaviorCallback::~NalmakPxControllerBehaviorCallback()
{
}

PxControllerBehaviorFlags NalmakPxControllerBehaviorCallback::getBehaviorFlags(const PxShape & shape, const PxActor & actor)
{
	return (PxControllerBehaviorFlag::Enum)(((GameObject*)actor.userData)->GetLayer());
}

PxControllerBehaviorFlags NalmakPxControllerBehaviorCallback::getBehaviorFlags(const PxController & controller)
{
	return PxControllerBehaviorFlags();
}

PxControllerBehaviorFlags NalmakPxControllerBehaviorCallback::getBehaviorFlags(const PxObstacle & obstacle)
{
	return PxControllerBehaviorFlags();
}
