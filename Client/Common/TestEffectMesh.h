#pragma once
#include "Component.h"
class CTestEffectMesh :
	public Component
{
public:
	typedef struct Desc
	{
	}DESC;
public:
	CTestEffectMesh(Desc* _desc);
	virtual ~CTestEffectMesh();

	// Component을(를) 통해 상속됨
	virtual void Initialize() override;
	virtual void Update() override;

private:
	GameObject* m_pObj;
	vector<Mesh*> m_vecMesh;
public:
	GameObject* GetEffectObject();

private:
	int m_iIndex;
	float m_fSpeed_size;
};

