#include "Animator.h"
#include "MeshRenderer.h"
#include "Material.h"

Animator::Animator(Desc * _desc)
{
	m_isPlay = true;
	m_isSleep = false;
	m_interval = _desc->interval;
	m_loop = _desc->loop;
	m_isNormal = _desc->isNormal;
	m_spriteDiffuseData = ResourceManager::GetInstance()->GetResource<Texture>(_desc->spriteName);
	if (m_isNormal)
		m_spriteNormalData = ResourceManager::GetInstance()->GetResource<Texture>(_desc->spriteName + L"_n");
	m_maxIndex = m_spriteDiffuseData->GetSpriteCount();
	m_currentIndex = _desc->startIndex;
	m_time = TimeManager::GetInstance();
}

Animator::~Animator()
{
}

void Animator::Initialize()
{
}

void Animator::Update()
{
	if (m_isSleep)
		return;

	m_timer += m_time->GetdeltaTime();


	if (m_timer >= m_interval)
	{
		m_timer = m_timer - m_interval;
		//m_timer = 0;
		++m_currentIndex;

		if (m_currentIndex >= m_maxIndex)
		{
			if (m_loop)
				m_currentIndex = 0;
			else
			{
				--m_currentIndex;
				m_isPlay = false;
			}
		}
	}
}

void Animator::LateUpdate()
{
}

void Animator::Release()
{
}

void Animator::Play(wstring _spriteName)
{
	m_isPlay = true;
	m_animName = _spriteName;
	m_spriteDiffuseData = ResourceManager::GetInstance()->GetResource<Texture>(_spriteName);

	if (m_isNormal)
		m_spriteNormalData = ResourceManager::GetInstance()->GetResource<Texture>(_spriteName + L"_n");
	m_currentIndex = 0;
	m_maxIndex = m_spriteDiffuseData->GetSpriteCount();
}

void Animator::Stop()
{
	m_isSleep = true;
}

void Animator::Resume()
{
	m_isSleep = false;
}

IDirect3DBaseTexture9* Animator::GetDiffuseSprite()
{
	return m_spriteDiffuseData->GetTexure(m_currentIndex);
}

IDirect3DBaseTexture9* Animator::GetNormalSprite()
{
	return  m_spriteNormalData->GetTexure(m_currentIndex);
}


