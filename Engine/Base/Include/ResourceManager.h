#pragma once

#ifndef __RESOURCEMANAGER_H__
#define __RESOURCEMANAGER_H__

#include "Nalmak_Include.h"
#include "Shader.h"
#include "Texture.h"
#include "VIBuffer.h"
#include "Material.h"
#include "RenderTarget.h"
#include "IResource.h"

BEGIN(Nalmak)
class NALMAK_DLL ResourceManager
{
	DECLARE_SINGLETON(ResourceManager)
private:
	ResourceManager();
	~ResourceManager();
public:
	HRESULT Initialize(bool _allLoad, const wstring& _path);
	void Update();
	HRESULT Release();
	void ReleaseSceneResouce();

	template<typename T>
	T* GetResource(const wstring& _name)
	{
		IResource* resource = m_resoucreContainers[typeid(T).name()][_name];
		
#ifdef _DEBUG
		if (!resource)
		{
			ERR_MSG((L"Resource with that name '" + _name + L"' does not exist").c_str());
			assert(0);
		}
#endif // DEBUG
		return (T*)resource;
	}
	template<typename T>
	T* GetResourceIfExist(const wstring& _name)
	{
		const char* typeId = typeid(T).name();
		if (m_resoucreContainers[typeId].find(_name) == m_resoucreContainers[typeId].end())
			return nullptr;

		IResource* resource = m_resoucreContainers[typeId][_name];
		
		return (T*)resource;
	}
private:
	unordered_map<string, unordered_map<wstring, IResource*>> m_resoucreContainers; 
	typedef unordered_map<string, unordered_map<wstring, IResource*>> RESOURCES;

private:
	wstring m_engineDirectoryPath;
	wstring m_clientDirectoryPath;



public:
	void LoadAllResources(const wstring& _directoryPath, bool _isStatic);
	void LoadResourcesBySceneFoloderName(const wstring& _sceneName, bool _isStatic);
	void CreateDefaultResource();
private:
	void CreateDefaultMesh();

public:
	void UpdateMaterial(const wstring& _fp, bool _isStatic); // Material 데이터 다시 쓰기
	void LoadTextures(const TCHAR* _extention, bool _isStatic);
public:
	template <typename TYPE, typename T>
	void LoadResource(const wstring&_filePath, bool _isStatic = false)
	{
		wstring filePath = _filePath;
		wstring fileName = filePath.substr(filePath.find_last_of(L"/") + 1);
		size_t targetNum = fileName.find_last_of(L".");
		fileName = fileName.substr(0, targetNum);

		if (m_resoucreContainers[typeid(TYPE).name()][fileName])
		{
			MessageBox(NULL, (L"Resource is already exist! " + filePath).c_str(), NULL, MB_OK);
			assert(0);
		}

		TYPE* resource = new T();
		resource->m_isStatic = _isStatic;
		assert("Fail to Create Resource!" && resource);
		((IResource*)resource)->m_name = fileName;
		resource->Initialize(filePath);
		m_resoucreContainers[typeid(TYPE).name()][fileName] = resource;
	}
private:
	template <typename TYPE, typename T>
	void LoadAllResources(const TCHAR* _extention, bool _isStatic)
	{
		list<wstring> filePaths;
		FileIO::SearchingDir(&filePaths, m_engineDirectoryPath.c_str(), _extention);

		for (auto& file : filePaths)
		{
			wstring filePath = file;
			wstring fileName = filePath.substr(filePath.find_last_of(L"/") + 1);
			size_t targetNum = fileName.find_last_of(L".");
			fileName = fileName.substr(0, targetNum);

			if (m_resoucreContainers[typeid(TYPE).name()][fileName])
			{
				MessageBox(NULL, (L"Resource is already exist! " + filePath).c_str(), NULL, MB_OK);
				assert(0);
			}

			TYPE* resource = new T();
			resource->m_isStatic = _isStatic;
			assert("Fail to Create Resource!" && resource);
			((IResource*)resource)->m_name = fileName;
			resource->Initialize(filePath);
			m_resoucreContainers[typeid(TYPE).name()][fileName] = resource;
		}
	}
public:
	template<typename T>
	unordered_map<wstring, IResource* >& GetAllResource()
	{
		return m_resoucreContainers[typeid(T).name()];
	}
public:
	const wstring& GetResourceDirectoryPath() { return m_clientDirectoryPath; }
};
END
#endif
