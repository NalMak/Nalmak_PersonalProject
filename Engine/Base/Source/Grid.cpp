#include "..\Include\Grid.h"
#include "LineManager.h"


Grid::Grid(Desc* _desc)
{
}


Grid::~Grid()
{
}

void Grid::Initialize()
{
	m_line = LineManager::GetInstance();
}

void Grid::Update()
{
	m_line->DrawLine(Vector3(-100, 0, 0), Vector3(100, 0, 0));
	m_line->DrawLine(Vector3(0, -100, 0), Vector3(0, 100, 0));
	m_line->DrawLine(Vector3(0, 0, -100), Vector3(0, 0, 100));
}
