// AnimationTool.cpp : 구현 파일입니다.
//

#include "stdafx.h"
#include "Nalmak3D_MapTool.h"
#include "AnimationTool.h"
#include "afxdialogex.h"
#include "MapToolManager.h"
#include "MFC_Utility.h"
#include "XFileMesh.h"
#include "Mesh.h"
#include "AnimationController.h"
#include "Nalmak_Animation.h"
// AnimationTool 대화 상자입니다.

IMPLEMENT_DYNAMIC(AnimationTool, CDialogEx)

AnimationTool::AnimationTool(CWnd* pParent /*=NULL*/)
	: CDialogEx(IDD_DIALOG3, pParent)
{

}

AnimationTool::~AnimationTool()
{
}

void AnimationTool::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_COMBO2, m_sceneName);
	DDX_Control(pDX, IDC_LIST1, m_meshList);
	DDX_Control(pDX, IDC_LIST3, m_animationList);
	DDX_Control(pDX, IDC_TREE1, m_boneList);
	DDX_Control(pDX, IDC_LIST2, m_animationPlayList);
	DDX_Control(pDX, IDC_CHECK1, m_animationLoop);
	DDX_Control(pDX, IDC_COMBO1, m_firstAnimationName);
	DDX_Control(pDX, IDC_COMBO5, m_secondAnimationName);
	DDX_Control(pDX, IDC_EDIT2, m_firstAnimationSpeed);
	DDX_Control(pDX, IDC_EDIT4, m_transitionTime);
	DDX_Control(pDX, IDC_EDIT5, m_animationWeight);
	DDX_Control(pDX, IDC_EDIT1, m_scale);
}


BEGIN_MESSAGE_MAP(AnimationTool, CDialogEx)
	ON_CBN_SELCHANGE(IDC_COMBO2, &AnimationTool::OnCbnSelchangeComboSceneName)
	ON_LBN_SELCHANGE(IDC_LIST1, &AnimationTool::OnLbnSelchangeMeshList)
	ON_LBN_SELCHANGE(IDC_LIST3, &AnimationTool::OnLbnSelchangeAnimationList)
	ON_NOTIFY(TVN_SELCHANGED, IDC_TREE1, &AnimationTool::OnTvnSelchangedBoneTree)
	ON_LBN_SELCHANGE(IDC_LIST2, &AnimationTool::OnLbnSelchangeAnimPlayList)
	ON_BN_CLICKED(IDC_BUTTON1, &AnimationTool::OnBnClickedPlayAnimation)
	ON_BN_CLICKED(IDC_BUTTON2, &AnimationTool::OnBnClickedPlayAnimationAll)
	ON_BN_CLICKED(IDC_BUTTON3, &AnimationTool::OnBnClickedStopAnimation)
	ON_BN_CLICKED(IDC_CHECK1, &AnimationTool::OnBnClickedCheckAnimationLoop)
	ON_BN_CLICKED(IDC_BUTTON4, &AnimationTool::OnBnClickedAddAnimation)
	ON_BN_CLICKED(IDC_BUTTON5, &AnimationTool::OnBnClickedDeleteAnimation)
	ON_BN_CLICKED(IDC_BUTTON6, &AnimationTool::OnBnClickedClearAnimation)
	ON_CBN_SELCHANGE(IDC_COMBO1, &AnimationTool::OnCbnSelchangeFirstAnimation)
	ON_CBN_SELCHANGE(IDC_COMBO5, &AnimationTool::OnCbnSelchangeSecondAnimation)
	ON_EN_CHANGE(IDC_EDIT2, &AnimationTool::OnEnChangeFirstAnimationSpeed)
	ON_EN_CHANGE(IDC_EDIT3, &AnimationTool::OnEnChangeSecondAnimationSpeed)
	ON_EN_CHANGE(IDC_EDIT4, &AnimationTool::OnEnChangeEditTransitionTime)
	ON_EN_CHANGE(IDC_EDIT5, &AnimationTool::OnEnChangeEditAnimationWeight)
	ON_EN_CHANGE(IDC_EDIT1, &AnimationTool::OnEnChangeEditScale)
END_MESSAGE_MAP()


