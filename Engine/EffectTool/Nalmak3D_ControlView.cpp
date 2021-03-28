// Nalmak3D_ControlView.cpp : ���� �����Դϴ�.
//

#include "stdafx.h"
#include "Nalmak3D_EffectTool.h"
#include "Nalmak3D_ControlView.h"
#include "ParticleObjectManager.h"
#include "Nalmak3D_EffectToolView.h"

// Nalmak3D_ControlView

IMPLEMENT_DYNCREATE(Nalmak3D_ControlView, CFormView)

Nalmak3D_ControlView::Nalmak3D_ControlView()
	: CFormView(IDD_NALMAK3D_CONTROLVIEW)
{

}

Nalmak3D_ControlView::~Nalmak3D_ControlView()
{
	ParticleObjectManager::DestroyInstance();
}

void Nalmak3D_ControlView::DoDataExchange(CDataExchange* pDX)
{
	CFormView::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_LIST2, m_objectListBox);
	DDX_Control(pDX, IDC_EDIT1, m_posX);
	DDX_Control(pDX, IDC_EDIT2, m_posY);
	DDX_Control(pDX, IDC_EDIT3, m_posZ);
	DDX_Control(pDX, IDC_EDIT4, m_rotX);
	DDX_Control(pDX, IDC_EDIT5, m_rotY);
	DDX_Control(pDX, IDC_EDIT6, m_rotZ);
	DDX_Control(pDX, IDC_EDIT8, m_particleName);
	DDX_Control(pDX, IDC_LIST3, m_materialList);
	DDX_Control(pDX, IDC_EDIT7, m_materialName);

	DDX_Control(pDX, IDC_RADIO1, m_sphereShape);
	DDX_Control(pDX, IDC_RADIO2, m_circleShape);
	DDX_Control(pDX, IDC_RADIO3, m_boxShape);
	DDX_Control(pDX, IDC_RADIO4, m_coneShape);
	DDX_Control(pDX, IDC_EDIT18, m_minRadius);
	DDX_Control(pDX, IDC_EDIT19, m_maxRadius);
	DDX_Control(pDX, IDC_EDIT23, m_coneAngle);
	DDX_Control(pDX, IDC_EDIT20, m_width);
	DDX_Control(pDX, IDC_EDIT21, m_height);
	DDX_Control(pDX, IDC_EDIT22, m_depth);
	DDX_Control(pDX, IDC_EDIT26, m_emitCount);
	DDX_Control(pDX, IDC_EDIT16, m_duration);
	DDX_Control(pDX, IDC_EDIT25, m_minAwakeTime);
	DDX_Control(pDX, IDC_EDIT17, m_maxAwakeTime);
	DDX_Control(pDX, IDC_EDIT9, m_maxCount);
	DDX_Control(pDX, IDC_CHECK1, m_isLoop);
	DDX_Control(pDX, IDC_EDIT36, m_minLifeTime);
	DDX_Control(pDX, IDC_EDIT37, m_maxLifeTime);
	DDX_Control(pDX, IDC_EDIT40, m_minStartScale);
	DDX_Control(pDX, IDC_EDIT41, m_maxStartScale);
	DDX_Control(pDX, IDC_EDIT42, m_minEndScale);
	DDX_Control(pDX, IDC_EDIT43, m_maxEndScale);
	DDX_Control(pDX, IDC_EDIT10, m_minStartSpeed);
	DDX_Control(pDX, IDC_EDIT11, m_maxStartSpeed);
	DDX_Control(pDX, IDC_EDIT12, m_minEndSpeed);
	DDX_Control(pDX, IDC_EDIT13, m_maxEndSpeed);
	DDX_Control(pDX, IDC_EDIT14, m_minRotation);
	DDX_Control(pDX, IDC_EDIT15, m_maxRotation);
	DDX_Control(pDX, IDC_MFCCOLORBUTTON1, m_minStartColor);
	DDX_Control(pDX, IDC_MFCCOLORBUTTON2, m_maxStartColor);
	DDX_Control(pDX, IDC_MFCCOLORBUTTON3, m_minEndColor);
	DDX_Control(pDX, IDC_MFCCOLORBUTTON4, m_maxEndColor);
	DDX_Control(pDX, IDC_EDIT38, m_minstartAlpha);
	DDX_Control(pDX, IDC_EDIT44, m_minEndAlpha);
	DDX_Control(pDX, IDC_EDIT39, m_maxStartAlpha);
	DDX_Control(pDX, IDC_EDIT45, m_maxEndAlpha);
	DDX_Control(pDX, IDC_RADIO5, m_local);
	DDX_Control(pDX, IDC_RADIO6, m_world);
	DDX_Control(pDX, IDC_EDIT24, m_gravity);
	DDX_Control(pDX, IDC_EDIT30, m_velocityX);
	DDX_Control(pDX, IDC_EDIT31, m_velocityY);
	DDX_Control(pDX, IDC_EDIT32, m_velocityZ);
	DDX_Control(pDX, IDC_RADIO7, m_velocityLocal);
	DDX_Control(pDX, IDC_RADIO8, m_velocityWorld);
	DDX_Control(pDX, IDC_CHECK2, m_isPlayOnAwake);
	DDX_Control(pDX, IDC_LIST1, m_burstList);
	DDX_Control(pDX, IDC_EDIT27, m_burstTime);
	DDX_Control(pDX, IDC_EDIT28, m_burstCount);
	DDX_Control(pDX, IDC_EDIT46, m_minAngularVelocity);
	DDX_Control(pDX, IDC_EDIT47, m_maxAngularVelocity);
	DDX_Control(pDX, IDC_EDIT48, m_stretchedScale);
	DDX_Control(pDX, IDC_EDIT49, m_animationTileX);
	DDX_Control(pDX, IDC_EDIT50, m_animationTileY);
	DDX_Control(pDX, IDC_RADIO9, m_billboardNone);
	DDX_Control(pDX, IDC_RADIO10, m_billboardDefault);
	DDX_Control(pDX, IDC_RADIO11, m_billboardHorizontal);
	DDX_Control(pDX, IDC_RADIO12, m_billboardVertical);
	DDX_Control(pDX, IDC_RADIO13, m_billboardStertched);
}

