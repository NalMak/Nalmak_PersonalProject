#pragma once
#include "afxwin.h"
#include "afxcmn.h"


// AnimationTool 대화 상자입니다.

class AnimationTool : public CDialogEx
{
	DECLARE_DYNAMIC(AnimationTool)

public:
	AnimationTool(CWnd* pParent = NULL);   // 표준 생성자입니다.
	virtual ~AnimationTool();

// 대화 상자 데이터입니다.
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_DIALOG3 };
#endif

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 지원입니다.

	DECLARE_MESSAGE_MAP()
private:
	void SearchFrame(Nalmak_Frame* _frame, HTREEITEM _item);
public:
	virtual BOOL OnInitDialog();
	afx_msg void OnCbnSelchangeComboSceneName();
	CComboBox m_sceneName;
	CListBox m_meshList;
	afx_msg void OnLbnSelchangeMeshList();
	CListBox m_animationList;
	afx_msg void OnLbnSelchangeAnimationList();
	CTreeCtrl m_boneList;
	afx_msg void OnTvnSelchangedBoneTree(NMHDR *pNMHDR, LRESULT *pResult);
	CListBox m_animationPlayList;
	afx_msg void OnLbnSelchangeAnimPlayList();
	afx_msg void OnBnClickedPlayAnimation();
	afx_msg void OnBnClickedPlayAnimationAll();
	afx_msg void OnBnClickedStopAnimation();
	afx_msg void OnBnClickedCheckAnimationLoop();
	CButton m_animationLoop;
	afx_msg void OnBnClickedAddAnimation();
	afx_msg void OnBnClickedDeleteAnimation();
	afx_msg void OnBnClickedClearAnimation();
	afx_msg void OnCbnSelchangeFirstAnimation();
	afx_msg void OnCbnSelchangeSecondAnimation();
	CComboBox m_firstAnimationName;
	CComboBox m_secondAnimationName;
	afx_msg void OnEnChangeFirstAnimationSpeed();
	afx_msg void OnEnChangeSecondAnimationSpeed();
	CEdit m_firstAnimationSpeed;
	afx_msg void OnEnChangeEditTransitionTime();
	CEdit m_transitionTime;
	afx_msg void OnEnChangeEditAnimationWeight();
	CEdit m_animationWeight;

	afx_msg void OnEnChangeEditScale();
	CEdit m_scale;

};
