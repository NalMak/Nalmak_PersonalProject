#include "StaticObjectInfo.h"



StaticObjectInfo::StaticObjectInfo()
{
}


StaticObjectInfo::~StaticObjectInfo()
{
}

void StaticObjectInfo::Initialize(wstring _fp)
{
	HANDLE handle = CreateFile(_fp.c_str(), GENERIC_READ, 0, nullptr, OPEN_EXISTING, FILE_ATTRIBUTE_NORMAL, nullptr);

	if (INVALID_HANDLE_VALUE == handle)
	{
		ERR_MSG((L"Can't Load " + _fp + L" : Static Object Data ").c_str());
		assert(0);
		return;
	}
	DWORD byte;
	wstring name = Nalmak_String::ReadWString_ReadEachCharacter_FromFile(handle);
	m_data.name = name;

	int tag;
	ReadFile(handle, &tag, sizeof(int), &byte, nullptr);
	m_data.tag = tag;

	int layer;
	ReadFile(handle, &layer, sizeof(int), &byte, nullptr);
	m_data.layer = layer;

	Transform::Desc transform;
	ReadFile(handle, &transform, sizeof(Transform::Desc), &byte, nullptr);
	m_data.transformDesc = transform;

	bool isExist;
	ReadFile(handle, &isExist, sizeof(bool), &byte, nullptr);
	m_data.isExistmeshRenderer = isExist;

	if (isExist)
	{
		wstring meshName = Nalmak_String::ReadWString_ReadEachCharacter_FromFile(handle);
		m_data.mesh = ResourceManager::GetInstance()->GetResource<Mesh>(meshName);

		int materialCount;
		ReadFile(handle, &materialCount, sizeof(int), &byte, nullptr);

		for (int i = 0; i < materialCount; ++i)
		{
			wstring mtrlName = Nalmak_String::ReadWString_ReadEachCharacter_FromFile(handle);
			m_data.materials.emplace_back(ResourceManager::GetInstance()->GetResource<Material>(mtrlName));
		}
	}

	ReadFile(handle, &isExist, sizeof(bool), &byte, nullptr);
	m_data.isExistSphereCollider = isExist;

	if (isExist)
	{
		SphereCollider::Desc sphere;
		ReadFile(handle, &sphere, sizeof(SphereCollider::Desc), &byte, nullptr);
		m_data.sphereDesc = sphere;
	}

	ReadFile(handle, &isExist, sizeof(bool), &byte, nullptr);
	m_data.isExistBoxCollider = isExist;

	if (isExist)
	{
		BoxCollider::Desc box;
		ReadFile(handle, &box, sizeof(BoxCollider::Desc), &byte, nullptr);
		m_data.boxDesc = box;
	}

	ReadFile(handle, &isExist, sizeof(bool), &byte, nullptr);
	m_data.isExistCapsuleCollider = isExist;

	if (isExist)
	{
		CapsuleCollider::Desc capsule;
		ReadFile(handle, &capsule, sizeof(CapsuleCollider::Desc), &byte, nullptr);
		m_data.capsuleDesc = capsule;
	}

	ReadFile(handle, &isExist, sizeof(bool), &byte, nullptr);
	m_data.isExistMeshCollider = isExist;

	if (isExist)
	{
		MeshCollider::Desc mesh;
		ReadFile(handle, &mesh, sizeof(MeshCollider::Desc), &byte, nullptr);
		m_data.meshDesc = mesh;
	}

	CloseHandle(handle);
}

void StaticObjectInfo::Release()
{
}
