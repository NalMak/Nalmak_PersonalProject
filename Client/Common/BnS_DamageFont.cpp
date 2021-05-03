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
	m_lifeTime = 2.f;
}


BnS_DamageFont::~BnS_DamageFont()
{
}

void BnS_DamageFont::Initialize()
{
	

	vector<UINT> damageNum;
	

	bool digitNum = false;
	for (int i = 6; i >= 0; --i)
	{
		UINT num = (UINT)pow(10, i + 1);
		UINT num2 = (UINT)pow(10, i);
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
	UINT numCount = (UINT)damageNum.size();

	m_velocity = { Nalmak_Math::Rand(-1.f,1.f),Nalmak_Math::Rand(0.f,-3.f),0 };
	m_velocity = m_velocity * 100.f;

	wstring texName;
	Vector2 screenPos;
	if (m_isCritical)
	{
		screenPos = Core::GetInstance()->GetMainCamera()->WorldToScreenPos(m_transform->position + Vector3(0,3,0));
		for (UINT i = 0; i < numCount; ++i)
		{
			SingleImage::Desc image;
			image.color = { 1,1,1,1.f };
			image.textureName = L"UI_CriticalDamageFont" + to_wstring(damageNum[i]);
			auto damageFont = INSTANTIATE()->AddComponent<CanvasRenderer>()->AddComponent<SingleImage>(&image)->SetPosition(screenPos.x + i * 50, screenPos.y)->SetScale(50, 50);
			//damageFont->SetParents(m_gameObject);
			m_fontData.emplace_back(damageFont->GetComponent<SingleImage>());
		}
	}
	else
	{
		screenPos = Core::GetInstance()->GetMainCamera()->WorldToScreenPos(m_transform->position);

		for (UINT i = 0; i < numCount; ++i)
		{
			SingleImage::Desc image;
			image.color = { 1,1,1,1.f };
			image.textureName = L"UI_DamageFont" + to_wstring(damageNum[i]);
			auto damageFont = INSTANTIATE()->AddComponent<CanvasRenderer>()->AddComponent<SingleImage>(&image)->SetPosition(screenPos.x + i * 25, screenPos.y)->SetScale(25, 25);
			//damageFont->SetParents(m_gameObject);
			m_fontData.emplace_back(damageFont->GetComponent<SingleImage>());
		}
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

	float alpha = m_lifeTime / 3.f;
	for (auto& num : m_fontData)
	{
		num->SetColor(Vector4(1, 1, 1, alpha));
	}
	//m_velocity += Vector3(0, 100, 0) * dTime;
	//m_transform->position += m_velocity * dTime * 100;
}

void BnS_DamageFont::DestroyFont()
{
	for (auto& font : m_fontData)
	{
		DESTROY(font->GetGameObject());
	}
	m_fontData.clear();
}
