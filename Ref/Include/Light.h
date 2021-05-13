#pragma once
#include "Component.h"
#include "LightManager.h"
class NALMAK_DLL Light : public Component
{
public:
	Light();
	~Light();
private:
	// Component을(를) 통해 상속됨
	virtual void Initialize() override = 0;
	virtual void Update() override = 0;
protected:
	class LightManager* m_lightManager;
	LIGHT_MODE m_lightMode;
public:
	LIGHT_MODE GetLightMode() { return m_lightMode; }

};

