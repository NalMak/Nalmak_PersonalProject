#include "stdafx.h"
#include "TitleScene.h"
#include "Homework_Player.h"

#include "LynStateControl.h"
#include "LynIdle.h"
#include "LynRun.h"
#include "LynTurning.h"
#include "LynIdleToJump.h"
#include "LynJump.h"
#include "LynJumpToIdle.h"
#include "LynJumpToMove.h"
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


	auto cam = INSTANTIATE()->AddComponent<Camera>();
	
	INSTANTIATE()->AddComponent<DebuggingMode>();

	//MAKE_STATIC(L"musin_boss_floor");
	{
		MeshRenderer::Desc mesh;
		mesh.meshName = L"plane";
		RigidBody::Desc rigid;
		rigid.isKinematic = true;
		rigid.isGravity = false;
		auto plane = INSTANTIATE()->AddComponent<MeshRenderer>(&mesh)->AddComponent<MeshCollider>()->SetScale(10, 10, 10)->SetPosition(0, -10, 0);
		plane->SetLayer(OBJECT_LAYER_BACKGROUND);
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
	
	


	auto lyn = INSTANTIATE()->SetRotation(0,-90,0);
	cam->SetParents(lyn);
	cam->SetPosition(0, 6, -10);
	cam->SetRotation(30, 0, 0);

	SkinnedMeshRenderer::Desc skin;
	skin.meshName = L"Lyn_Model2";
	skin.mtrlName = L"lyn_hair";
	lyn->AddComponent<SkinnedMeshRenderer>(&skin);

	lyn->AddComponent<LynInfo>();
	lyn->AddComponent<DebugObject>();
	AnimationController::Desc anim;
	anim.meshName = L"Lyn_Model2";
	lyn->AddComponent<AnimationController>(&anim)->SetScale(0.1f,0.1f,0.1f);

	lyn->AddComponent<LynStateControl>();
	lyn->GetComponent<LynStateControl>()->AddState<LynIdle>(L"idle");
	lyn->GetComponent<LynStateControl>()->AddState<LynRun>(L"run");
	lyn->GetComponent<LynStateControl>()->AddState<LynTurning>(L"turning");
	lyn->GetComponent<LynStateControl>()->AddState<LynIdleToJump>(L"idleToJump");
	lyn->GetComponent<LynStateControl>()->AddState<LynJump>(L"jump");
	lyn->GetComponent<LynStateControl>()->AddState<LynJumpToIdle>(L"jumpToIdle");
	lyn->GetComponent<LynStateControl>()->AddState<LynJumpToMove>(L"jumpToMove");


	lyn->GetComponent<LynStateControl>()->InitState(L"idle");

	lyn->GetComponent<SkinnedMeshRenderer>()->SetFrustumCulling(false);
	lyn->GetComponent<SkinnedMeshRenderer>()->ReserveMaterial(3);
	lyn->GetComponent<SkinnedMeshRenderer>()->SetMaterial(L"lyn_body",0);
	lyn->GetComponent<SkinnedMeshRenderer>()->SetMaterial(L"lyn_face",1);
	lyn->GetComponent<SkinnedMeshRenderer>()->SetMaterial(L"lyn_hair2",2);

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


	controller->AddAnimationClip("Lyn_P_Std_Mov_RunRightBack", 1.f, true);
	controller->AddAnimationClip("Lyn_P_Std_Mov_RunRight", 1.f, true);
	controller->AddAnimationClip("Lyn_P_Std_Mov_RunLeftBack", 1.f, true);
	controller->AddAnimationClip("Lyn_P_Std_Mov_RunFront", 1.f, true);
	controller->AddAnimationClip("Lyn_P_Std_Mov_RunBack", 1.f, true);
	controller->AddAnimationClip("Lyn_P_Std_Mov_RunLeft", 1.f, true);

	controller->AddAnimationClip("Lyn_P_Std_Mov_IdleToJump_Front", 1.f, false);
	controller->AddAnimationClip("Lyn_P_Std_Mov_IdleToJump_Left", 1.f, false);
	controller->AddAnimationClip("Lyn_P_Std_Mov_IdleToJump_Right", 1.f, false);

	controller->AddAnimationClip("Lyn_P_Std_Mov_JumpFront", 1.f, false);
	controller->AddAnimationClip("Lyn_P_Std_Mov_JumpLeft", 1.f, false);
	controller->AddAnimationClip("Lyn_P_Std_Mov_JumpRight", 1.f, false);
	controller->AddAnimationClip("Lyn_P_Std_Mov_JumpToIdle", 1.f, false);

	controller->AddAnimationClip("Lyn_P_Std_Mov_JumpToMove_Back", 1.f, false);
	controller->AddAnimationClip("Lyn_P_Std_Mov_JumpToMove_Front", 1.f, false);
	controller->AddAnimationClip("Lyn_P_Std_Mov_JumpToMove_Left", 1.f, false);
	controller->AddAnimationClip("Lyn_P_Std_Mov_JumpToMove_Right", 1.f, false);


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
	controller->SetEntryClip("Lyn_P_Std_Idle_Event1");


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


	NavCollider::Desc navCollider;
	navCollider.navName = L"default";
	INSTANTIATE()->AddComponent<NavCollider>(&navCollider);
}
