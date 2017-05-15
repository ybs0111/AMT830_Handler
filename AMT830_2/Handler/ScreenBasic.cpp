// ScreenBasic.cpp : 구현 파일입니다.
//

#include "stdafx.h"
#include "Handler.h"
#include "ScreenBasic.h"
#include "PublicFunction.h"
#include "Dialog_Message.h"
#include "io.h"			// 파일 존재 유무 검사 함수 호출하기 위해서는 반드시 필요
#include "Dialog_KeyBoard.h"
#include "Dialog_KeyPad.h"
#include "MyBasicData.h"
#include "Dialog_Message.h"
#include "Alg_Mysql.h"
//#include "InterfaceGms.h"
#include "XgemClient.h"
#include "AlgMemory.h"
#include "ClientGms.h"
#include "Dialog_Pass_Check.h"
#include "Dialog_Pass_Check.h"
#include ".\\Ctrl\\KeyBoard.h"

// CScreenBasic


IMPLEMENT_DYNCREATE(CScreenBasic, CFormView)

CScreenBasic::CScreenBasic()
	: CFormView(CScreenBasic::IDD)
{

}

CScreenBasic::~CScreenBasic()
{
}

void CScreenBasic::DoDataExchange(CDataExchange* pDX)
{
	CFormView::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_BTN_MODEL_CREATE,		m_btnModelCreate);
	DDX_Control(pDX, IDC_BTN_MODEL_DELETE,		m_btnModelDelete);
	DDX_Control(pDX, IDC_BTN_APPLY,				m_btnApply);
	DDX_Control(pDX, IDC_BTN_RELOAD,			m_btnReLoad);
	DDX_Control(pDX, IDC_GROUP_MODEL_INFO,		m_groupModelInfo);
	DDX_Control(pDX, IDC_GROUP_DEVICE_MODE,		m_groupDeviceMode);
	DDX_Control(pDX, IDC_CUSTOM_DEVICE_MODE,	m_pGridDevice);
	DDX_Control(pDX, IDC_CUSTOM_MODEL_LIST,		m_pGridModel);
	DDX_Control(pDX, IDC_GROUP_LOTSET_LOT_SET, m_group_LotSet);
	DDX_Control(pDX, IDC_GROUP_PICKER_GAP, m_group_Picker_Gap);
	DDX_Control(pDX, IDC_GROUP_ALARM_DELAY, m_group_Alarm_Delay);
	DDX_Control(pDX, IDC_GROUP_NETWORK_WAIT_TME, m_group_Network_Wait_Time);
	DDX_Control(pDX, IDC_GROUP_NETWORK_RETRY_CNT, m_group_network_retry_cnt);
	DDX_Control(pDX, IDC_GROUP_LABEL_ERROR_CNT, m_group_Label_error_Cnt);
	DDX_Control(pDX, IDC_GROUP_LABEL_VISION_PAPER, m_group_Label_Vision_Papper);
	DDX_Control(pDX, IDC_GROUP_LABEL_BIN_PRINT, m_group_Label_Bin_Papper);
	DDX_Control(pDX, IDC_GROUP_DVC_REPICK_CNT, m_group_Dvc_Repick_Cnt);
	DDX_Control(pDX, IDC_MSG_LOTSET_MODULE_LOAD, m_msg_Lotset_Module_Load);
	DDX_Control(pDX, IDC_MSG_LOTSET_HEATSINK_LEFT, m_msg_Lotset_HeatSink_Left);
	DDX_Control(pDX, IDC_MSG_LOTSET_HEATSINK_RIGHT, m_msg_Lotset_HeatSink_Right);
	DDX_Control(pDX, IDC_MSG_LOTSET_CLIP, m_msg_LotSet_Clip);
	DDX_Control(pDX, IDC_MSG_LOTSET_UNLOADER, m_msg_LotSet_Unloader);
	DDX_Control(pDX, IDC_MSG_LOTSET_REJECT, m_msg_LotSet_Reject);
	DDX_Control(pDX, IDC_MSG_PICKER_GAP_MODULE_LOAD, m_msg_Picker_gap_Module_Load);
	DDX_Control(pDX, IDC_MSG_PICKER_GAP_HEATSINK_LEFT, m_msg_Picker_gap_HeatSink_Left);
	DDX_Control(pDX, IDC_MSG_PICKER_GAP_HEATSINK_RIGHT, m_msg_Picker_gap_HeatSink_Right);
	DDX_Control(pDX, IDC_DGT_LOTSET_MODULE_LOAD, m_dgt_LotSet_Module_Load);
	DDX_Control(pDX, IDC_DGT_LOTSET_HEATSINK_LEFT, m_dgt_LotSet_HeatSink_Left);
	DDX_Control(pDX, IDC_DGT_LOTSET_HEATSINK_RIGHT, m_dgt_LotSet_HeatSink_Right);
	DDX_Control(pDX, IDC_DGT_LOTSET_CLIP, m_dgt_LotSet_Clip);
	DDX_Control(pDX, IDC_DGT_LOTSET_UNLOADER, m_dgt_LotSet_Unloader);
	DDX_Control(pDX, IDC_DGT_LOTSET_REJECT, m_dgt_LotSet_Reject);
	DDX_Control(pDX, IDC_DGT_PICKER_GAP_MODULE_LOAD, m_dgt_Picker_gap_Module_load);
	DDX_Control(pDX, IDC_DGT_PICKER_GAP_HEATSINK_LEFT, m_dgt_Picker_gap_HeatSink_Left);
	DDX_Control(pDX, IDC_DGT_PICKER_GAP_HEATSINK_RIGHT, m_dgt_Picker_gap_HeatSink_Right);
	DDX_Control(pDX, IDC_DGT_ALARM_DELAY, m_dgt_Alarm_Delay);
	DDX_Control(pDX, IDC_DGT_NETWORK_WAIT_TIME, m_dgt_network_wait_time);
	DDX_Control(pDX, IDC_DGT_NETWORK_RETRY_CNT, m_dgt_network_retry_cnt);
	DDX_Control(pDX, IDC_DGT_LABEL_BIN_PRINT, m_dgt_Label_bin_Print);
	DDX_Control(pDX, IDC_DGT_LABEL_VISION_PAPER, m_dgt_Label_Vision_Paper);
	DDX_Control(pDX, IDC_DGT_LABEL_ERROR_CNT, m_dgt_Label_Error_Cnt);
	DDX_Control(pDX, IDC_DGT_DVC_REPICK_CNT, m_dgt_Dvc_Repick_Cnt);
}

BEGIN_MESSAGE_MAP(CScreenBasic, CFormView)
	ON_NOTIFY(NM_CLICK, IDC_CUSTOM_MODEL_LIST,	OnModelCellClick)
	ON_NOTIFY(NM_CLICK, IDC_CUSTOM_MODEL_LIST,	OnModelCellRClick)
	ON_NOTIFY(NM_CLICK, IDC_CUSTOM_DEVICE_MODE, OnDeviceCellClick)
	ON_BN_CLICKED(IDC_BTN_MODEL_CREATE,			&CScreenBasic::OnClickedBtnModelCreate)
	ON_BN_CLICKED(IDC_BTN_MODEL_DELETE,			&CScreenBasic::OnClickedBtnModelDelete)
	ON_BN_CLICKED(IDC_BTN_RELOAD,				&CScreenBasic::OnClickedBtnReload)
	ON_BN_CLICKED(IDC_BTN_APPLY,				&CScreenBasic::OnClickedBtnApply)
	ON_WM_ERASEBKGND()
	ON_WM_DESTROY()
	ON_WM_CTLCOLOR()
	ON_WM_TIMER()
	ON_STN_CLICKED(IDC_DGT_LOTSET_CLIP, &CScreenBasic::OnStnClickedDgtLotsetClip)
END_MESSAGE_MAP()


// CScreenBasic 진단입니다.

#ifdef _DEBUG
void CScreenBasic::AssertValid() const
{
	CFormView::AssertValid();
}

#ifndef _WIN32_WCE
void CScreenBasic::Dump(CDumpContext& dc) const
{
	CFormView::Dump(dc);
}
#endif
#endif //_DEBUG


// CScreenBasic 메시지 처리기입니다.


void CScreenBasic::OnInitialUpdate()
{
	CFormView::OnInitialUpdate();

	OnDataInit();
	OnInitGroupBox();
	OnInitLabel();
	OnInitDigit();
	OnInitButton();

	OnInitGridDeviceMode();
	OnInitGridModelList();
	
	UpdateData(FALSE);

	st_handler_info.cWndBasic = this;
}


BOOL CScreenBasic::DestroyWindow()
{
	// TODO: Add your specialized code here and/or call the base class
/*	if (OnDataComparison() == RET_ERROR)
	{
		OnDataHistoryLog();
		OnDataApply();
	}
	st_handler_info.cWndBasic = NULL;*/
	return CFormView::DestroyWindow();
}

void CScreenBasic::OnInitGroupBox()
{
	m_groupModelInfo.SetFont(clsFunc.OnLogFont(16));
	m_groupModelInfo.SetCatptionTextColor(BLUE_C);
	m_groupModelInfo.SetBorderColor(ORANGE_C);
	m_groupModelInfo.SetFontBold(TRUE);
	m_groupModelInfo.SetBackgroundColor(WINDOW_UP);

	m_groupDeviceMode.SetFont(clsFunc.OnLogFont(16));
	m_groupDeviceMode.SetCatptionTextColor(BLUE_C);
	m_groupDeviceMode.SetBorderColor(ORANGE_C);
	m_groupDeviceMode.SetFontBold(TRUE);
	m_groupDeviceMode.SetBackgroundColor(WINDOW_UP);

	//kwlee 2017.0515
	m_group_LotSet.SetFont(clsFunc.OnLogFont(16));
	m_group_LotSet.SetCatptionTextColor(BLUE_C);
	m_group_LotSet.SetBorderColor(ORANGE_C);
	m_group_LotSet.SetFontBold(TRUE);
	m_group_LotSet.SetBackgroundColor(WINDOW_UP);

	m_group_Picker_Gap.SetFont(clsFunc.OnLogFont(16));
	m_group_Picker_Gap.SetCatptionTextColor(BLUE_C);
	m_group_Picker_Gap.SetBorderColor(ORANGE_C);
	m_group_Picker_Gap.SetFontBold(TRUE);
	m_group_Picker_Gap.SetBackgroundColor(WINDOW_UP);

	m_group_Alarm_Delay.SetFont(clsFunc.OnLogFont(16));
	m_group_Alarm_Delay.SetCatptionTextColor(BLUE_C);
	m_group_Alarm_Delay.SetBorderColor(ORANGE_C);
	m_group_Alarm_Delay.SetFontBold(TRUE);
	m_group_Alarm_Delay.SetBackgroundColor(WINDOW_UP);

	m_group_Network_Wait_Time.SetFont(clsFunc.OnLogFont(16));
	m_group_Network_Wait_Time.SetCatptionTextColor(BLUE_C);
	m_group_Network_Wait_Time.SetBorderColor(ORANGE_C);
	m_group_Network_Wait_Time.SetFontBold(TRUE);
	m_group_Network_Wait_Time.SetBackgroundColor(WINDOW_UP);

	m_group_network_retry_cnt.SetFont(clsFunc.OnLogFont(16));
	m_group_network_retry_cnt.SetCatptionTextColor(BLUE_C);
	m_group_network_retry_cnt.SetBorderColor(ORANGE_C);
	m_group_network_retry_cnt.SetFontBold(TRUE);
	m_group_network_retry_cnt.SetBackgroundColor(WINDOW_UP);

	m_group_Label_Bin_Papper.SetFont(clsFunc.OnLogFont(16));
	m_group_Label_Bin_Papper.SetCatptionTextColor(BLUE_C);
	m_group_Label_Bin_Papper.SetBorderColor(ORANGE_C);
	m_group_Label_Bin_Papper.SetFontBold(TRUE);
	m_group_Label_Bin_Papper.SetBackgroundColor(WINDOW_UP);

	m_group_Label_Vision_Papper.SetFont(clsFunc.OnLogFont(16));
	m_group_Label_Vision_Papper.SetCatptionTextColor(BLUE_C);
	m_group_Label_Vision_Papper.SetBorderColor(ORANGE_C);
	m_group_Label_Vision_Papper.SetFontBold(TRUE);
	m_group_Label_Vision_Papper.SetBackgroundColor(WINDOW_UP);

	m_group_Label_error_Cnt.SetFont(clsFunc.OnLogFont(16));
	m_group_Label_error_Cnt.SetCatptionTextColor(BLUE_C);
	m_group_Label_error_Cnt.SetBorderColor(ORANGE_C);
	m_group_Label_error_Cnt.SetFontBold(TRUE);
	m_group_Label_error_Cnt.SetBackgroundColor(WINDOW_UP);

	m_group_Dvc_Repick_Cnt.SetFont(clsFunc.OnLogFont(16));
	m_group_Dvc_Repick_Cnt.SetCatptionTextColor(BLUE_C);
	m_group_Dvc_Repick_Cnt.SetBorderColor(ORANGE_C);
	m_group_Dvc_Repick_Cnt.SetFontBold(TRUE);
	m_group_Dvc_Repick_Cnt.SetBackgroundColor(WINDOW_UP);
}


