#include "stdafx.h"
#include "TitleScene.h"

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
	INSTANTIATE()->AddComponent<RigidBody>(&rigid)->AddComponent<BoxCollider>()->AddComponent<MeshRenderer>(&render);

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
		MeshRenderer::Desc render;
		render.meshName = L"Arisha";
		render.mtrlName = L"Arisha_mtrl";
		RigidBody::Desc rigid;
		rigid.isKinematic = true;
		auto player = INSTANTIATE()->AddComponent<MeshCollider>()->AddComponent<RigidBody>(&rigid)->SetPosition(0.5f, -20.f, 0)->AddComponent<MeshRenderer>(&render)->SetScale(0.1f,0.1f,0.1f);
		player->SetStatic(true);
		//player->GetComponent<MeshRenderer>()->AddMaterial()
	}


	


}
