#pragma once
#include "IRenderer.h"
class DynamicMesh;

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
public:
	virtual void Render(ConstantBuffer & _cBuffer) override;
	virtual void RenderPure() override;
	virtual void BindingStreamSource() override;
public:
	virtual int GetMaterialCount() override;
	virtual Material * GetMaterial(int _index = 0) override;
	virtual void SetMaterial(Material * _material, int _index = 0) override;
	virtual void SetMaterial(const wstring & _mtrlName, int _index = 0) override;
	Mesh* GetMesh();
private:
	vector<Material*> m_materials;
	
	DynamicMesh* m_mesh;
	unsigned long GetSubsetCount();
	int m_index = 0;
};

