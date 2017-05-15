#pragma once

#include "BtnST.h"
#include "VLabel.h"
// CDialog_Door_Open 대화 상자입니다.
#define TIM_DOOR_OPEN	1000
class CDialog_Door_Open : public CDialog
{
	DECLARE_DYNAMIC(CDialog_Door_Open)
public:
	CVLabel				m_msgTopDoor[6];
	CVLabel				m_msgBottomDoor[5];

	CBitmap				m_bmGround;
public:
	CDialog_Door_Open(CWnd* pParent = NULL);   // 표준 생성자입니다.
	virtual ~CDialog_Door_Open();

	int	nDoorOpenBack[12];

	void OnInitButton();
	void OnInitLabel();

	void OnDoorOpenCheck();
// 대화 상자 데이터입니다.
	enum { IDD = IDD_DIALOG_DOOR };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 지원입니다.

	DECLARE_MESSAGE_MAP()
public:
	afx_msg void OnTimer(UINT_PTR nIDEvent);
	afx_msg void OnDestroy();
	afx_msg void OnBnClickedDialogDoorOpen();
	afx_msg void OnBnClickedDialogDoorClose();
	afx_msg void OnBnClickedDialogDoorExit();
	virtual BOOL OnInitDialog();

	CButtonST m_btnDoorOpen;
	CButtonST m_btnDoorClose;
	CButtonST m_btnDoorExit;
	afx_msg BOOL OnEraseBkgnd(CDC* pDC);
};
