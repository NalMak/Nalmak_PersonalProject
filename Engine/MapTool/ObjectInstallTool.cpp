// ObjectInstallTool.cpp : 구현 파일입니다.
//

#include "stdafx.h"
#include "Nalmak3D_MapTool.h"
#include "ObjectInstallTool.h"
#include "afxdialogex.h"
#include "MapToolManager.h"
#include "MFC_Utility.h"
#include "StaticObjectInfo.h"

// ObjectInstallTool 대화 상자입니다.

IMPLEMENT_DYNAMIC(ObjectInstallTool, CDialogEx)

ObjectInstallTool::ObjectInstallTool(CWnd* pParent /*=NULL*/)
	: CDialogEx(IDD_DIALOG1, pParent)
{

}

ObjectInstallTool::~ObjectInstallTool()
{
}

void ObjectInstallTool::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_LIST1, m_objectList);
	DDX_Control(pDX, IDC_LIST2, m_meshList);
	DDX_Control(pDX, IDC_LIST3, m_materialList);
	DDX_Control(pDX, IDC_LIST4, m_materialRenderList);
	DDX_Control(pDX, IDC_EDIT17, m_objectName);
	DDX_Control(pDX, IDC_COMBO2, m_objectTag);
	DDX_Control(pDX, IDC_EDIT1, m_posX);
	DDX_Control(pDX, IDC_EDIT2, m_posY);
	DDX_Control(pDX, IDC_EDIT3, m_posZ);
	DDX_Control(pDX, IDC_EDIT4, m_rotX);
	DDX_Control(pDX, IDC_EDIT5, m_rotY);
	DDX_Control(pDX, IDC_EDIT6, m_rotZ);
	DDX_Control(pDX, IDC_EDIT10, m_scaleX);
	DDX_Control(pDX, IDC_EDIT11, m_scaleY);
	DDX_Control(pDX, IDC_EDIT16, m_scaleZ);
	DDX_Control(pDX, IDC_EDIT18, m_meshName);
	DDX_Control(pDX, IDC_EDIT19, m_shaderName);
	DDX_Control(pDX, IDC_EDIT21, m_materialCount);
	DDX_Control(pDX, IDC_COMBO3, m_layer);
	DDX_Control(pDX, IDC_CHECK1, m_useMeshRenderer);
	DDX_Control(pDX, IDC_CHECK2, m_useSphereCollider);
	DDX_Control(pDX, IDC_CHECK6, m_IsTriggerSphereCollider);
	DDX_Control(pDX, IDC_CHECK3, m_useBoxCollider);
	DDX_Control(pDX, IDC_CHECK7, m_IsTriggerBoxCollider);
	DDX_Control(pDX, IDC_CHECK4, m_useCylinderCollider);
	DDX_Control(pDX, IDC_CHECK8, m_IsTriggerCylinderCollider);
	DDX_Control(pDX, IDC_CHECK5, m_useMeshCollider);
	DDX_Control(pDX, IDC_CHECK9, m_IsTriggerMeshCollider);
	DDX_Control(pDX, IDC_EDIT22, m_sphereColliderRadius);
	DDX_Control(pDX, IDC_EDIT23, m_sphereColliderX);
	DDX_Control(pDX, IDC_EDIT24, m_sphereColliderY);
	DDX_Control(pDX, IDC_EDIT25, m_sphereColliderZ);
	DDX_Control(pDX, IDC_EDIT26, m_boxColliderWidth);
	DDX_Control(pDX, IDC_EDIT27, m_boxColliderHeight);
	DDX_Control(pDX, IDC_EDIT28, m_boxColliderDepth);
	DDX_Control(pDX, IDC_EDIT29, m_boxColliderX);
	DDX_Control(pDX, IDC_EDIT30, m_boxColliderY);
	DDX_Control(pDX, IDC_EDIT31, m_boxColliderZ);
	DDX_Control(pDX, IDC_EDIT32, m_cylinderColliderRadius);
	DDX_Control(pDX, IDC_EDIT33, m_cylinderColliderHeight);
	DDX_Control(pDX, IDC_EDIT34, m_cylinderColliderX);
	DDX_Control(pDX, IDC_EDIT35, m_cylinderColliderY);
	DDX_Control(pDX, IDC_EDIT36, m_cylinderColliderZ);
	DDX_Control(pDX, IDC_BUTTON15, m_renderMaterialAddButton);
	DDX_Control(pDX, IDC_BUTTON16, m_renderMaterialChangeButton);
	DDX_Control(pDX, IDC_BUTTON17, m_renderMaterialDeleteButton);
	DDX_Control(pDX, IDC_COMBO4, m_sceneName);
	DDX_Control(pDX, IDC_LIST5, m_subsetCountList);
	DDX_Control(pDX, IDC_COMBO1, m_meshRenderer_selectedMesh);
}

BOOL ObjectInstallTool::OnInitDialog()
{
	CDialogEx::OnInitDialog();


	m_mapToolManager = MapToolManager::GetInstance();
	m_mapToolManager->SetControlView(this);

	for (int i = 0; i < OBJECT_TAG_MAX; ++i)
	{
		m_objectTag.InsertString(i, g_objectTagName[i].c_str());
	}
	for (int i = 0; i < OBJECT_LAYER_MAX; ++i)
	{
		m_layer.InsertString(i, g_objectLayerName[i].c_str());
	}

	wstring path = ResourceManager::GetInstance()->GetResourceDirectoryPath();

	vector<wstring> sceneFolderNames;
	{
		wstring defaultPath = path;
		wstring path = defaultPath + L"/*.*";
		int checkDirFile = 0;
		struct _wfinddata_t fd;
		intptr_t handle;

		//fd 구조체 초기화.
		if ((handle = _wfindfirst(path.c_str(), &fd)) == -1L)
		{
			//파일이나 디렉토리가 없을 경우.
			_findclose(handle);
		}
		else
		{
			do //폴더 탐색 반복 시작	
			{
				//현재 객체 종류 확인(파일 or 디렉토리)
				checkDirFile = FileIO::IsFileOrDir(fd);
				if (checkDirFile == 0 && fd.name[0] != '.')
				{
					sceneFolderNames.emplace_back(fd.name);
				}
			} while (_wfindnext(handle, &fd) == 0);
			_findclose(handle);
		}
	}
	int i = 0;
	for (auto& sceneName : sceneFolderNames)
	{
		m_sceneName.InsertString(i,sceneName.c_str());
		++i;
	}


	EventHandler e1 = [=]()
	{
		MapToolManager::GetInstance()->SelectObject(MapToolManager::GetInstance()->GetDebuggingObject()->GetPickingObject());
	};
	EventHandler e2 = [=]()
	{
		MapToolManager::GetInstance()->UpdateSelectObjectTransform(MapToolManager::GetInstance()->GetDebuggingObject()->GetPickingObject());
	};
	MapToolManager::GetInstance()->GetDebuggingObject()->AddEvent(e1);
	MapToolManager::GetInstance()->GetDebuggingObject()->AddEvent(e2);

	return TRUE;  
}



