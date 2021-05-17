#pragma once

#include "Nalmak_Include.h"
#include "Component.h"
#include "Nalmak_Animation.h"
#include "AnimationTransition.h"
#include "AnimationClip.h"
#include "Bezier.h"
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
	void UpdateBoneSeparationMatrix(Nalmak_Frame * _bone, const Matrix & _parent);


	void UpdateFixedBoneSeparationMatrix(Nalmak_Frame * _bone, const Matrix & _parent);


	void UpdateFixedBoneMatrix(Nalmak_Frame * _bone, const Matrix & _parent);

	const Matrix& GetRootMatrix();

public:
	void PlayBlending(AnimationController* _otherController);

	void Play(AnimationClip* _clip, double _startTime = 0);
	void Play(const string& _animName, double _otherTime = 0);

	void PlayBlending(AnimationClip* _clip, double _otherTime = 0);
	void PlayBlending(const string&  _clipName, double _otherTime = 0);

	void PlayBlendingOrigin(AnimationClip* _clip, double _otherTime = 0);
	void PlayBlendingOrigin(const string&  _clipName, double _otherTime = 0);

	void PlayBlending(AnimationClip* _clip1, AnimationClip* _clip2, float _weight);
	void PlayBlending(const string& _clip1, const string& _clip2, float _weight);

	void Stop();
	bool IsPlay();
	bool IsPlay(const string& _name);

	double GetPlayTime();
	double GetTotalPlayTime();
	double GetPlayRemainTime();
	float GetPlayRatio();
	bool IsOverTime(double _time);
	bool IsOverRealTime(double _time);

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
	map<string,Nalmak_MeshContainer*>		m_meshContainerList;

	Matrix m_rootMatrix;
	bool m_isSeparte;
	bool m_isUpper;
	bool m_isRootAnimation;
	bool m_rootMotion_fixXAxis;
	bool m_rootMotion_fixYAxis;
	bool m_rootMotion_fixZAxis;

private:
	map<string,AnimationClip*> m_animationClips;
	AnimationClip* m_currentAnimationClip;
	AnimationController* m_otherController;
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
private:
	//0 0  0 1  1 1 1 0
	bool m_useCurve;
	Bezier m_bezier;
	Vector3 m_startOffset;
	Vector3 m_endOffset;
	Vector3 m_curretOffset;
	float m_bezierRatio;
	float m_bezierTotalTime;
	float m_bezierCurrentTime;
public:
	void SetAnimatinoOffsetByBeizer(
		const Vector3& _startOffset,
		const Vector3& _endOffset,
		float _time,
		const Vector2& _p1,
		const Vector2& _p2, 
		const Vector2& _p3,
		const Vector2& _p4);
};