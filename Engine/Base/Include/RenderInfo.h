#pragma once
#include "Nalmak_Include.h"

class IRenderer;

struct RenderInfo
{
	IRenderer* renderer = nullptr;
	UINT containerNum = 0;
	UINT subsetNum = 0;
};


