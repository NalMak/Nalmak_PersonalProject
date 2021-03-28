#pragma once
#include "afxwin.h"
#include "afxcolorbutton.h"



// Nalmak3D_ControlView 폼 뷰입니다.

class Nalmak3D_ControlView : public CFormView
{
	DECLARE_DYNCREATE(Nalmak3D_ControlView)

protected:
	Nalmak3D_ControlView();           // 동적 만들기에 사용되는 protected 생성자입니다.
	virtual ~Nalmak3D_ControlView();

public:
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_NALMAK3D_CONTROLVIEW };
#endif
#ifdef _DEBUG
	virtual void AssertValid() const;
#ifndef _WIN32_WCE
	virtual void Dump(CDumpContext& dc) const;
#endif
#endif

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 지원입니다.

	DECLARE_MESSAGE_MAP()
public:
	bool m_isDataChange = false;
	GameObject* m_currentSelectObject = nullptr;
	CListBox m_objectListBox;
	afx_msg void OnBnClickedCreateParticle();
	afx_msg void OnBnClickedDeleteParticle();
	void UpdateCurrentObject();
	void UpdateData();
	afx_msg void OnEnChangePositionX();
	afx_msg void OnEnChangePositionY();
	afx_msg void OnEnChangePositionZ();
	afx_msg void OnEnChangeRotationX();
	afx_msg void OnEnChangeRotationY();
	afx_msg void OnEnChangeRotationZ();
	CEdit m_posX;
	CEdit m_posY;
	CEdit m_posZ;
	CEdit m_rotX;
	CEdit m_rotY;
	CEdit m_rotZ;
	afx_msg void OnLbnSelchangeObjectList();
	CEdit m_particleName;
	afx_msg void OnEnChangeParticleName();
	afx_msg void OnBnClickedNameChange();
	CListBox m_materialList;
	virtual void OnInitialUpdate();
	afx_msg void OnBnClickedSelectMaterial();
	CEdit m_materialName;
	//afx_msg void OnBnClickedCircleShape();
	//afx_msg void OnBnClickedSphereShape();
	//afx_msg void OnBnClickedBoxShape();
	//afx_msg void OnBnClickedConeShape();


	CButton m_sphereShape;
	CButton m_circleShape;
	CButton m_boxShape;
	CButton m_coneShape;
	afx_msg void OnBnClickedSphereShape();
	afx_msg void OnBnClickedCircleShape();
	afx_msg void OnBnClickedBoxShape();
	afx_msg void OnBnClickedConeShape();
	afx_msg void OnEnChangeMinRadius();
	afx_msg void OnEnChangeMaxRadius();
	afx_msg void OnEnChangeAngle();
	afx_msg void OnEnChangeBoxWidth();
	afx_msg void OnEnChangeBoxHeight();
	afx_msg void OnEnChangeBoxDepth();
	CEdit m_minRadius;
	CEdit m_maxRadius;
	CEdit m_coneAngle;
	CEdit m_width;
	CEdit m_height;
	CEdit m_depth;
	afx_msg void OnEnChangeEmitCount();
	CEdit m_emitCount;
	afx_msg void OnBnClickedIsLoop();
	afx_msg void OnEnChangeDuration();
	CEdit m_duration;
	CEdit m_minAwakeTime;
	CEdit m_maxAwakeTime;
	afx_msg void OnEnChangeMinAwakeTime();
	afx_msg void OnEnChangeMaxAwakeTime();
	afx_msg void OnEnChangeMaxCount();
	CEdit m_maxCount;
	CButton m_isLoop;
	afx_msg void OnEnChangeMinLifeTime();
	afx_msg void OnEnChangeMaxLifeTime();
	afx_msg void OnEnChangeMinStartScale();
	afx_msg void OnEnChangeMaxStartScale();
	afx_msg void OnEnChangeMinEndScale();
	afx_msg void OnEnChangeMaxEndScale();
	afx_msg void OnEnChangeMinStartSpeed();
	afx_msg void OnEnChangeMaxStartSpeed();
	afx_msg void OnEnChangeMinEndSpeed();
	afx_msg void OnEnChangeMaxEndSpeed();
	afx_msg void OnEnChangeMinRotation();
	afx_msg void OnEnChangeMaxRotation();
	CEdit m_minLifeTime;
	CEdit m_maxLifeTime;
	CEdit m_minStartScale;
	CEdit m_maxStartScale;
	CEdit m_minEndScale;
	CEdit m_maxEndScale;
	CEdit m_minStartSpeed;
	CEdit m_maxStartSpeed;
	CEdit m_minEndSpeed;
	CEdit m_maxEndSpeed;
	CEdit m_minRotation;
	CEdit m_maxRotation;
	afx_msg void OnBnClickedUpdateMaterial();
	afx_msg void OnBnClickedMinStartColor();
	CMFCColorButton m_minStartColor;
	afx_msg void OnBnClickedMaxStartColor();
	CMFCColorButton m_maxStartColor;
	afx_msg void OnBnClickedMfcMinEndColor();
	afx_msg void OnBnClickedMfcMaxEndColor();
	CMFCColorButton m_minEndColor;
	CMFCColorButton m_maxEndColor;
	afx_msg void OnEnChangeMinStartAlpha();
	afx_msg void OnEnChangeEditMaxStartAlpha();
	afx_msg void OnEnChangeEditMinEndAlpha();
	afx_msg void OnEnChangeEditMaxEndAlpha();
	CEdit m_minstartAlpha;
	CEdit m_minEndAlpha;
	CEdit m_maxStartAlpha;
	CEdit m_maxEndAlpha;
	afx_msg void OnBnClickedPlay();
	afx_msg void OnBnClickedPlayAll();
	afx_msg void OnBnClickedStop();
	afx_msg void OnBnClickedLocal();
	afx_msg void OnBnClickedWorld();
	CButton m_local;
	CButton m_world;
	afx_msg void OnEnChangeGravity();
	CEdit m_gravity;
	afx_msg void OnEnChangeVelocityX();
	afx_msg void OnEnChangeVelocityY();
	afx_msg void OnEnChangeVelocityZ();
	afx_msg void OnBnClickedSetVelocityLocal();
	afx_msg void OnBnClickedSetVelocityWorld();
	CEdit m_velocityX;
	CEdit m_velocityY;
	CEdit m_velocityZ;
	CButton m_velocityLocal;
	CButton m_velocityWorld;
	CButton m_isPlayOnAwake;
	afx_msg void OnBnClickedIsPlayOnAwake();
	CListBox m_burstList;
	CEdit m_burstTime;
	CEdit m_burstCount;
	afx_msg void OnBnClickedAddBurst();
	afx_msg void OnBnClickedDeleteBurst();
	afx_msg void OnBnClickedButtonSave();
	afx_msg void OnBnClickedButtonLoad();
	afx_msg void OnEnChangeMinAngularVelocity();
	afx_msg void OnEnChangeMaxAngularVelocity();
	CEdit m_minAngularVelocity;
	CEdit m_maxAngularVelocity;
	afx_msg void OnBnClickedStretched();
	afx_msg void OnEnChangeStretchedScale();
	CEdit m_stretchedScale;
	CEdit m_animationTileX;
	CEdit m_animationTileY;
	afx_msg void OnEnChangeAnimationTileX();
	afx_msg void OnEnChangeAnimationTileY();
	CButton m_isAnimation;
	afx_msg void OnBnClickedRadioBillboardNone();
	afx_msg void OnBnClickedRadioBillboard();
	afx_msg void OnBnClickedRadioBillboardHorizontal();
	afx_msg void OnBnClickedRadioBillboardVertical();
	afx_msg void OnBnClickedRadioBillboardStertched();
	CButton m_billboardNone;
	CButton m_billboardDefault;
	CButton m_billboardHorizontal;
	CButton m_billboardVertical;
	CButton m_billboardStertched;
};


