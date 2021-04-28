#pragma once
#include "IRenderer.h"
class NALMAK_DLL Terrain :
	public IRenderer
{
public:
	struct Desc
	{
		wstring mtrlName = L"default";
		Material* mtrl = nullptr;

		int width = 100;
		int depth = 100;
		float interval = 0.1f;
		float brushPower = 1.f;
		float brushRadius = 1.f;
	};
public:
	Terrain(Desc* _desc);
	~Terrain();
private:
	static int m_terrainID;
private:
	// IRenderer을(를) 통해 상속됨
	virtual void Initialize() override;
	virtual void Update() override;
	virtual void LateUpdate() override;
	virtual void Release() override;
	virtual void Render(ConstantBuffer& _cBuffer, UINT _containerIndex, UINT _subsetIndex) override;
private:
	virtual void BindingStreamSource() override;
private:
	VIBuffer* m_viBuffer;
	Material* m_material;
	// IRenderer을(를) 통해 상속됨
public:
	virtual int GetMaterialCount() override;
	virtual Material * GetMaterial(int _index = 0) override;
	virtual void SetMaterial(Material * _material, int _index = 0) override;
	virtual void SetMaterial(const wstring & _mtrlName, int _index = 0) override;
public:
	float GetHeight(const Vector3& _pos);
private:
	INPUT_LAYOUT_POSITION_NORMAL_UV* m_vertexInfo;
	int m_width;
	int m_depth;
	float m_interval;
	float m_brushPower;
	float m_brushRadius;
	bool m_isChangeData;
	class Camera* m_mainCam;



	// IRenderer을(를) 통해 상속됨
	virtual float GetBoundingRadius() override;
	virtual Vector3 GetBoundingCenter() override;

};

