#include "..\Include\Mesh.h"



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

unsigned long Mesh::GetStride()
{
	return m_stride;
}

unsigned long Mesh::GetVertexCount()
{
	return m_vertexCount;
}

unsigned long Mesh::GetFigureCount()
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
