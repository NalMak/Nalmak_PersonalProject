#include "LineManager.h"

#include "GameObject.h"
#include "MeshRenderer.h"
#include "Transform.h"
#include "MeshRenderer.h"
IMPLEMENT_SINGLETON(LineManager)

LineManager::LineManager()
{
}


LineManager::~LineManager()
{
	Release();
}

void LineManager::Initialize()
{
#ifdef _DEBUG
	m_lineCount = 0;

	MeshRenderer::Desc desc;
	desc.meshName = L"line";
	desc.mtrlName = L"SYS_Line_Green";
	desc.layer = 0;
	m_isLineRender = true;

	for (UINT i = 0; i < m_maxLineCount; ++i)
	{
		auto line = GameObject::Instantiate(0, L"line")->AddComponent<MeshRenderer>(&desc);
		line->SetDontDestroy(true);
		line->SetActive(false);
		line->InitializeComponents();
		m_dynamicLine.emplace_back(line);
	}

	m_debugMaterial[0] = ResourceManager::GetInstance()->GetResource<Material>(L"SYS_Line_Red");
	m_debugMaterial[1] = ResourceManager::GetInstance()->GetResource<Material>(L"SYS_Line_Green");
	m_debugMaterial[2] = ResourceManager::GetInstance()->GetResource<Material>(L"SYS_Line_Blue");
#endif // _DEBUG

}

void LineManager::DrawLine(Vector3 _vec1, Vector3 _vec2, DEBUG_COLOR _color)
{
#ifdef _DEBUG
	if (!m_isLineRender)
		return;

	if (m_lineCount >= m_maxLineCount)
		return;

	auto line = m_dynamicLine[m_lineCount];
	line->GetComponent<MeshRenderer>()->SetMaterial(m_debugMaterial[_color]);
	line->SetActive(true);
	line->GetTransform()->scale = Vector3(Vector::Distance(_vec1, _vec2), Vector::Distance(_vec1, _vec2), Vector::Distance(_vec1, _vec2));
	Vector3 norLine = Vector::Normalize(_vec2 - _vec1);
	Vector3 axis = Vector::Cross(Vector3(1, 0, 0), norLine);
	if (axis != Vector3(0, 0, 0))
	{
		Quaternion rot;
		D3DXQuaternionRotationAxis(&rot, &axis, acos(Vector::Dot(Vector3(1, 0, 0), norLine)));
		line->GetTransform()->rotation = rot;
	}
	else
	{
		line->GetTransform()->rotation = { 0,0,0,1 };
	}
	line->GetTransform()->position = (_vec1 + _vec2) * 0.5f;


	++m_lineCount;
#endif
}

void LineManager::Release()
{
#ifdef _DEBUG
	m_dynamicLine.clear();
#endif
}

void LineManager::DeleteLines()
{
#ifdef _DEBUG
	for (UINT i = 0; i < m_lineCount; ++i)
		m_dynamicLine[i]->SetActive(false);
	m_lineCount = 0;
#endif
}

void LineManager::Toggle()
{
#ifdef _DEBUG
	m_isLineRender ^= true;
#endif
}
