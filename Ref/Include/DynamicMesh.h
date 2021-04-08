#pragma once
#include "Mesh.h"
class DynamicMesh :
	public Mesh
{
public:
	DynamicMesh();
	~DynamicMesh();
private:
	// Mesh��(��) ���� ��ӵ�
	virtual void Initialize(wstring _fp) override;
	virtual void Release() override;
	virtual void Draw(UINT subset = 0) override;
	virtual void BindingStreamSource(unsigned int _inputLayoutSize) override;

private:
	class DynamicMeshHierarchy* m_hierarchy;
	LPD3DXFRAME m_root;
};

