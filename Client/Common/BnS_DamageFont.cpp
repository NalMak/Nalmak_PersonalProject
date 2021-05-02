#include "stdafx.h"
#include "BnS_DamageFont.h"


BnS_DamageFont::BnS_DamageFont(Desc* _desc)
{
	m_damage = _desc->damage;
	m_isCritical = _desc->isCritical;
	m_animationType = _desc->animationType;

	switch (m_animationType)
	{
	case DAMAGE_FONT_ANIMATION_TYPE_FALLING:
		m_lifeTime = 3.f;
		break;
	case DAMAGE_FONT_ANIMATION_TYPE_EMPHASIS:
		m_lifeTime = 2.f;
		break;
	default:
		break;
	}
}


BnS_DamageFont::~BnS_DamageFont()
{
}

void BnS_DamageFont::Initialize()
{
}

void BnS_DamageFont::Update()
{
	m_lifeTime -= dTime;
	if (m_lifeTime <= 0.f)
	{
		DESTROY(m_gameObject);
		return;
	}
}
