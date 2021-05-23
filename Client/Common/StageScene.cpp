
#include "stdafx.h"
#include "StageScene.h"
#include "Homework_Player.h"

#include "BnS_MainCamera.h"

#include "LynStateControl.h"
#include "LynVerticalCut_L0.h"
#include "LynVerticalCut_L1.h"
#include "LynVerticalCut_L2.h"
#include "LynVerticalCut_R0.h"
#include "LynVerticalCut_R1.h"
#include "LynVerticalCut_R2.h"
#include "LynIdle.h"
#include "LynBattleToPeace.h"
#include "LynBackStep.h"
#include "LynThunderSlash.h"
#include "LynWakeUp.h"

#include "LynLightningSlash.h"
#include "LynSpinSlash_End.h"
#include "LynSpinSlash_Start.h"

#include "LynSlash1.h"
#include "LynSlash2.h"
#include "LynSlash3.h"
#include "LynBaldo.h"
#include "LynSkillController.h"
#include "LynChamWall.h"
#include "LynFrontKick.h"
#include "LynHold.h"
#include "LynFrontDash.h"
#include "LynLowerSlash.h"
#include "LynLowerSlash2.h"
#include "LynDown.h"

#include "StaticObjectInfo.h"

#include "LynMove.h"
#include "LynFall.h"
#include "LynJump.h"
#include "LynLand.h"
#include "LynRebound.h"

#include "LynSideDashE.h"
#include "LynSideDashQ.h"

#include "LynWindyMoonSlash.h"
#include "LynUpperSlash.h"
#include "LynThrowSoulBlade.h"
#include "LynRotateSoulBlade.h"
#include "LynLightningCombo.h"
#include "LynLayDown.h"
#include "LynKnockBackLong.h"
#include "LynKnockBackMiddle.h"
#include "LynIlSum.h"
#include "LynHolded.h"
#include "LynGrogy.h"
#include "LynExcape.h"
#include "LynDown.h"
#include "LynDead.h"
#include "LynBackRoll.h"

#include "ZakanPeaceIdle.h"
#include "ZakanBattleIdle.h"
#include "ZakanSpawn.h"
#include "ZakanNATK1.h"
#include "ZakanNATK2.h"
#include "ZakanMove.h"
#include "ZakanPattern.h"


#include "BnS_Enemy.h"
#include "UIManager.h"
#include "CameraShake.h"
#include "ZakanSmash.h"
#include "ZakanDown.h"
#include "ZakanAir.h"
#include "ZakanRise.h"
#include "LynWeapon.h"
#include "ZakanTeleport.h"
#include "ZakanArea360.h"
#include "LynEventIdle.h"
#include "BnS_SystemSetting.h"
#include "ZakanPowerATK.h"
#include "ZakanSpellExplosion.h"
#include "ZakanDamageShield.h"
#include "ZakanSplitBlood.h"
#include "ZakanTeleportCenter.h"
#include "ZakanDead.h"
#include "LynEffectControl.h"
#include "BnS_Fire.h"
#include "ZakanEffectControl.h"
#include "ZakanChange.h"
#include "ZakanBackStep.h"
#include "ZakanFireSpellWave.h"
#include "ZakanSpellSuction.h"
#include "MeshEffect_Slash.h"
#include "LynStateThunderbolt.h"
#include "LynSprint.h"
#include "LynFly.h"
#include "ZakanStun.h"
#include "LynStarAttack.h"
#include "LynCrash.h"
StageScene::StageScene()
{
}


StageScene::~StageScene()
{
}


