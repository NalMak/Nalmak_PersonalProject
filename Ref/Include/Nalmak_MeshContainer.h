#pragma once

#include "Nalmak_Include.h"

struct Nalmak_MeshContainer final : public D3DXMESHCONTAINER
{
	DWORD boneCount = 0;

	LPD3DXMESH		originalMesh = nullptr;
	D3DXMATRIX*		offsetMatrices;
	D3DXMATRIX**	boneCombinedMatrices;
	D3DXMATRIX*		renderingMatrices;

	DWORD attributeTableCount = 0;
	DWORD maxVertexInfl;
	LPD3DXBUFFER boneCombinationTable = nullptr;
};

