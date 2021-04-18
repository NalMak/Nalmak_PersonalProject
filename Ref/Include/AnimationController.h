#pragma once

#include "Nalmak_Include.h"
#include "Component.h"
#include "Nalmak_Animation.h"
#include "AnimationTransition.h"
#include "AnimationClip.h"

// 트랙 -> 애니메이션 셋 -> 키 프레임

// 트랙 -> 재생도구 
class XFileMesh;
class NALMAK_DLL AnimationController : public Component
{
public:
	struct Desc
	{
		wstring meshName = L"";
	};
public:
	AnimationController(Desc* _desc);
	~AnimationController();
public:
	// Component을(를) 통해 상속됨
	virtual void Initialize() override;
	virtual	void Update() override;
	virtual void EachRender() override;
	virtual void Release() override;
public:
	static void UpdateBoneMatrix(Nalmak_Frame * _bone, const Matrix & _parent);
public:
	void SetEntryClip(const string& _clipName);

	void Play(AnimationClip* _clip);
	void Play(const string& _animName);

	void Stop();
	bool IsPlay();
	void SetSpeed();
	float GetSpeed();
	float GetPlayTime();
	float GetTotalPlayTime();
private:
	void Play(AnimationTransition* _transition);
	void CheckNextAnimationByFrame();
	void CheckNextAnimationByExitTime();
	void CheckNextAnimation(AnimationTransition* _transition);
	void UpdateBoneMatrix();
private:
	class SkinnedMeshRenderer* m_renderer;
	LPD3DXANIMATIONCONTROLLER m_animController;
	LPD3DXFRAME m_root;
	vector<Nalmak_MeshContainer*>		m_meshContainerList;
private:
	vector<AnimationClip*> m_animationClips;
	AnimationClip* m_currentAnimationClip;
private:
	vector<pair<string,float>> m_parmeterFloat;
	vector<pair<string,bool>> m_parameterBool;
	vector<pair<string,int>> m_parameterInt;
public:
	void AddFloatParameter(const string& _param, float _value);
	void AddBoolParameter(const string& _param, bool _value);
	void AddIntParameter(const string& _param, int _value);
public:
	float GetFloat(const string& _param);
	bool GetBool(const string& _param);
	int GetInt(const string& _param);
public:
	void SetFloat(const string& _param,float _value);
	void SetBool(const string& _param,bool _value);
	void SetInt(const string& _param,int _value);
public:
	void AddAnimationClip(const string& _animName, float _speed = 1, bool _loop = true, bool _reverse = false);
	AnimationTransition* AddAnimationTransition(const string & _firstAnim, const string & _secondAnim, float _transitionTime, float _weight, bool _hasExitTime, D3DXTRANSITION_TYPE _type);
	AnimationClip* GetAnimationClip(const string& _clipName);

private:
	UINT m_currentTrack;
	UINT m_nextTrack;

	double m_totalTime;
	double m_animPlayTime;

	bool m_isStop;
};