void StageScene::Initialize()
{
	//{
	//	MeshRenderer::Desc mesh;
	//	mesh.mtrlName = L"zakan_floorAttack";
	//	mesh.meshName = L"em_trail_test2";
	//	INSTANTIATE()->AddComponent<MeshRenderer>(&mesh)->AddComponent<MeshEffect_Slash>()->SetScale(0.1f, 0.1f, 0.1f)->SetPosition(30, 30, 30);
	//}
	//{
	//	MeshRenderer::Desc mesh;
	//	mesh.mtrlName = L"zakan_floorAttack2";
	//	mesh.meshName = L"Lyn_em_slash";
	//	INSTANTIATE()->AddComponent<MeshRenderer>(&mesh)->AddComponent<MeshEffect_Slash>()->SetScale(0.1f, 0.1f, 0.1f)->SetPosition(30, 10, 30);
	//}
#pragma region Debug
	DebuggingMode::Desc debug;
	debug.createDirectoryMonitor = true;
	INSTANTIATE()->AddComponent<DebuggingMode>(&debug);
#pragma endregion Debug


	UIManager::GetInstance()->CreateMainUI();
	auto staticObj = ResourceManager::GetInstance()->GetAllResource<StaticObjectInfo>();
	for (auto& obj : staticObj)
		MAKE_STATIC(obj.first);

	auto zakan = INSTANTIATE(OBJECT_TAG_ENEMY, OBJECT_LAYER_ENEMY)->SetScale(0.05f, 0.05f, 0.05f)->SetPosition(-5, 10, -5)->SetRotation(0,90,0);
	auto lyn = INSTANTIATE(OBJECT_TAG_PLAYER, OBJECT_LAYER_PLAYER, L"Player")->SetPosition(-130, 46, -7)->SetScale(0.5f,0.5f,0.5f);
	auto cam = INSTANTIATE(OBJECT_TAG_DEFAULT, OBJECT_LAYER_CAMERA);
	
	INSTANTIATE()->AddComponent<BnS_SystemSetting>();

	INSTANTIATE()->AddComponent<MeshRenderer>()->AddComponent<BoxCollider>()->SetPosition(-10,10,0);

	INSTANTIATE()->AddComponent<BnS_Fire>();
	

#pragma region Navi Mesh
	NavCollider::Desc navCollider;
	navCollider.navName = L"stage1";
	INSTANTIATE(OBJECT_TAG_DEFAULT, OBJECT_LAYER_NAVIMESH)->AddComponent<NavCollider>(&navCollider);

	navCollider.navName = L"stage1_floor2";
	INSTANTIATE(OBJECT_TAG_DEFAULT, OBJECT_LAYER_NAVIMESH)->AddComponent<NavCollider>(&navCollider);
#pragma endregion Navi Mesh
#pragma region Lyn
	lyn->AddComponent<LynSkillController>();
	SkinnedMeshRenderer::Desc skin;
	skin.meshName = L"Lyn_Model2";
	skin.mtrlName = L"lyn_hair";
	lyn->AddComponent<SkinnedMeshRenderer>(&skin);
	lyn->GetComponent<SkinnedMeshRenderer>()->SetFrustumCullingState(FRUSTUM_CULLING_STATE_FREE_PASS);
	lyn->GetComponent<SkinnedMeshRenderer>()->SetMaterial(L"lyn_body", 0);
	lyn->GetComponent<SkinnedMeshRenderer>()->AddMaterial(L"lyn_face");
	lyn->GetComponent<SkinnedMeshRenderer>()->AddMaterial(L"lyn_hair2");

	lyn->AddComponent<LynInfo>();
	UIManager::GetInstance()->SetLynInfo(lyn->GetComponent<LynInfo>());
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

	lowerControl->AddState<LynMove>(L"move", false);
	upperControl->AddState<LynMove>(L"move", true);
	lowerControl->AddState<LynFall>(L"fall", false);
	upperControl->AddState<LynFall>(L"fall", true);
	lowerControl->AddState<LynLand>(L"land", false);
	upperControl->AddState<LynLand>(L"land", true);
	lowerControl->AddState<LynJump>(L"jump", false);
	upperControl->AddState<LynJump>(L"jump", true);
	lowerControl->AddState<LynIdle>(L"idle", false);
	upperControl->AddState<LynIdle>(L"idle", true);
	lowerControl->AddState<LynEventIdle>(L"eventIdle", false);
	upperControl->AddState<LynEventIdle>(L"eventIdle", true);
	lowerControl->AddState<LynRebound>(L"rebound", false);
	upperControl->AddState<LynRebound>(L"rebound", true);



	lowerControl->AddState<LynWindyMoonSlash>(L"windyWallSlash", false);
	upperControl->AddState<LynWindyMoonSlash>(L"windyWallSlash", true);
	lowerControl->AddState<LynUpperSlash>(L"upperSlash", false);
	upperControl->AddState<LynUpperSlash>(L"upperSlash", true);
	lowerControl->AddState<LynThrowSoulBlade>(L"throwSoulBlade", false);
	upperControl->AddState<LynThrowSoulBlade>(L"throwSoulBlade", true);
	lowerControl->AddState<LynRotateSoulBlade>(L"rotateSoulBlade", false);
	upperControl->AddState<LynRotateSoulBlade>(L"rotateSoulBlade", true);
	lowerControl->AddState<LynLightningCombo>(L"lightningCombo", false);
	upperControl->AddState<LynLightningCombo>(L"lightningCombo", true);
	lowerControl->AddState<LynLayDown>(L"layDown", false);
	upperControl->AddState<LynLayDown>(L"layDown", true);
	lowerControl->AddState<LynKnockBackLong>(L"knockBackLong", false);
	upperControl->AddState<LynKnockBackLong>(L"knockBackLong", true);
	lowerControl->AddState<LynKnockBackMiddle>(L"knockBackMiddle", false);
	upperControl->AddState<LynKnockBackMiddle>(L"knockBackMiddle", true);
	lowerControl->AddState<LynIlSum>(L"ilsum", false);
	upperControl->AddState<LynIlSum>(L"ilsum", true);
	lowerControl->AddState<LynHolded>(L"holded", false);
	upperControl->AddState<LynHolded>(L"holded", true);
	lowerControl->AddState<LynGrogy>(L"grogy", false);
	upperControl->AddState<LynGrogy>(L"grogy", true);
	lowerControl->AddState<LynExcape>(L"excape", false);
	upperControl->AddState<LynExcape>(L"excape", true);
	lowerControl->AddState<LynDown>(L"down", false);
	upperControl->AddState<LynDown>(L"down", true);
	lowerControl->AddState<LynDead>(L"dead", false);
	upperControl->AddState<LynDead>(L"dead", true);
	lowerControl->AddState<LynBackRoll>(L"backRoll", false);
	upperControl->AddState<LynBackRoll>(L"backRoll", true);
	lowerControl->AddState<LynStateThunderbolt>(L"thunderbolt", false);
	upperControl->AddState<LynStateThunderbolt>(L"thunderbolt", true);

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

	lowerControl->AddState<LynStarAttack>(L"starAttack", false);
	upperControl->AddState<LynStarAttack>(L"starAttack", true);

	upperControl->AddState<LynBackStep>(L"backStep", true);
	lowerControl->AddState<LynBackStep>(L"backStep", false);

	upperControl->AddState<LynWakeUp>(L"wakeUp", true);
	lowerControl->AddState<LynWakeUp>(L"wakeUp", false);

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


	upperControl->AddState<LynBaldo>(L"baldo", true);
	lowerControl->AddState<LynBaldo>(L"baldo", false);

	upperControl->AddState<LynThunderSlash>(L"thunderSlash", true);
	lowerControl->AddState<LynThunderSlash>(L"thunderSlash", false);

	upperControl->AddState<LynLightningSlash>(L"lightningSlash", true);
	lowerControl->AddState<LynLightningSlash>(L"lightningSlash", false);

	upperControl->AddState<LynChamWall>(L"chamWall", true);
	lowerControl->AddState<LynChamWall>(L"chamWall", false);

	upperControl->AddState<LynFrontKick>(L"frontKick", true);
	lowerControl->AddState<LynFrontKick>(L"frontKick", false);

	upperControl->AddState<LynFrontDash>(L"frontDash", true);
	lowerControl->AddState<LynFrontDash>(L"frontDash", false);

	upperControl->AddState<LynLowerSlash>(L"lowerSlash", true);
	lowerControl->AddState<LynLowerSlash>(L"lowerSlash", false);

	upperControl->AddState<LynLowerSlash2>(L"lowerSlash2", true);
	lowerControl->AddState<LynLowerSlash2>(L"lowerSlash2", false);

	upperControl->AddState<LynHold>(L"hold", true);
	lowerControl->AddState<LynHold>(L"hold", false);

	upperControl->AddState<LynFly>(L"fly", true);
	lowerControl->AddState<LynFly>(L"fly", false);

	upperControl->AddState<LynCrash>(L"crash", true);
	lowerControl->AddState<LynCrash>(L"crash", false);

	CharacterController::Desc character;
	character.center = { 0,2.f,0 };
	character.height = 1.6f;
	character.stepOffset = 0.3f;
	lyn->AddComponent<CharacterController>(&character);

	AnimationController* controller = lyn->GetComponent<AnimationController>();
	controller->SetRootMotion(true);

	controller->AddAnimationClip("Lyn_P_Std_Mov_Idle", 1.f, true);
	controller->AddAnimationClip("Lyn_P_Std_Idle_Event1", 1.f, false);
	controller->AddAnimationClip("Lyn_P_Std_Idle_Event2", 1.f, false);
	controller->AddAnimationClip("Lyn_P_Std_Idle_Event3", 1.f, false);
	controller->AddAnimationClip("Lyn_P_Std_Idle_Event4", 1.f, false);
	controller->AddAnimationClip("Lyn_P_Std_Idle_Event5", 1.f, false);
	controller->AddAnimationClip("Lyn_P_Std_Idle_Event6", 1.f, false);


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
	controller->AddAnimationClip("Lyb_B_Std_VerticalCul_01_3", 2.25f, false);
	controller->AddAnimationClip("Lyb_B_Std_VerticalCul_02_1", 1.1f, false);
	controller->AddAnimationClip("Lyb_B_Std_VerticalCul_02_2", 1.1f, false);
	controller->AddAnimationClip("Lyb_B_Std_VerticalCul_02_3", 2.25f, false);

	controller->AddAnimationClip("Lyn_B_Hide_SwordFlash_End", 3.f, false);
	controller->AddAnimationClip("Lyn_B_Hide_SwordFlash_Exec", 0.8f, false);
	controller->AddAnimationClip("Lyn_B_Hide_SwordFlash_Swing", 0.5f, false);


	controller->AddAnimationClip("Lyn_B_Std_BackStep", 1.3f, false);
	controller->AddAnimationClip("Lyn_B_Hide_BackStep", 0.95f, false);


	controller->AddAnimationClip("Lyn_B_Std_SideMov_E", 1.f, false);
	controller->AddAnimationClip("Lyn_B_Std_SideMov_Q", 1.f, false);

	controller->AddAnimationClip("Lyn_B_Hide_Baldo0", 1.4f, false);
	controller->AddAnimationClip("Lyn_B_Hide_Baldo1", 1.4f, false);


	controller->AddAnimationClip("Lyn_B_defaultSlash1", 1.4f, false);
	controller->AddAnimationClip("Lyn_B_defaultSlash2", 1.4f, false);
	controller->AddAnimationClip("Lyn_B_defaultSlash3", 1.4f, false);

	controller->AddAnimationClip("Lyn_B_Std_SpinSlash_01", 1.f, false);
	controller->AddAnimationClip("Lyn_B_Std_SpinSlash_02", 1.f, false);

	controller->AddAnimationClip("Lyn_B_Std_ThunderCut", 1.f, false);

	controller->AddAnimationClip("Lyn_B_Chamwall", 1.f, false);

	controller->AddAnimationClip("Lyn_B_CripplingCut_Exec", 1.f, false);
	controller->AddAnimationClip("Lyn_B_CripplingCut_Fire", 1.f, false);


	controller->AddAnimationClip("Lyn_B_FrontKick", 1.2f, false);

	controller->AddAnimationClip("Lyn_B_lowerSlash1", 1.3f, false);
	controller->AddAnimationClip("Lyn_B_lowerSlash2", 1.3f, false);
	controller->AddAnimationClip("Lyn_B_Std_Dash_1", 1.f, false);
	controller->AddAnimationClip("Lyn_B_Std_Dash_2", 1.f, false);
	

	controller->AddAnimationClip("Lyn_B_Hide_RotateSoulBlade", 1.f, false);
	controller->AddAnimationClip("Lyn_B_Std_RotateSoulBlade", 1.f, false);


	controller->AddAnimationClip("Lyn_B_Stun_Start", 1.f, false);
	controller->AddAnimationClip("Lyn_B_Stun_Looping", 1.f, true);
	
	controller->AddAnimationClip("Lyn_B_KnockBack_Long_B", 1.f, false);
	controller->AddAnimationClip("Lyn_B_KnockBack_Long_F", 1.f, false);
	controller->AddAnimationClip("Lyn_B_KnockBack_Mid_B", 1.f, false);
	controller->AddAnimationClip("Lyn_B_KnockBack_Mid_F", 1.f, false);
	controller->AddAnimationClip("Lyn_B_Hide_LightningCombo", 1.1f, false);
	controller->AddAnimationClip("Lyn_B_Down", 1.f, false);// 두개 테스트 필요
	controller->AddAnimationClip("Lyn_B_layDown", 1.f, false);//
	controller->AddAnimationClip("Lyn_B_Down_B", 1.f, false);
	controller->AddAnimationClip("Lyn_B_wakeUp1", 1.f, false);
	controller->AddAnimationClip("Lyn_B_wakeUp2", 1.f, false);

	controller->AddAnimationClip("Lyn_B_Down_F", 1.f, false);
	controller->AddAnimationClip("Lyn_P_Std_Dash", 1.f, false);
	controller->AddAnimationClip("Lyn_B_Std_BackRoll", 1.f, false);
	controller->AddAnimationClip("Lyn_B_Throw1", 1.f, false);
	controller->AddAnimationClip("Lyn_B_Throw2", 1.f, false);
	controller->AddAnimationClip("Lyn_B_Dead", 1.f, false);
	controller->AddAnimationClip("Lyn_B_Exhausted_Mov_Idle", 1.f, false);
	controller->AddAnimationClip("Lyn_B_Holded_Looping", 1.f, false);
	controller->AddAnimationClip("Lyn_B_Holded_Start", 1.f, false);
	controller->AddAnimationClip("Lyn_B_Holded_ToGrogy", 1.f, false);
	controller->AddAnimationClip("Lyn_B_upperSlash2", 1.5f, false);
	controller->AddAnimationClip("Lyn_B_Hide_Ilsum", 2.f, false); // 테스트 필요
	controller->AddAnimationClip("Lyn_B_Hide_Ilsum_End", 1.f, false);
	controller->AddAnimationClip("Lyn_B_Hide_Ilsum_Fire", 1.f, false);
	controller->AddAnimationClip("Lyb_B_Std_Excape_1", 1.f, false);
	controller->AddAnimationClip("Lyb_B_Std_Excape_2", 1.f, false);
	controller->AddAnimationClip("Lyn_B_Hide_WindyMoonSlash1", 1.f, false);
	controller->AddAnimationClip("Lyn_B_Hide_WindyMoonSlash2", 1.f, false);
	controller->AddAnimationClip("Lyn_B_Hide_WindyMoonSlashEnd", 1.f, false);
	controller->AddAnimationClip("Lyn_B_Magnetic_Cast_Start", 1.f, false);
	controller->AddAnimationClip("Lyn_B_Magnetic_Cast_Looping", 1.f, false);

	controller->AddAnimationClip("Lyn_B_FlyByHit", 1.f, false);
	controller->AddAnimationClip("Lyn_B_KnockBack_Long_B", 1.f, false);
	controller->AddAnimationClip("Lyn_B_KnockBack_Long_F", 1.f, false);
	controller->AddAnimationClip("Lyn_B_KnockBack_Mid_B", 1.f, false);
	controller->AddAnimationClip("Lyn_B_KnockBack_Mid_F", 1.f, false);

	controller->AddAnimationClip("Lyn_B_Grogy_Start", 1.f, false);
	controller->AddAnimationClip("Lyn_B_Grogy_End", 1.f, false);

	controller->AddAnimationClip("Lyn_B_Crash", 1.f, false);


	controller->AddAnimationClip("Lyn_P_Std_Mov_Sprint_JumpFront", 1.5f, true);

	controller->AddAnimationClip("Lyn_P_Std_Mov_Glide_Front_Start", 1.f, false);
	controller->AddAnimationClip("Lyn_P_Std_Mov_Glide_Front_Boost_Looping", 1.f, true);
	controller->AddAnimationClip("Lyn_P_Std_Mov_Glide_Front_Boost", 1.f, false);

	controller->AddAnimationClip("Lyn_B_takeWing", 1.5f, false);


	controller->SeparateBone("Bip01Spine");
	controller->SetFixedAnimationBoneName("Bip01", true, false, true);
	AnimationController::Desc anim2;
	anim2.cloneAnimationController = controller;
	lyn->AddComponent<AnimationController>(&anim2);
	lyn->GetComponents<AnimationController>()[1]->SetFixedAnimationBoneName("Bip01", true, false, true);
	lyn->GetComponents<AnimationController>()[1]->SetRootMotion(true);
	lyn->AddComponent<AudioSource>();
	lyn->AddComponent<LynEffectControl>();

#pragma endregion Lyn
#pragma region Lyn Weapon
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
		TrailRenderer::Desc trail;
		trail.detailCount = 6;
		trail.maxTrailCount = 50;
		trail.mtrlName = L"Lyn_weapon_trail";
		trail.playOnStart = false;
		auto weapon = INSTANTIATE(L"weapon")->AddComponent<MeshRenderer>(&mesh)->AddComponent<LynWeapon>()->AddComponent<TrailRenderer>(&trail)->SetScale(0.5f, 0.65f, 0.5f);
		lyn->GetComponent<LynInfo>()->EquipeWeapon(weapon);
	}
