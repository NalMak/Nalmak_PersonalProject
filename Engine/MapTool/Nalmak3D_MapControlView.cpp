// Nalmak3D_MapControlView.cpp : 구현 파일입니다.
//

#include "stdafx.h"
#include "Nalmak3D_MapTool.h"
#include "Nalmak3D_MapControlView.h"
#include "MapToolManager.h"
#include "PublicData.h"
#include "MFC_Utility.h"
#include "GameObject.h"

IMPLEMENT_DYNCREATE(Nalmak3D_MapControlView, CFormView)

Nalmak3D_MapControlView::Nalmak3D_MapControlView()
	: CFormView(IDD_NALMAK3D_MAPCONTROLVIEW)
{

}

Nalmak3D_MapControlView::~Nalmak3D_MapControlView()
{
}

void Nalmak3D_MapControlView::DoDataExchange(CDataExchange* pDX)
{
	CFormView::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_LIST1, m_objectList);
	DDX_Control(pDX, IDC_LIST2, m_materialList);
	DDX_Control(pDX, IDC_LIST3, m_meshList);
	DDX_Control(pDX, IDC_EDIT12, m_objectName);
	DDX_Control(pDX, IDC_COMBO1, m_objectTag);
	DDX_Control(pDX, IDC_EDIT1, m_positionX);
	DDX_Control(pDX, IDC_EDIT2, m_positionY);
	DDX_Control(pDX, IDC_EDIT3, m_positionZ);
	DDX_Control(pDX, IDC_EDIT5, m_rotationY);
	DDX_Control(pDX, IDC_EDIT4, m_rotationX);
	DDX_Control(pDX, IDC_EDIT6, m_rotationZ);
	DDX_Control(pDX, IDC_EDIT7, m_scaleX);
	DDX_Control(pDX, IDC_EDIT8, m_scaleY);
	DDX_Control(pDX, IDC_EDIT9, m_scaleZ);
	DDX_Control(pDX, IDC_EDIT10, m_materialName);
	DDX_Control(pDX, IDC_EDIT11, m_meshName);
	DDX_Control(pDX, IDC_EDIT13, m_shaderName);
}

BEGIN_MESSAGE_MAP(Nalmak3D_MapControlView, CFormView)
	ON_LBN_SELCHANGE(IDC_LIST1, &Nalmak3D_MapControlView::OnLbnSelchangeObjectList)
	ON_BN_CLICKED(IDC_BUTTON5, &Nalmak3D_MapControlView::OnBnClickedButtonCreateObject)
	ON_BN_CLICKED(IDC_BUTTON6, &Nalmak3D_MapControlView::OnBnClickedButtonDeleteObject)
	ON_CBN_SELCHANGE(IDC_COMBO1, &Nalmak3D_MapControlView::OnCbnSelchangeComboObjectTag)
	ON_BN_CLICKED(IDC_BUTTON1, &Nalmak3D_MapControlView::OnBnClickedButtonSave)
	ON_BN_CLICKED(IDC_BUTTON2, &Nalmak3D_MapControlView::OnBnClickedButtonLoad)
	ON_BN_CLICKED(IDC_BUTTON3, &Nalmak3D_MapControlView::OnBnClickedButtonSaveAll)
	ON_BN_CLICKED(IDC_BUTTON4, &Nalmak3D_MapControlView::OnBnClickedButtonLoadAll)
	ON_EN_CHANGE(IDC_EDIT12, &Nalmak3D_MapControlView::OnEnChangeEditObjectName)
	ON_EN_CHANGE(IDC_EDIT1, &Nalmak3D_MapControlView::OnEnChangeEditPositionX)
	ON_EN_CHANGE(IDC_EDIT2, &Nalmak3D_MapControlView::OnEnChangeEditPositionY)
	ON_EN_CHANGE(IDC_EDIT3, &Nalmak3D_MapControlView::OnEnChangeEditPositionZ)
	ON_EN_CHANGE(IDC_EDIT4, &Nalmak3D_MapControlView::OnEnChangeEditRotationX)
	ON_EN_CHANGE(IDC_EDIT5, &Nalmak3D_MapControlView::OnEnChangeEditRotationY)
	ON_EN_CHANGE(IDC_EDIT6, &Nalmak3D_MapControlView::OnEnChangeEditRotationZ)
	ON_EN_CHANGE(IDC_EDIT7, &Nalmak3D_MapControlView::OnEnChangeEditScaleX)
	ON_EN_CHANGE(IDC_EDIT8, &Nalmak3D_MapControlView::OnEnChangeEditScaleY)
	ON_EN_CHANGE(IDC_EDIT9, &Nalmak3D_MapControlView::OnEnChangeEditScaleZ)
	ON_EN_CHANGE(IDC_EDIT10, &Nalmak3D_MapControlView::OnEnChangeEditMaterialName)
	ON_EN_CHANGE(IDC_EDIT11, &Nalmak3D_MapControlView::OnEnChangeEditMeshName)
	ON_LBN_DBLCLK(IDC_LIST2, &Nalmak3D_MapControlView::OnLbnDblclkListMaterial)
	ON_LBN_DBLCLK(IDC_LIST3, &Nalmak3D_MapControlView::OnLbnDblclkListMesh)