void CScreenBasic::OnInitLabel()
{
	m_msg_Lotset_Module_Load.SetFont(clsFunc.m_pFont[2]);
	m_msg_Lotset_Module_Load.SetWindowText(_T("Module Load"));
	m_msg_Lotset_Module_Load.SetCenterText();
	m_msg_Lotset_Module_Load.SetColor(WHITE_C);
	m_msg_Lotset_Module_Load.SetGradientColor(GREEN_C);
	m_msg_Lotset_Module_Load.SetTextColor(BLACK_C);

	m_msg_Lotset_HeatSink_Left.SetFont(clsFunc.m_pFont[2]);
	m_msg_Lotset_HeatSink_Left.SetWindowText(_T("HeatSink Left"));
	m_msg_Lotset_HeatSink_Left.SetCenterText();
	m_msg_Lotset_HeatSink_Left.SetColor(WHITE_C);
	m_msg_Lotset_HeatSink_Left.SetGradientColor(GREEN_C);
	m_msg_Lotset_HeatSink_Left.SetTextColor(BLACK_C);

	m_msg_Lotset_HeatSink_Right.SetFont(clsFunc.m_pFont[2]);
	m_msg_Lotset_HeatSink_Right.SetWindowText(_T("HeatSink Right"));
	m_msg_Lotset_HeatSink_Right.SetCenterText();
	m_msg_Lotset_HeatSink_Right.SetColor(WHITE_C);
	m_msg_Lotset_HeatSink_Right.SetGradientColor(GREEN_C);
	m_msg_Lotset_HeatSink_Right.SetTextColor(BLACK_C);

	m_msg_LotSet_Clip.SetFont(clsFunc.m_pFont[2]);
	m_msg_LotSet_Clip.SetWindowText(_T("Clip"));
	m_msg_LotSet_Clip.SetCenterText();
	m_msg_LotSet_Clip.SetColor(WHITE_C);
	m_msg_LotSet_Clip.SetGradientColor(GREEN_C);
	m_msg_LotSet_Clip.SetTextColor(BLACK_C);

	m_msg_LotSet_Unloader.SetFont(clsFunc.m_pFont[2]);
	m_msg_LotSet_Unloader.SetWindowText(_T("Unloader"));
	m_msg_LotSet_Unloader.SetCenterText();
	m_msg_LotSet_Unloader.SetColor(WHITE_C);
	m_msg_LotSet_Unloader.SetGradientColor(GREEN_C);
	m_msg_LotSet_Unloader.SetTextColor(BLACK_C);

	m_msg_LotSet_Reject.SetFont(clsFunc.m_pFont[2]);
	m_msg_LotSet_Reject.SetWindowText(_T("Reject"));
	m_msg_LotSet_Reject.SetCenterText();
	m_msg_LotSet_Reject.SetColor(WHITE_C);
	m_msg_LotSet_Reject.SetGradientColor(GREEN_C);
	m_msg_LotSet_Reject.SetTextColor(BLACK_C);

	m_msg_Picker_gap_Module_Load.SetFont(clsFunc.m_pFont[2]);
	m_msg_Picker_gap_Module_Load.SetWindowText(_T("Module Load"));
	m_msg_Picker_gap_Module_Load.SetCenterText();
	m_msg_Picker_gap_Module_Load.SetColor(WHITE_C);
	m_msg_Picker_gap_Module_Load.SetGradientColor(GREEN_C);
	m_msg_Picker_gap_Module_Load.SetTextColor(BLACK_C);

	m_msg_Picker_gap_HeatSink_Left.SetFont(clsFunc.m_pFont[2]);
	m_msg_Picker_gap_HeatSink_Left.SetWindowText(_T("HeatSink Left"));
	m_msg_Picker_gap_HeatSink_Left.SetCenterText();
	m_msg_Picker_gap_HeatSink_Left.SetColor(WHITE_C);
	m_msg_Picker_gap_HeatSink_Left.SetGradientColor(GREEN_C);
	m_msg_Picker_gap_HeatSink_Left.SetTextColor(BLACK_C);

	m_msg_Picker_gap_HeatSink_Right.SetFont(clsFunc.m_pFont[2]);
	m_msg_Picker_gap_HeatSink_Right.SetWindowText(_T("HeatSink Right"));
	m_msg_Picker_gap_HeatSink_Right.SetCenterText();
	m_msg_Picker_gap_HeatSink_Right.SetColor(WHITE_C);
	m_msg_Picker_gap_HeatSink_Right.SetGradientColor(GREEN_C);
	m_msg_Picker_gap_HeatSink_Right.SetTextColor(BLACK_C);

}


void CScreenBasic::OnInitDigit()
{
	m_dgt_LotSet_Module_Load.SetStyle(CDigit::DS_INT, 3, CDigit::DC_BGREEN, CDigit::DC_BDISABLE);
	m_dgt_LotSet_Module_Load.SetVal(m_nLotSet_Module_Load[1]);

	m_dgt_LotSet_HeatSink_Left.SetStyle(CDigit::DS_INT, 3, CDigit::DC_BGREEN, CDigit::DC_BDISABLE);
	m_dgt_LotSet_HeatSink_Left.SetVal(m_nLotSet_HeatSinkLeft[1]);

	m_dgt_LotSet_HeatSink_Right.SetStyle(CDigit::DS_INT, 3, CDigit::DC_BGREEN, CDigit::DC_BDISABLE);
	m_dgt_LotSet_HeatSink_Right.SetVal(m_nLotSet_HeatSinkRight[1]);

	m_dgt_LotSet_Clip.SetStyle(CDigit::DS_INT, 3, CDigit::DC_BGREEN, CDigit::DC_BDISABLE);
	m_dgt_LotSet_Clip.SetVal(m_nLotSet_Clip[1]);

	m_dgt_LotSet_Unloader.SetStyle(CDigit::DS_INT, 3, CDigit::DC_BGREEN, CDigit::DC_BDISABLE);
	m_dgt_LotSet_Unloader.SetVal(m_nLotSet_Unloader[1]);

	m_dgt_LotSet_Reject.SetStyle(CDigit::DS_INT, 3, CDigit::DC_BGREEN, CDigit::DC_BDISABLE);
	m_dgt_LotSet_Reject.SetVal(m_nLotSet_Reject[1]);

	m_dgt_Picker_gap_Module_load.SetStyle(CDigit::DS_INT, 6, CDigit::DC_BGREEN, CDigit::DC_BDISABLE);
	m_dgt_Picker_gap_Module_load.SetVal(m_nPicker_Gap_Module_Load[1]);

	m_dgt_Picker_gap_HeatSink_Left.SetStyle(CDigit::DS_INT, 6, CDigit::DC_BGREEN, CDigit::DC_BDISABLE);
	m_dgt_Picker_gap_HeatSink_Left.SetVal(m_nPicker_Gap_HeatSink_Left[1]);

	m_dgt_Picker_gap_HeatSink_Right.SetStyle(CDigit::DS_INT, 6, CDigit::DC_BGREEN, CDigit::DC_BDISABLE);
	m_dgt_Picker_gap_HeatSink_Right.SetVal(m_nPicker_Gap_HeatSink_Right[1]);

	m_dgt_Alarm_Delay.SetStyle(CDigit::DS_INT, 3, CDigit::DC_BGREEN, CDigit::DC_BDISABLE);
	m_dgt_Alarm_Delay.SetVal(m_nAlarm_Delay[1]);

	m_dgt_network_wait_time.SetStyle(CDigit::DS_INT, 3, CDigit::DC_BGREEN, CDigit::DC_BDISABLE);
	m_dgt_network_wait_time.SetVal(m_nNetwork_Wait_Time[1]);

	m_dgt_network_retry_cnt.SetStyle(CDigit::DS_INT, 3, CDigit::DC_BGREEN, CDigit::DC_BDISABLE);
	m_dgt_network_retry_cnt.SetVal(m_nNetwork_Retry_Cnt[1]);

	m_dgt_Label_bin_Print.SetStyle(CDigit::DS_INT, 3, CDigit::DC_BGREEN, CDigit::DC_BDISABLE);
	m_dgt_Label_bin_Print.SetVal(m_nLabel_Bin_Printer[1]);

	m_dgt_Label_Vision_Paper.SetStyle(CDigit::DS_INT, 3, CDigit::DC_BGREEN, CDigit::DC_BDISABLE);
	m_dgt_Label_Vision_Paper.SetVal(m_nLabel_Vision_Paper[1]);

	m_dgt_Label_Error_Cnt.SetStyle(CDigit::DS_INT, 3, CDigit::DC_BGREEN, CDigit::DC_BDISABLE);
	m_dgt_Label_Error_Cnt.SetVal(m_nLabel_Error_Cnt[1]);

	m_dgt_Dvc_Repick_Cnt.SetStyle(CDigit::DS_INT, 3, CDigit::DC_BGREEN, CDigit::DC_BDISABLE);
	m_dgt_Dvc_Repick_Cnt.SetVal(m_nDvc_Repick_Cnt[1]);

}


void CScreenBasic::OnInitButton()
{
	m_btnModelCreate.SetBitmaps(IDC_BTN_MODEL_CREATE, IDB_BITMAP_CREATE_DN, WINDOW_DN, IDB_BITMAP_CREATE_UP, WINDOW_UP);
	m_btnModelCreate.SetColor(CButtonST::BTNST_COLOR_BK_IN, WINDOW_DN);
	m_btnModelCreate.SetColor(CButtonST::BTNST_COLOR_BK_OUT, WINDOW_UP);
	m_btnModelCreate.SetColor(CButtonST::BTNST_COLOR_BK_FOCUS, WINDOW_UP);
	m_btnModelCreate.SetColor(CButtonST::BTNST_COLOR_FG_IN, BLACK_C);
	m_btnModelCreate.SetColor(CButtonST::BTNST_COLOR_FG_OUT, BLUE_C);
	m_btnModelCreate.SetColor(CButtonST::BTNST_COLOR_FG_FOCUS, BLUE_C);
	m_btnModelCreate.SetFont(clsFunc.m_pFont[3]);
	m_btnModelCreate.SetTooltipText(_T("Model Create"));

	m_btnModelDelete.SetBitmaps(IDC_BTN_MODEL_DELETE, IDB_BITMAP_DELETE_DN, WINDOW_DN, IDB_BITMAP_DELETE_UP, WINDOW_UP);
	m_btnModelDelete.SetColor(CButtonST::BTNST_COLOR_BK_IN, WINDOW_DN);
	m_btnModelDelete.SetColor(CButtonST::BTNST_COLOR_BK_OUT, WINDOW_UP);
	m_btnModelDelete.SetColor(CButtonST::BTNST_COLOR_BK_FOCUS, WINDOW_UP);
	m_btnModelDelete.SetColor(CButtonST::BTNST_COLOR_FG_IN, BLACK_C);
	m_btnModelDelete.SetColor(CButtonST::BTNST_COLOR_FG_OUT, BLUE_C);
	m_btnModelDelete.SetColor(CButtonST::BTNST_COLOR_FG_FOCUS, BLUE_C);
	m_btnModelDelete.SetFont(clsFunc.m_pFont[3]);
	m_btnModelDelete.SetTooltipText(_T("Model Delete"));

	m_btnApply.SetBitmaps(IDC_BTN_APPLY, IDB_BITMAP_APPLY_DN, WINDOW_DN, IDB_BITMAP_APPLY_UP, WINDOW_UP);
	m_btnApply.SetColor(CButtonST::BTNST_COLOR_BK_IN, WINDOW_DN);
	m_btnApply.SetColor(CButtonST::BTNST_COLOR_BK_OUT, WINDOW_UP);
	m_btnApply.SetColor(CButtonST::BTNST_COLOR_BK_FOCUS, WINDOW_UP);
	m_btnApply.SetColor(CButtonST::BTNST_COLOR_FG_IN, BLACK_C);
	m_btnApply.SetColor(CButtonST::BTNST_COLOR_FG_OUT, BLUE_C);
	m_btnApply.SetColor(CButtonST::BTNST_COLOR_FG_FOCUS, BLUE_C);
	m_btnApply.SetFont(clsFunc.m_pFont[3]);
	m_btnApply.SetTooltipText(_T("Basic Data Apply"));

	m_btnReLoad.SetBitmaps(IDC_BTN_RELOAD, IDB_BITMAP_RELOAD_DN, WINDOW_DN, IDB_BITMAP_RELOAD_UP, WINDOW_UP);
	m_btnReLoad.SetColor(CButtonST::BTNST_COLOR_BK_IN, WINDOW_DN);
	m_btnReLoad.SetColor(CButtonST::BTNST_COLOR_BK_OUT, WINDOW_UP);
	m_btnReLoad.SetColor(CButtonST::BTNST_COLOR_BK_FOCUS, WINDOW_UP);
	m_btnReLoad.SetColor(CButtonST::BTNST_COLOR_FG_IN, BLACK_C);
	m_btnReLoad.SetColor(CButtonST::BTNST_COLOR_FG_OUT, BLUE_C);
	m_btnReLoad.SetColor(CButtonST::BTNST_COLOR_FG_FOCUS, BLUE_C);
	m_btnReLoad.SetFont(clsFunc.m_pFont[3]);
	m_btnReLoad.SetTooltipText(_T("Basic Data ReLoad"));

}