void ObjectInstallTool::UpdateObjectInfo(GameObject * _selectedObj, int _index)
{
	if (_index == -1)
		return;

	_selectedObj->InitializeComponents();

	m_objectList.SetCurSel(_index);

	auto renderer = _selectedObj->GetComponent<MeshRenderer>();
	if (renderer)
	{
		m_meshList.EnableWindow(true);
		m_materialList.EnableWindow(true);
		m_materialRenderList.EnableWindow(true);
		m_renderMaterialAddButton.EnableWindow(true);
		m_renderMaterialChangeButton.EnableWindow(true);
		m_renderMaterialDeleteButton.EnableWindow(true);
		m_meshRenderer_selectedMesh.EnableWindow(true);
		int mtrlCount = renderer->GetMaterialCount();

		m_materialRenderList.ResetContent();
		

		for (int i = 0; i < mtrlCount; ++i)
		{
			auto mtrl = renderer->GetMaterial(i);
			CString str;
			str = mtrl->GetName().c_str();
			m_materialRenderList.AddString(str);
		}
		{
			MFC_Utility::SetEditBoxInt(&m_materialCount, renderer->GetMaterialCount());
		}
		{
			CString str;
			str = renderer->GetMesh()->GetName().c_str();
			m_meshName.SetWindowTextW(str);
		}
		/*	{

				for (UINT i = 0; i < renderer->GetMesh()->GetMeshContainerSize(); ++i)
				{
					unsigned long index = renderer->GetMesh()->GetSubsetCount(i);
					CString str = to_wstring(index).c_str();
					m_subsetCountList.AddString(str);
				}
			}*/
	}
	else
	{
		m_meshList.EnableWindow(false);
		m_materialList.EnableWindow(false);
		m_materialRenderList.EnableWindow(false);
		m_renderMaterialAddButton.EnableWindow(false);
		m_renderMaterialChangeButton.EnableWindow(false);
		m_renderMaterialDeleteButton.EnableWindow(false);
		m_meshRenderer_selectedMesh.EnableWindow(false);

	}
	{
		CString str;
		str = _selectedObj->GetName().c_str();
		m_objectName.SetWindowTextW(str);
	}
	{
		m_objectTag.SetCurSel(_selectedObj->GetTag());
	}
	{
		m_layer.SetCurSel(_selectedObj->GetLayer());
	}
	{
		if (_selectedObj->GetComponent<MeshRenderer>())
		{
			m_useMeshRenderer.SetCheck(1);
		}
		else
		{
			m_useMeshRenderer.SetCheck(0);
		}
		if (_selectedObj->GetComponent<SphereCollider>())
		{
			auto collider = _selectedObj->GetComponent<SphereCollider>();
			m_useSphereCollider.SetCheck(1);
			m_IsTriggerSphereCollider.SetCheck(collider->IsTrigger());
			MFC_Utility::SetEditBoxFloat(&m_sphereColliderX, collider->GetPosOffset().x);
			MFC_Utility::SetEditBoxFloat(&m_sphereColliderY, collider->GetPosOffset().y);
			MFC_Utility::SetEditBoxFloat(&m_sphereColliderZ, collider->GetPosOffset().z);
			MFC_Utility::SetEditBoxFloat(&m_sphereColliderRadius, collider->GetRadius());
			m_sphereColliderX.EnableWindow(true);
			m_sphereColliderY.EnableWindow(true);
			m_sphereColliderZ.EnableWindow(true);
			m_sphereColliderRadius.EnableWindow(true);
		}
		else
		{
			m_useSphereCollider.SetCheck(0);
			m_IsTriggerSphereCollider.SetCheck(0);
			m_sphereColliderX.EnableWindow(false);
			m_sphereColliderY.EnableWindow(false);
			m_sphereColliderZ.EnableWindow(false);
			m_sphereColliderRadius.EnableWindow(false);
		}
		if (_selectedObj->GetComponent<BoxCollider>())
		{
			auto collider = _selectedObj->GetComponent<BoxCollider>();
			m_useBoxCollider.SetCheck(1);
			m_IsTriggerBoxCollider.SetCheck(collider->IsTrigger());
			MFC_Utility::SetEditBoxFloat(&m_boxColliderX, collider->GetPosOffset().x);
			MFC_Utility::SetEditBoxFloat(&m_boxColliderY, collider->GetPosOffset().y);
			MFC_Utility::SetEditBoxFloat(&m_boxColliderZ, collider->GetPosOffset().z);
			MFC_Utility::SetEditBoxFloat(&m_boxColliderWidth, collider->GetWidth());
			MFC_Utility::SetEditBoxFloat(&m_boxColliderHeight, collider->GetHeight());
			MFC_Utility::SetEditBoxFloat(&m_boxColliderDepth, collider->GetDepth());
			m_boxColliderX.EnableWindow(true);
			m_boxColliderY.EnableWindow(true);
			m_boxColliderZ.EnableWindow(true);
			m_boxColliderWidth.EnableWindow(true);
			m_boxColliderHeight.EnableWindow(true);
			m_boxColliderDepth.EnableWindow(true);

		}
		else
		{
			m_useBoxCollider.SetCheck(0);
			m_IsTriggerBoxCollider.SetCheck(0);
			m_boxColliderX.EnableWindow(false);
			m_boxColliderY.EnableWindow(false);
			m_boxColliderZ.EnableWindow(false);
			m_boxColliderWidth.EnableWindow(false);
			m_boxColliderHeight.EnableWindow(false);
			m_boxColliderDepth.EnableWindow(false);
		}
		if (_selectedObj->GetComponent<CapsuleCollider>())
		{
			auto collider = _selectedObj->GetComponent<CapsuleCollider>();

			m_useCylinderCollider.SetCheck(1);
			m_IsTriggerCylinderCollider.SetCheck(collider->IsTrigger());
			MFC_Utility::SetEditBoxFloat(&m_cylinderColliderX, collider->GetPosOffset().x);
			MFC_Utility::SetEditBoxFloat(&m_cylinderColliderY, collider->GetPosOffset().y);
			MFC_Utility::SetEditBoxFloat(&m_cylinderColliderZ, collider->GetPosOffset().z);
			MFC_Utility::SetEditBoxFloat(&m_cylinderColliderHeight, collider->GetHeight());
			MFC_Utility::SetEditBoxFloat(&m_cylinderColliderRadius, collider->GetRadius());

			m_cylinderColliderX.EnableWindow(true);
			m_cylinderColliderY.EnableWindow(true);
			m_cylinderColliderZ.EnableWindow(true);
			m_cylinderColliderHeight.EnableWindow(true);
			m_cylinderColliderRadius.EnableWindow(true);

		}
		else
		{
			m_useCylinderCollider.SetCheck(0);
			m_IsTriggerCylinderCollider.SetCheck(0);
			m_cylinderColliderX.EnableWindow(false);
			m_cylinderColliderY.EnableWindow(false);
			m_cylinderColliderZ.EnableWindow(false);
			m_cylinderColliderHeight.EnableWindow(false);
			m_cylinderColliderRadius.EnableWindow(false);
		}
		if (_selectedObj->GetComponent<MeshCollider>())
		{
			auto collider = _selectedObj->GetComponent<MeshCollider>();

			m_useMeshCollider.SetCheck(1);
			m_IsTriggerMeshCollider.SetCheck(collider->IsTrigger());
			m_IsTriggerMeshCollider.EnableWindow(true);
		}
		else
		{
			m_useMeshCollider.SetCheck(0);
			m_IsTriggerMeshCollider.SetCheck(0);
			m_IsTriggerMeshCollider.EnableWindow(false);

		}
	}


	{
		int index = m_materialRenderList.GetCurSel();
		if (index != -1)
		{
			CString str;
			str = renderer->GetMaterial(index)->GetShader()->GetName().c_str();
			m_shaderName.SetWindowTextW(str);
		}
		else
		{
			CString str = L"";
			m_shaderName.SetWindowTextW(str);
		}
	}
	UpdateObjectTransformInfo(_selectedObj);
}

