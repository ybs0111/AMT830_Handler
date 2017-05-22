// ScreenMain.cpp : 구현 파일입니다.
//

#include "stdafx.h"
#include "Handler.h"
#include "MainFrm.h"
#include "ScreenMain.h"
#include "Variable.h"
#include "Dialog_Message.h"
#include "DialogMessageBox.h"
#include "Dialog_KeyBoard.h"
#include "PublicFunction.h"
#include "Ctlbd_Variable.h"
#include "ComizoaPublic.h"
#include "FastechPublic_IO.h"
#include "Cmmsdk.h"
#include "CmmsdkDef.h"
#include "FtpClient.h"
#include "ClientEcFirst.h"
#include "CtlBd_Library.h"
#include "Dialog_Message.h"
#include "DialogMessageView.h"
#include "AlgMemory.h"

#define TM_FRONT_SMEMA		100
#define TM_REAR_SMEMA		200
#define TM_INTERFACE		300
#define TM_DOOR				400


IMPLEMENT_DYNCREATE(CScreenMain, CFormView)

CScreenMain::CScreenMain()
	: CFormView(CScreenMain::IDD)
{
	m_bmGround.LoadBitmap(IDB_BITMAP_BACK_GROUND);

	m_pImagelist		= NULL;
}

CScreenMain::~CScreenMain()
{
	if (m_pImagelist != NULL)
	{
		delete m_pImagelist;
		m_pImagelist = NULL;
	}
}

void CScreenMain::DoDataExchange(CDataExchange* pDX)
{
	CFormView::DoDataExchange(pDX);

	DDX_Control(pDX, IDC_CUSTOM_MAIN_WORK_INFO_C,				m_pGridWorkInfoC);
	DDX_Control(pDX, IDC_CUSTOM_MAIN_WORK_INFO_N,				m_pGridWorkInfoN);
	DDX_Control(pDX, IDC_CUSTOM_TIME_INFO,						m_pGridTimeInfo);
	DDX_Control(pDX, IDC_GROUP_TIME_INFO,						m_groupTimeInfo);
	DDX_Control(pDX, IDC_GROUP_WORK_INFO,						m_groupWorkInfo);
}

BEGIN_MESSAGE_MAP(CScreenMain, CFormView)
	ON_WM_ERASEBKGND()
	ON_WM_PAINT()
	ON_MESSAGE(WM_WORK_DISPLAY,									OnMainWorkInfoDisplay)  // 출력용 사용자 정의 메시지
	ON_MESSAGE(WM_WORK_COMMAND,									OnMainWorkInfoCommand)  // 출력용 사용자 정의 메시지
	ON_WM_TIMER()
	ON_WM_SHOWWINDOW()
	//ON_NOTIFY(NM_CLICK, IDC_CUSTOM_WORK_INFO,		OnWorkCellClick)
	ON_WM_DESTROY()
	ON_WM_CTLCOLOR()
	ON_BN_CLICKED(IDC_BTN_MAIN_ANIMATE,								&CScreenMain::OnClickedBtnMainAnimate)
	ON_BN_CLICKED(IDC_BTN_MAIN_DATA,								&CScreenMain::OnClickedBtnMainData)
	ON_BN_CLICKED(IDC_BUTTON_TRACK_OUT,								&CScreenMain::OnBnClickedButtonTrackOut)
	ON_NOTIFY(NM_CLICK, IDC_CUSTOM_TIME_INFO,						OnTimeCellClick)
	ON_NOTIFY(NM_CLICK, IDC_CUSTOM_MAIN_WORK_INFO_C,				OnWorkInfoCurrCellClick)
END_MESSAGE_MAP()


// CScreenMain 진단입니다.

#ifdef _DEBUG
void CScreenMain::AssertValid() const
{
	CFormView::AssertValid();
}

#ifndef _WIN32_WCE
void CScreenMain::Dump(CDumpContext& dc) const
{
	CFormView::Dump(dc);
}
#endif
#endif //_DEBUG

