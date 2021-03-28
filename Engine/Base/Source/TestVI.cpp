#include "..\Include\TestVI.h"



TestVI::TestVI()
{
}


TestVI::~TestVI()
{
}

void TestVI::Initialize(wstring _fp)
{
	CreateVertexBuffer();
	CreateIndexBuffer();

	SetFigureCount(32);
	SetVertexCount(25);
}

void TestVI::CreateVertexBuffer()
{
	ThrowIfFailed(m_device->CreateVertexBuffer(
		sizeof(INPUT_LAYOUT_POSITION_NORMAL_UV) * 25,
		0, // 파티클이나 각종 옵션 조절
		NULL, //D3DFVF_XYZ | D3DFVF_NORMAL | D3DFVF_TEX1 | D3DFVF_TEXCOORDSIZE2(0),
		D3DPOOL_MANAGED,
		&m_vBuffer,
		nullptr
	));

	INPUT_LAYOUT_POSITION_NORMAL_UV* vetices = nullptr;

	m_vBuffer->Lock(0, 0, (void**)&vetices, 0);

	vetices[0].position = Vector3(-30.f, 0.0f, 15.f);
	vetices[1].position = Vector3(-30.f, 0.0f, 30.f);
	vetices[2].position = Vector3(-15.f, -0.5f, 15.f);
	vetices[3].position = Vector3(-15.0f, 0.f, 30.f);
	vetices[4].position = Vector3(0.f, 0.f, 15.f);

	vetices[5].position = Vector3(0.f, 0.f, 30.f);
	vetices[6].position = Vector3(15.f, 0.f, 15.f);
	vetices[7].position = Vector3(15.f, 0.f, 30.f);
	vetices[8].position = Vector3(30.f, 0.f, 15.f);
	vetices[9].position = Vector3(30.f, 0.f, 30.f);

	vetices[10].position = Vector3(-30.f, 0.f, 0.f);
	vetices[11].position = Vector3(-15.f, 0.f, 0.f);
	vetices[12].position = Vector3(0.f, 0.f, 0.f);
	vetices[13].position = Vector3(15.f, 0.f, 0.f);
	vetices[14].position = Vector3(30.f, 0.f, 0.f);

	vetices[15].position = Vector3(-30.f, 0.f, -15.f);
	vetices[16].position = Vector3(-15.f, 0.f, -15.f);
	vetices[17].position = Vector3(0.f, 0.f, -15.f);
	vetices[18].position = Vector3(15.f, 0.f, -15.f);
	vetices[19].position = Vector3(30.f, 0.f, -15.f);

	vetices[20].position = Vector3(-30.f, 0.f, -30.f);
	vetices[21].position = Vector3(-15.f, 0.f, -30.f);
	vetices[22].position = Vector3(0.f, 0.f, -30.f);
	vetices[23].position = Vector3(15.f, 0.f, -30.f);
	vetices[24].position = Vector3(30.f, 0.f, -30.f);


	vetices[0].uv = Vector2(0, 0.25); 
	vetices[1].uv = Vector2(0, 0);
	vetices[2].uv = Vector2(0.25, 0.25);
	vetices[3].uv = Vector2(0.25, 0);
	vetices[4].uv = Vector2(0.5, 0.25);
	vetices[5].uv = Vector2(0.5, 0);
	vetices[6].uv = Vector2(0.75, 0.25);
	vetices[7].uv = Vector2(0.75, 0);
	vetices[8].uv = Vector2(1.0, 0.25);
	vetices[9].uv = Vector2(1.0, 0);
	vetices[10].uv = Vector2(0, 0.5);
	vetices[11].uv = Vector2(0.25, 0.5);
	vetices[12].uv = Vector2(0.5, 0.5);
	vetices[13].uv = Vector2(0.75, 0.5);
	vetices[14].uv = Vector2(1.0, 0.5);
	vetices[15].uv = Vector2(0, 0.75);
	vetices[16].uv = Vector2(0.25, 0.75);
	vetices[17].uv = Vector2(0.5, 0.75);
	vetices[18].uv = Vector2(0.75, 0.75);
	vetices[19].uv = Vector2(1.0, 0.75);
	vetices[20].uv = Vector2(0, 1.0);
	vetices[21].uv = Vector2(0.25, 1.0);
	vetices[22].uv = Vector2(0.5, 1.0);
	vetices[23].uv = Vector2(0.75, 1.0);
	vetices[24].uv = Vector2(1.0, 1.0);


	for (int i = 0; i < 25; ++i)
	{
		vetices[i].normal = Vector3(0,1,0);
	}


	m_vBuffer->Unlock();
}

