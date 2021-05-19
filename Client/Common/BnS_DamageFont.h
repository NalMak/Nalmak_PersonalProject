#pragma once
#include "Component.h"
class BnS_DamageFont :
	public Component
{
public:
	struct Desc
	{
		UINT damage;
		bool isCritical;
		DAMAGE_FONT_ANIMATION_TYPE animationType;
	};
public:
	BnS_DamageFont(Desc* _desc);
	~BnS_DamageFont();

	// Component을(를) 통해 상속됨
	virtual void Initialize() override;
	virtual void Update() override;
private:
	void DestroyFont();
private:
	UINT m_damage;
	bool m_isCritical;
	DAMAGE_FONT_ANIMATION_TYPE m_animationType;
	float m_lifeTime;
	float m_totalLifeTime;
	Vector2 m_screenPos;
	Vector2 m_screenVelocity;
	Vector3 m_worldPos;
	Transform* m_camTrans;
	vector<SingleImage*> m_fontData;

};

