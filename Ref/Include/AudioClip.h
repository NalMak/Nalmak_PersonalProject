#pragma once

#ifndef __AUDIOCLIP_H__
#define __AUDIOCLIP_H__

#include "IResource.h"
#include "Nalmak_Include.h"
struct FMOD_SOUND;
struct FMOD_SYSTEM;
struct  FMOD_CHANNEL;

class AudioClip : public IResource
{
	friend class SoundManager;
	friend class ResourceManager;
public:
	AudioClip();
	~AudioClip();
private:
	// IResource을(를) 통해 상속됨
	virtual void Initialize(wstring _fp) override;
	virtual void Release() override;
private:
	FMOD_SOUND* m_audio;
public:
	float volume;
	float pitch;
	bool loop;
	float minDistance;
	float maxDistance;
	_SOUND_CHANNEL channel;
};

#endif