BEGIN_MESSAGE_MAP(Nalmak3D_ControlView, CFormView)
	ON_BN_CLICKED(IDC_BUTTON1, &Nalmak3D_ControlView::OnBnClickedCreateParticle)
	ON_BN_CLICKED(IDC_BUTTON2, &Nalmak3D_ControlView::OnBnClickedDeleteParticle)
	ON_EN_CHANGE(IDC_EDIT1, &Nalmak3D_ControlView::OnEnChangePositionX)
	ON_EN_CHANGE(IDC_EDIT2, &Nalmak3D_ControlView::OnEnChangePositionY)
	ON_EN_CHANGE(IDC_EDIT3, &Nalmak3D_ControlView::OnEnChangePositionZ)
	ON_EN_CHANGE(IDC_EDIT4, &Nalmak3D_ControlView::OnEnChangeRotationX)
	ON_EN_CHANGE(IDC_EDIT5, &Nalmak3D_ControlView::OnEnChangeRotationY)
	ON_EN_CHANGE(IDC_EDIT6, &Nalmak3D_ControlView::OnEnChangeRotationZ)
	ON_LBN_SELCHANGE(IDC_LIST2, &Nalmak3D_ControlView::OnLbnSelchangeObjectList)
	ON_EN_CHANGE(IDC_EDIT8, &Nalmak3D_ControlView::OnEnChangeParticleName)
	ON_BN_CLICKED(IDC_BUTTON3, &Nalmak3D_ControlView::OnBnClickedNameChange)
	ON_BN_CLICKED(IDC_BUTTON4, &Nalmak3D_ControlView::OnBnClickedSelectMaterial)

	ON_BN_CLICKED(IDC_RADIO1, &Nalmak3D_ControlView::OnBnClickedSphereShape)
	ON_BN_CLICKED(IDC_RADIO2, &Nalmak3D_ControlView::OnBnClickedCircleShape)
	ON_BN_CLICKED(IDC_RADIO3, &Nalmak3D_ControlView::OnBnClickedBoxShape)
	ON_BN_CLICKED(IDC_RADIO4, &Nalmak3D_ControlView::OnBnClickedConeShape)
	ON_EN_CHANGE(IDC_EDIT18, &Nalmak3D_ControlView::OnEnChangeMinRadius)
	ON_EN_CHANGE(IDC_EDIT19, &Nalmak3D_ControlView::OnEnChangeMaxRadius)
	ON_EN_CHANGE(IDC_EDIT23, &Nalmak3D_ControlView::OnEnChangeAngle)
	ON_EN_CHANGE(IDC_EDIT20, &Nalmak3D_ControlView::OnEnChangeBoxWidth)
	ON_EN_CHANGE(IDC_EDIT21, &Nalmak3D_ControlView::OnEnChangeBoxHeight)
	ON_EN_CHANGE(IDC_EDIT22, &Nalmak3D_ControlView::OnEnChangeBoxDepth)
	ON_EN_CHANGE(IDC_EDIT26, &Nalmak3D_ControlView::OnEnChangeEmitCount)
	ON_BN_CLICKED(IDC_CHECK1, &Nalmak3D_ControlView::OnBnClickedIsLoop)
	ON_EN_CHANGE(IDC_EDIT16, &Nalmak3D_ControlView::OnEnChangeDuration)
	ON_EN_CHANGE(IDC_EDIT25, &Nalmak3D_ControlView::OnEnChangeMinAwakeTime)
	ON_EN_CHANGE(IDC_EDIT17, &Nalmak3D_ControlView::OnEnChangeMaxAwakeTime)
	ON_EN_CHANGE(IDC_EDIT9, &Nalmak3D_ControlView::OnEnChangeMaxCount)
	ON_EN_CHANGE(IDC_EDIT36, &Nalmak3D_ControlView::OnEnChangeMinLifeTime)
	ON_EN_CHANGE(IDC_EDIT37, &Nalmak3D_ControlView::OnEnChangeMaxLifeTime)
	ON_EN_CHANGE(IDC_EDIT40, &Nalmak3D_ControlView::OnEnChangeMinStartScale)
	ON_EN_CHANGE(IDC_EDIT41, &Nalmak3D_ControlView::OnEnChangeMaxStartScale)
	ON_EN_CHANGE(IDC_EDIT42, &Nalmak3D_ControlView::OnEnChangeMinEndScale)
	ON_EN_CHANGE(IDC_EDIT43, &Nalmak3D_ControlView::OnEnChangeMaxEndScale)
	ON_EN_CHANGE(IDC_EDIT10, &Nalmak3D_ControlView::OnEnChangeMinStartSpeed)
	ON_EN_CHANGE(IDC_EDIT11, &Nalmak3D_ControlView::OnEnChangeMaxStartSpeed)
	ON_EN_CHANGE(IDC_EDIT12, &Nalmak3D_ControlView::OnEnChangeMinEndSpeed)
	ON_EN_CHANGE(IDC_EDIT13, &Nalmak3D_ControlView::OnEnChangeMaxEndSpeed)
	ON_EN_CHANGE(IDC_EDIT14, &Nalmak3D_ControlView::OnEnChangeMinRotation)
	ON_EN_CHANGE(IDC_EDIT15, &Nalmak3D_ControlView::OnEnChangeMaxRotation)
	ON_BN_CLICKED(IDC_BUTTON10, &Nalmak3D_ControlView::OnBnClickedUpdateMaterial)
	ON_BN_CLICKED(IDC_MFCCOLORBUTTON1, &Nalmak3D_ControlView::OnBnClickedMinStartColor)
	ON_BN_CLICKED(IDC_MFCCOLORBUTTON2, &Nalmak3D_ControlView::OnBnClickedMaxStartColor)
	ON_BN_CLICKED(IDC_MFCCOLORBUTTON3, &Nalmak3D_ControlView::OnBnClickedMfcMinEndColor)
	ON_BN_CLICKED(IDC_MFCCOLORBUTTON4, &Nalmak3D_ControlView::OnBnClickedMfcMaxEndColor)
	ON_EN_CHANGE(IDC_EDIT38, &Nalmak3D_ControlView::OnEnChangeMinStartAlpha)
	ON_EN_CHANGE(IDC_EDIT39, &Nalmak3D_ControlView::OnEnChangeEditMaxStartAlpha)
	ON_EN_CHANGE(IDC_EDIT44, &Nalmak3D_ControlView::OnEnChangeEditMinEndAlpha)
	ON_EN_CHANGE(IDC_EDIT45, &Nalmak3D_ControlView::OnEnChangeEditMaxEndAlpha)
	ON_BN_CLICKED(IDC_BUTTON5, &Nalmak3D_ControlView::OnBnClickedPlay)
	ON_BN_CLICKED(IDC_BUTTON6, &Nalmak3D_ControlView::OnBnClickedPlayAll)
	ON_BN_CLICKED(IDC_BUTTON7, &Nalmak3D_ControlView::OnBnClickedStop)
	ON_BN_CLICKED(IDC_RADIO5, &Nalmak3D_ControlView::OnBnClickedLocal)
	ON_BN_CLICKED(IDC_RADIO6, &Nalmak3D_ControlView::OnBnClickedWorld)
	ON_EN_CHANGE(IDC_EDIT24, &Nalmak3D_ControlView::OnEnChangeGravity)
	ON_EN_CHANGE(IDC_EDIT30, &Nalmak3D_ControlView::OnEnChangeVelocityX)
	ON_EN_CHANGE(IDC_EDIT31, &Nalmak3D_ControlView::OnEnChangeVelocityY)
	ON_EN_CHANGE(IDC_EDIT32, &Nalmak3D_ControlView::OnEnChangeVelocityZ)
	ON_BN_CLICKED(IDC_RADIO7, &Nalmak3D_ControlView::OnBnClickedSetVelocityLocal)
	ON_BN_CLICKED(IDC_RADIO8, &Nalmak3D_ControlView::OnBnClickedSetVelocityWorld)
	ON_BN_CLICKED(IDC_CHECK2, &Nalmak3D_ControlView::OnBnClickedIsPlayOnAwake)
	ON_BN_CLICKED(IDC_BUTTON8, &Nalmak3D_ControlView::OnBnClickedAddBurst)
	ON_BN_CLICKED(IDC_BUTTON9, &Nalmak3D_ControlView::OnBnClickedDeleteBurst)
	ON_BN_CLICKED(IDC_BUTTON11, &Nalmak3D_ControlView::OnBnClickedButtonSave)
	ON_BN_CLICKED(IDC_BUTTON12, &Nalmak3D_ControlView::OnBnClickedButtonLoad)
	ON_EN_CHANGE(IDC_EDIT46, &Nalmak3D_ControlView::OnEnChangeMinAngularVelocity)
	ON_EN_CHANGE(IDC_EDIT47, &Nalmak3D_ControlView::OnEnChangeMaxAngularVelocity)
	ON_EN_CHANGE(IDC_EDIT48, &Nalmak3D_ControlView::OnEnChangeStretchedScale)
	ON_EN_CHANGE(IDC_EDIT49, &Nalmak3D_ControlView::OnEnChangeAnimationTileX)
	ON_EN_CHANGE(IDC_EDIT50, &Nalmak3D_ControlView::OnEnChangeAnimationTileY)
	ON_BN_CLICKED(IDC_RADIO9, &Nalmak3D_ControlView::OnBnClickedRadioBillboardNone)
	ON_BN_CLICKED(IDC_RADIO10, &Nalmak3D_ControlView::OnBnClickedRadioBillboard)
	ON_BN_CLICKED(IDC_RADIO11, &Nalmak3D_ControlView::OnBnClickedRadioBillboardHorizontal)
	ON_BN_CLICKED(IDC_RADIO12, &Nalmak3D_ControlView::OnBnClickedRadioBillboardVertical)
	ON_BN_CLICKED(IDC_RADIO13, &Nalmak3D_ControlView::OnBnClickedRadioBillboardStertched)
