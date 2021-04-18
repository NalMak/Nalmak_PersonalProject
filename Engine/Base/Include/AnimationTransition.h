#pragma once

#include "Nalmak_Include.h"

class AnimationController;
class AnimationClip;

enum ANIMATION_CONDITION_COMPARISION_TYPE
{
	ANIMATION_CONDITION_COMPARISION_TYPE_EQUAL,
	ANIMATION_CONDITION_COMPARISION_TYPE_LESS,
	ANIMATION_CONDITION_COMPARISION_TYPE_GREATER,
	ANIMATION_CONDITION_COMPARISION_TYPE_NOTEQUAL,
	ANIMATION_CONDITION_COMPARISION_TYPE_MAX

};
class  NALMAK_DLL TransitionCondition
{
protected:
	string m_name;
	ANIMATION_CONDITION_COMPARISION_TYPE m_type;
public:
	virtual bool Comparision(AnimationController* anim) = 0;
};
class NALMAK_DLL TransitionConditionFloat : public TransitionCondition
{
public:
	TransitionConditionFloat(const string& _name, float _value, ANIMATION_CONDITION_COMPARISION_TYPE _type);
private:
	float m_value;
public:
	virtual bool Comparision(AnimationController* anim) override;
};
class NALMAK_DLL TransitionConditionInt : public TransitionCondition
{
public:
	TransitionConditionInt(const string& _name, int _value, ANIMATION_CONDITION_COMPARISION_TYPE _type);
private:
	int m_value;
public:
	virtual bool Comparision(AnimationController* anim) override;
};
class NALMAK_DLL TransitionConditionBool : public TransitionCondition
{
public:
	TransitionConditionBool(const string& _name, bool _value, ANIMATION_CONDITION_COMPARISION_TYPE _type);
private:
	bool m_value;
public:
	virtual bool Comparision(AnimationController* anim) override;
};

class NALMAK_DLL AnimationTransition
{
	friend class AnimationController;
public:
	AnimationTransition(AnimationClip* _firstClip, AnimationClip* _secondClip, float transitionTime, float weight, bool hasExitTime, D3DXTRANSITION_TYPE _type = D3DXTRANSITION_TYPE::D3DXTRANSITION_LINEAR);
	virtual ~AnimationTransition();
public:
	void Release();
private:
	float m_transitionTime;
	float m_weight;
	bool m_hasExitTime;
	D3DXTRANSITION_TYPE m_transitionType;
	AnimationClip* m_firstClip = nullptr;
	AnimationClip* m_SecondClip = nullptr;
	vector<TransitionCondition*> m_conditions;
public:
	void AddConditionFloat(const string& _name, float _value, ANIMATION_CONDITION_COMPARISION_TYPE _type);
	void AddConditionInt(const string& _name, int _value, ANIMATION_CONDITION_COMPARISION_TYPE _type);
	void AddConditionBool(const string& _name, bool _value, ANIMATION_CONDITION_COMPARISION_TYPE _type);
	bool Comparision(AnimationController* controller) const;
};

