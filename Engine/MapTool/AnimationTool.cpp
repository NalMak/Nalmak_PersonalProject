// AnimationTool.cpp : ���� �����Դϴ�.
//

#include "stdafx.h"
#include "Nalmak3D_MapTool.h"
#include "AnimationTool.h"
#include "afxdialogex.h"


// AnimationTool ��ȭ �����Դϴ�.

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


// AnimationTool �޽��� ó�����Դϴ�.


void AnimationTool::OnCbnSelchangeComboSceneName()
{
	// TODO: ���⿡ ��Ʈ�� �˸� ó���� �ڵ带 �߰��մϴ�.
}


void AnimationTool::OnLbnSelchangeMeshList()
{
	// TODO: ���⿡ ��Ʈ�� �˸� ó���� �ڵ带 �߰��մϴ�.
}


void AnimationTool::OnLbnSelchangeAnimationList()
{
	// TODO: ���⿡ ��Ʈ�� �˸� ó���� �ڵ带 �߰��մϴ�.
}


void AnimationTool::OnTvnSelchangedBoneTree(NMHDR *pNMHDR, LRESULT *pResult)
{
	LPNMTREEVIEW pNMTreeView = reinterpret_cast<LPNMTREEVIEW>(pNMHDR);
	// TODO: ���⿡ ��Ʈ�� �˸� ó���� �ڵ带 �߰��մϴ�.
	*pResult = 0;
}


void AnimationTool::OnLbnSelchangeAnimPlayList()
{
	// TODO: ���⿡ ��Ʈ�� �˸� ó���� �ڵ带 �߰��մϴ�.
}


void AnimationTool::OnBnClickedPlayAnimation()
{
	// TODO: ���⿡ ��Ʈ�� �˸� ó���� �ڵ带 �߰��մϴ�.
}


void AnimationTool::OnBnClickedPlayAnimationAll()
{
	// TODO: ���⿡ ��Ʈ�� �˸� ó���� �ڵ带 �߰��մϴ�.
}


void AnimationTool::OnBnClickedStopAnimation()
{
	// TODO: ���⿡ ��Ʈ�� �˸� ó���� �ڵ带 �߰��մϴ�.
}


void AnimationTool::OnBnClickedCheckAnimationLoop()
{
	// TODO: ���⿡ ��Ʈ�� �˸� ó���� �ڵ带 �߰��մϴ�.
}


void AnimationTool::OnBnClickedAddAnimation()
{
	// TODO: ���⿡ ��Ʈ�� �˸� ó���� �ڵ带 �߰��մϴ�.
}


void AnimationTool::OnBnClickedDeleteAnimation()
{
	// TODO: ���⿡ ��Ʈ�� �˸� ó���� �ڵ带 �߰��մϴ�.
}


void AnimationTool::OnBnClickedClearAnimation()
{
	// TODO: ���⿡ ��Ʈ�� �˸� ó���� �ڵ带 �߰��մϴ�.
}


void AnimationTool::OnCbnSelchangeFirstAnimation()
{
	// TODO: ���⿡ ��Ʈ�� �˸� ó���� �ڵ带 �߰��մϴ�.
}


void AnimationTool::OnCbnSelchangeSecondAnimation()
{
	// TODO: ���⿡ ��Ʈ�� �˸� ó���� �ڵ带 �߰��մϴ�.
}


void AnimationTool::OnEnChangeFirstAnimationSpeed()
{
	// TODO:  RICHEDIT ��Ʈ���� ���, �� ��Ʈ����
	// CDialogEx::OnInitDialog() �Լ��� ������ 
	//�ϰ� ����ũ�� OR �����Ͽ� ������ ENM_CHANGE �÷��׸� �����Ͽ� CRichEditCtrl().SetEventMask()�� ȣ������ ������
	// �� �˸� �޽����� ������ �ʽ��ϴ�.

	// TODO:  ���⿡ ��Ʈ�� �˸� ó���� �ڵ带 �߰��մϴ�.
}


void AnimationTool::OnEnChangeSecondAnimationSpeed()
{
	// TODO:  RICHEDIT ��Ʈ���� ���, �� ��Ʈ����
	// CDialogEx::OnInitDialog() �Լ��� ������ 
	//�ϰ� ����ũ�� OR �����Ͽ� ������ ENM_CHANGE �÷��׸� �����Ͽ� CRichEditCtrl().SetEventMask()�� ȣ������ ������
	// �� �˸� �޽����� ������ �ʽ��ϴ�.

	// TODO:  ���⿡ ��Ʈ�� �˸� ó���� �ڵ带 �߰��մϴ�.
}


void AnimationTool::OnEnChangeEditTransitionTime()
{
	// TODO:  RICHEDIT ��Ʈ���� ���, �� ��Ʈ����
	// CDialogEx::OnInitDialog() �Լ��� ������ 
	//�ϰ� ����ũ�� OR �����Ͽ� ������ ENM_CHANGE �÷��׸� �����Ͽ� CRichEditCtrl().SetEventMask()�� ȣ������ ������
	// �� �˸� �޽����� ������ �ʽ��ϴ�.

	// TODO:  ���⿡ ��Ʈ�� �˸� ó���� �ڵ带 �߰��մϴ�.
}


void AnimationTool::OnEnChangeEditAnimationWeight()
{
	// TODO:  RICHEDIT ��Ʈ���� ���, �� ��Ʈ����
	// CDialogEx::OnInitDialog() �Լ��� ������ 
	//�ϰ� ����ũ�� OR �����Ͽ� ������ ENM_CHANGE �÷��׸� �����Ͽ� CRichEditCtrl().SetEventMask()�� ȣ������ ������
	// �� �˸� �޽����� ������ �ʽ��ϴ�.

	// TODO:  ���⿡ ��Ʈ�� �˸� ó���� �ڵ带 �߰��մϴ�.
}
