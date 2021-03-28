#pragma once
#ifndef __NALMAK_TYPEDEF_H__
#define __NALMAK_TYPEDEF_H__


typedef D3DXVECTOR2 Vector2;
typedef D3DXVECTOR3 Vector3;
typedef D3DXVECTOR4 Vector4;
typedef D3DXMATRIX Matrix;
typedef D3DXQUATERNION Quaternion;

typedef int _OBJECT_TAG;
typedef int _RENDER_LAYER;
typedef int _RENDER_QUEUE;
typedef int _COLLISION_LAYER;
typedef int _SOUND_CHANNEL;
typedef int _CANVAS_GROUP;


typedef function<int(void)> GetIntFunc;
typedef function<void(int*, function<int(void)>)>  SetIntFunc;
typedef function<float(void)> GetFloatFunc;
typedef function<void(float*, function<float(void)>)>  SetFloatFunc;
typedef function<Vector2(void)> GetVector2Func;
typedef function<void(Vector2*, function<Vector2(void)>)>  SetVector2Func;
typedef function<Vector3(void)> GetVector3Func;
typedef function<void(Vector3*, function<Vector3(void)>)>  SetVector3Func;

#endif