#pragma once

#include "Nalmak_Include.h"

struct Nalmak_MeshContainer final : public D3DXMESHCONTAINER
{
	unsigned int boneCount;

	LPD3DXMESH		originalMesh;
	D3DXMATRIX*		offsetMatrices;
	D3DXMATRIX**	boneWorldMatrices;
	D3DXMATRIX*		renderingMatrices;
};

