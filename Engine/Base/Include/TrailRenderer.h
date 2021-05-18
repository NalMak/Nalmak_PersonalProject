#pragma once
#include "IRenderer.h"
#include "DynamicInstanceBuffer.h"

class NALMAK_DLL TrailRenderer :
	public IRenderer
{
public:
	struct Desc
	{
		wstring mtrlName = L"SYS_Trail";
		Material* mtrl = nullptr;

		int trailCountPerSec = 60;
		int maxTrailCount = 300;
		int detailCount = 1;
		int layer = 0;
	};
public:
	TrailRenderer(Desc* _desc);
	~TrailRenderer();
private:
	// IRenderer을(를) 통해 상속됨
	virtual void Initialize() override;
	virtual void Update() override;
	virtual void LateUpdate() override;
	virtual void Release() override;
	virtual void Render(Shader* _shader, ConstantBuffer& _cBuffer, UINT _containerIndex, UINT _subsetIndex) override;
private:
	virtual void BindingStreamSource() override;
public:
	void RecordTrail(const Vector3& _startPos, const Vector3& _endPos);
	virtual int GetMaterialCount() override;
	virtual Material * GetMaterial(UINT _containerIndex = 0, UINT _subsetIndex = 0) override;
	virtual void SetMaterial(Material * _material, int _index = 0) override;
	virtual void SetMaterial(const wstring & _mtrlName, int _index = 0) override;

private:
	Material* m_material;

	int m_maxTrailCount;
	int m_currentTrailCount;

	int m_catmullrom_divideCount;

	int m_maxCatmullrom_TrailCount;
	int m_currentCatmullrom_TrailCount;

	float m_secPerTrail;
	float m_timer;
	class DynamicInstanceBuffer<INPUT_LAYOUT_POSITION_UV>* m_instanceBuffer = nullptr;
	INPUT_LAYOUT_POSITION_UV* m_trailVertexData = nullptr;
	INPUT_LAYOUT_POSITION_UV* m_trailCatmullromVertexData = nullptr;

private:
	void CreateDynamicBuffer();
};

