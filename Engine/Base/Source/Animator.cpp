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

	if (_desc->meshName != L"")
	{
		auto mesh = ResourceManager::GetInstance()->GetResource<Mesh>(_desc->meshName);
		if (mesh->GetMeshType() == MESH_TYPE_ANIMATION)
		{
			XFileMesh* xMesh = (XFileMesh*)mesh;
			m_animController = AnimationController::CloneAnimationController(xMesh->GetAnimationController(),xMesh->GetRoot());
		}
	}
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
	SAFE_RELEASE(m_animController);
}

void Animator::UpdateEachAnimation()
{
	if (m_animController)
	{
		m_animController->Update();
	}
}

void Animator::Play(wstring _spriteName)
{
	m_isPlay = true;
	m_animName = _spriteName;
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



