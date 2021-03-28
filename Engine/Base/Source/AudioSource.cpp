#include "..\Include\AudioSource.h"
#include "SoundManager.h"
#include "Transform.h"



AudioSource::AudioSource(Desc * _desc)
{
	m_channelIndex = -1;
	m_isPlay = false;
	m_soundManager = SoundManager::GetInstance();

	if(_desc->audioClipName != L"")
		m_audioClip = ResourceManager::GetInstance()->GetResource<AudioClip>(_desc->audioClipName);

	m_isPlayOnAwake = _desc->playOnAwake;
	
}

AudioSource::~AudioSource()
{
	Release();
}

void AudioSource::Initialize()
{
	if(m_isPlayOnAwake)
		Play();
}

void AudioSource::Update()
{
	if (m_isPlay)
	{
		m_soundManager->SetSpeakerPosition(m_channelIndex, m_transform->GetWorldPosition());

		DEBUG_LOG(L"playing channel", m_channelIndex);

		if (!IsPlay())
		{
			IsPlay();
			m_isPlay = false;
			m_soundManager->DeAllocChannel(m_channelIndex);
			m_channelIndex = -1;
		}
	}
	
}

void AudioSource::Release()
{
	m_soundManager->Stop(m_channelIndex);
	m_soundManager->DeAllocChannel(m_channelIndex);

}

void AudioSource::SetAudioClip(const wstring & _audioClip)
{
	m_audioClip = ResourceManager::GetInstance()->GetResource<AudioClip>(_audioClip);
}

void AudioSource::Play()
{
	assert(L"Audio clip is null! " && m_audioClip);

	if (m_isPlay)
	{
		m_soundManager->Play(this, m_channelIndex);
	}
	else
	{
		m_channelIndex = m_soundManager->AllocChannel();
		if (-1 == m_channelIndex)
			return;
		m_soundManager->Play(this, m_channelIndex);

		m_isPlay = true;
	}
	
}

void AudioSource::PlayOneShot(const wstring & _audioClip)
{
	m_soundManager->PlayOneShot(this, _audioClip);
}

bool AudioSource::IsPlay()
{
	return m_soundManager->IsPlay(m_channelIndex);
}

void AudioSource::Stop()
{
	m_soundManager->Stop(m_channelIndex);
}

void AudioSource::Pause()
{
	m_soundManager->Pause(m_channelIndex);
}

void AudioSource::Resume()
{
	m_soundManager->Resume(m_channelIndex);
}
