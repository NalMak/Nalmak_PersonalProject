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
		wstring mtrlName = L"SYS_Standard";
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
	virtual void RenderForShadow() override;
	virtual void BindingStreamSource() override;
public:
	virtual int GetMaterialCount() override;
	virtual Material * GetMaterial(int _index = 0) override;
	virtual void SetMaterial(Material * _material, int _index = 0) override;
	virtual void SetMaterial(const wstring & _mtrlName, int _index = 0) override;
	XFileMesh* GetMesh();
private:
	vector<Material*> m_materials;
	XFileMesh * m_mesh = nullptr;
private:
	static bool m_onceInit;
	static LPDIRECT3DTEXTURE9 m_fetchTexture;
public:
	DWORD GetSubsetCount();

};

