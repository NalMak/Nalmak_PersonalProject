#include "stdafx.h"
#include "StageScene.h"
#include "Homework_Player.h"

#include "BnS_MainCamera.h"

#include "LynStateControl.h"
#include "LynWait.h"
#include "LynVerticalCut_L0.h"
#include "LynVerticalCut_L1.h"
#include "LynVerticalCut_L2.h"
#include "LynVerticalCut_R0.h"
#include "LynVerticalCut_R1.h"
#include "LynVerticalCut_R2.h"
#include "LynIdle.h"
#include "LynBattleToPeace.h"
#include "LynBackStep.h"
#include "LynSkillTest.h"
#include "LynThunderSlash.h"

#include "LynLightningSlash.h"
#include "LynSpinSlash_Combo.h"
#include "LynSpinSlash_End.h"
#include "LynSpinSlash_Start.h"

#include "LynSlash1.h"
#include "LynSlash2.h"
#include "LynSlash3.h"
#include "LynBaldo.h"
#include "LynSkillController.h"

#include "StaticObjectInfo.h"

#include "LynMove.h"
#include "LynFall.h"
#include "LynJump.h"
#include "LynLand.h"

#include "LynSideDashE.h"
#include "LynSideDashQ.h"


#include "BnS_Enemy.h"
#include "UIManager.h"
#include "CameraShake.h"

StageScene::StageScene()
{
}


StageScene::~StageScene()
{
}


