#pragma once

#ifndef __NALMAK_STRUCT_H__
#define __NALMAK_STRUCT_H__

#include "Nalmak_Include.h"

#pragma region LIGHT INFO


struct RenderInfo
{
	class IRenderer* renderer = nullptr;
	UINT containerNum = 0;
	UINT subsetNum = 0;
};

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
// 공용 상수 버퍼
// 쉐이더가 바뀔 때 마다 공통적으로 이 데이터는 정보를 보내줌
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







/////////////////////////////////////////////////////////////////////////////////
// INPUT LAYOUT 추가 시 꼭 해야할것!!
//  1. VERTEX_INPUT_LAYOUT enum 추가 
//  2. Shader Initialize inputLayout마다 분기문 추가
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

struct INPUT_LAYOUT_POSITION_NORMAL_UV_ANIMATIONBLENDING
{
	Vector3 position;
	Vector3 normal;
	Vector2 uv;
	Vector4 weight;
	Vector4 boneIndex;
};


// 일단 안씀
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