END_MESSAGE_MAP()


// Nalmak3D_ControlView �����Դϴ�.

#ifdef _DEBUG
void Nalmak3D_ControlView::AssertValid() const
{
	CFormView::AssertValid();
}

#ifndef _WIN32_WCE
void Nalmak3D_ControlView::Dump(CDumpContext& dc) const
{
	CFormView::Dump(dc);
}
#endif
#endif //_DEBUG


// Nalmak3D_ControlView �޽��� ó�����Դϴ�.

void Nalmak3D_ControlView::OnLbnSelchangeObjectList()
{
	int  currentIndex = m_objectListBox.GetCurSel();
	//m_objectListBox.SetCurSel(currentIndex);
	m_currentSelectObject = ParticleObjectManager::GetInstance()->GetParticleObject(currentIndex);


	PARTICLE_EMIT_SHAPE shape = m_currentSelectObject->GetComponent<ParticleRenderer>()->m_info.shape;

	m_sphereShape.SetCheck(false);
	m_coneShape.SetCheck(false);
	m_boxShape.SetCheck(false);
	m_circleShape.SetCheck(false);
	switch (shape)
	{
	case PARTICLE_EMIT_SHAPE_SPHERE:
		m_sphereShape.SetCheck(true);
		break;
	case PARTICLE_EMIT_SHAPE_CIRCLE:
		m_circleShape.SetCheck(true);
		break;
	case PARTICLE_EMIT_SHAPE_BOX:
		m_boxShape.SetCheck(true);
		break;
	case PARTICLE_EMIT_SHAPE_CONE:
		m_coneShape.SetCheck(true);
		break;
	default:
		break;
	}

	PARTICLE_BILLBOARD_TYPE billboard = m_currentSelectObject->GetComponent<ParticleRenderer>()->m_info.billboard;

	m_billboardDefault.SetCheck(false);
	m_billboardHorizontal.SetCheck(false);
	m_billboardNone.SetCheck(false);
	m_billboardStertched.SetCheck(false);
	m_billboardVertical.SetCheck(false);

	switch (billboard)
	{
	case PARTICLE_BILLBOARD_TYPE_NONE:
		m_billboardNone.SetCheck(true);
		break;
	case PARTICLE_BILLBOARD_TYPE_DEFAULT:
		m_billboardDefault.SetCheck(true);
		break;
	case PARTICLE_BILLBOARD_TYPE_HORIZONTAL:
		m_billboardHorizontal.SetCheck(true);
		break;
	case PARTICLE_BILLBOARD_TYPE_VERTICAL:
		m_billboardVertical.SetCheck(true);
		break;
	case PARTICLE_BILLBOARD_TYPE_STERTCHED:
		m_billboardStertched.SetCheck(true);
		break;
	default:
		break;
	}


	Material* mtrl = m_currentSelectObject->GetComponent<ParticleRenderer>()->GetMaterial();
	if (mtrl)
	{
		CString str;
		str = mtrl->GetName().c_str();
		m_materialName.SetWindowTextW(str);
	}

	ParticleObjectManager::GetInstance()->OffActiveParticles();
	ParticleObjectManager::GetInstance()->OnActiveParticle(m_currentSelectObject);

	m_burstList.ResetContent();
	for (auto& burst : m_currentSelectObject->GetComponent<ParticleRenderer>()->GetBurstList())
	{
		CString burstStr;
		CString finalStr;
		burstStr.Format(_T("%f"), burst.time);
		finalStr += L"Time : ";
		finalStr += burstStr;
		finalStr += L" / ";
		finalStr += L"Burst Count: ";
		burstStr.Format(_T("%d"), burst.count);
		finalStr += burstStr;

		m_burstList.AddString(finalStr);
	}


	UpdateData();
}


void Nalmak3D_ControlView::OnBnClickedCreateParticle()
{
	// TODO: ���⿡ ��Ʈ�� �˸� ó���� �ڵ带 �߰��մϴ�.
	auto obj = INSTANTIATE(0,L"particle")->AddComponent<ParticleRenderer>();
	ParticleObjectManager::GetInstance()->AddObject(obj);
	m_objectListBox.AddString(L"particle");
	m_objectListBox.SetCurSel((int)(ParticleObjectManager::GetInstance()->GetAllObjects().size() - 1));
	m_currentSelectObject = obj;
	Material* mtrl = obj->GetComponent<ParticleRenderer>()->GetMaterial();
	if (mtrl)
	{
		CString str;
		str = mtrl->GetName().c_str();
		m_materialName.SetWindowTextW(str);
	}
	else
	{
		m_materialName.SetWindowTextW(L"particleAdd_billboard");
	}

	MFC_Utility::SetEditBoxFloat(&m_burstTime, 0);
	MFC_Utility::SetEditBoxInt(&m_burstCount, 0);

	OnLbnSelchangeObjectList();
}


void Nalmak3D_ControlView::OnBnClickedDeleteParticle()
{
	// TODO: ���⿡ ��Ʈ�� �˸� ó���� �ڵ带 �߰��մϴ�.

	int  currentIndex = m_objectListBox.GetCurSel();
	ParticleObjectManager::GetInstance()->DeleteObject(currentIndex);
	m_objectListBox.DeleteString(currentIndex);
	m_objectListBox.SetCurSel(currentIndex - 1);
	m_currentSelectObject = ParticleObjectManager::GetInstance()->GetParticleObject(currentIndex - 1);
	UpdateData();
}

void Nalmak3D_ControlView::UpdateCurrentObject()
{
	int  currentIndex = m_objectListBox.GetCurSel();
	m_currentSelectObject = ParticleObjectManager::GetInstance()->GetParticleObject(currentIndex);
}

