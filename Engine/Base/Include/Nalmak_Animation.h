#pragma once
#include "Nalmak_Include.h"

typedef struct NALMAK_DLL Nalmak_MeshContainer final : public D3DXMESHCONTAINER
{
	DWORD boneCount = 0;

	LPD3DXMESH		originalMesh = nullptr;
	D3DXMATRIX*		offsetMatrices;
	D3DXMATRIX**	boneCombinedMatrices;
	D3DXMATRIX*		renderingMatrices;

	D3DXATTRIBUTERANGE*		attributeTable = nullptr;

	DWORD attributeTableCount = 0;
	DWORD maxVertexInfl = 0;
	LPD3DXBUFFER boneCombinationTable = nullptr;
}Nalmak_MeshContainer;

typedef struct NALMAK_DLL Nalmak_Frame final : public D3DXFRAME
{
public:
	Nalmak_Frame()
	{
		boneCombinedMatrix = { 1,0,0,0,0,1,0,0,0,0,1,0,0,0,0,1 };
		TransformationMatrix = { 1,0,0,0,0,1,0,0,0,0,1,0,0,0,0,1 };
	}
	/*	LPSTR                   Name;
	D3DXMATRIX              TransformationMatrix; // ª¿¿« ∑Œƒ√ ∞≥≥‰

	LPD3DXMESHCONTAINER     pMeshContainer;

	struct _D3DXFRAME       *pFrameSibling;
	struct _D3DXFRAME       *pFrameFirstChild;*/
public:
	Matrix boneCombinedMatrix;
}Nalmak_Frame;