BOOL AnimationTool::OnInitDialog()
{
	CDialogEx::OnInitDialog();


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
		m_sceneName.InsertString(i, sceneName.c_str());
		++i;
	}

	return TRUE;  // return TRUE unless you set the focus to a control
				  // 예외: OCX 속성 페이지는 FALSE를 반환해야 합니다.
}



void AnimationTool::OnCbnSelchangeComboSceneName()
{
	CString sceneName;
	m_sceneName.GetLBText(m_sceneName.GetCurSel(), sceneName);
	wstring path = ResourceManager::GetInstance()->GetResourceDirectoryPath();
	path += L"/" + sceneName;
	ResourceManager::GetInstance()->ReleaseSceneResouce();
	ResourceManager::GetInstance()->LoadAllResources(path, false);

	
	m_meshList.ResetContent();
	auto& meshes = ResourceManager::GetInstance()->GetAllResource<Mesh>();
	for (auto& mesh : meshes)
	{
		if(((Mesh*)(mesh.second))->GetMeshType() == MESH_TYPE_ANIMATION)
			m_meshList.AddString(mesh.first.c_str());
	}
}


void AnimationTool::OnLbnSelchangeMeshList()
{
	UINT index = m_meshList.GetCurSel();
	if (index == -1)
		return;
	CString name;
	m_meshList.GetText(index, name);

	MapToolManager::GetInstance()->SetAnimationObjectMesh(name.GetString());

	m_boneList.DeleteAllItems();

	XFileMesh* mesh = (XFileMesh*)ResourceManager::GetInstance()->GetResource<Mesh>(name.GetString());
	Nalmak_Frame* frame = (Nalmak_Frame*)mesh->GetRoot();


	m_animationList.ResetContent();
	for (UINT i = 0; i < mesh->GetAnimationController()->GetMaxNumAnimationSets(); ++i)
	{
		LPD3DXANIMATIONSET anim;
		mesh->GetAnimationController()->GetAnimationSet(i, &anim);
		wstring wName;
		wName = Nalmak_String::StringToWString(anim->GetName());
		m_animationList.AddString(wName.c_str());
	}

	SearchFrame(frame, nullptr);

	MFC_Utility::SetEditBoxFloat(&m_scale, 1);
	MapToolManager::GetInstance()->GetAnimationObject()->GetTransform()->SetScale(1, 1, 1);
}


void AnimationTool::OnLbnSelchangeAnimationList()
{
	UINT animIndex = m_animationList.GetCurSel();
	UINT index = m_meshList.GetCurSel();

	if (index == -1)
		return;
	if (animIndex == -1)
		return;

	CString name;
	m_meshList.GetText(index, name);

	XFileMesh* mesh = (XFileMesh*)ResourceManager::GetInstance()->GetResource<Mesh>(name.GetString());



	//MapToolManager::GetInstance()->GetAnimationObject()->GetComponent<AnimationController>()->Play();
	// TODO: 여기에 컨트롤 알림 처리기 코드를 추가합니다.
}


void AnimationTool::OnTvnSelchangedBoneTree(NMHDR *pNMHDR, LRESULT *pResult)
{
	LPNMTREEVIEW pNMTreeView = reinterpret_cast<LPNMTREEVIEW>(pNMHDR);

	
	// TODO: 여기에 컨트롤 알림 처리기 코드를 추가합니다.
	*pResult = 0;
}

void AnimationTool::SearchFrame(Nalmak_Frame * _frame, HTREEITEM _item)
{
	Nalmak_Frame* sibling = (Nalmak_Frame *)_frame->pFrameSibling;
	Nalmak_Frame* child = (Nalmak_Frame *)_frame->pFrameFirstChild;

	
	string name = "default";
	wstring wName;
	if (_frame->Name != nullptr)
		name = _frame->Name;
	wName = Nalmak_String::StringToWString(name);
	HTREEITEM childItem;
	if (_item)
		childItem = m_boneList.InsertItem(wName.c_str(),0,0, _item, TVI_LAST);
	else
		childItem = m_boneList.InsertItem(wName.c_str(),0,0, TVI_ROOT, TVI_LAST);

	if (sibling)
		SearchFrame(sibling, _item);
	if (child)
		SearchFrame(child, childItem);
}

