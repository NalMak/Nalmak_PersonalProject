#include "stdafx.h"
#include "NavPointDraw.h"



NavPointDraw::NavPointDraw(Desc * _desc)
{
	m_point = _desc->navPoint;
	m_cell = _desc->navCell;
}

NavPointDraw::~NavPointDraw()
{
}

void NavPointDraw::Initialize()
{
	MeshRenderer::Desc render;
	render.meshName = L"sphere";

	if (m_point)
	{
		render.mtrlName = L"SYS_Diffuse_White";
	}
	else if(m_cell)
	{
		render.mtrlName = L"SYS_Diffuse_Red";
	}
	AddComponent<MeshRenderer>(&render)->SetScale(0.2f,0.2f,0.2f);
	GetComponent<MeshRenderer>()->SetPickingEnable(false);

}

void NavPointDraw::Update()
{
	if(m_point)
		m_point->position = m_transform->GetWorldPosition();

	if (m_cell)
	{
		m_cell->Update();
		Vector3 a1, a2, a3;
		a1 = m_cell->GetPoints()[0]->position;
		a2 = m_cell->GetPoints()[1]->position;
		a3 = m_cell->GetPoints()[2]->position;

		Vector3 normal = Nalmak_Math::Cross(a1 - a2, a1 - a3);
		normal = Nalmak_Math::Normalize(normal);

		if(normal.y > 0)
			Core::GetInstance()->DrawLine(m_cell->GetCenter(), m_cell->GetCenter() + normal, DEBUG_COLOR_RED);
		else
			Core::GetInstance()->DrawLine(m_cell->GetCenter(), m_cell->GetCenter() + normal, DEBUG_COLOR_BLUE);

		m_transform->SetPosition(m_cell->GetCenter());
	}
}

void NavPointDraw::SetPoint(NavPoint * _point)
{
	m_point = _point;
}

void NavPointDraw::ReverseCell()
{
	if (!m_cell)
		return;

	m_cell->ReverseCCW();
}
