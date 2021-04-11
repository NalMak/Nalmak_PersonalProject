#pragma once
#include "Mesh.h"
#include "Nalmak_Frame.h"
#include "Nalmak_MeshContainer.h"

class NALMAK_DLL DynamicMesh :
	public Mesh
{
private:
	// Mesh을(를) 통해 상속됨
	virtual void Initialize(wstring _fp) override;
	virtual void Release() override;
public:
	virtual void Draw(UINT subset = 0) override;
	virtual void BindingStreamSource(unsigned int _inputLayoutSize) override;
private:
	class DynamicMeshHierarchy* m_hierarchy;
	LPD3DXFRAME m_root;
	class AnimationController* m_animController;
	vector<Nalmak_MeshContainer*>		m_meshContainerList;
private:
	void TraverseBone(Nalmak_Frame* _frame);
public:
	void SetAnimation(UINT _index);
	void UpdateBoneMatrix();
	void UpdateAnimationController();
private:
	void UpdateBoneMatrix(Nalmak_Frame* _bone, const Matrix& _parent);
};

