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

Vector3 * Mesh::GetVertexPositionData()
{
	return m_vertexPositionData;
}

INDEX32 * Mesh::GetIndices()
{
	return m_indexData;
}

D3DPRIMITIVETYPE Mesh::GetPrimitiveType()
{
	return m_primitiveType;
}
