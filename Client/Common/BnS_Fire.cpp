#include "stdafx.h"
#include "BnS_Fire.h"


BnS_Fire::BnS_Fire(Desc* _desc)
{
}


BnS_Fire::~BnS_Fire()
{
}

void BnS_Fire::Initialize()
{
	MeshRenderer::Desc mesh;
	mesh.meshName = L"plane";
	mesh.mtrlName = L"BnS_Fire";

	m_lightRadiusTimer = 0.f;
	for (int i = 0; i < 8; ++i)
	{
		Animator::Desc anim;
		anim.loop = true;
		anim.mtrlName = L"BnS_Fire";
		wstring index = Nalmak_Math::Random<wstring>(L"A", L"B", L"C");
		anim.spriteName = L"fireGround" + index;
		anim.interval = Nalmak_Math::Rand(0.02f, 0.03f);
		m_fireImage[i] = INSTANTIATE()->AddComponent<MeshRenderer>(&mesh)->SetPosition(-137 + Nalmak_Math::Rand(-20.f, 0.f), 7.f, -6.4f + Nalmak_Math::Rand(-3.f, 3.f))->SetScale(Nalmak_Math::Rand(1.f, 3.5f), 1, 1)->SetRotation(-90, -90, 0)->AddComponent<Animator>(&anim);
	}
	PointLight::Desc point;
	point.color = Vector3(0.95f, 0.6f, 0.2f);
	point.radius = 25;
	point.diffuseIntensity = 5.f;
	point.ambientIntensity = 0.2f;
	auto light = INSTANTIATE()->AddComponent<PointLight>(&point)->SetPosition(-137, 10.f, -4.4f);
	m_pointLight = light->GetComponent<PointLight>();
	m_lightTargetTime = Nalmak_Math::Rand(0.05f, 0.15f);
}

void BnS_Fire::Update()
{
	if (m_lightRadiusTimer > m_lightTargetTime)
	{
		m_lightTargetTime = Nalmak_Math::Rand(0.05f, 0.15f);
		m_lightRadiusTimer = 0.f;
		m_pointLight->SetDiffuseIntensity(Nalmak_Math::Rand(3.f, 6.f));
		m_pointLight->SetRadius(Nalmak_Math::Rand(30.f,35.f));
	}
	m_lightRadiusTimer += dTime;

}
