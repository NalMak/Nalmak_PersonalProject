#include "TrailRenderer.h"
#include "Transform.h"
#include "RenderManager.h"

TrailRenderer::TrailRenderer(Desc * _desc)
{
	if (!_desc->mtrl)
	{
		m_material = ResourceManager::GetInstance()->GetResource<Material>(_desc->mtrlName);
	}
	else
	{
		m_material = _desc->mtrl;
	}
	
	m_maxTrailCount = _desc->maxTrailCount;
	m_catmullrom_divideCount = _desc->detailCount;
	m_maxCatmullrom_TrailCount = m_maxTrailCount * m_catmullrom_divideCount;

	m_currentTrailCount = 0;
	m_currentCatmullrom_TrailCount = 0;


	m_secPerTrail = 1.f / _desc->trailCountPerSec;
	m_timer = 0;

	m_type = RENDERER_TYPE_TRAIL;

	CreateDynamicBuffer();
}

void TrailRenderer::CreateDynamicBuffer()
{
	m_instanceBuffer = new DynamicInstanceBuffer<INPUT_LAYOUT_POSITION_UV>(m_maxCatmullrom_TrailCount * 4);
	m_instanceBuffer->CreateIndexBufferUsedByTrail(m_maxCatmullrom_TrailCount * 2);

	m_trailVertexData = new INPUT_LAYOUT_POSITION_UV[m_maxTrailCount * 4];
	m_trailCatmullromVertexData = new INPUT_LAYOUT_POSITION_UV[m_maxCatmullrom_TrailCount * 4];

	for (int i = 0; i < m_maxTrailCount * 4; ++i)
	{
		m_trailVertexData[i].position = { 0,0,0 };
	}
	for (int i = 0; i < m_maxCatmullrom_TrailCount * 4; ++i)
	{
		m_trailCatmullromVertexData[i].position = { 0,0,0 };
	}
	for (int i = 0; i < m_maxCatmullrom_TrailCount; i += 4)
	{
		m_trailCatmullromVertexData[i].uv = {i / (float)m_maxCatmullrom_TrailCount, 1 };
		m_trailCatmullromVertexData[i + 1].uv = { (i + 1) / (float)m_maxCatmullrom_TrailCount, 1 };
		m_trailCatmullromVertexData[i + 2].uv = { (i + 1) / (float)m_maxCatmullrom_TrailCount, 0 };
		m_trailCatmullromVertexData[i + 3].uv = { i / (float)m_maxCatmullrom_TrailCount, 0 };

	}
}



TrailRenderer::~TrailRenderer()
{

}

void TrailRenderer::Initialize()
{
	//Vector3 worldPos = m_transform->GetWorldPosition();
	//for (int i = 0; i < m_maxTrailCount * 4; ++i)
	//{
	//	m_trailVertexData[i].position = worldPos;
	//}
	//for (int i = 0; i < m_maxCatmullrom_TrailCount * 4; ++i)
	//{
	//	m_trailCatmullromVertexData[i].position = worldPos;
	//}
}

void TrailRenderer::Update()
{
	
}

void TrailRenderer::LateUpdate()
{
	if (m_currentTrailCount < 3)
		return;

	
	m_instanceBuffer->UpdateInstanceBuffer(m_trailCatmullromVertexData, m_currentTrailCount * m_catmullrom_divideCount);
}

void TrailRenderer::Release()
{
	m_currentTrailCount = 0;
	SAFE_DELETE_ARR(m_trailVertexData);
	SAFE_DELETE_ARR(m_trailCatmullromVertexData);
	SAFE_DELETE(m_instanceBuffer);
}

void TrailRenderer::Render(ConstantBuffer& _cBuffer)
{
	if (m_currentTrailCount < 3) 
		return;

	BindingStreamSource();

	m_renderManager->UpdateMaterial(m_material, _cBuffer);
	m_renderManager->UpdateRenderTarget();

	Shader* shader = m_material->GetShader();
	assert("Current Shader is nullptr! " && shader);

	shader->CommitChanges();

	ThrowIfFailed(m_device->DrawIndexedPrimitive(D3DPRIMITIVETYPE::D3DPT_TRIANGLELIST, 0, 0, 2 * m_currentTrailCount * m_catmullrom_divideCount + 2, 0, m_currentTrailCount * m_catmullrom_divideCount * 2));

}

