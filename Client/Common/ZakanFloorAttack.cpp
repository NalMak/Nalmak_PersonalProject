#include "stdafx.h"
#include "ZakanFloorAttack.h"


ZakanFloorAttack::ZakanFloorAttack(Desc * desc)
{
}

ZakanFloorAttack::~ZakanFloorAttack()
{
}

void ZakanFloorAttack::Initialize()
{
	m_explosionTimer = 3.f;
}

void ZakanFloorAttack::Update()
{
	m_explosionTimer -= dTime;

	if (m_explosionTimer < 0)
		DESTROY(m_gameObject);


}
	
