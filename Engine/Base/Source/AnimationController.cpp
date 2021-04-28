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
	m_transitionTime = 1.f;
	m_blendWeight = 1.f;
	m_transtionType = D3DXTRANSITION_TYPE::D3DXTRANSITION_LINEAR;
	m_rootMatrix = _desc->rootMatrix;

	m_isStop = false;

	m_currentAnimationClip = nullptr;


	Mesh* mesh = ResourceManager::GetInstance()->GetResource<Mesh>(_desc->meshName);

	if (mesh->GetMeshType() != MESH_TYPE_ANIMATION)
		assert(L"This Animation Controller mesh must be of animation type!" && 0);
	XFileMesh* xMesh = (XFileMesh*)mesh;
	m_root = xMesh->GetRoot();

	LPD3DXANIMATIONCONTROLLER originController = xMesh->GetAnimationController();

	if (!originController)
		return;

	LPD3DXANIMATIONCONTROLLER clone;
	originController->CloneAnimationController(
		originController->GetMaxNumAnimationOutputs(),
		originController->GetMaxNumAnimationSets(),
		originController->GetMaxNumTracks(),
		originController->GetMaxNumEvents(),
		&clone
	);

	m_animController = clone;


}

AnimationController::~AnimationController()
{

}


void AnimationController::Update()
{

}

void AnimationController::EachRender()
{
	if (m_isStop)
		return;
	if (!m_currentAnimationClip)
		return;

	double time = (double)TimeManager::GetInstance()->GetdeltaTime();
	m_totalTime += time;

	if (m_totalTime < m_animPlayTime - 0.001f)
	{
		m_animController->AdvanceTime(time, NULL);	// 내부적으로 카운딩되는 시간 값(애니메이션 동작에 따른 사운드나 이펙트에 대한 처리를 담당하는 객체 주소)
		UpdateBoneMatrix();
	}
	else if (m_currentAnimationClip->loop)
	{
		m_animController->ResetTime();
		m_totalTime = 0;
		m_animController->SetTrackPosition(m_currentTrack, 0);
		//m_animController->AdvanceTime(time, NULL);	
		UpdateBoneMatrix();
	}
	else
	{
		m_totalTime = m_animPlayTime;
		m_isStop = true;
	}

}


void AnimationController::Initialize()
{


}

//1. 애니메이션컨트롤러로 부터 애니메이션셋을 받아와야한다.
//2. 애니메이션셋을 트랙에 셋팅해야 한다.
//3. 애니메이션 트랙을 활성화시킨다.
//4. 애니메이션 컨트롤러로 애니메이션을 진행시킨다.



//void AnimationController::CheckNextAnimation(AnimationTransition* _transition)
//{
//	if (_transition->Comparision(this))
//	{
//		Play(_transition);
//	}
//}

void AnimationController::AddAnimationClip(const string & _animName, float _speed, bool _loop)
{
	Mesh* mesh = ResourceManager::GetInstance()->GetResource<Mesh>(Nalmak_String::StringToWString(_animName));
	if (mesh->GetMeshType() != MESH_TYPE_ANIMATION)
		assert(L"No animation data in mesh File! " && 0);
	XFileMesh* xMesh = (XFileMesh*)mesh;

	LPD3DXANIMATIONCONTROLLER mixedAnimController;
	LPD3DXANIMATIONCONTROLLER animController = xMesh->GetAnimationController();
	UINT newAnimationCount = animController->GetNumAnimationSets();

	if (m_animController)
	{
		ThrowIfFailed(m_animController->CloneAnimationController(
			m_animController->GetMaxNumAnimationOutputs(),
			m_animController->GetMaxNumAnimationSets() + newAnimationCount,
			m_animController->GetMaxNumTracks(),
			m_animController->GetMaxNumEvents(),
			&mixedAnimController));

		m_animController->Release();
	}
	else
	{
		ThrowIfFailed(animController->CloneAnimationController(
			animController->GetMaxNumAnimationOutputs(),
			animController->GetMaxNumAnimationSets(),
			animController->GetMaxNumTracks(),
			animController->GetMaxNumEvents(),
			&mixedAnimController));
	}


	m_animController = mixedAnimController;
	LPD3DXANIMATIONSET animSet;
	for (UINT animCount = 0; animCount < newAnimationCount; ++animCount)
	{
		animController->GetAnimationSet(animCount, &animSet);
		m_animController->RegisterAnimationSet(animSet);
		UINT num =  m_animController->GetNumAnimationSets();

		AnimationClip* clip = new AnimationClip();
		clip->animationName = animSet->GetName();
		clip->speed = _speed;
		clip->loop = _loop;

		clip->animationSet = animSet;

		m_animationClips.emplace_back(clip);

		animSet->Release();

	}


	
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
	assert(L"Can't find animation clip!" && 0);
	return nullptr;
}


void AnimationController::UpdateBoneMatrix(Nalmak_Frame * _bone, const Matrix & _parent)
{
	_bone->boneCombinedMatrix = _bone->TransformationMatrix * _parent;

	DEBUG_LOG(L"bone", Vector3(_bone->boneCombinedMatrix._11, _bone->boneCombinedMatrix._21, _bone->boneCombinedMatrix._31));
	if (_bone->pFrameFirstChild)
		UpdateBoneMatrix((Nalmak_Frame*)_bone->pFrameFirstChild, _bone->boneCombinedMatrix);

	if (_bone->pFrameSibling)
		UpdateBoneMatrix((Nalmak_Frame*)_bone->pFrameSibling, _parent);
}