void Nalmak3D_ControlView::UpdateData()
{
	if (!m_currentSelectObject)
		return;

	CString str = m_currentSelectObject->GetName().c_str();
	m_particleName.SetWindowTextW(str);

	ParticleRenderer* particle = m_currentSelectObject->GetComponent<ParticleRenderer>();

	MFC_Utility::SetEditBoxFloat(&m_posX, particle->m_info.posOffset.x);
	MFC_Utility::SetEditBoxFloat(&m_posY, particle->m_info.posOffset.y);
	MFC_Utility::SetEditBoxFloat(&m_posZ, particle->m_info.posOffset.z);

	Quaternion quaternion = particle->m_info.rotOffset;
	Vector3 rot = Nalmak_Math::QuaternionToEuler(quaternion);
	MFC_Utility::SetEditBoxFloat(&m_rotX, rot.x);
	MFC_Utility::SetEditBoxFloat(&m_rotY, rot.y);
	MFC_Utility::SetEditBoxFloat(&m_rotZ, rot.z);

	MFC_Utility::SetEditBoxFloat(&m_minRadius, particle->m_info.minRadius);
	MFC_Utility::SetEditBoxFloat(&m_maxRadius, particle->m_info.maxRadius);
	MFC_Utility::SetEditBoxFloat(&m_coneAngle, particle->m_info.coneAngle * Rad2Deg);
	MFC_Utility::SetEditBoxFloat(&m_width, particle->m_info.width);
	MFC_Utility::SetEditBoxFloat(&m_height, particle->m_info.height);
	MFC_Utility::SetEditBoxFloat(&m_depth, particle->m_info.depth);

	MFC_Utility::SetEditBoxInt(&m_maxCount, particle->m_info.maxParticleCount);



	MFC_Utility::SetEditBoxFloat(&m_minAwakeTime, particle->m_info.minAwakeTime);
	MFC_Utility::SetEditBoxFloat(&m_maxAwakeTime, particle->m_info.maxAwakeTime);
	MFC_Utility::SetEditBoxFloat(&m_duration, particle->m_info.duration);
	MFC_Utility::SetEditBoxInt(&m_emitCount, particle->m_info.emittorCount);
	//MFC_Utility::SetEditBoxFloat(&m_depth, particle->m_info.depth);
	m_isLoop.SetCheck(particle->m_info.isLoop);

	m_world.SetCheck(!particle->m_info.isLocal);
	m_local.SetCheck(particle->m_info.isLocal);

	m_velocityWorld.SetCheck(!particle->m_info.isVelocityLocal);
	m_velocityLocal.SetCheck(particle->m_info.isVelocityLocal);

	MFC_Utility::SetEditBoxFloat(&m_minStartScale, particle->m_info.startMinScale);
	MFC_Utility::SetEditBoxFloat(&m_minEndScale, particle->m_info.endMinScale);
	MFC_Utility::SetEditBoxFloat(&m_maxStartScale, particle->m_info.startMaxScale);
	MFC_Utility::SetEditBoxFloat(&m_maxEndScale, particle->m_info.endMaxScale);

	MFC_Utility::SetEditBoxFloat(&m_minStartSpeed, particle->m_info.startMinSpeed);
	MFC_Utility::SetEditBoxFloat(&m_minEndSpeed, particle->m_info.endMinSpeed);
	MFC_Utility::SetEditBoxFloat(&m_maxStartSpeed, particle->m_info.startMaxSpeed);
	MFC_Utility::SetEditBoxFloat(&m_maxEndSpeed, particle->m_info.endMaxSpeed);

	MFC_Utility::SetEditBoxFloat(&m_minLifeTime, particle->m_info.minLifeTime);
	MFC_Utility::SetEditBoxFloat(&m_maxLifeTime, particle->m_info.maxLifeTime);

	MFC_Utility::SetEditBoxFloat(&m_minRotation, Rad2Deg * particle->m_info.minAngle);
	MFC_Utility::SetEditBoxFloat(&m_maxRotation, Rad2Deg * particle->m_info.maxAngle);

	MFC_Utility::SetEditBoxFloat(&m_minAngularVelocity, Rad2Deg * particle->m_info.minAngularVelocity);
	MFC_Utility::SetEditBoxFloat(&m_maxAngularVelocity, Rad2Deg * particle->m_info.maxAngularVelocity);

	MFC_Utility::SetEditBoxFloat(&m_velocityX, particle->m_info.force.x);
	MFC_Utility::SetEditBoxFloat(&m_velocityY, particle->m_info.force.y);
	MFC_Utility::SetEditBoxFloat(&m_velocityZ, particle->m_info.force.z);
	MFC_Utility::SetEditBoxFloat(&m_gravity, particle->m_info.gravity);

	MFC_Utility::SetEditBoxFloat(&m_stretchedScale, particle->m_info.stretchedScale);

	MFC_Utility::SetEditBoxInt(&m_animationTileX, particle->m_info.animationTileX);
	MFC_Utility::SetEditBoxInt(&m_animationTileY, particle->m_info.animationTileY);


	COLORREF color = COLOR3_TO_RGB(particle->m_info.startMinColor.x, particle->m_info.startMinColor.y, particle->m_info.startMinColor.z);
	m_minStartColor.SetColor(color);

	color = COLOR3_TO_RGB(particle->m_info.startMaxColor.x, particle->m_info.startMaxColor.y, particle->m_info.startMaxColor.z);
	m_maxStartColor.SetColor(color);

	color = COLOR3_TO_RGB(particle->m_info.endMinColor.x, particle->m_info.endMinColor.y, particle->m_info.endMinColor.z);
	m_minEndColor.SetColor(color);

	color = COLOR3_TO_RGB(particle->m_info.endMaxColor.x, particle->m_info.endMaxColor.y, particle->m_info.endMaxColor.z);
	m_maxEndColor.SetColor(color);

	particle->m_info.startMinColor.w = Nalmak_Math::Clamp(particle->m_info.startMinColor.w, 0.f, 1.f);
	particle->m_info.startMaxColor.w = Nalmak_Math::Clamp(particle->m_info.startMaxColor.w, 0.f, 1.f);
	particle->m_info.endMinColor.w = Nalmak_Math::Clamp(particle->m_info.endMinColor.w, 0.f, 1.f);
	particle->m_info.endMaxColor.w = Nalmak_Math::Clamp(particle->m_info.endMaxColor.w, 0.f, 1.f);

	MFC_Utility::SetEditBoxFloat(&m_minstartAlpha, particle->m_info.startMinColor.w);
	MFC_Utility::SetEditBoxFloat(&m_maxStartAlpha, particle->m_info.startMaxColor.w);
	MFC_Utility::SetEditBoxFloat(&m_minEndAlpha, particle->m_info.endMinColor.w);
	MFC_Utility::SetEditBoxFloat(&m_maxEndAlpha, particle->m_info.endMaxColor.w);

	m_isPlayOnAwake.SetCheck(particle->m_info.isPlayOnAwake);



}



void Nalmak3D_ControlView::OnEnChangePositionX()
{
	if (!m_currentSelectObject)
		return;

	CString value;
	GetDlgItem(IDC_EDIT1)->GetWindowTextW(value);
	m_currentSelectObject->GetComponent<ParticleRenderer>()->m_info.posOffset.x = (float)_tstof(value);


}


void Nalmak3D_ControlView::OnEnChangePositionY()
{
	if (!m_currentSelectObject)
		return;


	CString value;
	GetDlgItem(IDC_EDIT2)->GetWindowTextW(value);
	m_currentSelectObject->GetComponent<ParticleRenderer>()->m_info.posOffset.y = (float)_tstof(value);

}


void Nalmak3D_ControlView::OnEnChangePositionZ()
{
	if (!m_currentSelectObject)
		return;


	CString value;
	GetDlgItem(IDC_EDIT3)->GetWindowTextW(value);
	m_currentSelectObject->GetComponent<ParticleRenderer>()->m_info.posOffset.z = (float)_tstof(value);

}


void Nalmak3D_ControlView::OnEnChangeRotationX()
{
	if (!m_currentSelectObject)
		return;

	CString valueX;
	GetDlgItem(IDC_EDIT4)->GetWindowTextW(valueX);
	CString valueY;
	GetDlgItem(IDC_EDIT5)->GetWindowTextW(valueY);
	CString valueZ;
	GetDlgItem(IDC_EDIT6)->GetWindowTextW(valueZ);
	Quaternion rot;
	D3DXQuaternionRotationYawPitchRoll(&rot,(float)_tstof(valueY) * Deg2Rad, (float)_tstof(valueX) * Deg2Rad, (float)_tstof(valueZ) * Deg2Rad);
	m_currentSelectObject->GetComponent<ParticleRenderer>()->m_info.rotOffset = rot;
}


