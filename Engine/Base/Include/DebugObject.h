#pragma once
#include "Component.h"
class NALMAK_DLL DebugObject :
	public Component
{
public:
	struct Desc
	{

	};
public:
	DebugObject(Desc* _desc);
	~DebugObject();

	// Component��(��) ���� ��ӵ�
	virtual void Initialize() override;
	virtual void Update() override;
	virtual void LateUpdate() override;
private:
	class LineManager* m_line;
	MeshRenderer* m_pickingObject[3];
public:
	bool IsPickingSuccess();
};

