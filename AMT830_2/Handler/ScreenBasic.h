#pragma once



// CScreenBasic �� ���Դϴ�.

#include "Variable.h"
#include "XPGroupBox.h"
#include ".\\Union\\Grid\\GridCtrl.h"
#include ".\\Union\\Grid\\GridURLCell.h"
#include ".\\Union\\Grid\\GridCellCombo.h"
#include ".\\Union\\Grid\\GridCellCheck.h"
#include ".\\Union\\Grid\\GridCellNumeric.h"
#include ".\\Union\\Grid\\GridCellDateTime.h"
#include "BtnST.h"
#include "GradientStatic.h"
#include "Digit.h"

class CScreenBasic : public CFormView
{
	DECLARE_DYNCREATE(CScreenBasic)

public:
	int					m_nDeviceName;					// ���õ� ����̽��� ����Ʈ ��ġ ���� ����
	int					m_nOldDeviceName;
	int					m_nModeDevice[2];
	int					m_nModeInterface[2];
	int					m_nModeSecsGem[2];
	int					m_nModeWork[2];
	int					m_nModeFrontSmema[2];
	int					m_nModeRearSmema[2];
	int					m_nModeRfid[2];
	                

	CString				m_strTempDevice;				// ���õ� ����̽� ���� �ӽ� ���� ����
	CString				m_strLoadFile;					// �ε��� ���Ͽ� ���� [����]+[���ϸ�] ���� ����
	CString				m_strDeviceName[2];
	CString				m_strModelName[2];

	CButtonST			m_btnModelCreate;
	CButtonST			m_btnModelDelete;
	CButtonST			m_btnApply;
	CButtonST			m_btnReLoad;


	CXPGroupBox			m_groupModelInfo;
	CXPGroupBox			m_groupDeviceMode;

	CXPGroupBox			m_groupProcess;

	CGridCtrl			m_pGridDevice;
	CGridCtrl			m_pGridModel;
	CGridCtrl			m_pGridHifix;


	void				OnInitGroupBox();
	void				OnInitLabel();
	void				OnInitButton();
	void				OnInitDigit();
	void				OnInitGridDeviceMode();
	void				OnInitGridModelList();
	void				OnDataHistoryLog();
	void				OnDeviceColorChange(int nSelectRow, int nSelectCol);
	void				OnDataRecovery();
	int					OnDataComparison();
	void				OnDataApply();
	void				OnDataBackup();
	void				OnDataInit();
	int					OnInitModelList(CString strFileName);
	int					OnAddItem(int nIndex, WIN32_FIND_DATA *pFd);
	void				OnDisplayModelList(int nMode, int nCount, CString strFileName);
	bool				OnModelDeviceCheck(CString strFileName);
	bool				OnModelCreateDeviceCheck(CString strFileName);

public:
	CScreenBasic();           // ���� ����⿡ ���Ǵ� protected �������Դϴ�.
	virtual ~CScreenBasic();

public:
	enum { IDD = IDD_SCREEN_BASIC };
#ifdef _DEBUG
	virtual void AssertValid() const;
#ifndef _WIN32_WCE
	virtual void Dump(CDumpContext& dc) const;
#endif
#endif

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV �����Դϴ�.

	DECLARE_MESSAGE_MAP()
public:
	virtual void OnInitialUpdate();
	virtual BOOL DestroyWindow();
	afx_msg void OnDeviceCellClick(NMHDR *pNotifyStruct, LRESULT* pResult);
	//afx_msg void OnWorkModeCellClick(NMHDR *pNotifyStruct, LRESULT* pResult);
	afx_msg void OnModelCellClick(NMHDR *pNotifyStruct, LRESULT* pResult);
	afx_msg void OnModelCellRClick(NMHDR *pNotifyStruct, LRESULT* pResult);
	afx_msg void OnClickedBtnModelCreate();
	afx_msg void OnClickedBtnModelDelete();
	afx_msg void OnClickedBtnReload();
	afx_msg void OnClickedBtnApply();
	afx_msg BOOL OnEraseBkgnd(CDC* pDC);
	virtual void PostNcDestroy();
	afx_msg void OnDestroy();
	afx_msg HBRUSH OnCtlColor(CDC* pDC, CWnd* pWnd, UINT nCtlColor);
	afx_msg void OnTimer(UINT_PTR nIDEvent);
};


