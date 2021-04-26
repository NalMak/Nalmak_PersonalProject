#pragma once
#include "IRenderer.h"

// https://icoder.tistory.com/entry/DirectX-Sample-SkinnedMesh

#define HARDWARE_SKINNING_BONE_COUNT_MAX 256

class XFileMesh;
class AnimationController;

class NALMAK_DLL SkinnedMeshRenderer :
	public IRenderer
{
public:
	struct Desc
	{
		wstring mtrlName = L"SYS_Standard_HWSkinning_FetchTex";
		Material* mtrl = nullptr;

		wstring meshName = L"box";
	};
public:
	SkinnedMeshRenderer(Desc* _desc);
private:
	// IRenderer을(를) 통해 상속됨
	virtual void Initialize() override;
	virtual void Update() override;
	virtual void LateUpdate() override;
	virtual void Release() override;
private:
	void RenderSW(ConstantBuffer & _cBuffer);
	void RenderHW_ConstantBuffer(ConstantBuffer & _cBuffer);
	void RenderHW_FetchTex(ConstantBuffer & _cBuffer);

public:
	virtual void Render(ConstantBuffer & _cBuffer) override;
	virtual void RenderForShadow(Shader* _shader) override;
	virtual void BindingStreamSource() override;
public:
	void ReserveMaterial(UINT _index);
	void AddMaterial(const wstring& _mtrl);
	void AddMaterial(Material* _mtrl);
	virtual int GetMaterialCount() override;
	virtual Material * GetMaterial(int _index = 0) override;
	virtual void SetMaterial(Material * _material, int _index = 0) override;
	virtual void SetMaterial(const wstring & _mtrlName, int _index = 0) override;
	XFileMesh* GetMesh();
	void SetMesh(const wstring& _meshName);
	Matrix* GetBoneWorldMatrix(const string& _boneName);
private:
	vector<Material*> m_materials;
	XFileMesh * m_mesh = nullptr;
private:
	LPDIRECT3DTEXTURE9* m_fetchTexture = nullptr;
	D3DXMATRIX** m_boneWorldMatrices = nullptr;
	UINT m_meshContainerSize;
	UINT m_textureCount;
public:
	DWORD GetSubsetCount();

};

