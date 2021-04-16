// AnimationTool.cpp : 구현 파일입니다.
//

#include "stdafx.h"
#include "Nalmak3D_MapTool.h"
#include "AnimationTool.h"
#include "afxdialogex.h"


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
END_MESSAGE_MAP()


// AnimationTool 메시지 처리기입니다.


void AnimationTool::OnCbnSelchangeComboSceneName()
{
	// TODO: 여기에 컨트롤 알림 처리기 코드를 추가합니다.
}


void AnimationTool::OnLbnSelchangeMeshList()
{
	// TODO: 여기에 컨트롤 알림 처리기 코드를 추가합니다.
}


void AnimationTool::OnLbnSelchangeAnimationList()
{
	// TODO: 여기에 컨트롤 알림 처리기 코드를 추가합니다.
}


void AnimationTool::OnTvnSelchangedBoneTree(NMHDR *pNMHDR, LRESULT *pResult)
{
	LPNMTREEVIEW pNMTreeView = reinterpret_cast<LPNMTREEVIEW>(pNMHDR);
	// TODO: 여기에 컨트롤 알림 처리기 코드를 추가합니다.
	*pResult = 0;
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