void CScreenBasic::OnInitGridDeviceMode()
{
	CString strTmp;
	int i, j;
	
	m_pGridDevice.SetFrameFocusCell(FALSE);
	m_pGridDevice.SetTrackFocusCell(FALSE);
	m_pGridDevice.EnableSelection(FALSE);

	m_pGridDevice.SetGridLineColor(BLACK_C);
	m_pGridDevice.SetGridLines(1);

	m_pGridDevice.SetRowCount(24);
	m_pGridDevice.SetColumnCount(2);

	m_pGridDevice.SetFixedRowCount(0);
	m_pGridDevice.SetFixedColumnCount(0);
	m_pGridDevice.SetFixedBkColor(RGB(0,0,200));
	m_pGridDevice.SetFixedBkColor(RGB(200,200,255));
	m_pGridDevice.SetTextBkColor(RGB(150,150,200));

	for (i=0; i<24; i++) 
	{
		m_pGridDevice.SetRowHeight(i, 31);

		for (j=0; j<2; j++) 
		{
			switch (j)
			{
				case 0:
					m_pGridDevice.SetColumnWidth(j, 25);
					break;

				case 1:
					m_pGridDevice.SetColumnWidth(j, 150);
					break;
			}

			m_pGridDevice.SetItemFormat(i, j, DT_CENTER|DT_VCENTER|DT_SINGLELINE);
			m_pGridDevice.SetItemState(i, j, GVIS_READONLY);
			m_pGridDevice.SetItemBkColour(i, j, WHITE_C, CLR_DEFAULT);
		}
	}

	// IO MAP Header ////////////////////////////////////////////////////////////////////////////////////////////// 
	m_pGridDevice.SetItemBkColour(0, 0, RGB(219, 229, 241), BLACK_L);
	m_pGridDevice.SetItemFont(0, 0, &clsFunc.OnLogFont(13));
	m_pGridDevice.SetItemText(0, 0, _T("No."));

	m_pGridDevice.SetItemBkColour(0, 1, RGB(219, 229, 241), BLACK_L);
	m_pGridDevice.SetItemFont(0, 1, &clsFunc.OnLogFont(16));
	m_pGridDevice.SetItemText(0, 1, _T("MODE"));


	m_pGridDevice.SetItemBkColour(1, 0, BLACK_L, YELLOW_C);
	m_pGridDevice.SetItemFont(1, 0, &clsFunc.OnLogFont(16));
	m_pGridDevice.SetItemText(1, 0, _T("1"));

	m_pGridDevice.SetItemBkColour(1, 1, BLACK_L, YELLOW_C);
	m_pGridDevice.SetItemFont(1, 1, &clsFunc.OnLogFont(16));
	m_pGridDevice.SetItemText(1, 1, _T("WithOut"));

	m_pGridDevice.SetItemBkColour(2, 0, BLACK_L, YELLOW_C);
	m_pGridDevice.SetItemFont(2, 0, &clsFunc.OnLogFont(16));
	m_pGridDevice.SetItemText(2, 0, _T("2"));

	m_pGridDevice.SetItemBkColour(2, 1, BLACK_L, YELLOW_C);
	m_pGridDevice.SetItemFont(2, 1, &clsFunc.OnLogFont(16));
	m_pGridDevice.SetItemText(2, 1, _T("With"));

	if (m_nModeDevice[1]		== WITHOUT_DVC)
	{
		m_pGridDevice.SetItemBkColour(1, 0, RGB(79, 79, 225), WHITE_C);
		m_pGridDevice.SetItemBkColour(1, 1, RGB(79, 79, 225), WHITE_C);
	}
	else if (m_nModeDevice[1]	== WITH_DVC)
	{
		m_pGridDevice.SetItemBkColour(2, 0, RGB(79, 79, 225), WHITE_C);
		m_pGridDevice.SetItemBkColour(2, 1, RGB(79, 79, 225), WHITE_C);
	}

	m_pGridDevice.MergeCells(3, 0, 3, 1);
	m_pGridDevice.SetItemBkColour(3, 0, RGB(219, 229, 241), BLACK_L);
	m_pGridDevice.SetItemFont(3, 0, &clsFunc.OnLogFont(16));
	m_pGridDevice.SetItemText(3, 0, _T("INTERFACE"));

	m_pGridDevice.SetItemBkColour(4, 0, GREEN_D, BLACK_C);
	m_pGridDevice.SetItemFont(4, 0, &clsFunc.OnLogFont(16));
	m_pGridDevice.SetItemText(4, 0, _T("1"));

	m_pGridDevice.SetItemBkColour(4, 1, GREEN_D, BLACK_C);
	m_pGridDevice.SetItemFont(4, 1, &clsFunc.OnLogFont(16));
	m_pGridDevice.SetItemText(4, 1, _T("Off Line"));

	m_pGridDevice.SetItemBkColour(5, 0, GREEN_D, BLACK_C);
	m_pGridDevice.SetItemFont(5, 0, &clsFunc.OnLogFont(16));
	m_pGridDevice.SetItemText(5, 0, _T("2"));

	m_pGridDevice.SetItemBkColour(5, 1, GREEN_D, BLACK_C);
	m_pGridDevice.SetItemFont(5, 1, &clsFunc.OnLogFont(16));
	m_pGridDevice.SetItemText(5, 1, _T("On Line"));

	if (m_nModeInterface[1] == EQP_OFF_LINE)
	{
		m_pGridDevice.SetItemBkColour(4, 0, GREEN_C, BLACK_C);
		m_pGridDevice.SetItemBkColour(4, 1, GREEN_C, BLACK_C);
	}
	else
	{
		m_pGridDevice.SetItemBkColour(5, 0, GREEN_C, BLACK_C);
		m_pGridDevice.SetItemBkColour(5, 1, GREEN_C, BLACK_C);
	}

	m_pGridDevice.MergeCells(6, 0, 6, 1);
	m_pGridDevice.SetItemBkColour(6, 0, RGB(219, 229, 241), BLACK_L);
	m_pGridDevice.SetItemFont(6, 0, &clsFunc.OnLogFont(16));
	m_pGridDevice.SetItemText(6, 0, _T("Work Mode"));

	m_pGridDevice.SetItemBkColour(7, 0, GREEN_D, BLACK_C);
	m_pGridDevice.SetItemFont(7, 0, &clsFunc.OnLogFont(16));
	m_pGridDevice.SetItemText(7, 0, _T("1"));

	m_pGridDevice.SetItemBkColour(7, 1, GREEN_D, BLACK_C);
	m_pGridDevice.SetItemFont(7, 1, &clsFunc.OnLogFont(16));
	m_pGridDevice.SetItemText(7, 1, _T("Stand Alone"));

	m_pGridDevice.SetItemBkColour(8, 0, GREEN_D, BLACK_C);
	m_pGridDevice.SetItemFont(8, 0, &clsFunc.OnLogFont(16));
	m_pGridDevice.SetItemText(8, 0, _T("2"));

	m_pGridDevice.SetItemBkColour(8, 1, GREEN_D, BLACK_C);
	m_pGridDevice.SetItemFont(8, 1, &clsFunc.OnLogFont(16));
	m_pGridDevice.SetItemText(8, 1, _T("In-Line"));

	if (m_nModeRearSmema[1] == NO)
	{
		m_pGridDevice.SetItemBkColour(7, 0, GREEN_C, BLACK_C);
		m_pGridDevice.SetItemBkColour(7, 1, GREEN_C, BLACK_C);
	}
	else
	{
		m_pGridDevice.SetItemBkColour(8, 0, GREEN_C, BLACK_C);
		m_pGridDevice.SetItemBkColour(8, 1, GREEN_C, BLACK_C);
	}
	/////////////////////////////////////////////////////////////////
	/////////////////////////////////////////////////////////////////
	//kwlee 2017.0515
	m_pGridDevice.MergeCells(9, 0, 9, 1);
	m_pGridDevice.SetItemBkColour(9, 0, RGB(219, 229, 241), BLACK_L);
	m_pGridDevice.SetItemFont(9, 0, &clsFunc.OnLogFont(16));
	m_pGridDevice.SetItemText(9, 0, _T("Clip Remove Error Mode"));

	m_pGridDevice.SetItemBkColour(10, 0, GREEN_D, BLACK_C);
	m_pGridDevice.SetItemFont(10, 0, &clsFunc.OnLogFont(16));
	m_pGridDevice.SetItemText(10, 0, _T("1"));

	m_pGridDevice.SetItemBkColour(10, 1, GREEN_D, BLACK_C);
	m_pGridDevice.SetItemFont(10, 1, &clsFunc.OnLogFont(16));
	m_pGridDevice.SetItemText(10, 1, _T("Clip Remover Alarm Use"));

	m_pGridDevice.SetItemBkColour(11, 0, GREEN_D, BLACK_C);
	m_pGridDevice.SetItemFont(11, 0, &clsFunc.OnLogFont(16));
	m_pGridDevice.SetItemText(11, 0, _T("2"));

	m_pGridDevice.SetItemBkColour(11, 1, GREEN_D, BLACK_C);
	m_pGridDevice.SetItemFont(11, 1, &clsFunc.OnLogFont(16));
	m_pGridDevice.SetItemText(11, 1, _T("Clip Remover Alarm Skip"));

	if (m_nClipRemoverErrorMode[1] == YES)
	{
		m_pGridDevice.SetItemBkColour(10, 0, GREEN_C, BLACK_C);
		m_pGridDevice.SetItemBkColour(10, 1, GREEN_C, BLACK_C);
	}
	else
	{
		m_pGridDevice.SetItemBkColour(11, 0, GREEN_C, BLACK_C);
		m_pGridDevice.SetItemBkColour(11, 1, GREEN_C, BLACK_C);
	}
	/////////////////////////////////////////////////////////////////
	/////////////////////////////////////////////////////////////////
	m_pGridDevice.MergeCells(12, 0, 12, 1);
	m_pGridDevice.SetItemBkColour(12, 0, RGB(219, 229, 241), BLACK_L);
	m_pGridDevice.SetItemFont(12, 0, &clsFunc.OnLogFont(16));
	m_pGridDevice.SetItemText(12, 0, _T("Cap Remove Mode"));

	m_pGridDevice.SetItemBkColour(13, 0, GREEN_D, BLACK_C);
	m_pGridDevice.SetItemFont(13, 0, &clsFunc.OnLogFont(16));
	m_pGridDevice.SetItemText(13, 0, _T("1"));

	m_pGridDevice.SetItemBkColour(13, 1, GREEN_D, BLACK_C);
	m_pGridDevice.SetItemFont(13, 1, &clsFunc.OnLogFont(16));
	m_pGridDevice.SetItemText(13, 1, _T("Remove use"));

	m_pGridDevice.SetItemBkColour(14, 0, GREEN_D, BLACK_C);
	m_pGridDevice.SetItemFont(14, 0, &clsFunc.OnLogFont(16));
	m_pGridDevice.SetItemText(14, 0, _T("2"));

	m_pGridDevice.SetItemBkColour(14, 1, GREEN_D, BLACK_C);
	m_pGridDevice.SetItemFont(14, 1, &clsFunc.OnLogFont(16));
	m_pGridDevice.SetItemText(14, 1, _T("Remove Skip"));

	if (m_nCapRemoverMode[1] == YES)
	{
		m_pGridDevice.SetItemBkColour(13, 0, GREEN_C, BLACK_C);
		m_pGridDevice.SetItemBkColour(13, 1, GREEN_C, BLACK_C);
	}
	else
	{
		m_pGridDevice.SetItemBkColour(14, 0, GREEN_C, BLACK_C);
		m_pGridDevice.SetItemBkColour(14, 1, GREEN_C, BLACK_C);
	}
	/////////////////////////////////////////////////////////////////
	/////////////////////////////////////////////////////////////////
	m_pGridDevice.MergeCells(15, 0, 15, 1);
	m_pGridDevice.SetItemBkColour(15, 0, RGB(219, 229, 241), BLACK_L);
	m_pGridDevice.SetItemFont(15, 0, &clsFunc.OnLogFont(16));
	m_pGridDevice.SetItemText(15, 0, _T("Sorter Picker Mode"));

	m_pGridDevice.SetItemBkColour(16, 0, GREEN_D, BLACK_C);
	m_pGridDevice.SetItemFont(16, 0, &clsFunc.OnLogFont(16));
	m_pGridDevice.SetItemText(16, 0, _T("1"));

	m_pGridDevice.SetItemBkColour(16, 1, GREEN_D, BLACK_C);
	m_pGridDevice.SetItemFont(16, 1, &clsFunc.OnLogFont(16));
	m_pGridDevice.SetItemText(16, 1, _T("Sorter Picker Use"));

	m_pGridDevice.SetItemBkColour(17, 0, GREEN_D, BLACK_C);
	m_pGridDevice.SetItemFont(17, 0, &clsFunc.OnLogFont(16));
	m_pGridDevice.SetItemText(17, 0, _T("2"));

	m_pGridDevice.SetItemBkColour(17, 1, GREEN_D, BLACK_C);
	m_pGridDevice.SetItemFont(17, 1, &clsFunc.OnLogFont(16));
	m_pGridDevice.SetItemText(17, 1, _T("Sorter Picker Skip"));

	if (m_nSorterPickerMode[1] == YES)
	{
		m_pGridDevice.SetItemBkColour(16, 0, GREEN_C, BLACK_C);
		m_pGridDevice.SetItemBkColour(16, 1, GREEN_C, BLACK_C);
	}
	else
	{
		m_pGridDevice.SetItemBkColour(17, 0, GREEN_C, BLACK_C);
		m_pGridDevice.SetItemBkColour(17, 1, GREEN_C, BLACK_C);
	}

	m_pGridDevice.MergeCells(18, 0, 18, 1);
	m_pGridDevice.SetItemBkColour(18, 0, RGB(219, 229, 241), BLACK_L);
	m_pGridDevice.SetItemFont(18, 0, &clsFunc.OnLogFont(16));
	m_pGridDevice.SetItemText(18, 0, _T("Hs Dir Chk Mode"));

	m_pGridDevice.SetItemBkColour(19, 0, GREEN_D, BLACK_C);
	m_pGridDevice.SetItemFont(19, 0, &clsFunc.OnLogFont(16));
	m_pGridDevice.SetItemText(19, 0, _T("1"));

	m_pGridDevice.SetItemBkColour(19, 1, GREEN_D, BLACK_C);
	m_pGridDevice.SetItemFont(19, 1, &clsFunc.OnLogFont(16));
	m_pGridDevice.SetItemText(19, 1, _T("Hs Dir Use"));

	m_pGridDevice.SetItemBkColour(20, 0, GREEN_D, BLACK_C);
	m_pGridDevice.SetItemFont(20, 0, &clsFunc.OnLogFont(16));
	m_pGridDevice.SetItemText(20, 0, _T("2"));

	m_pGridDevice.SetItemBkColour(20, 1, GREEN_D, BLACK_C);
	m_pGridDevice.SetItemFont(20, 1, &clsFunc.OnLogFont(16));
	m_pGridDevice.SetItemText(20, 1, _T("Hs Dir Skip"));

	if (m_nHsDirChkMode[1] == YES)
	{
		m_pGridDevice.SetItemBkColour(19, 0, GREEN_C, BLACK_C);
		m_pGridDevice.SetItemBkColour(19, 1, GREEN_C, BLACK_C);
	}
	else
	{
		m_pGridDevice.SetItemBkColour(20, 0, GREEN_C, BLACK_C);
		m_pGridDevice.SetItemBkColour(20, 1, GREEN_C, BLACK_C);
	}

	m_pGridDevice.MergeCells(21, 0, 21, 1);
	m_pGridDevice.SetItemBkColour(21, 0, RGB(219, 229, 241), BLACK_L);
	m_pGridDevice.SetItemFont(21, 0, &clsFunc.OnLogFont(16));
	m_pGridDevice.SetItemText(21, 0, _T("Module Dir Mode"));

	m_pGridDevice.SetItemBkColour(22, 0, GREEN_D, BLACK_C);
	m_pGridDevice.SetItemFont(22, 0, &clsFunc.OnLogFont(16));
	m_pGridDevice.SetItemText(22, 0, _T("1"));

	m_pGridDevice.SetItemBkColour(22, 1, GREEN_D, BLACK_C);
	m_pGridDevice.SetItemFont(22, 1, &clsFunc.OnLogFont(16));
	m_pGridDevice.SetItemText(22, 1, _T("Module Dir Use"));

	m_pGridDevice.SetItemBkColour(23, 0, GREEN_D, BLACK_C);
	m_pGridDevice.SetItemFont(23, 0, &clsFunc.OnLogFont(16));
	m_pGridDevice.SetItemText(23, 0, _T("2"));

	m_pGridDevice.SetItemBkColour(23, 1, GREEN_D, BLACK_C);
	m_pGridDevice.SetItemFont(23, 1, &clsFunc.OnLogFont(16));
	m_pGridDevice.SetItemText(23, 1, _T("Module Dir Skip"));

	if (m_nModuledirMode[1] == YES)
	{
		m_pGridDevice.SetItemBkColour(22, 0, GREEN_C, BLACK_C);
		m_pGridDevice.SetItemBkColour(22, 1, GREEN_C, BLACK_C);
	}
	else
	{
		m_pGridDevice.SetItemBkColour(23, 0, GREEN_C, BLACK_C);
		m_pGridDevice.SetItemBkColour(23, 1, GREEN_C, BLACK_C);
	}

	
	m_pGridDevice.Invalidate(FALSE);
}


