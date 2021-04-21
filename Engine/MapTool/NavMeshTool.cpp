// NavMeshTool.cpp : 구현 파일입니다.
//

#include "stdafx.h"
#include "Nalmak3D_MapTool.h"
#include "NavMeshTool.h"
#include "afxdialogex.h"
#include "MapToolManager.h"
#include "MapTool_NavMeshState.h"


// NavMeshTool 대화 상자입니다.

IMPLEMENT_DYNAMIC(NavMeshTool, CDialogEx)

NavMeshTool::NavMeshTool(CWnd* pParent /*=NULL*/)
	: CDialogEx(IDD_DIALOG2, pParent)
{

}

NavMeshTool::~NavMeshTool()
{
}

void NavMeshTool::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
}


BEGIN_MESSAGE_MAP(NavMeshTool, CDialogEx)
	ON_BN_CLICKED(IDC_BUTTON1, &NavMeshTool::OnBnClickedStartPosition)
	ON_BN_CLICKED(IDC_BUTTON2, &NavMeshTool::OnBnClickedEndPosition)
	ON_BN_CLICKED(IDC_BUTTON3, &NavMeshTool::OnBnClickedButtonSaveNav)
	ON_BN_CLICKED(IDC_BUTTON7, &NavMeshTool::OnBnClickedButtonLoadNav)
END_MESSAGE_MAP()


// NavMeshTool 메시지 처리기입니다.


void NavMeshTool::OnBnClickedStartPosition()
{
	MapTool_NavMeshState* nav = MapToolManager::GetInstance()->GetToolState()->GetState<MapTool_NavMeshState>(L"navMesh");
	nav->SetNavMeshToolMode(MapTool_NavMeshState::NAVMESH_TOOL_MODE_SET_START_POINT);
	// TODO: 여기에 컨트롤 알림 처리기 코드를 추가합니다.
}


void NavMeshTool::OnBnClickedEndPosition()
{
	MapTool_NavMeshState* nav = MapToolManager::GetInstance()->GetToolState()->GetState<MapTool_NavMeshState>(L"navMesh");
	nav->SetNavMeshToolMode(MapTool_NavMeshState::NAVMESH_TOOL_MODE_SET_END_POINT);
	// TODO: 여기에 컨트롤 알림 처리기 코드를 추가합니다.
}


void NavMeshTool::OnBnClickedButtonSaveNav()
{
	MapTool_NavMeshState* nav = MapToolManager::GetInstance()->GetToolState()->GetState<MapTool_NavMeshState>(L"navMesh");
	NavMesh* navmesh = nav->GetNavMesh();


	CFileDialog dlg
	(
		FALSE,
		L"nvd",
		(navmesh->GetGameObject()->GetName() + L".nvd").c_str(),
		OFN_OVERWRITEPROMPT,
		L"Data File(*.nvd) | *.nvd||",
		this
	);

	TCHAR fp[256] = L"";
	GetCurrentDirectory(256, fp);
	PathRemoveFileSpec(fp);
	lstrcat(fp, L"\\Data\\Static");
	dlg.m_ofn.lpstrInitialDir = fp;

	if (dlg.DoModal())
	{
		HANDLE handle = CreateFile(dlg.GetPathName(), GENERIC_WRITE, 0, nullptr, CREATE_ALWAYS, FILE_ATTRIBUTE_NORMAL, nullptr);
		if (INVALID_HANDLE_VALUE == handle)
		{
			AfxMessageBox(L"Failed to Save File");
			return;
		}
		DWORD byte;

		auto pointList = navmesh->GetPointList();
		auto lineList = navmesh->GetLineList();
		auto cellList = navmesh->GetCellList();

		size_t pointCount = pointList.size();
		size_t lineCount = lineList.size();
		size_t cellCount = cellList.size();


		WriteFile(handle, &pointCount, sizeof(size_t), &byte, nullptr);

		for (size_t i = 0; i < pointCount; ++i)
		{
			WriteFile(handle, &pointList[i]->position, sizeof(Vector3), &byte, nullptr);
		}

		WriteFile(handle, &lineCount, sizeof(size_t), &byte, nullptr);

		for (size_t i = 0; i < lineCount; ++i)
		{
			for (size_t j = 0; j < pointCount; ++j)
			{
				if (lineList[i]->GetPoint()[0] == pointList[j])
				{
					WriteFile(handle, &j, sizeof(size_t), &byte, nullptr);
				}
				if (lineList[i]->GetPoint()[1] == pointList[j])
				{
					WriteFile(handle, &j, sizeof(size_t), &byte, nullptr);
				}
			}
		
		}

		WriteFile(handle, &cellCount, sizeof(size_t), &byte, nullptr);

		for (size_t i = 0; i < cellCount; ++i)
		{
			for (size_t j = 0; j < pointCount; ++j)
			{
				if (cellList[i]->GetPoints()[0] == pointList[j])
				{
					WriteFile(handle, &j, sizeof(size_t), &byte, nullptr);
					continue;
				}
				if (cellList[i]->GetPoints()[1] == pointList[j])
				{
					WriteFile(handle, &j, sizeof(size_t), &byte, nullptr);
					continue;
				}
				if (cellList[i]->GetPoints()[2] == pointList[j])
				{
					WriteFile(handle, &j, sizeof(size_t), &byte, nullptr);
					continue;
				}
			}
		}

		CloseHandle(handle);
		AfxMessageBox(L"Succeeded to Save File");
	}

}


void NavMeshTool::OnBnClickedButtonLoadNav()
{
	CFileDialog dlg
	(
		TRUE,
		L"nvd",
		L"*.nvd",
		OFN_OVERWRITEPROMPT,
		L"Data File(*.nvd) | *.nvd||",
		this);

	TCHAR fp[256] = L"";
	GetCurrentDirectory(256, fp);
	PathRemoveFileSpec(fp);
	lstrcat(fp, L"\\Data\\Static");
	dlg.m_ofn.lpstrInitialDir = fp;

	if (dlg.DoModal())
	{
		DWORD byte;
		HANDLE handle = CreateFile(dlg.GetPathName(), GENERIC_READ, 0, nullptr, OPEN_EXISTING, FILE_ATTRIBUTE_NORMAL, nullptr);
		if (INVALID_HANDLE_VALUE == handle)
		{
			AfxMessageBox(L"Load File Failed");
			return;
		}

		vector<NavCell*> cells;
		vector<NavLine*> lines;
		vector<NavPoint*> points;

		auto temp = INSTANTIATE()->AddComponent<NavMesh>();
		NavMesh* nav = temp->GetComponent<NavMesh>();


		size_t count = 0;
		ReadFile(handle, &count, sizeof(size_t), &byte, nullptr);

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
			auto cell = new NavCell(nav);
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

		nav->SetData(cells, lines, points);
		MapTool_NavMeshState* navState = MapToolManager::GetInstance()->GetToolState()->GetState<MapTool_NavMeshState>(L"navMesh");
		navState->SetNavMesh(nav);

		CloseHandle(handle);

		/*for (auto& cell : cells)
		{
			SAFE_DELETE(cell);
		}
		for (auto& line : lines)
		{
			SAFE_DELETE(line);
		}
		for (auto& point : points)
		{
			SAFE_DELETE(point);
		}*/

	}
}