END_MESSAGE_MAP()



void Nalmak3D_MapControlView::OnInitialUpdate()
{
	CFormView::OnInitialUpdate();

	m_mapToolManager = MapToolManager::GetInstance();
	m_mapToolManager->SetControlView(this);

	for (int i = 0; i < OBJECT_TAG_MAX; ++i)
	{
		m_objectTag.InsertString(i, g_objectTagName[i].c_str());
	}

	auto& materials = ResourceManager::GetInstance()->GetAllResource<Material>();
	for (auto& mtrl : materials)
	{
		auto inputLayout = ((Material*)mtrl.second)->GetShader()->GetInputLayout();
		if(inputLayout == VERTEX_INPUT_LAYOUT::VERTEX_INPUT_LAYOUT_PARTICLE)
			continue;
		if (inputLayout == VERTEX_INPUT_LAYOUT::VERTEX_INPUT_LAYOUT_SKYBOX)
			continue;
		m_materialList.AddString(mtrl.first.c_str());
	}

	auto& meshes = ResourceManager::GetInstance()->GetAllResource<Mesh>();
	for (auto& mesh : meshes)
	{
		m_meshList.AddString(mesh.first.c_str());
	}


	//
}


#ifdef _DEBUG
void Nalmak3D_MapControlView::AssertValid() const
{
	CFormView::AssertValid();
}

#ifndef _WIN32_WCE
void Nalmak3D_MapControlView::Dump(CDumpContext& dc) const
{
	CFormView::Dump(dc);
}
#endif
#endif //_DEBUG


// Nalmak3D_MapControlView 메시지 처리기입니다.


void Nalmak3D_MapControlView::UpdateObjectInfo(GameObject* _selectedObj)
{
	Material* mtrl = _selectedObj->GetComponent<MeshRenderer>()->GetMaterial();
	if (mtrl)
	{
		CString str;
		str = mtrl->GetName().c_str();
		m_materialName.SetWindowTextW(str);
	}
	{
		CString str;
		str = _selectedObj->GetName().c_str();
		m_objectName.SetWindowTextW(str);
	}
	{
		CString str;
		str = _selectedObj->GetComponent<MeshRenderer>()->GetMesh()->GetName().c_str();
		m_meshName.SetWindowTextW(str);
	}
	{
		CString str;
		str = _selectedObj->GetComponent<MeshRenderer>()->GetMaterial()->GetShader()->GetName().c_str();
		m_shaderName.SetWindowTextW(str);
	}
	Transform* trs = _selectedObj->GetTransform();
	MFC_Utility::SetEditBoxFloat(&m_positionX, trs->position.x);
	MFC_Utility::SetEditBoxFloat(&m_positionY, trs->position.y);
	MFC_Utility::SetEditBoxFloat(&m_positionZ, trs->position.z);

	Quaternion quaternion = trs->rotation;
	Vector3 rot = Nalmak_Math::QuaternionToEuler(quaternion);
	MFC_Utility::SetEditBoxFloat(&m_rotationX, rot.x);
	MFC_Utility::SetEditBoxFloat(&m_rotationY, rot.y);
	MFC_Utility::SetEditBoxFloat(&m_rotationZ, rot.z);

	MFC_Utility::SetEditBoxFloat(&m_scaleX, trs->scale.x);
	MFC_Utility::SetEditBoxFloat(&m_scaleY, trs->scale.y);
	MFC_Utility::SetEditBoxFloat(&m_scaleZ, trs->scale.z);
}

void Nalmak3D_MapControlView::OnLbnSelchangeObjectList()
{
	int objectIndex = m_objectList.GetCurSel();

	if (-1 == objectIndex)
		return;

	m_mapToolManager->SeleteObject(objectIndex);
}


void Nalmak3D_MapControlView::OnBnClickedButtonCreateObject()
{
	auto newObj = INSTANTIATE()->AddComponent<MeshRenderer>();
	m_mapToolManager->CreateObject(newObj);
	m_objectList.AddString(newObj->GetName().c_str());


	m_mapToolManager->SelectObject(newObj);
}


void Nalmak3D_MapControlView::OnBnClickedButtonDeleteObject()
{
	int objectIndex = m_objectList.GetCurSel();

	if (-1 == objectIndex)
		return;

	m_objectList.DeleteString(objectIndex);
	m_mapToolManager->DeleteObject(objectIndex);

}


void Nalmak3D_MapControlView::OnCbnSelchangeComboObjectTag()
{
}


void Nalmak3D_MapControlView::OnBnClickedButtonSave()
{
}


void Nalmak3D_MapControlView::OnBnClickedButtonLoad()
{
}


void Nalmak3D_MapControlView::OnBnClickedButtonSaveAll()
{
}


