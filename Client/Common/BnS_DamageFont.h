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

	// Component��(��) ���� ��ӵ�
	virtual void Initialize() override;
	virtual void Update() override;
private:
	void DestroyFont();
private:
	UINT m_damage;
	bool m_isCritical;
	DAMAGE_FONT_ANIMATION_TYPE m_animationType;
	float m_lifeTime;
	vector<SingleImage*> m_fontData;

	Vector3 m_velocity;
};

