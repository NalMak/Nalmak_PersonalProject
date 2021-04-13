#pragma once

#ifndef  __VIBUFFER_H__
#define __VIBUFFER_H__

#include "Mesh.h"

BEGIN(Nalmak)
class  VIBuffer :
	public Mesh
{
public:
	VIBuffer();
	virtual ~VIBuffer();
public:
	void OnInitialize(const TCHAR * _fp = L"");
	virtual void Initialize(wstring _fp = L"") override = 0;
private:
	virtual void Release() override;
public:
	virtual void Draw(UINT meshContainerIndex = 0, UINT subset = 0) override;
	virtual void BindingStreamSource(unsigned int _inputLayoutSize) override;

protected:
	PDIRECT3DVERTEXBUFFER9	m_vBuffer = nullptr;
	PDIRECT3DINDEXBUFFER9	m_iBuffer = nullptr;


public:
	PDIRECT3DVERTEXBUFFER9 GetVertexBuffer() { assert("Vertex Buffer is Empty!" && m_vBuffer); return m_vBuffer; }
	PDIRECT3DINDEXBUFFER9 GetIndexBuffer() { assert("Index Buffer is Empty!" && m_iBuffer); return m_iBuffer; }
	D3DPRIMITIVETYPE GetPrimitiveType() { return m_primitiveType; }

protected:
	template <typename T>
	void CopyVertexPositionData(T* _vertices, int _count)
	{
		m_vertexPositionData = new Vector3[24];

		for (int i = 0; i < _count; ++i)
		{
			m_vertexPositionData[i] = _vertices[i].position;
		}
	}





};

END
#endif // ! __VIBUFFER_H__
