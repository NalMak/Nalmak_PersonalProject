#pragma once
#include "Nalmak_Include.h"

class MeshHierarchy final : public ID3DXAllocateHierarchy
{
public:
	MeshHierarchy();
	~MeshHierarchy();

public:
	// ID3DXAllocateHierarchy을(를) 통해 상속됨
	virtual HRESULT CreateFrame(LPCSTR Name, LPD3DXFRAME * ppNewFrame) override;

	virtual HRESULT CreateMeshContainer(LPCSTR Name, CONST D3DXMESHDATA * pMeshData, CONST D3DXMATERIAL * pMaterials, CONST D3DXEFFECTINSTANCE * pEffectInstances, DWORD NumMaterials, CONST DWORD * pAdjacency, LPD3DXSKININFO pSkinInfo, LPD3DXMESHCONTAINER * ppNewMeshContainer) override;

	virtual HRESULT DestroyFrame(LPD3DXFRAME pFrameToFree) override;

	virtual HRESULT DestroyMeshContainer(LPD3DXMESHCONTAINER pMeshContainerToFree) override;

private:
	void AllocateName(char ** _dst, const char * _src);
	LPDIRECT3DDEVICE9 m_device;
};

