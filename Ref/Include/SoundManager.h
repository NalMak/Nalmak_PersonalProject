#pragma once
#include "Nalmak_Include.h"
#include "AudioSource.h"

#ifndef __SOUNDMANAGER_H__
#define __SOUNDMANAGER_H__

class AudioClip;
class AudioListener;
class SoundManager
{
	DECLARE_SINGLETON(SoundManager)
public:
	SoundManager();
	~SoundManager();
public:
	void Initialize();
	void Update();
	void Release();
public:
	void Play(AudioSource*  _clip, const _SOUND_CHANNEL& _channel);
	void PlayOneShot(AudioSource* _source, AudioClip* _audioClip);
	void PlayOneShot(AudioSource * _source,const wstring& _clipName);
	bool IsPlay(const _SOUND_CHANNEL& _channel);
	void Stop(const _SOUND_CHANNEL& _channel);
	void Pause(const _SOUND_CHANNEL& _channel);
	void Resume(const _SOUND_CHANNEL& _channel);
//public:
	//void Play(const wstring& _clip, const int& _channel);
//	void Play(const wstring& pSoundKey);
//
//	bool IsPlay(_SOUND_CHANNEL  _channel);
//	void PlayEffect(const wstring& pSoundKey);
//	void PlayEffect(AudioClip*  _clip);
//	void Pause(_SOUND_CHANNEL  _channel);
//	void Resume(_SOUND_CHANNEL  _channel);
//	void Stop(_SOUND_CHANNEL  _channel);
//	
//	void SetVolumeRatio(_SOUND_CHANNEL _channel, float _ratio);
//	void SetVolume(_SOUND_CHANNEL _channel, float _volume);
//
//	void Pause();
//	void Resume();
//	void Stop();
//	void SetMaterVolume(float _v);
//	bool CompareCurrentClip(_SOUND_CHANNEL  _channel, const wstring& pSoundKey);
	//AudioClip* GetAudioClip(const wstring& _pSoundKey);
	void AddAudioListener(AudioListener* _listener);
	void DeleteAudioListener(AudioListener* _listener);
	void SetListenerPosition(const Matrix& _worldMat);
	void SetSpeakerPosition(_SOUND_CHANNEL _channel, const Vector3& _pos);
private:
	int GetAvailableChannel();
	// Store all sound file from file path at SoundList
public:
	FMOD_SYSTEM* GetFModSystem() { return m_pSystem; }
public:
	_SOUND_CHANNEL AllocChannel();
	void DeAllocChannel(_SOUND_CHANNEL _channel);
private:
	int m_channelCount = 0;
	pair<bool, FMOD_CHANNEL*> m_pChannelArr[SOUND_CHANNEL_COUNT_MAX];

	FMOD_SYSTEM* m_pSystem = nullptr;
	list<int> m_publicSoundPriority;
private:
	float m_volumeRatio; // [0~1]
	bool m_b3DSound;
private:
	class ResourceManager* m_resourceManager;
	class AudioListener* m_listener;
};

#endif

