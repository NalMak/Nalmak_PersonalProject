#pragma once
#include "IState.h"
#include "LynInfo.h"
#include "AttackInfo.h"
#include "LynStateControl.h"
#include "CameraShake.h"
#include "BnS_MainCamera.h"
#include "LynSkillController.h"
#include "UIManager.h"
#include "BnS_Buff.h"
#include "LynEffectControl.h"

class LynState :
	public IState
{
	friend class LynStateControl;
public:
	LynState();
	~LynState();	
protected:
	// IState을(를) 통해 상속됨
	virtual void Initialize() = 0;
	virtual void EnterState() = 0;
	virtual void UpdateState() = 0;
	virtual void ExitState() = 0;
protected:
	AnimationController* m_animController;
	CharacterController* m_character;
	LynInfo* m_info;
	BnS_MainCamera* m_bnsMainCam;
	LynSkillController* m_skillController;
	LynEffectControl* m_effect;
	AudioSource* m_camAudio;

	bool m_isUpper;

	void ReduceInnerPower(UINT _innerPower);
	void AddInnerPower(UINT _innerPower);
	GameObject*  CreateAttackInfo(AttackInfo::Desc* _attackInfo, float _forward, float _height, float _powerMultiply);
	GameObject*  CreateAttackInfo(AttackInfo::Desc* _attackInfo, float _forward, float _height, float _powerMultiply, AttackInfo::HitEvent _hitEvent);

	void ChangeSkillSlotTexture(BNS_SKILL_SLOT _slot, Texture* _tex,wstring _skillName);
	void PlayOneShot(const wstring& _sound);
	void PlayOneShotLower(const wstring& _sound);
	void VoicePlay(const wstring& _sound);
	bool IsAnyMoveKeyInput();
private:
	AudioSource* m_audio;

protected:
	void CreateVerticalSlashEffect(bool _dir);

};

