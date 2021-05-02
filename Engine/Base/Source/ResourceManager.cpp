#include "ResourceManager.h"
#include "Quad.h"
#include "Triangle.h"
#include "LineVI.h"
#include "QuadNoneNormal.h"
#include "SkyBox.h"
#include "DepthStencil.h"
#include "RenderManager.h"
#include "ParticleInfo.h"
#include "Core.h"
#include "ScreenQuad.h"
#include "AudioClip.h"
#include "StaticObjectInfo.h"
#include "XFileMesh.h"
#include "NavMeshData.h"

USING(Nalmak)
IMPLEMENT_SINGLETON(ResourceManager)
ResourceManager::ResourceManager()
{
}


ResourceManager::~ResourceManager()
{
	Release();
}

HRESULT ResourceManager::Initialize(bool _allLoad, const wstring & _path)
{

	// Font
	//AddFontResource(L"../../Resource/Client/Font/Selected/Astrolab.ttf");
	m_clientDirectoryPath = _path;

	LoadAllResources(L"../Engine/Resource",true);
	LoadAllResources(L"../../Engine/Resource",true);
	LoadAllResources(L"../../../../Engine/Resource",true);
	if (!_allLoad)
		return S_OK;
	
	LoadAllResources(_path ,true);

	return S_OK;
}

void ResourceManager::Update()
{
#ifdef _DEBUG

#endif // _DEBUG



}

HRESULT ResourceManager::Release()
{
	for (auto& resources : m_resoucreContainers)
	{
		for (auto& resource : resources.second)
		{
			if (resource.second)
			{
				resource.second->Release();
				SAFE_DELETE(resource.second);
			}
		}
		resources.second.clear();
	}
	m_resoucreContainers.clear();


	// Font
	//RemoveFontResource(L"../../Resource/Client/Font/Selected/Astrolab.ttf");
	

	return S_OK;
}

void ResourceManager::ReleaseSceneResouce()
{
	for (auto& resources : m_resoucreContainers)
	{
		for (auto iter = resources.second.begin(); iter != resources.second.end();)
		{
			if ((*iter).second)
			{
				if ((*iter).second->m_isStatic)
				{
					++iter;
					continue;
				}
				auto resource = (*iter).second;
				iter = resources.second.erase(iter);
				resource->Release();
				SAFE_DELETE(resource);
			}
		}
	}

}



void ResourceManager::LoadAllResources(const wstring & _directoryPath, bool _isStatic)
{
	m_engineDirectoryPath = _directoryPath;

	LoadAllResources<Mesh, XFileMesh>(L"X", _isStatic);
	//LoadAllResources<Mesh, DynamicMesh>(L"X", _isStatic);



	LoadAllResources<AudioClip, AudioClip>(L"aud", _isStatic);

	LoadTextures(L"jpg",_isStatic);
	LoadTextures(L"png",_isStatic);
	LoadTextures(L"dds",_isStatic);
	LoadTextures(L"tga",_isStatic);
	LoadTextures(L"bmp",_isStatic);

	LoadAllResources<RenderTarget, RenderTarget>(L"rtd", _isStatic);
	LoadAllResources<DepthStencil, DepthStencil>(L"dsd", _isStatic);
	LoadAllResources<Shader, Shader>(L"sd", _isStatic);
	LoadAllResources<Material, Material>(L"mtrl", _isStatic);
	LoadAllResources<ParticleInfo, ParticleInfo>(L"ptd", _isStatic);
	LoadAllResources<StaticObjectInfo, StaticObjectInfo>(L"sttd", _isStatic);
	LoadAllResources<NavMeshData, NavMeshData>(L"nvd", _isStatic);

}

void ResourceManager::LoadResourcesBySceneFoloderName(const wstring & _sceneName, bool _isStatic)
{
	wstring resourceDirectory = m_clientDirectoryPath + L"/" + _sceneName;

	LoadAllResources(resourceDirectory, _isStatic);
}

void ResourceManager::CreateDefaultResource()
{
	CreateDefaultMesh();
}



