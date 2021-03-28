#include "DrawGizmo_2D.h"
#include "Transform.h"
#include "CanvasRenderer.h"
#include "CanvasPicking.h"
#include "PositionHandle_2D.h"
#include "ScaleHandle_2D.h"
#include "SingleImage.h"
#include "LineManager.h"

DrawGizmo_2D::DrawGizmo_2D(Desc * _desc)
{
}


void DrawGizmo_2D::SetActivePositionHandles(bool _value)
{
	m_rightPositionHandle->SetActive(_value);
	m_upPositionHandle->SetActive(_value);
}

void DrawGizmo_2D::SetActiveScaleHandles(bool _value)
{
	m_rightScaleHandle->SetActive(_value);
	m_upScaleHandle->SetActive(_value);
}


bool DrawGizmo_2D::CheckHandlePicked()
{
	PositionHandle_2D* rightHandle = m_rightPositionHandle->GetComponent<PositionHandle_2D>();
	if (rightHandle)
	{
		if(rightHandle->CheckPicked())
			return true;
	}

	PositionHandle_2D* upHandle = m_upPositionHandle->GetComponent<PositionHandle_2D>();
	if (upHandle)
	{
		if (upHandle->CheckPicked())
			return true;
	}
	
	ScaleHandle_2D* rightScaleHandle = m_rightScaleHandle->GetComponent<ScaleHandle_2D>();
	if (rightScaleHandle)
	{
		if (rightScaleHandle->CheckPicked())
			return true;
	}

	ScaleHandle_2D* upScaleHandle = m_upScaleHandle->GetComponent<ScaleHandle_2D>();
	if (upScaleHandle)
	{
		if (upScaleHandle->CheckPicked())
			return true;
	}
	return false;
}

void DrawGizmo_2D::ResetingHandlePosition()
{
	m_rightPositionHandle->GetComponent<PositionHandle_2D>()->ResetingPosition();
	m_upPositionHandle->GetComponent<PositionHandle_2D>()->ResetingPosition();

	m_rightScaleHandle->GetComponent<ScaleHandle_2D>()->ResetingPosition();
	m_upScaleHandle->GetComponent<ScaleHandle_2D>()->ResetingPosition();
}

void DrawGizmo_2D::Initialize()
{
	m_line = LineManager::GetInstance();

	SingleImage::Desc desc_si;
	PositionHandle_2D::Desc desc_ph;

	desc_si.textureName = L"defaultCircle";
	desc_ph.dir = PositionHandle_2D::RIGHT;
	desc_ph.target = m_transform;
	m_rightPositionHandle =
		INSTANTIATE()->
		AddComponent<CanvasRenderer>()->
		AddComponent<SingleImage>(&desc_si)->
		AddComponent<CanvasPicking>()->
		AddComponent<PositionHandle_2D>(&desc_ph)->
		SetScale(20.f, 20.f);
	//m_rightHandle->SetParents(m_gameObject);
	m_rightPositionHandle->GetComponent<SingleImage>()->SetColor({ 1.f,0.f,0.f,1.f });

	desc_ph.dir = PositionHandle_2D::UP;
	m_upPositionHandle =
		INSTANTIATE()->
		AddComponent<CanvasRenderer>()->
		AddComponent<SingleImage>(&desc_si)->
		AddComponent<CanvasPicking>()->
		AddComponent<PositionHandle_2D>(&desc_ph)->
		SetScale(20.f, 20.f);
	//m_upHandle->SetParents(m_gameObject);
	m_upPositionHandle->GetComponent<SingleImage>()->SetColor({ 0.f,1.f,0.f,1.f });

	ScaleHandle_2D::Desc desc_sh;
	desc_sh.dir = ScaleHandle_2D::RIGHT;
	desc_sh.target = m_transform;
	m_rightScaleHandle =
		INSTANTIATE()->
		AddComponent<CanvasRenderer>()->
		AddComponent<SingleImage>()->
		AddComponent<CanvasPicking>()->
		AddComponent<ScaleHandle_2D>(&desc_sh)->
		SetScale(20.f, 20.f);
	//m_rightHandle->SetParents(m_gameObject);
	m_rightScaleHandle->GetComponent<SingleImage>()->SetColor({ 1.f,0.f,0.f,1.f });

	desc_sh.dir = ScaleHandle_2D::UP;
	m_upScaleHandle =
		INSTANTIATE()->
		AddComponent<CanvasRenderer>()->
		AddComponent<SingleImage>()->
		AddComponent<CanvasPicking>()->
		AddComponent<ScaleHandle_2D>(&desc_sh)->
		SetScale(20.f, 20.f);
	//m_upHandle->SetParents(m_gameObject);
	m_upScaleHandle->GetComponent<SingleImage>()->SetColor({ 0.f,1.f,0.f,1.f });

	m_currentMode = NONE;
}

void DrawGizmo_2D::Update()
{
}

void DrawGizmo_2D::LateUpdate()
{
	//Matrix world = m_transform->GetNoneScaleWorldMatrix();
	//m_line->DrawLine(m_transform->position, m_transform->position + Vector3(world._11, world._12, world._13), DEBUG_COLOR_RED);		// right
	//m_line->DrawLine(m_transform->position, m_transform->position + Vector3(world._21, world._22, world._23), DEBUG_COLOR_GREEN);	// up

}
