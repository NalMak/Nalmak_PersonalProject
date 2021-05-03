#pragma once
#include "IResource.h"
#include "Transform.h"
#include "SphereCollider.h"
#include "BoxCollider.h"
#include "CapsuleCollider.h"
#include "MeshCollider.h"
#include "PointLight.h"

struct NALMAK_DLL StaticObjectInfoData
{
	wstring name = L"default";
	int tag = 0;
	int layer = 0;
	Transform::Desc transformDesc;

	bool isExistmeshRenderer = false;
	Mesh* mesh;
	vector<Material*> materials;

	bool isExistSphereCollider = false;
	SphereCollider::Desc sphereDesc;

	bool isExistBoxCollider = false;
	BoxCollider::Desc boxDesc;

	bool isExistCapsuleCollider = false;
	CapsuleCollider::Desc capsuleDesc;

	bool isExistMeshCollider = false;
	MeshCollider::Desc meshDesc;

	bool isExistPointLight = false;
	PointLight::Desc pointDesc;


	
};

class NALMAK_DLL StaticObjectInfo : public IResource
{
public:
	StaticObjectInfo();
	~StaticObjectInfo();

	// IResource을(를) 통해 상속됨
	virtual void Initialize(wstring _fp) override;
	virtual void Release() override;
public:
	StaticObjectInfoData& GetData() { return m_data; }
private:
	StaticObjectInfoData m_data;
};

