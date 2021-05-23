#include "stdafx.h"
#include "LynSpinSlashEffect.h"

#include "LynAttachedEffect.h"


LynSpinSlashEffect::LynSpinSlashEffect(Desc * _desc)
{
	m_boneMatrix = _desc->host->GetComponent<SkinnedMeshRenderer>()->GetBoneWorldMatrix(_desc->boneName);
	m_host = _desc->host->GetTransform();
	//m_lotateSpeedBezier = Bezier({ 0,0 }, { 0,0.532594f }, { 0.347059f,0.336765f }, { 1,0 })/*Bezier({ 0.f , 0.f }, { 0.0308824f , 0.402941f }, { 0.961765f, 0.410294f }, { 1.f ,0.f })*/;
}

LynSpinSlashEffect::~LynSpinSlashEffect()
{
}

void LynSpinSlashEffect::Initialize()
{
	m_lynAttachedEffect = GetComponent<LynAttachedEffect>();
	m_mtrl = GetComponent<MeshRenderer>()->GetMaterial();

	
}

void LynSpinSlashEffect::Update()
{
	Vector3 pos = m_host->GetWorldPosition();
	auto world =  *m_boneMatrix * m_host->GetTransform()->GetWorldMatrix();
	m_transform->position = { pos.x, world._42 + 2.f ,pos.z };
	//m_transform->position = pos;

}
