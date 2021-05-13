#pragma once
#ifndef __UIINTERACTOR_H__
#define __UIINTERACTOR_H__

#include "Nalmak_Include.h"

#include "Event.h"
#include "EventHandler.h"
#include "Component.h"
class NALMAK_DLL UIInteractor :
	public Component
{
public:
	struct Desc
	{

	};

public:
	UIInteractor(Desc* _desc);

	virtual void Initialize() override;
	virtual void Update() override;
	virtual void Release() override;

public:
	void AddEventHandler(EventHandler _eventFunc);

private:	
	Event m_event;

};


#endif // !__UIINTERACTOR_H__