void TestVI::CreateIndexBuffer()
{
	ThrowIfFailed(m_device->CreateIndexBuffer(
		sizeof(short) * 96,
		0,
		D3DFMT_INDEX16,
		D3DPOOL_MANAGED,
		&m_iBuffer,
		nullptr));

	short* test = nullptr;

	m_iBuffer->Lock(0, 0, (void**)&test, 0);

	test[0] = 1;
	test[1] = 2;
	test[2] = 3;
	//Second Face
	test[3] = 4;
	test[4] = 3;
	test[5] = 2;
	//Third Face
	test[6] = 3;
	test[7] = 4;
	test[8] = 5;
	// 4
	test[9] = 6;
	test[10] = 5;
	test[11] = 4;
	//5 
	test[12] = 5;
	test[13] = 6;
	test[14] = 7;
	///////////////////////////
	//6 
	test[15] = 8;
	test[16] = 7;
	test[17] = 6;
	//7
	test[18] = 7;
	test[19] = 8;
	test[20] = 9;

	test[21] = 10;
	test[22] = 9;
	test[23] = 8;

	test[24] = 11;
	test[25] = 1;
	test[26] = 12;

	test[27] = 3;
	test[28] = 12;
	test[29] = 1;
	//////////////////////
	// 3
	test[30] = 12;
	test[31] = 3;
	test[32] = 13;

	test[33] = 5;
	test[34] = 13;
	test[35] = 3;

	test[36] = 13;
	test[37] = 5;
	test[38] = 14;

	test[39] = 7;
	test[40] = 14;
	test[41] = 5;

	test[42] = 14;
	test[43] = 7;
	test[44] = 15;

	// 4
	test[45] = 9;
	test[46] = 15;
	test[47] = 7;

	test[48] = 16;
	test[49] = 11;
	test[50] = 17;

	test[51] = 12;
	test[52] = 17;
	test[53] = 11;

	test[54] = 17;
	test[55] = 12;
	test[56] = 18;

	test[57] = 13;
	test[58] = 18;
	test[59] = 12;

	//5
	test[60] = 18;
	test[61] = 13;
	test[62] = 19;

	test[63] = 14;
	test[64] = 19;
	test[65] = 13;

	test[66] = 19;
	test[67] = 14;
	test[68] = 20;

	test[69] = 15;
	test[70] = 20;
	test[71] = 14;

	test[72] = 21;
	test[73] = 16;
	test[74] = 22;

	//6
	test[75] = 17;
	test[76] = 22;
	test[77] = 16;

	test[78] = 22;
	test[79] = 17;
	test[80] = 23;

	test[81] = 18;
	test[82] = 23;
	test[83] = 17;

	test[84] = 23;
	test[85] = 18;
	test[86] = 24;

	test[87] = 19;
	test[88] = 24;
	test[89] = 18;

	//7
	test[90] = 24;
	test[91] = 19;
	test[92] = 25;

	test[93] = 20;
	test[94] = 25;
	test[95] = 19;

	for (int i = 0; i < 96; ++i)
	{
		test[i] -= 1;
	}

	m_iBuffer->Unlock();
}
