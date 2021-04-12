#pragma once
#include "Mesh.h"
#include "Nalmak_Frame.h"
#include "Nalmak_MeshContainer.h"

class XFileMesh :
	public Mesh
{
public:
	XFileMesh();
	~XFileMesh();

private:
	virtual void Initialize(wstring _fp) override;
	virtual void Release() override;
public:
	virtual void Draw(UINT subset = 0) override;
	virtual void BindingStreamSource(unsigned int _inputLayoutSize) override;
private:
	LPD3DXFRAME m_root;
	class DynamicMeshHierarchy* m_hierarchy;
	class AnimationController* m_animController;
	vector<Nalmak_MeshContainer*>		m_meshContainerList;
private:
	void TraverseBone(Nalmak_Frame* _frame);
	void UpdateBoneMatrix(Nalmak_Frame* _bone, const Matrix& _parent);
public:
	AnimationController* CloneAnimationController();
	void SetAnimation(UINT _index);
	void UpdateBoneMatrix();
	void UpdateAnimationController();
};

