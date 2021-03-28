#pragma once

#ifndef __SYSTEMINFOMANAGER_H__
#define __SYSTEMINFOMANAGER_H__

#include "Nalmak_Include.h"
class DeviceManager;

class SystemManager
{
	DECLARE_SINGLETON(SystemManager)
private:
	SystemManager();
	~SystemManager();

public:
	void Update();

	template <typename T>
	void Log(wstring, const T& e)
	{
#ifdef _DEBUG
		if (isRender)
		{
			AutoSortLog("|Type |  ", typeid(T).name(), m_typeColumnLen);
			AutoSortLog("|Name |  ", name, m_nameColumnLen);
			AutoSortLog("|Value|  ", e, m_valueColumnLen);
			cout << "+-----+----------------------------------------------------------------------------------------------------------" << endl;
		}
#endif 

	}

	void Log(wstring name, const Vector3& e);
	void Log(wstring name, const Vector2& e);
private:
	template<typename T>
	void AutoSortLog(wstring title, T name, const int& width)
	{
		cout << fixed << left;
		cout << title;
		cout.fill(' ');
		cout.width(width);
		cout << name;
		cout << endl;
	}
	void DrawLine();
	const int m_typeColumnLen = 100;
	const int m_nameColumnLen = 100;
	const int m_valueColumnLen = 100;
public:
	void SetDraw() { m_isRender = true; }
	wstring GetFPS() { return m_fps; }
private:
	void UpdateFPS();
	void UpdateFrequency();
private:
	bool m_isRender;
	float m_updateTimer;
	DeviceManager* m_device;
	wstring m_fps;
	wstring m_systemMessage;
};

#endif
