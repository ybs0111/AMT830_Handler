#pragma once



// CScreenBasic 폼 뷰입니다.

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
	int					m_nDeviceName;					// 선택된 디바이스의 리스트 위치 저장 변수
	int					m_nOldDeviceName;
	int					m_nModeDevice[2];
	int					m_nModeInterface[2];
	int					m_nModeSecsGem[2];
	int					m_nModeWork[2];
	int					m_nModeFrontSmema[2];
	int					m_nModeRearSmema[2];
	int					m_nModeRfid[2];

	//kwlee 2017.0523
	int                 m_nModeCapRemoveUse[2];
	int                 m_nModeSorterPickerUse[2];
	int                 m_nModeModuleDirCheck[2];
	int                 m_nModeHeatSinkDirCheck[2];

	int                 m_nPrinterVisionPapper[2];
	int                 m_nPrintBinPapper[2];
	int                 m_nLabelErrCnt[2];
	//////
	//kwlee 2017.0524
	int                 m_nRepickCnt[2];
	int                 m_nDeviceCnt[2];

	CString				m_strTempDevice;				// 선택된 디바이스 종류 임시 저장 변수
	CString				m_strLoadFile;					// 로딩할 파일에 대한 [폴더]+[파일명] 저장 변수
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
	
	CXPGroupBox			m_group_Label_error_Cnt;
	CXPGroupBox			m_group_Label_Vision_Papper;
	CXPGroupBox			m_group_Label_Bin_Papper;

	CDigit				m_dgt_Label_Error_Cnt;
	CDigit				m_dgt_Label_Vision_Paper;
	CDigit				m_dgt_Label_bin_Print;

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
	CScreenBasic();           // 동적 만들기에 사용되는 protected 생성자입니다.
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
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 지원입니다.

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
	afx_msg void OnStnClickedDgtLotsetClip();
	afx_msg void OnStnClickedDgtPickerGapModuleLoad();
	
	afx_msg void OnStnClickedDgtLabelErrorCnt();
	afx_msg void OnStnClickedDgtLabelVisionPaper();
	afx_msg void OnStnClickedDgtLabelBinPrint();
	CXPGroupBox m_group_Device_Cnt;
	CDigit m_dgt_Device_Cnt;
	CXPGroupBox m_group_Repick_Cnt;
	CDigit m_dgt_Repick_Cnt;
	afx_msg void OnStnClickedDgtDeviceCnt();
	afx_msg void OnStnClickedDgtRepickCnt();
};


