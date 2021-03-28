#pragma once
#include "IResource.h"
class Mesh :
	public IResource
{
public:
	Mesh();
	~Mesh();

	// IResource을(를) 통해 상속됨
	virtual void Initialize(wstring _fp) override = 0;
	virtual void Release() override = 0;

public:
	virtual void Draw() = 0;
	virtual void BindingStreamSource(unsigned int _inputLayoutSize) = 0;
protected:

protected:
	unsigned long	 m_stride;
	unsigned long	 m_vertexCount;
	unsigned long	 m_figureCount;
	Vector3* m_vertexPositionData = nullptr;
	INDEX32* m_indexData = nullptr;
	D3DPRIMITIVETYPE m_primitiveType = D3DPRIMITIVETYPE::D3DPT_TRIANGLELIST;

public:
	unsigned long GetStride();
	unsigned long GetVertexCount();
	unsigned long GetFigureCount();
	Vector3* GetVertexPositionData();
	INDEX32* GetIndices();
	D3DPRIMITIVETYPE GetPrimitiveType();

protected:
	float m_boundingSphereRadius;
	Vector3 m_boundingSphereCenter;
	unsigned long m_subsetCount = 1;
public:
	float GetBoundingSphereRadius();
	Vector3 GetBoundingSphereCenter();
	unsigned long GetSubsetCount() { return m_subsetCount; }

	
};

