
#ifndef __PUBLIC_DATA_H__
#define __PUBLIC_DATA_H__

#include <xstring>

using namespace std;

enum OBJECT_TAG
{
	OBJECT_TAG_DEFAULT,
	OBJECT_TAG_PLAYER,
	OBJECT_TAG_ATTACKINFO,
	OBJECT_TAG_ENVIRONMENT,
	OBJECT_TAG_ENEMY,
	OBJECT_TAG_MAX
};

const wstring g_objectTagName[OBJECT_TAG_MAX]
{
	L"Default",
	L"Player",
	L"Environment",
	L"Enemy"
};

enum OBJECT_LAYER
{
	OBJECT_LAYER_DEFAULT,
	OBJECT_LAYER_NAVIMESH,
	OBJECT_LAYER_CAMERA,
	OBJECT_LAYER_PLAYER,
	OBJECT_LAYER_PLAYER_HITBOX,
	OBJECT_LAYER_ENEMY,
	OBJECT_LAYER_ENEMY_HITBOX,
	OBJECT_LAYER_MAX
};

const wstring g_objectLayerName[OBJECT_LAYER_MAX]
{
	L"Default",
	L"NavMesh",
	L"Camera",
	L"Player",
	L"PlayerHitbox",
	L"Enemy",
	L"EnemyHitBox"
};

#endif // !__PUBLIC_DATA_H__

