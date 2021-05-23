#include "stdafx.h"
#include "LynState.h"
#include "LynAttachedEffect.h"
#include "EffectMove.h"


LynState::LynState()
{
}


LynState::~LynState()
{
}

void LynState::ReduceInnerPower(UINT _innerPower)
{
	if (m_isUpper)
		m_info->ReduceInnerPower(_innerPower);
}

void LynState::AddInnerPower(UINT _innerPower)
{
	if (m_isUpper)
		m_info->AddInnerPower(_innerPower);
}

GameObject* LynState::CreateAttackInfo(AttackInfo::Desc* _attackInfo, float _forward, float _height, float _powerMultiply)
{
	if (m_isUpper)
	{
		_attackInfo->host = m_gameObject;
		_attackInfo->power =(UINT)( m_info->m_power * _powerMultiply * Nalmak_Math::Rand(0.8f,1.2f));
		if (_attackInfo->isCritical)
			_attackInfo->isCritical = true;
		else
		{
			float critical = Nalmak_Math::Rand(0.f, 1.f);
			_attackInfo->isCritical = m_info->m_criticalRatio > critical;
		}
		auto obj = INSTANTIATE(OBJECT_TAG_ATTACKINFO, OBJECT_LAYER_PLAYER_HITBOX, L"vertical")
			->AddComponent<AttackInfo>(_attackInfo)
			->SetPosition(m_transform->GetWorldPosition() + m_transform->GetForward() * _forward + Vector3(0, _height, 0))
			->SetRotation(m_transform->GetWorldRotation());

		return obj;
	}
	else 
		return nullptr;
}

GameObject*  LynState::CreateAttackInfo(AttackInfo::Desc * _attackInfo, float _forward, float _height, float _powerMultiply, AttackInfo::HitEvent _hitEvent)
{
	if (m_isUpper)
	{
		_attackInfo->host = m_gameObject;
		_attackInfo->power = (UINT)(m_info->m_power * _powerMultiply * Nalmak_Math::Rand(0.8f, 1.2f));
		float critical = Nalmak_Math::Rand(0.f, 1.f);
		_attackInfo->isCritical = m_info->m_criticalRatio > critical;
		auto attack = INSTANTIATE(OBJECT_TAG_ATTACKINFO, OBJECT_LAYER_PLAYER_HITBOX, L"vertical")
			->AddComponent<AttackInfo>(_attackInfo)
			->SetPosition(m_transform->GetWorldPosition() + m_transform->GetForward() * _forward + Vector3(0, _height, 0))
			->SetRotation(m_transform->GetWorldRotation());

		attack->GetComponent<AttackInfo>()->AddHitEvent(_hitEvent);

		return attack;
	}
	else
		return nullptr;
}

void LynState::ChangeSkillSlotTexture(BNS_SKILL_SLOT _slot, Texture * _tex, wstring _skillName)
{
	if (m_isUpper)
	{
		UIManager::GetInstance()->ChangeSkillSlotTexture(_slot, _tex, _skillName);
	}
}

void LynState::PlayOneShotLower(const wstring & _sound)
{
	if (!m_isUpper)
	{
		m_audio->PlayOneShot(_sound);
	}
}

void LynState::VoicePlay(const wstring & _sound)
{
	if (m_isUpper)
	{
		if(!m_audio->IsPlay())
			m_audio->Play(_sound);
	}
}

bool LynState::IsAnyMoveKeyInput()
{
	if (!m_isUpper)
	{
		if (InputManager::GetInstance()->GetKeyPress(KEY_STATE_W) || InputManager::GetInstance()->GetKeyPress(KEY_STATE_A)
			|| InputManager::GetInstance()->GetKeyPress(KEY_STATE_S) || InputManager::GetInstance()->GetKeyPress(KEY_STATE_D))
			return true;
	}
	return false;
}

void LynState::CreateVerticalSlashEffect(bool _dir)
{

	float posOffset;
	if (_dir)
		posOffset = 1;
	else
		posOffset = -1;

	float angle;

	for (int i = 0; i < 4; ++i)
	{
		switch (i)
		{
		case 0:
			angle = -30;
			break;
		case 1:
			angle = -60;
			break;
		case 2:
			angle = 30;
			break;
		case 3:
			angle = 60;
			break;
		default:
			break;
		}
		MeshRenderer::Desc meshRenderer2;
		meshRenderer2.meshName = L"Electronic02";
		meshRenderer2.mtrlName = L"Lyn_VerticalCut2";
		LynAttachedEffect::Desc effectDesc2;
		effectDesc2.emissionPower = 12.f;
		effectDesc2.lifeTime = Nalmak_Math::Rand(0.24f,0.28f);
		effectDesc2.scaleAnimation = { 0.3f,3.5f,3.1f };
		EffectMove::Desc effectMove2;
		effectMove2.speed = 55.f;
		effectMove2.direction = m_transform->GetForward();
		Quaternion rot2;
		D3DXQuaternionRotationYawPitchRoll(&rot2, 90.f * Deg2Rad, angle * Deg2Rad, 0);

		auto effect2 = INSTANTIATE()->AddComponent<MeshRenderer>(&meshRenderer2)->AddComponent<LynAttachedEffect>(&effectDesc2)
			->AddComponent<EffectMove>(&effectMove2)
			->SetScale(0.1f, 0.1f, 0.1f)->SetRotation(rot2 * m_transform->GetWorldRotation())
			->SetPosition(m_transform->position.x, m_transform->position.y + 0.1f, m_transform->position.z);
		effect2->GetTransform()->position -= m_transform->GetForward();
		effect2->GetTransform()->position -= m_transform->GetRight() * posOffset * 1.1f;

		if (i == 0)
		{
			PointLight::Desc point;
			point.color = Vector3(0.85f, 0.9f, 1.f);
			point.radius = 12.f;
			point.diffuseIntensity = 6.f;
			effect2->AddComponent<PointLight>(&point);
		}
	}


}



void LynState::PlayOneShot(const wstring& _sound)
{
	if (m_isUpper)
	{
		m_audio->PlayOneShot(_sound);
	}
}

