#pragma once
#include "afxwin.h"



// Nalmak3D_MapControlView 폼 뷰입니다.

class Nalmak3D_MapControlView : public CFormView
{
	DECLARE_DYNCREATE(Nalmak3D_MapControlView)

protected:
	Nalmak3D_MapControlView();           // 동적 만들기에 사용되는 protected 생성자입니다.
	virtual ~Nalmak3D_MapControlView();

public:
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_NALMAK3D_MAPCONTROLVIEW };
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
	void UpdateObjectInfo(GameObject* newObj, int _index);
	void UpdateObjectTransformInfo(GameObject* _obj);
private:
	class MapToolManager* m_mapToolManager;
	bool m_isFocusRotation = false;
public:
	afx_msg void OnLbnSelchangeObjectList();
	CListBox m_objectList;
	CListBox m_materialList;
	CListBox m_meshList;
	afx_msg void OnBnClickedButtonCreateObject();
	afx_msg void OnBnClickedButtonDeleteObject();
	CEdit m_objectName;
	afx_msg void OnCbnSelchangeComboObjectTag();
	CComboBox m_objectTag;
	CEdit m_positionX;
	CEdit m_positionY;
	CEdit m_positionZ;
	CEdit m_rotationY;
	CEdit m_rotationX;
	CEdit m_rotationZ;
	CEdit m_scaleX;
	CEdit m_scaleY;
	CEdit m_scaleZ;
	afx_msg void OnBnClickedButtonSave();
	afx_msg void OnBnClickedButtonLoad();
	afx_msg void OnBnClickedButtonSaveAll();
	afx_msg void OnBnClickedButtonLoadAll();
	CEdit m_meshName;
	afx_msg void OnEnChangeEditObjectName();
	afx_msg void OnEnChangeEditPositionX();
	afx_msg void OnEnChangeEditPositionY();
	afx_msg void OnEnChangeEditPositionZ();
	afx_msg void OnEnChangeEditRotationX();
	afx_msg void OnEnChangeEditRotationY();
	afx_msg void OnEnChangeEditRotationZ();
	afx_msg void OnEnChangeEditScaleX();
	afx_msg void OnEnChangeEditScaleY();
	afx_msg void OnEnChangeEditScaleZ();
	afx_msg void OnEnChangeEditMaterialName();
	afx_msg void OnEnChangeEditMeshName();
	virtual void OnInitialUpdate();
	CEdit m_shaderName;
	//afx_msg void OnLbnDblclkListMaterial();
	afx_msg void OnLbnDblclkListMesh();
	CEdit m_subSetCount;
	CListBox m_materialRenderList;
	afx_msg void OnBnClickedButtonAddRenderMaterial();
	afx_msg void OnBnClickedButtonDeleteRenderMaterial();
	afx_msg void OnLbnSelchangeListMaterial();
	afx_msg void OnBnClickedButtonMaterialChange();
	afx_msg void OnLbnDblclkListMaterialList();
	CEdit m_renderMaterialCount;

	afx_msg void OnEnSetfocusRotX();
	afx_msg void OnEnKillfocusRotX();
	afx_msg void OnEnSetfocusRotY();
	afx_msg void OnEnKillfocusRotY();
	afx_msg void OnEnSetfocusRotZ();
	afx_msg void OnEnKillfocusEditRotZ();
};


