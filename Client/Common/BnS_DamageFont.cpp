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
		m_totalLifeTime = 1.f;
		break;
	case DAMAGE_FONT_ANIMATION_TYPE_EMPHASIS:
		m_totalLifeTime = 1.f;
		break;
	default:
		break;
	}
	m_lifeTime = 0;
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


	wstring texName;
	if (m_isCritical)
	{
		m_screenPos = Core::GetInstance()->GetMainCamera()->WorldToScreenPos(m_transform->position + Vector3(0,3,0) + Nalmak_Math::RandDirectionXY());
		for (UINT i = 0; i < numCount; ++i)
		{
			SingleImage::Desc image;
			image.color = { 1,1,1,1.f };
			image.textureName = L"UI_CriticalDamageFont" + to_wstring(damageNum[i]);
			auto damageFont = INSTANTIATE()->AddComponent<CanvasRenderer>()->AddComponent<SingleImage>(&image)->SetPosition(m_screenPos.x + i * 50, m_screenPos.y)->SetScale(50, 50);
			//damageFont->SetParents(m_gameObject);
			m_fontData.emplace_back(damageFont->GetComponent<SingleImage>());
		}
	}
	else
	{
		m_screenPos = Core::GetInstance()->GetMainCamera()->WorldToScreenPos(m_transform->position + Nalmak_Math::RandDirectionXY());

		for (UINT i = 0; i < numCount; ++i)
		{
			SingleImage::Desc image;
			image.color = { 1,1,1,1.f };
			image.textureName = L"UI_DamageFont" + to_wstring(damageNum[i]);
			auto damageFont = INSTANTIATE()->AddComponent<CanvasRenderer>()->AddComponent<SingleImage>(&image)->SetPosition(m_screenPos.x + i * 25, m_screenPos.y)->SetScale(25, 25);
			//damageFont->SetParents(m_gameObject);
			m_fontData.emplace_back(damageFont->GetComponent<SingleImage>());
		}
	}
	if (m_animationType == DAMAGE_FONT_ANIMATION_TYPE_FALLING)
		m_screenVelocity = Vector2(Nalmak_Math::Rand(50.f, 100.f) * Nalmak_Math::Random<int>(1,-1), Nalmak_Math::Rand(-250.f,-200.f));

}

void BnS_DamageFont::Update()
{

	m_lifeTime += dTime;
	if (m_lifeTime >= m_totalLifeTime)
	{
		DestroyFont();
		DESTROY(m_gameObject);
		return;
	}

	float ratio = m_lifeTime / m_totalLifeTime;
	float scale = 0;
	float alphaValue = 1;

	switch (m_animationType)
	{
	case DAMAGE_FONT_ANIMATION_TYPE_FALLING:
	{
		scale = 15.f;
		if (ratio < 0.2f)
		{
			float curRatio = ((0.2f - ratio) / 0.2f);
			alphaValue = curRatio * 0.5f;
		}
		else if(ratio > 0.8f)
		{
			float curRatio = ((ratio - 0.8f) / 0.2f);
			alphaValue = (1 - curRatio)* 0.5f;
		}
		m_screenVelocity.y += 550 * dTime;
		m_screenPos += m_screenVelocity * dTime;
		break;
	}
	case DAMAGE_FONT_ANIMATION_TYPE_EMPHASIS:
	{
		if (ratio < 0.2f)
		{
			float curRatio = ((0.2f - ratio) / 0.2f);
			scale = 40 + (curRatio * 70);
			alphaValue = curRatio;
		}
		else if (ratio < 0.7f)
		{
			scale = 40;
			alphaValue = 1;
		}
		else
		{
			
			float curRatio = ((ratio - 0.7f) / 0.3f);
			scale = 40 + (curRatio * 45);
			alphaValue = (1 - curRatio)* 0.5f;
		}
		break;
	}
	default:
		break;
	}

	size_t size = m_fontData.size();
	alphaValue = alphaValue * 0.95f;
	for (size_t i = 0; i < size; ++i)
	{
		float index = i - size * 0.5f;
		m_fontData[i]->SetPosition(m_screenPos.x  + index * scale * 0.9f, m_screenPos.y,0);
		m_fontData[i]->GetGameObject()->SetScale(scale, scale);
		m_fontData[i]->SetColor(Vector4(1, 1, 1, alphaValue * 0.9f));
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
