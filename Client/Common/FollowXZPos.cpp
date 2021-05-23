#include "stdafx.h"
#include "FollowXZPos.h"


FollowXZPos::FollowXZPos(Desc* _desc)
{
}


FollowXZPos::~FollowXZPos()
{
}

void FollowXZPos::Initialize()
{
	m_target = Core::GetInstance()->FindFirstObject(OBJECT_TAG_PLAYER);
}

void FollowXZPos::Update()
{
	DEBUG_LOG(L"light pos", m_transform->GetWorldPosition());
	//m_transform->LookAt(m_target,1);
	/*m_transform->position.x = m_target->GetTransform()->GetWorldPosition().x;
	m_transform->position.z = m_target->GetTransform()->GetWorldPosition().z;
	m_transform->position.y = m_target->GetTransform()->GetWorldPosition().y + 5;*/
}
