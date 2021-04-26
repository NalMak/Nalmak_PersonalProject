#include "NavMeshData.h"


NavMeshData::NavMeshData()
{
}


NavMeshData::~NavMeshData()
{
}

void NavMeshData::Initialize(wstring _fp)
{
	HANDLE handle = CreateFile(_fp.c_str(), GENERIC_READ, 0, nullptr, OPEN_EXISTING, FILE_ATTRIBUTE_NORMAL, nullptr);

	if (INVALID_HANDLE_VALUE == handle)
	{
		ERR_MSG((L"Can't Load " + _fp + L" : Nav Mesh Data ").c_str());
		assert(0);
		return;
	}
	DWORD byte;

	size_t count = 0;
	ReadFile(handle, &count, sizeof(size_t), &byte, nullptr);

	vector<NavCell*> cells;
	vector<NavLine*> lines;
	vector<NavPoint*> points;

	vector<INDEX32> indices;


	for (size_t i = 0; i < count; ++i)
	{
		Vector3 point;
		ReadFile(handle, &point, sizeof(Vector3), &byte, nullptr);
		points.emplace_back(new NavPoint(point.x, point.y, point.z));
	}

	ReadFile(handle, &count, sizeof(size_t), &byte, nullptr);
	for (size_t i = 0; i < count; ++i)
	{
		size_t index;
		size_t index2;
		ReadFile(handle, &index, sizeof(size_t), &byte, nullptr);
		ReadFile(handle, &index2, sizeof(size_t), &byte, nullptr);

		auto line = new NavLine(points[index], points[index2]);
		lines.emplace_back(line);
	}

	ReadFile(handle, &count, sizeof(size_t), &byte, nullptr);
	for (size_t i = 0; i < count; ++i)
	{
		size_t index;
		ReadFile(handle, &index, sizeof(size_t), &byte, nullptr);
		size_t index2;
		ReadFile(handle, &index2, sizeof(size_t), &byte, nullptr);
		size_t index3;
		ReadFile(handle, &index3, sizeof(size_t), &byte, nullptr);
		INDEX32 index32;
		index32._0 = (DWORD)index;
		index32._1 = (DWORD)index2;
		index32._2 = (DWORD)index3;

		indices.emplace_back(index32);

		auto cell = new NavCell;
		cell->GetPoints()[0] = points[index];
		cell->GetPoints()[1] = points[index2];
		cell->GetPoints()[2] = points[index3];

		points[index]->AddParentCell(cell);
		points[index2]->AddParentCell(cell);
		points[index3]->AddParentCell(cell);

		for (size_t j = 0; j < lines.size(); ++j)
		{
			if (lines[j]->GetPoint()[0] == points[index] || lines[j]->GetPoint()[0] == points[index2] || lines[j]->GetPoint()[0] == points[index3])
			{
				if (lines[j]->GetPoint()[1] == points[index] || lines[j]->GetPoint()[1] == points[index2] || lines[j]->GetPoint()[1] == points[index3])
				{
					cell->AddLine(lines[j]);
				}
			}
		}
		cells.emplace_back(cell);

	}

	m_vertexCount = (DWORD)points.size();
	m_vertexPositionData = new Vector3[m_vertexCount];
	for (size_t i = 0; i < m_vertexCount; ++i)
		m_vertexPositionData[i] = points[i]->position;
	m_figureCount = (DWORD)cells.size();
	m_indexData = new INDEX32[m_figureCount];
	for (size_t i = 0; i < m_figureCount; ++i)
	{
		m_indexData[i] = indices[i];
	}

	CloseHandle(handle);


	for (auto& point : points)
		SAFE_DELETE(point);

	for (auto& line : lines)
		SAFE_DELETE(line);

	for (auto& cell : cells)
		SAFE_DELETE(cell);


	points.clear();
	lines.clear();
	cells.clear();
}

void NavMeshData::Release()
{
	SAFE_DELETE_ARR(m_vertexPositionData);
	SAFE_DELETE_ARR(m_indexData);
}

DWORD NavMeshData::GetVertexCount()
{
	return m_vertexCount;
}

DWORD NavMeshData::GetFigureCount()
{
	return m_figureCount;
}

Vector3 * NavMeshData::GetVertexPositionData()
{
	return m_vertexPositionData;
}

INDEX32 * NavMeshData::GetIndexData()
{
	return m_indexData;
}