void ObjectInstallTool::UpdateObjectTransformInfo(GameObject * _obj)
{
	Transform* trs = _obj->GetTransform();
	MFC_Utility::SetEditBoxFloat(&m_posX, trs->position.x);
	MFC_Utility::SetEditBoxFloat(&m_posY, trs->position.y);
	MFC_Utility::SetEditBoxFloat(&m_posZ, trs->position.z);

	Quaternion quaternion = trs->rotation;
	Vector3 rot = Nalmak_Math::QuaternionToEuler(quaternion);
	MFC_Utility::SetEditBoxFloat(&m_rotX, rot.x);
	MFC_Utility::SetEditBoxFloat(&m_rotY, rot.y);
	MFC_Utility::SetEditBoxFloat(&m_rotZ, rot.z);

	MFC_Utility::SetEditBoxFloat(&m_scaleX, trs->scale.x);
	MFC_Utility::SetEditBoxFloat(&m_scaleY, trs->scale.y);
	MFC_Utility::SetEditBoxFloat(&m_scaleZ, trs->scale.z);

	UpdatePhysicsUpdate(_obj);
}

void ObjectInstallTool::DeleteAllObject()
{
	m_mapToolManager->DeleteAllObject();
	m_objectList.ResetContent();
}

void ObjectInstallTool::UpdatePhysicsUpdate(GameObject * _obj)
{
	_obj->GetTransform()->UpdateMatrix();

	if (m_useBoxCollider.GetCheck())
	{
		_obj->GetComponent<BoxCollider>()->UpdatePysicsTransform();
	}
	if (m_useCylinderCollider.GetCheck())
	{
		_obj->GetComponent<CapsuleCollider>()->UpdatePysicsTransform();
	}
	if (m_useMeshCollider.GetCheck())
	{
		_obj->GetComponent<MeshCollider>()->UpdatePysicsTransform();
	}
	if (m_useSphereCollider.GetCheck())
	{
		_obj->GetComponent<SphereCollider>()->UpdatePysicsTransform();
	}
}

void ObjectInstallTool::SaveObject(GameObject * _obj)
{
	auto obj = _obj; 
	if (!obj)
		return;

	CFileDialog dlg
	(
		FALSE,
		L"sttd",
		(_obj->GetName() + L".sttd").c_str(),
		OFN_OVERWRITEPROMPT,
		L"Data File(*.sttd) | *.sttd||",
		this
	);

	TCHAR fp[256] = L"";
	GetCurrentDirectory(256, fp);
	PathRemoveFileSpec(fp);
	lstrcat(fp, L"\\Data\\Static");
	dlg.m_ofn.lpstrInitialDir = fp;

	if (dlg.DoModal())
	{
		HANDLE handle = CreateFile(dlg.GetPathName(), GENERIC_WRITE, 0, nullptr, CREATE_ALWAYS, FILE_ATTRIBUTE_NORMAL, nullptr);
		if (INVALID_HANDLE_VALUE == handle)
		{
			AfxMessageBox(L"Failed to Save File");
			return;
		}
		DWORD byte;

		int tag = m_objectTag.GetCurSel();
		WriteFile(handle, &tag, sizeof(int), &byte, nullptr);
		int layer = m_layer.GetCurSel();
		WriteFile(handle, &layer, sizeof(int), &byte, nullptr);

		Transform::Desc trans;
		trans.position = obj->GetTransform()->GetWorldPosition();
		trans.rotation = obj->GetTransform()->GetWorldRotation();
		trans.scale = obj->GetTransform()->scale;

		WriteFile(handle, &trans, sizeof(Transform::Desc), &byte, nullptr);


		bool isExist = false;
		auto render = obj->GetComponent<MeshRenderer>();
		if (render)
			isExist = true;
		else
			isExist = false;
		WriteFile(handle, &isExist, sizeof(bool), &byte, nullptr);
		if (isExist)
		{
			wstring meshName = render->GetMesh()->GetName();
			DWORD meshNameLength = (DWORD)meshName.length();
			WriteFile(handle, &meshNameLength, sizeof(DWORD), &byte, nullptr);
			WriteFile(handle, meshName.c_str(), meshNameLength * sizeof(wchar_t), &byte, nullptr);

			int materialCount = render->GetMaterialCount();
			WriteFile(handle, &materialCount, sizeof(int), &byte, nullptr);

			for (int i = 0; i < materialCount; ++i)
			{
				wstring materialName = render->GetMaterial(i)->GetName();
				DWORD mtrlNameLength = (DWORD)materialName.length();
				WriteFile(handle, &mtrlNameLength, sizeof(DWORD), &byte, nullptr);
				WriteFile(handle, materialName.c_str(), mtrlNameLength * sizeof(wchar_t), &byte, nullptr);
			}
		}
		auto sphereCollider = obj->GetComponent<SphereCollider>();
		if (sphereCollider)
			isExist = true;
		else
			isExist = false;
		WriteFile(handle, &isExist, sizeof(bool), &byte, nullptr);

		if (isExist)
		{
			SphereCollider::Desc sphere;
			sphere.isTrigger = sphereCollider->IsTrigger();
			sphere.posOffset = sphereCollider->GetPosOffset();
			sphere.radius = sphereCollider->GetRadius();

			WriteFile(handle, &sphere, sizeof(SphereCollider::Desc), &byte, nullptr);
		}

		auto boxCollider = obj->GetComponent<BoxCollider>();
		if (boxCollider)
			isExist = true;
		else
			isExist = false;
		WriteFile(handle, &isExist, sizeof(bool), &byte, nullptr);

		if (isExist)
		{
			BoxCollider::Desc box;
			box.isTrigger = boxCollider->IsTrigger();
			box.width = boxCollider->GetWidth();
			box.height = boxCollider->GetHeight();
			box.depth = boxCollider->GetDepth();
			box.posOffset = boxCollider->GetPosOffset();
			WriteFile(handle, &box, sizeof(BoxCollider::Desc), &byte, nullptr);
		}

		auto capsuleCollider = obj->GetComponent<CapsuleCollider>();
		if (capsuleCollider)
			isExist = true;
		else
			isExist = false;
		WriteFile(handle, &isExist, sizeof(bool), &byte, nullptr);

		if (isExist)
		{
			CapsuleCollider::Desc capsule;
			capsule.isTrigger = capsuleCollider->IsTrigger();
			capsule.radius = capsuleCollider->GetRadius();
			capsule.height = capsuleCollider->GetHeight();
			capsule.posOffset = capsuleCollider->GetPosOffset();
			WriteFile(handle, &capsule, sizeof(CapsuleCollider::Desc), &byte, nullptr);
		}
		auto meshCollider = obj->GetComponent<MeshCollider>();
		if (meshCollider)
			isExist = true;
		else
			isExist = false;
		WriteFile(handle, &isExist, sizeof(bool), &byte, nullptr);

		if (isExist)
		{
			MeshCollider::Desc mesh;
			mesh.isTrigger = meshCollider->IsTrigger();
			WriteFile(handle, &mesh, sizeof(MeshCollider::Desc), &byte, nullptr);
		}
		CloseHandle(handle);
		AfxMessageBox(L"Succeeded to Save File");
	}
}


