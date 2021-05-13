#pragma once
#include "Component.h"
#include "Nalmak_Include.h"

class MeshRenderer;
class RenderManager;
class Mesh;
class NALMAK_DLL LOD_Group :
	public Component
{
public:
	struct Desc
	{

	};
public:
	LOD_Group(Desc* _desc);
	~LOD_Group();
private:
	// Component을(를) 통해 상속됨
	virtual void Initialize() override;
	virtual void Update() override;
	virtual void EachRender() override;
private:
	typedef pair<Mesh*, float> LOD;
	vector<LOD> m_lodGroup;
public:
	void AddLODMesh(Mesh* _mesh, float _distanceRatio);
	void AddLODMesh(const wstring& _meshName, float _distanceRatio);

private:
	MeshRenderer* m_staticMeshRenderer;
	RenderManager* m_renderManager;
};

