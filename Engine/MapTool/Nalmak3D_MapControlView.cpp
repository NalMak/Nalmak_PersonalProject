// Nalmak3D_MapControlView.cpp : 구현 파일입니다.
//

#include "stdafx.h"
#include "Nalmak3D_MapTool.h"
#include "Nalmak3D_MapControlView.h"
#include "MapToolManager.h"
#include "MFC_Utility.h"
#include "GameObject.h"
#include "Material.h"

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
	DDX_Control(pDX, IDC_EDIT11, m_meshName);
	DDX_Control(pDX, IDC_EDIT13, m_shaderName);
	DDX_Control(pDX, IDC_EDIT14, m_subSetCount);
	DDX_Control(pDX, IDC_LIST4, m_materialRenderList);
	DDX_Control(pDX, IDC_EDIT15, m_renderMaterialCount);
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
	ON_LBN_DBLCLK(IDC_LIST3, &Nalmak3D_MapControlView::OnLbnDblclkListMesh)
	ON_BN_CLICKED(IDC_BUTTON7, &Nalmak3D_MapControlView::OnBnClickedButtonAddRenderMaterial)
	ON_BN_CLICKED(IDC_BUTTON8, &Nalmak3D_MapControlView::OnBnClickedButtonDeleteRenderMaterial)
	ON_LBN_SELCHANGE(IDC_LIST2, &Nalmak3D_MapControlView::OnLbnSelchangeListMaterial)
	ON_BN_CLICKED(IDC_BUTTON9, &Nalmak3D_MapControlView::OnBnClickedButtonMaterialChange)
	ON_LBN_DBLCLK(IDC_LIST2, &Nalmak3D_MapControlView::OnLbnDblclkListMaterialList)
	ON_EN_SETFOCUS(IDC_EDIT4, &Nalmak3D_MapControlView::OnEnSetfocusRotX)
	ON_EN_KILLFOCUS(IDC_EDIT4, &Nalmak3D_MapControlView::OnEnKillfocusRotX)
	ON_EN_SETFOCUS(IDC_EDIT5, &Nalmak3D_MapControlView::OnEnSetfocusRotY)
	ON_EN_KILLFOCUS(IDC_EDIT5, &Nalmak3D_MapControlView::OnEnKillfocusRotY)
	ON_EN_SETFOCUS(IDC_EDIT6, &Nalmak3D_MapControlView::OnEnSetfocusRotZ)
	ON_EN_KILLFOCUS(IDC_EDIT6, &Nalmak3D_MapControlView::OnEnKillfocusEditRotZ)
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


void Nalmak3D_MapControlView::UpdateObjectInfo(GameObject* _selectedObj, int _index)
{
	m_objectList.SetCurSel(_index);

	auto renderer = _selectedObj->GetComponent<MeshRenderer>();
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
		MFC_Utility::SetEditBoxInt(&m_renderMaterialCount, renderer->GetMaterialCount());
	}
	{
		CString str;
		str = _selectedObj->GetName().c_str();
		m_objectName.SetWindowTextW(str);
	}
	{
		CString str;
		str = renderer->GetMesh()->GetName().c_str();
		m_meshName.SetWindowTextW(str);
	}
	{
		unsigned long index = renderer->GetMesh()->GetSubsetCount();
		MFC_Utility::SetEditBoxInt(&m_subSetCount, index);
	}
	{
		m_objectTag.SetCurSel(_selectedObj->GetTag());
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

void Nalmak3D_MapControlView::UpdateObjectTransformInfo(GameObject * _obj)
{
	Transform* trs = _obj->GetTransform();
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
	m_objectList.InsertString(m_objectList.GetCount(), newObj->GetName().c_str());
	int count = m_objectList.GetCount();
	m_objectList.SetCurSel(count - 1);
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
	auto obj = m_mapToolManager->GetSelectedObject();
	if (!obj)
		return;

	int index = m_objectTag.GetCurSel();

	if (index != -1)
		obj->SetTag(index);

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

}


void Nalmak3D_MapControlView::OnEnChangeEditRotationY()
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
}


void Nalmak3D_MapControlView::OnEnChangeEditRotationZ()
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


//
//void Nalmak3D_MapControlView::OnLbnDblclkListMaterial()
//{
//	auto obj = m_mapToolManager->GetSelectedObject();
//	if (!obj)
//		return;
//
//	int index = m_materialList.GetCurSel();
//	if (index == -1)
//		return;
//
//	CString mtrlName;
//	m_materialList.GetText(index, mtrlName);
//
//	obj->GetComponent<MeshRenderer>()->SetMaterial(mtrlName.GetString());
//	m_materialName.SetWindowTextW(mtrlName);
//
//	UpdateObjectInfo(obj);
//}


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
	MFC_Utility::SetEditBoxInt(&m_subSetCount, obj->GetComponent<MeshRenderer>()->GetMesh()->GetSubsetCount());

	UpdateObjectInfo(obj, m_objectList.GetCurSel());
}


void Nalmak3D_MapControlView::OnBnClickedButtonAddRenderMaterial()
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
	m_materialRenderList.InsertString(m_materialRenderList.GetSelCount(),mtrlName);
	MFC_Utility::SetEditBoxInt(&m_renderMaterialCount, render->GetMaterialCount());
}


void Nalmak3D_MapControlView::OnBnClickedButtonDeleteRenderMaterial()
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
		MFC_Utility::SetEditBoxInt(&m_renderMaterialCount, render->GetMaterialCount());
		
	}
	// TODO: 여기에 컨트롤 알림 처리기 코드를 추가합니다.
}


void Nalmak3D_MapControlView::OnLbnSelchangeListMaterial()
{
	int index = m_materialList.GetCurSel();
	if (index == -1)
		return;

	CString mtrlName;
	m_materialList.GetText(index, mtrlName);

	Material* mtrl = ResourceManager::GetInstance()->GetResource<Material>(mtrlName.GetString());

	m_shaderName.SetWindowTextW(mtrl->GetShader()->GetName().c_str());

}


void Nalmak3D_MapControlView::OnBnClickedButtonMaterialChange()
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


void Nalmak3D_MapControlView::OnLbnDblclkListMaterialList()
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


void Nalmak3D_MapControlView::OnEnSetfocusRotX()
{
	m_isFocusRotation = true;
	// TODO: 여기에 컨트롤 알림 처리기 코드를 추가합니다.
}


void Nalmak3D_MapControlView::OnEnKillfocusRotX()
{
	m_isFocusRotation = false;

	// TODO: 여기에 컨트롤 알림 처리기 코드를 추가합니다.
}


void Nalmak3D_MapControlView::OnEnSetfocusRotY()
{
	m_isFocusRotation = true;

	// TODO: 여기에 컨트롤 알림 처리기 코드를 추가합니다.
}


void Nalmak3D_MapControlView::OnEnKillfocusRotY()
{
	m_isFocusRotation = false;

	// TODO: 여기에 컨트롤 알림 처리기 코드를 추가합니다.
}


void Nalmak3D_MapControlView::OnEnSetfocusRotZ()
{
	m_isFocusRotation = true;
	// TODO: 여기에 컨트롤 알림 처리기 코드를 추가합니다.
}


void Nalmak3D_MapControlView::OnEnKillfocusEditRotZ()
{
	m_isFocusRotation = false;

	// TODO: 여기에 컨트롤 알림 처리기 코드를 추가합니다.
}
