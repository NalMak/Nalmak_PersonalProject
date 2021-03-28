#pragma once
#include "Collider.h"
class Mesh;

class NALMAK_DLL MeshCollider :
	public Collider
{
public:
	struct Desc
	{
		bool isTrigger = false;
	};
public:
	MeshCollider(Desc* _desc);
	~MeshCollider();
private:
	// Collider��(��) ���� ��ӵ�
	virtual void Initialize() override;
	virtual void Update() override;
private:
	PxConvexMesh* m_convexMesh;
};

