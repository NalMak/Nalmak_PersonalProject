#pragma once
#include "Light.h"
class NALMAK_DLL DirectionalLight :
	public Light
{
public:
	struct Desc
	{
		Vector3 color = Vector3(0.97f, 0.95f, 0.8f);
		float diffuseIntensity = 1.f;
		float ambientIntensity = 0.2f;
	};
public:
	DirectionalLight(Desc* _desc);
	~DirectionalLight();

	// Component��(��) ���� ��ӵ�
	virtual void Initialize() override;
	virtual void Update() override;
	virtual void PreRender() override;
	virtual void Release() override;
public:
	const DirectionalLightInfo& GetDirectionalLightInfo();
	Camera* GetLightCamera();
private:
	DirectionalLightInfo m_info;
	Camera* m_lightCam;
private:
	void CreateLightCam();
};

