#include "..\Include\ScreenQuad.h"



ScreenQuad::ScreenQuad()
{
}


ScreenQuad::~ScreenQuad()
{
}

void ScreenQuad::Initialize(wstring _fp)
{
	m_figureCount = 2;
	m_vertexCount = 4;

	CreateVertexBuffer();
	CreateIndexBuffer();

}

void ScreenQuad::CreateVertexBuffer()
{
	ThrowIfFailed(m_device->CreateVertexBuffer(
		sizeof(INPUT_LAYOUT_POSITION_UV) * 4,
		0, // 파티클이나 각종 옵션 조절
		NULL,
		D3DPOOL_MANAGED,
		&m_vBuffer,
		nullptr
	));

	INPUT_LAYOUT_POSITION_UV* vertices = nullptr;

	m_vBuffer->Lock(0, 0, (void**)&vertices, 0);
	vertices[0].position = Vector3(-1.f, -1.f, 0.f);
	vertices[0].uv = Vector2(0.f, 1.f);

	vertices[1].position = Vector3(-1.f, 1.f, 0.f);
	vertices[1].uv = Vector2(0.f, 0.f);

	vertices[2].position = Vector3(1.f, -1.f, 0.f);
	vertices[2].uv = Vector2(1.f, 1.f);

	vertices[3].position = Vector3(1.f, 1.f, 0.f);
	vertices[3].uv = Vector2(1.f, 0.f);

	m_vBuffer->Unlock();

	CopyVertexPositionData(vertices, m_vertexCount);
	D3DXComputeBoundingSphere(&vertices[0].position, 4, sizeof(INPUT_LAYOUT_POSITION_UV), &m_boundingSphereCenter, &m_boundingSphereRadius);

}

void ScreenQuad::CreateIndexBuffer()
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
	indices[3] = 1;
	indices[4] = 3;
	indices[5] = 2;

	m_indexData = new INDEX32[m_figureCount];
	memcpy(m_indexData, indices, sizeof(unsigned long) * m_figureCount * 3);

	m_iBuffer->Unlock();
}
