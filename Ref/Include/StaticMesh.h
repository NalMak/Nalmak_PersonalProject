#pragma once
#include "Mesh.h"
class StaticMesh :
	public Mesh
{
public:
	StaticMesh();
	~StaticMesh();

	virtual void Initialize(wstring _fp) override;
	virtual void Release() override;

private:
	LPD3DXMESH			m_originMesh;
	LPD3DXMESH			m_mesh;
	LPD3DXBUFFER		m_adjacency;
	LPD3DXBUFFER		m_subset;
public:
	virtual void Draw() override;
	virtual void BindingStreamSource(unsigned int _inputLayoutSize) override;

};
