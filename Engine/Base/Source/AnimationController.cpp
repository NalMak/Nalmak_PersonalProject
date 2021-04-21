#include "AnimationController.h"
#include "TimeManager.h"
#include "DebugManager.h"
#include "AnimationController.h"
#include "XFileMesh.h"
#include "SkinnedMeshRenderer.h"
#include "AnimationTransition.h"
#include "AnimationController.h"


AnimationController::AnimationController(Desc * _desc)
{
	m_currentTrack = 0;
	m_nextTrack = 1;
	m_totalTime = 0.f;
	m_animPlayTime = 0.0;
	m_isStop = false;

	m_currentAnimationClip = nullptr;

	
	Mesh* mesh = ResourceManager::GetInstance()->GetResource<Mesh>(_desc->meshName);

	if (mesh->GetMeshType() != MESH_TYPE_ANIMATION)
		assert(L"This Animation Controller mesh must be of animation type!" && 0);

	XFileMesh* xMesh = (XFileMesh*)mesh;
	LPD3DXANIMATIONCONTROLLER originController = xMesh->GetAnimationController();
	LPD3DXANIMATIONCONTROLLER clone;
	originController->CloneAnimationController(
		originController->GetMaxNumAnimationOutputs(),
		originController->GetMaxNumAnimationSets(),
		originController->GetMaxNumTracks(),
		originController->GetMaxNumEvents(),
		&clone
	);

	m_animController = clone;
	m_root = xMesh->GetRoot();

}

AnimationController::~AnimationController()
{
	
}


void AnimationController::Update()
{
	if (m_isStop)
		return;
	if (!m_currentAnimationClip)
		return;

	CheckNextAnimationByFrame();

	for (auto& transition : m_currentAnimationClip->transtionInfos)
	{
		if (m_totalTime > m_animPlayTime - transition->m_transitionTime)
		{
			CheckNextAnimation(transition);
		}
	}

}

void AnimationController::EachRender()
{
	if (m_isStop)
		return;
	if (!m_currentAnimationClip)
		return;

	double time = (double)TimeManager::GetInstance()->GetdeltaTime();
	

	if (m_totalTime < m_animPlayTime)
	{
		m_totalTime += time;
		m_animController->AdvanceTime(time, NULL);	// ���������� ī����Ǵ� �ð� ��(�ִϸ��̼� ���ۿ� ���� ���峪 ����Ʈ�� ���� ó���� ����ϴ� ��ü �ּ�)
		UpdateBoneMatrix();
	}
	else if (m_currentAnimationClip->loop)
	{
		m_totalTime = 0;
		m_animController->AdvanceTime(time, NULL);	
		UpdateBoneMatrix();
	}
	else
	{
		m_totalTime = m_animPlayTime;
	}
	
}


void AnimationController::Initialize()
{
	

}

//1. �ִϸ��̼���Ʈ�ѷ��� ���� �ִϸ��̼Ǽ��� �޾ƿ;��Ѵ�.
//2. �ִϸ��̼Ǽ��� Ʈ���� �����ؾ� �Ѵ�.
//3. �ִϸ��̼� Ʈ���� Ȱ��ȭ��Ų��.
//4. �ִϸ��̼� ��Ʈ�ѷ��� �ִϸ��̼��� �����Ų��.

void AnimationController::SetEntryClip(const string& _clipName)
{
	for (auto& clip : m_animationClips)
	{
		if (clip->animationName == _clipName)
		{
			m_currentAnimationClip = clip;
			Play(m_currentAnimationClip);
			return;
		}
	}
	assert(L"Can't find animation clip!" && 0);
}

void AnimationController::CheckNextAnimationByFrame()
{
	for (auto& transition : m_currentAnimationClip->transtionInfos)
	{
		if (!transition->m_hasExitTime)
			CheckNextAnimation(transition);
	}
}


void AnimationController::CheckNextAnimation(AnimationTransition* _transition)
{
	if (_transition->Comparision(this))
	{
		Play(_transition);
	}
}

void AnimationController::AddAnimationClip(const string & _animName, float _speed, bool _loop, bool _reverse)
{
	AnimationClip* clip = new AnimationClip();
	clip->animationName = _animName;
	clip->speed = _speed;
	clip->loop = _loop;
	clip->reverse = _reverse;

	LPD3DXANIMATIONSET anim = nullptr;
	m_animController->GetAnimationSetByName(_animName.c_str(), &anim);
	assert(L"Can't find animation Set!" && anim);
	clip->animationSet = anim;

	m_animationClips.emplace_back(clip);
}

