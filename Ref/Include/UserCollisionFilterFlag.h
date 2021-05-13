#pragma once

#include "PxPhysicsAPI.h"

using namespace physx;

PxFilterFlags UserCollisionFilterFlag
(
	PxFilterObjectAttributes _attributes0, PxFilterData _filterData0,
	PxFilterObjectAttributes _attributes1, PxFilterData _filterData1,
	PxPairFlags& _pairFlags, const void* _constantBlock, PxU32 _constantBlockSize)
{
	if (PxFilterObjectIsTrigger(_attributes0) || PxFilterObjectIsTrigger(_attributes1))
	{
		_pairFlags = PxPairFlag::eTRIGGER_DEFAULT
			| PxPairFlag::eNOTIFY_TOUCH_FOUND
			| PxPairFlag::eNOTIFY_TOUCH_LOST;
		return PxFilterFlag::eDEFAULT;
	}
	/*if (PxFilterObjectIsKinematic(_attributes0) || PxFilterObjectIsKinematic(_attributes1))
	{
		_pairFlags = PxPairFlag::eCONTACT_DEFAULT
			| PxPairFlag::eSOLVE_CONTACT
			| PxPairFlag::eDETECT_DISCRETE_CONTACT
			| PxPairFlag::eNOTIFY_CONTACT_POINTS
			| PxPairFlag::eNOTIFY_TOUCH_FOUND
			| PxPairFlag::eNOTIFY_TOUCH_PERSISTS
			| PxPairFlag::eNOTIFY_TOUCH_LOST;

		return PxFilterFlag::eDEFAULT;
	}*/
	
	//_pairFlags = PxPairFlag::eCONTACT_DEFAULT;

	if ((_filterData0.word0 & _filterData1.word1) && (_filterData1.word0 & _filterData0.word1))
	{
		_pairFlags = PxPairFlag::eSOLVE_CONTACT
			| PxPairFlag::eDETECT_DISCRETE_CONTACT
			| PxPairFlag::eNOTIFY_CONTACT_POINTS
			| PxPairFlag::eNOTIFY_TOUCH_FOUND
			| PxPairFlag::eNOTIFY_TOUCH_PERSISTS
			| PxPairFlag::eNOTIFY_TOUCH_LOST;
	}

	return PxFilterFlag::eDEFAULT;

}

