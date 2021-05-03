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
		AnimationController* cloneAnimationController = nullptr;
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
	void UpdateBoneSeparationMatrix(Nalmak_Frame * _bone, const Matrix & _parent, bool _isSub);
	void UpdateFixedBoneSeparationMatrix(Nalmak_Frame * _bone, const Matrix & _parent, bool _isSub);
	void UpdateFixedBoneMatrix(Nalmak_Frame * _bone, const Matrix & _parent);

	const Matrix& GetRootMatrix();

public:
	void PlayBlending(AnimationController* _otherController);

	void Play(AnimationClip* _clip);
	void Play(const string& _animName);

	void PlayBlending(AnimationClip* _clip);
	void PlayBlending(AnimationClip* _clip, double _otherTime);
	void PlayBlending(const string&  _clipName);

	void PlayBlending(AnimationClip* _clip1, AnimationClip* _clip2, float _weight);
	void PlayBlending(const string& _clip1, const string& _clip2, float _weight);

	void Stop();
	bool IsPlay();
	void SetSpeed();
	float GetSpeed();
	float GetPlayTime();
	float GetTotalPlayTime();
	double GetPlayRemainTime();
	float GetPlayRatio();
	bool IsOverTime(double _time);
	void SetFixedAnimationBoneName(string _boneName,bool _xAxis, bool _yAxis, bool _zAxis);
	void SetRootMotion(bool _isFixed);
	const string& GetCurrentPlayAnimationName();
	AnimationClip* GetCurrentPlayAnimation();

	void SetBlendOption(float _blendTime, float _weight, D3DXTRANSITION_TYPE _type);
	void SeparateBone(const string& _refBone);
	void SetSeparate(bool _separate);
private:
	//void CheckNextAnimation(AnimationTransition* _transition);
	void UpdateBoneMatrix();
private:
	class SkinnedMeshRenderer* m_renderer;
	LPD3DXANIMATIONCONTROLLER m_animController;

	LPD3DXFRAME m_root;
	LPD3DXFRAME m_subRoot;
	LPD3DXFRAME m_fixedBone;
	XFileMesh* m_mesh;
	vector<Nalmak_MeshContainer*>		m_meshContainerList;
	Matrix m_rootMatrix;
	bool m_isSeparte;
	bool m_isSub;
	bool m_isRootAnimation;
	bool m_rootMotion_fixXAxis;
	bool m_rootMotion_fixYAxis;
	bool m_rootMotion_fixZAxis;

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

	double m_currentPlayTime;
	double m_prePlayTime;
	double m_totalPlayTime;

	bool m_isStop;
};