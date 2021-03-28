#pragma once
#include "Component.h"
class MeshRenderer;


// Mesh Renderer를 가진경우에만 작동!
// Mehs Renderer의 material에 접근해 0번 Texture를 애니메이션 시켜준다
// sprite는 만들어진 텍스쳐의 0번부터 마지막 인덱스까지의 묶음이다
// Resource 폴더안에 xxxx_0, xxxx_1 등 으로 텍스쳐를 저장하면 xxxx라는 이름으로 스프라이트를 만들어준다
class NALMAK_DLL Animator :
	public Component
{
public:
	struct Desc
	{
		UINT maxIndex = 0;
		UINT startIndex = 0;
		float interval = 0.05f;
		float timer = 0;
		wstring spriteName = L"default";


		bool isNormal = false;
		bool loop = true;
	};
public:
	Animator(Desc* _desc);
	~Animator();
private:
	// Component을(를) 통해 상속됨
	virtual void Initialize() override;
	virtual void Update() override;
	virtual void LateUpdate() override;
	virtual void Release() override;
private:
	size_t m_maxIndex;
	size_t m_currentIndex = 0;;
	float m_interval = 0.1f;
	float m_timer = 0;
	bool m_isNormal = false;
	bool m_loop = true;
	wstring m_animName;
	Texture* m_spriteDiffuseData;
	Texture* m_spriteNormalData;
	bool m_isPlay;
	bool m_isSleep;

public:
	void Play(wstring _spriteName);
	void Stop();
	void Resume();
	void SetInterval(float _interval) { m_interval = _interval; }
	bool IsPlay() { return m_isPlay; }
	void SetLoop(bool _loop) { m_loop = _loop; }
	wstring GetAnimationName()const { return m_animName; }
	IDirect3DBaseTexture9* GetDiffuseSprite();
	IDirect3DBaseTexture9* GetNormalSprite();
	size_t GetAnimationIndex() { return m_currentIndex; }

private:
	TimeManager* m_time;
};