void AnimationTool::OnLbnSelchangeAnimPlayList()
{
	// TODO: 여기에 컨트롤 알림 처리기 코드를 추가합니다.
}


void AnimationTool::OnBnClickedPlayAnimation()
{
	// TODO: 여기에 컨트롤 알림 처리기 코드를 추가합니다.
}


void AnimationTool::OnBnClickedPlayAnimationAll()
{
	// TODO: 여기에 컨트롤 알림 처리기 코드를 추가합니다.
}


void AnimationTool::OnBnClickedStopAnimation()
{
	// TODO: 여기에 컨트롤 알림 처리기 코드를 추가합니다.
}


void AnimationTool::OnBnClickedCheckAnimationLoop()
{
	int check = m_animationLoop.GetCheck();

	//MapToolManager::GetInstance()->GetAnimationObject()->GetComponent<AnimationController>()
	// TODO: 여기에 컨트롤 알림 처리기 코드를 추가합니다.
}


void AnimationTool::OnBnClickedAddAnimation()
{
	// TODO: 여기에 컨트롤 알림 처리기 코드를 추가합니다.
}


void AnimationTool::OnBnClickedDeleteAnimation()
{
	// TODO: 여기에 컨트롤 알림 처리기 코드를 추가합니다.
}


void AnimationTool::OnBnClickedClearAnimation()
{
	// TODO: 여기에 컨트롤 알림 처리기 코드를 추가합니다.
}


void AnimationTool::OnCbnSelchangeFirstAnimation()
{
	// TODO: 여기에 컨트롤 알림 처리기 코드를 추가합니다.
}


void AnimationTool::OnCbnSelchangeSecondAnimation()
{
	// TODO: 여기에 컨트롤 알림 처리기 코드를 추가합니다.
}


void AnimationTool::OnEnChangeFirstAnimationSpeed()
{
	// TODO:  RICHEDIT 컨트롤인 경우, 이 컨트롤은
	// CDialogEx::OnInitDialog() 함수를 재지정 
	//하고 마스크에 OR 연산하여 설정된 ENM_CHANGE 플래그를 지정하여 CRichEditCtrl().SetEventMask()를 호출하지 않으면
	// 이 알림 메시지를 보내지 않습니다.

	// TODO:  여기에 컨트롤 알림 처리기 코드를 추가합니다.
}


void AnimationTool::OnEnChangeSecondAnimationSpeed()
{
	// TODO:  RICHEDIT 컨트롤인 경우, 이 컨트롤은
	// CDialogEx::OnInitDialog() 함수를 재지정 
	//하고 마스크에 OR 연산하여 설정된 ENM_CHANGE 플래그를 지정하여 CRichEditCtrl().SetEventMask()를 호출하지 않으면
	// 이 알림 메시지를 보내지 않습니다.

	// TODO:  여기에 컨트롤 알림 처리기 코드를 추가합니다.
}


void AnimationTool::OnEnChangeEditTransitionTime()
{
	// TODO:  RICHEDIT 컨트롤인 경우, 이 컨트롤은
	// CDialogEx::OnInitDialog() 함수를 재지정 
	//하고 마스크에 OR 연산하여 설정된 ENM_CHANGE 플래그를 지정하여 CRichEditCtrl().SetEventMask()를 호출하지 않으면
	// 이 알림 메시지를 보내지 않습니다.

	// TODO:  여기에 컨트롤 알림 처리기 코드를 추가합니다.
}


void AnimationTool::OnEnChangeEditAnimationWeight()
{
	// TODO:  RICHEDIT 컨트롤인 경우, 이 컨트롤은
	// CDialogEx::OnInitDialog() 함수를 재지정 
	//하고 마스크에 OR 연산하여 설정된 ENM_CHANGE 플래그를 지정하여 CRichEditCtrl().SetEventMask()를 호출하지 않으면
	// 이 알림 메시지를 보내지 않습니다.

	// TODO:  여기에 컨트롤 알림 처리기 코드를 추가합니다.
}




void AnimationTool::OnEnChangeEditScale()
{
	float scale;
	GetFloatByEditBox(scale, IDC_EDIT1);
	
	MapToolManager::GetInstance()->GetAnimationObject()->GetTransform()->SetScale(scale, scale, scale);

}

