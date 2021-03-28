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




// 일단 안씀
//struct INPUT_LAYOUT_STATIC_MESH
//{
//	Matrix worldMatrix;
//};

#pragma endregion INPUT_LAYOUT
//
/////////////////////////////////////////////////////////////////////////////////

struct NALMAK_DLL ParticleData
{
	Vector3 posOffset;
	Quaternion rotOffset;

	PARTICLE_EMIT_SHAPE shape = PARTICLE_EMIT_SHAPE::PARTICLE_EMIT_SHAPE_SPHERE;
	PARTICLE_BILLBOARD_TYPE billboard = PARTICLE_BILLBOARD_TYPE::PARTICLE_BILLBOARD_TYPE_DEFAULT;
	// for Circle
	// for Sphere 
	float minRadius = 0.2f;
	float maxRadius = 0.3f;

	// for box
	float width = 1.f;
	float height = 1.f;
	float depth = 1.f;

	// for cone
	float coneAngle = 45.f * Deg2Rad;

	float startMinSpeed = 0.1f;
	float startMaxSpeed = 0.1f;
	float endMinSpeed = 0.1f;
	float endMaxSpeed = 0.15f;

	UINT emittorCount = 30;
	float duration = 5.f;
	float minAwakeTime = 0.f;
	float maxAwakeTime = 0.f;


	Vector3 force = Vector3(0, 0, 0);

	float gravity = 0.f;

	float minAngle = 0.f;
	float maxAngle = 0.f;

	float minAngularVelocity = 0.f;
	float maxAngularVelocity = 0.f;

	float startMinScale = 0.1f;
	float startMaxScale = 0.2f;
	float endMinScale = 0.15f;
	float endMaxScale = 0.2f;


	Vector4 startMinColor = Vector4(1, 1, 1, 1);
	Vector4 startMaxColor = Vector4(1, 1, 1, 1);
	Vector4 endMinColor = Vector4(0, 0, 0, 0);
	Vector4 endMaxColor = Vector4(0, 0, 0, 0);

	float minLifeTime = 3;
	float maxLifeTime = 5;

	float stretchedScale = 2.f;
	int animationTileX = 1;
	int animationTileY = 1;

	int maxParticleCount = 300;

	bool  isLoop = true;
	bool  isPlay = true;
	bool isPlayOnAwake = true;
	bool isLocal = false;
	bool isVelocityLocal = false;
};

struct TextureBuffer
{
	PDIRECT3DTEXTURE9 name;
	Vector4 color;
	Vector2 uvScaling;
};

struct Line
{
	Vector3 start, end;
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