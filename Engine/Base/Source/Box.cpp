#include "..\Include\Box.h"



Box::Box()
{
}


Box::~Box()
{
}

void Box::Initialize(wstring _fp )
{

	m_figureCount = 12;
	m_vertexCount = 24;

	CreateVertexBuffer();
	CreateIndexBuffer();
}

void Box::CreateVertexBuffer()
{
	ThrowIfFailed(m_device->CreateVertexBuffer(
		sizeof(INPUT_LAYOUT_POSITION_NORMAL_UV) * 24,
		0, // 파티클이나 각종 옵션 조절
		NULL, //D3DFVF_XYZ | D3DFVF_NORMAL | D3DFVF_TEX1 | D3DFVF_TEXCOORDSIZE2(0),
		D3DPOOL_MANAGED,
		&m_vBuffer,
		nullptr
	));

	INPUT_LAYOUT_POSITION_NORMAL_UV* vertices = nullptr;

	float w2 = 0.5f;
	float h2 = 0.5f;
	float d2 = 0.5f;

	m_vBuffer->Lock(0, 0, (void**)&vertices, 0);

	vertices[0].position = Vector3(-w2, -h2, -d2);
	vertices[0].normal = Vector3(0.f, 0.f, -1.f);
	vertices[0].uv = Vector2(0.f, 1.f);

	vertices[1].position = Vector3(-w2, +h2, -d2);
	vertices[1].normal = Vector3(0.f, 0.f, -1.f);
	vertices[1].uv = Vector2(0.f, 0.f);

	vertices[2].position = Vector3(+w2, +h2, -d2);
	vertices[2].uv = Vector2(1.f, 0.f);
	vertices[2].normal = Vector3(0.f, 0.f, -1.f);

	vertices[3].position = Vector3(+w2, -h2, -d2);
	vertices[3].uv = Vector2(1.f, 1.f);
	vertices[3].normal = Vector3(0.f, 0.f, -1.f);
	//////////////////////////////////////////////////////////
	vertices[4].position = Vector3(-w2, -h2, +d2);
	vertices[4].normal = Vector3(0.f, 0.f, 1.f);
	vertices[4].uv = Vector2(1.f, 1.f);

	vertices[5].position = Vector3(w2, -h2, +d2);
	vertices[5].normal = Vector3(0.f, 0.f, 1.f);
	vertices[5].uv = Vector2(0.f, 1.f);

	vertices[6].position = Vector3(+w2, +h2, +d2);
	vertices[6].normal = Vector3(0.f, 0.f, 1.f);
	vertices[6].uv = Vector2(0.f, 0.f);

	vertices[7].position = Vector3(-w2, h2, d2);
	vertices[7].normal = Vector3(0.f, 0.f, 1.f);
	vertices[7].uv = Vector2(1.f, 0.f);
	//////////////////////////////////////////////////////////
	vertices[8].position = Vector3(-w2, +h2, -d2);
	vertices[8].normal = Vector3(0.f, 1.f, 0.f);
	vertices[8].uv = Vector2(0.f, 1.f);

	vertices[9].position = Vector3(-w2, +h2, +d2);
	vertices[9].normal = Vector3(0.f, 1.f, 0.f);
	vertices[9].uv = Vector2(0.f, 0.f);

	vertices[10].position = Vector3(+w2, +h2, +d2);
	vertices[10].normal = Vector3(0.f, 1.f, 0.f);
	vertices[10].uv = Vector2(1.f, 0.f);

	vertices[11].position = Vector3(w2, h2, -d2);
	vertices[11].normal = Vector3(0.f, 1.f, 0.f);
	vertices[11].uv = Vector2(1.f, 1.f);
	//////////////////////////////////////////////////////////

	vertices[12].position = Vector3(-w2, -h2, -d2);
	vertices[12].normal = Vector3(0.f, -1.f, 0.f);
	vertices[12].uv = Vector2(1.f, 1.f);

	vertices[13].position = Vector3(w2, -h2, -d2);
	vertices[13].normal = Vector3(0.f, -1.f, 0.f);
	vertices[13].uv = Vector2(0.f, 1.f);

	vertices[14].position = Vector3(+w2, -h2, +d2);
	vertices[14].normal = Vector3(0.f, -1.f, 0.f);
	vertices[14].uv = Vector2(0.f, 0.f);

	vertices[15].position = Vector3(-w2, -h2, +d2);
	vertices[15].normal = Vector3(0.f, -1.f, 0.f);
	vertices[15].uv = Vector2(1.f, 0.f);
	//////////////////////////////////////////////////////////

	vertices[16].position = Vector3(-w2, -h2, d2);
	vertices[16].normal = Vector3(-1.f, 0.f, 0.f);
	vertices[16].uv = Vector2(0.f, 1.f);

	vertices[17].position = Vector3(-w2, h2, d2);
	vertices[17].normal = Vector3(-1.f, 0.f, 0.f);
	vertices[17].uv = Vector2(0.f, 0.f);

	vertices[18].position = Vector3(-w2, +h2, -d2);
	vertices[18].normal = Vector3(-1.f, 0.f, 0.f);
	vertices[18].uv = Vector2(1.f, 0.f);

	vertices[19].position = Vector3(-w2, -h2, -d2);
	vertices[19].normal = Vector3(-1.f, 0.f, 0.f);
	vertices[19].uv = Vector2(1.f, 1.f);
	//////////////////////////////////////////////////////////

	vertices[20].position = Vector3(w2, -h2, -d2);
	vertices[20].normal = Vector3(1.f, 0.f, 0.f);
	vertices[20].uv = Vector2(0.f, 1.f);

	vertices[21].position = Vector3(w2, h2, -d2);
	vertices[21].normal = Vector3(1.f, 0.f, 0.f);
	vertices[21].uv = Vector2(0.f, 0.f);

	vertices[22].position = Vector3(w2, +h2, d2);
	vertices[22].normal = Vector3(1.f, 0.f, 0.f);
	vertices[22].uv = Vector2(1.f, 0.f);

	vertices[23].position = Vector3(w2, -h2, d2);
	vertices[23].normal = Vector3(1.f, 0.f, 0.f);
	vertices[23].uv = Vector2(1.f, 1.f);
	//////////////////////////////////////////////////////////
	m_vertexPositionData = new Vector3[24];

	m_vBuffer->Unlock();

	CopyVertexPositionData(vertices, m_vertexCount);
	D3DXComputeBoundingSphere(&vertices[0].position, 24, sizeof(INPUT_LAYOUT_POSITION_NORMAL_UV), &m_boundingSphereCenter, &m_boundingSphereRadius);
}

void Box::CreateIndexBuffer()
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


	indices[0] = 0; indices[1] = 1; indices[2] = 2;
	indices[3] = 0; indices[4] = 2; indices[5] = 3;

	indices[6] = 4; indices[7] = 5; indices[8] = 6;
	indices[9] = 4; indices[10] = 6; indices[11] = 7;

	indices[12] = 8; indices[13] = 9; indices[14] = 10;
	indices[15] = 8; indices[16] = 10; indices[17] = 11;

	indices[18] = 12; indices[19] = 13; indices[20] = 14;
	indices[21] = 12; indices[22] = 14; indices[23] = 15;

	indices[24] = 16; indices[25] = 17; indices[26] = 18;
	indices[27] = 16; indices[28] = 18; indices[29] = 19;

	indices[30] = 20; indices[31] = 21; indices[32] = 22;
	indices[33] = 20; indices[34] = 22; indices[35] = 23;

	m_indexData = new INDEX32[m_figureCount];
	memcpy(m_indexData, indices, sizeof(unsigned long) * m_figureCount * 3);

	m_iBuffer->Unlock();
}
