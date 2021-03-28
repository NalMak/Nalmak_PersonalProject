#include "..\Include\GroundVIBuffer.h"




void GroundVIBuffer::Initialize(wstring _fp)
{
	CreateVertexBuffer();
	CreateIndexBuffer();

	m_figureCount = 2;
	m_vertexCount = 4;
}

void GroundVIBuffer::CreateVertexBuffer()
{
	ThrowIfFailed(m_device->CreateVertexBuffer(
		sizeof(INPUT_LAYOUT_POSITION_NORMAL_UV) * 4,
		0, // 파티클이나 각종 옵션 조절
		NULL, //D3DFVF_XYZ | D3DFVF_NORMAL | D3DFVF_TEX1 | D3DFVF_TEXCOORDSIZE2(0),
		D3DPOOL_MANAGED,
		&m_vBuffer,
		nullptr
	));

	INPUT_LAYOUT_POSITION_NORMAL_UV* vertices = nullptr;

	m_vBuffer->Lock(0, 0, (void**)&vertices, 0);

	vertices[0].position = Vector3(-0.5f, 0.f, - 0.5f);
	vertices[0].uv = Vector2(0.f, 1.f);
	vertices[0].normal = Vector3(0.f, 1.f, 0.f);

	vertices[1].position = Vector3(-0.5f,  0.f, 0.5f);
	vertices[1].uv = Vector2(0.f, 0.f);
	vertices[1].normal = Vector3(0.f, 1.f, 0.f);

	vertices[2].position = Vector3(0.5f,  0.f, -0.5f);
	vertices[2].uv = Vector2(1.f, 1.f);
	vertices[2].normal = Vector3(0.f, 1.f, 0.f);

	vertices[3].position = Vector3(0.5f,  0.f, 0.5f);
	vertices[3].uv = Vector2(1.f, 0.f);
	vertices[3].normal = Vector3(0.f, 1.f, 0.f);

	m_vBuffer->Unlock();

	D3DXComputeBoundingSphere(&vertices[0].position, 4, sizeof(INPUT_LAYOUT_POSITION_UV), &m_boundingSphereCenter, &m_boundingSphereRadius);
}

void GroundVIBuffer::CreateIndexBuffer()
{
	ThrowIfFailed(m_device->CreateIndexBuffer(
		sizeof(short) * 6,
		0,
		D3DFMT_INDEX16,
		D3DPOOL_MANAGED,
		&m_iBuffer,
		nullptr));

	short* indices = nullptr;

	m_iBuffer->Lock(0, 0, (void**)&indices, 0);

	indices[0] = 0;
	indices[1] = 1;
	indices[2] = 2;
	indices[3] = 1;
	indices[4] = 3;
	indices[5] = 2;

	m_iBuffer->Unlock();
}