void ResourceManager::CreateDefaultMesh()
{
	{
		VIBuffer* mesh = new Quad();
		assert("Fail to Create Mesh!" && mesh);
		mesh->OnInitialize();
		m_resoucreContainers[typeid(Mesh).name()][L"quad"] = mesh;
	}
	{
		VIBuffer* mesh = new ScreenQuad();
		assert("Fail to Create Mesh!" && mesh);
		mesh->OnInitialize();
		m_resoucreContainers[typeid(Mesh).name()][L"screenQuad"] = mesh;
	}
	{
		VIBuffer* mesh = new Triangle();
		assert("Fail to Create Mesh!" && mesh);
		mesh->OnInitialize();
		m_resoucreContainers[typeid(Mesh).name()][L"triangle"] = mesh;
	}
	{
		VIBuffer* mesh = new SkyBox();
		assert("Fail to Create Mesh!" && mesh);
		mesh->OnInitialize();
		m_resoucreContainers[typeid(Mesh).name()][L"skyBox"] = mesh;
	}

	{
		VIBuffer* mesh = new LineVI();
		assert("Fail to Create Mesh!" && mesh);
		mesh->OnInitialize();
		m_resoucreContainers[typeid(Mesh).name()][L"line"] = mesh;
	}
	{
		VIBuffer* mesh = new QuadNoneNormal();
		assert("Fail to Create Mesh!" && mesh);
		mesh->OnInitialize();
		m_resoucreContainers[typeid(Mesh).name()][L"quadNoneNormal"] = mesh;
	}

}

void ResourceManager::UpdateMaterial(const wstring& _fp, bool _isStatic)
{

	list<wstring> filePaths;
	FileIO::SearchingDir(&filePaths, _fp.c_str(), L"mtrl");

	for (auto& file : filePaths)
	{
		wstring filePath = file;
		wstring fileName = filePath.substr(filePath.find_last_of(L"/") + 1);
		size_t targetNum = fileName.find_last_of(L".");
		fileName = fileName.substr(0, targetNum);

		if (m_resoucreContainers[typeid(Material).name()][fileName])
		{
			Material material;
			material.Initialize(filePath);
			Material* existingMtrl = (Material*)m_resoucreContainers[typeid(Material).name()][fileName];
			existingMtrl->m_name = fileName;
			*existingMtrl = material;
		}
		else
		{
			Material* resource = new Material();
			resource->m_isStatic = _isStatic;
			assert("Fail to Create Resource!" && resource);
			((IResource*)resource)->m_name = fileName;
			resource->Initialize(filePath);
			m_resoucreContainers[typeid(Material).name()][fileName] = resource;
		}


	}
}

void ResourceManager::LoadTextures(const TCHAR * _extention, bool _isStatic)
{

	list<wstring> filePaths;
	FileIO::SearchingDir(&filePaths, m_engineDirectoryPath.c_str(), _extention);

	for (auto& file : filePaths)
	{
		wstring filePath = file;
		wstring fileName = filePath.substr(filePath.find_last_of(L"/") + 1);
		size_t targetNum = fileName.find_last_of(L".");
		fileName = fileName.substr(0, targetNum);



		targetNum = fileName.find_last_of(L"_");
		if (targetNum != -1)
		{
			wstring fileIndex = fileName.substr(targetNum + 1, fileName.length());

			int texIndex = 0;
			if (Nalmak_String::IsDigitString(&texIndex, fileIndex))
			{
				fileName = fileName.substr(0, targetNum);

				Texture* tex = (Texture*)m_resoucreContainers[typeid(Texture).name()][fileName];
				if (!tex)
				{
					tex = new Texture;
					tex->m_isStatic = _isStatic;
					m_resoucreContainers[typeid(Texture).name()][fileName] = tex;
				}
				tex->Initialize(filePath.c_str());

			}
			else
			{
				if (m_resoucreContainers[typeid(Texture).name()][fileName])
				{
					MessageBox(NULL, (L"Resource is already exist! " + filePath).c_str(), NULL, MB_OK);
				}
				Texture* tex = new Texture();
				assert("Fail to Create Resource!" && tex);
				tex->m_isStatic = _isStatic;
				tex->Initialize(filePath.c_str());
				m_resoucreContainers[typeid(Texture).name()][fileName] = tex;
			}
		}
		else
		{
			if (m_resoucreContainers[typeid(Texture).name()][fileName])
			{
				MessageBox(NULL, (L"Resource is already exist! " + filePath).c_str(), NULL, MB_OK);
			}
			Texture* tex = new Texture();
			tex->m_isStatic = _isStatic;
			assert("Fail to Create Resource!" && tex);
			tex->Initialize(filePath.c_str());
			m_resoucreContainers[typeid(Texture).name()][fileName] = tex;
		}


	}
}

