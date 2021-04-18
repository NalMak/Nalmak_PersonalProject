#pragma once
#include "IState.h"
class MapTool_AnimationState :
	public IState
{
public:
	MapTool_AnimationState();
	~MapTool_AnimationState();

	// IState��(��) ���� ��ӵ�
	virtual void Initialize() override;
	virtual void EnterState() override;
	virtual void UpdateState() override;
	virtual void ExitState() override;

private:
	GameObject* m_animObj;
public:
	GameObject* GetAnimationObject();
};