void CScreenMain::OnInitialUpdate()
{
	CFormView::OnInitialUpdate();

	OnInitButton();
	OnInitGroupBox();
	OnInitLabel();
	OnInitDigit();
	OnInitGridWorkInfoCurr();
	OnInitGridWorkInfoNext();
	OnInitGridTimeInfo(st_work_info.nPgmInfo);	
	OnMainDisplay();

	st_handler_info.cWndMain = this;
}


void CScreenMain::OnMainDisplay()
{
	OnMainCountDisplay();
	OnMainTimeDisplay();


	if (st_handler_info.cWndTitle != NULL)
	{
		st_handler_info.cWndTitle->PostMessage(WM_STATUS_CHANGE, DEVICE_MODE, st_basic_info.nModeDevice);			// Device Mode
	}
}


BOOL CScreenMain::DestroyWindow()
{
	KillTimer(TM_FRONT_SMEMA);
	KillTimer(TM_REAR_SMEMA);
	KillTimer(TM_INTERFACE);
	KillTimer(TM_DOOR);
	KillTimer(500);

	if (m_pImagelist != NULL)
	{
		delete m_pImagelist;
		m_pImagelist = NULL;
	}

	st_handler_info.cWndMain = NULL;

	return CFormView::DestroyWindow();
}


BOOL CScreenMain::OnEraseBkgnd(CDC* pDC)
{
	CDC  memDC;                     // 메모리 DC
	CBitmap * pOldBitmap = NULL;    // m_BackBitmap으로 새로운 그림을 DC에 그릴 때, 이전 그려졌던 DC(즉, Bitmap)을 저장.
	BITMAP bitmapInfo;              // 그림의 정보(m_BackBitmap)
	st_handler_info.m_BackBitmap.GetBitmap(&bitmapInfo); // Bitmap 크기 구함.

	memDC.CreateCompatibleDC(pDC);  // 메모리 DC 생성
	pOldBitmap = memDC.SelectObject(&m_bmGround);
	pDC->BitBlt(0, 0, bitmapInfo.bmWidth, bitmapInfo.bmHeight, &memDC, 0, 0, SRCCOPY);   // 메모리 DC에 그림을 그림

	memDC.SelectObject(pOldBitmap);
	memDC.DeleteDC();

	return true; // 흰 부러쉬가 아닌 배경을 그려야 하기 때문에 true
}


void CScreenMain::OnInitButton()
{

}

void CScreenMain::OnInitDigit()
{

}


void CScreenMain::OnInitLabel()
{

}


void CScreenMain::OnPaint()
{
	CPaintDC dc(this); // device context for painting
	
	CRect rect;

}

LRESULT CScreenMain::OnMainWorkInfoCommand(WPARAM wParam, LPARAM lParam) 
{

	return 0;
}


LRESULT CScreenMain::OnMainWorkInfoDisplay(WPARAM wParam, LPARAM lParam) 
{
	CString sFile, sPath;

	int nPart = 0;
	int nSite = 0;

	nPart = (int)wParam;
	nSite = (int)lParam;

	switch (wParam)
	{
		case MAIN_TIMEINFO:
			OnMainTimeDisplay();
			break;

		case MAIN_COUNT_DISPLAY:
			OnMainCountDisplay();
			break;
	}

	return 0;
}

