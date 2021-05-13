#pragma once

#ifndef __SYSTEMINFO_H__
#define __SYSTEMINFO_H__

#include "Component.h"
class SystemManager;
class Text;
class DebugManager;
class NALMAK_DLL SystemInfo :
	public Component
{
public:
	struct Desc
	{
		Vector2 fontSize = { 6,12 };
	};
public:
	SystemInfo(Desc* _desc);
	~SystemInfo();
	// Component을(를) 통해 상속됨
	virtual void Initialize() override;
	virtual void Update() override;
	virtual void PreRender()override;
private:
	Text* m_text;
	SystemManager* m_systemInfo;
	DebugManager* m_debugLog;
	wstring m_info;

	Vector2 m_fontSize;
};

#endif
