#include "..\Include\VIBuffer.h"

USING(Nalmak)


VIBuffer::VIBuffer()
{
	m_vertexCount = 0;
	m_figureCount = 0;
	m_subsetCounts.emplace_back(1);
}


VIBuffer::~VIBuffer()
{
	Release();
}

void VIBuffer::OnInitialize(const TCHAR * _fp)
{
	m_isStatic = true;
	m_meshType = MESH_TYPE_VIBUFFER;
	Initialize(_fp);

	assert("Please Set vertex Count In Initialize!" && m_vertexCount);
	assert("Please Set figure Count In Initialize!" && m_figureCount);
}

void VIBuffer::Initialize(wstring _fp)
{

}

void VIBuffer::Release()
{
	SAFE_RELEASE(m_vBuffer);
	SAFE_RELEASE(m_iBuffer);

	SAFE_DELETE_ARR(m_indexData);
	SAFE_DELETE_ARR(m_vertexPositionData);
}

void VIBuffer::Draw(UINT meshContainerIndex, UINT subset)
{
	ThrowIfFailed(m_device->DrawIndexedPrimitive(m_primitiveType, 0, 0, GetVertexCount(), 0, GetFigureCount()));
}

void VIBuffer::BindingStreamSource(UINT _inputLayoutSize)
{
	ThrowIfFailed(m_device->SetStreamSource(0, m_vBuffer, 0, _inputLayoutSize));
	ThrowIfFailed(m_device->SetIndices(m_iBuffer));
}