BEGIN_MESSAGE_MAP(ObjectInstallTool, CDialogEx)
	ON_LBN_SELCHANGE(IDC_LIST1, &ObjectInstallTool::OnLbnSelchangeObjectList)
	ON_BN_CLICKED(IDC_BUTTON1, &ObjectInstallTool::OnBnClickedButtonCreateObject)
	ON_BN_CLICKED(IDC_BUTTON10, &ObjectInstallTool::OnBnClickedButtonDeleteObject)
	ON_EN_CHANGE(IDC_EDIT17, &ObjectInstallTool::OnEnChangeEditObjectName)
	ON_CBN_SELCHANGE(IDC_COMBO2, &ObjectInstallTool::OnCbnSelchangeComboObjectTag)
	ON_EN_CHANGE(IDC_EDIT1, &ObjectInstallTool::OnEnChangeEditPositionX)
	ON_EN_CHANGE(IDC_EDIT2, &ObjectInstallTool::OnEnChangeEditPositionY)
	ON_EN_CHANGE(IDC_EDIT3, &ObjectInstallTool::OnEnChangeEditPositionZ)
	ON_EN_CHANGE(IDC_EDIT4, &ObjectInstallTool::OnEnChangeEditRotationX)
	ON_EN_CHANGE(IDC_EDIT5, &ObjectInstallTool::OnEnChangeEditRotationY)
	ON_EN_CHANGE(IDC_EDIT6, &ObjectInstallTool::OnEnChangeEditRotationZ)
	ON_EN_CHANGE(IDC_EDIT10, &ObjectInstallTool::OnEnChangeEditScaleX)
	ON_EN_CHANGE(IDC_EDIT11, &ObjectInstallTool::OnEnChangeEditScaleY)
	ON_EN_CHANGE(IDC_EDIT16, &ObjectInstallTool::OnEnChangeEditScaleZ)
	ON_BN_CLICKED(IDC_BUTTON11, &ObjectInstallTool::OnBnClickedButtonSave)
	ON_BN_CLICKED(IDC_BUTTON12, &ObjectInstallTool::OnBnClickedButtonSaveAll)
	ON_BN_CLICKED(IDC_BUTTON13, &ObjectInstallTool::OnBnClickedButtonLoad)
	ON_BN_CLICKED(IDC_BUTTON14, &ObjectInstallTool::OnBnClickedButtonLoadAll)
	ON_LBN_SELCHANGE(IDC_LIST2, &ObjectInstallTool::OnLbnSelchangeMeshList)
	ON_LBN_SELCHANGE(IDC_LIST3, &ObjectInstallTool::OnLbnSelchangeMaterialList)
	ON_BN_CLICKED(IDC_BUTTON15, &ObjectInstallTool::OnBnClickedButtonAddMaterial)
	ON_BN_CLICKED(IDC_BUTTON16, &ObjectInstallTool::OnBnClickedButtonChangeMaterial)
	ON_BN_CLICKED(IDC_BUTTON17, &ObjectInstallTool::OnBnClickedButtonDeleteMaterial)
	ON_LBN_DBLCLK(IDC_LIST3, &ObjectInstallTool::OnLbnDblclkMaterialList)
	ON_EN_SETFOCUS(IDC_EDIT4, &ObjectInstallTool::OnEnSetfocusRotX)
	ON_EN_KILLFOCUS(IDC_EDIT4, &ObjectInstallTool::OnEnKillfocusEditRotX)
	ON_EN_SETFOCUS(IDC_EDIT5, &ObjectInstallTool::OnEnSetfocusEditRotY)
	ON_EN_KILLFOCUS(IDC_EDIT5, &ObjectInstallTool::OnEnKillfocusEditRotY)
	ON_EN_SETFOCUS(IDC_EDIT6, &ObjectInstallTool::OnEnSetfocusEditRotZ)
	ON_EN_KILLFOCUS(IDC_EDIT6, &ObjectInstallTool::OnEnKillfocusEditRotZ)
	ON_CBN_SELCHANGE(IDC_COMBO3, &ObjectInstallTool::OnCbnSelchangeComboLayer)
	ON_BN_CLICKED(IDC_CHECK1, &ObjectInstallTool::OnBnClickedCheckMeshRender)
	ON_BN_CLICKED(IDC_CHECK2, &ObjectInstallTool::OnBnClickedCheckSphereCollider)
	ON_BN_CLICKED(IDC_CHECK3, &ObjectInstallTool::OnBnClickedCheckBoxCollider)
	ON_BN_CLICKED(IDC_CHECK4, &ObjectInstallTool::OnBnClickedCheckCylinderCollider)
	ON_BN_CLICKED(IDC_CHECK5, &ObjectInstallTool::OnBnClickedCheckMeshCollider)
	ON_BN_CLICKED(IDC_CHECK6, &ObjectInstallTool::OnBnClickedCheckSphereIsTrigger)
	ON_BN_CLICKED(IDC_CHECK7, &ObjectInstallTool::OnBnClickedCheckBoxIsTrigger)
	ON_BN_CLICKED(IDC_CHECK8, &ObjectInstallTool::OnBnClickedCheckCylinderIsTrigger)
	ON_BN_CLICKED(IDC_CHECK9, &ObjectInstallTool::OnBnClickedCheckMeshIsTrigger)
	ON_EN_CHANGE(IDC_EDIT22, &ObjectInstallTool::OnEnChangeEditSphereColliderRadius)
	ON_EN_CHANGE(IDC_EDIT23, &ObjectInstallTool::OnEnChangeEditSphereColliderX)
	ON_EN_CHANGE(IDC_EDIT24, &ObjectInstallTool::OnEnChangeEditSphereColliderY)
	ON_EN_CHANGE(IDC_EDIT25, &ObjectInstallTool::OnEnChangeEditSphereColliderZ)
	ON_EN_CHANGE(IDC_EDIT26, &ObjectInstallTool::OnEnChangeEditBoxColliderWidth)
	ON_EN_CHANGE(IDC_EDIT27, &ObjectInstallTool::OnEnChangeEditBoxColliderHeight)
	ON_EN_CHANGE(IDC_EDIT28, &ObjectInstallTool::OnEnChangeEditBoxColliderDepth)
	ON_EN_CHANGE(IDC_EDIT29, &ObjectInstallTool::OnEnChangeEditBoxColliderX)
	ON_EN_CHANGE(IDC_EDIT30, &ObjectInstallTool::OnEnChangeEditBoxColliderY)
	ON_EN_CHANGE(IDC_EDIT31, &ObjectInstallTool::OnEnChangeEditBoxColliderZ)
	ON_EN_CHANGE(IDC_EDIT32, &ObjectInstallTool::OnEnChangeEditCylinderColliderRadius)
	ON_EN_CHANGE(IDC_EDIT33, &ObjectInstallTool::OnEnChangeEditCylinderColliderHeight)
	ON_EN_CHANGE(IDC_EDIT34, &ObjectInstallTool::OnEnChangeEditCylinderColliderX)
	ON_EN_CHANGE(IDC_EDIT35, &ObjectInstallTool::OnEnChangeEditCylinderColliderY)
	ON_EN_CHANGE(IDC_EDIT36, &ObjectInstallTool::OnEnChangeEditCylinderColliderZ)
	ON_CBN_SELCHANGE(IDC_COMBO4, &ObjectInstallTool::OnCbnSelchangeComboSceneName)
	ON_CBN_SELCHANGE(IDC_COMBO1, &ObjectInstallTool::OnCbnSelchangeComboMeshRendererToMesh)
