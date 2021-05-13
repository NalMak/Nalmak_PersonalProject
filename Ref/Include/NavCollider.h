#pragma once
#include "Collider.h"
class NALMAK_DLL NavCollider :
	public Collider
{
public:
	struct Desc
	{
		wstring navName = L"";
	};
public:
	NavCollider(Desc* _desc);
	~NavCollider();

private:
	virtual void Initialize() override;
	virtual void Update() override;

private:
	class NavMeshData* m_navData;
};

