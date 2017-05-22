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

	
}


void CScreenBasic::OnInitLabel()
{

}


void CScreenBasic::OnInitDigit()
{
	
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

	OnInitModelList(st_path_info.strPath_Model);
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

	
	return RET_GOOD;
}


void CScreenBasic::OnDataApply()
{
	st_basic_info.nModeDevice		= m_nModeDevice[1];;	// [Title Bar 상태 표시] < WHIT/WHIT OUT ㅡ MODE 표시	>
	st_basic_info.nModeInterface	= m_nModeInterface[1];
//	st_basic_info.nModeSecsGem		= m_nModeSecsGem[1];
	st_basic_info.nModeWork			= m_nModeWork[1];
	st_basic_info.strDeviceName		= m_strDeviceName[1];	// [Title Bar 상태 표시] < 장비에서 설정한 DEVICE 표시	>
	st_basic_info.strModelName		= m_strModelName[1];
	


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

	

}


void CScreenBasic::OnDataInit()
{
	m_nModeDevice[1]					= st_basic_info.nModeDevice;
	m_strDeviceName[1]					= st_basic_info.strDeviceName;

	m_nModeInterface[1]					= st_basic_info.nModeInterface;
//	m_nModeSecsGem[1]					= st_basic_info.nModeSecsGem;
	m_nModeWork[1]						= st_basic_info.nModeWork;
	m_strModelName[1]					= st_basic_info.strModelName;

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


