#include "..\Include\StaticMesh.h"



StaticMesh::StaticMesh()
{
}


StaticMesh::~StaticMesh()
{
}

void StaticMesh::Initialize(wstring _fp)
{
	//

	ThrowIfFailed(D3DXLoadMeshFromX(_fp.c_str(), D3DXMESH_32BIT |D3DXMESH_MANAGED, m_device, &m_adjacency, &m_subset, NULL, &m_subsetCount, &m_originMesh));

	unsigned long FVF = m_originMesh->GetFVF();

	if (!(FVF & D3DFVF_NORMAL))
	{
		D3DVERTEXELEMENT9		vtxElement[] =
		{
		{ 0, 0, D3DDECLTYPE_FLOAT3, D3DDECLMETHOD_DEFAULT, D3DDECLUSAGE_POSITION, 0 },
		{ 0,12,D3DDECLTYPE_FLOAT3,D3DDECLMETHOD_DEFAULT, D3DDECLUSAGE_NORMAL,  0 },
		{ 0,24,D3DDECLTYPE_FLOAT2,D3DDECLMETHOD_DEFAULT, D3DDECLUSAGE_TEXCOORD,  0 },

		D3DDECL_END()
		};
		m_originMesh->CloneMesh(m_originMesh->GetOptions(), vtxElement, m_device, &m_mesh);
		D3DXComputeNormals(m_mesh, (unsigned long*)m_adjacency->GetBufferPointer());
		D3DXComputeTangent(m_mesh, 0, 0, 0, true, (unsigned long*)m_adjacency->GetBufferPointer());
	}
	else
	{
		m_originMesh->CloneMeshFVF(m_originMesh->GetOptions(), FVF, m_device, &m_mesh);
	}

	//D3DVERTEXELEMENT9		vtxElement[] =
	//{
	//	{ 0, 0, D3DDECLTYPE_FLOAT3, D3DDECLMETHOD_DEFAULT, D3DDECLUSAGE_POSITION, 0 },
	//	{ 0, 12, D3DDECLTYPE_FLOAT3, D3DDECLMETHOD_DEFAULT, D3DDECLUSAGE_NORMAL, 0 },
	//	{ 0,24,D3DDECLTYPE_FLOAT3,D3DDECLMETHOD_DEFAULT, D3DDECLUSAGE_BINORMAL,  0 },
	//	{ 0,36,D3DDECLTYPE_FLOAT3,D3DDECLMETHOD_DEFAULT, D3DDECLUSAGE_TANGENT,  0 },
	//	{ 0,48,D3DDECLTYPE_FLOAT2,D3DDECLMETHOD_DEFAULT, D3DDECLUSAGE_TEXCOORD,0 },
	//	D3DDECL_END()
	//};
	//unsigned long FVF = 56;

	//m_originMesh->CloneMesh(m_originMesh->GetOptions(), vtxElement, m_device, &m_mesh);
	//D3DXComputeNormals(m_mesh, (unsigned long*)m_adjacency->GetBufferPointer());
	//D3DXComputeTangent(m_mesh, 0, 0, 0, true, (unsigned long*)m_adjacency->GetBufferPointer());




	D3DVERTEXELEMENT9 decl[MAX_FVF_DECL_SIZE];
	ZeroMemory(decl, sizeof(D3DVERTEXELEMENT9) * MAX_FVF_DECL_SIZE);
	m_mesh->GetDeclaration(decl);

	////////////////////////////////////////////////////////////////////////
	unsigned char positionOffset = 0;

	for (unsigned long i = 0; i < MAX_FVF_DECL_SIZE; ++i)
	{
		if (decl[i].Usage == D3DDECLUSAGE_POSITION)
		{
			positionOffset = (unsigned char)decl[i].Offset;
			break;
		}
	}
	////////////////////////////////////////////////////////////////////////

	void* vertex = nullptr;
	m_mesh->LockVertexBuffer(0, &vertex);
	m_stride = D3DXGetFVFVertexSize(FVF);
	m_vertexCount = m_mesh->GetNumVertices(); //Á¤Á¡ÀÇ °¹¼ö¸¦ ¾ò¾î¿È
	m_vertexPositionData = new Vector3[m_vertexCount];

	for (unsigned long i = 0; i < m_vertexCount; ++i)
	{
		m_vertexPositionData[i] = ((INPUT_LAYOUT_POSITION_NORMAL_UV*)vertex)[i].position;
	}

	////////////////////////////////////////////////////////////////////////



	void* indices = nullptr;
	m_mesh->LockIndexBuffer(0, &indices);
	m_figureCount = m_mesh->GetNumFaces();
	m_indexData = new INDEX32[m_figureCount];

	memcpy(m_indexData, indices, sizeof(INDEX32) * m_figureCount);

	D3DXComputeBoundingSphere((Vector3*)vertex,
		m_mesh->GetNumVertices(),
		m_mesh->GetNumBytesPerVertex(),
		&m_boundingSphereCenter,
		&m_boundingSphereRadius);

	m_mesh->UnlockVertexBuffer();
	m_mesh->UnlockIndexBuffer();
}

void StaticMesh::Release()
{
	SAFE_DELETE_ARR(m_vertexPositionData);
	SAFE_DELETE_ARR(m_indexData);

	SAFE_RELEASE(m_adjacency);
	SAFE_RELEASE(m_subset);
	SAFE_RELEASE(m_mesh);
	SAFE_RELEASE(m_originMesh);
}

void StaticMesh::Draw()
{
	for (unsigned int i = 0; i < m_subsetCount; ++i)
	{
		m_mesh->DrawSubset(i);
	}
}

void StaticMesh::BindingStreamSource(unsigned int _inputLayoutSize)
{
}

