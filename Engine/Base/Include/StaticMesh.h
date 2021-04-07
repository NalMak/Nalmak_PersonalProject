#pragma once
#include "Mesh.h"

// normal : 점이 구성하고 있는 평면의 수직인 벡터
class StaticMesh :
	public Mesh
{
public:
	StaticMesh();
	~StaticMesh();

	virtual void Initialize(wstring _fp) override;
	virtual void Release() override;

private:
	LPD3DXMESH			m_originMesh;
	LPD3DXMESH			m_mesh;
	//LPD3DXBUFFER -> 직접 채우진 못함. DX 함수로만 채울 수 있음  // 가장 앞 주소를 리턴받을 수 있음
	LPD3DXBUFFER		m_adjacency; // 0번 삼각형의 이웃 3개 1번 삼각형의 이웃 3개 ... 정수 배열  -> 사용 용도 : normal 이 없는 경우  유추해서 만들어냄
	LPD3DXBUFFER		m_subset;
public:
	virtual void Draw(UINT _subset = 0) override;
	virtual void BindingStreamSource(unsigned int _inputLayoutSize) override;

};
