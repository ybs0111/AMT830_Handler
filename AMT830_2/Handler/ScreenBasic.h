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
	//kwlee 2017.0515
	int                 m_nClipRemoverErrorMode[2];
	int                 m_nCapRemoverMode[2];
	int                 m_nSorterPickerMode[2];
	int                 m_nHsDirChkMode[2];
	int                 m_nModuledirMode[2];
	
	int                 m_nLotSet_Module_Load[2];
	int                 m_nLotSet_HeatSinkLeft[2];
	int                 m_nLotSet_HeatSinkRight[2];
	int                 m_nLotSet_Clip[2];
	int                 m_nLotSet_Unloader[2];
	int                 m_nLotSet_Reject[2];

	int                 m_nPicker_Gap_Module_Load[2];
	int                 m_nPicker_Gap_HeatSink_Left[2];
	int                 m_nPicker_Gap_HeatSink_Right[2];

	int                 m_nAlarm_Delay[2];
	int                 m_nNetwork_Wait_Time[2];
	int                 m_nNetwork_Retry_Cnt[2];
	int                 m_nLabel_Bin_Printer[2];
	int                 m_nLabel_Vision_Paper[2];
	int                 m_nLabel_Error_Cnt[2];
	int                 m_nDvc_Repick_Cnt[2];

	//

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
	//kwlee 2017.0515
	CXPGroupBox			m_group_LotSet;
	CXPGroupBox			m_group_Picker_Gap;
	CXPGroupBox			m_group_Alarm_Delay;
	CXPGroupBox			m_group_Network_Wait_Time;
	CXPGroupBox			m_group_network_retry_cnt;
	CXPGroupBox			m_group_Label_error_Cnt;
	CXPGroupBox			m_group_Label_Vision_Papper;
	CXPGroupBox			m_group_Label_Bin_Papper;
	CXPGroupBox			m_group_Dvc_Repick_Cnt;
	CGradientStatic		m_msg_Lotset_Module_Load;
	CGradientStatic		m_msg_Lotset_HeatSink_Left;
	CGradientStatic		m_msg_Lotset_HeatSink_Right;
	CGradientStatic		m_msg_LotSet_Clip;
	CGradientStatic		m_msg_LotSet_Unloader;
	CGradientStatic		m_msg_LotSet_Reject;
	CGradientStatic		m_msg_Picker_gap_Module_Load;
	CGradientStatic		m_msg_Picker_gap_HeatSink_Left;
	CGradientStatic		m_msg_Picker_gap_HeatSink_Right;
	CDigit				m_dgt_LotSet_Module_Load;
	CDigit				m_dgt_LotSet_HeatSink_Left;
	CDigit				m_dgt_LotSet_HeatSink_Right;
	CDigit				m_dgt_LotSet_Clip;
	CDigit				m_dgt_LotSet_Unloader;
	CDigit				m_dgt_LotSet_Reject;
	CDigit				m_dgt_Picker_gap_Module_load;
	CDigit				m_dgt_Picker_gap_HeatSink_Left;
	CDigit				m_dgt_Picker_gap_HeatSink_Right;
	CDigit				m_dgt_Alarm_Delay;
	CDigit				m_dgt_network_wait_time;
	CDigit				m_dgt_network_retry_cnt;
	CDigit				m_dgt_Label_bin_Print;
	CDigit				m_dgt_Label_Vision_Paper;
	CDigit				m_dgt_Label_Error_Cnt;
	CDigit				m_dgt_Dvc_Repick_Cnt;

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
};