void CScreenMain::OnInitGridTimeInfo(int nMode)
{
	int   i, j;
	int	  max_row, max_col;
	int   row;
	CString strTmp;

	if (nMode == 0)
	{
		max_row = 4; // 
		max_col = 2;
	}
	else
	{
		max_row = 6; // 
		max_col = 2;
	}
	
	m_pGridTimeInfo.SetFrameFocusCell(FALSE);
	m_pGridTimeInfo.SetTrackFocusCell(FALSE);
	m_pGridTimeInfo.EnableSelection(FALSE);

	m_pGridTimeInfo.SetGridLineColor(BLACK_C);
	m_pGridTimeInfo.SetGridLines(1);

	m_pGridTimeInfo.SetRowCount(max_row);
	m_pGridTimeInfo.SetColumnCount(max_col);

	m_pGridTimeInfo.SetFixedRowCount(0);
	m_pGridTimeInfo.SetFixedColumnCount(0);
	m_pGridTimeInfo.SetFixedBkColor(RGB(0,0,200));
	m_pGridTimeInfo.SetFixedBkColor(RGB(200,200,255));
	m_pGridTimeInfo.SetTextBkColor(RGB(150,150,200));

	for (i=0; i<max_row; i++) 
	{
		if (nMode == 0)
		{
			m_pGridTimeInfo.SetRowHeight(i, 37);
		}
		else
		{
			m_pGridTimeInfo.SetRowHeight(i, 25);
		}

		for (j=0; j<max_col; j++) 
		{
			m_pGridTimeInfo.SetColumnWidth(j, 120);
				
			m_pGridTimeInfo.SetItemFormat(i, j, DT_CENTER|DT_VCENTER|DT_SINGLELINE);
			m_pGridTimeInfo.SetItemState(i, j, GVIS_READONLY);
			m_pGridTimeInfo.SetItemBkColour(i, j, WHITE_C, CLR_DEFAULT);
		}
	}

	row = 0;
	m_pGridTimeInfo.SetItemBkColour(row, 0, GREEN_L, BLACK_L);
	m_pGridTimeInfo.SetItemFont(row, 0, &clsFunc.OnLogFont(16));
	m_pGridTimeInfo.SetItemText(row, 0, _T("RUN"));

	m_pGridTimeInfo.SetItemBkColour(row, 1, GREEN_L, BLACK_L);
	m_pGridTimeInfo.SetItemFont(row, 1, &clsFunc.OnLogFont(16));
	m_pGridTimeInfo.SetItemText(row, 1, _T("00 : 00 : 00"));

	row = 1;
	m_pGridTimeInfo.SetItemBkColour(row, 0, YELLOW_L, BLACK_L);
	m_pGridTimeInfo.SetItemFont(row, 0, &clsFunc.OnLogFont(16));
	m_pGridTimeInfo.SetItemText(row, 0, _T("STOP"));

	m_pGridTimeInfo.SetItemBkColour(row, 1, YELLOW_L, BLACK_L);
	m_pGridTimeInfo.SetItemFont(row, 1, &clsFunc.OnLogFont(16));
	m_pGridTimeInfo.SetItemText(row, 1, _T("00 : 00 : 00"));

	row = 2;
	m_pGridTimeInfo.SetItemBkColour(row, 0, RED_L, BLACK_L);
	m_pGridTimeInfo.SetItemFont(row, 0, &clsFunc.OnLogFont(16));
	m_pGridTimeInfo.SetItemText(row, 0, _T("ALARM"));

	m_pGridTimeInfo.SetItemBkColour(row, 1, RED_L, BLACK_L);
	m_pGridTimeInfo.SetItemFont(row, 1, &clsFunc.OnLogFont(16));
	m_pGridTimeInfo.SetItemText(row, 1, _T("00 : 00 : 00"));

	row = 3;
	m_pGridTimeInfo.SetItemBkColour(row, 0, BLUE_C, WHITE_C);
	m_pGridTimeInfo.SetItemFont(row, 0, &clsFunc.OnLogFont(16));
	m_pGridTimeInfo.SetItemText(row, 0, _T("MTBI"));

	m_pGridTimeInfo.SetItemBkColour(row, 1, BLUE_C, WHITE_C);
	m_pGridTimeInfo.SetItemFont(row, 1, &clsFunc.OnLogFont(16));
	m_pGridTimeInfo.SetItemText(row, 1, _T("00 : 00 : 00"));

	if (nMode == 1)
	{
		row = 4;
		m_pGridTimeInfo.SetItemBkColour(row, 0, BLACK_C, GREEN_C);
		m_pGridTimeInfo.SetItemFont(row, 0, &clsFunc.OnLogFont(16));
		m_pGridTimeInfo.SetItemText(row, 0, _T("Latest/Daily UPH"));
		//m_pGridTimeInfo.SetItemText(row, 0, _T("Daily UPH"));

		m_pGridTimeInfo.SetItemBkColour(row, 1, BLACK_C, GREEN_C);
		m_pGridTimeInfo.SetItemFont(row, 1, &clsFunc.OnLogFont(16));
		m_pGridTimeInfo.SetItemText(row, 1, _T("0"));

		row = 5;
		m_pGridTimeInfo.SetItemBkColour(row, 0, YELLOW_L, BLACK_L);
		m_pGridTimeInfo.SetItemFont(row, 0, &clsFunc.OnLogFont(16));
		m_pGridTimeInfo.SetItemText(row, 0, _T("Cycle Time"));

		m_pGridTimeInfo.SetItemBkColour(row, 1, WHITE_C, BLACK_L);
		m_pGridTimeInfo.SetItemFont(row, 1, &clsFunc.OnLogFont(16));
		m_pGridTimeInfo.SetItemText(row, 1, _T("0"));
	}
}


