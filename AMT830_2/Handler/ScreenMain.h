#pragma once

#include ".\\Controls\\Picture.h"  // �̹��� �ε� Ŭ����
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
#include "GradientStatic.h"
#include "MyBasicData.h"

// CScreenMain �� ���Դϴ�.

class CScreenMain : public CFormView
{
	DECLARE_DYNCREATE(CScreenMain)

public:
	int						m_nTime;


public:
	CScreenMain();           // ���� ����⿡ ���Ǵ� protected �������Դϴ�.
	virtual ~CScreenMain();

public:
	enum { IDD = IDD_SCREEN_MAIN };
#ifdef _DEBUG
	virtual void AssertValid() const;
#ifndef _WIN32_WCE
	virtual void Dump(CDumpContext& dc) const;
#endif
#endif

public:
	CXPGroupBox			m_groupTimeInfo;
	CXPGroupBox			m_groupWorkInfo;

	CGridCtrl			m_pGridWorkInfoC;
	CGridCtrl			m_pGridWorkInfoN;
	CGridCtrl			m_pGridTimeInfo;


	CImageList			*m_pImagelist;

	CBitmap				m_bmGround;

	DWORD				m_dwAnimateWaitTime[3];

	// jtkim 20150316
	void				OnMainCountDisplay();
	void				OnMainTimeDisplay();
	void				OnInitButton();
	void				OnInitGroupBox();
	void				OnInitLabel();
	void				OnInitDigit();
	void				OnInitGridWorkInfoCurr();
	void				OnInitGridWorkInfoNext();
	void				OnInitGridTimeInfo(int nMode);
	void				OnMainDisplay();

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV �����Դϴ�.

	DECLARE_MESSAGE_MAP()
public:
	virtual void OnInitialUpdate();
	virtual BOOL DestroyWindow();
	afx_msg BOOL OnEraseBkgnd(CDC* pDC);
	afx_msg void OnPaint();
	afx_msg LRESULT OnMainWorkInfoDisplay(WPARAM wParam, LPARAM lParam);  // ȭ�� ������ ���ſ� ����� �޽���
	afx_msg LRESULT	OnMainWorkInfoCommand(WPARAM wParam, LPARAM lParam);  // ȭ�� ������ ���ſ� ����� �޽���
	afx_msg void OnTimer(UINT_PTR nIDEvent);
	afx_msg void OnShowWindow(BOOL bShow, UINT nStatus);
	virtual void PostNcDestroy();
	afx_msg void OnDestroy();
	afx_msg void OnClickedBtnMainAnimate();
	afx_msg void OnClickedBtnMainData();
	afx_msg void OnBnClickedButtonTrackOut();
	afx_msg void OnTimeCellClick(NMHDR *pNotifyStruct, LRESULT* pResult);
	afx_msg void OnWorkInfoCurrCellClick(NMHDR *pNotifyStruct, LRESULT* pResult);
};


