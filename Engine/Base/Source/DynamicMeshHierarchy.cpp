#include "DynamicMeshHierarchy.h"



DynamicMeshHierarchy::DynamicMeshHierarchy()
{
}


DynamicMeshHierarchy::~DynamicMeshHierarchy()
{
}

HRESULT DynamicMeshHierarchy::CreateFrame(LPCSTR Name, LPD3DXFRAME * ppNewFrame)
{
	//d3dxframe_derived* frame = new d3dxframe_drived;
	//*ppNewFrame = frame;

	return E_NOTIMPL;
}

HRESULT DynamicMeshHierarchy::CreateMeshContainer(LPCSTR Name, CONST D3DXMESHDATA * pMeshData, CONST D3DXMATERIAL * pMaterials, CONST D3DXEFFECTINSTANCE * pEffectInstances, DWORD NumMaterials, CONST DWORD * pAdjacency, LPD3DXSKININFO pSkinInfo, LPD3DXMESHCONTAINER * ppNewMeshContainer)
{
	return E_NOTIMPL;
}

HRESULT DynamicMeshHierarchy::DestroyFrame(LPD3DXFRAME pFrameToFree)
{
	return E_NOTIMPL;
}

HRESULT DynamicMeshHierarchy::DestroyMeshContainer(LPD3DXMESHCONTAINER pMeshContainerToFree)
{
	return E_NOTIMPL;
}

