#pragma once
#ifndef __LINEMANAGER_H__
#define __LINEMANAGER_H__

#include "Nalmak_Include.h"

class Material;

class GameObject;

class LineManager
{
	DECLARE_SINGLETON(LineManager)
private:
	LineManager();
	~LineManager();
public:
	void Initialize();
	void DrawLine(Vector3 _vec1, Vector3 _vec2, DEBUG_COLOR = DEBUG_COLOR_GREEN);
	void Release();
public:
	void DeleteLines();
	void Toggle();
private:
	vector<GameObject*> m_dynamicLine;
	Material* m_debugMaterial[3];

private:
	const UINT m_maxLineCount = 0;
	UINT m_lineCount;
	bool m_isLineRender;
};

#endif 
