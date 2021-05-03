#pragma once

#ifndef __ICYCLE_H__
#define __ICYCLE_H__

#include "Nalmak_Include.h"

BEGIN(Nalmak)


class NALMAK_DLL ICycle
{
public:
	ICycle();
	virtual ~ICycle();
protected:
	virtual void Initialize() = 0;
	virtual void OnEnable();
	virtual void OnDisable();
	virtual void Update();
	virtual void LateUpdate();
	virtual void PreRender();
	virtual void EachRender();
	virtual void PostRender();
	virtual void Release() = 0;

	virtual void OnTriggerEnter(Collision& _col);
	virtual void OnTriggerStay(Collision& _col);
	virtual void OnTriggerExit(Collision& _col);

	virtual void OnCollisionEnter(Collision& _col);
	virtual void OnCollisionStay(Collision& _col);
	virtual void OnCollisionExit(Collision& _col);


};
END
#endif // !__ICYCLE_H__
