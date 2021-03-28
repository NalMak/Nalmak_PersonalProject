#include "..\Include\AudioListener.h"
#include "SoundManager.h"
#include "Transform.h"


AudioListener::AudioListener(Desc * _desc)
{
}

AudioListener::~AudioListener()
{
}

void AudioListener::Initialize()
{
	m_soundManager = SoundManager::GetInstance();

	m_soundManager->AddAudioListener(this);
}

void AudioListener::Update()
{
}

void AudioListener::LateUpdate()
{
	m_soundManager->SetListenerPosition(m_transform->GetWorldMatrix());
}

void AudioListener::Release()
{
	m_soundManager->DeleteAudioListener(this);
}
