#pragma once
#include "afxwin.h"


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
	void DeleteAllObject();
	void UpdatePhysicsUpdate(GameObject* obj);
	void SaveObject(GameObject* _obj);
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
	afx_msg void OnCbnSelchangeComboLayer();
	CComboBox m_layer;
	afx_msg void OnBnClickedCheckMeshRender();
	afx_msg void OnBnClickedCheckSphereCollider();
	afx_msg void OnBnClickedCheckBoxCollider();
	afx_msg void OnBnClickedCheckCylinderCollider();
	afx_msg void OnBnClickedCheckMeshCollider();
	afx_msg void OnBnClickedCheckSphereIsTrigger();
	afx_msg void OnBnClickedCheckBoxIsTrigger();
	afx_msg void OnBnClickedCheckCylinderIsTrigger();
	afx_msg void OnBnClickedCheckMeshIsTrigger();
	CButton m_useMeshRenderer;
	CButton m_useSphereCollider;
	CButton m_IsTriggerSphereCollider;
	CButton m_useBoxCollider;
	CButton m_IsTriggerBoxCollider;
	CButton m_useCylinderCollider;
	CButton m_IsTriggerCylinderCollider;
	CButton m_useMeshCollider;
	CButton m_IsTriggerMeshCollider;
	afx_msg void OnEnChangeEditSphereColliderRadius();
	afx_msg void OnEnChangeEditSphereColliderX();
	afx_msg void OnEnChangeEditSphereColliderY();
	afx_msg void OnEnChangeEditSphereColliderZ();
	afx_msg void OnEnChangeEditBoxColliderWidth();
	afx_msg void OnEnChangeEditBoxColliderHeight();
	afx_msg void OnEnChangeEditBoxColliderDepth();
	afx_msg void OnEnChangeEditBoxColliderX();
	afx_msg void OnEnChangeEditBoxColliderY();
	afx_msg void OnEnChangeEditBoxColliderZ();
	afx_msg void OnEnChangeEditCylinderColliderRadius();
	afx_msg void OnEnChangeEditCylinderColliderHeight();
	afx_msg void OnEnChangeEditCylinderColliderX();
	afx_msg void OnEnChangeEditCylinderColliderY();
	afx_msg void OnEnChangeEditCylinderColliderZ();
	CEdit m_sphereColliderRadius;
	CEdit m_sphereColliderX;
	CEdit m_sphereColliderY;
	CEdit m_sphereColliderZ;
	CEdit m_boxColliderWidth;
	CEdit m_boxColliderHeight;
	CEdit m_boxColliderDepth;
	CEdit m_boxColliderX;
	CEdit m_boxColliderY;
	CEdit m_boxColliderZ;
	CEdit m_cylinderColliderRadius;
	CEdit m_cylinderColliderHeight;
	CEdit m_cylinderColliderX;
	CEdit m_cylinderColliderY;
	CEdit m_cylinderColliderZ;
	CButton m_renderMaterialAddButton;
	CButton m_renderMaterialChangeButton;
	CButton m_renderMaterialDeleteButton;
	CComboBox m_sceneName;
	afx_msg void OnCbnSelchangeComboSceneName();
};