void AnimationController::Play(AnimationClip * _clip)
{
	LPD3DXANIMATIONSET anim = _clip->animationSet;

	m_isStop = false;

	m_currentAnimationClip = _clip;
	m_animController->SetTrackSpeed(m_currentTrack, _clip->speed);

	m_animController->ResetTime();
	m_totalTime = 0.0;
	m_animPlayTime = anim->GetPeriod();

	m_animController->SetTrackPosition(m_currentTrack, 0.0);
	m_animController->SetTrackEnable(m_currentTrack, true);
	m_animController->SetTrackAnimationSet(m_currentTrack, anim);
}


void AnimationController::Play(const string & _animName)
{
	Play(GetAnimationClip(_animName));
}

void AnimationController::PlayBlending(AnimationClip * _clip)
{
	if (!m_currentAnimationClip)
	{
		Play(_clip);
		return;
	}

	m_isStop = false;

	AnimationClip* nextClip = _clip;

	m_nextTrack = (m_currentTrack == 0 ? 1 : 0); // 0이면 시작

	LPD3DXANIMATIONSET anim = nextClip->animationSet;

	m_animController->SetTrackAnimationSet(m_nextTrack, anim);

	m_animController->UnkeyAllTrackEvents(m_currentTrack);
	m_animController->UnkeyAllTrackEvents(m_nextTrack);

	

	
	m_animController->KeyTrackEnable(m_currentTrack, false, m_totalTime + m_transitionTime);
	m_animController->KeyTrackSpeed(m_currentTrack, m_currentAnimationClip->speed, m_totalTime, m_transitionTime, m_transtionType);
	m_animController->KeyTrackWeight(m_currentTrack, 1 - m_blendWeight, m_totalTime, m_transitionTime, m_transtionType);

	m_animController->SetTrackEnable(m_nextTrack, true);
	m_animController->KeyTrackSpeed(m_nextTrack, nextClip->speed, m_totalTime, m_transitionTime, m_transtionType);
	m_animController->KeyTrackWeight(m_nextTrack, m_blendWeight, m_totalTime, m_transitionTime, m_transtionType);


	// 내부에 누적된 시간값 초기화
	m_animController->ResetTime();
	m_animPlayTime = anim->GetPeriod();
	m_totalTime = 0.0;

	m_animController->SetTrackPosition(m_nextTrack, 0.0);

	m_currentTrack = m_nextTrack;
	m_currentAnimationClip = nextClip;
}

void AnimationController::PlayBlending(const string & _clipName)
{
	PlayBlending(GetAnimationClip(_clipName));


}

void AnimationController::Stop()
{
	m_isStop = true;
}

bool AnimationController::IsPlay()
{
	return !m_isStop;
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

double AnimationController::GetPlayRemainTime()
{
	return m_animPlayTime - m_totalTime;
}

float AnimationController::GetPlayRatio()
{
	return (float)(m_totalTime / m_animPlayTime);
}

void AnimationController::SetBlendOption(float _blendTime, float _weight, D3DXTRANSITION_TYPE _type)
{
	m_transitionTime = _blendTime;
	m_blendWeight = _weight;
	m_transtionType = _type;
}


void AnimationController::UpdateBoneMatrix()
{
	UpdateBoneMatrix((Nalmak_Frame*)m_root, m_rootMatrix);
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

TransitionConditionFloat::TransitionConditionFloat(const string & _name, float _value, ANIM_COMPARE_TYPE _type)
{
	m_value = _value;
	m_name = _name;
	m_type = _type;
}

bool TransitionConditionFloat::Comparision(AnimationController* anim)
{
	switch (m_type)
	{
	case ANIM_COMPARE_TYPE_EQUAL:
		return m_value == anim->GetFloat(m_name);
		break;
	case ANIM_COMPARE_TYPE_LESS:
		return m_value > anim->GetFloat(m_name);
		break;
	case ANIM_COMPARE_TYPE_GREATER:
		return m_value < anim->GetFloat(m_name);
		break;
	case ANIM_COMPARE_TYPE_NOTEQUAL:
		return m_value != anim->GetFloat(m_name);
		break;
	default:
		break;
	}
	assert(L"Comparision type is not valid" && 0);
	return false;
}

TransitionConditionInt::TransitionConditionInt(const string & _name, int _value, ANIM_COMPARE_TYPE _type)
{
	m_value = _value;
	m_name = _name;
	m_type = _type;
}

bool TransitionConditionInt::Comparision(AnimationController* anim)
{
	switch (m_type)
	{
	case ANIM_COMPARE_TYPE_EQUAL:
		return m_value == anim->GetInt(m_name);
		break;
	case ANIM_COMPARE_TYPE_LESS:
		return m_value > anim->GetInt(m_name);
		break;
	case ANIM_COMPARE_TYPE_GREATER:
		return m_value < anim->GetInt(m_name);
		break;
	case ANIM_COMPARE_TYPE_NOTEQUAL:
		return m_value != anim->GetInt(m_name);
		break;
	default:
		break;
	}
	assert(L"Comparision type is not valid" && 0);
	return false;
}

TransitionConditionBool::TransitionConditionBool(const string & _name, bool _value, ANIM_COMPARE_TYPE _type)
{
	m_value = _value;
	m_name = _name;
	m_type = _type;
}

bool TransitionConditionBool::Comparision(AnimationController* anim)
{
	switch (m_type)
	{
	case ANIM_COMPARE_TYPE_EQUAL:
		return m_value == anim->GetBool(m_name);
		break;
	case ANIM_COMPARE_TYPE_NOTEQUAL:
		return m_value != anim->GetBool(m_name);
		break;
	default:
		break;
	}
	assert(L"Comparision type is not valid" && 0);
	return false;
}
