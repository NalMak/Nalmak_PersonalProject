#include "stdafx.h"
#include "TitleScene.h"
#include "TestPlayer.h"

TitleScene::TitleScene()
{
}


TitleScene::~TitleScene()
{
}

void TitleScene::Initialize()
{
	
	/*TestComponent::Desc test2;
	test2.obj = test;
	INSTANTIATE()->AddComponent<TestComponent>(&test2);*/
	DirectionalLight::Desc light;
	light.diffuseIntensity = 0.8f;
	INSTANTIATE()->AddComponent<DirectionalLight>(&light)->SetRotation(0, 180, 0);
	auto cam = INSTANTIATE()->AddComponent<Camera>()->SetPosition(0,0,-10);
	INSTANTIATE()->AddComponent<DebuggingMode>();

	RigidBody::Desc rigid;
	rigid.isKinematic = true;
	MeshRenderer::Desc render;
	render.meshName = L"box";
	INSTANTIATE()->AddComponent<MeshRenderer>(&render)->SetRotation(30,30,0)->AddComponent<MeshCollider>();

	for (int i = 0; i < 10; ++i)
	{
		RigidBody::Desc rigid;
		//rigid.isKinematic = true;
		MeshRenderer::Desc render;
		MeshRenderer::Desc mesh;
		mesh.meshName = L"sphere";
		mesh.mtrlName = L"test1";
		Vector3 dir = Nalmak_Math::RandDirection();
		if (dir.y < 0)
			dir.y *= -1;
		auto sphere = INSTANTIATE()->AddComponent<RigidBody>(&rigid)->AddComponent<MeshRenderer>(&mesh)->AddComponent<ParticleRenderer>()->AddComponent<SphereCollider>()->AddComponent<PointLight>()->SetPosition(dir * Nalmak_Math::Rand(0.f, 10.f) + Vector3(0,5,0));
		cam->SetParents(sphere);
	}

	{
		//MeshRenderer::Desc render;
		//render.meshName = L"Arisha";
		//render.mtrlName = L"Arisha_mtrl";
		//RigidBody::Desc rigid;
		//rigid.isKinematic = true;
		//auto player = INSTANTIATE()->AddComponent<MeshCollider>()->AddComponent<RigidBody>(&rigid)->SetPosition(0.5f, -20.f, 0)->AddComponent<MeshRenderer>(&render)->SetScale(0.1f,0.1f,0.1f);
		//player->SetStatic(true);
		//player->GetComponent<MeshRenderer>()->AddMaterial()
	}
	{
		MeshRenderer::Desc mesh;
		mesh.meshName = L"plane";
		RigidBody::Desc rigid;
		rigid.isKinematic = true;
		INSTANTIATE()->AddComponent<MeshRenderer>(&mesh)->AddComponent<MeshCollider>()->SetScale(10, 10, 10)->SetPosition(0, -10, 0);
	}

	{
		MeshRenderer::Desc render;
		render.meshName = L"f15";
		RigidBody::Desc rigid;
		rigid.isGravity = false;
		INSTANTIATE()->AddComponent<MeshRenderer>(&render)->AddComponent<RigidBody>(&rigid)->SetPosition(0,5,0);
	}

	
	INSTANTIATE()->AddComponent<MeshRenderer>()->AddComponent<RigidBody>()->AddComponent<CapsuleCollider>()->AddComponent<BoxCollider>()->AddComponent<TestPlayer>()->SetPosition(0,3,0);

}
