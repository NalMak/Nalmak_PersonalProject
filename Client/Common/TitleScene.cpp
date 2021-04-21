#include "stdafx.h"
#include "TitleScene.h"
#include "TestPlayer.h"
#include "Homework_Player.h"
#include "Player.h"
#include "PlayerIdle.h"


TitleScene::TitleScene()
{
}


TitleScene::~TitleScene()
{
}

void TitleScene::Initialize()
{

	DirectionalLight::Desc light;
	light.diffuseIntensity = 0.8f;
	light.ambientIntensity = 0.3f;
	INSTANTIATE()->AddComponent<DirectionalLight>(&light)->SetRotation(15, 70, 0)->AddComponent<Homework_Player>();


	auto cam = INSTANTIATE()->AddComponent<Camera>()->SetPosition(0,0,-10);
	
	INSTANTIATE()->AddComponent<DebuggingMode>();

	
	{
		MeshRenderer::Desc mesh;
		mesh.meshName = L"plane";
		RigidBody::Desc rigid;
		rigid.isKinematic = true;
		rigid.isGravity = false;
		auto plane = INSTANTIATE()->AddComponent<MeshRenderer>(&mesh)->AddComponent<MeshCollider>()->SetScale(10, 10, 10)->SetPosition(0, -10, 0);
		plane->SetLayer(OBJECT_LAYER_BACKGROUND);
	}

	{
		MeshRenderer::Desc render;
		render.meshName = L"sphere";
		for(int i = 0 ; i < 10; ++i)
			INSTANTIATE()->AddComponent<RigidBody>()->AddComponent<SphereCollider>()->AddComponent<MeshRenderer>(&render)->SetPosition(Nalmak_Math::RandDirection() * Nalmak_Math::Rand(0.f, 10.f) + Vector3(0, 5, 0));
	}
	/*{
		auto obj = INSTANTIATE();
		SkinnedMeshRenderer::Desc render;
		render.meshName = L"lyn_test";
		render.mtrlName = L"lyn_test1";
		AnimationController::Desc anim;
		anim.meshName = L"lyn_test";
		obj->AddComponent<SkinnedMeshRenderer>(&render);
		obj->GetComponent<SkinnedMeshRenderer>()->SetFrustumCulling(false);

		obj->AddComponent<Player>();
		CharacterController::Desc controller;
		controller.height = 2.f;
		controller.center = { 0,1.3f,0 };
		controller.stepOffset = 0.5f;
		controller.slopeLimit = 80;
		obj->AddComponent<CharacterController>(&controller);
		obj->AddComponent<AnimationController>(&anim);
		obj->GetComponent<AnimationController>()->AddAnimationClip("Anim1", 1.f, true, false);
		obj->GetComponent<AnimationController>()->SetEntryClip("Anim1");
		obj->AddComponent<StateControl>();
		obj->GetComponent<StateControl>()->AddState<PlayerIdle>(L"idle");
		obj->GetComponent<StateControl>()->InitState(L"idle");

		obj->SetScale(0.1f, 0.1f, 0.1f)->SetPosition(0, 10, -3);
	}*/

	//MAKE_STATIC(L"building")->AddComponent<MeshCollider>();
	{
		MeshRenderer::Desc render;
		render.meshName = L"cylinder";
		render.mtrlName = L"SYS_Standard_NormalMap";
		auto cylinder = INSTANTIATE()->AddComponent<MeshRenderer>(&render)->AddComponent<LOD_Group>();
		cylinder->GetComponent<LOD_Group>()->AddLODMesh(L"cylinder", 0.1f);
		cylinder->GetComponent<LOD_Group>()->AddLODMesh(L"box", 0.3f);
		cylinder->GetComponent<LOD_Group>()->AddLODMesh(L"lyn_test", 0.4f);
	}


	NavCollider::Desc navCollider;
	navCollider.navName = L"default";
	INSTANTIATE()->AddComponent<NavCollider>(&navCollider);
}
