#pragma once
#include "IResource.h"
class CubeTexture :
	public IResource
{
public:
	CubeTexture();
	~CubeTexture();

	// IResource��(��) ���� ��ӵ�
	virtual void Initialize(wstring _fp) override;
	virtual void Release() override;
public:
	LPDIRECT3DCUBETEXTURE9 GetCubeTexture() { return m_cubeTexture; }
private:
	LPDIRECT3DCUBETEXTURE9 m_cubeTexture;
};

