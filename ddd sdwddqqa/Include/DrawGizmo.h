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

private:
	virtual void OnEnable();
	virtual void OnDisable();
	// Component을(를) 통해 상속됨
	virtual void Initialize() override;
	virtual void Update() override;
	virtual void LateUpdate() override;
private:
	LineManager* m_line;
	class GameObject* m_pickingGizmo[3];
public:
	void ChangeGizmoType(GIZMO_TYPE _type);
	PICKING_TYPE PickGizmo();
};