END_MESSAGE_MAP()


// ObjectInstallTool 메시지 처리기입니다.








void ObjectInstallTool::OnLbnSelchangeObjectList()
{
	int objectIndex = m_objectList.GetCurSel();

	if (-1 == objectIndex)
		return;

	m_mapToolManager->SeleteObject(objectIndex);
}


void ObjectInstallTool::OnBnClickedButtonCreateObject()
{
	auto newObj = INSTANTIATE()->AddComponent<MeshRenderer>();
	m_mapToolManager->CreateObject(newObj);
	m_objectList.InsertString(m_objectList.GetCount(), newObj->GetName().c_str());
	int count = m_objectList.GetCount();
	m_objectList.SetCurSel(count - 1);
	m_mapToolManager->SelectObject(newObj);
}


void ObjectInstallTool::OnBnClickedButtonDeleteObject()
{
	int objectIndex = m_objectList.GetCurSel();

	if (-1 == objectIndex)
		return;

	m_objectList.DeleteString(objectIndex);
	m_mapToolManager->DeleteObject(objectIndex);
}


void ObjectInstallTool::OnEnChangeEditObjectName()
{
	int index = m_objectList.GetCurSel();
	if (index == -1)
		return;

	auto obj = m_mapToolManager->GetSelectedObject();
	if (!obj)
		return;
	CString name;
	m_objectName.GetWindowTextW(name);
	obj->SetName(name.GetString());
	m_objectList.DeleteString(index);
	m_objectList.InsertString(index, name);
	m_objectList.SetCurSel(index);
}


void ObjectInstallTool::OnCbnSelchangeComboObjectTag()
{
	int index = m_objectTag.GetCurSel();
	if (index == -1)
		return;

	auto obj = m_mapToolManager->GetSelectedObject();
	if (!obj)
		return;

	obj->SetTag(index);
}


void ObjectInstallTool::OnEnChangeEditPositionX()
{
	auto obj = m_mapToolManager->GetSelectedObject();
	if (!obj)
		return;

	GetFloatByEditBox(obj->GetTransform()->position.x, IDC_EDIT1);
	UpdatePhysicsUpdate(obj);
}


void ObjectInstallTool::OnEnChangeEditPositionY()
{
	auto obj = m_mapToolManager->GetSelectedObject();
	if (!obj)
		return;

	GetFloatByEditBox(obj->GetTransform()->position.y, IDC_EDIT2);
	UpdatePhysicsUpdate(obj);
}


void ObjectInstallTool::OnEnChangeEditPositionZ()
{
	auto obj = m_mapToolManager->GetSelectedObject();
	if (!obj)
		return;

	GetFloatByEditBox(obj->GetTransform()->position.z, IDC_EDIT3);
	UpdatePhysicsUpdate(obj);
}