AnimationTransition* AnimationController::AddAnimationTransition(const string & _firstAnim, const string & _secondAnim, float _transitionTime, float _weight,bool _hasExitTime, D3DXTRANSITION_TYPE _type)
{
	AnimationClip* first =  GetAnimationClip(_firstAnim);
	AnimationClip* second = GetAnimationClip(_secondAnim);

	AnimationTransition* transition = new AnimationTransition(first, second, _transitionTime, _weight, _hasExitTime, _type);
	first->transtionInfos.emplace_back(transition);

	return transition;

}

AnimationClip* AnimationController::GetAnimationClip(const string & _clipName)
{
	for (auto& clip : m_animationClips)
	{
		if (clip->animationName == _clipName)
		{
			return clip;
		}
	}
	return nullptr;
}


void AnimationController::UpdateBoneMatrix(Nalmak_Frame * _bone, const Matrix & _parent)
{
	_bone->boneCombinedMatrix = _bone->TransformationMatrix * _parent;

	if (_bone->pFrameFirstChild)
		UpdateBoneMatrix((Nalmak_Frame*)_bone->pFrameFirstChild, _bone->boneCombinedMatrix);

	if (_bone->pFrameSibling)
		UpdateBoneMatrix((Nalmak_Frame*)_bone->pFrameSibling, _parent);
}

void AnimationController::Play(AnimationClip * _clip)
{
	LPD3DXANIMATIONSET anim = _clip->animationSet;

	m_animController->SetTrackSpeed(m_currentTrack, _clip->speed);

	m_animController->ResetTime();
	m_totalTime = 0.0;

	m_animController->SetTrackPosition(m_currentTrack, 0.0);

}

void AnimationController::Play(const string & _animName)
{



}




void AnimationController::Play(AnimationTransition* _transition)
{
	AnimationClip* nextClip = _transition->m_SecondClip;

	m_nextTrack = (m_currentTrack == 0 ? 1 : 0); // 0�̸� ����

	LPD3DXANIMATIONSET anim = nextClip->animationSet;

	m_animPlayTime = anim->GetPeriod();
	m_animController->SetTrackAnimationSet(m_nextTrack, anim);

	m_animController->UnkeyAllTrackEvents(m_currentTrack);
	m_animController->UnkeyAllTrackEvents(m_nextTrack);

	// Ư�������� Ʈ���� Ȱ��ȭ��
	m_animController->KeyTrackEnable(m_currentTrack, false, m_totalTime + _transition->m_transitionTime);
	m_animController->KeyTrackSpeed(m_currentTrack, m_currentAnimationClip->speed, m_totalTime, _transition->m_transitionTime, _transition->m_transitionType);
	m_animController->KeyTrackWeight(m_currentTrack, _transition->m_weight, m_totalTime, _transition->m_transitionTime, _transition->m_transitionType);

	m_animController->SetTrackEnable(m_nextTrack, true);
	m_animController->KeyTrackSpeed(m_nextTrack, nextClip->speed, m_totalTime, _transition->m_transitionTime, _transition->m_transitionType);
	m_animController->KeyTrackWeight(m_nextTrack, 1 - _transition->m_weight, m_totalTime, _transition->m_transitionTime, _transition->m_transitionType);

	// ���ο� ������ �ð��� �ʱ�ȭ
	m_animController->ResetTime(); 
	m_totalTime = 0.0;

	m_animController->SetTrackPosition(m_nextTrack, 0.0);

	m_currentTrack = m_nextTrack;
	m_currentAnimationClip = nextClip;
}

void AnimationController::Stop()
{
}

bool AnimationController::IsPlay()
{
	return false;
}

void AnimationController::SetSpeed()
{
}

float AnimationController::GetSpeed()
{
	return 0.0f;
}

float AnimationController::GetPlayTime()
{
	return 0.0f;
}

float AnimationController::GetTotalPlayTime()
{
	return 0.0f;
}

void AnimationController::UpdateBoneMatrix()
{
	Matrix mat = { 1,0,0,0,0,1,0,0,0,0,1,0,0,0,0,1 };
	UpdateBoneMatrix((Nalmak_Frame*)m_root, mat);
}

void AnimationController::AddFloatParameter(const string & _param, float _value)
{
	m_parmeterFloat.emplace_back(pair<string, float>(_param, _value));
}

void AnimationController::AddBoolParameter(const string & _param, bool _value)
{
	m_parameterBool.emplace_back(pair<string, bool>(_param, _value));
}

