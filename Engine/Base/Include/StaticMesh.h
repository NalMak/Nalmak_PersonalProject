#pragma once
#include "Mesh.h"

// normal : ���� �����ϰ� �ִ� ����� ������ ����
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
	//LPD3DXBUFFER -> ���� ä���� ����. DX �Լ��θ� ä�� �� ����  // ���� �� �ּҸ� ���Ϲ��� �� ����
	LPD3DXBUFFER		m_adjacency; // 0�� �ﰢ���� �̿� 3�� 1�� �ﰢ���� �̿� 3�� ... ���� �迭  -> ��� �뵵 : normal �� ���� ���  �����ؼ� ����
	LPD3DXBUFFER		m_subset;
public:
	virtual void Draw(UINT _subset = 0) override;
	virtual void BindingStreamSource(unsigned int _inputLayoutSize) override;

};
