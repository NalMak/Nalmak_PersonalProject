#pragma once
#include "Component.h"
class MeshEffect_Slash :
	public Component
{
public:
	struct Desc
	{
		float emissionChange = 0;
		Vector3 scaleChange = { 0,0,0 };
	};
public:
	MeshEffect_Slash(Desc* _desc);
	~MeshEffect_Slash();

	// Component을(를) 통해 상속됨
	virtual void Initialize() override;
	virtual void Update() override;
	virtual void EachRender() override;

private:
	Vector3 m_scaleChange;
	float m_currentEmissionPower;
	float m_emissionChange;
	Mesh* m_mesh;
	Material* m_material;

};

