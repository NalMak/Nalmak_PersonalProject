#pragma once

#ifndef __AUDIOLISTENER_H__
#define __AUDIOLISTENER_H__

#include "Component.h"
class NALMAK_DLL AudioListener :
	public Component
{
public:
	struct Desc
	{

	};
public:
	AudioListener(Desc* _desc);
	~AudioListener();
private:
	// Component을(를) 통해 상속됨
	virtual void Initialize() override;
	virtual void Update() override;
	virtual void LateUpdate() override;
	virtual void Release() override;
private:
	class SoundManager* m_soundManager;
};

#endif

