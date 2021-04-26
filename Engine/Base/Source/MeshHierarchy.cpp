#include "MeshHierarchy.h"
#include "DeviceManager.h"
#include "Nalmak_Animation.h"


MeshHierarchy::MeshHierarchy()
{
	m_device = DeviceManager::GetInstance()->GetDevice();
}


MeshHierarchy::~MeshHierarchy()
{
}
// »À °¹¼ö ¸¸Å­ È£Ãâ
HRESULT MeshHierarchy::CreateFrame(LPCSTR Name, LPD3DXFRAME * ppNewFrame)
{
	Nalmak_Frame* frame;
	SAFE_NEW(frame, Nalmak_Frame);
	
	CopyHeap(&frame->Name, Name);
	
	*ppNewFrame = frame;


	//d3dxframe_derived* frame = new d3dxframe_drived;
	//*ppNewFrame = frame;

	return S_OK;
}

HRESULT MeshHierarchy::CreateMeshContainer(
	LPCSTR Name,
	CONST D3DXMESHDATA * pMeshData,
	CONST D3DXMATERIAL * pMaterials,
	CONST D3DXEFFECTINSTANCE * pEffectInstances,
	DWORD NumMaterials,
	CONST DWORD * pAdjacency,
	LPD3DXSKININFO pSkinInfo, 
	LPD3DXMESHCONTAINER * ppNewMeshContainer)
{
	Nalmak_MeshContainer* meshContainer;
	SAFE_NEW(meshContainer,Nalmak_MeshContainer);

	CopyHeap(&meshContainer->Name, Name);

	meshContainer->MeshData.Type = D3DXMESHTYPE_MESH;

	LPD3DXMESH mesh = pMeshData->pMesh;

	DWORD numFaces = mesh->GetNumFaces();


	meshContainer->pAdjacency = new DWORD[numFaces * 3];
	memcpy(meshContainer->pAdjacency, pAdjacency, sizeof(DWORD) * numFaces * 3);


	D3DVERTEXELEMENT9 decl[MAX_FVF_DECL_SIZE] =
	{
		{ 0,0,D3DDECLTYPE_FLOAT3,D3DDECLMETHOD_DEFAULT, D3DDECLUSAGE_POSITION, 0 },
		{ 0,12,D3DDECLTYPE_FLOAT3,D3DDECLMETHOD_DEFAULT, D3DDECLUSAGE_NORMAL,  0 },
		{ 0,24,D3DDECLTYPE_FLOAT3,D3DDECLMETHOD_DEFAULT, D3DDECLUSAGE_BINORMAL,  0 },
		{ 0,36,D3DDECLTYPE_FLOAT3,D3DDECLMETHOD_DEFAULT, D3DDECLUSAGE_TANGENT,  0 },
		{ 0,48,D3DDECLTYPE_FLOAT2,D3DDECLMETHOD_DEFAULT, D3DDECLUSAGE_TEXCOORD,0 },
		D3DDECL_END()
	};

	mesh->CloneMesh(mesh->GetOptions() | D3DXMESH_32BIT, decl, m_device, &meshContainer->MeshData.pMesh);


	D3DXComputeNormals(meshContainer->MeshData.pMesh, meshContainer->pAdjacency);
	D3DXComputeTangent(meshContainer->MeshData.pMesh, 0, 0, 0, 0, (DWORD*)meshContainer->pAdjacency);

	meshContainer->MeshData.pMesh->CloneMesh(meshContainer->MeshData.pMesh->GetOptions(),
		decl,
		m_device,
		&meshContainer->originalMesh);

	meshContainer->NumMaterials = (NumMaterials == 0 ? 1 : NumMaterials);

	//SAFE_NEW_ARR(meshContainer->pMaterials, D3DXMATERIAL, meshContainer->NumMaterials);



	///////////////////////////////////////////////////////////////////////////////////////////////
	// need skin info
	///////////////////////////////////////////////////////////////////////////////////////////////
	if (!pSkinInfo)
	{
		*ppNewMeshContainer = meshContainer;
		return S_OK;
	}
	unsigned char offset;

	D3DVERTEXELEMENT9			Decl[MAX_FVF_DECL_SIZE];
	ZeroMemory(Decl, sizeof(D3DVERTEXELEMENT9) * MAX_FVF_DECL_SIZE);

	meshContainer->MeshData.pMesh->GetDeclaration(Decl);

	for (DWORD i = 0; i < MAX_FVF_DECL_SIZE; ++i)
	{
		if (Decl[i].Usage == D3DDECLUSAGE_TANGENT)
		{
			offset = (unsigned char)Decl[i].Offset;
		}
		if (Decl[i].Usage == D3DDECLUSAGE_NORMAL)
		{
			offset = (unsigned char)Decl[i].Offset;
		}
		if (Decl[i].Usage == D3DDECLUSAGE_BINORMAL)
		{
			offset = (unsigned char)Decl[i].Offset;
		}
	}


	meshContainer->pSkinInfo = pSkinInfo;
	meshContainer->pSkinInfo->AddRef(); // !!

	meshContainer->boneCount = pSkinInfo->GetNumBones();


	SAFE_NEW_ARR(meshContainer->offsetMatrices, Matrix, meshContainer->boneCount);
	SAFE_NEW_ARR(meshContainer->boneCombinedMatrices, Matrix*, meshContainer->boneCount);


	for (DWORD i = 0; i < meshContainer->boneCount; ++i)
		meshContainer->offsetMatrices[i] = *pSkinInfo->GetBoneOffsetMatrix(i);
	*ppNewMeshContainer = meshContainer;

	return S_OK;
}

HRESULT MeshHierarchy::DestroyFrame(LPD3DXFRAME pFrameToFree)
{
	SAFE_DELETE_ARR(pFrameToFree->Name);

	if (pFrameToFree->pMeshContainer)
		DestroyMeshContainer(pFrameToFree->pMeshContainer);

	if (pFrameToFree->pFrameFirstChild)
		DestroyFrame(pFrameToFree->pFrameFirstChild);

	if (pFrameToFree->pFrameSibling)
		DestroyFrame(pFrameToFree->pFrameSibling);

	SAFE_DELETE(pFrameToFree);

	return S_OK;
}

HRESULT MeshHierarchy::DestroyMeshContainer(LPD3DXMESHCONTAINER pMeshContainerToFree)
{
	Nalmak_MeshContainer* meshContainer = (Nalmak_MeshContainer*)pMeshContainerToFree;

	SAFE_DELETE_ARR(meshContainer->Name);

	SAFE_DELETE_ARR(meshContainer->pAdjacency);
	SAFE_DELETE_ARR(meshContainer->offsetMatrices);
	SAFE_DELETE_ARR(meshContainer->boneCombinedMatrices);


	SAFE_RELEASE(meshContainer->MeshData.pMesh);
	SAFE_RELEASE(meshContainer->originalMesh);
	SAFE_RELEASE(meshContainer->pSkinInfo);

	SAFE_DELETE(meshContainer);

	return S_OK;
}

void MeshHierarchy::CopyHeap(char ** _dst, const char * _src)
{
	if (!_src)
		return;

	size_t strLength = strlen(_src);

	*_dst = new char[strLength + 1];

	strcpy_s(*_dst, (strLength + 1), _src);

}

