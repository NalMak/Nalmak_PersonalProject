#pragma once
#include "IResource.h"

#include "NavMesh.h"
#include "NavLine.h"
#include "NavPoint.h"
#include "NavCell.h"

class NavMeshData :
	public IResource
{
public:
	NavMeshData();
	~NavMeshData();

	// IResource을(를) 통해 상속됨
	virtual void Initialize(wstring _fp) override;
	virtual void Release() override;
public:
	DWORD GetVertexCount();
	DWORD GetFigureCount();
	Vector3* GetVertexPositionData();
	INDEX32* GetIndexData();
private:
	DWORD m_vertexCount = 0;
	DWORD m_figureCount = 0;
	Vector3* m_vertexPositionData = nullptr;
	INDEX32* m_indexData = nullptr;
public:

};

