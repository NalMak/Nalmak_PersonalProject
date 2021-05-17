#pragma once
#include "Component.h"
class NALMAK_DLL AudioSource :
	public Component
{
public:
	struct Desc
	{
		wstring audioClipName = L"";
		bool playOnAwake = false;
	};
public:
	AudioSource(Desc* _desc);
	~AudioSource();
private:
	// Component을(를) 통해 상속됨
	virtual void Initialize() override;
	virtual void Update() override;
	virtual void Release() override;
public:
	void SetAudioClip(const wstring& _audioClip);
	void Play();
	void Play(const wstring& _audioClip);
	void PlayOneShot(const wstring& _audioClip);
	bool IsPlay();
	void Stop();
	void Pause();
	void Resume();
	AudioClip* GetAudioClip() { return m_audioClip; }
private:
	AudioClip* m_audioClip = nullptr;
	class SoundManager* m_soundManager = nullptr;
	_SOUND_CHANNEL m_channelIndex;
	bool m_isPlay;
	bool m_isPlayOnAwake;
};