void ObjectInstallTool::OnEnChangeEditRotationX()
{
	if (!m_isFocusRotation)
		return;

	auto obj = m_mapToolManager->GetSelectedObject();
	if (!obj)
		return;

	Quaternion rot;
	GetFloatByEditBox(rot.x, IDC_EDIT4);
	GetFloatByEditBox(rot.y, IDC_EDIT5);
	GetFloatByEditBox(rot.z, IDC_EDIT6);
	D3DXQuaternionRotationYawPitchRoll(&rot, rot.y * Deg2Rad, rot.x * Deg2Rad, rot.z * Deg2Rad);

	obj->GetTransform()->rotation = rot;
	UpdatePhysicsUpdate(obj);
}


void ObjectInstallTool::OnEnChangeEditRotationY()
{
	if (!m_isFocusRotation)
		return;

	auto obj = m_mapToolManager->GetSelectedObject();
	if (!obj)
		return;

	Quaternion rot;
	GetFloatByEditBox(rot.x, IDC_EDIT4);
	GetFloatByEditBox(rot.y, IDC_EDIT5);
	GetFloatByEditBox(rot.z, IDC_EDIT6);
	D3DXQuaternionRotationYawPitchRoll(&rot, rot.y * Deg2Rad, rot.x * Deg2Rad, rot.z * Deg2Rad);

	obj->GetTransform()->rotation = rot;
	UpdatePhysicsUpdate(obj);
}


void ObjectInstallTool::OnEnChangeEditRotationZ()
{
	if (!m_isFocusRotation)
		return;

	auto obj = m_mapToolManager->GetSelectedObject();
	if (!obj)
		return;

	Quaternion rot;
	GetFloatByEditBox(rot.x, IDC_EDIT4);
	GetFloatByEditBox(rot.y, IDC_EDIT5);
	GetFloatByEditBox(rot.z, IDC_EDIT6);
	D3DXQuaternionRotationYawPitchRoll(&rot, rot.y * Deg2Rad, rot.x * Deg2Rad, rot.z * Deg2Rad);

	obj->GetTransform()->rotation = rot;
	UpdatePhysicsUpdate(obj);
}


void ObjectInstallTool::OnEnChangeEditScaleX()
{
	auto obj = m_mapToolManager->GetSelectedObject();
	if (!obj)
		return;

	GetFloatByEditBox(obj->GetTransform()->scale.x, IDC_EDIT10);
}


void ObjectInstallTool::OnEnChangeEditScaleY()
{
	auto obj = m_mapToolManager->GetSelectedObject();
	if (!obj)
		return;

	GetFloatByEditBox(obj->GetTransform()->scale.y, IDC_EDIT11);
}


void ObjectInstallTool::OnEnChangeEditScaleZ()
{
	auto obj = m_mapToolManager->GetSelectedObject();
	if (!obj)
		return;

	GetFloatByEditBox(obj->GetTransform()->scale.z, IDC_EDIT16);
}


void ObjectInstallTool::OnBnClickedButtonSave()
{
	auto obj = m_mapToolManager->GetSelectedObject();
	SaveObject(obj);
}


void ObjectInstallTool::OnBnClickedButtonSaveAll()
{
	int count = (int)m_mapToolManager->GetObjectCount();
	for (int i = 0; i < count; ++i)
	{
		auto obj = m_mapToolManager->GetGameObject(i);
		SaveObject(obj);
	}
}


void ObjectInstallTool::OnBnClickedButtonLoad()
{
	CFileDialog dlg
	(
		TRUE,
		L"sttd",
		L"*.sttd",
		OFN_OVERWRITEPROMPT,
		L"Data File(*.sttd) | *.sttd||",
		this);

	TCHAR fp[256] = L"";
	GetCurrentDirectory(256, fp);
	PathRemoveFileSpec(fp);
	lstrcat(fp, L"\\Data\\Static");
	dlg.m_ofn.lpstrInitialDir = fp;

	if (dlg.DoModal())
	{

		HANDLE handle = CreateFile(dlg.GetPathName(), GENERIC_READ, 0, nullptr, OPEN_EXISTING, FILE_ATTRIBUTE_NORMAL, nullptr);
		if (INVALID_HANDLE_VALUE == handle)
		{
			AfxMessageBox(L"Load File Failed");
			return;
		}
		CloseHandle(handle);

		wstring filePath = dlg.GetPathName();
		wstring fileName = filePath.substr(filePath.find_last_of(L'\\') + 1);
		size_t targetNum = fileName.find_last_of(L".");
		fileName = fileName.substr(0, targetNum);

		int count = m_objectList.GetCount();
		m_objectList.SetCurSel(count - 1);

		GameObject* staticObj = MAKE_STATIC(fileName);

		m_mapToolManager->CreateObject(staticObj);
		m_objectList.InsertString(m_objectList.GetCount(), staticObj->GetName().c_str());
		int objCount = m_objectList.GetCount();
		m_objectList.SetCurSel(objCount - 1);

		m_mapToolManager->SelectObject(staticObj);

	}
}


void ObjectInstallTool::OnBnClickedButtonLoadAll()
{
	CString sceneName;
	m_sceneName.GetWindowTextW(sceneName);

	for (auto& staticObjInfo : ResourceManager::GetInstance()->GetAllResource<StaticObjectInfo>())
	{
		auto staticObj = MAKE_STATIC(staticObjInfo.first);

		m_mapToolManager->CreateObject(staticObj);
		m_objectList.InsertString(m_objectList.GetCount(), staticObj->GetName().c_str());
		int objCount = m_objectList.GetCount();
		m_objectList.SetCurSel(objCount - 1);

		m_mapToolManager->SelectObject(staticObj);
	}
}


void ObjectInstallTool::OnLbnSelchangeMeshList()
{
	auto obj = m_mapToolManager->GetSelectedObject();
	if (!obj)
		return;

	int index = m_meshList.GetCurSel();
	if (index == -1)
		return;


	m_subsetCountList.ResetContent();


	CString meshName;
	m_meshList.GetText(index, meshName);
	auto mesh = ResourceManager::GetInstance()->GetResource<Mesh>(meshName.GetString());
	

	for (UINT i = 0; i <mesh->GetMeshContainerSize(); ++i)
	{
		unsigned long index = mesh->GetSubsetCount(i);
		CString str = to_wstring(index).c_str();
		m_subsetCountList.AddString(str);
	}
}


void ObjectInstallTool::OnLbnSelchangeMaterialList()
{
	int index = m_materialList.GetCurSel();
	if (index == -1)
		return;

	CString mtrlName;
	m_materialList.GetText(index, mtrlName);

	Material* mtrl = ResourceManager::GetInstance()->GetResource<Material>(mtrlName.GetString());

	m_shaderName.SetWindowTextW(mtrl->GetShader()->GetName().c_str());
}


