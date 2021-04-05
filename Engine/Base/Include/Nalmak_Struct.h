#pragma once

#ifndef __NALMAK_STRUCT_H__
#define __NALMAK_STRUCT_H__

#include "Nalmak_Include.h"

#pragma region LIGHT INFO

struct BaseLightInfo
{
	Vector3 color = Vector3(1,1,1);
	float ambientIntensity = 0.01f;
	float diffuseIntensity = 0.2f;
};

struct PointLightInfo
{
	BaseLightInfo base;

	Vector3 position;
	float radius;
};

struct DirectionalLightInfo
{
	DirectionalLightInfo() = default;
	DirectionalLightInfo(Vector3 _direction, Vector3 _color, float _intensity ,float _ambientIntensity)
	{
		direction = _direction;

		base.color = _color;
		base.diffuseIntensity = _intensity;
		base.ambientIntensity = _ambientIntensity;
	}
	BaseLightInfo base;

	Vector3 direction = Vector3(0,1,0);
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




typedef struct INDEX32
{
	unsigned long  _0;
	unsigned long  _1;
	unsigned long  _2;

}INDEX32;

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