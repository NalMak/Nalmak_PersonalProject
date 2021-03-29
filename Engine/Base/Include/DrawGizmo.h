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
	// Component을(를) 통해 상속됨
	virtual void Initialize() override;
	virtual void Update() override;
	virtual void LateUpdate() override;
private:
	LineManager* m_line;

};

