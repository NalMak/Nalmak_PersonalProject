#include "NalmakPxEventCallBack.h"
#include "GameObject.h"
#include "PxSimulationEventCallback.h"
#include "PxPhysicsAPI.h"


NalmakPxEventCallBack::NalmakPxEventCallBack()
{
}


NalmakPxEventCallBack::~NalmakPxEventCallBack()
{
}

void NalmakPxEventCallBack::onConstraintBreak(PxConstraintInfo * constraints, PxU32 count)
{
}

void NalmakPxEventCallBack::onWake(PxActor ** actors, PxU32 count)
{
}

void NalmakPxEventCallBack::onSleep(PxActor ** actors, PxU32 count)
{
}

void NalmakPxEventCallBack::onContact(const PxContactPairHeader & pairHeader, const PxContactPair * pairs, PxU32 nbPairs)
{
	for (PxU32 i = 0; i < nbPairs; i++)
	{
		const PxContactPair& cp = pairs[i];

		GameObject* obj0 = (GameObject*)(pairHeader.actors[0]->userData);
		GameObject* obj1 = (GameObject*)(pairHeader.actors[1]->userData);
		
		if (cp.events & PxPairFlag::eNOTIFY_TOUCH_FOUND)
		{
			Collision collision0;
			Collision collision1;
			collision0.hitObj = obj1;
			collision1.hitObj = obj0;
			obj0->OnCollisionEnter(collision0);
			obj1->OnCollisionEnter(collision1);
		}
		if (cp.events & PxPairFlag::eNOTIFY_TOUCH_PERSISTS)
		{
			Collision collision0;
			Collision collision1;
			collision0.hitObj = obj1;
			collision1.hitObj = obj0;
			obj0->OnCollisionEnter(collision0);
			obj1->OnCollisionEnter(collision1);
		}
		if (cp.events & PxPairFlag::eNOTIFY_TOUCH_LOST)
		{
			Collision collision0;
			Collision collision1;
			collision0.hitObj = obj1;
			collision1.hitObj = obj0;

			obj0->OnCollisionExit(collision0);
			obj1->OnCollisionExit(collision1);
		}
	}
}

void NalmakPxEventCallBack::onTrigger(PxTriggerPair * pairs, PxU32 count)
{
	for (PxU32 i = 0; i < count; i++)
	{
		const PxTriggerPair& tp = pairs[i];

		GameObject* obj0 = (GameObject*)(tp.triggerActor->userData);
		GameObject* obj1 = (GameObject*)(tp.otherActor->userData);

		if (!IsValid(obj0) || !IsValid(obj1))
			continue;

		if (!obj0 || !obj1)
			continue;

		

		if (tp.status & PxPairFlag::eNOTIFY_TOUCH_FOUND)
		{
			Collision collision0;
			Collision collision1;
			collision0.hitObj = obj1;
			collision1.hitObj = obj0;

			obj0->OnTriggerEnter(collision0);
			obj1->OnTriggerEnter(collision1);
		}
		if (tp.status & PxPairFlag::eNOTIFY_TOUCH_LOST)
		{
			Collision collision0;
			Collision collision1;
			collision0.hitObj = obj1;
			collision1.hitObj = obj0;

			obj0->OnTriggerExit(collision0);
			obj1->OnTriggerExit(collision1);
		}
	}
}

void NalmakPxEventCallBack::onAdvance(const PxRigidBody * const * bodyBuffer, const PxTransform * poseBuffer, const PxU32 count)
{
}