void CScreenMain::OnInitGroupBox()
{
	m_groupWorkInfo.SetFont(clsFunc.OnLogFont(14));
	m_groupWorkInfo.SetCatptionTextColor(BLUE_C);
	m_groupWorkInfo.SetBorderColor(ORANGE_C);
	m_groupWorkInfo.SetFontBold(TRUE);
	m_groupWorkInfo.SetBackgroundColor(WINDOW_UP);

	m_groupTimeInfo.SetFont(clsFunc.OnLogFont(14));
	m_groupTimeInfo.SetCatptionTextColor(BLUE_C);
	m_groupTimeInfo.SetBorderColor(ORANGE_C);
	m_groupTimeInfo.SetFontBold(TRUE);
	m_groupTimeInfo.SetBackgroundColor(WINDOW_UP);
}

void CScreenMain::OnInitGridWorkInfoCurr()
{
	int   i, j;
	int	  max_row, max_col;
	int   row;

	CString strTmp;
	CRect rect;

	max_row = 6; // unloader tray y count
	max_col = 2;

	m_pGridWorkInfoC.SetFrameFocusCell(FALSE);
	m_pGridWorkInfoC.SetTrackFocusCell(FALSE);
	m_pGridWorkInfoC.EnableSelection(FALSE);

	m_pGridWorkInfoC.SetGridLineColor(BLACK_C);
	m_pGridWorkInfoC.SetGridLines(1);

	m_pGridWorkInfoC.SetRowCount(max_row);
	m_pGridWorkInfoC.SetColumnCount(max_col);

	m_pGridWorkInfoC.SetFixedRowCount(0);
	m_pGridWorkInfoC.SetFixedColumnCount(0);
	m_pGridWorkInfoC.SetFixedBkColor(RGB(0,0,200));
	m_pGridWorkInfoC.SetFixedBkColor(RGB(200,200,255));
	m_pGridWorkInfoC.SetTextBkColor(RGB(150,150,200));

	for (i=0; i<max_row; i++) 
	{
		m_pGridWorkInfoC.SetRowHeight(i, 23);

		for (j=0; j<max_col; j++) 
		{
			m_pGridWorkInfoC.SetColumnWidth(j, 120);
				
			m_pGridWorkInfoC.SetItemFormat(i, j, DT_CENTER|DT_VCENTER|DT_SINGLELINE);
			m_pGridWorkInfoC.SetItemState(i, j, GVIS_READONLY);
			m_pGridWorkInfoC.SetItemBkColour(i, j, WHITE_C, CLR_DEFAULT);
		}
	}

	row = 0;
	m_pGridWorkInfoC.MergeCells(row, 0, row, 1);
	m_pGridWorkInfoC.SetItemBkColour(row, 0, RGB(219, 229, 241), BLACK_C);
	m_pGridWorkInfoC.SetItemFont(row, 0, &clsFunc.OnLogFont(16));
	m_pGridWorkInfoC.SetItemText(row, 0, _T("Current Lot Info"));

	row = 1;
	m_pGridWorkInfoC.SetItemBkColour(row, 0, BLUE_D, WHITE_C);
	m_pGridWorkInfoC.SetItemFont(row, 0, &clsFunc.OnLogFont(16));
	m_pGridWorkInfoC.SetItemText(row, 0, _T("Lot No"));

	m_pGridWorkInfoC.SetItemBkColour(row, 1, WHITE_C, BLACK_C);
	m_pGridWorkInfoC.SetItemFont(row, 1, &clsFunc.OnLogFont(10));
	m_pGridWorkInfoC.SetItemText(row, 1, _T("-"));

	row = 2;
	m_pGridWorkInfoC.SetItemBkColour(row, 0, BLUE_D, WHITE_C);
	m_pGridWorkInfoC.SetItemFont(row, 0, &clsFunc.OnLogFont(16));
	m_pGridWorkInfoC.SetItemText(row, 0, _T("Part No"));

	m_pGridWorkInfoC.SetItemBkColour(row, 1, WHITE_C, BLACK_C);
	m_pGridWorkInfoC.SetItemFont(row, 1, &clsFunc.OnLogFont(10));
	m_pGridWorkInfoC.SetItemText(row, 1, _T("-"));

	row = 3;
	m_pGridWorkInfoC.SetItemBkColour(row, 0, BLUE_D, WHITE_C);
	m_pGridWorkInfoC.SetItemFont(row, 0, &clsFunc.OnLogFont(16));
	m_pGridWorkInfoC.SetItemText(row, 0, _T("Last Module"));

	m_pGridWorkInfoC.SetItemBkColour(row, 1, WHITE_C, BLACK_C);
	m_pGridWorkInfoC.SetItemFont(row, 1, &clsFunc.OnLogFont(10));
	m_pGridWorkInfoC.SetItemText(row, 1, _T("-"));

	row = 4;
	m_pGridWorkInfoC.SetItemBkColour(row, 0, ORANGE_C, BLACK_C);
	m_pGridWorkInfoC.SetItemFont(row, 0, &clsFunc.OnLogFont(16));
	m_pGridWorkInfoC.SetItemText(row, 0, _T("Hour Socket"));

	m_pGridWorkInfoC.SetItemBkColour(row, 1, WHITE_C, BLACK_C);
	m_pGridWorkInfoC.SetItemFont(row, 1, &clsFunc.OnLogFont(16));
	m_pGridWorkInfoC.SetItemText(row, 1, _T("-"));

	row = 5;
	m_pGridWorkInfoC.SetItemBkColour(row, 0, ORANGE_C, BLACK_C);
	m_pGridWorkInfoC.SetItemFont(row, 0, &clsFunc.OnLogFont(16));
	m_pGridWorkInfoC.SetItemText(row, 0, _T("Daily Socket"));

	m_pGridWorkInfoC.SetItemBkColour(row, 1, WHITE_C, BLACK_C);
	m_pGridWorkInfoC.SetItemFont(row, 1, &clsFunc.OnLogFont(16));
	m_pGridWorkInfoC.SetItemText(row, 1, _T("-"));
}

