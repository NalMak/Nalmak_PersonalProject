#include "stdafx.h"
#include "TitleScene.h"
#include "Homework_Player.h"

#include "BnS_MainCamera.h"

#include "LynStateControl.h"
#include "LynIdle.h"
#include "LynRun.h"
#include "LynTurning.h"
#include "LynIdleToJump.h"
#include "LynJump.h"
#include "LynJumpToIdle.h"
#include "LynJumpToMove.h"

#include "LynMove.h"

TitleScene::TitleScene()
{
}


TitleScene::~TitleScene()
{
}

void TitleScene::Initialize()
{
	/*INSTANTIATE()->AddComponent<Camera>()->SetPosition(0,0,-5);
	INSTANTIATE()->AddComponent<DebuggingMode>();
	MeshRenderer::Desc homework;
	homework.mtrlName = L"homework";
	INSTANTIATE()->AddComponent<MeshRenderer>(&homework);*/


	MAKE_STATIC(L"column");
	MAKE_STATIC(L"floor");
	MAKE_STATIC(L"plane");
	MAKE_STATIC(L"roof");
	MAKE_STATIC(L"mainLight");
	MAKE_STATIC(L"wall");


	INSTANTIATE()->AddComponent<ParticleRenderer>()->SetPosition(0,3,0);

	/*for (int i = 0; i < 70; ++i)
	{
		PointLight::Desc point;
		point.diffuseIntensity = Nalmak_Math::Rand(10.f, 30.f);
		point.radius = Nalmak_Math::Rand(10.f, 60.f);
		point.color = Nalmak_Math::RandColor();
		INSTANTIATE()->AddComponent<PointLight>(&point)->SetPosition(Nalmak_Math::RandDirection() * Nalmak_Math::Rand(0.f, 100.f));
	}*/
	

	DirectionalLight::Desc light;
	light.diffuseIntensity = 0.6f;
	light.ambientIntensity = 0.1f;
	INSTANTIATE()->AddComponent<DirectionalLight>(&light)->SetRotation(90, 0, 0);


	
	DebuggingMode::Desc debug;
	debug.createDirectoryMonitor = true;
	auto obj = INSTANTIATE()->AddComponent<DebuggingMode>(&debug);
	//MAKE_STATIC(L"musin_boss_floor");
	{
		MeshRenderer::Desc mesh;
		mesh.meshName = L"plane";
		RigidBody::Desc rigid;
		rigid.isKinematic = true;
		rigid.isGravity = false;
		auto plane = INSTANTIATE()->AddComponent<MeshRenderer>(&mesh)->AddComponent<MeshCollider>()->SetScale(10, 10, 10)->SetPosition(0, 0.5f, 0);
		plane->SetLayer(OBJECT_LAYER_BACKGROUND);
	}

	



	NavCollider::Desc navCollider;
	navCollider.navName = L"default";
	INSTANTIATE()->AddComponent<NavCollider>(&navCollider);


	auto lyn = INSTANTIATE();// ->SetRotation(0, -90, 0);
	auto cam = INSTANTIATE();

	lyn->AddComponent<LynMove>();

	SkinnedMeshRenderer::Desc skin;
	skin.meshName = L"Lyn_Model2";
	skin.mtrlName = L"lyn_hair";
	lyn->AddComponent<SkinnedMeshRenderer>(&skin);
	lyn->AddComponent<LynInfo>();
	lyn->AddComponent<DebugObject>();
	AnimationController::Desc anim;
	anim.meshName = L"Lyn_Model2";
	Matrix rotMat;
	anim.rootMatrix = *D3DXMatrixRotationY(&rotMat, -90 * Deg2Rad);
	lyn->AddComponent<AnimationController>(&anim)->SetScale(0.1f,0.1f,0.1f);

	//lyn->AddComponent<LynStateControl>();
	////lyn->AddComponent<LynStateControl>();

	//lyn->GetComponents<LynStateControl>()[0]->AddState<LynIdle>(L"idle");
	//lyn->GetComponents<LynStateControl>()[0]->AddState<LynRun>(L"run");
	//lyn->GetComponents<LynStateControl>()[0]->AddState<LynTurning>(L"turning");
	//lyn->GetComponents<LynStateControl>()[0]->AddState<LynIdleToJump>(L"idleToJump");
	//lyn->GetComponents<LynStateControl>()[0]->AddState<LynJump>(L"jump");
	//lyn->GetComponents<LynStateControl>()[0]->AddState<LynJumpToIdle>(L"jumpToIdle");
	//lyn->GetComponents<LynStateControl>()[0]->AddState<LynJumpToMove>(L"jumpToMove");

	//lyn->GetComponents<LynStateControl>()[0]->InitState(L"idle");

	lyn->GetComponent<SkinnedMeshRenderer>()->SetFrustumCullingState(FRUSTUM_CULLING_STATE_FREE_PASS);
	lyn->GetComponent<SkinnedMeshRenderer>()->SetMaterial(L"lyn_body",0);
	lyn->GetComponent<SkinnedMeshRenderer>()->AddMaterial(L"lyn_face");
	lyn->GetComponent<SkinnedMeshRenderer>()->AddMaterial(L"lyn_hair2");

	CharacterController::Desc character;
	character.center = { 0,2.6f,0 };
	character.height = 3.2f;
	lyn->AddComponent<CharacterController>(&character);
	
	AnimationController* controller = lyn->GetComponent<AnimationController>();


	controller->AddAnimationClip("Lyn_P_Std_Idle_Event1", 1.f, false);
	controller->AddAnimationClip("Lyn_P_Std_Idle_Event2", 1.f, false);
	controller->AddAnimationClip("Lyn_P_Std_Idle_Event3", 1.f, false);
	controller->AddAnimationClip("Lyn_P_Std_Idle_Event4", 1.f, false);

	controller->AddAnimationClip("Lyn_P_Std_Mov_LeftToRight", 1.f, false);
	controller->AddAnimationClip("Lyn_P_Std_Mov_RightToLeft", 1.f, false);


	controller->AddAnimationClip("Lyn_P_Std_Mov_RunRight", 1.3f, true);
	controller->AddAnimationClip("Lyn_P_Std_Mov_RunFront", 1.3f, true);
	controller->AddAnimationClip("Lyn_P_Std_Mov_RunLeft", 1.3f, true);
	controller->AddAnimationClip("Lyn_P_Std_Mov_RunRightBack", 1.f, true);
	controller->AddAnimationClip("Lyn_P_Std_Mov_RunLeftBack", 1.f, true);
	controller->AddAnimationClip("Lyn_P_Std_Mov_RunBack", 1.2f, true);
	controller->AddAnimationClip("Lyn_P_Std_Mov_RunRightFront", 1.3f, true);
	controller->AddAnimationClip("Lyn_P_Std_Mov_RunLeftFront", 1.3f, true);

	controller->AddAnimationClip("Lyn_P_Std_Mov_IdleToJump_Front", 1.1f, false);
	controller->AddAnimationClip("Lyn_P_Std_Mov_IdleToJump_Left", 1.1f, false);
	controller->AddAnimationClip("Lyn_P_Std_Mov_IdleToJump_Right", 1.1f, false);

	controller->AddAnimationClip("Lyn_P_Std_Mov_JumpFront", 1.f, true);
	controller->AddAnimationClip("Lyn_P_Std_Mov_JumpLeft", 1.f, true);
	controller->AddAnimationClip("Lyn_P_Std_Mov_JumpRight", 1.f, true);
	controller->AddAnimationClip("Lyn_P_Std_Mov_JumpToIdle", 1.f, true);

	controller->AddAnimationClip("Lyn_P_Std_Mov_JumpToMove_Back", 1.f, false);
	controller->AddAnimationClip("Lyn_P_Std_Mov_JumpToMove_Front", 1.f, false);
	controller->AddAnimationClip("Lyn_P_Std_Mov_JumpToMove_Left", 1.f, false);
	controller->AddAnimationClip("Lyn_P_Std_Mov_JumpToMove_Right", 1.f, false);

	controller->AddAnimationClip("Lyn_P_BtoP_1", 1.f, false);
	controller->AddAnimationClip("Lyn_P_BtoP_2", 1.f, false);



	{
		BnS_MainCamera::Desc bnsCam;
		bnsCam.player = lyn;
		SphereCollider::Desc sphere;
		sphere.isTrigger = true;
		sphere.radius = 2.f;
		RigidBody::Desc rigid;
		rigid.isGravity = false;
		cam->AddComponent<Camera>()->AddComponent<BnS_MainCamera>(&bnsCam)->AddComponent<SphereCollider>(&sphere)->AddComponent<RigidBody>(&rigid);
	}

	//controller->AddAnimationClip("lyn_idle", 1.f, true);


	//controller->AddIntParameter("state", PLAYER_STATE::PLAYER_STATE_IDLE);

	//controller->AddAnimationTransition("lyn_battle_move_runFront", "lyn_battle_move_leftToRight", 0.15f, 0.1f, false, D3DXTRANSITION_TYPE::D3DXTRANSITION_LINEAR)
	//	->AddConditionInt("state", PLAYER_STATE_MOVE_RIGHT, ANIM_COMPARE_TYPE_EQUAL);
	//controller->AddAnimationTransition("lyn_battle_move_leftToRight", "lyn_battle_move_runFront", 0.15f, 0.1f, false, D3DXTRANSITION_TYPE::D3DXTRANSITION_LINEAR)
	//	->AddConditionInt("state", PLAYER_STATE_IDLE, ANIM_COMPARE_TYPE_EQUAL);
	//controller->AddAnimationTransition("lyn_battle_move_runFront", "lyn_battle_move_rightToLeft", 0.15f, 0.1f, false, D3DXTRANSITION_TYPE::D3DXTRANSITION_LINEAR)
	//	->AddConditionInt("state", PLAYER_STATE_MOVE_LEFT, ANIM_COMPARE_TYPE_EQUAL);
	//controller->AddAnimationTransition("lyn_battle_move_rightToLeft", "lyn_battle_move_runFront", 0.15f, 0.1f, false, D3DXTRANSITION_TYPE::D3DXTRANSITION_LINEAR)
	//	->AddConditionInt("state", PLAYER_STATE_IDLE, ANIM_COMPARE_TYPE_EQUAL);

	//controller->AddAnimationTransition("lyn_idle", "lyn_battle_move_runFront", 0.15f, 0.1f, false, D3DXTRANSITION_TYPE::D3DXTRANSITION_LINEAR)
	//	->AddConditionInt("state", PLAYER_STATE_battle_move_FRONT, ANIM_COMPARE_TYPE_EQUAL);
	//controller->AddAnimationTransition("lyn_battle_move_runFront", "lyn_idle", 0.15f, 0.1f, false, D3DXTRANSITION_TYPE::D3DXTRANSITION_LINEAR)
	//	->AddConditionInt("state", PLAYER_STATE_IDLE, ANIM_COMPARE_TYPE_EQUAL);

	//
	{
		MeshRenderer::Desc mesh;
		mesh.meshName = L"lyn_weapon";
		mesh.mtrlName = L"lyn_weapon";
		CapsuleCollider::Desc capsule;
		capsule.height = 1.6f;
		capsule.isTrigger = true;
		capsule.radius = 0.1f;
		capsule.rotOffset = { 0,0,77 };
		capsule.posOffset = { 0,1.5f,0 };
		RigidBody::Desc rigid;
		rigid.isKinematic = true;
		rigid.isGravity = false;
		auto weapon = INSTANTIATE(L"weapon")->AddComponent<MeshRenderer>(&mesh)->SetScale(0.5f,0.5f,0.5f)->AddComponent<DebugObject>()->AddComponent<CapsuleCollider>(&capsule)->AddComponent<RigidBody>(&rigid);
		weapon->SetParents(lyn, lyn->GetComponent<SkinnedMeshRenderer>()->GetBoneWorldMatrix("WeaponR"));
	}

}
