#pragma once
#include "Component.h"
class TitleToStage :
	public Component
{
public:
	struct Desc
	{

	};
public:
	TitleToStage(Desc* _desc);
	~TitleToStage();

	// Component을(를) 통해 상속됨
	virtual void Initialize() override;
	virtual void Update() override;
};