void CScreenBasic::OnDeviceCellClick(NMHDR *pNotifyStruct, LRESULT* pResult)
{
	CDialog_Pass_Check  pass_chk_dlg;

	int nRow, nCol;

	CString strTmp;
	CString strMsg;

	NM_GRIDVIEW* pItem	= (NM_GRIDVIEW*) pNotifyStruct;

	nRow				= pItem->iRow;
	nCol				= pItem->iColumn;

	if(nRow < 1) return;

	if (nRow == 1 && m_nModeDevice[1] != WITHOUT_DVC)
	{
		if (st_lot_info[LOT_CURR].nLotStatus >= LOT_START || st_lot_info[LOT_NEXT].nLotStatus >= LOT_START)
		{
			if (st_handler_info.cWndList != NULL)
			{
				clsMem.OnNormalMessageWrite(_T("Data Change Fail. Lot Start Status...."));
				st_handler_info.cWndList->SendMessage(WM_LIST_DATA, 0, NORMAL_MSG);
			}

			return;
		}

		m_nModeDevice[1] = WITHOUT_DVC; 

		m_pGridDevice.SetItemBkColour(1, 0, RGB(79, 79, 225), WHITE_C);
		m_pGridDevice.SetItemBkColour(1, 1, RGB(79, 79, 225), WHITE_C);

		m_pGridDevice.SetItemBkColour(2, 0, BLACK_L, YELLOW_C);
		m_pGridDevice.SetItemBkColour(2, 1, BLACK_L, YELLOW_C);
	}
	else if (nRow == 2 && m_nModeDevice[1] != WITH_DVC)
	{
		if (st_lot_info[LOT_CURR].nLotStatus >= LOT_START || st_lot_info[LOT_NEXT].nLotStatus >= LOT_START)
		{
			if (st_handler_info.cWndList != NULL)
			{
				clsMem.OnNormalMessageWrite(_T("Data Change Fail. Lot Start Status...."));
				st_handler_info.cWndList->SendMessage(WM_LIST_DATA, 0, NORMAL_MSG);
			}

			return;
		}

		m_nModeDevice[1] = WITH_DVC;

		m_pGridDevice.SetItemBkColour(1, 0, BLACK_L, YELLOW_C);
		m_pGridDevice.SetItemBkColour(1, 1, BLACK_L, YELLOW_C);

		m_pGridDevice.SetItemBkColour(2, 0, RGB(79, 79, 225), WHITE_C);
		m_pGridDevice.SetItemBkColour(2, 1, RGB(79, 79, 225), WHITE_C);
	}
	else if (nRow == 4 && m_nModeInterface[1] != EQP_OFF_LINE)
	{
		if (st_lot_info[LOT_CURR].nLotStatus >= LOT_START || st_lot_info[LOT_NEXT].nLotStatus >= LOT_START)
		{
			if (st_handler_info.cWndList != NULL)
			{
				clsMem.OnNormalMessageWrite(_T("Data Change Fail. Lot Start Status...."));
				st_handler_info.cWndList->SendMessage(WM_LIST_DATA, 0, NORMAL_MSG);
			}

			return;
		}

		m_nModeInterface[1] = EQP_OFF_LINE;

		m_pGridDevice.SetItemBkColour(4, 0, GREEN_C, BLACK_C);
		m_pGridDevice.SetItemBkColour(4, 1, GREEN_C, BLACK_C);

		m_pGridDevice.SetItemBkColour(5, 0, GREEN_D, BLACK_C);
		m_pGridDevice.SetItemBkColour(5, 1, GREEN_D, BLACK_C);
	}
	else if (nRow == 5 && m_nModeInterface[1] != EQP_ON_LINE)
	{
		if (st_lot_info[LOT_CURR].nLotStatus >= LOT_START || st_lot_info[LOT_NEXT].nLotStatus >= LOT_START)
		{
			if (st_handler_info.cWndList != NULL)
			{
				clsMem.OnNormalMessageWrite(_T("Data Change Fail. Lot Start Status...."));
				st_handler_info.cWndList->SendMessage(WM_LIST_DATA, 0, NORMAL_MSG);
			}

			return;
		}

		m_nModeInterface[1] = EQP_ON_LINE;

		m_pGridDevice.SetItemBkColour(4, 0, GREEN_D, BLACK_C);
		m_pGridDevice.SetItemBkColour(4, 1, GREEN_D, BLACK_C);

		m_pGridDevice.SetItemBkColour(5, 0, GREEN_C, BLACK_C);
		m_pGridDevice.SetItemBkColour(5, 1, GREEN_C, BLACK_C);
	}
	else if (nRow == 7 && m_nModeRearSmema[1] != NO)
	{
/*
		if (st_lot_info[LOT_CURR].nLotStatus >= LOT_START || st_lot_info[LOT_NEXT].nLotStatus >= LOT_START)
		{
			if (st_handler_info.cWndList != NULL)
			{
				clsMem.OnNormalMessageWrite(_T("Data Change Fail. Lot Start Status...."));
				st_handler_info.cWndList->SendMessage(WM_LIST_DATA, 0, NORMAL_MSG);
			}

			return;
		}
*/
		m_nModeRearSmema[1] = NO;

		m_pGridDevice.SetItemBkColour(7, 0, GREEN_C, BLACK_C);
		m_pGridDevice.SetItemBkColour(7, 1, GREEN_C, BLACK_C);

		m_pGridDevice.SetItemBkColour(8, 0, GREEN_D, BLACK_C);
		m_pGridDevice.SetItemBkColour(8, 1, GREEN_D, BLACK_C);
	}
	else if (nRow == 8 && m_nModeRearSmema[1] != YES)
	{
/*		
		if (st_lot_info[LOT_CURR].nLotStatus >= LOT_START || st_lot_info[LOT_NEXT].nLotStatus >= LOT_START)
		{
			if (st_handler_info.cWndList != NULL)
			{
				clsMem.OnNormalMessageWrite(_T("Data Change Fail. Lot Start Status...."));
				st_handler_info.cWndList->SendMessage(WM_LIST_DATA, 0, NORMAL_MSG);
			}

			return;
		}
*/
		m_nModeRearSmema[1] = YES;

		m_pGridDevice.SetItemBkColour(7, 0, GREEN_D, BLACK_C);
		m_pGridDevice.SetItemBkColour(7, 1, GREEN_D, BLACK_C);

		m_pGridDevice.SetItemBkColour(8, 0, GREEN_C, BLACK_C);
		m_pGridDevice.SetItemBkColour(8, 1, GREEN_C, BLACK_C);
	}
	else if (nRow == 10 && m_nModeRfid[1] != NO)
	{
		if (st_lot_info[LOT_CURR].nLotStatus >= LOT_START || st_lot_info[LOT_NEXT].nLotStatus >= LOT_START)
		{
			if (st_handler_info.cWndList != NULL)
			{
				clsMem.OnNormalMessageWrite(_T("Data Change Fail. Lot Start Status...."));
				st_handler_info.cWndList->SendMessage(WM_LIST_DATA, 0, NORMAL_MSG);
			}

			return;
		}

		m_nModeRfid[1] = NO;

		m_pGridDevice.SetItemBkColour(10, 0, GREEN_C, BLACK_C);
		m_pGridDevice.SetItemBkColour(10, 1, GREEN_C, BLACK_C);

		m_pGridDevice.SetItemBkColour(11, 0, GREEN_D, BLACK_C);
		m_pGridDevice.SetItemBkColour(11, 1, GREEN_D, BLACK_C);

	}
	else if (nRow == 11 && m_nModeRfid[1] != YES)
	{
		if (st_lot_info[LOT_CURR].nLotStatus >= LOT_START || st_lot_info[LOT_NEXT].nLotStatus >= LOT_START)
		{
			if (st_handler_info.cWndList != NULL)
			{
				clsMem.OnNormalMessageWrite(_T("Data Change Fail. Lot Start Status...."));
				st_handler_info.cWndList->SendMessage(WM_LIST_DATA, 0, NORMAL_MSG);
			}

			return;
		}

		m_nModeRfid[1] = YES;

		m_pGridDevice.SetItemBkColour(10, 0, GREEN_D, BLACK_C);
		m_pGridDevice.SetItemBkColour(10, 1, GREEN_D, BLACK_C);

		m_pGridDevice.SetItemBkColour(11, 0, GREEN_C, BLACK_C);
		m_pGridDevice.SetItemBkColour(11, 1, GREEN_C, BLACK_C);
	}

	m_pGridDevice.Invalidate();
}

