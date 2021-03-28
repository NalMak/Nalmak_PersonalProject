#include "..\Include\SkyBox.h"



SkyBox::SkyBox()
{
}


SkyBox::~SkyBox()
{
}

void SkyBox::Initialize(wstring _fp)
{
	m_figureCount = 12;
	m_vertexCount = 8;

	CreateVertexBuffer();
	CreateIndexBuffer();
	
}

void SkyBox::CreateVertexBuffer()
{
	ThrowIfFailed(m_device->CreateVertexBuffer(
		sizeof(INPUT_LAYOUT_SKYBOX) * 8,
		0, // 파티클이나 각종 옵션 조절
		NULL, //D3DFVF_XYZ | D3DFVF_NORMAL | D3DFVF_TEX1 | D3DFVF_TEXCOORDSIZE2(0),
		D3DPOOL_MANAGED,
		&m_vBuffer,
		nullptr
	));

	INPUT_LAYOUT_SKYBOX* vertices = nullptr;
	m_vBuffer->Lock(0, 0, (void**)&vertices, 0);

	vertices[0].position = Vector3(-0.5f, 0.5f, -0.5f);
	vertices[0].uvw = vertices[0].position;

	vertices[1].position = Vector3(0.5f, 0.5f, -0.5f);
	vertices[1].uvw = vertices[1].position;

	vertices[2].position = Vector3(0.5f, -0.5f, -0.5f);
	vertices[2].uvw = vertices[2].position;

	vertices[3].position = Vector3(-0.5f, -0.5f, -0.5f);
	vertices[3].uvw = vertices[3].position;

	vertices[4].position = Vector3(-0.5f, 0.5f, 0.5f);
	vertices[4].uvw = vertices[4].position;

	vertices[5].position = Vector3(0.5f, 0.5f, 0.5f);
	vertices[5].uvw = vertices[5].position;

	vertices[6].position = Vector3(0.5f, -0.5f, 0.5f);
	vertices[6].uvw = vertices[6].position;

	vertices[7].position = Vector3(-0.5f, -0.5f, 0.5f);
	vertices[7].uvw = vertices[7].position;

	m_vBuffer->Unlock();

	CopyVertexPositionData(vertices, m_vertexCount);
	m_boundingSphereRadius = 0;

}

void SkyBox::CreateIndexBuffer()
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

	indices[0] = 1;
	indices[1] = 5;
	indices[2] = 6;

	indices[3] = 1;
	indices[4] = 6;
	indices[5] = 2;

	indices[6] = 4;
	indices[7] = 0;
	indices[8] = 3;

	indices[9] = 4;
	indices[10] = 3;
	indices[11] = 7;


	indices[12] = 4;
	indices[13] = 5;
	indices[14] = 1;

	indices[15] = 4;
	indices[16] = 1;
	indices[17] = 0;

	indices[18] = 6;
	indices[19] = 7;
	indices[20] = 3;

	indices[21] = 6;
	indices[22] = 3;
	indices[23] = 2;


	indices[24] = 5;
	indices[25] = 4;
	indices[26] = 7;

	indices[27] = 5;
	indices[28] = 7;
	indices[29] = 6;

	indices[30] = 0;
	indices[31] = 1;
	indices[32] = 2;

	indices[33] = 0;
	indices[34] = 2;
	indices[35] = 3;

	m_indexData = new INDEX32[m_figureCount];
	memcpy(m_indexData, indices, sizeof(unsigned long) * m_figureCount * 3);

	m_iBuffer->Unlock();
}
