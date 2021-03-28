#include "..\Include\LineVI.h"



void LineVI::Initialize(wstring _fp)
{
	m_primitiveType = D3DPRIMITIVETYPE::D3DPT_LINELIST;

	m_figureCount = 1;
	m_vertexCount = 2;

	CreateVertexBuffer();
	CreateIndexBuffer();


}

void LineVI::CreateVertexBuffer()
{
	ThrowIfFailed(m_device->CreateVertexBuffer(
		sizeof(INPUT_LAYOUT_POSITION) * 2,
		0, // 파티클이나 각종 옵션 조절
		NULL,
		D3DPOOL_MANAGED,
		&m_vBuffer,
		nullptr
	));

	INPUT_LAYOUT_POSITION* vertices = nullptr;

	m_vBuffer->Lock(0, 0, (void**)&vertices, 0);

	vertices[0].position = Vector3(-0.5f, 0.f, 0.f);
	vertices[1].position = Vector3(0.5f, 0.f, 0.f);


	m_vBuffer->Unlock();


	CopyVertexPositionData<INPUT_LAYOUT_POSITION>(vertices, m_vertexCount);
	D3DXComputeBoundingSphere(&vertices[0].position, m_vertexCount, sizeof(INPUT_LAYOUT_POSITION), &m_boundingSphereCenter, &m_boundingSphereRadius);
}

void LineVI::CreateIndexBuffer()
{
	ThrowIfFailed(m_device->CreateIndexBuffer(
		sizeof(unsigned long) * 2,
		0,
		D3DFMT_INDEX32,
		D3DPOOL_MANAGED,
		&m_iBuffer,
		nullptr));

	unsigned long* indices = nullptr;

	m_iBuffer->Lock(0, 0, (void**)&indices, 0);

	indices[0] = 0;
	indices[1] = 1;

	m_indexData = new INDEX32[m_figureCount];
	memcpy(m_indexData, indices, sizeof(unsigned long) * m_figureCount * 2);

	m_iBuffer->Unlock();
}