void CScreenBasic::OnInitGridModelList()
{
	CString strTmp;
	
	m_pGridModel.SetFrameFocusCell(FALSE);
	m_pGridModel.SetTrackFocusCell(FALSE);
	m_pGridModel.EnableSelection(FALSE);

	m_pGridModel.SetGridLineColor(BLACK_C);
	m_pGridModel.SetGridLines(1);

	m_pGridModel.SetRowCount(1);
	m_pGridModel.SetColumnCount(1);

	m_pGridModel.SetFixedRowCount(0);
	m_pGridModel.SetFixedColumnCount(0);
	m_pGridModel.SetFixedBkColor(RGB(0,0,200));
	m_pGridModel.SetFixedBkColor(RGB(200,200,255));
	m_pGridModel.SetTextBkColor(RGB(150,150,200));

	m_pGridModel.SetRowHeight(0, 50);
	m_pGridModel.SetColumnWidth(0, 200);

	m_pGridModel.SetItemFormat(0, 0, DT_CENTER|DT_VCENTER|DT_SINGLELINE);
	m_pGridModel.SetItemState(0, 0, GVIS_READONLY);
	m_pGridModel.SetItemBkColour(0, 0, WHITE_C, CLR_DEFAULT);

	m_pGridModel.SetItemBkColour(0, 0, RGB(219, 229, 241), BLACK_L);
	m_pGridModel.SetItemFont(0, 0, &clsFunc.OnLogFont(18));
	m_pGridModel.SetItemText(0, 0, _T("Model Name"));

	//OnInitModelList(st_path_info.strBasic);
	//kwlee 2017.0511
	OnInitModelList(st_path_info.strpathModel);
}

void CScreenBasic::OnModelCellClick(NMHDR *pNotifyStruct, LRESULT* pResult)
{
	CDialog_Message dlgMsg;
	int nRow, nCol;
	INT_PTR nResponse;

	CString strTmp;
	CString strMsg;

	NM_GRIDVIEW* pItem	= (NM_GRIDVIEW*) pNotifyStruct;

	nRow				= pItem->iRow;
	nCol				= pItem->iColumn;

	if (nRow < 1) return;

	if (st_lot_info[LOT_CURR].nLotStatus >= LOT_START || st_lot_info[LOT_NEXT].nLotStatus >= LOT_START)
	{
		if (st_handler_info.cWndList != NULL)
		{
			clsMem.OnNormalMessageWrite(_T("Data Change Fail. Lot Start Status...."));
			st_handler_info.cWndList->SendMessage(WM_LIST_DATA, 0, NORMAL_MSG);
		}

		return;
	}

	strTmp = m_pGridModel.GetItemText(nRow, nCol);

	dlgMsg.m_nMessageType	= 1;
	dlgMsg.m_strMessage.Format(_T("[%s] Model\r\nDo you want a clicked model?"), strTmp);

	nResponse = dlgMsg.DoModal();
		
	if(nResponse == IDOK)
	{
		if(OnModelDeviceCheck(strTmp) == false)  // 입력된 디바이스 이름 정상 유무 검사 함수
		{
			return ;
		}

		m_strDeviceName[1]			= strTmp;
		st_basic_info.strDeviceName	= m_strDeviceName[1];
			
		clsBasic.OnBasic_Data_Load(1);
		clsBasic.OnModuleRobot_Teach_Data_Load(st_basic_info.strDeviceName);
		clsBasic.OnMaintenance_Data_Load();
		clsBasic.OnWaitTime_Data_Load();
		clsBasic.OnMotorSpeed_Set_Data_Load();
		clsBasic.OnInterface_Data_Load();
		clsBasic.OnRecipe_Data_Load(st_basic_info.strDeviceName);
			
		OnDataInit();
		OnInitGridDeviceMode();

		OnDeviceColorChange(nRow, nCol);

		// jtkim 20150929
		::SendMessage(st_handler_info.hWnd, WM_CLIENT_MSG + FTP_NETWORK, 1, 0);

		m_pGridModel.Refresh();// .Invalidate();
	}
	else
	{
		m_pGridModel.SetItemBkColour(nRow, nCol, RGB(79, 79, 225), WHITE_C);
	}
}

void CScreenBasic::OnModelCellRClick(NMHDR *pNotifyStruct, LRESULT* pResult)
{
	CDialog_Message dlgMsg;
	CDialog_Pass_Check	dlgPass;

	int nRow, nCol;
	INT_PTR nResponse;

	CString strTmp;
	CString strMsg;

	NM_GRIDVIEW* pItem	= (NM_GRIDVIEW*) pNotifyStruct;

	nRow				= pItem->iRow;
	nCol				= pItem->iColumn;

	if (nRow < 1) return;

	st_other_info.strPassLevel = _T("AMT_MASTER");

	dlgPass.m_nPassLevel = 6;
	nResponse = (int)dlgPass.DoModal();

	if (nResponse == IDOK)
	{
		strTmp = m_pGridModel.GetItemText(nRow, nCol);

		dlgMsg.m_nMessageType	= 1;
		dlgMsg.m_strMessage.Format(_T("[%s] Model\r\nDo you want a clicked model?"), strTmp);

		nResponse = dlgMsg.DoModal();

		if(nResponse == IDOK)
		{
			if(OnModelDeviceCheck(strTmp) == false)  // 입력된 디바이스 이름 정상 유무 검사 함수
			{
				return ;
			}

			m_strDeviceName[1]			= strTmp;
			st_basic_info.strDeviceName	= m_strDeviceName[1];

			clsBasic.OnBasic_Data_Load(1);
			clsBasic.OnModuleRobot_Teach_Data_Load(st_basic_info.strDeviceName);
			clsBasic.OnMaintenance_Data_Load();
			clsBasic.OnWaitTime_Data_Load();
			clsBasic.OnMotorSpeed_Set_Data_Load();
			clsBasic.OnInterface_Data_Load();
			clsBasic.OnRecipe_Data_Load(st_basic_info.strDeviceName);

			OnDataInit();
			OnInitGridDeviceMode();

			OnDeviceColorChange(nRow, nCol);

			m_pGridModel.Refresh();// .Invalidate();
		}
		else
		{
			m_pGridModel.SetItemBkColour(nRow, nCol, RGB(79, 79, 225), WHITE_C);
		}
	}
	else 
	{
		return;
	}
}

void CScreenBasic::OnDeviceColorChange(int nSelectRow, int nSelectCol)
{
	int nTotRowCnt;
	nTotRowCnt = m_pGridModel.GetRowCount();

	m_nDeviceName = nSelectRow;

	m_pGridModel.SetItemBkColour(m_nDeviceName, nSelectCol, RGB(79, 79, 225), WHITE_C);

	for(int i=1; i< nTotRowCnt; i++)
	{
		if(i != m_nDeviceName) 
		{
			m_pGridModel.SetItemBkColour(i, nSelectCol, BLACK_L, WHITE_C);
		}
	}

	m_nOldDeviceName = m_nDeviceName;

}

