#include "Animator.h"
#include "MeshRenderer.h"
#include "Material.h"
#include "XFileMesh.h"
#include "Animator.h"
#include "AnimationController.h"

Animator::Animator(Desc * _desc)
{
	m_isPlay = true;
	m_isSleep = false;
	m_interval = _desc->interval;
	m_loop = _desc->loop;
	m_isNormal = _desc->isNormal;

	m_currentIndex = _desc->startIndex;
	m_time = TimeManager::GetInstance();

	if (_desc->mtrlName == L"")
	{
		assert(L"Please Set target Material!" && 0);
	}
	m_timer = 0;
	m_mtrl = ResourceManager::GetInstance()->GetResource<Material>(_desc->mtrlName);
	m_sprite = ResourceManager::GetInstance()->GetResource<Texture>(_desc->spriteName);
	m_currentIndex = 0;
	m_maxIndex = m_sprite->GetSpriteCount();
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

void Animator::EachRender()
{
	m_mtrl->SetTexture("g_mainTex", m_sprite->GetTexure(m_currentIndex));
}

void Animator::Release()
{
}

void Animator::Play(wstring _spriteName)
{
	m_isPlay = true;
	m_sprite = ResourceManager::GetInstance()->GetResource<Texture>(_spriteName);

	m_currentIndex = 0;
	m_maxIndex = m_sprite->GetSpriteCount();
}

void Animator::Stop()
{
	m_isSleep = true;
}

void Animator::Resume()
{
	m_isSleep = false;
}



