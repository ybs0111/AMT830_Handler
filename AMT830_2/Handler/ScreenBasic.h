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
	int		m_nDeviceName;					// 선택된 디바이스의 리스트 위치 저장 변수
	int		m_nOldDeviceName;
	int		m_nModeDevice[2];
	int		m_nModeInterface[2];
	int		m_nModeSecsGem[2];
	int		m_nModeWork[2];
	int		m_nModeFrontSmema[2];
	int		m_nModeRearSmema[2];
	int		m_nModeRfid[2];
	//kwlee 2017.0515
	int     m_nClipRemoverErrorMode[2];
	int     m_nCapRemoverMode[2];
	int     m_nSorterPickerMode[2];
	int     m_nHsDirChkMode[2];
	int     m_nModuledirMode[2];
	int     m_nTrayTubeBcrMode[2];
	
	int     m_nLotSet_Module_Load[2];
	int     m_nLotSet_HeatSinkLeft[2];
	int     m_nLotSet_HeatSinkRight[2];
	int     m_nLotSet_Clip[2];
	int     m_nLotSet_Unloader[2];
	int     m_nLotSet_Reject[2];

	double  m_dPicker_Gap_Module_Load[2];
	double  m_dPicker_Gap_HeatSink_Left[2];
	double  m_dPicker_Gap_HeatSink_Right[2];

	int   m_nAlarm_Delay[2];
	int   m_nNetwork_Wait_Time[2];
	int   m_nNetwork_Retry_Cnt[2];
	int   m_nLabel_Bin_Printer[2];
	int   m_nLabel_Vision_Paper[2];
	int   m_nLabel_Error_Cnt[2];
	int   m_nDvc_Repick_Cnt[2];

	int   m_nContinue_Error[2];
	int   m_nTotal_Error[2];
	int   mn_mode_use_vis_cont_err[2];

	//kwlee 2017.0518
	int		mn_label_name;	
	int     mstr_label_name[2];
	CString	mstr_new_label;			// 새로 생성할 디바이스의 이름.
	CString mstr_load_file;
	BOOL	b_create_list;

	int		mn_label_mode[2];		
	int		mn_labelset_sd[2];
	int		mn_labelset_lt[2];
	int		mn_labelset_lh1[2];
	int		mn_labelset_lh2[2];
	int		md_labelset_x1_pos[2];
	int		md_labelset_x2_pos[2];
	int		md_labelset_x3_pos[2];
	int		md_labelset_x4_pos[2];
	int		md_labelset_x5_pos[2];
	int		md_labelset_x6_pos[2];
	int		md_labelset_y1_pos[2];
	int		md_labelset_y2_pos[2];
	int		md_labelset_y3_pos[2];
	int		md_labelset_y4_pos[2];
	int		md_labelset_y5_pos[2];
	int		md_labelset_y6_pos[2];
	int		md_labelset_x1_width[2];
	int		md_labelset_x2_width[2];
	int		md_labelset_x3_width[2];
	int		md_labelset_x4_width[2];
	int		md_labelset_y1_height[2];
	int		md_labelset_y2_height[2];
	int		md_labelset_y3_height[2];
	int		md_labelset_y4_height[2];
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
	CXPGroupBox			m_group_Label_Info;
	CButtonST			m_btn_Label_Create;
	CButtonST			m_btn_Label_Del;
	CButtonST			m_btn_Label_Apply;
	CButtonST			m_btn_Label_Cancel;
	CListBox			m_list_label_type;
	CButtonST			m_btn_Hs_Vis_Continue;
	CGradientStatic		m_msg_Continue_error;
	CGradientStatic		m_msg_Total_Error;
	CDigit				m_dgt_Continue_Error;
	CDigit				m_dgt_Total_Error;
	CXPGroupBox			m_group_Hs_Vis_Continue;

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
	//kwlee 2017.0518
	void				OnBasic_Label_Focus_Set();
	int					OnBasic_Label_Init_List(LPCTSTR pszPath);
	BOOL				Label_AddItem(int nIndex, WIN32_FIND_DATA *pfd);
	int					OnBasic_New_Label_Check(CString str_label);
	void				OnBasic_Create_Label();
	//kwlee 2017.0518
	int					OnBasic_Label_Data_Comparison();
	void				OnBasic_Label_Data_Apply();
	void				OnBasic_Label_LogFile_Create();
	void				OnBasic_Label_Data_BackUp();
	void				OnBasic_Label_Data_Recovery();
	void				OnBasic_Label_Data_Set();
	int					OnBasic_Label_Input_Data_Check();
	void				OnBasic_Label_DeviceData_Apply();
	void                OnBasic_Label_Data_Display();



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
	afx_msg void OnBnClickedBtnHsVisContinue();
	afx_msg void OnStnClickedDgtContinueError();
	afx_msg void OnStnClickedDgtPickerGapHeatsinkLeft();
	afx_msg void OnStnClickedDgtPickerGapHeatsinkRight();
	afx_msg void OnStnClickedDgtPickerGapModuleLoad();
	afx_msg void OnStnClickedDgtTotalError();
	afx_msg void OnStnClickedDgtLotsetModuleLoad();
	afx_msg void OnStnClickedDgtLotsetHeatsinkLeft();
	afx_msg void OnStnClickedDgtLotsetHeatsinkRight();
	afx_msg void OnStnClickedDgtLotsetClip();
	afx_msg void OnStnClickedDgtLotsetUnloader();
	afx_msg void OnStnClickedDgtLotsetReject();
	afx_msg void OnStnClickedDgtNetworkRetryCnt();
	afx_msg void OnStnClickedDgtLabelErrorCnt();
	afx_msg void OnStnClickedDgtNetworkWaitTime();
	afx_msg void OnStnClickedDgtLabelVisionPaper();
	afx_msg void OnStnClickedDgtAlarmDelay();
	afx_msg void OnStnClickedDgtLabelBinPrint();
	afx_msg void OnStnClickedDgtDvcRepickCnt();
	afx_msg void OnBnClickedBtnLabelApply();
	afx_msg void OnBnClickedBtnLabelCancel();
	afx_msg void OnBnClickedBtnLabelCreate();
	afx_msg void OnBnClickedBtnLabelDelete();
	
};


