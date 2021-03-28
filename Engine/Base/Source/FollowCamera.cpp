#include "..\Include\FollowCamera.h"
#include "RenderManager.h"
#include "Transform.h"


FollowCamera::FollowCamera(Desc * _desc)
{
}

FollowCamera::~FollowCamera()
{
}

void FollowCamera::Initialize()
{
	m_camTrans = RenderManager::GetInstance()->GetMainCamera()->GetTransform();

	assert(L"Can't find camera!" && m_camTrans);

}

void FollowCamera::Update()
{
	m_transform->SetPosition(m_camTrans->GetWorldPosition());
}