void ObjectInstallTool::OnBnClickedButtonAddMaterial()
{
	auto obj = m_mapToolManager->GetSelectedObject();
	if (!obj)
		return;

	int index = m_materialList.GetCurSel();
	if (index == -1)
		return;

	CString mtrlName;
	m_materialList.GetText(index, mtrlName);

	auto render = obj->GetComponent<MeshRenderer>();

	render->AddMaterial(mtrlName.GetString());
	m_materialRenderList.InsertString(m_materialRenderList.GetSelCount(), mtrlName);
	MFC_Utility::SetEditBoxInt(&m_materialCount, render->GetMaterialCount());
}


void ObjectInstallTool::OnBnClickedButtonChangeMaterial()
{
	auto obj = m_mapToolManager->GetSelectedObject();
	if (!obj)
		return;

	int renderIndex = m_materialRenderList.GetCurSel();
	if (renderIndex == -1)
		return;

	int mtrlIndex = m_materialList.GetCurSel();
	if (mtrlIndex == -1)
		return;

	CString mtrlName;
	m_materialList.GetText(mtrlIndex, mtrlName);

	auto render = obj->GetComponent<MeshRenderer>();
	render->SetMaterial(mtrlName.GetString(), renderIndex);


	m_materialRenderList.DeleteString(renderIndex);
	m_materialRenderList.InsertString(renderIndex, mtrlName);
	m_materialRenderList.SetCurSel(renderIndex);
}


void ObjectInstallTool::OnBnClickedButtonDeleteMaterial()
{
	auto obj = m_mapToolManager->GetSelectedObject();
	if (!obj)
		return;

	int index = m_materialRenderList.GetCurSel();
	if (index == -1)
		return;


	auto render = obj->GetComponent<MeshRenderer>();

	if (render->GetMaterialCount() > 1)
	{
		render->DeleteMaterial(index);
		m_materialRenderList.DeleteString(index);
		MFC_Utility::SetEditBoxInt(&m_materialCount, render->GetMaterialCount());

	}
}


void ObjectInstallTool::OnLbnDblclkMaterialList()
{
	OnBnClickedButtonChangeMaterial();
}


void ObjectInstallTool::OnEnSetfocusRotX()
{
	m_isFocusRotation = true;
}


void ObjectInstallTool::OnEnKillfocusEditRotX()
{
	m_isFocusRotation = false;
}


void ObjectInstallTool::OnEnSetfocusEditRotY()
{
	m_isFocusRotation = true;
}


void ObjectInstallTool::OnEnKillfocusEditRotY()
{
	m_isFocusRotation = false;
}


void ObjectInstallTool::OnEnSetfocusEditRotZ()
{
	m_isFocusRotation = true;
}


void ObjectInstallTool::OnEnKillfocusEditRotZ()
{
	m_isFocusRotation = false;
}


void ObjectInstallTool::OnCbnSelchangeComboLayer()
{
	auto obj = m_mapToolManager->GetSelectedObject();
	if (!obj)
		return;

	int index = m_layer.GetCurSel();
	if (index == -1)
		return;

	obj->SetLayer((USHORT)index);
}


void ObjectInstallTool::OnBnClickedCheckMeshRender()
{
	auto obj = m_mapToolManager->GetSelectedObject();
	if (!obj)
		return;
	if (m_useMeshRenderer.GetCheck())
	{
		obj->AddComponent<MeshRenderer>();
	}
	else
	{
		obj->DeleteComponent<MeshRenderer>();
	}
	UpdateObjectInfo(obj, m_objectList.GetCurSel());
}


void ObjectInstallTool::OnBnClickedCheckSphereCollider()
{
	auto obj = m_mapToolManager->GetSelectedObject();
	if (!obj)
		return;
	if (m_useSphereCollider.GetCheck())
	{
		obj->AddComponent<SphereCollider>();
	}
	else
	{
		obj->DeleteComponent<SphereCollider>();
	}
	UpdateObjectInfo(obj, m_objectList.GetCurSel());
}


void ObjectInstallTool::OnBnClickedCheckBoxCollider()
{
	auto obj = m_mapToolManager->GetSelectedObject();
	if (!obj)
		return;
	if (m_useBoxCollider.GetCheck())
	{
		obj->AddComponent<BoxCollider>();
	}
	else
	{
		obj->DeleteComponent<BoxCollider>();
	}
	UpdateObjectInfo(obj, m_objectList.GetCurSel());
}


void ObjectInstallTool::OnBnClickedCheckCylinderCollider()
{
	auto obj = m_mapToolManager->GetSelectedObject();
	if (!obj)
		return;
	if (m_useCylinderCollider.GetCheck())
	{
		obj->AddComponent<CapsuleCollider>();
	}
	else
	{
		obj->DeleteComponent<CapsuleCollider>();
	}
	UpdateObjectInfo(obj, m_objectList.GetCurSel());
}


void ObjectInstallTool::OnBnClickedCheckMeshCollider()
{
	auto obj = m_mapToolManager->GetSelectedObject();
	if (!obj)
		return;

	if (m_useMeshCollider.GetCheck())
	{
		obj->AddComponent<MeshCollider>();
	}
	else
	{
		obj->DeleteComponent<MeshCollider>();
	}
	UpdateObjectInfo(obj, m_objectList.GetCurSel());
}


void ObjectInstallTool::OnBnClickedCheckSphereIsTrigger()
{
	auto obj = m_mapToolManager->GetSelectedObject();
	if (!obj)
		return;
	obj->GetComponent<SphereCollider>()->SetTrigger(m_IsTriggerSphereCollider.GetCheck());
}


void ObjectInstallTool::OnBnClickedCheckBoxIsTrigger()
{
	auto obj = m_mapToolManager->GetSelectedObject();
	if (!obj)
		return;
	obj->GetComponent<BoxCollider>()->SetTrigger(m_IsTriggerSphereCollider.GetCheck());
}


void ObjectInstallTool::OnBnClickedCheckCylinderIsTrigger()
{
	auto obj = m_mapToolManager->GetSelectedObject();
	if (!obj)
		return;
	obj->GetComponent<CapsuleCollider>()->SetTrigger(m_IsTriggerSphereCollider.GetCheck());
}


void ObjectInstallTool::OnBnClickedCheckMeshIsTrigger()
{
	auto obj = m_mapToolManager->GetSelectedObject();
	if (!obj)
		return;
	obj->GetComponent<MeshCollider>()->SetTrigger(m_IsTriggerSphereCollider.GetCheck());
}


void ObjectInstallTool::OnEnChangeEditSphereColliderRadius()
{
	auto obj = m_mapToolManager->GetSelectedObject();
	if (!obj)
		return;
	float res;
	GetFloatByEditBox(res, IDC_EDIT22);
	obj->GetComponent<SphereCollider>()->SetRadius(res);
}


