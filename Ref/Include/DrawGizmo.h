#pragma once
#include "LineManager.h"
#include "Component.h"
class NALMAK_DLL DrawGizmo :
	public Component
{
public:
	struct Desc
	{

	};
public:
	DrawGizmo(Desc* _desc);
	~DrawGizmo();

public:
	void SetActiveHandles(bool _value);
	bool GetSelected() { return m_selected; }
	bool CheckHandlePicked();

private:
	// Component을(를) 통해 상속됨
	virtual void Initialize() override;
	virtual void Update() override;
	virtual void LateUpdate() override;
private:
	LineManager* m_line;

	GameObject* m_rightHandle;
	GameObject* m_upHandle;
	GameObject* m_forwardHandle;

	bool m_selected;
};