void CScreenBasic::OnDataHistoryLog()
{
	CString strMsg;

	if (m_nModeDevice[0]		!= m_nModeDevice[1])
	{
		strMsg.Format(_T("[BASIC] Device Mode Change %d -> %d"), m_nModeDevice[0], m_nModeDevice[1]);
		clsFunc.OnLogFileAdd(0, strMsg);
	}

	if (m_nModeInterface[0]		!= m_nModeInterface[1])
	{
		strMsg.Format(_T("[BASIC] Interface Mode Change %d -> %d"), m_nModeInterface[0], m_nModeInterface[1]);
		clsFunc.OnLogFileAdd(0, strMsg);
	}

	if (m_nModeSecsGem[0]		!= m_nModeSecsGem[1])
	{
		strMsg.Format(_T("[BASIC] SecsGem Mode Change %d -> %d"), m_nModeSecsGem[0], m_nModeSecsGem[1]);
		clsFunc.OnLogFileAdd(0, strMsg);
	}

	if (m_nModeWork[0]		!= m_nModeWork[1])
	{
		strMsg.Format(_T("[BASIC] Work Mode Change %d -> %d"), m_nModeWork[0], m_nModeWork[1]);
		clsFunc.OnLogFileAdd(0, strMsg);
	}

	if (m_strDeviceName[0]		!= m_strDeviceName[1])
	{
		strMsg.Format(_T("[BASIC] Device Name Change %s -> %s"), m_strDeviceName[0], m_strDeviceName[1]);
		clsFunc.OnLogFileAdd(0, strMsg);
	}

	if (m_nModeFrontSmema[0]			!= m_nModeFrontSmema[1])
	{
		strMsg.Format(_T("[BASIC] Front Smema Check Mode Change %d -> %d"), m_nModeFrontSmema[0], m_nModeFrontSmema[1]);
		clsFunc.OnLogFileAdd(0, strMsg);
	}

	if (m_nModeRearSmema[0]			!= m_nModeRearSmema[1])
	{
		strMsg.Format(_T("[BASIC] Rear Smema Check Mode Change %d -> %d"), m_nModeRearSmema[0], m_nModeRearSmema[1]);
		clsFunc.OnLogFileAdd(0, strMsg);
	}
	
	if (m_nModeRfid[0]			!= m_nModeRfid[1])
	{
		strMsg.Format(_T("[BASIC] RFID Mode Change %d -> %d"), m_nModeRfid[0], m_nModeRfid[1]);
		clsFunc.OnLogFileAdd(0, strMsg);
	}

	
	if (m_strModelName[0]		!= m_strModelName[1])
	{
		strMsg.Format(_T("[BASIC] Model Name Change %s -> %s"), m_strModelName[0], m_strModelName[1]);
		clsFunc.OnLogFileAdd(0, strMsg);
	}

	//kwlee 2017.0515
	if (m_nClipRemoverErrorMode[0]		!= m_nClipRemoverErrorMode[1])
	{
		strMsg.Format(_T("[BASIC] Clip Remover Error Mode Change %d -> %d"), m_nClipRemoverErrorMode[0], m_nClipRemoverErrorMode[1]);
		clsFunc.OnLogFileAdd(0, strMsg);
	}

	if (m_nCapRemoverMode[0]		!= m_nCapRemoverMode[1])
	{
		strMsg.Format(_T("[BASIC] Cap Remover Mode Change %d -> %d"), m_nCapRemoverMode[0], m_nCapRemoverMode[1]);
		clsFunc.OnLogFileAdd(0, strMsg);
	}

	if (m_nSorterPickerMode[0]		!= m_nSorterPickerMode[1])
	{
		strMsg.Format(_T("[BASIC] SorterPicker Mode Change %d -> %d"), m_nSorterPickerMode[0], m_nSorterPickerMode[1]);
		clsFunc.OnLogFileAdd(0, strMsg);
	}

	if (m_nHsDirChkMode[0]		!= m_nHsDirChkMode[1])
	{
		strMsg.Format(_T("[BASIC] HeatSink Direction Chk Mode Change %d -> %d"), m_nHsDirChkMode[0], m_nHsDirChkMode[1]);
		clsFunc.OnLogFileAdd(0, strMsg);
	}

	if (m_nModuledirMode[0]		!= m_nModuledirMode[1])
	{
		strMsg.Format(_T("[BASIC] Module direction Mode Change %s -> %s"), m_nModuledirMode[0], m_nModuledirMode[1]);
		clsFunc.OnLogFileAdd(0, strMsg);
	}

	if (m_nLotSet_Module_Load[0]			!= m_nLotSet_Module_Load[1])
	{
		strMsg.Format(_T("[BASIC] LotSet_Module_Load Change %d -> %d"), m_nLotSet_Module_Load[0], m_nLotSet_Module_Load[1]);
		clsFunc.OnLogFileAdd(0, strMsg);
	}

	if (m_nModeRearSmema[0]			!= m_nModeRearSmema[1])
	{
		strMsg.Format(_T("[BASIC] Rear Smema Check Mode Change %d -> %d"), m_nModeRearSmema[0], m_nModeRearSmema[1]);
		clsFunc.OnLogFileAdd(0, strMsg);
	}

	if (m_nLotSet_HeatSinkLeft[0]			!= m_nLotSet_HeatSinkLeft[1])
	{
		strMsg.Format(_T("[BASIC] LotSet_HeatSink Left Change %d -> %d"), m_nLotSet_HeatSinkLeft[0], m_nLotSet_HeatSinkLeft[1]);
		clsFunc.OnLogFileAdd(0, strMsg);
	}


	if (m_nLotSet_HeatSinkRight[0]		!= m_nLotSet_HeatSinkRight[1])
	{
		strMsg.Format(_T("[BASIC] LotSet_HeatSink Right Change %s -> %s"), m_nLotSet_HeatSinkRight[0], m_nLotSet_HeatSinkRight[1]);
		clsFunc.OnLogFileAdd(0, strMsg);
	}

	if (m_nLotSet_Clip[0]		!= m_nLotSet_Clip[1])
	{
		strMsg.Format(_T("[BASIC] LotSet_Clip Change %d -> %d"), m_nLotSet_Clip[0], m_nLotSet_Clip[1]);
		clsFunc.OnLogFileAdd(0, strMsg);
	}

	if (m_nLotSet_Unloader[0]		!= m_nLotSet_Unloader[1])
	{
		strMsg.Format(_T("[BASIC] LotSet_Unloader Change %d -> %d"), m_nLotSet_Unloader[0], m_nLotSet_Unloader[1]);
		clsFunc.OnLogFileAdd(0, strMsg);
	}

	if (m_nLotSet_Reject[0]		!= m_nLotSet_Reject[1])
	{
		strMsg.Format(_T("[BASIC] LotSet_Reject Change %d -> %d"), m_nLotSet_Reject[0], m_nLotSet_Reject[1]);
		clsFunc.OnLogFileAdd(0, strMsg);
	}

	if (m_nPicker_Gap_Module_Load[0]		!= m_nPicker_Gap_Module_Load[1])
	{
		strMsg.Format(_T("[BASIC] Picker_Gap_Module_Load Change %d -> %d"), m_nPicker_Gap_Module_Load[0], m_nPicker_Gap_Module_Load[1]);
		clsFunc.OnLogFileAdd(0, strMsg);
	}

	if (m_nPicker_Gap_HeatSink_Left[0]		!= m_nPicker_Gap_HeatSink_Left[1])
	{
		strMsg.Format(_T("[BASIC] Picker_Gap_HeatSink_Left Change %s -> %s"), m_nPicker_Gap_HeatSink_Left[0], m_nPicker_Gap_HeatSink_Left[1]);
		clsFunc.OnLogFileAdd(0, strMsg);
	}

	if (m_nPicker_Gap_HeatSink_Right[0]			!= m_nPicker_Gap_HeatSink_Right[1])
	{
		strMsg.Format(_T("[BASIC] Picker_Gap_HeatSink_Right Change %d -> %d"), m_nPicker_Gap_HeatSink_Right[0], m_nPicker_Gap_HeatSink_Right[1]);
		clsFunc.OnLogFileAdd(0, strMsg);
	}

	if (m_nAlarm_Delay[0]			!= m_nAlarm_Delay[1])
	{
		strMsg.Format(_T("[BASIC] Alarm_Delay Time Change %d -> %d"), m_nAlarm_Delay[0], m_nAlarm_Delay[1]);
		clsFunc.OnLogFileAdd(0, strMsg);
	}

	if (m_nNetwork_Wait_Time[0]			!= m_nNetwork_Wait_Time[1])
	{
		strMsg.Format(_T("[BASIC] Network_Wait_Time Change %d -> %d"), m_nNetwork_Wait_Time[0], m_nNetwork_Wait_Time[1]);
		clsFunc.OnLogFileAdd(0, strMsg);
	}

	if (m_nNetwork_Retry_Cnt[0]		!= m_nNetwork_Retry_Cnt[1])
	{
		strMsg.Format(_T("[BASIC]Network_Retry_Cnt Change %s -> %s"), m_nNetwork_Retry_Cnt[0], m_nNetwork_Retry_Cnt[1]);
		clsFunc.OnLogFileAdd(0, strMsg);
	}

	if (m_nLabel_Bin_Printer[0]		!= m_nLabel_Bin_Printer[1])
	{
		strMsg.Format(_T("[BASIC] Label_Bin_Printer Change %s -> %s"), m_nLabel_Bin_Printer[0], m_nLabel_Bin_Printer[1]);
		clsFunc.OnLogFileAdd(0, strMsg);
	}

	if (m_nLabel_Vision_Paper[0]		!= m_nLabel_Vision_Paper[1])
	{
		strMsg.Format(_T("[BASIC] Label_Vision_Paper Change %s -> %s"), m_nLabel_Vision_Paper[0], m_nLabel_Vision_Paper[1]);
		clsFunc.OnLogFileAdd(0, strMsg);
	}

	if (m_nLabel_Error_Cnt[0]		!= m_nLabel_Error_Cnt[1])
	{
		strMsg.Format(_T("[BASIC] Label_Error_Cnt Change %s -> %s"), m_nLabel_Error_Cnt[0], m_nLabel_Error_Cnt[1]);
		clsFunc.OnLogFileAdd(0, strMsg);
	}

	if (m_nDvc_Repick_Cnt[0]		!= m_nDvc_Repick_Cnt[1])
	{
		strMsg.Format(_T("[BASIC] Dvc_Repick_Cnt Change %s -> %s"), m_nDvc_Repick_Cnt[0], m_nDvc_Repick_Cnt[1]);
		clsFunc.OnLogFileAdd(0, strMsg);
	}
}

void CScreenBasic::OnDataRecovery()
{
	m_nModeDevice[1]		= m_nModeDevice[0];			// [Title Bar 상태 표시] < WHIT/WHIT OUT ㅡ MODE 표시
	m_nModeInterface[1]		= m_nModeInterface[0];
	m_nModeSecsGem[1]		= m_nModeSecsGem[0];

	m_strDeviceName[1]		= m_strDeviceName[0];		// [Title Bar 상태 표시] < 장비에서 설정한 DEVICE 표시	>

	m_nModeFrontSmema[1]	= m_nModeFrontSmema[0];
	m_nModeRearSmema[1]		= m_nModeRearSmema[0];
	m_nModeRfid[1]			= m_nModeRfid[0];
	
	m_strModelName[1]		= m_strModelName[0];

	//kwlee 2017.0515
	m_nLotSet_Module_Load[1]		=	m_nLotSet_Module_Load[0];
	m_nLotSet_HeatSinkLeft[1]		=	m_nLotSet_HeatSinkLeft[0];
	m_nLotSet_HeatSinkRight[1]		=	m_nLotSet_HeatSinkRight[0];
	m_nLotSet_Clip[1]				=	m_nLotSet_Clip[0];
	m_nLotSet_Unloader[1]			=	m_nLotSet_Unloader[0];
	m_nLotSet_Reject[1]				=	m_nLotSet_Reject[0];

	m_nPicker_Gap_Module_Load[1]	=  m_nPicker_Gap_Module_Load[0];
	m_nPicker_Gap_HeatSink_Left[1]  =  m_nPicker_Gap_HeatSink_Left[0];
	m_nPicker_Gap_HeatSink_Right[1]	=  m_nPicker_Gap_HeatSink_Right[0];

	m_nNetwork_Wait_Time[1]	   =  m_nNetwork_Wait_Time[0];
	m_nNetwork_Retry_Cnt[1]	   =  m_nNetwork_Retry_Cnt[0];
	m_nLabel_Bin_Printer[1]	   =  m_nLabel_Bin_Printer[0];
	m_nLabel_Error_Cnt[1]	   =  m_nLabel_Error_Cnt[0];
	m_nLabel_Vision_Paper[1]   =  m_nLabel_Vision_Paper[0];
	m_nAlarm_Delay[1]		   =  m_nAlarm_Delay[0];
	m_nDvc_Repick_Cnt[1]	   =  m_nDvc_Repick_Cnt[0];

	m_nCapRemoverMode[1]	   =  m_nCapRemoverMode[0];
	m_nClipRemoverErrorMode[1] =  m_nClipRemoverErrorMode[0];
	m_nModuledirMode[1]		   =  m_nModuledirMode[0];
	m_nHsDirChkMode[1]		   =  m_nHsDirChkMode[0];
	m_nSorterPickerMode[1]	   =  m_nSorterPickerMode[0];
}


int	CScreenBasic::OnDataComparison()
{
	if (m_nModeDevice[0]		!= m_nModeDevice[1])			return RET_ERROR;			// [Title Bar 상태 표시] < WHIT/WHIT OUT ㅡ MODE 표시
	if (m_nModeInterface[0]		!= m_nModeInterface[1])			return RET_ERROR;
	if (m_nModeSecsGem[0]		!= m_nModeSecsGem[1])			return RET_ERROR;
	if (m_nModeWork[0]			!= m_nModeWork[1])				return RET_ERROR;

	if (m_strDeviceName[0]		!= m_strDeviceName[1])			return RET_ERROR;		// [Title Bar 상태 표시] < 장비에서 설정한 DEVICE 표시	>

	if (m_nModeFrontSmema[0]	!= m_nModeFrontSmema[1])		return RET_ERROR;
	if (m_nModeRearSmema[0]		!= m_nModeRearSmema[1])			return RET_ERROR;
	if (m_nModeRfid[0]			!= m_nModeRfid[1])				return RET_ERROR;
	if (m_strModelName[0]		!= m_strModelName[1])			return RET_ERROR;

	//kwlee 2017.0515
	if (m_nLotSet_Module_Load[1]		!=	m_nLotSet_Module_Load[0]) return RET_ERROR;
	if (m_nLotSet_HeatSinkLeft[1]		!=	m_nLotSet_HeatSinkLeft[0]) return RET_ERROR;
	if (m_nLotSet_HeatSinkRight[1]		!=	m_nLotSet_HeatSinkRight[0]) return RET_ERROR;
	if (m_nLotSet_Clip[1]				!=	m_nLotSet_Clip[0]) return RET_ERROR;
	if (m_nLotSet_Unloader[1]			!=	m_nLotSet_Unloader[0]) return RET_ERROR;
	if (m_nLotSet_Reject[1]				!=	m_nLotSet_Reject[0]) return RET_ERROR;

	if (m_nPicker_Gap_Module_Load[1]	!=  m_nPicker_Gap_Module_Load[0]) return RET_ERROR;
	if (m_nPicker_Gap_HeatSink_Left[1]  !=  m_nPicker_Gap_HeatSink_Left[0]) return RET_ERROR;
	if (m_nPicker_Gap_HeatSink_Right[1]	!=  m_nPicker_Gap_HeatSink_Right[0]) return RET_ERROR;

	if (m_nNetwork_Wait_Time[1]	   !=  m_nNetwork_Wait_Time[0]) return RET_ERROR;
	if (m_nNetwork_Retry_Cnt[1]	   !=  m_nNetwork_Retry_Cnt[0]) return RET_ERROR;
	if (m_nLabel_Bin_Printer[1]	   !=  m_nLabel_Bin_Printer[0]) return RET_ERROR;
	if (m_nLabel_Error_Cnt[1]	   !=  m_nLabel_Error_Cnt[0]) return RET_ERROR;
	if (m_nLabel_Vision_Paper[1]   !=  m_nLabel_Vision_Paper[0]) return RET_ERROR;
	if (m_nAlarm_Delay[1]		   !=  m_nAlarm_Delay[0]) return RET_ERROR;
	if (m_nDvc_Repick_Cnt[1]	   !=  m_nDvc_Repick_Cnt[0]) return RET_ERROR;

	if (m_nCapRemoverMode[1]	   !=  m_nCapRemoverMode[0]) return RET_ERROR;
	if (m_nClipRemoverErrorMode[1] !=  m_nClipRemoverErrorMode[0]) return RET_ERROR;
	if (m_nModuledirMode[1]		   !=  m_nModuledirMode[0]) return RET_ERROR;
	if (m_nHsDirChkMode[1]		   !=  m_nHsDirChkMode[0]) return RET_ERROR;
	if (m_nSorterPickerMode[1]	   !=  m_nSorterPickerMode[0]) return RET_ERROR;
	
	return RET_GOOD;
}


