#include "DynamicMeshHierarchy.h"
#include "Nalmak_Frame.h"
#include "Nalmak_MeshContainer.h"
#include "DeviceManager.h"



DynamicMeshHierarchy::DynamicMeshHierarchy()
{
	m_device = DeviceManager::GetInstance()->GetDevice();
}


DynamicMeshHierarchy::~DynamicMeshHierarchy()
{
}
// »À °¹¼ö ¸¸Å­ È£Ãâ
HRESULT DynamicMeshHierarchy::CreateFrame(LPCSTR Name, LPD3DXFRAME * ppNewFrame)
{
	Nalmak_Frame* frame;
	SAFE_NEW(frame, Nalmak_Frame);
	
	AllocateName(&frame->Name, Name);
	
	*ppNewFrame = frame;


	//d3dxframe_derived* frame = new d3dxframe_drived;
	//*ppNewFrame = frame;

	return S_OK;
}

HRESULT DynamicMeshHierarchy::CreateMeshContainer(
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

	AllocateName(&meshContainer->Name, Name);

	meshContainer->MeshData.Type = D3DXMESHTYPE_MESH;

	LPD3DXMESH mesh = pMeshData->pMesh;

	DWORD numFaces = mesh->GetNumFaces();


	meshContainer->pAdjacency = new DWORD[numFaces * 3];
	memcpy(meshContainer->pAdjacency, pAdjacency, sizeof(DWORD) * numFaces * 3);


	DWORD FVF = mesh->GetFVF();
	if (!(FVF & D3DFVF_NORMAL))
	{
		mesh->CloneMeshFVF(mesh->GetOptions() | D3DXMESH_32BIT, FVF | D3DFVF_NORMAL , m_device, &meshContainer->MeshData.pMesh);
		D3DXComputeNormals(meshContainer->MeshData.pMesh, meshContainer->pAdjacency);
	}
	else
	{
		mesh->CloneMeshFVF(mesh->GetOptions() | D3DXMESH_32BIT, FVF, m_device, &meshContainer->MeshData.pMesh);
	}
	meshContainer->MeshData.pMesh->CloneMeshFVF(meshContainer->MeshData.pMesh->GetOptions(),
		meshContainer->MeshData.pMesh->GetFVF(),
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

	//pSkinInfo->ConvertToIndexedBlendedMesh()


	meshContainer->pSkinInfo = pSkinInfo;
	meshContainer->pSkinInfo->AddRef(); // !!


	meshContainer->boneCount = pSkinInfo->GetNumBones();

	meshContainer->NumMaterials = NumMaterials;

	SAFE_NEW_ARR(meshContainer->offsetMatrices, Matrix, meshContainer->boneCount);
	SAFE_NEW_ARR(meshContainer->boneWorldMatrices, Matrix*, meshContainer->boneCount);
	SAFE_NEW_ARR(meshContainer->renderingMatrices, Matrix, meshContainer->boneCount);


	for (DWORD i = 0; i < meshContainer->boneCount; ++i)
		meshContainer->offsetMatrices[i] = *pSkinInfo->GetBoneOffsetMatrix(i);
	*ppNewMeshContainer = meshContainer;

	return S_OK;
}

HRESULT DynamicMeshHierarchy::DestroyFrame(LPD3DXFRAME pFrameToFree)
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

HRESULT DynamicMeshHierarchy::DestroyMeshContainer(LPD3DXMESHCONTAINER pMeshContainerToFree)
{
	Nalmak_MeshContainer* meshContainer = (Nalmak_MeshContainer*)pMeshContainerToFree;

	SAFE_DELETE_ARR(meshContainer->Name);

	SAFE_DELETE_ARR(meshContainer->pAdjacency);
	SAFE_DELETE_ARR(meshContainer->offsetMatrices);
	SAFE_DELETE_ARR(meshContainer->boneWorldMatrices);
	SAFE_DELETE_ARR(meshContainer->renderingMatrices);


	SAFE_RELEASE(meshContainer->MeshData.pMesh);
	SAFE_RELEASE(meshContainer->originalMesh);
	SAFE_RELEASE(meshContainer->pSkinInfo);

	SAFE_DELETE(meshContainer);

	return S_OK;
}

void DynamicMeshHierarchy::AllocateName(char ** _dst, const char * _src)
{
	if (!_src)
		return;

	size_t strLength = strlen(_src);

	*_dst = new char[strLength + 1];

	strcpy_s(*_dst, (strLength + 1), _src);

}