void CScreenMain::OnInitGridWorkInfoNext()
{
	int   i, j;
	int	  max_row, max_col;
	int   row;

	CString strTmp;
	CRect rect;

	max_row = 3; // unloader tray y count
	max_col = 2;

	m_pGridWorkInfoN.SetFrameFocusCell(FALSE);
	m_pGridWorkInfoN.SetTrackFocusCell(FALSE);
	m_pGridWorkInfoN.EnableSelection(FALSE);

	m_pGridWorkInfoN.SetGridLineColor(BLACK_C);
	m_pGridWorkInfoN.SetGridLines(1);

	m_pGridWorkInfoN.SetRowCount(max_row);
	m_pGridWorkInfoN.SetColumnCount(max_col);

	m_pGridWorkInfoN.SetFixedRowCount(0);
	m_pGridWorkInfoN.SetFixedColumnCount(0);
	m_pGridWorkInfoN.SetFixedBkColor(RGB(0,0,200));
	m_pGridWorkInfoN.SetFixedBkColor(RGB(200,200,255));
	m_pGridWorkInfoN.SetTextBkColor(RGB(150,150,200));

	for (i=0; i<max_row; i++) 
	{
		m_pGridWorkInfoN.SetRowHeight(i, 23);

		for (j=0; j<max_col; j++) 
		{
			m_pGridWorkInfoN.SetColumnWidth(j, 120);
				
			m_pGridWorkInfoN.SetItemFormat(i, j, DT_CENTER|DT_VCENTER|DT_SINGLELINE);
			m_pGridWorkInfoN.SetItemState(i, j, GVIS_READONLY);
			m_pGridWorkInfoN.SetItemBkColour(i, j, WHITE_C, CLR_DEFAULT);
		}
	}

	row = 0;
	m_pGridWorkInfoN.MergeCells(row, 0, row, 1);
	m_pGridWorkInfoN.SetItemBkColour(row, 0, RGB(219, 229, 241), BLACK_C);
	m_pGridWorkInfoN.SetItemFont(row, 0, &clsFunc.OnLogFont(16));
	m_pGridWorkInfoN.SetItemText(row, 0, _T("Next Lot Info"));

	row = 1;
	m_pGridWorkInfoN.SetItemBkColour(row, 0, BLUE_D, WHITE_C);
	m_pGridWorkInfoN.SetItemFont(row, 0, &clsFunc.OnLogFont(16));
	m_pGridWorkInfoN.SetItemText(row, 0, _T("Lot No"));

	m_pGridWorkInfoN.SetItemBkColour(row, 1, WHITE_C, BLACK_C);
	m_pGridWorkInfoN.SetItemFont(row, 1, &clsFunc.OnLogFont(10));
	m_pGridWorkInfoN.SetItemText(row, 1, _T("-"));

	row = 2;
	m_pGridWorkInfoN.SetItemBkColour(row, 0, BLUE_D, WHITE_C);
	m_pGridWorkInfoN.SetItemFont(row, 0, &clsFunc.OnLogFont(16));
	m_pGridWorkInfoN.SetItemText(row, 0, _T("Part No"));

	m_pGridWorkInfoN.SetItemBkColour(row, 1, WHITE_C, BLACK_C);
	m_pGridWorkInfoN.SetItemFont(row, 1, &clsFunc.OnLogFont(10));
	m_pGridWorkInfoN.SetItemText(row, 1, _T("-"));
}


