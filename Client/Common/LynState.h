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
	AudioSource* m_audio;
	bool m_isUpper;

	void ReduceInnerPower(UINT _innerPower);
	void AddInnerPower(UINT _innerPower);
	void CreateAttackInfo(AttackInfo::Desc* _attackInfo, float _forward, float _height, float _powerMultiply);
	void ChangeSkillSlotTexture(BNS_SKILL_SLOT _slot, Texture* _tex);
private:

};