void Nalmak3D_ControlView::OnEnChangeRotationY()
{
	UpdateCurrentObject();

	if (!m_currentSelectObject)
		return;


	CString valueX;
	GetDlgItem(IDC_EDIT4)->GetWindowTextW(valueX);
	CString valueY;
	GetDlgItem(IDC_EDIT5)->GetWindowTextW(valueY);
	CString valueZ;
	GetDlgItem(IDC_EDIT6)->GetWindowTextW(valueZ);
	Quaternion rot;
	D3DXQuaternionRotationYawPitchRoll(&rot, (float)_tstof(valueY) * Deg2Rad, (float)_tstof(valueX) * Deg2Rad, (float)_tstof(valueZ) * Deg2Rad);
	m_currentSelectObject->GetComponent<ParticleRenderer>()->m_info.rotOffset = rot;

}


void Nalmak3D_ControlView::OnEnChangeRotationZ()
{
	if (!m_currentSelectObject)
		return;


	CString valueX;
	GetDlgItem(IDC_EDIT4)->GetWindowTextW(valueX);
	CString valueY;
	GetDlgItem(IDC_EDIT5)->GetWindowTextW(valueY);
	CString valueZ;
	GetDlgItem(IDC_EDIT6)->GetWindowTextW(valueZ);
	Quaternion rot;
	D3DXQuaternionRotationYawPitchRoll(&rot, (float)_tstof(valueY) * Deg2Rad, (float)_tstof(valueX) * Deg2Rad, (float)_tstof(valueZ) * Deg2Rad);
	m_currentSelectObject->GetComponent<ParticleRenderer>()->m_info.rotOffset = rot;

}



void Nalmak3D_ControlView::OnEnChangeParticleName()
{
	if (!m_currentSelectObject)
		return;

//
}


void Nalmak3D_ControlView::OnBnClickedNameChange()
{
	CString name;
	m_particleName.GetWindowTextW(name);

	m_currentSelectObject->SetName(name.GetString());
	int  currentIndex = m_objectListBox.GetCurSel();
	m_objectListBox.DeleteString(currentIndex);
	m_objectListBox.InsertString(currentIndex, name);
}



void Nalmak3D_ControlView::OnInitialUpdate()
{
	CFormView::OnInitialUpdate();

	for (auto& mtrl : ResourceManager::GetInstance()->GetAllResource<Material>())
	{
		if (((Material*)(mtrl.second))->GetShader()->GetInputLayout() == VERTEX_INPUT_LAYOUT_PARTICLE)
		{
			CString str = mtrl.second->GetName().c_str();
			m_materialList.AddString(str);
		}
	}
}


void Nalmak3D_ControlView::OnBnClickedSelectMaterial()
{
	int curIndex = m_materialList.GetCurSel();
	if (curIndex == -1)
		return;
	if (!m_currentSelectObject)
		return;
	CString mtrlName;
	m_materialList.GetText(curIndex, mtrlName);
	m_currentSelectObject->GetComponent<ParticleRenderer>()->SetMaterial(mtrlName.GetString());

	Material* mtrl = m_currentSelectObject->GetComponent<ParticleRenderer>()->GetMaterial();
	if (mtrl)
	{
		CString str;
		str = mtrl->GetName().c_str();
		m_materialName.SetWindowTextW(str);
	}
}



void Nalmak3D_ControlView::OnBnClickedSphereShape()
{
	if (!m_currentSelectObject)
		return;
	m_minRadius.EnableWindow(true);
	m_maxRadius.EnableWindow(true);
	m_coneAngle.EnableWindow(false);
	m_width.EnableWindow(false);
	m_height.EnableWindow(false);
	m_depth.EnableWindow(false);

	m_currentSelectObject->GetComponent<ParticleRenderer>()->m_info.shape = PARTICLE_EMIT_SHAPE_SPHERE;

}


void Nalmak3D_ControlView::OnBnClickedCircleShape()
{
	if (!m_currentSelectObject)
		return;
	m_minRadius.EnableWindow(true);
	m_maxRadius.EnableWindow(true);
	m_coneAngle.EnableWindow(false);
	m_width.EnableWindow(false);
	m_height.EnableWindow(false);
	m_depth.EnableWindow(false);

	m_currentSelectObject->GetComponent<ParticleRenderer>()->m_info.shape = PARTICLE_EMIT_SHAPE_CIRCLE;
}


void Nalmak3D_ControlView::OnBnClickedBoxShape()
{
	if (!m_currentSelectObject)
		return;
	m_minRadius.EnableWindow(false);
	m_maxRadius.EnableWindow(false);
	m_coneAngle.EnableWindow(false);
	m_width.EnableWindow(true);
	m_height.EnableWindow(true);
	m_depth.EnableWindow(true);

	m_currentSelectObject->GetComponent<ParticleRenderer>()->m_info.shape = PARTICLE_EMIT_SHAPE_BOX;
}


void Nalmak3D_ControlView::OnBnClickedConeShape()
{
	if (!m_currentSelectObject)
		return;
	m_minRadius.EnableWindow(true);
	m_maxRadius.EnableWindow(true);
	m_coneAngle.EnableWindow(true);
	m_width.EnableWindow(false);
	m_height.EnableWindow(false);
	m_depth.EnableWindow(false);

	m_currentSelectObject->GetComponent<ParticleRenderer>()->m_info.shape = PARTICLE_EMIT_SHAPE_CONE;
}




void Nalmak3D_ControlView::OnEnChangeMinRadius()
{
	if (!m_currentSelectObject)
		return;
	CString value;
	GetDlgItem(IDC_EDIT18)->GetWindowTextW(value);
	m_currentSelectObject->GetComponent<ParticleRenderer>()->m_info.minRadius = (float)_tstof(value);
}


void Nalmak3D_ControlView::OnEnChangeMaxRadius()
{
	if (!m_currentSelectObject)
		return;
	CString value;
	GetDlgItem(IDC_EDIT19)->GetWindowTextW(value);
	m_currentSelectObject->GetComponent<ParticleRenderer>()->m_info.maxRadius = (float)_tstof(value);
}


void Nalmak3D_ControlView::OnEnChangeAngle()
{
	if (!m_currentSelectObject)
		return;
	CString value;
	GetDlgItem(IDC_EDIT23)->GetWindowTextW(value);
	m_currentSelectObject->GetComponent<ParticleRenderer>()->m_info.coneAngle = (float)_tstof(value) * Deg2Rad;
}


void Nalmak3D_ControlView::OnEnChangeBoxWidth()
{
	if (!m_currentSelectObject)
		return;
	CString value;
	GetDlgItem(IDC_EDIT20)->GetWindowTextW(value);
	m_currentSelectObject->GetComponent<ParticleRenderer>()->m_info.width = (float)_tstof(value);
}


void Nalmak3D_ControlView::OnEnChangeBoxHeight()
{
	if (!m_currentSelectObject)
		return;
	CString value;
	GetDlgItem(IDC_EDIT21)->GetWindowTextW(value);
	m_currentSelectObject->GetComponent<ParticleRenderer>()->m_info.height = (float)_tstof(value);
}


void Nalmak3D_ControlView::OnEnChangeBoxDepth()
{
	if (!m_currentSelectObject)
		return;
	CString value;
	GetDlgItem(IDC_EDIT22)->GetWindowTextW(value);
	m_currentSelectObject->GetComponent<ParticleRenderer>()->m_info.depth = (float)_tstof(value);
}


void Nalmak3D_ControlView::OnEnChangeEmitCount()
{
	if (!m_currentSelectObject)
		return;
	CString value;
	GetDlgItem(IDC_EDIT26)->GetWindowTextW(value);
	m_currentSelectObject->GetComponent<ParticleRenderer>()->SetEmitCount((int)_tstoi(value));
}


