#include "stdafx.h"
#include "NavSelectedPoint.h"




NavSelectedPoint::NavSelectedPoint(Desc * _desc)
{
}

NavSelectedPoint::~NavSelectedPoint()
{
}

void NavSelectedPoint::Initialize()
{
}

void NavSelectedPoint::Update()
{
	Vector3 camPos = Core::GetInstance()->GetMainCamera()->GetTransform()->GetWorldPosition();
	float distance = Nalmak_Math::Distance(camPos, m_transform->GetWorldPosition());
	m_transform->scale = Vector3(1, 1, 1) * distance * 0.05f;
	m_transform->scale *= 1.1f;
}
