#pragma once

#ifndef __MESHRENDERER_H__
#define __MESHRENDERER_H__

#include "IRenderer.h"

class Animator;

class NALMAK_DLL MeshRenderer :
	public IRenderer
{
public:
	struct Desc
	{
		wstring mtrlName = L"SYS_Standard";
		Material* mtrl = nullptr;

		wstring meshName = L"box";
	};
	MeshRenderer(Desc* _desc);
private:
	virtual void Initialize() override;
	virtual void Update() override;
	virtual void LateUpdate() override;
	virtual void Release() override;
public:
	virtual void Render(ConstantBuffer& _cBuffer) override;
	virtual void RenderForShadow(Shader* _shader) override;

	virtual void BindingStreamSource() override;
public:
	void AddMaterial(const wstring& _mtrl);
	void AddMaterial(Material* _mtrl);
	virtual void SetMaterial(Material * _material, int _index = 0) override;
	virtual void SetMaterial(const wstring& _mtrlName, int _index = 0) override;
	virtual void DeleteMaterial(int _index);
	void SetMesh(const wstring& _meshName);
	void SetMesh(Mesh* _mesh);
public:
	virtual Material * GetMaterial(int _index = 0) override;
	virtual float GetBoundingRadius() override;
	virtual Vector3 GetBoundingCenter() override;
	virtual int GetMaterialCount() override;
	Mesh* GetMesh();
private:
	vector<Material*> m_materials;
	Mesh* m_mesh;
	unsigned long GetSubsetCount();


};

#endif // !__MESHRENDERER_H__
