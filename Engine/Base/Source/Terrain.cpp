#include "..\Include\Terrain.h"
#include "Transform.h"
#include "ResourceManager.h"
#include "Camera.h"
int Terrain::m_terrainID = 0;


Terrain::Terrain(Desc * _desc)
{
	m_isChangeData = false;

	m_width = _desc->width;
	m_depth = _desc->depth;
	m_interval = _desc->interval;
	m_brushPower = _desc->brushPower;
	m_brushRadius = _desc->brushRadius;
	if (!_desc->mtrl)
		m_material = ResourceManager::GetInstance()->GetResource<Material>(_desc->mtrlName);
	else
		m_material = _desc->mtrl;

	/*Plane * viBuffer = new Plane(m_width, m_depth, m_interval);
	viBuffer->Initialize();
	m_viBuffer = viBuffer;
	ResourceManager::GetInstance()->AddResource<VIBuffer>(L"terrainData" + to_wstring(m_terrainID), viBuffer);*/
	++m_terrainID;

	m_vertexInfo = new INPUT_LAYOUT_POSITION_NORMAL_UV[(_desc->width + 1) * (_desc->depth + 1)];

	for (int row = 0; row < m_depth + 1; ++row)
	{
		for (int col = 0; col < m_width + 1; ++col)
		{
			int index = row * (m_depth + 1) + col;
			m_vertexInfo[index].position = Vector3(m_interval * col, 0.f, m_interval * row);
			m_vertexInfo[index].uv = Vector2(m_interval * col / m_width, m_interval * row / m_depth);
			m_vertexInfo[index].normal = Vector3(0.f, 0.f, 0.f);
		}
	}
}

Terrain::~Terrain()
{
}

void Terrain::Initialize()
{
	m_mainCam = RenderManager::GetInstance()->GetMainCamera();

	
}

void Terrain::Update()
{
	
	


}

void Terrain::LateUpdate()
{

}

void Terrain::Release()
{
	SAFE_DELETE_ARR(m_vertexInfo);
}

void Terrain::Render(ConstantBuffer& _cBuffer, UINT _containerIndex, UINT _subsetIndex)
{
	BindingStreamSource();

	m_renderManager->UpdateMaterial(m_material, _cBuffer);
	m_renderManager->UpdateRenderTarget();

	Shader* shader = m_material->GetShader();

	assert("Current Shader is nullptr! " && shader);

	m_transform->UpdateMatrix();
	shader->SetMatrix("g_world", GetTransform()->GetWorldMatrix());

	shader->CommitChanges();				   // BeginPass 호출시 반드시 그리기 전에 호출
												   ////////////////////////////////////////////////////////////////////////////////////
												   // DrawPrimitive (index 사용 x)
												   // Type, 이번에 이용될 인데스, 최소 참조갯수, 호출될 버텍스 수, 인덱스 버퍼내에서 읽기 시작할 인덱스, 그리는 도형 수
	m_viBuffer->Draw();
}

void Terrain::BindingStreamSource()
{
	ThrowIfFailed(m_device->SetStreamSource(0, m_viBuffer->GetVertexBuffer(), 0, m_material->GetShader()->GetInputLayoutSize()));
	ThrowIfFailed(m_device->SetIndices(m_viBuffer->GetIndexBuffer()));
}

float Terrain::GetHeight(const Vector3 & _pos)
{
	if (_pos.x < 0 || _pos.x > m_width * m_interval)
		return 0;

	if(_pos.y < 0 || _pos.y > m_depth * m_interval)
		return 0;

	int widthIndex = (int)(_pos.x / m_interval);
	int depthIndex = (int)(_pos.z / m_interval);


	Vector3 xzPos = Vector3(_pos.x, 0, _pos.z);

	float distance1 = Nalmak_Math::Distance(xzPos, Vector3(widthIndex * m_interval, 0, depthIndex * m_interval));
	float distance2 = Nalmak_Math::Distance(xzPos, Vector3((widthIndex + 1) * m_interval, 0, (depthIndex + 1)* m_interval));


	D3DXPLANE plane;
	Vector3 v0;
	Vector3 v1;
	Vector3 v2;

	if (distance1 < distance2)
	{
		v0 = m_vertexInfo[(m_depth + 1) * depthIndex + widthIndex].position;
		v1 = m_vertexInfo[(m_depth + 1) * depthIndex + (widthIndex + 1)].position;
		v2 = m_vertexInfo[(m_depth + 1) * (depthIndex + 1) + widthIndex].position;

		D3DXPlaneFromPoints(&plane, &v0, &v1, &v2);
	}
	else
	{
		v0 = m_vertexInfo[(m_depth + 1) * (depthIndex + 1)+ (widthIndex + 1)].position;
		v1 = m_vertexInfo[(m_depth + 1) * depthIndex + widthIndex + 1].position;
		v2 = m_vertexInfo[(m_depth + 1) * (depthIndex + 1) + widthIndex].position;

		D3DXPlaneFromPoints(&plane, &v0, &v1, &v2);
	}
	// ax + by + cz + d = 0;
	if (plane.b == 0)
	{
		return 0;
	}
	float height = (-plane.a * _pos.x - plane.c * _pos.z - plane.d) / plane.b;
	return height;
}

float Terrain::GetBoundingRadius()
{
	return m_viBuffer->GetBoundingSphereRadius();
}

Vector3 Terrain::GetBoundingCenter()
{
	return m_viBuffer->GetBoundingSphereCenter();
}


int Terrain::GetMaterialCount()
{
	return 1;
}

Material * Terrain::GetMaterial(int _index)
{
	return m_material;
}

void Terrain::SetMaterial(Material * _material, int _index)
{
	m_material = _material;
}

void Terrain::SetMaterial(const wstring & _mtrlName, int _index)
{
	m_material = ResourceManager::GetInstance()->GetResource<Material>(_mtrlName);
}