void CScreenBasic::OnDataApply()
{
	st_basic_info.nModeDevice		= m_nModeDevice[1];;	// [Title Bar 상태 표시] < WHIT/WHIT OUT ㅡ MODE 표시	>
	st_basic_info.nModeInterface	= m_nModeInterface[1];
//	st_basic_info.nModeSecsGem		= m_nModeSecsGem[1];
	st_basic_info.nModeWork			= m_nModeWork[1];
	st_basic_info.strDeviceName		= m_strDeviceName[1];	// [Title Bar 상태 표시] < 장비에서 설정한 DEVICE 표시	>
	st_basic_info.nModeFrontSmema	= m_nModeFrontSmema[1];
	st_basic_info.nModeRearSmema	= m_nModeRearSmema[1];
	// jtkim 20150625 in-line
	if (st_basic_info.nModeRearSmema == YES)
	{
		if (st_lot_info[LOT_NEXT].nLotStatus == LOT_START)
		{
			if (st_lot_info[LOT_NEXT].nTrayRunMode_StandAlone == YES)
			{
				st_lot_info[LOT_NEXT].nTrayRunMode_StandAlone = NO;

				if (st_handler_info.cWndList != NULL)  
				{
					clsMem.OnNormalMessageWrite(_T("Next Lot In-line Mode Success"));
					st_handler_info.cWndList->SendMessage(WM_LIST_DATA, 0, NORMAL_MSG); 
				}
			}
		}
	}

	st_basic_info.strModelName		= m_strModelName[1];
	//kwlee 2017.0515
	st_basic_info.nLotSetModuleLoad = m_nLotSet_Module_Load[1];
	st_basic_info.nLotSetHeatSinkLeft = m_nLotSet_HeatSinkLeft[1];
	st_basic_info.nLotSetHeatSinkRight = m_nLotSet_HeatSinkRight[1];
	st_basic_info.nLotSetClip = m_nLotSet_Clip[1];
	st_basic_info.nLotSetUnloader = m_nLotSet_Unloader[1];
	st_basic_info.nLotSetReject = m_nLotSet_Reject[1];

	st_basic_info.nPickGapModuleLoad = m_nPicker_Gap_Module_Load[1];
	st_basic_info.nPickGapHeatSinkLeft = m_nPicker_Gap_HeatSink_Left[1];
	st_basic_info.nPickGapHeatSinkRight = m_nPicker_Gap_HeatSink_Right[1];

	st_basic_info.nNetworkWaitTime = m_nNetwork_Wait_Time[1];
	st_basic_info.nNetworkRetryCnt = m_nNetwork_Retry_Cnt[1];
	st_basic_info.nLabelBinPrint = m_nLabel_Bin_Printer[1];
	st_basic_info.nLabelErrorCnt = m_nLabel_Error_Cnt[1];
	st_basic_info.nLabelVisionPaper = m_nLabel_Vision_Paper[1];
	st_basic_info.nAlarmDelayTime = m_nAlarm_Delay[1];
	st_basic_info.nDvcRepickCnt = m_nDvc_Repick_Cnt[1];

	st_basic_info.n_mode_cap_remove = m_nCapRemoverMode[1];
	st_basic_info.n_mode_clip_alarm = m_nClipRemoverErrorMode[1];
	st_basic_info.n_mode_m_direction = m_nModuledirMode[1];
	st_basic_info.n_mode_hs_direction = m_nHsDirChkMode[1];
	st_basic_info.n_mode_use_sorter_picker = m_nSorterPickerMode[1];


}

void CScreenBasic::OnDataBackup()
{
	m_nModeDevice[0]		= m_nModeDevice[1];			// [Title Bar 상태 표시] < WHIT/WHIT OUT ㅡ MODE 표시
	m_nModeInterface[0]		= m_nModeInterface[1];
	m_nModeSecsGem[0]		= m_nModeSecsGem[1];
	m_nModeWork[0]			= m_nModeWork[1];
	m_strDeviceName[0]		= m_strDeviceName[1];		// [Title Bar 상태 표시] < 장비에서 설정한 DEVICE 표시	>
	m_nModeFrontSmema[0]	= m_nModeFrontSmema[1];
	m_nModeRearSmema[0]		= m_nModeRearSmema[1];
	m_nModeRfid[0]			= m_nModeRfid[1];
	m_strModelName[0]		= m_strModelName[1];

	//kwlee 2017.0515
	m_nLotSet_Module_Load[0]		=	m_nLotSet_Module_Load[1];
	m_nLotSet_HeatSinkLeft[0]		=	m_nLotSet_HeatSinkLeft[1];
	m_nLotSet_HeatSinkRight[0]		=	m_nLotSet_HeatSinkRight[1];
	m_nLotSet_Clip[0]				=	m_nLotSet_Clip[1];
	m_nLotSet_Unloader[0]			=	m_nLotSet_Unloader[1];
	m_nLotSet_Reject[0]				=	m_nLotSet_Reject[1];

	m_nPicker_Gap_Module_Load[0]	=  m_nPicker_Gap_Module_Load[1];
	m_nPicker_Gap_HeatSink_Left[0]  =  m_nPicker_Gap_HeatSink_Left[1];
	m_nPicker_Gap_HeatSink_Right[0]	=  m_nPicker_Gap_HeatSink_Right[1];

	m_nNetwork_Wait_Time[0]	   =  m_nNetwork_Wait_Time[1];
	m_nNetwork_Retry_Cnt[0]	   =  m_nNetwork_Retry_Cnt[1];
	m_nLabel_Bin_Printer[0]	   =  m_nLabel_Bin_Printer[1];
	m_nLabel_Error_Cnt[0]	   =  m_nLabel_Error_Cnt[1];
	m_nLabel_Vision_Paper[0]   =  m_nLabel_Vision_Paper[1];
	m_nAlarm_Delay[0]		   =  m_nAlarm_Delay[1];
	m_nDvc_Repick_Cnt[0]	   =  m_nDvc_Repick_Cnt[1];

	m_nCapRemoverMode[0]	   =  m_nCapRemoverMode[1];
	m_nClipRemoverErrorMode[0] =  m_nClipRemoverErrorMode[1];
	m_nModuledirMode[0]		   =  m_nModuledirMode[1];
	m_nHsDirChkMode[0]		   =  m_nHsDirChkMode[1];
	m_nSorterPickerMode[0]	   =  m_nSorterPickerMode[1];
}


void CScreenBasic::OnDataInit()
{
	m_nModeDevice[1]					= st_basic_info.nModeDevice;
	m_strDeviceName[1]					= st_basic_info.strDeviceName;

	m_nModeInterface[1]					= st_basic_info.nModeInterface;
//	m_nModeSecsGem[1]					= st_basic_info.nModeSecsGem;
	m_nModeWork[1]						= st_basic_info.nModeWork;
	m_nModeFrontSmema[1]				= st_basic_info.nModeFrontSmema;
	m_nModeRearSmema[1]					= st_basic_info.nModeRearSmema;
	m_nModeRfid[1]						= st_basic_info.nModeRfid;
	m_strModelName[1]					= st_basic_info.strModelName;

	//kwlee 2017.0515
	m_nLotSet_Module_Load[1]	=		st_basic_info.nLotSetModuleLoad;		 
	m_nLotSet_HeatSinkLeft[1]	=		st_basic_info.nLotSetHeatSinkLeft;		 
	m_nLotSet_HeatSinkRight[1]	=		st_basic_info.nLotSetHeatSinkRight;	 
	m_nLotSet_Clip[1]			=		st_basic_info.nLotSetClip;				 
	m_nLotSet_Unloader[1]		=		st_basic_info.nLotSetUnloader;			 
	m_nLotSet_Reject[1]			=		st_basic_info.nLotSetReject;			 
											 
	m_nPicker_Gap_Module_Load[1]	 =	st_basic_info.nPickGapModuleLoad;		 
	m_nPicker_Gap_HeatSink_Left[1]	 =	st_basic_info.nPickGapHeatSinkLeft;	 
	m_nPicker_Gap_HeatSink_Right[1]  =	st_basic_info.nPickGapHeatSinkRight;	 
											 
	m_nNetwork_Wait_Time[1]			=	st_basic_info.nNetworkWaitTime;		 
	m_nNetwork_Retry_Cnt[1]			=	st_basic_info.nNetworkRetryCnt;		 
	m_nLabel_Bin_Printer[1]			=	st_basic_info.nLabelBinPrint;			 
	m_nLabel_Error_Cnt[1]			=	st_basic_info.nLabelErrorCnt;			 
	m_nLabel_Vision_Paper[1]		=	st_basic_info.nLabelVisionPaper;		 
	m_nAlarm_Delay[1]				=	st_basic_info.nAlarmDelayTime;			 
	m_nDvc_Repick_Cnt[1]			=	st_basic_info.nDvcRepickCnt;			 
											 
	m_nCapRemoverMode[1]			=	st_basic_info.n_mode_cap_remove;		 
	m_nClipRemoverErrorMode[1]		=	st_basic_info.n_mode_clip_alarm;		 
	m_nModuledirMode[1]				=	st_basic_info.n_mode_m_direction;		 
	m_nHsDirChkMode[1]				=	st_basic_info.n_mode_hs_direction;		 
	m_nSorterPickerMode[1]			=	st_basic_info.n_mode_use_sorter_picker; 
	OnDataBackup();
}

int CScreenBasic::OnInitModelList(CString strFileName)
{
	int nCnt = 0;
	int nChk;						// 함수 리턴 플래그
	CString strTmp;

	HANDLE hFind;
    WIN32_FIND_DATA fd;

	if (strFileName.Right (1) != "\\")
	{
        strFileName += "\\";
	}
	
	strFileName += "*.*";
    
    if ((hFind = ::FindFirstFile ((LPCTSTR) strFileName, &fd)) != INVALID_HANDLE_VALUE) 
	{
        if (!(fd.dwFileAttributes & FILE_ATTRIBUTE_DIRECTORY)) 
		{
			nChk = OnAddItem(nCnt, &fd);
			if (nChk == RET_GOOD)
			{
				nCnt++;
			}
        }

        while (::FindNextFile (hFind, &fd)) 
		{
			nChk = RET_READY;
            if (!(fd.dwFileAttributes & FILE_ATTRIBUTE_DIRECTORY))
			{
				nChk = OnAddItem(nCnt, &fd);
				if (nChk == RET_ERROR) 
				{
					break;
				}
				else
				{
					nCnt++;
				}
			}
        }
		::FindClose(hFind);
    }
	
	return nCnt;
}

int CScreenBasic::OnAddItem(int nIndex, WIN32_FIND_DATA *pFd)
{
	CString strTempDvc;
	CString strDevice;
	CString strExpansion;
	int nPos;

	HICON	hIcon = NULL;

	strTempDvc = (pFd->cFileName);	// 파일 이름 설정

	strTempDvc.MakeUpper();
	
	/* ************************************************************************** */
	/* 파일 이름 중 확장자 확인                                                   */
	/* ************************************************************************** */
	nPos = strTempDvc.Find('.');		// 확장자 위치 설정
	
	if (nPos == -1)					// 확장자 미존재
	{
		strExpansion = _T("");
	}
	else								// 확장자 존재
	{
		strExpansion = strTempDvc.Mid(nPos + 1);
	}
	/* ************************************************************************** */

	if (strExpansion != _T("TXT"))
	{
		return RET_READY;	
	}

	strDevice = strTempDvc;			// 파일명 전체 화면 출력
	
	if (strDevice == m_strDeviceName[1])
	{
		m_nDeviceName = nIndex;
		OnDisplayModelList(1, nIndex, strDevice);
	}
	else
	{
		OnDisplayModelList(0, nIndex, strDevice);
	}
	/* ************************************************************************** */

    return RET_GOOD;
}

