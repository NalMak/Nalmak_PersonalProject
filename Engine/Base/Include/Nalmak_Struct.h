#pragma once

#ifndef __NALMAK_STRUCT_H__
#define __NALMAK_STRUCT_H__

#include "Nalmak_Include.h"

#pragma region LIGHT INFO

struct BaseLightInfo
{
	Vector3 color = Vector3(1,1,1);
	Vector3 position = { 0,0,0 };
	float ambientIntensity = 0.01f;
	float diffuseIntensity = 0.2f;
};

struct PointLightInfo
{
	BaseLightInfo base;

	float radius;
};

struct DirectionalLightInfo
{
	DirectionalLightInfo() = default;
	DirectionalLightInfo(
		const Vector3& _direction,
		const Vector3& _color,
		float _intensity ,
		float _ambientIntensity, 
		const Vector3& _lightPos,
		const Matrix& _lightViewProj)
	{
		direction = _direction;
		lightViewProj = _lightViewProj;

		base.position = _lightPos;
		base.color = _color;
		base.diffuseIntensity = _intensity;
		base.ambientIntensity = _ambientIntensity;
	}
	BaseLightInfo base;

	Vector3 direction = Vector3(0,1,0);
	Matrix	lightViewProj;
};	
#pragma endregion LIGHT INFO



/////////////////////////////////////////////////////////////////////////////////
// ���� ��� ����
// ���̴��� �ٲ� �� ���� ���������� �� �����ʹ� ������ ������
#pragma region Constant Buffer

struct ConstantBuffer
{
	Matrix viewProj;
	Matrix invView;
	Matrix invProj;
	Vector3 worldCamPos;
	Vector3 worldCamLook;
	float time;
};
#pragma endregion Constant Buffer
//
/////////////////////////////////////////////////////////////////////////////////

typedef struct INDEX16
{
	unsigned short _0;
	unsigned short _1;
	unsigned short _2;
}INDEX16;


typedef struct INDEX32
{
	unsigned long  _0;
	unsigned long  _1;
	unsigned long  _2;

}INDEX32;


typedef struct Nalmak_MeshContainer final : public D3DXMESHCONTAINER
{
	DWORD boneCount = 0;

	LPD3DXMESH		originalMesh = nullptr;
	D3DXMATRIX*		offsetMatrices;
	D3DXMATRIX**	boneCombinedMatrices;
	D3DXMATRIX*		renderingMatrices;

	DWORD attributeTableCount = 0;
	DWORD maxVertexInfl = 0;
	LPD3DXBUFFER boneCombinationTable = nullptr;
}Nalmak_MeshContainer;


typedef struct Nalmak_Frame final : public D3DXFRAME
{
public:
	Nalmak_Frame()
	{
		boneCombinedMatrix = { 1,0,0,0,0,1,0,0,0,0,1,0,0,0,0,1 };
		TransformationMatrix = { 1,0,0,0,0,1,0,0,0,0,1,0,0,0,0,1 };
	}
	/*	LPSTR                   Name;
	D3DXMATRIX              TransformationMatrix; // ���� ���� ����

	LPD3DXMESHCONTAINER     pMeshContainer;

	struct _D3DXFRAME       *pFrameSibling;
	struct _D3DXFRAME       *pFrameFirstChild;*/
public:
	Matrix boneCombinedMatrix;
}Nalmak_Frame;

/////////////////////////////////////////////////////////////////////////////////
// INPUT LAYOUT �߰� �� �� �ؾ��Ұ�!!
//  1. VERTEX_INPUT_LAYOUT enum �߰� 
//  2. Shader Initialize inputLayout���� �б⹮ �߰�
#pragma region INPUT_LAYOUT
struct INPUT_LAYOUT_POSITION
{
	Vector3 position;
};

struct INPUT_LAYOUT_POSITION_COLOR
{
	Vector3 position;
	Vector3 color;
};

struct INPUT_LAYOUT_POSITION_UV
{
	Vector3 position;
	Vector2 uv;
};


struct INPUT_LAYOUT_POSITION_NORMAL_UV
{
	Vector3 position;
	Vector3 normal;
	Vector2 uv;
};

struct INPUT_LAYOUT_POSITION_NORMAL_BINORMAL_TANGENT_UV
{
	Vector3 position;
	Vector3 normal;
	Vector3 binormal;
	Vector3 tangent;
	Vector2 uv;

	bool operator == (const INPUT_LAYOUT_POSITION_NORMAL_BINORMAL_TANGENT_UV& other) const
	{
		
		return position == other.position &&
			normal == other.normal &&
			binormal == other.binormal &&
			tangent == other.tangent &&
			uv == other.uv;
	}
	bool operator > (const INPUT_LAYOUT_POSITION_NORMAL_BINORMAL_TANGENT_UV& other) const
	{
		return position + normal + binormal + tangent + Vector3(uv.x, uv.y, 0) >
			other.position + other.normal + other.binormal + other.tangent + Vector3(other.uv.x, other.uv.y, 0);
	}
};



struct INPUT_LAYOUT_SKYBOX
{
	Vector3 position;
	Vector3 uvw;
};

struct INPUT_LAYOUT_PARTICLE
{
	Matrix worldMatrix;
	Vector4 color;
	Vector3 spriteX_spriteY_index;
};




// �ϴ� �Ⱦ�
//struct INPUT_LAYOUT_STATIC_MESH
//{
//	Matrix worldMatrix;
//};

#pragma endregion INPUT_LAYOUT
//
/////////////////////////////////////////////////////////////////////////////////





struct TextureBuffer
{
	PDIRECT3DTEXTURE9 name;
	Vector4 color;
	Vector2 uvScaling;
};



class AudioClip;

struct AudioChannel
{
	FMOD_CHANNEL* channel = nullptr;
	AudioClip* currentClip = nullptr;

	// if 3D Use
	Vector3* position = nullptr;
	////////////////////////////////
};

#endif