void CScreenMain::OnTimer(UINT_PTR nIDEvent)
{

	CFormView::OnTimer(nIDEvent);
}

void CScreenMain::OnMainTimeDisplay()
{
//	int nState;
	static int nOldTime = 0;
	int nMtbi = 0;
	double dTemp;
	CString strTime;

	strTime.Format(_T("%02d:%02d:%02d"), st_handler_info.tStop.GetHours(), st_handler_info.tStop.GetMinutes(), st_handler_info.tStop.GetSeconds());
	m_pGridTimeInfo.SetItemText(1, 1, strTime);
	
	strTime.Format(_T("%02d:%02d:%02d"), st_handler_info.tRun.GetHours(), st_handler_info.tRun.GetMinutes(), st_handler_info.tRun.GetSeconds());
	m_pGridTimeInfo.SetItemText(0, 1, strTime);

	nMtbi = (int)st_handler_info.tRun.GetTotalHours() * 3600 + (int)st_handler_info.tRun.GetMinutes() * 60 + (int)st_handler_info.tRun.GetSeconds();
	if (st_alarm_info.nAlarmNum > 0)
	{
		nMtbi = nMtbi / st_alarm_info.nAlarmNum;
	}

	strTime.Format(_T("%02d:%02d:%02d"), nMtbi / 3600, (nMtbi % 3600) / 60, nMtbi % 60 );
	m_pGridTimeInfo.SetItemText(3, 1, strTime);
	
	strTime.Format(_T("%02d:%02d:%02d"), st_handler_info.tJam.GetHours(), st_handler_info.tJam.GetMinutes(), st_handler_info.tJam.GetSeconds());
	m_pGridTimeInfo.SetItemText(2, 1, strTime);

	if (st_work_info.nPgmInfo == 1)
	{
		if (st_count_info.nPassCount[1][0] <= 0) return;
		if (((int)st_handler_info.tRun.GetTotalHours() * 60 + (int)st_handler_info.tRun.GetMinutes()) <= 0) return;

		if (nOldTime != (int)(st_handler_info.tRef.GetHour()))
		{
			nOldTime = (int)(st_handler_info.tRef.GetHour() - 1);

			if (nOldTime == -1) nOldTime = 23;

			m_pGridTimeInfo.Invalidate(FALSE);
		}

		//dTemp = (double)((int)st_handler_info.tRun.GetTotalHours() * 60 + (int)st_handler_info.tRun.GetMinutes()) / 60.0f;
		//strTime.Format(_T("%d / %0.2f"), st_count_info.nLatestUph[nOldTime] ,double(st_count_info.nPassCount[1][0] / dTemp));
		//strTime.Format(_T("%0.2f"), double(st_count_info.nPassCount[1][0] / dTemp));
		dTemp = 0.0f;
		if (st_count_info.nDailyUph > 0 && st_count_info.nUphCnt > 0)
		{
			dTemp = (double)st_count_info.nDailyUph / (double)st_count_info.nUphCnt;
		}
		strTime.Format(_T("%d / %0.2f"), st_count_info.nUph , dTemp);
		m_pGridTimeInfo.SetItemText(4, 1, strTime);

	}



	m_pGridTimeInfo.Invalidate(FALSE);
}

