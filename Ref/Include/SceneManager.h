#pragma once
#ifndef __SCENEMANAGER_H__
#define __SCENEMANAGER_H__

#include "Nalmak_Include.h"
#include "Scene.h"


class SceneManager
{
	DECLARE_SINGLETON(SceneManager)
private:
	SceneManager() = default;
	~SceneManager();
public:
	HRESULT Initialize();
	void Update();
	void LateUpdate();
	void Release();
	void PreRender();
	void Render();
	void PostRender();
	void DeleteObject();
public:
	void SetFirstScene(const wstring& _name);
	void Load(const wstring& _name, SCENE_LOAD_TYPE _loadType);
	void AddScene(const wstring& _name, Scene*);
	bool CompareCurrentScene(const wstring& _name);
	Scene* Find_Scene_Name(const wstring& _name);
private:
	void CleanUpScene();
	void LoadResource();
	void LoadNextScene();
	unordered_map<wstring, Scene*> m_sceneList;
	Scene* m_currentScene;
	Scene* m_nextScene;
	float m_sceneLoadProgressPercentage;
private:
	SCENE_LOAD_TYPE m_isLoad;
	HANDLE m_thread;
	bool m_isOver = false;
	CRITICAL_SECTION m_crt;
private:
	static unsigned __stdcall ExecuteFunc(LPVOID pArg);
};

#endif // !__SCENEMANAGER_H__