void TrailRenderer::RecordTrail(const Vector3 & _startPos, const Vector3 & _endPos)
{
	m_timer += dTime;
	
	if (m_timer < m_secPerTrail) 
		return;

	m_timer = 0;

	if (m_currentTrailCount < m_maxTrailCount)
		++m_currentTrailCount;

	Vector3 currentRect[4];
	Vector3 nextRect[4];


	for (int i = 0; i < m_currentTrailCount; ++i)
	{
		int index = i * 4;

		if (i == 0)
		{
			for (int j = 0; j < 4; ++j)
			{
				nextRect[j] = m_trailVertexData[index + j].position;
			}
			m_trailVertexData[index + 1].position = _startPos;
			m_trailVertexData[index + 2].position = _endPos;
			m_trailVertexData[index + 0].position = _startPos;
			m_trailVertexData[index + 3].position = _endPos;

		}
		else
		{
			for (int j = 0; j < 4; ++j)
			{
				currentRect[j] = nextRect[j];
			}
			for (int j = 0; j < 4; ++j)
			{
				nextRect[j] = m_trailVertexData[index + j].position;
			}
			for (int j = 0; j < 4; ++j)
			{
				m_trailVertexData[index + j].position = currentRect[j];
			}
		}
	}
	/*for (int i = m_currentTrailCount; i < m_maxTrailCount; ++i)
	{
		int index = i * 4;

		if (i != 0)
		{
			
			m_trailVertexData[index + 1].position = m_trailVertexData[((m_currentTrailCount - 1) * 4) + 1].position;
			m_trailVertexData[index + 2].position = m_trailVertexData[((m_currentTrailCount - 1) * 4) + 2].position;
			m_trailVertexData[index + 0].position = m_trailVertexData[((m_currentTrailCount - 1) * 4) + 0].position;
			m_trailVertexData[index + 3].position = m_trailVertexData[((m_currentTrailCount - 1) * 4) + 3].position;

		}
	
	}*/


	for (int i = 0; i < m_currentTrailCount * m_catmullrom_divideCount; ++i)
	{
		int index = i * 4;

		if (i / (float)m_catmullrom_divideCount < 1)
			continue;

		if (i / (float)m_catmullrom_divideCount >= m_currentTrailCount - 2)
			continue;

		D3DXVec3CatmullRom(&m_trailCatmullromVertexData[index + 0].position,
			&m_trailVertexData[(i / m_catmullrom_divideCount - 1) * 4 + 0].position,
			&m_trailVertexData[(i / m_catmullrom_divideCount + 0) * 4 + 0].position,
			&m_trailVertexData[(i / m_catmullrom_divideCount + 1) * 4 + 0].position,
			&m_trailVertexData[(i / m_catmullrom_divideCount + 2) * 4 + 0].position,
			float(i % m_catmullrom_divideCount) / float(m_catmullrom_divideCount));

		D3DXVec3CatmullRom(&m_trailCatmullromVertexData[index + 1].position,
			&m_trailVertexData[(i / m_catmullrom_divideCount - 1) * 4 + 0].position,
			&m_trailVertexData[(i / m_catmullrom_divideCount + 0) * 4 + 0].position,
			&m_trailVertexData[(i / m_catmullrom_divideCount + 1) * 4 + 0].position,
			&m_trailVertexData[(i / m_catmullrom_divideCount + 2) * 4 + 0].position,
			float(i % m_catmullrom_divideCount + 1) / float(m_catmullrom_divideCount));

		D3DXVec3CatmullRom(&m_trailCatmullromVertexData[index + 2].position,
			&m_trailVertexData[(i / m_catmullrom_divideCount - 1) * 4 + 3].position,
			&m_trailVertexData[(i / m_catmullrom_divideCount + 0) * 4 + 3].position,
			&m_trailVertexData[(i / m_catmullrom_divideCount + 1) * 4 + 3].position,
			&m_trailVertexData[(i / m_catmullrom_divideCount + 2) * 4 + 3].position,
			float(i % m_catmullrom_divideCount + 1) / float(m_catmullrom_divideCount));

		D3DXVec3CatmullRom(&m_trailCatmullromVertexData[index + 3].position,
			&m_trailVertexData[(i / m_catmullrom_divideCount - 1) * 4 + 3].position,
			&m_trailVertexData[(i / m_catmullrom_divideCount + 0) * 4 + 3].position,
			&m_trailVertexData[(i / m_catmullrom_divideCount + 1) * 4 + 3].position,
			&m_trailVertexData[(i / m_catmullrom_divideCount + 2) * 4 + 3].position,
			float(i % m_catmullrom_divideCount) / float(m_catmullrom_divideCount));
	}


}

void TrailRenderer::BindingStreamSource()
{
	ThrowIfFailed(m_device->SetStreamSource(0, m_instanceBuffer->GetVertexBuffer(), 0, m_material->GetShader()->GetInputLayoutSize()));
	ThrowIfFailed(m_device->SetIndices(m_instanceBuffer->GetIndexBuffer()));
}

int TrailRenderer::GetMaterialCount()
{
	return 1;
}

Material * TrailRenderer::GetMaterial(int _index)
{
	return m_material;
}

void TrailRenderer::SetMaterial(Material * _material, int _index)
{
	m_material = _material;
}

void TrailRenderer::SetMaterial(const wstring & _mtrlName, int _index)
{
	m_material = ResourceManager::GetInstance()->GetResource<Material>(_mtrlName);

}