#pragma endregion Lyn Weapon
#pragma region Zakan
	{
		SkinnedMeshRenderer::Desc skin;
		skin.meshName = L"zakan";
		zakan->AddComponent<SkinnedMeshRenderer>(&skin);
		auto skinRenderer = zakan->GetComponent<SkinnedMeshRenderer>();
		skinRenderer->SetFrustumCullingState(FRUSTUM_CULLING_STATE_FREE_PASS);
		skinRenderer->SetMaterial(L"zakan_arm");
		//skinRenderer->AddMaterial(L"zakan_cape");
		skinRenderer->AddMaterial(L"zakan_head");
		skinRenderer->AddMaterial(L"zakan_body");
		CharacterController::Desc character;
		character.height = 7.f;
		character.radius = 4.f;
		character.center = { 0.f,7.6f,0.f };
		zakan->AddComponent<EnemyStateControl>();
		zakan->AddComponent<CharacterController>(&character);
		zakan->AddComponent<BnS_Enemy>();
		AnimationController::Desc anim;
		anim.meshName = L"zakan";
		Matrix rotMat;
		anim.rootMatrix = *D3DXMatrixRotationY(&rotMat, -90 * Deg2Rad);

		zakan->AddComponent<AnimationController>(&anim);
		zakan->AddComponent<AudioSource>();
		zakan->AddComponent<ZakanEffectControl>();
	

		auto stateCtrl = zakan->GetComponent<EnemyStateControl>();
		stateCtrl->AddState<ZakanSpawn>(L"spawn");
		stateCtrl->AddState<ZakanMove>(L"move");

		stateCtrl->AddState<ZakanPeaceIdle>(L"peace_idle");
		stateCtrl->AddState<ZakanBattleIdle>(L"battle_idle");
		stateCtrl->AddState<ZakanNATK1>(L"NATK1");
		stateCtrl->AddState<ZakanNATK2>(L"NATK2");
		stateCtrl->AddState<ZakanSmash>(L"smash");
		stateCtrl->AddState<ZakanPattern>(L"pattern");
		stateCtrl->AddState<ZakanDown>(L"down");
		stateCtrl->AddState<ZakanAir>(L"air");
		stateCtrl->AddState<ZakanRise>(L"rise");
		stateCtrl->AddState<ZakanTeleport>(L"teleport");
		stateCtrl->AddState<ZakanArea360>(L"area360");
		stateCtrl->AddState<ZakanPowerATK>(L"powerATK");
		stateCtrl->AddState<ZakanSpellExplosion>(L"explosion");
		stateCtrl->AddState<ZakanDamageShield>(L"damageShield");
		stateCtrl->AddState<ZakanSplitBlood>(L"splitBlood");
		stateCtrl->AddState<ZakanTeleportCenter>(L"teleportCenter");
		stateCtrl->AddState<ZakanDead>(L"dead");
		stateCtrl->AddState<ZakanChange>(L"change");
		stateCtrl->AddState<ZakanBackStep>(L"backStep");
		stateCtrl->AddState<ZakanFireSpellWave>(L"fireSpellWave");
		stateCtrl->AddState<ZakanSpellSuction>(L"spellSuction");
		stateCtrl->AddState<ZakanStun>(L"stun");









		stateCtrl->InitState(L"peace_idle");

		auto animCtrl = zakan->GetComponent<AnimationController>();
		animCtrl->AddAnimationClip("Zakan_P_Std_Mov_Idle", 1.f, true);
		animCtrl->AddAnimationClip("Zakan_B_Std_Mov_Idle", 1.f, true);
		animCtrl->AddAnimationClip("Zakan_B_None_Mov_Idle", 1.f, true);

		animCtrl->AddAnimationClip("Zakan_B_Std_RunFront", 1.f, true);


		animCtrl->AddAnimationClip("Zakan_B_Std_NATK1_Cast", 1.3f, false);
		animCtrl->AddAnimationClip("Zakan_B_Std_NATK1_Exec", 1.2f, false);
		animCtrl->AddAnimationClip("Zakan_B_Std_NATK2_Cast", 1.3f, false);
		animCtrl->AddAnimationClip("Zakan_B_Std_NATK2_Exec", 1.2f, false);

		animCtrl->AddAnimationClip("Zakan_B_Spell_Skl_Smash_Cast", 1.2f, false);
		animCtrl->AddAnimationClip("Zakan_B_Spell_Skl_Smash_Exec1", 1.2f, false);
		animCtrl->AddAnimationClip("Zakan_B_Spell_Skl_Smash_Exec2", 1.2f, false);

		animCtrl->AddAnimationClip("Zakan_B_Std_Down_Front_Start", 1.f, false);
		animCtrl->AddAnimationClip("Zakan_B_Std_Down_Front_Looping", 1.f, true);
		animCtrl->AddAnimationClip("Zakan_B_Std_Down_Front_End", 1.f, false);

		animCtrl->AddAnimationClip("Zakan_B_Std_Down_Start", 0.5f, false);
		animCtrl->AddAnimationClip("Zakan_B_Std_Down_Looping", 1.5f, true);
		animCtrl->AddAnimationClip("Zakan_B_Std_Down", 0.5f, false);

		animCtrl->AddAnimationClip("Zakan_B_Std_MidAir1_idle", 1.f, true);
		animCtrl->AddAnimationClip("Zakan_B_Std_MidAir1_lower", 1.5f, false);
		animCtrl->AddAnimationClip("Zakan_B_Std_MidAir1_upper", 1.5f, false);
		animCtrl->AddAnimationClip("Zakan_B_Std_MidAir2_upper", 1.f, false);

		animCtrl->AddAnimationClip("Zakan_B_Spell_Skl_Teleport_Cast", 1.1f, false);
		animCtrl->AddAnimationClip("Zakan_B_Spell_Skl_Teleport_Fire", 0.8f, false);
		animCtrl->AddAnimationClip("Zakan_B_Spell_Skl_Teleport_End", 0.8f, false);

		animCtrl->AddAnimationClip("Zakan_B_Spell_Skl_Area360_Cast", 1.1f, false);
		animCtrl->AddAnimationClip("Zakan_B_Spell_Skl_Area360_Exec", 1.1f, false);

		animCtrl->AddAnimationClip("Zakan_B_Spell_Skl_PowerATK_Cast", 1.1f, false);
		animCtrl->AddAnimationClip("Zakan_B_Skl_PowerATK_Exec1", 1.1f, false);
		animCtrl->AddAnimationClip("Zakan_B_Skl_PowerATK_Exec2", 1.1f, false);
		animCtrl->AddAnimationClip("Zakan_B_Spell_Skl_PowerATK_End", 0.8f, false);
		animCtrl->AddAnimationClip("Zakan_B_Spell_Skl_PowerATK_Fire", 1.f, false);

		animCtrl->AddAnimationClip("Zakan_B_Spell_Explosion_Cast", 1.f, false);
		animCtrl->AddAnimationClip("Zakan_B_Spell_Explosion_Exec", 1.f, false);
		animCtrl->AddAnimationClip("Zakan_B_Spell_Explosion_Exec1", 1.f, false);
		animCtrl->AddAnimationClip("Zakan_B_Spell_Explosion_Exec2", 1.f, false);

		animCtrl->AddAnimationClip("Zakan_B_DamageShield_Cast", 0.7f, false);
		animCtrl->AddAnimationClip("Zakan_B_DamageShield_Exec", 0.7f, false);

		animCtrl->AddAnimationClip("Zakan_SplitBlood_Cast", 1.3f, false);
		animCtrl->AddAnimationClip("Zakan_SplitBlood_Exec", 1.f, false);

		animCtrl->AddAnimationClip("zakan_summon_cast", 0.7f, false);
		animCtrl->AddAnimationClip("zakan_summon_exec", 0.7f, false);

		animCtrl->AddAnimationClip("Zakan_FireSpellWave_Cast", 1.f, false);
		animCtrl->AddAnimationClip("Zakan_FireSpellWave_Exec", 1.f, false);

		animCtrl->AddAnimationClip("Zakan_SpellSuction_Cast", 1.f, false);
		animCtrl->AddAnimationClip("Zakan_SpellSuction_Exec_End", 1.f, false);
		animCtrl->AddAnimationClip("Zakan_SpellSuction_Exec_Loop", 1.f, false);

		animCtrl->AddAnimationClip("Zakan_B_Std_Stun_Start", 1.f, false);
		animCtrl->AddAnimationClip("Zakan_B_Std_Stun_Looping", 1.f, true);






	}
