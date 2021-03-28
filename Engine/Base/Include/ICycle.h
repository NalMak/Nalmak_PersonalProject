#pragma once

#ifndef __ICYCLE_H__
#define __ICYCLE_H__

#include "Nalmak_Include.h"

BEGIN(Nalmak)

typedef vector<int> Collisions;
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
	virtual void PostRender();
	virtual void Release() = 0;

	virtual void OnTriggerEnter(Collisions& _col);
	virtual void OnTriggerStay(Collisions& _col);
	virtual void OnTriggerExit(Collisions& _col);

	virtual void OnCollisionEnter(Collisions& _col);
	virtual void OnCollisionStay(Collisions& _col);
	virtual void OnCollisionExit(Collisions& _col);


};
END
#endif // !__ICYCLE_H__
