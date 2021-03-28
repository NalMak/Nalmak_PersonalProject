#pragma once

#ifndef __DYNAMIC_INSTANCE_BUFFER_H__
#define  __DYNAMIC_INSTANCE_BUFFER_H__
#include "VIBuffer.h"
template <typename T>
class DynamicInstanceBuffer :
	public VIBuffer
{
public:
	DynamicInstanceBuffer(int _maxCount)
	{
		ThrowIfFailed(m_device->CreateVertexBuffer(
			sizeof(T) * _maxCount,
			D3DUSAGE_DYNAMIC | D3DUSAGE_WRITEONLY,
			NULL,
			D3DPOOL_DEFAULT,
			&m_vBuffer,
			nullptr
		));
	}
	virtual void Initialize(wstring _fp = L"") override;

private:
	virtual void CreateVertexBuffer();
	virtual void CreateIndexBuffer();
public:
	void UpdateInstanceBuffer(T* _instanceList, int _count)
	{
		T* instanceData = nullptr;

		m_vBuffer->Lock(0, 0, (void**)&instanceData, D3DLOCK_DISCARD);
		memcpy(instanceData, _instanceList, sizeof(T)* _count);
		m_vBuffer->Unlock();
	}

	void CreateIndexBufferUsedByTrail(int _catmullomMaxCount);
};

#endif

template<typename T>
inline void DynamicInstanceBuffer<T>::Initialize(wstring _fp)
{
}

template<typename T>
inline void DynamicInstanceBuffer<T>::CreateVertexBuffer()
{
}

template<typename T>
inline void DynamicInstanceBuffer<T>::CreateIndexBuffer()
{
}

template<typename T>
inline void DynamicInstanceBuffer<T>::CreateIndexBufferUsedByTrail(int _triCount)
{

	m_figureCount = _triCount;

	ThrowIfFailed(m_device->CreateIndexBuffer(
		sizeof(INDEX32) * _triCount,
		0,
		D3DFMT_INDEX32,
		D3DPOOL_MANAGED,
		&m_iBuffer,
		nullptr));

	INDEX32*		indexBuffer = nullptr;

	m_iBuffer->Lock(0, 0, (void**)&indexBuffer, 0);

	int triCount = 0;
	int index  = 0;
	int CatmullromCount = (int)(_triCount * 0.5f);
	for (int i = 0; i < CatmullromCount; ++i)
	{
		index = i * 4;

		indexBuffer[triCount]._0 = index + 0;
		indexBuffer[triCount]._1 = index + 1;
		indexBuffer[triCount]._2 = index + 2;
		++triCount;

		indexBuffer[triCount]._0 = index + 0;
		indexBuffer[triCount]._1 = index + 2;
		indexBuffer[triCount]._2 = index + 3;
		++triCount;
	}

	m_iBuffer->Unlock();

}
