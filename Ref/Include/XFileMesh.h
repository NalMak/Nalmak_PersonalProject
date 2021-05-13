#pragma once
#include "Mesh.h"
#include "Nalmak_Animation.h"

class Shader;

class NALMAK_DLL XFileMesh :
	public Mesh
{
public:
	XFileMesh();
	~XFileMesh();

private:
	virtual void Initialize(wstring _fp) override;
	virtual void Release() override;

	void InitializeSW();
	void InitializeHW();
	void StoreVertexIndexData();
public:
	virtual void Draw(UINT meshContainerIndex = 0, UINT subset = 0) override;
	virtual void BindingStreamSource(UINT _inputLayoutSize) override;
	Nalmak_MeshContainer* GetMeshContainer(UINT _index);
private:
	class MeshHierarchy* m_hierarchy;
	LPD3DXANIMATIONCONTROLLER m_animController;
	LPD3DXFRAME m_root;
	vector<Nalmak_MeshContainer*>		m_meshContainerList;
private:
	void TraverseBone(Nalmak_Frame* _frame);
public:
	LPD3DXANIMATIONCONTROLLER  GetAnimationController();
	LPD3DXFRAME GetRoot();

};

