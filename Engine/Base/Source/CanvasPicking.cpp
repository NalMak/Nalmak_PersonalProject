#include "..\Include\CanvasPicking.h"

#include "CanvasRenderer.h"
#include "Transform.h"
#include "DrawGizmo_2D.h"
#include "RenderManager.h"
#include "PositionHandle_2D.h"
#include "ScaleHandle_2D.h"
#include "InputManager.h"

CanvasPicking::CanvasPicking(Desc * _desc)
{
}

void CanvasPicking::Initialize()
{
	m_renderer = GetComponent<CanvasRenderer>();
	m_gizmo = GetComponent<DrawGizmo_2D>();
	m_positionHandle = GetComponent<PositionHandle_2D>();
	m_scaleHandle = GetComponent<ScaleHandle_2D>();
}

void CanvasPicking::Update()
{
	if (InputManager::GetInstance()->GetKeyDown(KEY_STATE_LEFT_MOUSE))
	{
		if (m_scaleHandle)
		{
			if (m_renderer->IsCursorOnRect())
			{
				m_scaleHandle->PickHandle(true);
			}
		}
		else if (m_positionHandle)
		{
			if (m_renderer->IsCursorOnRect())
			{
				m_positionHandle->PickHandle(true);
			}
		}
		else if (m_gizmo)
		{
			if (!m_gizmo->CheckHandlePicked())
			{
				if (m_renderer->IsCursorOnRect())
				{
					switch (m_gizmo->GetCurrentMode())
					{
					case DrawGizmo_2D::NONE:
						m_gizmo->SetActivePositionHandles(true);
						m_gizmo->SetCurrentMode(DrawGizmo_2D::POS);
						break;
					case DrawGizmo_2D::POS:
						m_gizmo->SetActivePositionHandles(false);
						m_gizmo->SetActiveScaleHandles(true);
						m_gizmo->SetCurrentMode(DrawGizmo_2D::SCALE);
						break;
					case DrawGizmo_2D::SCALE:
						m_gizmo->SetActiveScaleHandles(false);
						m_gizmo->SetCurrentMode(DrawGizmo_2D::NONE);
						break;
					}
				}
				else
				{
					m_gizmo->SetActivePositionHandles(false);
					m_gizmo->SetActiveScaleHandles(false);
					m_gizmo->SetCurrentMode(DrawGizmo_2D::NONE);
				}
			}
		}
		
	}

	if (InputManager::GetInstance()->GetKeyUp(KEY_STATE_LEFT_MOUSE))
	{
		if (m_positionHandle)
		{
			m_positionHandle->PickHandle(false);
		}
		else if (m_scaleHandle)
		{
			m_scaleHandle->PickHandle(false);
		}
	}
}