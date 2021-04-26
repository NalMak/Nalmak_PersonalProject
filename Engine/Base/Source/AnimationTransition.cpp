#include "AnimationTransition.h"



AnimationTransition::AnimationTransition(AnimationClip * _firstClip, AnimationClip * _secondClip, float transitionTime, float weight, bool hasExitTime, D3DXTRANSITION_TYPE _type)
{
	assert(L"Invalid Animation Clip!" && _firstClip);
	assert(L"Invalid Animation Clip!" && _secondClip);

	m_firstClip = _firstClip;
	m_SecondClip = _secondClip;

	m_transitionTime = transitionTime;
	m_weight = weight;
	m_hasExitTime = hasExitTime;
	m_transitionType = _type;
}

AnimationTransition::~AnimationTransition()
{
	Release();
}

void AnimationTransition::Release()
{
	for (auto& condition : m_conditions)
	{
		SAFE_DELETE(condition);
	}
}

AnimationTransition* AnimationTransition::AddConditionFloat(const string& _name, float _value, ANIM_COMPARE_TYPE _type)
{
	TransitionCondition* condition = new TransitionConditionFloat(_name, _value, _type);
	m_conditions.emplace_back(condition);

	return this;
}

AnimationTransition* AnimationTransition::AddConditionInt(const string& _name, int _value, ANIM_COMPARE_TYPE _type)
{
	TransitionCondition* condition = new TransitionConditionInt(_name, _value, _type);
	m_conditions.emplace_back(condition);

	return this;
}

AnimationTransition* AnimationTransition::AddConditionBool(const string& _name, bool _value, ANIM_COMPARE_TYPE _type)
{
	TransitionCondition* condition = new TransitionConditionBool(_name, _value, _type);
	m_conditions.emplace_back(condition);

	return this;
}

bool AnimationTransition::Comparision(AnimationController * controller) const
{
	for (auto& condition : m_conditions)
	{
		if (condition->Comparision(controller) == true)
			return true;
	}
	if(m_conditions.size() > 0)
		return false;
	return true;
}
