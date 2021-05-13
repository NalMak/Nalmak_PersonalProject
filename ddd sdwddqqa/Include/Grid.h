#pragma once
#include "Component.h"
class NALMAK_DLL Grid :
	public Component
{
public:
	struct Desc
	{

	};
public:
	Grid(Desc* _desc);
	~Grid();
private:
	// Component을(를) 통해 상속됨
	virtual void Initialize() override;
	virtual void Update() override;
private:
	class LineManager* m_line;
};

