#pragma once
#include "afxwin.h"


// ObjectInstallTool 대화 상자입니다.

class ObjectInstallTool : public CDialogEx
{
	DECLARE_DYNAMIC(ObjectInstallTool)

public:
	ObjectInstallTool(CWnd* pParent = NULL);   // 표준 생성자입니다.
	virtual ~ObjectInstallTool();

// 대화 상자 데이터입니다.
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_DIALOG1 };
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
	CListBox m_objectList;
	CListBox m_meshList;
	CListBox m_materialList;
	CListBox m_materialRenderList;
	afx_msg void OnLbnSelchangeObjectList();
	afx_msg void OnBnClickedButtonCreateObject();
	afx_msg void OnBnClickedButtonDeleteObject();
	CEdit m_objectName;
	afx_msg void OnEnChangeEditObjectName();
	CComboBox m_objectTag;
	afx_msg void OnCbnSelchangeComboObjectTag();
	CEdit m_posX;
	CEdit m_posY;
	CEdit m_posZ;
	CEdit m_rotX;
	CEdit m_rotY;
	CEdit m_rotZ;
	CEdit m_scaleX;
	CEdit m_scaleY;
	CEdit m_scaleZ;
	afx_msg void OnEnChangeEditPositionX();
	afx_msg void OnEnChangeEditPositionY();
	afx_msg void OnEnChangeEditPositionZ();
	afx_msg void OnEnChangeEditRotationX();
	afx_msg void OnEnChangeEditRotationY();
	afx_msg void OnEnChangeEditRotationZ();
	afx_msg void OnEnChangeEditScaleX();
	afx_msg void OnEnChangeEditScaleY();
	afx_msg void OnEnChangeEditScaleZ();
	afx_msg void OnBnClickedButtonSave();
	afx_msg void OnBnClickedButtonSaveAll();
	afx_msg void OnBnClickedButtonLoad();
	afx_msg void OnBnClickedButtonLoadAll();
	afx_msg void OnLbnSelchangeMeshList();
	CEdit m_meshName;
	CEdit m_subsetCount;
	afx_msg void OnLbnSelchangeMaterialList();
	CEdit m_shaderName;
	afx_msg void OnBnClickedButtonAddMaterial();
	afx_msg void OnBnClickedButtonChangeMaterial();
	afx_msg void OnBnClickedButtonDeleteMaterial();
	CEdit m_materialCount;
	virtual BOOL OnInitDialog();
	afx_msg void OnLbnDblclkMaterialList();
	afx_msg void OnEnSetfocusRotX();
	afx_msg void OnEnKillfocusEditRotX();
	afx_msg void OnEnSetfocusEditRotY();
	afx_msg void OnEnKillfocusEditRotY();
	afx_msg void OnEnSetfocusEditRotZ();
	afx_msg void OnEnKillfocusEditRotZ();
};
