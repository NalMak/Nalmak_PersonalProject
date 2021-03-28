#include "..\Include\Triangle.h"





void Triangle::Initialize(wstring _fp)
{

	m_figureCount = 1;
	m_vertexCount = 3;

	CreateVertexBuffer();
	CreateIndexBuffer();


}

void Triangle::CreateVertexBuffer()
{
	ThrowIfFailed(m_device->CreateVertexBuffer(
		sizeof(INPUT_LAYOUT_POSITION_NORMAL_UV) * 3,
		0, // 파티클이나 각종 옵션 조절
		NULL, //D3DFVF_XYZ | D3DFVF_NORMAL | D3DFVF_TEX1 | D3DFVF_TEXCOORDSIZE2(0),
		D3DPOOL_MANAGED,
		&m_vBuffer,
		nullptr
	));

	INPUT_LAYOUT_POSITION_NORMAL_UV* vertices = nullptr;

	m_vBuffer->Lock(0, 0, (void**)&vertices, 0);

	vertices[0].position = Vector3(-0.5f, -0.5f, 0.f);
	vertices[0].uv = Vector2(0.f, 1.f);
	vertices[0].normal = Vector3(0.f, 0.f, 1.f);

	vertices[1].position = Vector3(0.f, 0.36f, 0.f);
	vertices[1].uv = Vector2(1.f, 0.f);
	vertices[1].normal = Vector3(0.f, 0.f, 1.f);

	vertices[2].position = Vector3(0.5f, -0.5f, 0.f);
	vertices[2].uv = Vector2(1.f, 1.f);
	vertices[2].normal = Vector3(0.f, 0.f, 1.f);


	m_vBuffer->Unlock();

	CopyVertexPositionData(vertices, m_vertexCount);
	D3DXComputeBoundingSphere(&vertices[0].position, 3, sizeof(INPUT_LAYOUT_POSITION_NORMAL_UV), &m_boundingSphereCenter, &m_boundingSphereRadius);

}

void Triangle::CreateIndexBuffer()
{
	ThrowIfFailed(m_device->CreateIndexBuffer(
		sizeof(INDEX32) * m_figureCount,
		0,
		D3DFMT_INDEX32,
		D3DPOOL_MANAGED,
		&m_iBuffer,
		nullptr));

	unsigned long* indices = nullptr;


	m_iBuffer->Lock(0, 0, (void**)&indices, 0);

	indices[0] = 0;
	indices[1] = 1;
	indices[2] = 2;

	m_indexData = new INDEX32[m_figureCount];
	memcpy(m_indexData, indices, sizeof(unsigned long) * m_figureCount * 3);

	m_iBuffer->Unlock();
}
