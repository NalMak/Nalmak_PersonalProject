#pragma once
#include "PxPhysicsAPI.h"
using namespace physx;

class NalmakPxControllerFilterCallback : public PxControllerFilterCallback
{
public:
	virtual bool filter(const PxController & a, const PxController & b) override;
};

