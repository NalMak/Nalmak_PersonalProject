#pragma once
#ifndef __CANVASPICKING_H__
#define __CANVASPICKING_H__

#include "Component.h"

class DrawGizmo_2D;
class PositionHandle_2D;
class ScaleHandle_2D;
class CanvasRenderer;
class NALMAK_DLL CanvasPicking :
	public Component
{
public:
	struct Desc
	{
	};
public:
	CanvasPicking(Desc* _desc);

	virtual void Initialize() override;
	virtual void Update() override;
	
private:
	CanvasRenderer* m_renderer;
	DrawGizmo_2D* m_gizmo;
	PositionHandle_2D* m_positionHandle;
	ScaleHandle_2D* m_scaleHandle;
};


#endif // !__MESHPICKING2D_H__
