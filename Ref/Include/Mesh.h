#pragma once
#include "IResource.h"
class NALMAK_DLL Mesh :
	public IResource
{
public:
	Mesh();
	~Mesh();

	// IResource을(를) 통해 상속됨
	virtual void Initialize(wstring _fp) override = 0;
	virtual void Release() override = 0;

public:
	virtual void Draw(UINT meshContainerIndex = 0, UINT subset = 0) = 0;
	virtual void BindingStreamSource(UINT _inputLayoutSize) = 0;
protected:
	MESH_TYPE m_meshType;
protected:
	DWORD	 m_stride;
	DWORD	 m_vertexCount;
	DWORD	 m_figureCount;
	Vector3* m_vertexPositionData = nullptr;
	INDEX32* m_indexData = nullptr;
	D3DPRIMITIVETYPE m_primitiveType = D3DPRIMITIVETYPE::D3DPT_TRIANGLELIST;

public:
	MESH_TYPE GetMeshType();
	DWORD GetStride();
	DWORD GetVertexCount();
	DWORD GetFigureCount();
	UINT GetMeshContainerSize();
	Vector3* GetVertexPositionData();
	INDEX32* GetIndexData();
	D3DPRIMITIVETYPE GetPrimitiveType();

protected:
	float m_boundingSphereRadius;
	Vector3 m_boundingSphereCenter;
	vector<DWORD> m_subsetCounts;
public:
	float GetBoundingSphereRadius();
	Vector3 GetBoundingSphereCenter();
	DWORD GetSubsetCount(UINT _meshContainerIndex = 0);

	
};

