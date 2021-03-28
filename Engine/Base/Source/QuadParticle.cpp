#include "..\Include\QuadParticle.h"



QuadParticle::QuadParticle()
{
}


QuadParticle::~QuadParticle()
{
}

void QuadParticle::Initialize(wstring _fp)
{
	CreateVertexBuffer();
	CreateIndexBuffer();

	SetFigureCount(2);
	SetVertexCount(4);
}

void QuadParticle::CreateVertexBuffer()
{
	ThrowIfFailed(m_device->CreateVertexBuffer(
		sizeof(INPUT_LAYOUT_POSITION_UV_SPRITE) * 4,
		0, // 파티클이나 각종 옵션 조절
		NULL,
		D3DPOOL_MANAGED,
		&m_vBuffer,
		nullptr
	));

	INPUT_LAYOUT_POSITION_UV_SPRITE* vertices = nullptr;

	m_vBuffer->Lock(0, 0, (void**)&vertices, 0);
	vertices[0].position = Vector3(-0.5f, -0.5f, 0.f);
	vertices[0].uv = Vector2(0.f, 1.f);
	vertices[0].sprite = Vector2(5.f, 5.f);


	vertices[1].position = Vector3(-0.5f, 0.5f, 0.f);
	vertices[1].uv = Vector2(0.f, 0.f);
	vertices[1].sprite = Vector2(5.f, 5.f);


	vertices[2].position = Vector3(0.5f, -0.5f, 0.f);
	vertices[2].uv = Vector2(1.f, 1.f);
	vertices[2].sprite = Vector2(5.f, 5.f);


	vertices[3].position = Vector3(0.5f, 0.5f, 0.f);
	vertices[3].uv = Vector2(1.f, 0.f);
	vertices[3].sprite = Vector2(5.f, 5.f);

	m_vBuffer->Unlock();

	D3DXComputeBoundingSphere(&vertices[0].position, 4, sizeof(INPUT_LAYOUT_POSITION_UV_SPRITE), &m_boundingSphereCenter, &m_boundingSphereRadius);

}

void QuadParticle::CreateIndexBuffer()
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
