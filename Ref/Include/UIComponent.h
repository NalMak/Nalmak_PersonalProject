#pragma once
#include "Component.h"
class NALMAK_DLL UIComponent :
	public Component
{
public:
	UIComponent();
	virtual ~UIComponent();

	// Component��(��) ���� ��ӵ�
	virtual void Initialize() override = 0;
	virtual void Update() override;
	virtual void Release() override = 0;
	virtual void Render(Shader* _material, Mesh* _mesh) = 0;
};

