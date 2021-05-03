#pragma once
#ifndef __NALMAK_INCLUDE_H__
#define __NALMAK_INCLUDE_H__



#pragma warning(disable:4251)
#pragma warning(disable:4819)

#include <windows.h>

#include <stdlib.h>
#include <malloc.h>
#include <memory.h>
#include <tchar.h>

#include <iostream>
#include <string>
#include <cstdio>
#include <conio.h>
#include <functional> 
#include <chrono>
#include <thread>
#include <sstream>
#include <iomanip>
#include <io.h>
#include <mutex>
#include <process.h>

#include <unordered_map>
#include <vector>
#include <array>
#include <algorithm>
#include <map>
#include <queue>
#include <stack>

#include <assert.h>


#include <DirectXMath.h>
#include <d3d9.h>
#include <d3dx9.h>
#define DIRECTINPUT_VERSION	0x0800
#include <dinput.h>
#include <InitGuid.h>

#pragma comment(lib, "d3d9.lib")
#pragma comment(lib, "d3dx9.lib")
#pragma comment(lib, "dxguid.lib")
#pragma comment(lib, "dinput8.lib")

#pragma comment(lib, "fmodex64_vc.lib")



#ifdef _DEBUG
#pragma comment(lib, "PxPvdSDKDEBUG_x64.lib")
#pragma comment(lib, "PhysX3VehicleDEBUG.lib")
#pragma comment(lib, "PhysX3ExtensionsDEBUG.lib")
#pragma comment(lib, "PhysX3CookingDEBUG_x64.lib")
#pragma comment(lib, "PhysX3CharacterKinematicDEBUG_x64.lib")
#pragma comment(lib, "PxFoundationDEBUG_x64.lib")
#pragma comment(lib, "PhysX3CommonDEBUG_x64.lib")
#pragma comment(lib, "PhysX3DEBUG_x64.lib")
#else
#pragma comment(lib, "PxPvdSDK_x64.lib")
#pragma comment(lib, "PhysX3Vehicle.lib")
#pragma comment(lib, "PhysX3Extensions.lib")
#pragma comment(lib, "PhysX3Cooking_x64.lib")
#pragma comment(lib, "PhysX3CharacterKinematic_x64.lib")
#pragma comment(lib, "PxFoundation_x64.lib")
#pragma comment(lib, "PhysX3Common_x64.lib")
#pragma comment(lib, "PhysX3_x64.lib")
#endif

//#pragma comment(lib, "PxPvdSDK_x64.lib")
//#pragma comment(lib, "PhysX3Vehicle.lib")
//#pragma comment(lib, "PhysX3Extensions.lib")
//#pragma comment(lib, "PhysX3Cooking_x64.lib")
//#pragma comment(lib, "PhysX3CharacterKinematic_x64.lib")
//#pragma comment(lib, "PxFoundation_x64.lib")
//#pragma comment(lib, "PhysX3Common_x64.lib")
//#pragma comment(lib, "PhysX3_x64.lib")

using namespace DirectX;

using namespace std;

#include "fmod.h"

#include "Nalmak_Define.h"
#include "Nalmak_Function.h"
#include "Nalmak_Enum.h"
#include "Nalmak_Extern.h"
#include "Nalmak_Typedef.h"
#include "Nalmak_Struct.h"
#include "Nalmak_Math.h"
#include "Nalmak_DirectXMath.h"
#include "Nalmak_String.h"

#include "BitFlag.h"
#include "Exception.h"
#include "FileIO.h"
#include "SplineCurve.h"
#include "Collision.h"





#endif
