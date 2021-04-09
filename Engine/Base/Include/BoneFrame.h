#pragma once
#include "Nalmak_Include.h"
struct BoneFrame final : public D3DXFRAME
{
	/*	LPSTR                   Name;
		D3DXMATRIX              TransformationMatrix;

		LPD3DXMESHCONTAINER     pMeshContainer;

		struct _D3DXFRAME       *pFrameSibling;
		struct _D3DXFRAME       *pFrameFirstChild;*/
public:
	Matrix m_worldMatrix;
};