void Nalmak3D_MapControlView::OnBnClickedButtonLoadAll()
{
}


void Nalmak3D_MapControlView::OnEnChangeEditObjectName()
{
	
}


void Nalmak3D_MapControlView::OnEnChangeEditPositionX()
{
	auto obj = m_mapToolManager->GetSelectedObject();
	if (!obj)
		return;

	GetFloatByEditBox(obj->GetTransform()->position.x, IDC_EDIT1);
}


void Nalmak3D_MapControlView::OnEnChangeEditPositionY()
{
	auto obj = m_mapToolManager->GetSelectedObject();
	if (!obj)
		return;

	GetFloatByEditBox(obj->GetTransform()->position.y, IDC_EDIT2);
}


void Nalmak3D_MapControlView::OnEnChangeEditPositionZ()
{
	auto obj = m_mapToolManager->GetSelectedObject();
	if (!obj)
		return;

	GetFloatByEditBox(obj->GetTransform()->position.z, IDC_EDIT3);
}


void Nalmak3D_MapControlView::OnEnChangeEditRotationX()
{
	auto obj = m_mapToolManager->GetSelectedObject();
	if (!obj)
		return;

	Quaternion rot;
	GetFloatByEditBox(rot.x, IDC_EDIT4);
	GetFloatByEditBox(rot.y, IDC_EDIT5);
	GetFloatByEditBox(rot.z, IDC_EDIT6);
	D3DXQuaternionRotationYawPitchRoll(&rot, rot.y * Deg2Rad, rot.x * Deg2Rad, rot.z * Deg2Rad);

	obj->GetTransform()->rotation = rot;

}


void Nalmak3D_MapControlView::OnEnChangeEditRotationY()
{
	auto obj = m_mapToolManager->GetSelectedObject();
	if (!obj)
		return;

	Quaternion rot;
	GetFloatByEditBox(rot.x, IDC_EDIT4);
	GetFloatByEditBox(rot.y, IDC_EDIT5);
	GetFloatByEditBox(rot.z, IDC_EDIT6);
	D3DXQuaternionRotationYawPitchRoll(&rot, rot.y * Deg2Rad, rot.x * Deg2Rad, rot.z * Deg2Rad);

	obj->GetTransform()->rotation = rot;
}


void Nalmak3D_MapControlView::OnEnChangeEditRotationZ()
{
	auto obj = m_mapToolManager->GetSelectedObject();
	if (!obj)
		return;

	Quaternion rot;
	GetFloatByEditBox(rot.x, IDC_EDIT4);
	GetFloatByEditBox(rot.y, IDC_EDIT5);
	GetFloatByEditBox(rot.z, IDC_EDIT6);
	D3DXQuaternionRotationYawPitchRoll(&rot, rot.y * Deg2Rad, rot.x * Deg2Rad, rot.z * Deg2Rad);

	obj->GetTransform()->rotation = rot;
}


void Nalmak3D_MapControlView::OnEnChangeEditScaleX()
{
	auto obj = m_mapToolManager->GetSelectedObject();
	if (!obj)
		return;

	GetFloatByEditBox(obj->GetTransform()->scale.x, IDC_EDIT7);
}


void Nalmak3D_MapControlView::OnEnChangeEditScaleY()
{
	auto obj = m_mapToolManager->GetSelectedObject();
	if (!obj)
		return;

	GetFloatByEditBox(obj->GetTransform()->scale.y, IDC_EDIT8);
}


void Nalmak3D_MapControlView::OnEnChangeEditScaleZ()
{
	auto obj = m_mapToolManager->GetSelectedObject();
	if (!obj)
		return;

	GetFloatByEditBox(obj->GetTransform()->scale.z, IDC_EDIT9);
}


void Nalmak3D_MapControlView::OnEnChangeEditMaterialName()
{
	
}


void Nalmak3D_MapControlView::OnEnChangeEditMeshName()
{
	
}



void Nalmak3D_MapControlView::OnLbnDblclkListMaterial()
{
	auto obj = m_mapToolManager->GetSelectedObject();
	if (!obj)
		return;

	int index = m_materialList.GetCurSel();
	if (index == -1)
		return;

	CString mtrlName;
	m_materialList.GetText(index, mtrlName);

	obj->GetComponent<MeshRenderer>()->SetMaterial(mtrlName.GetString());
	m_materialName.SetWindowTextW(mtrlName);

	UpdateObjectInfo(obj);
}


void Nalmak3D_MapControlView::OnLbnDblclkListMesh()
{
	auto obj = m_mapToolManager->GetSelectedObject();
	if (!obj)
		return;

	int index = m_meshList.GetCurSel();
	if (index == -1)
		return;

	CString meshName;
	m_meshList.GetText(index, meshName);

	obj->GetComponent<MeshRenderer>()->SetMesh(meshName.GetString());
	m_meshName.SetWindowTextW(meshName);

	UpdateObjectInfo(obj);
}