void Nalmak3D_ControlView::OnBnClickedIsLoop()
{
	if (!m_currentSelectObject)
		return;
	m_currentSelectObject->GetComponent<ParticleRenderer>()->m_info.isLoop ^= true;
	m_isLoop.SetCheck(m_currentSelectObject->GetComponent<ParticleRenderer>()->m_info.isLoop);
}


void Nalmak3D_ControlView::OnEnChangeDuration()
{
	if (!m_currentSelectObject)
		return;
	CString value;
	GetDlgItem(IDC_EDIT16)->GetWindowTextW(value);
	m_currentSelectObject->GetComponent<ParticleRenderer>()->m_info.duration = (float)_tstof(value);
}


void Nalmak3D_ControlView::OnEnChangeMinAwakeTime()
{
	if (!m_currentSelectObject)
		return;
	CString value;
	GetDlgItem(IDC_EDIT25)->GetWindowTextW(value);
	m_currentSelectObject->GetComponent<ParticleRenderer>()->m_info.minAwakeTime = (float)_tstof(value);
}


void Nalmak3D_ControlView::OnEnChangeMaxAwakeTime()
{
	if (!m_currentSelectObject)
		return;
	CString value;
	GetDlgItem(IDC_EDIT17)->GetWindowTextW(value);
	m_currentSelectObject->GetComponent<ParticleRenderer>()->m_info.maxAwakeTime = (float)_tstof(value);
}


void Nalmak3D_ControlView::OnEnChangeMaxCount()
{
	if (!m_currentSelectObject)
		return;
	CString value;
	GetDlgItem(IDC_EDIT9)->GetWindowTextW(value);
	m_currentSelectObject->GetComponent<ParticleRenderer>()->UpdateParticleInfo(_tstoi(value));
}



void Nalmak3D_ControlView::OnEnChangeMinLifeTime()
{
	if (!m_currentSelectObject)
		return;
	CString value;
	GetDlgItem(IDC_EDIT36)->GetWindowTextW(value);
	m_currentSelectObject->GetComponent<ParticleRenderer>()->m_info.minLifeTime = (float)_tstof(value);
}


void Nalmak3D_ControlView::OnEnChangeMaxLifeTime()
{
	if (!m_currentSelectObject)
		return;
	CString value;
	GetDlgItem(IDC_EDIT37)->GetWindowTextW(value);
	m_currentSelectObject->GetComponent<ParticleRenderer>()->m_info.maxLifeTime = (float)_tstof(value);
}


void Nalmak3D_ControlView::OnEnChangeMinStartScale()
{
	if (!m_currentSelectObject)
		return;
	CString value;
	GetDlgItem(IDC_EDIT40)->GetWindowTextW(value);
	m_currentSelectObject->GetComponent<ParticleRenderer>()->m_info.startMinScale = (float)_tstof(value);
}


void Nalmak3D_ControlView::OnEnChangeMaxStartScale()
{
	if (!m_currentSelectObject)
		return;
	CString value;
	GetDlgItem(IDC_EDIT41)->GetWindowTextW(value);
	m_currentSelectObject->GetComponent<ParticleRenderer>()->m_info.startMaxScale = (float)_tstof(value);
}




void Nalmak3D_ControlView::OnEnChangeMinEndScale()
{
	if (!m_currentSelectObject)
		return;
	CString value;
	GetDlgItem(IDC_EDIT42)->GetWindowTextW(value);
	m_currentSelectObject->GetComponent<ParticleRenderer>()->m_info.endMinScale = (float)_tstof(value);
}


void Nalmak3D_ControlView::OnEnChangeMaxEndScale()
{
	if (!m_currentSelectObject)
		return;
	CString value;
	GetDlgItem(IDC_EDIT43)->GetWindowTextW(value);
	m_currentSelectObject->GetComponent<ParticleRenderer>()->m_info.endMaxScale = (float)_tstof(value);
}


void Nalmak3D_ControlView::OnEnChangeMinStartSpeed()
{
	if (!m_currentSelectObject)
		return;
	CString value;
	GetDlgItem(IDC_EDIT10)->GetWindowTextW(value);
	m_currentSelectObject->GetComponent<ParticleRenderer>()->m_info.startMinSpeed = (float)_tstof(value);
}


void Nalmak3D_ControlView::OnEnChangeMaxStartSpeed()
{
	if (!m_currentSelectObject)
		return;
	CString value;
	GetDlgItem(IDC_EDIT11)->GetWindowTextW(value);
	m_currentSelectObject->GetComponent<ParticleRenderer>()->m_info.startMaxSpeed = (float)_tstof(value);
}


void Nalmak3D_ControlView::OnEnChangeMinEndSpeed()
{
	if (!m_currentSelectObject)
		return;
	CString value;
	GetDlgItem(IDC_EDIT12)->GetWindowTextW(value);
	m_currentSelectObject->GetComponent<ParticleRenderer>()->m_info.endMinSpeed = (float)_tstof(value);
}


void Nalmak3D_ControlView::OnEnChangeMaxEndSpeed()
{
	if (!m_currentSelectObject)
		return;
	CString value;
	GetDlgItem(IDC_EDIT13)->GetWindowTextW(value);
	m_currentSelectObject->GetComponent<ParticleRenderer>()->m_info.endMaxSpeed = (float)_tstof(value);
}


void Nalmak3D_ControlView::OnEnChangeMinRotation()
{
	if (!m_currentSelectObject)
		return;
	CString value;
	GetDlgItem(IDC_EDIT14)->GetWindowTextW(value);
	m_currentSelectObject->GetComponent<ParticleRenderer>()->m_info.minAngle = Deg2Rad * (float)_tstof(value);
}


void Nalmak3D_ControlView::OnEnChangeMaxRotation()
{
	if (!m_currentSelectObject)
		return;
	CString value;
	GetDlgItem(IDC_EDIT15)->GetWindowTextW(value);
	m_currentSelectObject->GetComponent<ParticleRenderer>()->m_info.maxAngle = Deg2Rad * (float)_tstof(value);
}


void Nalmak3D_ControlView::OnBnClickedUpdateMaterial()
{
	ResourceManager::GetInstance()->UpdateMaterial(L"../Resource",true);

	m_materialList.ResetContent();

	for (auto& mtrl : ResourceManager::GetInstance()->GetAllResource<Material>())
	{
		if (((Material*)(mtrl.second))->GetShader()->GetInputLayout() == VERTEX_INPUT_LAYOUT_PARTICLE)
		{
			CString str = mtrl.second->GetName().c_str();
			m_materialList.AddString(str);
		}
	}

	if (!m_currentSelectObject)
		return;
	Material* mtrl = m_currentSelectObject->GetComponent<ParticleRenderer>()->GetMaterial();
	if (mtrl)
	{
		CString str;
		str = mtrl->GetName().c_str();
		m_materialName.SetWindowTextW(str);
	}
}




void Nalmak3D_ControlView::OnBnClickedMinStartColor()
{
	COLORREF color = m_minStartColor.GetColor();

	ParticleRenderer* particle = m_currentSelectObject->GetComponent<ParticleRenderer>();
	particle->m_info.startMinColor = Vector4(GetRValue(color) / 255.f, GetGValue(color) / 255.f, GetBValue(color) / 255.f, particle->m_info.startMinColor.w);
}


void Nalmak3D_ControlView::OnBnClickedMaxStartColor()
{
	COLORREF color = m_maxStartColor.GetColor();

	ParticleRenderer* particle = m_currentSelectObject->GetComponent<ParticleRenderer>();
	particle->m_info.startMaxColor = Vector4(GetRValue(color) / 255.f, GetGValue(color) / 255.f, GetBValue(color) / 255.f, particle->m_info.startMaxColor.w);
}


