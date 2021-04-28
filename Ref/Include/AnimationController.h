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
		Matrix rootMatrix = 
		{
			1,0,0,0,
			0,1,0,0,
			0,0,1,0,
			0,0,0,1
		};
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
	void Play(AnimationClip* _clip);
	void Play(const string& _animName);

	void PlayBlending(AnimationClip* _clip);
	void PlayBlending(const string&  _clipName);


	void Stop();
	bool IsPlay();
	void SetSpeed();
	float GetSpeed();
	float GetPlayTime();
	float GetTotalPlayTime();
	double GetPlayRemainTime();
	float GetPlayRatio();
	void SetBlendOption(float _blendTime, float _weight, D3DXTRANSITION_TYPE _type);
private:
	//void CheckNextAnimation(AnimationTransition* _transition);
	void UpdateBoneMatrix();
private:
	class SkinnedMeshRenderer* m_renderer;
	LPD3DXANIMATIONCONTROLLER m_animController;
	LPD3DXFRAME m_root;
	XFileMesh* m_mesh;
	vector<Nalmak_MeshContainer*>		m_meshContainerList;
	Matrix m_rootMatrix;
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
	void AddAnimationClip(const string& _animName, float _speed = 1, bool _loop = true);
	AnimationClip* GetAnimationClip(const string& _clipName);

private:
	float m_transitionTime;
	float m_blendWeight;
	D3DXTRANSITION_TYPE m_transtionType;

	UINT m_currentTrack;
	UINT m_nextTrack;

	double m_totalTime;
	double m_animPlayTime;

	bool m_isStop;
};