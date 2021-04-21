#include "Mesh.h"



Mesh::Mesh()
{
}


Mesh::~Mesh()
{
}

float Mesh::GetBoundingSphereRadius()
{
	return m_boundingSphereRadius;
}

Vector3 Mesh::GetBoundingSphereCenter()
{
	return m_boundingSphereCenter;
}

DWORD Mesh::GetSubsetCount(UINT _meshContainerIndex)
{
	return m_subsetCounts[_meshContainerIndex];
}

MESH_TYPE Mesh::GetMeshType()
{
	return m_meshType;
}

DWORD Mesh::GetStride()
{
	return m_stride;
}

DWORD Mesh::GetVertexCount()
{
	return m_vertexCount;
}

DWORD Mesh::GetFigureCount()
{
	return m_figureCount;
}

UINT Mesh::GetMeshContainerSize()
{
	return (UINT)m_subsetCounts.size();
}

Vector3 * Mesh::GetVertexPositionData()
{
	return m_vertexPositionData;
}

INDEX32 * Mesh::GetIndexData()
{
	return m_indexData;
}

D3DPRIMITIVETYPE Mesh::GetPrimitiveType()
{
	return m_primitiveType;
}