void Nalmak3D_ControlView::OnBnClickedMfcMinEndColor()
{
	COLORREF color = m_minEndColor.GetColor();

	ParticleRenderer* particle = m_currentSelectObject->GetComponent<ParticleRenderer>();
	particle->m_info.endMinColor = Vector4(GetRValue(color) / 255.f, GetGValue(color) / 255.f, GetBValue(color) / 255.f, particle->m_info.endMinColor.w);
}


void Nalmak3D_ControlView::OnBnClickedMfcMaxEndColor()
{
	COLORREF color = m_maxEndColor.GetColor();

	ParticleRenderer* particle = m_currentSelectObject->GetComponent<ParticleRenderer>();
	particle->m_info.endMaxColor = Vector4(GetRValue(color)/255.f, GetGValue(color) / 255.f, GetBValue(color) / 255.f, particle->m_info.endMaxColor.w);
}


void Nalmak3D_ControlView::OnEnChangeMinStartAlpha()
{
	if (!m_currentSelectObject)
		return;
	CString value;
	GetDlgItem(IDC_EDIT38)->GetWindowTextW(value);
	m_currentSelectObject->GetComponent<ParticleRenderer>()->m_info.startMinColor.w = (float)_tstof(value);
}


void Nalmak3D_ControlView::OnEnChangeEditMaxStartAlpha()
{
	if (!m_currentSelectObject)
		return;
	CString value;
	GetDlgItem(IDC_EDIT39)->GetWindowTextW(value);
	m_currentSelectObject->GetComponent<ParticleRenderer>()->m_info.startMaxColor.w = (float)_tstof(value);
}


void Nalmak3D_ControlView::OnEnChangeEditMinEndAlpha()
{
	if (!m_currentSelectObject)
		return;
	CString value;
	GetDlgItem(IDC_EDIT44)->GetWindowTextW(value);
	m_currentSelectObject->GetComponent<ParticleRenderer>()->m_info.endMinColor.w = (float)_tstof(value);
}


void Nalmak3D_ControlView::OnEnChangeEditMaxEndAlpha()
{
	if (!m_currentSelectObject)
		return;
	CString value;
	GetDlgItem(IDC_EDIT45)->GetWindowTextW(value);
	m_currentSelectObject->GetComponent<ParticleRenderer>()->m_info.endMaxColor.w = (float)_tstof(value);
}


void Nalmak3D_ControlView::OnBnClickedPlay()
{
	ParticleObjectManager::GetInstance()->OffActiveParticles();
	ParticleObjectManager::GetInstance()->OnActiveParticle(m_currentSelectObject);
	// TODO: ���⿡ ��Ʈ�� �˸� ó���� �ڵ带 �߰��մϴ�.
}


void Nalmak3D_ControlView::OnBnClickedPlayAll()
{
	ParticleObjectManager::GetInstance()->OnActiveParticles();

	// TODO: ���⿡ ��Ʈ�� �˸� ó���� �ڵ带 �߰��մϴ�.
}


void Nalmak3D_ControlView::OnBnClickedStop()
{
	ParticleObjectManager::GetInstance()->OffActiveParticles();
	// TODO: ���⿡ ��Ʈ�� �˸� ó���� �ڵ带 �߰��մϴ�.
}


void Nalmak3D_ControlView::OnBnClickedLocal()
{
	if (!m_currentSelectObject)
		return;
	m_local.SetCheck(true);
	m_currentSelectObject->GetComponent<ParticleRenderer>()->m_info.isLocal = true;
}


void Nalmak3D_ControlView::OnBnClickedWorld()
{
	if (!m_currentSelectObject)
		return;
	m_local.SetCheck(false);
	m_currentSelectObject->GetComponent<ParticleRenderer>()->m_info.isLocal = false;
}


void Nalmak3D_ControlView::OnEnChangeGravity()
{
	if (!m_currentSelectObject)
		return;
	CString value;
	GetDlgItem(IDC_EDIT24)->GetWindowTextW(value);
	m_currentSelectObject->GetComponent<ParticleRenderer>()->SetGravityScale((float)_tstof(value));
}


void Nalmak3D_ControlView::OnEnChangeVelocityX()
{
	if (!m_currentSelectObject)
		return;
	CString value;
	GetDlgItem(IDC_EDIT30)->GetWindowTextW(value);
	m_currentSelectObject->GetComponent<ParticleRenderer>()->m_info.force.x = (float)_tstof(value);
}


void Nalmak3D_ControlView::OnEnChangeVelocityY()
{
	if (!m_currentSelectObject)
		return;
	CString value;
	GetDlgItem(IDC_EDIT31)->GetWindowTextW(value);
	m_currentSelectObject->GetComponent<ParticleRenderer>()->m_info.force.y = (float)_tstof(value);
}


void Nalmak3D_ControlView::OnEnChangeVelocityZ()
{
	if (!m_currentSelectObject)
		return;
	CString value;
	GetDlgItem(IDC_EDIT32)->GetWindowTextW(value);
	m_currentSelectObject->GetComponent<ParticleRenderer>()->m_info.force.z = (float)_tstof(value);
}


void Nalmak3D_ControlView::OnBnClickedSetVelocityLocal()
{
	if (!m_currentSelectObject)
		return;

	m_currentSelectObject->GetComponent<ParticleRenderer>()->m_info.isVelocityLocal = true;
}


void Nalmak3D_ControlView::OnBnClickedSetVelocityWorld()
{
	if (!m_currentSelectObject)
		return;

	m_currentSelectObject->GetComponent<ParticleRenderer>()->m_info.isVelocityLocal = false;

}


void Nalmak3D_ControlView::OnBnClickedIsPlayOnAwake()
{
	if (!m_currentSelectObject)
		return;
	int check = m_isPlayOnAwake.GetCheck();
	if(check == 0)
		m_currentSelectObject->GetComponent<ParticleRenderer>()->m_info.isPlayOnAwake = false;
	else
		m_currentSelectObject->GetComponent<ParticleRenderer>()->m_info.isPlayOnAwake = true;

	// TODO: ���⿡ ��Ʈ�� �˸� ó���� �ڵ带 �߰��մϴ�.
}


void Nalmak3D_ControlView::OnBnClickedAddBurst()
{
	if (!m_currentSelectObject)
		return;
	ParticleRenderer::Burst burst;
	CString value;
	CString burstStr;
	GetDlgItem(IDC_EDIT27)->GetWindowTextW(value);
	burstStr = L"Time : " + value + L" / ";
	burst.time =	(float)_tstof(value);
	GetDlgItem(IDC_EDIT28)->GetWindowTextW(value);
	burstStr += L"Burst Count : " + value;
	burst.count = (int)_tstoi(value);

	m_burstList.AddString(burstStr);

	m_currentSelectObject->GetComponent<ParticleRenderer>()->AddBurst(burst);

	MFC_Utility::SetEditBoxFloat(&m_burstTime, 0);
	MFC_Utility::SetEditBoxInt(&m_burstCount, 0);

	// TODO: ���⿡ ��Ʈ�� �˸� ó���� �ڵ带 �߰��մϴ�.
}


void Nalmak3D_ControlView::OnBnClickedDeleteBurst()
{
	int index = m_burstList.GetCurSel();
	if (index < 0)
		return;

	if (!m_currentSelectObject)
		return;

	m_currentSelectObject->GetComponent<ParticleRenderer>()->DeleteBurst(index);
	m_burstList.DeleteString(index);


}