#pragma endregion Zakan
#pragma region Zakan Weapon

	{
		MeshRenderer::Desc mesh;
		mesh.meshName = L"zakan_weapon";
		mesh.mtrlName = L"zakan_weapon";
		CapsuleCollider::Desc capsule;
		capsule.height = 3.6f;
		capsule.isTrigger = true;
		capsule.radius = 0.1f;
		capsule.rotOffset = { 0,0,77 };
		capsule.posOffset = { 0,1.5f,0 };
		RigidBody::Desc rigid;
		rigid.isKinematic = true;
		rigid.isGravity = false;
		
		TrailRenderer::Desc trail;
		trail.detailCount = 5;
		trail.maxTrailCount = 50;
		trail.mtrlName = L"Zakan_weapon_trail";
		auto weapon = INSTANTIATE(L"weapon")->AddComponent<MeshRenderer>(&mesh)->AddComponent<TrailRenderer>(&trail);
		weapon->SetParents(zakan, "WeaponL");
		zakan->GetComponent<ZakanEffectControl>()->CreateWeaponTrailEffect(weapon);
	}
#pragma endregion Zakan Weapon
#pragma region BnS Camera
	{
		BnS_MainCamera::Desc bnsCam;
		bnsCam.player = lyn;
		SphereCollider::Desc sphere;
		sphere.isTrigger = true;
		sphere.radius = 1.f;
		RigidBody::Desc rigid;
		rigid.isGravity = false;
		cam->AddComponent<BnS_MainCamera>(&bnsCam)->AddComponent<SphereCollider>(&sphere)
			->AddComponent<RigidBody>(&rigid)->AddComponent<Camera>()->AddComponent<CameraShake>()
			->AddComponent<AudioListener>()->AddComponent<AudioSource>()->AddComponent<AudioSource>()->AddComponent<AudioSource>();
		//INSTANTIATE()->AddComponent<Camera>()->AddComponent<CameraShake>()->SetParents(cam);
	}
#pragma endregion BnS Camera
	


	
	
}
