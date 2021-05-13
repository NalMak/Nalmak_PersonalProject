#pragma once
#include "Component.h"
class NALMAK_DLL UIComponent :
	public Component
{
public:
	UIComponent();
	virtual ~UIComponent();

	// Component을(를) 통해 상속됨
	virtual void Initialize() override = 0;
	virtual void Update() override;
	virtual void Release() override = 0;
	virtual void Render(Shader* _material, Mesh* _mesh) = 0;
};