void CScreenMain::OnMainCountDisplay()
{
	
}


void CScreenMain::OnShowWindow(BOOL bShow, UINT nStatus)
{
	CFormView::OnShowWindow(bShow, nStatus);

	// TODO: 여기에 메시지 처리기 코드를 추가합니다.
}

void CScreenMain::OnTimeCellClick(NMHDR *pNotifyStruct, LRESULT* pResult)
{
	int nRow, nCol;

	NM_GRIDVIEW* pItem	= (NM_GRIDVIEW*) pNotifyStruct;

	nRow				= pItem->iRow;
	nCol				= pItem->iColumn;

	if (st_work_info.nPgmInfo == 0)
	{
		st_work_info.nPgmInfo = 1;
	}
	else
	{
		st_work_info.nPgmInfo = 0;
	}
	OnInitGridTimeInfo(st_work_info.nPgmInfo);
}

void CScreenMain::OnWorkInfoCurrCellClick(NMHDR *pNotifyStruct, LRESULT* pResult)
{
	if (st_handler_info.nRunStatus != dSTOP) return;

}
/*
void CScreenMain::OnWorkCellClick(NMHDR *pNotifyStruct, LRESULT* pResult)
{
	int nRow, nCol;


	NM_GRIDVIEW* pItem	= (NM_GRIDVIEW*) pNotifyStruct;

	nRow				= pItem->iRow;
	nCol				= pItem->iColumn;

	if(nRow < 2) return ; 
	if (st_handler_info.nRunStatus != dSTOP) return;

	switch (nRow)
	{
		case 5:
			break;

		default:
			break;
	}
//	m_pGridWorkInfo.Refresh();
}*/


void CScreenMain::PostNcDestroy()
{
	// TODO: 여기에 특수화된 코드를 추가 및/또는 기본 클래스를 호출합니다.

	CFormView::PostNcDestroy();
}


void CScreenMain::OnDestroy()
{
	CFormView::OnDestroy();
/*
	// TODO: 여기에 메시지 처리기 코드를 추가합니다.
	if (m_pImagelist != NULL)
	{
		delete m_pImagelist;
		m_pImagelist = NULL;
	}

	if (m_pPcbInfo != NULL)
	{
		delete m_pPcbInfo;
		m_pPcbInfo = NULL;
	}

	if (m_pPcbStatus != NULL)
	{
		delete m_pPcbStatus;
		m_pPcbStatus = NULL;
	}

	if (m_pLotDisplay != NULL)
	{
		m_pLotDisplay->DestroyWindow();

		delete m_pLotDisplay;
		m_pLotDisplay = NULL;
	}

	st_handler_info.cWndMain = NULL;*/
}



void CScreenMain::OnClickedBtnMainAnimate()
{
	
	if (st_handler_info.nRunStatus != dSTOP) return;

	CDialog_Message dlgMsg;
	int nResponse;

	dlgMsg.m_nMessageType	= 1;


}


void CScreenMain::OnClickedBtnMainData()
{
	
	
	// TODO: 여기에 컨트롤 알림 처리기 코드를 추가합니다.
 	if (st_handler_info.nRunStatus != dSTOP) return;
 
 	CDialog_Message dlgMsg;

	
}


void CScreenMain::OnBnClickedButtonTrackOut()
{
	if (st_handler_info.nLotStatus != dSTOP) return;


}