void StageScene::Initialize()
{


	UIManager::GetInstance()->CreateMainUI();

	auto staticObj = ResourceManager::GetInstance()->GetAllResource<StaticObjectInfo>();
	for (auto& obj : staticObj)
	{
		MAKE_STATIC(obj.first);
	}

	

	INSTANTIATE()->AddComponent<ParticleRenderer>()->SetPosition(0, 3, 0);

	{
		RigidBody::Desc rigid;
		BoxCollider::Desc box;
		box.isTrigger = true;
		INSTANTIATE(OBJECT_TAG_DEFAULT,OBJECT_LAYER_NAVIMESH)->AddComponent<BoxCollider>(&box)->AddComponent<MeshRenderer>()->SetPosition(5, 10, 0);
	}
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
		auto plane = INSTANTIATE(OBJECT_TAG_DEFAULT, OBJECT_LAYER_NAVIMESH)->AddComponent<MeshRenderer>(&mesh)->AddComponent<MeshCollider>()->SetScale(10, 10, 10)->SetPosition(0, 8.f, 0);
	}

	{
		auto boss = INSTANTIATE(OBJECT_TAG_ENEMY, OBJECT_LAYER_ENEMY)->SetScale(0.07f,0.07f,0.07f)->SetPosition(-5,7,0);
		MeshRenderer::Desc skin;
		skin.meshName = L"Lyn_Model2";
		boss->AddComponent<MeshRenderer>(&skin);

		CapsuleCollider::Desc capsule;
		capsule.posOffset= { 0,2.6f,0 };
		capsule.height = 3.2f;
		capsule.isTrigger = false;
		boss->AddComponent<CapsuleCollider>(&capsule);
		boss->AddComponent<RigidBody>();
		boss->AddComponent<BnS_Enemy>();
	}



	NavCollider::Desc navCollider;
	navCollider.navName = L"GW_navi";
	INSTANTIATE(OBJECT_TAG_DEFAULT, OBJECT_LAYER_NAVIMESH)->AddComponent<NavCollider>(&navCollider);

	

	
	auto lyn = INSTANTIATE(OBJECT_TAG_PLAYER, OBJECT_LAYER_PLAYER,L"Player")->SetPosition(0, 10, 0);
	auto cam = INSTANTIATE(OBJECT_TAG_DEFAULT,OBJECT_LAYER_CAMERA);

	lyn->AddComponent<LynSkillController>();

	SkinnedMeshRenderer::Desc skin;
	skin.meshName = L"Lyn_Model2";
	skin.mtrlName = L"lyn_hair";
	lyn->AddComponent<SkinnedMeshRenderer>(&skin);
	lyn->AddComponent<LynInfo>();
	AnimationController::Desc anim;
	anim.meshName = L"Lyn_Model2";
	Matrix rotMat;
	anim.rootMatrix = *D3DXMatrixRotationY(&rotMat, -90 * Deg2Rad);
	lyn->AddComponent<AnimationController>(&anim)->SetScale(0.06f, 0.06f, 0.06f);

	lyn->AddComponent<LynStateControl>();
	lyn->AddComponent<LynStateControl>();

	LynStateControl* lowerControl = lyn->GetComponents<LynStateControl>()[0];
	LynStateControl* upperControl = lyn->GetComponents<LynStateControl>()[1];

	//lyn->AddComponent<LynStateControl>();

	lowerControl->AddState<LynMove>(L"move",false);
	upperControl->AddState<LynMove>(L"move",true);
	lowerControl->AddState<LynFall>(L"fall", false);
	upperControl->AddState<LynFall>(L"fall", true);
	lowerControl->AddState<LynLand>(L"land", false);
	upperControl->AddState<LynLand>(L"land", true);
	lowerControl->AddState<LynJump>(L"jump", false);
	upperControl->AddState<LynJump>(L"jump", true);
	lowerControl->AddState<LynIdle>(L"idle", false);
	upperControl->AddState<LynIdle>(L"idle", true);


	upperControl->InitState(L"idle");
	lowerControl->InitState(L"idle");

	lowerControl->AddState<LynBattleToPeace>(L"battleToPeace", false);
	upperControl->AddState<LynBattleToPeace>(L"battleToPeace", true);

	lowerControl->AddState<LynVerticalCut_L0>(L"verticalCut_l0", false);
	upperControl->AddState<LynVerticalCut_L0>(L"verticalCut_l0", true);
	lowerControl->AddState<LynVerticalCut_L1>(L"verticalCut_l1", false);
	upperControl->AddState<LynVerticalCut_L1>(L"verticalCut_l1", true);
	lowerControl->AddState<LynVerticalCut_L2>(L"verticalCut_l2", false);
	upperControl->AddState<LynVerticalCut_L2>(L"verticalCut_l2", true);
	lowerControl->AddState<LynVerticalCut_R0>(L"verticalCut_r0", false);
	upperControl->AddState<LynVerticalCut_R0>(L"verticalCut_r0", true);
	lowerControl->AddState<LynVerticalCut_R1>(L"verticalCut_r1", false);
	upperControl->AddState<LynVerticalCut_R1>(L"verticalCut_r1", true);
	lowerControl->AddState<LynVerticalCut_R2>(L"verticalCut_r2", false);
	upperControl->AddState<LynVerticalCut_R2>(L"verticalCut_r2", true);

	upperControl->AddState<LynBackStep>(L"backStep", true);
	lowerControl->AddState<LynBackStep>(L"backStep", false);

	upperControl->AddState<LynSideDashQ>(L"sideDashQ", true);
	lowerControl->AddState<LynSideDashQ>(L"sideDashQ", false);
	upperControl->AddState<LynSideDashE>(L"sideDashE", true);
	lowerControl->AddState<LynSideDashE>(L"sideDashE", false);

	upperControl->AddState<LynSlash1>(L"slash1", true);
	lowerControl->AddState<LynSlash1>(L"slash1", false);
	upperControl->AddState<LynSlash2>(L"slash2", true);
	lowerControl->AddState<LynSlash2>(L"slash2", false);
	upperControl->AddState<LynSlash3>(L"slash3", true);
	lowerControl->AddState<LynSlash3>(L"slash3", false);


	upperControl->AddState<LynSpinSlash_Start>(L"spinSlash_start", true);
	lowerControl->AddState<LynSpinSlash_Start>(L"spinSlash_start", false);
	upperControl->AddState<LynSpinSlash_End>(L"spinSlash_end", true);
	lowerControl->AddState<LynSpinSlash_End>(L"spinSlash_end", false);
	upperControl->AddState<LynSpinSlash_Combo>(L"spinSlash_combo", true);
	lowerControl->AddState<LynSpinSlash_Combo>(L"spinSlash_combo", false);

	upperControl->AddState<LynBaldo>(L"baldo", true);
	lowerControl->AddState<LynBaldo>(L"baldo", false);

	upperControl->AddState<LynThunderSlash>(L"thunderSlash", true);
	lowerControl->AddState<LynThunderSlash>(L"thunderSlash", false);

	upperControl->AddState<LynLightningSlash>(L"lightningSlash", true);
	lowerControl->AddState<LynLightningSlash>(L"lightningSlash", false);



	upperControl->AddState<LynSkillTest>(L"test", true);
	lowerControl->AddState<LynSkillTest>(L"test", false);

	lyn->GetComponent<SkinnedMeshRenderer>()->SetFrustumCullingState(FRUSTUM_CULLING_STATE_FREE_PASS);
	lyn->GetComponent<SkinnedMeshRenderer>()->SetMaterial(L"lyn_body", 0);
	lyn->GetComponent<SkinnedMeshRenderer>()->AddMaterial(L"lyn_face");
	lyn->GetComponent<SkinnedMeshRenderer>()->AddMaterial(L"lyn_hair2");

	CharacterController::Desc character;
	character.center = { 0,2.f,0 };
	character.height = 1.6f;
	lyn->AddComponent<CharacterController>(&character);

	AnimationController* controller = lyn->GetComponent<AnimationController>();

	controller->AddAnimationClip("Lyn_P_Std_Mov_Idle", 1.f, true);
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
	controller->AddAnimationClip("Lyn_P_Std_Mov_RunBack", 1.3f, true);
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


	controller->AddAnimationClip("Lyn_B_Std_Mov_IdleToJump_Front", 1.f, false);
	controller->AddAnimationClip("Lyn_B_Std_Mov_IdleToJump_Left", 1.f, false);
	controller->AddAnimationClip("Lyn_B_Std_Mov_IdleToJump_Right", 1.f, false);
	controller->AddAnimationClip("Lyn_B_Std_Mov_JumpFront", 1.f, true);
	controller->AddAnimationClip("Lyn_B_Std_Mov_JumpLeft", 1.f, true);
	controller->AddAnimationClip("Lyn_B_Std_Mov_JumpRight", 1.f, true);
	controller->AddAnimationClip("Lyn_B_Std_Mov_JumpToIdle", 1.f, true);
	controller->AddAnimationClip("Lyn_B_Std_Mov_JumpToMove_Back", 1.f, false);
	controller->AddAnimationClip("Lyn_B_Std_Mov_JumpToMove_Front", 1.f, false);
	controller->AddAnimationClip("Lyn_B_Std_Mov_JumpToMove_Left", 1.f, false);
	controller->AddAnimationClip("Lyn_B_Std_Mov_JumpToMove_Right", 1.f, false);
	controller->AddAnimationClip("Lyn_B_Std_Mov_LeftToRight", 1.f, false);
	controller->AddAnimationClip("Lyn_B_Std_Mov_MoveToIdle", 1.f, false);
	controller->AddAnimationClip("Lyn_B_Std_Mov_RightToLeft", 1.f, false);

	controller->AddAnimationClip("Lyn_B_Std_Mov_RunRightBack", 1.3f, true);
	controller->AddAnimationClip("Lyn_B_Std_Mov_RunBack", 1.3f, true);
	controller->AddAnimationClip("Lyn_B_Std_Mov_RunLeftBack", 1.3f, true);

	controller->AddAnimationClip("Lyn_B_Std_Mov_RunLeft", 1.3f, true);
	controller->AddAnimationClip("Lyn_B_Std_Mov_RunFront", 1.3f, true);
	controller->AddAnimationClip("Lyn_B_Std_Mov_RunRight", 1.3f, true);
	controller->AddAnimationClip("Lyn_B_Std_Mov_RunRightFront", 1.3f, true);
	controller->AddAnimationClip("Lyn_B_Std_Mov_RunLeftFront", 1.3f, true);

	controller->AddAnimationClip("Lyn_B_Std_Mov_Idle", 1.f, true);

	///////////////////////////////////////////////////////////////////////
	controller->AddAnimationClip("Lyn_B_Hide_Mov_IdleToJump_Front", 1.f, false);
	controller->AddAnimationClip("Lyn_B_Hide_Mov_IdleToJump_Left", 1.f, false);
	controller->AddAnimationClip("Lyn_B_Hide_Mov_IdleToJump_Right", 1.f, false);
	controller->AddAnimationClip("Lyn_B_Hide_Mov_JumpFront", 1.f, true);
	controller->AddAnimationClip("Lyn_B_Hide_Mov_JumpLeft", 1.f, true);
	controller->AddAnimationClip("Lyn_B_Hide_Mov_JumpRight", 1.f, true);
	controller->AddAnimationClip("Lyn_B_Hide_Mov_JumpToIdle", 1.f, true);
	controller->AddAnimationClip("Lyn_B_Hide_Mov_JumpToMove_Back", 1.f, false);
	controller->AddAnimationClip("Lyn_B_Hide_Mov_JumpToMove_Front", 1.f, false);
	controller->AddAnimationClip("Lyn_B_Hide_Mov_JumpToMove_Left", 1.f, false);
	controller->AddAnimationClip("Lyn_B_Hide_Mov_JumpToMove_Right", 1.f, false);
	controller->AddAnimationClip("Lyn_B_Hide_Mov_LeftToRight", 1.f, false);
	controller->AddAnimationClip("Lyn_B_Hide_Mov_MoveToIdle", 1.f, false);
	controller->AddAnimationClip("Lyn_B_Hide_Mov_RightToLeft", 1.f, false);

	controller->AddAnimationClip("Lyn_B_Hide_Mov_RunRightBack", 1.3f, true);
	controller->AddAnimationClip("Lyn_B_Hide_Mov_RunBack", 1.3f, true);
	controller->AddAnimationClip("Lyn_B_Hide_Mov_RunLeftBack", 1.3f, true);

	controller->AddAnimationClip("Lyn_B_Hide_Mov_RunLeft", 1.3f, true);
	controller->AddAnimationClip("Lyn_B_Hide_Mov_RunFront", 1.3f, true);
	controller->AddAnimationClip("Lyn_B_Hide_Mov_RunRight", 1.3f, true);
	controller->AddAnimationClip("Lyn_B_Hide_Mov_RunRightFront", 1.3f, true);
	controller->AddAnimationClip("Lyn_B_Hide_Mov_RunLeftFront", 1.3f, true);

	controller->AddAnimationClip("Lyn_B_Hide_Mov_Idle", 1.f, true);
	//controller->AddAnimationClip("Lyn_B_Hide_Mov_Idle", 1.f, true);
	///////////////////////////////////////////////////////////////////////

	controller->AddAnimationClip("Lyb_B_Std_VerticalCul_01_1", 1.1f, false);
	controller->AddAnimationClip("Lyb_B_Std_VerticalCul_01_2", 1.1f, false);
	controller->AddAnimationClip("Lyb_B_Std_VerticalCul_01_3", 2.f, false);
	controller->AddAnimationClip("Lyb_B_Std_VerticalCul_02_1", 1.1f, false);
	controller->AddAnimationClip("Lyb_B_Std_VerticalCul_02_2", 1.1f, false);
	controller->AddAnimationClip("Lyb_B_Std_VerticalCul_02_3", 2.f, false);

	controller->AddAnimationClip("Lyn_B_Hide_SwordFlash_End", 3.f, false);
	controller->AddAnimationClip("Lyn_B_Hide_SwordFlash_Exec", 0.8f, false);
	controller->AddAnimationClip("Lyn_B_Hide_SwordFlash_Swing", 0.8f, false);


	controller->AddAnimationClip("Lyn_B_Std_BackStep", 1.4f, false);

	controller->AddAnimationClip("Lyn_B_Std_SideMov_E", 1.f, false);
	controller->AddAnimationClip("Lyn_B_Std_SideMov_Q", 1.f, false);



	controller->AddAnimationClip("Lyn_B_Hide_Baldo0", 1.5f, false);
	controller->AddAnimationClip("Lyn_B_Hide_Baldo1", 1.5f, false);


	controller->AddAnimationClip("Lyn_B_defaultSlash1", 2.f, false);
	controller->AddAnimationClip("Lyn_B_defaultSlash2", 2.f, false);
	controller->AddAnimationClip("Lyn_B_defaultSlash3", 1.7f, false);

	controller->AddAnimationClip("Lyn_B_Std_SpinSlash_01", 2.f, false);
	controller->AddAnimationClip("Lyn_B_Std_SpinSlash_01_1", 1.5f, false);
	controller->AddAnimationClip("Lyn_B_Std_SpinSlash_02", 1.6f, false);

	controller->AddAnimationClip("Lyn_B_Std_ThunderCut", 1.f, false);



	/*controller->AddAnimationClip("Lyn_B_Hide_BattoCombo1_Dash_Exec.X", 1.f, false);
	controller->AddAnimationClip("Lyn_B_Hide_BattoCombo1_Dash_Swing.X", 1.f, false);

	controller->AddAnimationClip("Lyn_B_Hide_BattoCombo2_Exec.X", 1.f, false);
	controller->AddAnimationClip("Lyn_B_Hide_BattoCombo2_Swing.X", 1.f, false);*/

	controller->SeparateBone("Bip01Spine");
	controller->SetFixedAnimationBoneName("Bip01", true, false, true);
	AnimationController::Desc anim2;
	anim2.cloneAnimationController = controller;
	lyn->AddComponent<AnimationController>(&anim2);
	lyn->GetComponents<AnimationController>()[1]->SetFixedAnimationBoneName("Bip01", true, false, true);

	{
		BnS_MainCamera::Desc bnsCam;
		bnsCam.player = lyn;
		SphereCollider::Desc sphere;
		sphere.isTrigger = true;
		sphere.radius = 2.f;
		RigidBody::Desc rigid;
		rigid.isGravity = false;
		cam->AddComponent<BnS_MainCamera>(&bnsCam)->AddComponent<SphereCollider>(&sphere)->AddComponent<RigidBody>(&rigid)->AddComponent<Camera>()->AddComponent<CameraShake>();
		//INSTANTIATE()->AddComponent<Camera>()->AddComponent<CameraShake>()->SetParents(cam);
			
	}


	{
		MeshRenderer::Desc mesh;
		mesh.meshName = L"lyn_weapon";
		mesh.mtrlName = L"lyn_weapon";
		CapsuleCollider::Desc capsule;
		capsule.height = 3.6f;
		capsule.isTrigger = true;
		capsule.radius = 0.1f;
		capsule.rotOffset = { 0,0,77 };
		capsule.posOffset = { 0,1.5f,0 };
		RigidBody::Desc rigid;
		rigid.isKinematic = true;
		rigid.isGravity = false;
		auto weapon = INSTANTIATE(L"weapon")->AddComponent<MeshRenderer>(&mesh)->SetScale(0.5f, 0.65f, 0.5f)->AddComponent<DebugObject>();
		lyn->GetComponent<LynInfo>()->EquipeWeapon(weapon);
	}
}