void Nalmak3D_ControlView::OnBnClickedButtonSave()
{

	CFileDialog dlg
	(
		FALSE,
		L"ptd",
		L"*.ptd",
		OFN_OVERWRITEPROMPT,
		L"Data File(*.ptd) | *.ptd||",
		this);

	TCHAR fp[256] = L"";
	GetCurrentDirectory(256, fp);
	PathRemoveFileSpec(fp);
	lstrcat(fp, L"\\Data\\Particle");
	dlg.m_ofn.lpstrInitialDir = fp;

	if (dlg.DoModal())
	{
		HANDLE handle = CreateFile(dlg.GetPathName(), GENERIC_WRITE, 0, nullptr, CREATE_ALWAYS, FILE_ATTRIBUTE_NORMAL, nullptr);
		if (INVALID_HANDLE_VALUE == handle)
		{
			AfxMessageBox(L"Save File Failed");
			return;
		}
		DWORD byte;

		ParticleRenderer* particle = m_currentSelectObject->GetComponent<ParticleRenderer>();

		WriteFile(handle, &particle->m_info, sizeof(ParticleData), &byte, nullptr);

		DWORD burstCount = (DWORD)particle->GetBurstList().size();

		WriteFile(handle, &burstCount, sizeof(DWORD), &byte, nullptr);
		for (DWORD i = 0; i < burstCount; ++i)
		{
			WriteFile(handle, &particle->GetBurstList()[i], sizeof(ParticleRenderer::Burst), &byte, nullptr);
		}

		wstring mtrlName = particle->GetMaterial()->GetName();
		DWORD materialNameLength = (DWORD)mtrlName.length();
		WriteFile(handle, &materialNameLength, sizeof(DWORD), &byte,nullptr);
		WriteFile(handle, mtrlName.c_str(), materialNameLength * sizeof(wchar_t), &byte, nullptr);




		CloseHandle(handle);

		afx_msg(L"Save File Succeed");
	}
}


void Nalmak3D_ControlView::OnBnClickedButtonLoad()
{
	CFileDialog dlg
	(
		TRUE,
		L"ptd",
		L"*.ptd",
		OFN_OVERWRITEPROMPT,
		L"Data File(*.ptd) | *.ptd||",
		this);

	TCHAR fp[256] = L"";
	GetCurrentDirectory(256, fp);
	PathRemoveFileSpec(fp);
	lstrcat(fp, L"\\Resource\\Particle");
	dlg.m_ofn.lpstrInitialDir = fp;

	if (dlg.DoModal())
	{
		

		wstring filePath = dlg.GetPathName();
		wstring fileName = filePath.substr(filePath.find_last_of(L'\\') + 1);
		size_t targetNum = fileName.find_last_of(L".");
		fileName = fileName.substr(0, targetNum);

		ParticleRenderer::Desc render;
		render.particleDataName = fileName;
		auto obj = INSTANTIATE()->AddComponent<ParticleRenderer>(&render);


		ParticleObjectManager::GetInstance()->AddObject(obj);
		m_objectListBox.AddString(L"particle");
		m_objectListBox.SetCurSel((int)(ParticleObjectManager::GetInstance()->GetAllObjects().size() - 1));
		m_currentSelectObject = obj;
		Material* mtrl = obj->GetComponent<ParticleRenderer>()->GetMaterial();



		if (mtrl)
		{
			CString str;
			str = mtrl->GetName().c_str();
			m_materialName.SetWindowTextW(str);
		}


		MFC_Utility::SetEditBoxFloat(&m_burstTime, 0);
		MFC_Utility::SetEditBoxInt(&m_burstCount, 0);


		OnLbnSelchangeObjectList();


		afx_msg(L"Load File Succeed");

	}
}


void Nalmak3D_ControlView::OnEnChangeMinAngularVelocity()
{
	if (!m_currentSelectObject)
		return;
	CString value;
	GetDlgItem(IDC_EDIT46)->GetWindowTextW(value);
	m_currentSelectObject->GetComponent<ParticleRenderer>()->m_info.minAngularVelocity = Deg2Rad * (float)_tstof(value);
}


void Nalmak3D_ControlView::OnEnChangeMaxAngularVelocity()
{
	if (!m_currentSelectObject)
		return;
	CString value;
	GetDlgItem(IDC_EDIT47)->GetWindowTextW(value);
	m_currentSelectObject->GetComponent<ParticleRenderer>()->m_info.maxAngularVelocity = Deg2Rad *(float)_tstof(value);

}



void Nalmak3D_ControlView::OnEnChangeStretchedScale()
{
	if (!m_currentSelectObject)
		return;
	CString value;
	GetDlgItem(IDC_EDIT48)->GetWindowTextW(value);
	auto particle = m_currentSelectObject->GetComponent<ParticleRenderer>();
	particle->m_info.stretchedScale = (float)_tstof(value);

	particle->UpdateParticleInfo(particle->m_info.maxParticleCount);
}




void Nalmak3D_ControlView::OnEnChangeAnimationTileX()
{
	if (!m_currentSelectObject)
		return;
	CString value;
	GetDlgItem(IDC_EDIT49)->GetWindowTextW(value);

	auto particle = m_currentSelectObject->GetComponent<ParticleRenderer>();
	
	particle->m_info.animationTileX = _tstoi(value);
	particle->UpdateParticleInfo(particle->m_info.maxParticleCount);
}


void Nalmak3D_ControlView::OnEnChangeAnimationTileY()
{
	if (!m_currentSelectObject)
		return;
	CString value;
	GetDlgItem(IDC_EDIT50)->GetWindowTextW(value);

	auto particle = m_currentSelectObject->GetComponent<ParticleRenderer>();

	particle->m_info.animationTileY = _tstoi(value);
	particle->UpdateParticleInfo(particle->m_info.maxParticleCount);

}


void Nalmak3D_ControlView::OnBnClickedRadioBillboardNone()
{
	if (!m_currentSelectObject)
		return;
	m_stretchedScale.EnableWindow(false);

	m_currentSelectObject->GetComponent<ParticleRenderer>()->m_info.billboard = PARTICLE_BILLBOARD_TYPE::PARTICLE_BILLBOARD_TYPE_NONE;
}


void Nalmak3D_ControlView::OnBnClickedRadioBillboard()
{
	if (!m_currentSelectObject)
		return;
	m_stretchedScale.EnableWindow(false);

	m_currentSelectObject->GetComponent<ParticleRenderer>()->m_info.billboard = PARTICLE_BILLBOARD_TYPE::PARTICLE_BILLBOARD_TYPE_DEFAULT;
}


void Nalmak3D_ControlView::OnBnClickedRadioBillboardHorizontal()
{
	if (!m_currentSelectObject)
		return;
	m_stretchedScale.EnableWindow(false);

	m_currentSelectObject->GetComponent<ParticleRenderer>()->m_info.billboard = PARTICLE_BILLBOARD_TYPE::PARTICLE_BILLBOARD_TYPE_HORIZONTAL;
}


void Nalmak3D_ControlView::OnBnClickedRadioBillboardVertical()
{
	if (!m_currentSelectObject)
		return;
	m_stretchedScale.EnableWindow(false);

	m_currentSelectObject->GetComponent<ParticleRenderer>()->m_info.billboard = PARTICLE_BILLBOARD_TYPE::PARTICLE_BILLBOARD_TYPE_VERTICAL;
}


void Nalmak3D_ControlView::OnBnClickedRadioBillboardStertched()
{
	if (!m_currentSelectObject)
		return;
	m_stretchedScale.EnableWindow(true);

	m_currentSelectObject->GetComponent<ParticleRenderer>()->m_info.billboard = PARTICLE_BILLBOARD_TYPE::PARTICLE_BILLBOARD_TYPE_STERTCHED;
}