void AnimationController::AddIntParameter(const string & _param, int _value)
{
	m_parameterInt.emplace_back(pair<string, int>(_param, _value));
}

float AnimationController::GetFloat(const string & _param)
{
	for (auto& value : m_parmeterFloat)
	{
		if (value.first == _param)
		{
			value.second;
		}
	}
	assert(L"Can't find parameter!" && 0);
	return 0;
}

bool AnimationController::GetBool(const string & _param)
{
	for (auto& value : m_parameterBool)
	{
		if (value.first == _param)
		{
			return value.second;
		}
	}
	assert(L"Can't find parameter!" && 0);
	return false;
}

int AnimationController::GetInt(const string & _param)
{
	for (auto& value : m_parameterInt)
	{
		if (value.first == _param)
		{
			return value.second;
		}
	}
	assert(L"Can't find parameter!" && 0);
	return 0;
}

void AnimationController::SetFloat(const string & _param, float _value)
{
	for (auto& value : m_parmeterFloat)
	{
		if (value.first == _param)
		{
			value.second = _value;
			return;
		}
	}
	assert(L"Can't find float parameter!" && 0);
}

void AnimationController::SetBool(const string & _param, bool _value)
{
	for (auto& value : m_parameterBool)
	{
		if (value.first == _param)
		{
			value.second = _value;
			return;
		}
	}
	assert(L"Can't find bool parameter!" && 0);
}

void AnimationController::SetInt(const string & _param, int _value)
{
	for (auto& value : m_parameterInt)
	{
		if (value.first == _param)
		{
			value.second = _value;
			return;
		}
	}
	assert(L"Can't find int parameter!" && 0);
}





void AnimationController::Release()
{

	for (auto& clip : m_animationClips)
	{
		SAFE_DELETE(clip);
	}

	m_animationClips.clear();

	SAFE_RELEASE(m_animController);
}

TransitionConditionFloat::TransitionConditionFloat(const string & _name, float _value, ANIMATION_CONDITION_COMPARISION_TYPE _type)
{
	m_value = _value;
	m_name = _name;
	m_type = _type;
}

bool TransitionConditionFloat::Comparision(AnimationController* anim)
{
	switch (m_type)
	{
	case ANIMATION_CONDITION_COMPARISION_TYPE_EQUAL:
		return m_value == anim->GetFloat(m_name);
		break;
	case ANIMATION_CONDITION_COMPARISION_TYPE_LESS:
		return m_value > anim->GetFloat(m_name);
		break;
	case ANIMATION_CONDITION_COMPARISION_TYPE_GREATER:
		return m_value < anim->GetFloat(m_name);
		break;
	case ANIMATION_CONDITION_COMPARISION_TYPE_NOTEQUAL:
		return m_value != anim->GetFloat(m_name);
		break;
	default:
		break;
	}
	assert(L"Comparision type is not valid" && 0);
	return false;
}

TransitionConditionInt::TransitionConditionInt(const string & _name, int _value, ANIMATION_CONDITION_COMPARISION_TYPE _type)
{
	m_value = _value;
	m_name = _name;
	m_type = _type;
}

bool TransitionConditionInt::Comparision(AnimationController* anim)
{
	switch (m_type)
	{
	case ANIMATION_CONDITION_COMPARISION_TYPE_EQUAL:
		return m_value == anim->GetInt(m_name);
		break;
	case ANIMATION_CONDITION_COMPARISION_TYPE_LESS:
		return m_value > anim->GetInt(m_name);
		break;
	case ANIMATION_CONDITION_COMPARISION_TYPE_GREATER:
		return m_value < anim->GetInt(m_name);
		break;
	case ANIMATION_CONDITION_COMPARISION_TYPE_NOTEQUAL:
		return m_value != anim->GetInt(m_name);
		break;
	default:
		break;
	}
	assert(L"Comparision type is not valid" && 0);
	return false;
}

TransitionConditionBool::TransitionConditionBool(const string & _name, bool _value, ANIMATION_CONDITION_COMPARISION_TYPE _type)
{
	m_value = _value;
	m_name = _name;
	m_type = _type;
}

bool TransitionConditionBool::Comparision(AnimationController* anim)
{
	switch (m_type)
	{
	case ANIMATION_CONDITION_COMPARISION_TYPE_EQUAL:
		return m_value == anim->GetBool(m_name);
		break;
	case ANIMATION_CONDITION_COMPARISION_TYPE_NOTEQUAL:
		return m_value != anim->GetBool(m_name);
		break;
	default:
		break;
	}
	assert(L"Comparision type is not valid" && 0);
	return false;
}