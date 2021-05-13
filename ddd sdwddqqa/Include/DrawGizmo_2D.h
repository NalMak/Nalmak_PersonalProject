#pragma once
#include "Component.h"
class NALMAK_DLL DrawGizmo_2D :
	public Component
{
public:
	enum MODE { NONE, POS, SCALE };
public:
	struct Desc
	{

	};
public:
	DrawGizmo_2D(Desc* _desc);

public:
	void SetActivePositionHandles(bool _value);
	void SetActiveScaleHandles(bool _value);
	void SetCurrentMode(MODE _mode) { m_currentMode = _mode; }

	bool GetSelected() { return m_selected; }
	MODE GetCurrentMode() { return m_currentMode; }
	bool CheckHandlePicked();

	void ResetingHandlePosition();

private:
	// Component을(를) 통해 상속됨
	virtual void Initialize() override;
	virtual void Update() override;
	virtual void LateUpdate() override;
private:
	class LineManager* m_line;

	GameObject* m_rightPositionHandle;
	GameObject* m_upPositionHandle;

	GameObject* m_rightScaleHandle;
	GameObject* m_upScaleHandle;

	bool m_selected;
	MODE m_currentMode;
};

