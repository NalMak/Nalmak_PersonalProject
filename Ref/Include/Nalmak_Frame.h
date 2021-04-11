#pragma once
#include "Nalmak_Include.h"
struct Nalmak_Frame final : public D3DXFRAME
{
public:
	Nalmak_Frame()
	{
		boneWorldMatrix = { 1,0,0,0,0,1,0,0,0,0,1,0,0,0,0,1 };
		TransformationMatrix = { 1,0,0,0,0,1,0,0,0,0,1,0,0,0,0,1 };
	}
	/*	LPSTR                   Name;
		D3DXMATRIX              TransformationMatrix;

		LPD3DXMESHCONTAINER     pMeshContainer;

		struct _D3DXFRAME       *pFrameSibling;
		struct _D3DXFRAME       *pFrameFirstChild;*/
public:
	Matrix boneWorldMatrix;
};

