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
		vector<int> a;
		if (cp.events & PxPairFlag::eNOTIFY_TOUCH_FOUND)
		{
			obj0->OnCollisionEnter(a);
			obj1->OnCollisionEnter(a);
		}
		if (cp.events & PxPairFlag::eNOTIFY_TOUCH_PERSISTS)
		{
			obj0->OnCollisionStay(a);
			obj1->OnCollisionStay(a);
		}
		if (cp.events & PxPairFlag::eNOTIFY_TOUCH_LOST)
		{
			obj0->OnCollisionExit(a);
			obj1->OnCollisionExit(a);
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
		vector<int> a;
		if (tp.status & PxPairFlag::eNOTIFY_TOUCH_FOUND)
		{
			obj0->OnTriggerEnter(a);
			obj1->OnTriggerEnter(a);
		}
		if (tp.status & PxPairFlag::eNOTIFY_TOUCH_LOST)
		{
			obj0->OnTriggerExit(a);
			obj1->OnTriggerExit(a);
		}
	}
}

void NalmakPxEventCallBack::onAdvance(const PxRigidBody * const * bodyBuffer, const PxTransform * poseBuffer, const PxU32 count)
{
}