void ObjectInstallTool::OnEnChangeEditSphereColliderX()
{
	auto obj = m_mapToolManager->GetSelectedObject();
	if (!obj)
		return;
	float res;
	GetFloatByEditBox(res, IDC_EDIT23);
	obj->GetComponent<SphereCollider>()->SetPosX(res);

}


void ObjectInstallTool::OnEnChangeEditSphereColliderY()
{
	auto obj = m_mapToolManager->GetSelectedObject();
	if (!obj)
		return;
	float res;
	GetFloatByEditBox(res, IDC_EDIT24);
	obj->GetComponent<SphereCollider>()->SetPosY(res);

}


void ObjectInstallTool::OnEnChangeEditSphereColliderZ()
{
	auto obj = m_mapToolManager->GetSelectedObject();
	if (!obj)
		return;
	float res;
	GetFloatByEditBox(res, IDC_EDIT25);
	obj->GetComponent<SphereCollider>()->SetPosZ(res);

}


void ObjectInstallTool::OnEnChangeEditBoxColliderWidth()
{
	auto obj = m_mapToolManager->GetSelectedObject();
	if (!obj)
		return;
	float res;
	GetFloatByEditBox(res, IDC_EDIT26);
	obj->GetComponent<BoxCollider>()->SetWidth(res);

}


void ObjectInstallTool::OnEnChangeEditBoxColliderHeight()
{
	auto obj = m_mapToolManager->GetSelectedObject();
	if (!obj)
		return;
	float res;
	GetFloatByEditBox(res, IDC_EDIT27);
	obj->GetComponent<BoxCollider>()->SetHeight(res);

}


void ObjectInstallTool::OnEnChangeEditBoxColliderDepth()
{
	auto obj = m_mapToolManager->GetSelectedObject();
	if (!obj)
		return;
	float res;
	GetFloatByEditBox(res, IDC_EDIT28);
	obj->GetComponent<BoxCollider>()->SetDepth(res);

}


void ObjectInstallTool::OnEnChangeEditBoxColliderX()
{
	auto obj = m_mapToolManager->GetSelectedObject();
	if (!obj)
		return;
	float res;
	GetFloatByEditBox(res, IDC_EDIT29);
	obj->GetComponent<BoxCollider>()->SetPosX(res);
}


void ObjectInstallTool::OnEnChangeEditBoxColliderY()
{
	auto obj = m_mapToolManager->GetSelectedObject();
	if (!obj)
		return;
	float res;
	GetFloatByEditBox(res, IDC_EDIT30);
	obj->GetComponent<BoxCollider>()->SetPosY(res);
}


void ObjectInstallTool::OnEnChangeEditBoxColliderZ()
{
	auto obj = m_mapToolManager->GetSelectedObject();
	if (!obj)
		return;
	float res;
	GetFloatByEditBox(res, IDC_EDIT31);
	obj->GetComponent<BoxCollider>()->SetPosZ(res);
}


void ObjectInstallTool::OnEnChangeEditCylinderColliderRadius()
{
	auto obj = m_mapToolManager->GetSelectedObject();
	if (!obj)
		return;
	float res;
	GetFloatByEditBox(res, IDC_EDIT32);
	obj->GetComponent<CapsuleCollider>()->SetRadius(res);

}


void ObjectInstallTool::OnEnChangeEditCylinderColliderHeight()
{
	auto obj = m_mapToolManager->GetSelectedObject();
	if (!obj)
		return;
	float res;
	GetFloatByEditBox(res, IDC_EDIT33);
	obj->GetComponent<CapsuleCollider>()->SetHeight(res);

}


void ObjectInstallTool::OnEnChangeEditCylinderColliderX()
{
	auto obj = m_mapToolManager->GetSelectedObject();
	if (!obj)
		return;
	float res;
	GetFloatByEditBox(res, IDC_EDIT34);
	obj->GetComponent<CapsuleCollider>()->SetPosX(res);
}


void ObjectInstallTool::OnEnChangeEditCylinderColliderY()
{
	auto obj = m_mapToolManager->GetSelectedObject();
	if (!obj)
		return;
	float res;
	GetFloatByEditBox(res, IDC_EDIT35);
	obj->GetComponent<CapsuleCollider>()->SetPosY(res);
}


void ObjectInstallTool::OnEnChangeEditCylinderColliderZ()
{
	auto obj = m_mapToolManager->GetSelectedObject();
	if (!obj)
		return;
	float res;
	GetFloatByEditBox(res, IDC_EDIT36);
	obj->GetComponent<CapsuleCollider>()->SetPosZ(res);

}


void ObjectInstallTool::OnCbnSelchangeComboSceneName()
{
	CString sceneName;
	m_sceneName.GetLBText(m_sceneName.GetCurSel(), sceneName);
	wstring path = ResourceManager::GetInstance()->GetResourceDirectoryPath();
	path += L"/" + sceneName;
	ResourceManager::GetInstance()->ReleaseSceneResouce();
	ResourceManager::GetInstance()->LoadAllResources(path,false);

	auto& materials = ResourceManager::GetInstance()->GetAllResource<Material>();
	m_materialList.ResetContent();
	for (auto& mtrl : materials)
	{
		auto inputLayout = ((Material*)mtrl.second)->GetShader()->GetInputLayout();
		if (inputLayout == VERTEX_INPUT_LAYOUT::VERTEX_INPUT_LAYOUT_PARTICLE)
			continue;
		if (inputLayout == VERTEX_INPUT_LAYOUT::VERTEX_INPUT_LAYOUT_SKYBOX)
			continue;
		m_materialList.AddString(mtrl.first.c_str());
	}
	m_meshList.ResetContent();
	m_meshRenderer_selectedMesh.ResetContent();
	auto& meshes = ResourceManager::GetInstance()->GetAllResource<Mesh>();
	for (auto& mesh : meshes)
	{
		m_meshList.AddString(mesh.first.c_str());
		m_meshRenderer_selectedMesh.AddString(mesh.first.c_str());
	}
}


void ObjectInstallTool::OnCbnSelchangeComboMeshRendererToMesh()
{
	auto obj = m_mapToolManager->GetSelectedObject();
	if (!obj)
		return;
	CString meshName;
	m_meshRenderer_selectedMesh.GetLBText(m_meshRenderer_selectedMesh.GetCurSel(), meshName);

	obj->GetComponent<MeshRenderer>()->SetMesh(meshName.GetString());
	// TODO: 여기에 컨트롤 알림 처리기 코드를 추가합니다.
}
