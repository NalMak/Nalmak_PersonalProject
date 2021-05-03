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
	vector<UINT> damageNum;
	
	damageNum.emplace_back(m_damage % 1000000 / 100000);
	damageNum.emplace_back(m_damage % 100000 / 10000);
	damageNum.emplace_back(m_damage % 10000 / 1000);
	damageNum.emplace_back(m_damage % 1000 / 100);
	damageNum.emplace_back(m_damage % 10);

	bool digitNum = false;
	for (int i = 6; i >= 0; --i)
	{
		UINT num = pow(10, i + 1);
		UINT num2 = pow(10, i);
		UINT damage = m_damage % num / num2;

		if (!digitNum)
		{
			if (damage != 0)
			{
				digitNum = true;
				damageNum.emplace_back(damage);
			}
		}
		else
		{
			damageNum.emplace_back(damage);
		}
	
		
	}
	UINT numCount = damageNum.size();
	for (UINT i = 0 ; i < numCount; ++i)
	{
		auto damageFont = INSTANTIATE()->AddComponent<CanvasRenderer>()->AddComponent<SingleImage>();
		damageFont->SetParents(m_gameObject);
		m_fontData.emplace_back(damageFont);
	}
}

void BnS_DamageFont::Update()
{
	m_lifeTime -= dTime;
	if (m_lifeTime <= 0.f)
	{
		DestroyFont();
		DESTROY(m_gameObject);
		return;
	}
}

void BnS_DamageFont::DestroyFont()
{
	for (auto& font : m_fontData)
	{
		DESTROY(font);
	}
	m_fontData.clear();
}
