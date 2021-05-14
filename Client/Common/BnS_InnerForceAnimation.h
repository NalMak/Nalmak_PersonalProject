#pragma once
#include "Component.h"
class BnS_InnerForceAnimation :
	public SingleImage
{
public:
	struct Desc
	{
		wstring texName;
	};
public:
	BnS_InnerForceAnimation(Desc* _descs);
	~BnS_InnerForceAnimation();

	// Component��(��) ���� ��ӵ�
	virtual void Initialize() override;
	virtual void Update() override;
	virtual void PreRender() override;

	void SetTargetRatio(float _ratio);
	void SetCurrentRatio(float _ratio);
private:
	Material* m_material;
	float m_currentRatio;
	float m_targetRatio;

	// UIComponent��(��) ���� ��ӵ�
	virtual void Release() override;
	virtual void Render(Shader * _shader, Mesh * _mesh) override;
};