void CScreenBasic::OnDisplayModelList(int nMode, int nCount, CString strFileName)
{
	m_pGridModel.SetRowCount(nCount + 2); 
	m_pGridModel.SetColumnCount(1); 

	m_pGridModel.SetRowHeight(nCount + 1, 50);
	m_pGridModel.SetColumnWidth(0, 230);

	m_pGridModel.SetItemFormat(nCount + 1, 0, DT_CENTER|DT_VCENTER|DT_SINGLELINE);
	m_pGridModel.SetItemState(nCount + 1, 0, GVIS_READONLY);
	m_pGridModel.SetItemBkColour(nCount + 1, 0, WHITE_C, CLR_DEFAULT);

	if(nMode == 0)
	{
		m_pGridModel.SetItemBkColour(nCount + 1, 0, BLACK_L, YELLOW_C);
	}
	else
	{
		m_pGridModel.SetItemBkColour(nCount + 1, 0, RGB(79, 79, 225), WHITE_C);
	}
	m_pGridModel.SetItemFont(nCount + 1, 0, &clsFunc.OnLogFont(16));
	m_pGridModel.SetItemText(nCount + 1, 0, strFileName);
}

void CScreenBasic::OnClickedBtnModelCreate()
{
	// TODO: Add your control notification handler code here
	int nPos;

	CString strTmp, strFileName;
	
	KeyBoard(&strFileName);

	if(strFileName != "")
	{
		nPos = -1;
		nPos = strFileName.Find(_T("."), 0);
		
		strTmp = _T("");
		if(nPos > 0)
		{
			strTmp = strFileName.Mid(nPos+1, 3);
		}
		
		if(strTmp != "TXT")
		{
			strFileName += ".TXT";
		}
		
		if(OnModelCreateDeviceCheck(strFileName) == FALSE)
		{
			return;
		}

		OnDataBackup();

		clsBasic.OnBasic_Data_Save_As(strFileName);
		clsBasic.OnModuleRobot_Teach_Data_Save_As(strFileName);
		clsBasic.OnMaintenance_Data_Save_As(strFileName);
		clsBasic.OnInterface_Data_Save_As(strFileName);
		clsBasic.OnRecipe_Data_Save_As(strFileName);

		OnInitGridModelList();
	}
}


void CScreenBasic::OnClickedBtnModelDelete()
{
	// TODO: Add your control notification handler code here
	CDialog_Message	dlgMsg;
	char			chFileName[100];
	CString			strTmp;
	CString			strFileName;
	int				nResponse;
	int				nExistence;			// 파일 존재 유무 플래그

	strTmp = m_strDeviceName[1];
	if(OnModelDeviceCheck(strTmp) == false)  // 입력된 디바이스 이름 정상 유무 검사 함수
	{
		return ;
	}
	
	dlgMsg.m_nMessageType	= 1;
	dlgMsg.m_strMessage		= _T("Are you sure you want to delete the selected information?");

	nResponse = (int)dlgMsg.DoModal();
	
	if(nResponse == IDOK)
	{
		if(strTmp == m_strDeviceName[1])
		{
			m_strDeviceName[0] = m_strDeviceName[1] = m_pGridModel.GetItemText(1, 0);
			if(m_strDeviceName[1] == strTmp)
			{
				m_strDeviceName[1] = "";
				m_strDeviceName[0] = m_strDeviceName[1] = m_pGridModel.GetItemText(2, 0);
			}

		}
		
		strFileName = st_path_info.strBasic + strTmp;
		//wsprintfA(chFileName, "%S", strFileName);
		clsFunc.OnStringToChar(strFileName, chFileName);
// jtkim 20130704
//		nExistence = access(chFileName, 0) ;
		nExistence = _access(chFileName, 0) ;
		if (nExistence != -1)			// 파일 존재
		{
			DeleteFile(strFileName);  // 해당 파일 삭제
			
			OnInitGridModelList();
		}
		else  
		{
			return ;
		}
	}
}

void CScreenBasic::OnClickedBtnReload()
{
	CDialog_Message dlgMsg;
	int nResponse;

	dlgMsg.m_nMessageType	= 1;
	dlgMsg.m_strMessage		= _T("Do you want to change the existing value to the current value?");

	nResponse = (int)dlgMsg.DoModal();

	if (nResponse == IDOK)
	{
		OnDataRecovery();					// 화면 셋팅 정보 백업 받아놓은 변수로 복구 함수

		OnDataInit();
	}
}


void CScreenBasic::OnClickedBtnApply()
{
	CDialog_Message dlgMsg;
	int nResponse;
	
	dlgMsg.m_nMessageType	= 1;
	dlgMsg.m_strMessage		= _T("Do you want to change the existing value to the current value?");

	nResponse = (int)dlgMsg.DoModal();

	if (nResponse == IDOK)
	{
		OnDataHistoryLog();
		OnDataApply();
		OnDataBackup();

		OnInitialUpdate();

		if (st_handler_info.cWndTitle != NULL)
		{
			st_handler_info.cWndTitle->PostMessage(WM_STATUS_CHANGE, MODEL_MODE, 0);			// Device Mode
		}
	}
}

bool CScreenBasic::OnModelDeviceCheck(CString strFileName)
{
	CString strChkFile;  /* 생성할 [폴더]+[파일명] 저장 변수 */
	CString strChkExt;   /* 확장자 저장 변수 */
	int nPos;

	/* ************************************************************************** */
    /* 입력된 디바이스명 설정한다                                                 */
    /* ************************************************************************** */

	strFileName.MakeUpper();
	strFileName.TrimLeft(' ');               
	strFileName.TrimRight(' ');

	if(strFileName.IsEmpty())  
	{
		if(st_handler_info.cWndList != NULL)  // 리스트 바 화면 존재
		{
			//wsprintfA(st_other_info.cAbnormalMsg, "%S",  _T("[DEVICE] A name input error occurrence."));
			clsFunc.OnStringToChar(_T("[DEVICE] A name input error occurrence."), st_other_info.cAbnormalMsg);
			st_handler_info.cWndList->SendMessage(WM_LIST_DATA, 0, ABNORMAL_MSG);  // 동작 실패 출력 요청
		}
		return false;
	}
	/* ************************************************************************** */

	strChkFile = st_path_info.strPathDvc + strFileName;  // 생성할 [폴더]+[파일명] 설정
	nPos = strChkFile.Find(_T("."));  // 확장자 검사
	if (nPos == -1) 
	{
		strChkFile += _T(".TXT");
	}
	else 
	{
		strChkExt = strChkFile.Mid(nPos);  // 확장자 정보 설정
		if (strChkExt != _T(".TXT"))  
		{
			if (st_handler_info.cWndList != NULL)  // 리스트 바 화면 존재
			{
				//wsprintfA(st_other_info.cAbnormalMsg, "%S", _T("[DEVICE] A name extension input error occurrence."));
				//clsFunc.OnStringToChar(_T("[DEVICE] A name extension input error occurrence."), st_other_info.cAbnormalMsg);
				clsMem.OnAbNormalMessagWrite(_T("[DEVICE] A name extension input error occurrence."));
				st_handler_info.cWndList->SendMessage(WM_LIST_DATA, 0, ABNORMAL_MSG);  // 동작 실패 출력 요청
			}
			return false;
		}
	}

	m_strLoadFile = strChkFile;  // 생성할 [폴더]+[파일명]+[확장자] 설정

	return true;
}

bool CScreenBasic::OnModelCreateDeviceCheck(CString strFileName)
{
	CString strChkFile;  // 생성할 [폴더]+[파일명] 저장 변수
	CString strChkExt;   // 확장자 저장 변수
	int nPos;

	/* ************************************************************************** */
    /* 입력된 디바이스명 설정한다                                                 */
    /* ************************************************************************** */
	strFileName.MakeUpper();
	strFileName.TrimLeft(' ');               
	strFileName.TrimRight(' ');

	if(strFileName.IsEmpty())  
	{
		if (st_handler_info.cWndList != NULL)  // 리스트 바 화면 존재
		{
			//wsprintfA(st_other_info.cNormalMsg, "%S", _T("[DEVICE] A name input error occurrence."));
			//clsFunc.OnStringToChar(_T("[DEVICE] A name input error occurrence."), st_other_info.cNormalMsg);
			clsMem.OnAbNormalMessagWrite(_T("[DEVICE] A name input error occurrence."));
			st_handler_info.cWndList->SendMessage(WM_LIST_DATA, 0, ABNORMAL_MSG);  // 동작 실패 출력 요청
		}
		return false;
	}
	/* ************************************************************************** */

	strChkFile = st_path_info.strBasic + strFileName;  // 생성할 [폴더]+[파일명] 설정
	nPos = strChkFile.Find(_T("."));  // 확장자 검사
	if (nPos == -1) 
		strChkFile += _T(".TXT");
	else 
	{
		strChkExt = strChkFile.Mid(nPos);  // 확장자 정보 설정
		if (strChkExt != _T(".TXT"))  
		{
			if (st_handler_info.cWndList != NULL)  // 리스트 바 화면 존재
			{
				//wsprintfA(st_other_info.cNormalMsg, "%S",  _T("[DEVICE] A name extension input error occurrence."));
				//clsFunc.OnStringToChar(_T("[DEVICE] A name extension input error occurrence."), st_other_info.cNormalMsg);
				clsMem.OnAbNormalMessagWrite(_T("[DEVICE] A name extension input error occurrence."));
				st_handler_info.cWndList->SendMessage(WM_LIST_DATA, 0, ABNORMAL_MSG);  // 동작 실패 출력 요청
			}
			return false;
		}
	}

	m_strLoadFile = strChkFile;  // 생성할 [폴더]+[파일명]+[확장자] 설정

	return TRUE;
}

BOOL CScreenBasic::OnEraseBkgnd(CDC* pDC)
{
	CDC  memDC;                     // 메모리 DC
	CBitmap * pOldBitmap = NULL;    // m_BackBitmap으로 새로운 그림을 DC에 그릴 때, 이전 그려졌던 DC(즉, Bitmap)을 저장.
	BITMAP bitmapInfo;              // 그림의 정보(m_BackBitmap)
	st_handler_info.m_BackBitmap.GetBitmap(&bitmapInfo); // Bitmap 크기 구함.

	memDC.CreateCompatibleDC(pDC);  // 메모리 DC 생성
	pOldBitmap = memDC.SelectObject(&st_handler_info.m_BackBitmap);
	pDC->BitBlt(0, 0, bitmapInfo.bmWidth, bitmapInfo.bmHeight, &memDC, 0, 0, SRCCOPY);   // 메모리 DC에 그림을 그림

	memDC.SelectObject(pOldBitmap);
	memDC.DeleteDC();
	return true; // 흰 부러쉬가 아닌 배경을 그려야 하기 때문에 true
}



void CScreenBasic::PostNcDestroy()
{
	// TODO: 여기에 특수화된 코드를 추가 및/또는 기본 클래스를 호출합니다.
/*	if (OnDataComparison() == RET_ERROR)
	{
		OnDataHistoryLog();
		OnDataApply();
	}
	st_handler_info.cWndBasic = NULL;*/
	CFormView::PostNcDestroy();
}


void CScreenBasic::OnDestroy()
{
	CFormView::OnDestroy();

	// TODO: 여기에 메시지 처리기 코드를 추가합니다.
	if (OnDataComparison() == RET_ERROR)
	{
		OnDataHistoryLog();
		OnDataApply();
	}
	st_handler_info.cWndBasic = NULL;
}

HBRUSH CScreenBasic::OnCtlColor(CDC* pDC, CWnd* pWnd, UINT nCtlColor)
{
	HBRUSH hbr = CFormView::OnCtlColor(pDC, pWnd, nCtlColor);

	if (nCtlColor == CTLCOLOR_STATIC)
	{
		switch(pWnd->GetDlgCtrlID())
		{
		case IDC_TEXT_TOOLNAME:
		case IDC_TEXT_PARTNO:
		case IDC_TEXT_COMMENT:
			pDC->SetBkColor(WHITE_C);
			return (HBRUSH)::GetStockObject(WHITE_BRUSH);
			break;

		default:
			pDC->SetBkMode(TRANSPARENT);
			return (HBRUSH)::GetStockObject(NULL_BRUSH);
			break;
		}

	}
	return hbr;
}


void CScreenBasic::OnTimer(UINT_PTR nIDEvent)
{
	CFormView::OnTimer(nIDEvent);
}


void CScreenBasic::OnStnClickedDgtLotsetClip()
{
	// TODO: 여기에 컨트롤 알림 처리기 코드를 추가합니다.
}
