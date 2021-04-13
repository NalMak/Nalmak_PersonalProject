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

	void InitializeSW();
	void InitializeHW();

public:
	virtual void Draw(UINT subset = 0) override;
	void DrawHW();
	virtual void BindingStreamSource(unsigned int _inputLayoutSize) override;
private:
	class MeshHierarchy* m_hierarchy;
	LPD3DXANIMATIONCONTROLLER m_animController;
	LPD3DXFRAME m_root;
	vector<Nalmak_MeshContainer*>		m_meshContainerList;
	bool m_isRenderHW;
private:
	void TraverseBone(Nalmak_Frame* _frame);
public:
	LPD3DXANIMATIONCONTROLLER  GetAnimationController();
	LPD3DXFRAME GetRoot();
};

