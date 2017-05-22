#pragma once

#include "XPGroupBox.h"
#include "xShadeButton.h"	// ���� ��ư ���� Ŭ���� �߰�
#include ".\\Union\\Grid\\GridCtrl.h"
#include ".\\Union\\Grid\\GridURLCell.h"
#include ".\\Union\\Grid\\GridCellCombo.h"
#include ".\\Union\\Grid\\GridCellCheck.h"
#include ".\\Union\\Grid\\GridCellNumeric.h"
#include ".\\Union\\Grid\\GridCellDateTime.h"
#include "Digit.h"
#include "BtnST.h"
#include "Variable.h"
#include "GradientStatic.h"
// CDialogManualIO ��ȭ �����Դϴ�.

class CDialogManualIO : public CDialog
{
	DECLARE_DYNAMIC(CDialogManualIO)

public:
	CButtonST		m_btnExit;
	CButtonST		m_btnDoor;
	int				m_nTsiteNum;

	CBitmap			m_bmGround;
	DWORD			m_dwWaitTime[3];
	BOOL			Create();
	
	void			OnInitButton();
public:
	CDialogManualIO(CWnd* pParent = NULL);   // ǥ�� �������Դϴ�.
	virtual ~CDialogManualIO();

// ��ȭ ���� �������Դϴ�.
	enum { IDD = IDD_DIALOG_MANUAL_IO };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV �����Դϴ�.

	DECLARE_MESSAGE_MAP()
public:
	afx_msg BOOL OnEraseBkgnd(CDC* pDC);
	virtual BOOL DestroyWindow();
	virtual BOOL OnInitDialog();
	afx_msg void OnTimer(UINT_PTR nIDEvent);
	afx_msg void OnBnClickedBtnExit();
	afx_msg void OnBnClickedBtnRefresh();

};
