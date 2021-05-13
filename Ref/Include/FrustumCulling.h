#pragma once

#include "Nalmak_Include.h"

class NALMAK_DLL FrustumCulling
{
public:
	FrustumCulling();
	~FrustumCulling();

public:
	static bool IsInFrustumCulling(const Matrix& _view, const Matrix& _proj, const Vector3& _worldPos, float _radius);
};

