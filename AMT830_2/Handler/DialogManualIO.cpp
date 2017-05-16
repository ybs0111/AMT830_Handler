// DialogManualIO.cpp : 구현 파일입니다.
//

#include "stdafx.h"
#include "Handler.h"
#include "DialogManualIO.h"
#include "afxdialogex.h"
#include "Variable.h"
#include "PublicFunction.h"
#include "Dialog_KeyBoard.h"
#include "Dialog_KeyPad.h"
#include "Dialog_Message.h"
#include "Ctlbd_Variable.h"
#include "Dialog_Password_Change.h"
#include "ComizoaPublic.h"
#include "FastechPublic_IO.h"

// CDialogManualIO 대화 상자입니다.
#define TM_IO		100
IMPLEMENT_DYNAMIC(CDialogManualIO, CDialog)

CDialogManualIO::CDialogManualIO(CWnd* pParent /*=NULL*/)
	: CDialog(CDialogManualIO::IDD, pParent)
{
	m_bmGround.LoadBitmap(IDB_BITMAP_BACK_GROUND);   

	m_nTsiteNum = 0;
}

CDialogManualIO::~CDialogManualIO()
{
}

void CDialogManualIO::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
// 	DDX_Control(pDX, IDC_CUSTOM_IO_FUNCTION_TSITE,		m_pGridTsite);
// 	DDX_Control(pDX, IDC_CUSTOM_IO_FUNCTION_TSITE_RBT,	m_pGridTRbt);
// 	DDX_Control(pDX, IDC_CUSTOM_IO_FUNCTION_LD_RBT,		m_pGridLdRbt);
// 	DDX_Control(pDX, IDC_CUSTOM_IO_FUNCTION_ULD_RBT,	m_pGridUldRbt);
// 	DDX_Control(pDX, IDC_CUSTOM_IO_FUNCTION_LF_CONTACT,	m_pGridLfContact);
// 	DDX_Control(pDX, IDC_CUSTOM_IO_FUNCTION_RI_CONTACT,	m_pGridRiContact);
// 	DDX_Control(pDX, IDC_CUSTOM_IO_FUNCTION_BUFFER,		m_pGridBuf);
	DDX_Control(pDX, IDC_BTN_EXIT,						m_btnExit);
	//DDX_Control(pDX, IDC_BTN_REFRESH,					m_btnDoor);
	//DDX_Control(pDX, IDC_BTN_LEFT_CLAMP,				m_btnLeftMpClamp);
	//DDX_Control(pDX, IDC_BTN_LEFT_UNCLAMP,				m_btnLeftMpUnClamp);
	//DDX_Control(pDX, IDC_BTN_RIGHT_CLAMP,				m_btnRightMpClamp);
	//DDX_Control(pDX, IDC_BTN_RIGHT_UNCLAMP,				m_btnRightMpUnClamp);
}


BEGIN_MESSAGE_MAP(CDialogManualIO, CDialog)
	ON_WM_ERASEBKGND()
	ON_WM_TIMER()
	ON_NOTIFY(NM_CLICK, IDC_CUSTOM_IO_FUNCTION_TSITE,		&CDialogManualIO::OnTsiteCellClick)
	ON_NOTIFY(NM_CLICK, IDC_CUSTOM_IO_FUNCTION_TSITE_RBT,	&CDialogManualIO::OnTRbtCellClick)
	ON_NOTIFY(NM_CLICK, IDC_CUSTOM_IO_FUNCTION_LD_RBT,		&CDialogManualIO::OnLdRbtCellClick)
	ON_NOTIFY(NM_CLICK, IDC_CUSTOM_IO_FUNCTION_ULD_RBT,		&CDialogManualIO::OnUldRbtCellClick)
	ON_NOTIFY(NM_CLICK, IDC_CUSTOM_IO_FUNCTION_LF_CONTACT,	&CDialogManualIO::OnLeftContactCellClick)
	ON_NOTIFY(NM_CLICK, IDC_CUSTOM_IO_FUNCTION_RI_CONTACT,	&CDialogManualIO::OnRightContactCellClick)
	ON_NOTIFY(NM_CLICK, IDC_CUSTOM_IO_FUNCTION_BUFFER,		&CDialogManualIO::OnBufferCellClick)
	ON_BN_CLICKED(IDC_BTN_EXIT,								&CDialogManualIO::OnBnClickedBtnExit)
	ON_BN_CLICKED(IDC_BTN_REFRESH, &CDialogManualIO::OnBnClickedBtnRefresh)
	ON_BN_CLICKED(IDC_BTN_LEFT_CLAMP, &CDialogManualIO::OnBnClickedBtnLeftClamp)
	ON_BN_CLICKED(IDC_BTN_LEFT_UNCLAMP, &CDialogManualIO::OnBnClickedBtnLeftUnclamp)
	ON_BN_CLICKED(IDC_BTN_RIGHT_CLAMP, &CDialogManualIO::OnBnClickedBtnRightClamp)
	ON_BN_CLICKED(IDC_BTN_RIGHT_UNCLAMP, &CDialogManualIO::OnBnClickedBtnRightUnclamp)
END_MESSAGE_MAP()


// CDialogManualIO 메시지 처리기입니다.

BOOL CDialogManualIO::Create()
{
	return CDialog::Create( CDialogManualIO::IDD );
}

BOOL CDialogManualIO::OnEraseBkgnd(CDC* pDC)
{
	// TODO: 여기에 메시지 처리기 코드를 추가 및/또는 기본값을 호출합니다.
	CDC  memDC;                     // 메모리 DC
	CBitmap * pOldBitmap = NULL;    // m_BackBitmap으로 새로운 그림을 DC에 그릴 때, 이전 그려졌던 DC(즉, Bitmap)을 저장.
	BITMAP bitmapInfo;              // 그림의 정보(m_BackBitmap)
	m_bmGround.GetBitmap(&bitmapInfo); // Bitmap 크기 구함.

	memDC.CreateCompatibleDC(pDC);  // 메모리 DC 생성
	pOldBitmap = memDC.SelectObject(&m_bmGround);
	pDC->BitBlt(0, 0, bitmapInfo.bmWidth, bitmapInfo.bmHeight, &memDC, 0, 0, SRCCOPY);   // 메모리 DC에 그림을 그림

	memDC.SelectObject(pOldBitmap);
	memDC.DeleteDC();

//	return CFormView::OnEraseBkgnd(pDC);
	return true;
}


BOOL CDialogManualIO::DestroyWindow()
{
	// TODO: 여기에 특수화된 코드를 추가 및/또는 기본 클래스를 호출합니다.
	KillTimer(100);
	KillTimer(200);
	KillTimer(300);
	KillTimer(400);
	KillTimer(500);
	KillTimer(600);
	KillTimer(700);
	return CDialog::DestroyWindow();
}


BOOL CDialogManualIO::OnInitDialog()
{
	CDialog::OnInitDialog();

	// TODO:  여기에 추가 초기화 작업을 추가합니다.
	OnInitButton();

// 	OnInitGridTsite();
// 	OnInitGridTsiteRbt();
// 	OnInitGridLdRbt();
// 	OnInitGridUldRbt();
// 	OnInitGridLfContact();
// 	OnInitGridRiContact();
// 	OnInitGridBuffer();

// 	SetTimer(100, 500, NULL);
// 	SetTimer(200, 500, NULL);
// 	SetTimer(300, 500, NULL);
// 	SetTimer(400, 500, NULL);
// 	SetTimer(500, 500, NULL);
// 	SetTimer(600, 500, NULL);
// 	SetTimer(700, 500, NULL);
	return TRUE;  // return TRUE unless you set the focus to a control
	// 예외: OCX 속성 페이지는 FALSE를 반환해야 합니다.
}


void CDialogManualIO::OnTimer(UINT_PTR nIDEvent)
{
	// TODO: 여기에 메시지 처리기 코드를 추가 및/또는 기본값을 호출합니다.
// 	switch (nIDEvent)
// 	{
// 		case 100:
// 			OnDisplayLdRobot();
// 			break;
// 
// 		case 200:
// 			OnDisplayUnLdRobot();
// 			break;
// 
// 		case 300:
// 			OnDisplayTestSiteRobot();
// 			break;
// 
// 		case 400:
// 			OnDisplayLeftContact();
// 			break;
// 
// 		case 500:
// 			OnDisplayRightContact();
// 			break;
// 
// 		case 600:
// 			OnDisplayTestSite();
// 			break;
// 
// 		case 700:
// 			OnDisplayBuffer();
// 			break;
// 	}
	
	CDialog::OnTimer(nIDEvent);
}

void CDialogManualIO::OnInitGridTsite()
{
	int   i, j;
	int	  nMaxRow, nMaxCol;
//	int   nRow, nCol;
	CString strTemp;

	nMaxRow = 8;
	nMaxCol = 13;

	m_pGridTsite.SetFrameFocusCell(FALSE);
	m_pGridTsite.SetTrackFocusCell(FALSE);
	m_pGridTsite.EnableSelection(FALSE);

	m_pGridTsite.SetGridLineColor(BLACK_C);
	m_pGridTsite.SetGridLines(1);

	m_pGridTsite.SetRowCount(nMaxRow);
	m_pGridTsite.SetColumnCount(nMaxCol);

	m_pGridTsite.SetFixedRowCount(0);
	m_pGridTsite.SetFixedColumnCount(0);
	m_pGridTsite.SetFixedBkColor(RGB(0,0,200));
	m_pGridTsite.SetFixedBkColor(RGB(200,200,255));
	m_pGridTsite.SetTextBkColor(RGB(150,150,200));

	for (i=0; i<nMaxRow; i++)
	{
		m_pGridTsite.SetRowHeight(i, 25);
		
		for (j=0; j<nMaxCol; j++)
		{
			if (j == 0)
			{
				m_pGridTsite.SetColumnWidth(j, 160);
			}
			else
			{
				m_pGridTsite.SetColumnWidth(j, 83);
			}

			m_pGridTsite.SetItemFormat(i, j, DT_CENTER|DT_VCENTER|DT_SINGLELINE);
			m_pGridTsite.SetItemState(i, j, GVIS_READONLY);
			m_pGridTsite.SetItemBkColour(i, j, WHITE_C, CLR_DEFAULT);
		}
	}

	m_pGridTsite.MergeCells(0, 0, 1, 0);
	m_pGridTsite.SetItemBkColour(0, 0, ORANGE_C, YELLOW_C);
	m_pGridTsite.SetItemFont(0, 0, &clsFunc.OnLogFont(14));
	m_pGridTsite.SetItemText(0, 0, _T("Left Bottom"));

	m_pGridTsite.MergeCells(2, 0, 3, 0);
	m_pGridTsite.SetItemBkColour(2, 0, BLACK_L, YELLOW_C);
	m_pGridTsite.SetItemFont(2, 0, &clsFunc.OnLogFont(14));
	m_pGridTsite.SetItemText(2, 0, _T("Left Top"));

	m_pGridTsite.MergeCells(4, 0, 5, 0);
	m_pGridTsite.SetItemBkColour(4, 0, BLACK_L, YELLOW_C);
	m_pGridTsite.SetItemFont(4, 0, &clsFunc.OnLogFont(14));
	m_pGridTsite.SetItemText(4, 0, _T("Right Bottom"));

	m_pGridTsite.MergeCells(6, 0, 7, 0);
	m_pGridTsite.SetItemBkColour(6, 0, BLACK_L, YELLOW_C);
	m_pGridTsite.SetItemFont(6, 0, &clsFunc.OnLogFont(14));
	m_pGridTsite.SetItemText(6, 0, _T("Right Top"));

	for (i=0; i<3; i++)
	{
		m_nTsiteInsOut[0][i]	= 0;
		m_nTsiteInsOut[1][i]	= (i * 4) + 1;
		m_pGridTsite.MergeCells(m_nTsiteInsOut[0][i], m_nTsiteInsOut[1][i], m_nTsiteInsOut[0][i], m_nTsiteInsOut[1][i] + 3);
		m_pGridTsite.SetItemBkColour(m_nTsiteInsOut[0][i], m_nTsiteInsOut[1][i], GREEN_D, BLACK_C);
		m_pGridTsite.SetItemFont(m_nTsiteInsOut[0][i], m_nTsiteInsOut[1][i], &clsFunc.OnLogFont(14));
		strTemp.Format(_T("Insert_%02d"), (m_nTsiteNum * 12) + (i + 1));
		m_pGridTsite.SetItemText(m_nTsiteInsOut[0][i], m_nTsiteInsOut[1][i], strTemp);

		m_nTsiteInsFwd[0][i]	= 1;
		m_nTsiteInsFwd[1][i]	= (i * 4) + 1;
		m_pGridTsite.MergeCells(m_nTsiteInsFwd[0][i], m_nTsiteInsFwd[1][i], m_nTsiteInsFwd[0][i], m_nTsiteInsFwd[1][i] + 1);
		m_pGridTsite.SetItemBkColour(m_nTsiteInsFwd[0][i], m_nTsiteInsFwd[1][i], YELLOW_D, BLACK_C);
		m_pGridTsite.SetItemFont(m_nTsiteInsFwd[0][i], m_nTsiteInsFwd[1][i], &clsFunc.OnLogFont(14));
		m_pGridTsite.SetItemText(m_nTsiteInsFwd[0][i], m_nTsiteInsFwd[1][i], _T("Fwd"));

		m_nTsiteInsBwd[0][i]	= 1;
		m_nTsiteInsBwd[1][i]	= (i * 4) + 3;
		m_pGridTsite.MergeCells(m_nTsiteInsBwd[0][i], m_nTsiteInsBwd[1][i], m_nTsiteInsBwd[0][i], m_nTsiteInsBwd[1][i] + 1);
		m_pGridTsite.SetItemBkColour(m_nTsiteInsBwd[0][i], m_nTsiteInsBwd[1][i], YELLOW_D, BLACK_C);
		m_pGridTsite.SetItemFont(m_nTsiteInsBwd[0][i], m_nTsiteInsBwd[1][i], &clsFunc.OnLogFont(14));
		m_pGridTsite.SetItemText(m_nTsiteInsBwd[0][i], m_nTsiteInsBwd[1][i], _T("Bwd"));

		m_nTsiteInsOut[0][i + 3]	= 4;
		m_nTsiteInsOut[1][i + 3]	= (i * 4) + 1;
		m_pGridTsite.MergeCells(m_nTsiteInsOut[0][i + 3], m_nTsiteInsOut[1][i + 3], m_nTsiteInsOut[0][i + 3], m_nTsiteInsOut[1][i + 3] + 3);
		m_pGridTsite.SetItemBkColour(m_nTsiteInsOut[0][i + 3], m_nTsiteInsOut[1][i + 3], GREEN_D, BLACK_C);
		m_pGridTsite.SetItemFont(m_nTsiteInsOut[0][i + 3], m_nTsiteInsOut[1][i + 3], &clsFunc.OnLogFont(14));
		strTemp.Format(_T("Insert_%02d"), (m_nTsiteNum * 12) + (i + 4));
		m_pGridTsite.SetItemText(m_nTsiteInsOut[0][i + 3], m_nTsiteInsOut[1][i + 3], strTemp);

		m_nTsiteInsFwd[0][i + 3]	= 5;
		m_nTsiteInsFwd[1][i + 3]	= (i * 4) + 1;
		m_pGridTsite.MergeCells(m_nTsiteInsFwd[0][i + 3], m_nTsiteInsFwd[1][i + 3], m_nTsiteInsFwd[0][i + 3], m_nTsiteInsFwd[1][i + 3] + 1);
		m_pGridTsite.SetItemBkColour(m_nTsiteInsFwd[0][i + 3], m_nTsiteInsFwd[1][i + 3], YELLOW_D, BLACK_C);
		m_pGridTsite.SetItemFont(m_nTsiteInsFwd[0][i + 3], m_nTsiteInsFwd[1][i + 3], &clsFunc.OnLogFont(14));
		m_pGridTsite.SetItemText(m_nTsiteInsFwd[0][i + 3], m_nTsiteInsFwd[1][i + 3], _T("Fwd"));

		m_nTsiteInsBwd[0][i + 3]	= 5;
		m_nTsiteInsBwd[1][i + 3]	= (i * 4) + 3;
		m_pGridTsite.MergeCells(m_nTsiteInsBwd[0][i + 3], m_nTsiteInsBwd[1][i + 3], m_nTsiteInsBwd[0][i + 3], m_nTsiteInsBwd[1][i + 3] + 1);
		m_pGridTsite.SetItemBkColour(m_nTsiteInsBwd[0][i + 3], m_nTsiteInsBwd[1][i + 3], YELLOW_D, BLACK_C);
		m_pGridTsite.SetItemFont(m_nTsiteInsBwd[0][i + 3], m_nTsiteInsBwd[1][i + 3], &clsFunc.OnLogFont(14));
		m_pGridTsite.SetItemText(m_nTsiteInsBwd[0][i + 3], m_nTsiteInsBwd[1][i + 3], _T("Bwd"));
	}

	for (i=0; i<6; i++)
	{
		m_nTsitePogoOut[0][i]	= 2;
		m_nTsitePogoOut[1][i]	= (i * 2) + 1;
		m_pGridTsite.MergeCells(m_nTsitePogoOut[0][i], m_nTsitePogoOut[1][i], m_nTsitePogoOut[0][i], m_nTsitePogoOut[1][i] + 1);
		m_pGridTsite.SetItemBkColour(m_nTsitePogoOut[0][i], m_nTsitePogoOut[1][i], GREEN_D, BLACK_C);
		m_pGridTsite.SetItemFont(m_nTsitePogoOut[0][i], m_nTsitePogoOut[1][i], &clsFunc.OnLogFont(14));
		strTemp.Format(_T("Pogo_%02d"), (m_nTsiteNum * 12) + (i + 1));
		m_pGridTsite.SetItemText(m_nTsitePogoOut[0][i], m_nTsitePogoOut[1][i], strTemp);

		m_nTsitePogoIn[0][i]	= 3;
		m_nTsitePogoIn[1][i]	= (i * 2) + 1;
		m_pGridTsite.MergeCells(m_nTsitePogoIn[0][i], m_nTsitePogoIn[1][i], m_nTsitePogoIn[0][i], m_nTsitePogoIn[1][i] + 1);
		m_pGridTsite.SetItemBkColour(m_nTsitePogoIn[0][i], m_nTsitePogoIn[1][i], YELLOW_D, BLACK_C);
		m_pGridTsite.SetItemFont(m_nTsitePogoIn[0][i], m_nTsitePogoIn[1][i], &clsFunc.OnLogFont(14));
		m_pGridTsite.SetItemText(m_nTsitePogoIn[0][i], m_nTsitePogoIn[1][i], _T("Dn"));

		m_nTsitePogoOut[0][i + 6]	= 6;
		m_nTsitePogoOut[1][i + 6]	= (i * 2) + 1;
		m_pGridTsite.MergeCells(m_nTsitePogoOut[0][i + 6], m_nTsitePogoOut[1][i + 6], m_nTsitePogoOut[0][i + 6], m_nTsitePogoOut[1][i + 6] + 1);
		m_pGridTsite.SetItemBkColour(m_nTsitePogoOut[0][i + 6], m_nTsitePogoOut[1][i + 6], GREEN_D, BLACK_C);
		m_pGridTsite.SetItemFont(m_nTsitePogoOut[0][i + 6], m_nTsitePogoOut[1][i + 6], &clsFunc.OnLogFont(14));
		strTemp.Format(_T("Pogo_%02d"), (m_nTsiteNum * 12) + (i + 7));
		m_pGridTsite.SetItemText(m_nTsitePogoOut[0][i + 6], m_nTsitePogoOut[1][i + 6], strTemp);

		m_nTsitePogoIn[0][i + 6]	= 7;
		m_nTsitePogoIn[1][i + 6]	= (i * 2) + 1;
		m_pGridTsite.MergeCells(m_nTsitePogoIn[0][i + 6], m_nTsitePogoIn[1][i + 6], m_nTsitePogoIn[0][i + 6], m_nTsitePogoIn[1][i + 6] + 1);
		m_pGridTsite.SetItemBkColour(m_nTsitePogoIn[0][i + 6], m_nTsitePogoIn[1][i + 6], YELLOW_D, BLACK_C);
		m_pGridTsite.SetItemFont(m_nTsitePogoIn[0][i + 6], m_nTsitePogoIn[1][i + 6], &clsFunc.OnLogFont(14));
		m_pGridTsite.SetItemText(m_nTsitePogoIn[0][i + 6], m_nTsitePogoIn[1][i + 6], _T("Dn"));
	}

	OnDisplayTestSite(m_nTsiteNum);
}

void CDialogManualIO::OnInitGridTsiteRbt()
{
	int   i, j;
	int	  nMaxRow, nMaxCol;
//	int   nRow, nCol;
	CString strTmp;

	nMaxRow = 6; // unloader tray y count
	nMaxCol = 9;

	m_pGridTRbt.SetFrameFocusCell(FALSE);
	m_pGridTRbt.SetTrackFocusCell(FALSE);
	m_pGridTRbt.EnableSelection(FALSE);

	m_pGridTRbt.SetGridLineColor(BLACK_C);
	m_pGridTRbt.SetGridLines(1);

	m_pGridTRbt.SetRowCount(nMaxRow);
	m_pGridTRbt.SetColumnCount(nMaxCol);

	m_pGridTRbt.SetFixedRowCount(0);
	m_pGridTRbt.SetFixedColumnCount(0);
	m_pGridTRbt.SetFixedBkColor(RGB(0,0,200));
	m_pGridTRbt.SetFixedBkColor(RGB(200,200,255));
	m_pGridTRbt.SetTextBkColor(RGB(150,150,200));

	for (i=0; i<nMaxRow; i++)
	{
		m_pGridTRbt.SetRowHeight(i, 25);

		for (j=0; j<nMaxCol; j++)
		{
			m_pGridTRbt.SetColumnWidth(j, 60);

			m_pGridTRbt.SetItemFormat(i, j, DT_CENTER|DT_VCENTER|DT_SINGLELINE);
			m_pGridTRbt.SetItemState(i, j, GVIS_READONLY);
			m_pGridTRbt.SetItemBkColour(i, j, WHITE_C, CLR_DEFAULT);
		}
	}

	m_pGridTRbt.MergeCells(0, 0, 0, 8);
	m_pGridTRbt.SetItemBkColour(0, 0, BLUE_D, WHITE_C);
	m_pGridTRbt.SetItemFont(0, 0, &clsFunc.OnLogFont(15));
	m_pGridTRbt.SetItemText(0, 0, _T("Test Site Robot"));

	m_pGridTRbt.MergeCells(1, 1, 1, 2);
	m_pGridTRbt.SetItemBkColour(1, 1, YELLOW_L, BLACK_C);
	m_pGridTRbt.SetItemFont(1, 1, &clsFunc.OnLogFont(15));
	m_pGridTRbt.SetItemText(1, 1, _T("Picker #1"));

	m_pGridTRbt.MergeCells(1, 3, 1, 4);
	m_pGridTRbt.SetItemBkColour(1, 3, YELLOW_L, BLACK_C);
	m_pGridTRbt.SetItemFont(1, 3, &clsFunc.OnLogFont(15));
	m_pGridTRbt.SetItemText(1, 3, _T("Picker #2"));

	m_pGridTRbt.MergeCells(1, 5, 1, 6);
	m_pGridTRbt.SetItemBkColour(1, 5, YELLOW_L, BLACK_C);
	m_pGridTRbt.SetItemFont(1, 5, &clsFunc.OnLogFont(15));
	m_pGridTRbt.SetItemText(1, 5, _T("Picker #3"));

	m_pGridTRbt.MergeCells(1, 7, 1, 8);
	m_pGridTRbt.SetItemBkColour(1, 7, YELLOW_L, BLACK_C);
	m_pGridTRbt.SetItemFont(1, 7, &clsFunc.OnLogFont(15));
	m_pGridTRbt.SetItemText(1, 7, _T("Picker #4"));

	m_pGridTRbt.MergeCells(2, 0, 3, 0);
	m_pGridTRbt.SetItemBkColour(2, 0, BLUE_D, WHITE_C);
	m_pGridTRbt.SetItemFont(2, 0, &clsFunc.OnLogFont(15));
	m_pGridTRbt.SetItemText(2, 0, _T("Picker"));

	m_pGridTRbt.MergeCells(4, 0, 5, 0);
	m_pGridTRbt.SetItemBkColour(4, 0, BLUE_D, WHITE_C);
	m_pGridTRbt.SetItemFont(4, 0, &clsFunc.OnLogFont(15));
	m_pGridTRbt.SetItemText(4, 0, _T("Vaccum"));

	

	for (i=0; i<4; i++)
	{
		// down input
		m_nTsiteDnIn[0][i] = 2;
		m_nTsiteDnIn[1][i] = (i * 2) + 1;
		m_pGridTRbt.SetItemBkColour(m_nTsiteDnIn[0][i], m_nTsiteDnIn[1][i], YELLOW_D, BLACK_C);
		m_pGridTRbt.SetItemText(m_nTsiteDnIn[0][i], m_nTsiteDnIn[1][i], _T("Dn"));

		// down output
		m_nTsiteDnOut[0][i] = 2;
		m_nTsiteDnOut[1][i] = (i * 2) + 2;
		m_pGridTRbt.MergeCells(m_nTsiteDnOut[0][i], m_nTsiteDnOut[1][i], m_nTsiteDnOut[0][i] + 1, m_nTsiteDnOut[1][i]);
		m_pGridTRbt.SetItemBkColour(m_nTsiteDnOut[0][i], m_nTsiteDnOut[1][i], GREEN_D, BLACK_C);
		m_pGridTRbt.SetItemText(m_nTsiteDnOut[0][i], m_nTsiteDnOut[1][i], _T("On/Off"));

		// up input
		m_nTsiteUpIn[0][i] = 3;
		m_nTsiteUpIn[1][i] = (i * 2) + 1;
		m_pGridTRbt.SetItemBkColour(m_nTsiteUpIn[0][i], m_nTsiteUpIn[1][i], YELLOW_D, BLACK_C);
		m_pGridTRbt.SetItemText(m_nTsiteUpIn[0][i], m_nTsiteUpIn[1][i], _T("Up"));
/*
		// up output
		m_nTsiteUpOut[0][i] = 3;
		m_nTsiteUpOut[1][i] = (i * 2) + 2;
		m_pGridTRbt.SetItemBkColour(m_nTsiteUpOut[0][i], m_nTsiteUpOut[1][i], GREEN_D, BLACK_C);
		m_pGridTRbt.SetItemText(m_nTsiteUpOut[0][i], m_nTsiteUpOut[1][i], _T("Up"));
*/
		////////////////////////////////////////////////////////////////////////////////////////
		// vaccum input
		m_nTsiteVacIn[0][i] = 4;
		m_nTsiteVacIn[1][i] = (i * 2) + 1;
		m_pGridTRbt.MergeCells(m_nTsiteVacIn[0][i], m_nTsiteVacIn[1][i], m_nTsiteVacIn[0][i] + 1, m_nTsiteVacIn[1][i]);
		m_pGridTRbt.SetItemBkColour(m_nTsiteVacIn[0][i], m_nTsiteVacIn[1][i], YELLOW_D, BLACK_C);
		m_pGridTRbt.SetItemText(m_nTsiteVacIn[0][i], m_nTsiteVacIn[1][i], _T("Off"));

		// vaccum output
		m_nTsiteVacOut[0][i] = 4;
		m_nTsiteVacOut[1][i] = (i * 2) + 2;
		m_pGridTRbt.SetItemBkColour(m_nTsiteVacOut[0][i], m_nTsiteVacOut[1][i], GREEN_D, BLACK_C);
		m_pGridTRbt.SetItemText(m_nTsiteVacOut[0][i], m_nTsiteVacOut[1][i], _T("Vac"));

		// eject output
		m_nTsiteEjcOut[0][i] = 5;
		m_nTsiteEjcOut[1][i] = (i * 2) + 2;
		m_pGridTRbt.SetItemBkColour(m_nTsiteEjcOut[0][i], m_nTsiteEjcOut[1][i], GREEN_D, BLACK_C);
		m_pGridTRbt.SetItemText(m_nTsiteEjcOut[0][i], m_nTsiteEjcOut[1][i], _T("Ejc"));
	}

	m_pGridTRbt.Invalidate(FALSE);
}

void CDialogManualIO::OnInitGridLdRbt()
{
	int   i, j;
	int	  nMaxRow, nMaxCol;
//	int   nRow, nCol;
	CString strTmp;

	nMaxRow = 6; // unloader tray y count
	nMaxCol = 5;

	m_pGridLdRbt.SetFrameFocusCell(FALSE);
	m_pGridLdRbt.SetTrackFocusCell(FALSE);
	m_pGridLdRbt.EnableSelection(FALSE);

	m_pGridLdRbt.SetGridLineColor(BLACK_C);
	m_pGridLdRbt.SetGridLines(1);

	m_pGridLdRbt.SetRowCount(nMaxRow);
	m_pGridLdRbt.SetColumnCount(nMaxCol);

	m_pGridLdRbt.SetFixedRowCount(0);
	m_pGridLdRbt.SetFixedColumnCount(0);
	m_pGridLdRbt.SetFixedBkColor(RGB(0,0,200));
	m_pGridLdRbt.SetFixedBkColor(RGB(200,200,255));
	m_pGridLdRbt.SetTextBkColor(RGB(150,150,200));



	for (i=0; i<nMaxRow; i++)
	{
		m_pGridLdRbt.SetRowHeight(i, 25);

		for (j=0; j<nMaxCol; j++)
		{
			m_pGridLdRbt.SetColumnWidth(j, 60);

			m_pGridLdRbt.SetItemFormat(i, j, DT_CENTER|DT_VCENTER|DT_SINGLELINE);
			m_pGridLdRbt.SetItemState(i, j, GVIS_READONLY);
			m_pGridLdRbt.SetItemBkColour(i, j, WHITE_C, CLR_DEFAULT);
		}
	}

	m_pGridLdRbt.MergeCells(0, 0, 0, 4);
	m_pGridLdRbt.SetItemBkColour(0, 0, BLUE_D, WHITE_C);
	m_pGridLdRbt.SetItemFont(0, 0, &clsFunc.OnLogFont(15));
	m_pGridLdRbt.SetItemText(0, 0, _T("Loader Robot"));

	m_pGridLdRbt.MergeCells(1, 1, 1, 2);
	m_pGridLdRbt.SetItemBkColour(1, 1, YELLOW_L, BLACK_C);
	m_pGridLdRbt.SetItemFont(1, 1, &clsFunc.OnLogFont(15));
	m_pGridLdRbt.SetItemText(1, 1, _T("Picker #1"));

	m_pGridLdRbt.MergeCells(1, 3, 1, 4);
	m_pGridLdRbt.SetItemBkColour(1, 3, YELLOW_L, BLACK_C);
	m_pGridLdRbt.SetItemFont(1, 3, &clsFunc.OnLogFont(15));
	m_pGridLdRbt.SetItemText(1, 3, _T("Picker #2"));

	m_pGridLdRbt.MergeCells(2, 0, 3, 0);
	m_pGridLdRbt.SetItemBkColour(2, 0, BLUE_D, WHITE_C);
	m_pGridLdRbt.SetItemFont(2, 0, &clsFunc.OnLogFont(15));
	m_pGridLdRbt.SetItemText(2, 0, _T("Picker"));

	m_pGridLdRbt.MergeCells(4, 0, 5, 0);
	m_pGridLdRbt.SetItemBkColour(4, 0, BLUE_D, WHITE_C);
	m_pGridLdRbt.SetItemFont(4, 0, &clsFunc.OnLogFont(15));
	m_pGridLdRbt.SetItemText(4, 0, _T("Vaccum"));

	for (i=0; i<2; i++)
	{
		// down input
		m_nLdDnIn[0][i] = 2;
		m_nLdDnIn[1][i] = (i * 2) + 1;
		m_pGridLdRbt.SetItemBkColour(m_nLdDnIn[0][i], m_nLdDnIn[1][i], YELLOW_D, BLACK_C);
		m_pGridLdRbt.SetItemText(m_nLdDnIn[0][i], m_nLdDnIn[1][i], _T("Dn"));

		// down output
		m_nLdDnOut[0][i] = 2;
		m_nLdDnOut[1][i] = (i * 2) + 2;
		m_pGridLdRbt.MergeCells(m_nLdDnOut[0][i], m_nLdDnOut[1][i], m_nLdDnOut[0][i] + 1, m_nLdDnOut[1][i]);
		m_pGridLdRbt.SetItemBkColour(m_nLdDnOut[0][i], m_nLdDnOut[1][i], GREEN_D, BLACK_C);
		m_pGridLdRbt.SetItemText(m_nLdDnOut[0][i], m_nLdDnOut[1][i], _T("Dn/Up"));

		// up input
		m_nLdUpIn[0][i] = 3;
		m_nLdUpIn[1][i] = (i * 2) + 1;
		m_pGridLdRbt.SetItemBkColour(m_nLdUpIn[0][i], m_nLdUpIn[1][i], YELLOW_D, BLACK_C);
		m_pGridLdRbt.SetItemText(m_nLdUpIn[0][i], m_nLdUpIn[1][i], _T("Up"));
/*
		// up output
		m_nLdUpOut[0][i] = 3;
		m_nLdUpOut[1][i] = (i * 2) + 2;
		m_pGridLdRbt.SetItemBkColour(m_nLdUpOut[0][i], m_nLdUpOut[1][i], GREEN_D, BLACK_C);
		m_pGridLdRbt.SetItemText(m_nLdUpOut[0][i], m_nLdUpOut[1][i], _T("Up"));
*/
		////////////////////////////////////////////////////////////////////////////////////////
		// vaccum input
		m_nLdVacIn[0][i] = 4;
		m_nLdVacIn[1][i] = (i * 2) + 1;
		m_pGridLdRbt.MergeCells(m_nLdVacIn[0][i], m_nLdVacIn[1][i], m_nLdVacIn[0][i] + 1, m_nLdVacIn[1][i]);
		m_pGridLdRbt.SetItemBkColour(m_nLdVacIn[0][i], m_nLdVacIn[1][i], YELLOW_D, BLACK_C);
		m_pGridLdRbt.SetItemText(m_nLdVacIn[0][i], m_nLdVacIn[1][i], _T("Off"));

		// vaccum output
		m_nLdVacOut[0][i] = 4;
		m_nLdVacOut[1][i] = (i * 2) + 2;
		m_pGridLdRbt.SetItemBkColour(m_nLdVacOut[0][i], m_nLdVacOut[1][i], GREEN_D, BLACK_C);
		m_pGridLdRbt.SetItemText(m_nLdVacOut[0][i], m_nLdVacOut[1][i], _T("Vac"));

		// eject output
		m_nLdEjcOut[0][i] = 5;
		m_nLdEjcOut[1][i] = (i * 2) + 2;
		m_pGridLdRbt.SetItemBkColour(m_nLdEjcOut[0][i], m_nLdEjcOut[1][i], GREEN_D, BLACK_C);
		m_pGridLdRbt.SetItemText(m_nLdEjcOut[0][i], m_nLdEjcOut[1][i], _T("Ejc"));
	}

	m_pGridLdRbt.Invalidate(FALSE);
}

void CDialogManualIO::OnInitGridUldRbt()
{
	int   i, j;
	int	  nMaxRow, nMaxCol;
//	int   nRow, nCol;
	CString strTmp;

	nMaxRow = 6; // unloader tray y count
	nMaxCol = 5;

	m_pGridUldRbt.SetFrameFocusCell(FALSE);
	m_pGridUldRbt.SetTrackFocusCell(FALSE);
	m_pGridUldRbt.EnableSelection(FALSE);

	m_pGridUldRbt.SetGridLineColor(BLACK_C);
	m_pGridUldRbt.SetGridLines(1);

	m_pGridUldRbt.SetRowCount(nMaxRow);
	m_pGridUldRbt.SetColumnCount(nMaxCol);

	m_pGridUldRbt.SetFixedRowCount(0);
	m_pGridUldRbt.SetFixedColumnCount(0);
	m_pGridUldRbt.SetFixedBkColor(RGB(0,0,200));
	m_pGridUldRbt.SetFixedBkColor(RGB(200,200,255));
	m_pGridUldRbt.SetTextBkColor(RGB(150,150,200));

	for (i=0; i<nMaxRow; i++)
	{
		m_pGridUldRbt.SetRowHeight(i, 25);

		for (j=0; j<nMaxCol; j++)
		{
			m_pGridUldRbt.SetColumnWidth(j, 60);

			m_pGridUldRbt.SetItemFormat(i, j, DT_CENTER|DT_VCENTER|DT_SINGLELINE);
			m_pGridUldRbt.SetItemState(i, j, GVIS_READONLY);
			m_pGridUldRbt.SetItemBkColour(i, j, WHITE_C, CLR_DEFAULT);
		}
	}

	m_pGridUldRbt.MergeCells(0, 0, 0, 4);
	m_pGridUldRbt.SetItemBkColour(0, 0, BLUE_D, WHITE_C);
	m_pGridUldRbt.SetItemFont(0, 0, &clsFunc.OnLogFont(15));
	m_pGridUldRbt.SetItemText(0, 0, _T("UnLoader Robot"));

	m_pGridUldRbt.MergeCells(1, 1, 1, 2);
	m_pGridUldRbt.SetItemBkColour(1, 1, YELLOW_L, BLACK_C);
	m_pGridUldRbt.SetItemFont(1, 1, &clsFunc.OnLogFont(15));
	m_pGridUldRbt.SetItemText(1, 1, _T("Picker #1"));

	m_pGridUldRbt.MergeCells(1, 3, 1, 4);
	m_pGridUldRbt.SetItemBkColour(1, 3, YELLOW_L, BLACK_C);
	m_pGridUldRbt.SetItemFont(1, 3, &clsFunc.OnLogFont(15));
	m_pGridUldRbt.SetItemText(1, 3, _T("Picker #2"));

	m_pGridUldRbt.MergeCells(2, 0, 3, 0);
	m_pGridUldRbt.SetItemBkColour(2, 0, BLUE_D, WHITE_C);
	m_pGridUldRbt.SetItemFont(2, 0, &clsFunc.OnLogFont(15));
	m_pGridUldRbt.SetItemText(2, 0, _T("Picker"));

	m_pGridUldRbt.MergeCells(4, 0, 5, 0);
	m_pGridUldRbt.SetItemBkColour(4, 0, BLUE_D, WHITE_C);
	m_pGridUldRbt.SetItemFont(4, 0, &clsFunc.OnLogFont(15));
	m_pGridUldRbt.SetItemText(4, 0, _T("Vaccum"));


	for (i=0; i<2; i++)
	{
		// down input
		m_nUnLdDnIn[0][i] = 2;
		m_nUnLdDnIn[1][i] = (i * 2) + 1;
		m_pGridUldRbt.SetItemBkColour(m_nUnLdDnIn[0][i], m_nUnLdDnIn[1][i], YELLOW_D, BLACK_C);
		m_pGridUldRbt.SetItemText(m_nUnLdDnIn[0][i], m_nUnLdDnIn[1][i], _T("Dn"));

		// down output
		m_nUnLdDnOut[0][i] = 2;
		m_nUnLdDnOut[1][i] = (i * 2) + 2;
		m_pGridUldRbt.MergeCells(m_nUnLdDnOut[0][i], m_nUnLdDnOut[1][i], m_nUnLdDnOut[0][i] + 1, m_nUnLdDnOut[1][i]);
		m_pGridUldRbt.SetItemBkColour(m_nUnLdDnOut[0][i], m_nUnLdDnOut[1][i], GREEN_D, BLACK_C);
		m_pGridUldRbt.SetItemText(m_nUnLdDnOut[0][i], m_nUnLdDnOut[1][i], _T("Dn"));

		// up input
		m_nUnLdUpIn[0][i] = 3;
		m_nUnLdUpIn[1][i] = (i * 2) + 1;
		m_pGridUldRbt.SetItemBkColour(m_nUnLdUpIn[0][i], m_nUnLdUpIn[1][i], YELLOW_D, BLACK_C);
		m_pGridUldRbt.SetItemText(m_nUnLdUpIn[0][i], m_nUnLdUpIn[1][i], _T("Up"));
/*
		// up output
		m_nLdUpOut[0][i] = 3;
		m_nLdUpOut[1][i] = (i * 2) + 2;
		m_pGridUldRbt.SetItemBkColour(m_nLdUpOut[0][i], m_nLdUpOut[1][i], GREEN_D, BLACK_C);
		m_pGridUldRbt.SetItemText(m_nLdUpOut[0][i], m_nLdUpOut[1][i], _T("Up"));
*/
		////////////////////////////////////////////////////////////////////////////////////////
		// vaccum input
		m_nUnLdVacIn[0][i] = 4;
		m_nUnLdVacIn[1][i] = (i * 2) + 1;
		m_pGridUldRbt.MergeCells(m_nUnLdVacIn[0][i], m_nUnLdVacIn[1][i], m_nUnLdVacIn[0][i] + 1, m_nUnLdVacIn[1][i]);
		m_pGridUldRbt.SetItemBkColour(m_nUnLdVacIn[0][i], m_nUnLdVacIn[1][i], YELLOW_D, BLACK_C);
		m_pGridUldRbt.SetItemText(m_nUnLdVacIn[0][i], m_nUnLdVacIn[1][i], _T("Off"));

		// vaccum output
		m_nUnLdVacOut[0][i] = 4;
		m_nUnLdVacOut[1][i] = (i * 2) + 2;
		m_pGridUldRbt.SetItemBkColour(m_nUnLdVacOut[0][i], m_nUnLdVacOut[1][i], GREEN_D, BLACK_C);
		m_pGridUldRbt.SetItemText(m_nUnLdVacOut[0][i], m_nUnLdVacOut[1][i], _T("Vac"));

		// eject output
		m_nUnLdEjcOut[0][i] = 5;
		m_nUnLdEjcOut[1][i] = (i * 2) + 2;
		m_pGridUldRbt.SetItemBkColour(m_nUnLdEjcOut[0][i], m_nUnLdEjcOut[1][i], GREEN_D, BLACK_C);
		m_pGridUldRbt.SetItemText(m_nUnLdEjcOut[0][i], m_nUnLdEjcOut[1][i], _T("Ejc"));
	}

	m_pGridUldRbt.Invalidate(FALSE);
}

void CDialogManualIO::OnInitGridLfContact()
{
	int   i, j;
	int	  nMaxRow, nMaxCol;
//	int   nRow, nCol;
	CString strTmp;

	nMaxRow = 14; // unloader tray y count
	nMaxCol = 5;

	m_pGridLfContact.SetFrameFocusCell(FALSE);
	m_pGridLfContact.SetTrackFocusCell(FALSE);
	m_pGridLfContact.EnableSelection(FALSE);

	m_pGridLfContact.SetGridLineColor(BLACK_C);
	m_pGridLfContact.SetGridLines(1);

	m_pGridLfContact.SetRowCount(nMaxRow);
	m_pGridLfContact.SetColumnCount(nMaxCol);

	m_pGridLfContact.SetFixedRowCount(0);
	m_pGridLfContact.SetFixedColumnCount(0);
	m_pGridLfContact.SetFixedBkColor(RGB(0,0,200));
	m_pGridLfContact.SetFixedBkColor(RGB(200,200,255));
	m_pGridLfContact.SetTextBkColor(RGB(150,150,200));

	for (i=0; i<nMaxRow; i++)
	{
		m_pGridLfContact.SetRowHeight(i, 25);

		for (j=0; j<nMaxCol; j++)
		{
			if (j == 0)
			{
				m_pGridLfContact.SetColumnWidth(j, 100);
			}
			else 
			{
				m_pGridLfContact.SetColumnWidth(j, 70);
			}

			m_pGridLfContact.SetItemFormat(i, j, DT_CENTER|DT_VCENTER|DT_SINGLELINE);
			m_pGridLfContact.SetItemState(i, j, GVIS_READONLY);
			m_pGridLfContact.SetItemBkColour(i, j, WHITE_C, CLR_DEFAULT);
		}
	}

	

	m_pGridLfContact.MergeCells(0, 0, 0, 4);
	m_pGridLfContact.SetItemBkColour(0, 0, BLUE_D, WHITE_C);
	m_pGridLfContact.SetItemFont(0, 0, &clsFunc.OnLogFont(15));
	m_pGridLfContact.SetItemText(0, 0, _T("Left Hifix"));

	// cok clamp
	m_pGridLfContact.MergeCells(1, 0, 3, 0);
	m_pGridLfContact.SetItemBkColour(1, 0, YELLOW_L, BLACK_C);
	m_pGridLfContact.SetItemFont(1, 0, &clsFunc.OnLogFont(15));
	m_pGridLfContact.SetItemText(1, 0, _T("Left COK Clamp"));
	// bottom
	m_nLfBCokClampOut[0]	= 1;
	m_nLfBCokClampOut[1]	= 1;
	m_pGridLfContact.MergeCells(m_nLfBCokClampOut[0], m_nLfBCokClampOut[1], m_nLfBCokClampOut[0], m_nLfBCokClampOut[1] + 1);
	m_pGridLfContact.SetItemBkColour(m_nLfBCokClampOut[0], m_nLfBCokClampOut[1], GREEN_D, BLACK_C);
	m_pGridLfContact.SetItemText(m_nLfBCokClampOut[0], m_nLfBCokClampOut[1], _T("Fwd/Bwd"));

	m_nLfBCokClampFwd[0][0]	= 2;
	m_nLfBCokClampFwd[1][0]	= 1;
	m_pGridLfContact.SetItemBkColour(m_nLfBCokClampFwd[0][0], m_nLfBCokClampFwd[1][0], YELLOW_D, BLACK_C);
	m_pGridLfContact.SetItemText(m_nLfBCokClampFwd[0][0], m_nLfBCokClampFwd[1][0], _T("Lf Fwd"));

	m_nLfBCokClampFwd[0][1]	= 3;
	m_nLfBCokClampFwd[1][1]	= 1;
	m_pGridLfContact.SetItemBkColour(m_nLfBCokClampFwd[0][1], m_nLfBCokClampFwd[1][1], YELLOW_D, BLACK_C);
	m_pGridLfContact.SetItemText(m_nLfBCokClampFwd[0][1], m_nLfBCokClampFwd[1][1], _T("Ri Fwd"));

	m_nLfBCokClampBwd[0][0]	= 2;
	m_nLfBCokClampBwd[1][0]	= 2;
	m_pGridLfContact.SetItemBkColour(m_nLfBCokClampBwd[0][0], m_nLfBCokClampBwd[1][0], YELLOW_D, BLACK_C);
	m_pGridLfContact.SetItemText(m_nLfBCokClampBwd[0][0], m_nLfBCokClampBwd[1][0], _T("Lf Bwd"));

	m_nLfBCokClampBwd[0][1]	= 3;
	m_nLfBCokClampBwd[1][1]	= 2;
	m_pGridLfContact.SetItemBkColour(m_nLfBCokClampBwd[0][1], m_nLfBCokClampBwd[1][1], YELLOW_D, BLACK_C);
	m_pGridLfContact.SetItemText(m_nLfBCokClampBwd[0][1], m_nLfBCokClampBwd[1][1], _T("Ri Bwd"));
	// top
	m_nLfTCokClampOut[0]	= 1;
	m_nLfTCokClampOut[1]	= 3;
	m_pGridLfContact.MergeCells(m_nLfTCokClampOut[0], m_nLfTCokClampOut[1], m_nLfTCokClampOut[0], m_nLfTCokClampOut[1] + 1);
	m_pGridLfContact.SetItemBkColour(m_nLfTCokClampOut[0], m_nLfTCokClampOut[1], GREEN_D, BLACK_C);
	m_pGridLfContact.SetItemText(m_nLfTCokClampOut[0], m_nLfTCokClampOut[1], _T("Fwd/Bwd"));

	m_nLfTCokClampFwd[0][0]	= 2;
	m_nLfTCokClampFwd[1][0]	= 3;
	m_pGridLfContact.SetItemBkColour(m_nLfTCokClampFwd[0][0], m_nLfTCokClampFwd[1][0], YELLOW_D, BLACK_C);
	m_pGridLfContact.SetItemText(m_nLfTCokClampFwd[0][0], m_nLfTCokClampFwd[1][0], _T("Lf Fwd"));

	m_nLfTCokClampFwd[0][1]	= 3;
	m_nLfTCokClampFwd[1][1]	= 3;
	m_pGridLfContact.SetItemBkColour(m_nLfTCokClampFwd[0][1], m_nLfTCokClampFwd[1][1], YELLOW_D, BLACK_C);
	m_pGridLfContact.SetItemText(m_nLfTCokClampFwd[0][1], m_nLfTCokClampFwd[1][1], _T("Ri Fwd"));

	m_nLfTCokClampBwd[0][0]	= 2;
	m_nLfTCokClampBwd[1][0]	= 4;
	m_pGridLfContact.SetItemBkColour(m_nLfTCokClampBwd[0][0], m_nLfTCokClampBwd[1][0], YELLOW_D, BLACK_C);
	m_pGridLfContact.SetItemText(m_nLfTCokClampBwd[0][0], m_nLfTCokClampBwd[1][0], _T("Lf Bwd"));

	m_nLfTCokClampBwd[0][1]	= 3;
	m_nLfTCokClampBwd[1][1]	= 4;
	m_pGridLfContact.SetItemBkColour(m_nLfTCokClampBwd[0][1], m_nLfTCokClampBwd[1][1], YELLOW_D, BLACK_C);
	m_pGridLfContact.SetItemText(m_nLfTCokClampBwd[0][1], m_nLfTCokClampBwd[1][1], _T("Ri Bwd"));

	// left contact
	m_pGridLfContact.MergeCells(4, 0, 6, 0);
	m_pGridLfContact.SetItemBkColour(4, 0, YELLOW_L, BLACK_C);
	m_pGridLfContact.SetItemFont(4, 0, &clsFunc.OnLogFont(15));
	m_pGridLfContact.SetItemText(4, 0, _T("Left Contact"));

	m_nLfBContactOut[0][0]	= 4;
	m_nLfBContactOut[1][0]	= 1;
	m_pGridLfContact.SetItemBkColour(m_nLfBContactOut[0][0], m_nLfBContactOut[1][0], GREEN_D, BLACK_C);
	m_pGridLfContact.SetItemText(m_nLfBContactOut[0][0], m_nLfBContactOut[1][0], _T("Fwd"));

	m_nLfBContactOut[0][1]	= 4;
	m_nLfBContactOut[1][1]	= 2;
	m_pGridLfContact.SetItemBkColour(m_nLfBContactOut[0][1], m_nLfBContactOut[1][1], GREEN_D, BLACK_C);
	m_pGridLfContact.SetItemText(m_nLfBContactOut[0][1], m_nLfBContactOut[1][1], _T("Bwd"));

	m_nLfBContactFwd[0][0]	= 5;
	m_nLfBContactFwd[1][0]	= 1;
	m_pGridLfContact.SetItemBkColour(m_nLfBContactFwd[0][0], m_nLfBContactFwd[1][0], YELLOW_D, BLACK_C);
	m_pGridLfContact.SetItemText(m_nLfBContactFwd[0][0], m_nLfBContactFwd[1][0], _T("Lf Fwd"));

	m_nLfBContactFwd[0][1]	= 6;
	m_nLfBContactFwd[1][1]	= 1;
	m_pGridLfContact.SetItemBkColour(m_nLfBContactFwd[0][1], m_nLfBContactFwd[1][1], YELLOW_D, BLACK_C);
	m_pGridLfContact.SetItemText(m_nLfBContactFwd[0][1], m_nLfBContactFwd[1][1], _T("Ri Fwd"));

	m_nLfBContactBwd[0][0]	= 5;
	m_nLfBContactBwd[1][0]	= 2;
	m_pGridLfContact.SetItemBkColour(m_nLfBContactBwd[0][0], m_nLfBContactBwd[1][0], YELLOW_D, BLACK_C);
	m_pGridLfContact.SetItemText(m_nLfBContactBwd[0][0], m_nLfBContactBwd[1][0], _T("Lf Bwd"));

	m_nLfBContactBwd[0][1]	= 6;
	m_nLfBContactBwd[1][1]	= 2;
	m_pGridLfContact.SetItemBkColour(m_nLfBContactBwd[0][1], m_nLfBContactBwd[1][1], YELLOW_D, BLACK_C);
	m_pGridLfContact.SetItemText(m_nLfBContactBwd[0][1], m_nLfBContactBwd[1][1], _T("Ri Bwd"));

	////top
	m_nLfTContactOut[0][0]	= 4;
	m_nLfTContactOut[1][0]	= 3;
	m_pGridLfContact.SetItemBkColour(m_nLfTContactOut[0][0], m_nLfTContactOut[1][0], GREEN_D, BLACK_C);
	m_pGridLfContact.SetItemText(m_nLfTContactOut[0][0], m_nLfTContactOut[1][0], _T("Fwd"));

	m_nLfTContactOut[0][1]	= 4;
	m_nLfTContactOut[1][1]	= 4;
	m_pGridLfContact.SetItemBkColour(m_nLfTContactOut[0][1], m_nLfTContactOut[1][1], GREEN_D, BLACK_C);
	m_pGridLfContact.SetItemText(m_nLfTContactOut[0][1], m_nLfTContactOut[1][1], _T("Bwd"));

	m_nLfTContactFwd[0][0]	= 5;
	m_nLfTContactFwd[1][0]	= 3;
	m_pGridLfContact.SetItemBkColour(m_nLfTContactFwd[0][0], m_nLfTContactFwd[1][0], YELLOW_D, BLACK_C);
	m_pGridLfContact.SetItemText(m_nLfTContactFwd[0][0], m_nLfTContactFwd[1][0], _T("Lf Fwd"));

	m_nLfTContactFwd[0][1]	= 6;
	m_nLfTContactFwd[1][1]	= 3;
	m_pGridLfContact.SetItemBkColour(m_nLfTContactFwd[0][1], m_nLfTContactFwd[1][1], YELLOW_D, BLACK_C);
	m_pGridLfContact.SetItemText(m_nLfTContactFwd[0][1], m_nLfTContactFwd[1][1], _T("Ri Fwd"));

	m_nLfTContactBwd[0][0]	= 5;
	m_nLfTContactBwd[1][0]	= 4;
	m_pGridLfContact.SetItemBkColour(m_nLfTContactBwd[0][0], m_nLfTContactBwd[1][0], YELLOW_D, BLACK_C);
	m_pGridLfContact.SetItemText(m_nLfTContactBwd[0][0], m_nLfTContactBwd[1][0], _T("Lf Bwd"));

	m_nLfTContactBwd[0][1]	= 6;
	m_nLfTContactBwd[1][1]	= 4;
	m_pGridLfContact.SetItemBkColour(m_nLfTContactBwd[0][1], m_nLfTContactBwd[1][1], YELLOW_D, BLACK_C);
	m_pGridLfContact.SetItemText(m_nLfTContactBwd[0][1], m_nLfTContactBwd[1][1], _T("Ri Bwd"));

	// left hifix
	m_pGridLfContact.MergeCells(7, 0, 10, 0);
	m_pGridLfContact.SetItemBkColour(7, 0, YELLOW_L, BLACK_C);
	m_pGridLfContact.SetItemFont(7, 0, &clsFunc.OnLogFont(15));
	m_pGridLfContact.SetItemText(7, 0, _T("Left Hifix"));

	m_nLfHifixOut[0][0]	= 7;
	m_nLfHifixOut[1][0]	= 1;
	m_pGridLfContact.SetItemBkColour(m_nLfHifixOut[0][0], m_nLfHifixOut[1][0], GREEN_D, BLACK_C);
	m_pGridLfContact.SetItemText(m_nLfHifixOut[0][0], m_nLfHifixOut[1][0], _T("Fwd"));

	m_nLfHifixOut[0][1]	= 7;
	m_nLfHifixOut[1][1]	= 2;
	m_pGridLfContact.SetItemBkColour(m_nLfHifixOut[0][1], m_nLfHifixOut[1][1], GREEN_D, BLACK_C);
	m_pGridLfContact.SetItemText(m_nLfHifixOut[0][1], m_nLfHifixOut[1][1], _T("Bwd"));

	m_nLfHifixFwd[0][0]	= 8;
	m_nLfHifixFwd[1][0]	= 1;
	m_pGridLfContact.SetItemBkColour(m_nLfHifixFwd[0][0], m_nLfHifixFwd[1][0], YELLOW_D, BLACK_C);
	m_pGridLfContact.SetItemText(m_nLfHifixFwd[0][0], m_nLfHifixFwd[1][0], _T("Lf Top Fwd"));

	m_nLfHifixFwd[0][1]	= 9;
	m_nLfHifixFwd[1][1]	= 1;
	m_pGridLfContact.SetItemBkColour(m_nLfHifixFwd[0][1], m_nLfHifixFwd[1][1], YELLOW_D, BLACK_C);
	m_pGridLfContact.SetItemText(m_nLfHifixFwd[0][1], m_nLfHifixFwd[1][1], _T("Lf Btm Fwd"));

	m_nLfHifixFwd[0][2]	= 10;
	m_nLfHifixFwd[1][2]	= 1;
	m_pGridLfContact.SetItemBkColour(m_nLfHifixFwd[0][2], m_nLfHifixFwd[1][2], YELLOW_D, BLACK_C);
	m_pGridLfContact.SetItemText(m_nLfHifixFwd[0][2], m_nLfHifixFwd[1][2], _T("Ri Fwd"));

	m_nLfHifixBwd[0][0]	= 8;
	m_nLfHifixBwd[1][0]	= 2;
	m_pGridLfContact.SetItemBkColour(m_nLfHifixBwd[0][0], m_nLfHifixBwd[1][0], YELLOW_D, BLACK_C);
	m_pGridLfContact.SetItemText(m_nLfHifixBwd[0][0], m_nLfHifixBwd[1][0], _T("Lf Top Bwd"));

	m_nLfHifixBwd[0][1]	= 9;
	m_nLfHifixBwd[1][1]	= 2;
	m_pGridLfContact.SetItemBkColour(m_nLfHifixBwd[0][1], m_nLfHifixBwd[1][1], YELLOW_D, BLACK_C);
	m_pGridLfContact.SetItemText(m_nLfHifixBwd[0][1], m_nLfHifixBwd[1][1], _T("Lf Btm Bwd"));

	m_nLfHifixBwd[0][2]	= 10;
	m_nLfHifixBwd[1][2]	= 2;
	m_pGridLfContact.SetItemBkColour(m_nLfHifixBwd[0][2], m_nLfHifixBwd[1][2], YELLOW_D, BLACK_C);
	m_pGridLfContact.SetItemText(m_nLfHifixBwd[0][2], m_nLfHifixBwd[1][2], _T("Ri Bwd"));

	m_pGridLfContact.SetItemBkColour(7, 3, BLACK_L, YELLOW_C);
	m_pGridLfContact.SetItemText(7, 3, _T("-"));

	m_pGridLfContact.SetItemBkColour(7, 4, BLACK_L, YELLOW_C);
	m_pGridLfContact.SetItemText(7, 4, _T("-"));

	m_pGridLfContact.SetItemBkColour(8, 3, BLACK_L, YELLOW_C);
	m_pGridLfContact.SetItemText(8, 3, _T("-"));

	m_pGridLfContact.SetItemBkColour(8, 4, BLACK_L, YELLOW_C);
	m_pGridLfContact.SetItemText(8, 4, _T("-"));

	m_pGridLfContact.SetItemBkColour(9, 3, BLACK_L, YELLOW_C);
	m_pGridLfContact.SetItemText(9, 3, _T("-"));

	m_pGridLfContact.SetItemBkColour(9, 4, BLACK_L, YELLOW_C);
	m_pGridLfContact.SetItemText(9, 4, _T("-"));

	m_pGridLfContact.SetItemBkColour(10, 3, BLACK_L, YELLOW_C);
	m_pGridLfContact.SetItemText(10, 3, _T("-"));

	m_pGridLfContact.SetItemBkColour(10, 4, BLACK_L, YELLOW_C);
	m_pGridLfContact.SetItemText(10, 4, _T("-"));

	// left mp
	m_pGridLfContact.MergeCells(11, 0, 13, 0);
	m_pGridLfContact.SetItemBkColour(11, 0, YELLOW_L, BLACK_C);
	m_pGridLfContact.SetItemFont(11, 0, &clsFunc.OnLogFont(15));
	m_pGridLfContact.SetItemText(11, 0, _T("Left Mp"));

	m_nLfMpOut[0][0]	= 11;
	m_nLfMpOut[1][0]	= 1;
	m_pGridLfContact.SetItemBkColour(m_nLfMpOut[0][0], m_nLfMpOut[1][0], GREEN_D, BLACK_C);
	m_pGridLfContact.SetItemText(m_nLfMpOut[0][0], m_nLfMpOut[1][0], _T("Fwd"));

	m_nLfMpOut[0][1]	= 11;
	m_nLfMpOut[1][1]	= 2;
	m_pGridLfContact.SetItemBkColour(m_nLfMpOut[0][1], m_nLfMpOut[1][1], GREEN_D, BLACK_C);
	m_pGridLfContact.SetItemText(m_nLfMpOut[0][1], m_nLfMpOut[1][1], _T("Bwd"));

	m_nLfMpFwd[0][0]	= 12;
	m_nLfMpFwd[1][0]	= 1;
	m_pGridLfContact.SetItemBkColour(m_nLfMpFwd[0][0], m_nLfMpFwd[1][0], YELLOW_D, BLACK_C);
	m_pGridLfContact.SetItemText(m_nLfMpFwd[0][0], m_nLfMpFwd[1][0], _T("Lf Fwd"));

	m_nLfMpFwd[0][1]	= 13;
	m_nLfMpFwd[1][1]	= 1;
	m_pGridLfContact.SetItemBkColour(m_nLfMpFwd[0][1], m_nLfMpFwd[1][1], YELLOW_D, BLACK_C);
	m_pGridLfContact.SetItemText(m_nLfMpFwd[0][1], m_nLfMpFwd[1][1], _T("Ri Fwd"));

	m_nLfMpBwd[0][0]	= 12;
	m_nLfMpBwd[1][0]	= 2;
	m_pGridLfContact.SetItemBkColour(m_nLfMpBwd[0][0], m_nLfMpBwd[1][0], YELLOW_D, BLACK_C);
	m_pGridLfContact.SetItemText(m_nLfMpBwd[0][0], m_nLfMpBwd[1][0], _T("Lf Bwd"));

	m_nLfMpBwd[0][1]	= 13;
	m_nLfMpBwd[1][1]	= 2;
	m_pGridLfContact.SetItemBkColour(m_nLfMpBwd[0][1], m_nLfMpBwd[1][1], YELLOW_D, BLACK_C);
	m_pGridLfContact.SetItemText(m_nLfMpBwd[0][1], m_nLfMpBwd[1][1], _T("Ri Bwd"));

	m_pGridLfContact.SetItemBkColour(11, 3, BLACK_L, YELLOW_C);
	m_pGridLfContact.SetItemText(11, 3, _T("-"));

	m_pGridLfContact.SetItemBkColour(11, 4, BLACK_L, YELLOW_C);
	m_pGridLfContact.SetItemText(11, 4, _T("-"));

	m_pGridLfContact.SetItemBkColour(12, 3, BLACK_L, YELLOW_C);
	m_pGridLfContact.SetItemText(12, 3, _T("-"));

	m_pGridLfContact.SetItemBkColour(12, 4, BLACK_L, YELLOW_C);
	m_pGridLfContact.SetItemText(12, 4, _T("-"));

	m_pGridLfContact.SetItemBkColour(13, 3, BLACK_L, YELLOW_C);
	m_pGridLfContact.SetItemText(13, 3, _T("-"));

	m_pGridLfContact.SetItemBkColour(13, 4, BLACK_L, YELLOW_C);
	m_pGridLfContact.SetItemText(13, 4, _T("-"));

	m_pGridLfContact.Invalidate(FALSE);
}

void CDialogManualIO::OnInitGridRiContact()
{
	int   i, j;
	int	  nMaxRow, nMaxCol;
//	int   nRow, nCol;
	CString strTmp;

	nMaxRow = 14; // unloader tray y count
	nMaxCol = 5;

	m_pGridRiContact.SetFrameFocusCell(FALSE);
	m_pGridRiContact.SetTrackFocusCell(FALSE);
	m_pGridRiContact.EnableSelection(FALSE);

	m_pGridRiContact.SetGridLineColor(BLACK_C);
	m_pGridRiContact.SetGridLines(1);

	m_pGridRiContact.SetRowCount(nMaxRow);
	m_pGridRiContact.SetColumnCount(nMaxCol);

	m_pGridRiContact.SetFixedRowCount(0);
	m_pGridRiContact.SetFixedColumnCount(0);
	m_pGridRiContact.SetFixedBkColor(RGB(0,0,200));
	m_pGridRiContact.SetFixedBkColor(RGB(200,200,255));
	m_pGridRiContact.SetTextBkColor(RGB(150,150,200));

	for (i=0; i<nMaxRow; i++)
	{
		m_pGridRiContact.SetRowHeight(i, 25);

		for (j=0; j<nMaxCol; j++)
		{
			if (j == 0)
			{
				m_pGridRiContact.SetColumnWidth(j, 100);
			}
			else 
			{
				m_pGridRiContact.SetColumnWidth(j, 70);
			}

			m_pGridRiContact.SetItemFormat(i, j, DT_CENTER|DT_VCENTER|DT_SINGLELINE);
			m_pGridRiContact.SetItemState(i, j, GVIS_READONLY);
			m_pGridRiContact.SetItemBkColour(i, j, WHITE_C, CLR_DEFAULT);
		}
	}


	m_pGridRiContact.Invalidate(FALSE);
}

void CDialogManualIO::OnInitGridBuffer()
{
	int   i, j;
	int	  nMaxRow, nMaxCol;
//	int   nRow, nCol;
	CString strTmp;

	nMaxRow = 6; // unloader tray y count
	nMaxCol = 5;

	m_pGridBuf.SetFrameFocusCell(FALSE);
	m_pGridBuf.SetTrackFocusCell(FALSE);
	m_pGridBuf.EnableSelection(FALSE);

	m_pGridBuf.SetGridLineColor(BLACK_C);
	m_pGridBuf.SetGridLines(1);

	m_pGridBuf.SetRowCount(nMaxRow);
	m_pGridBuf.SetColumnCount(nMaxCol);

	m_pGridBuf.SetFixedRowCount(0);
	m_pGridBuf.SetFixedColumnCount(0);
	m_pGridBuf.SetFixedBkColor(RGB(0,0,200));
	m_pGridBuf.SetFixedBkColor(RGB(200,200,255));
	m_pGridBuf.SetTextBkColor(RGB(150,150,200));

	for (i=0; i<nMaxRow; i++)
	{
		m_pGridBuf.SetRowHeight(i, 25);

		for (j=0; j<nMaxCol; j++)
		{
			if (j == 0)
			{
				m_pGridBuf.SetColumnWidth(j, 100);
			}
			else 
			{
				m_pGridBuf.SetColumnWidth(j, 70);
			}

			m_pGridBuf.SetItemFormat(i, j, DT_CENTER|DT_VCENTER|DT_SINGLELINE);
			m_pGridBuf.SetItemState(i, j, GVIS_READONLY);
			m_pGridBuf.SetItemBkColour(i, j, WHITE_C, CLR_DEFAULT);
		}
	}

	

	m_pGridBuf.Invalidate(FALSE);
}

void CDialogManualIO::OnTsiteCellClick(NMHDR *pNotifyStruct, LRESULT* pResult)
{
	int nRow, nCol;

	NM_GRIDVIEW* pItem	= (NM_GRIDVIEW*) pNotifyStruct;

	nRow				= pItem->iRow;
	nCol				= pItem->iColumn;

	switch (nRow)
	{
		case 0:
			switch (nCol)
			{
				case 0:
					m_nTsiteNum = 0;
					OnDisplayTestSite(m_nTsiteNum);

					m_pGridTsite.SetItemBkColour(0, 0, ORANGE_C, YELLOW_C);
					m_pGridTsite.SetItemBkColour(2, 0, BLACK_L, YELLOW_C);
					m_pGridTsite.SetItemBkColour(4, 0, BLACK_L, YELLOW_C);
					m_pGridTsite.SetItemBkColour(6, 0, BLACK_L, YELLOW_C);
					break;

				case 1:
					FAS_IO.set_out_bit(m_nInsertCyl[m_nTsiteNum][0], !FAS_IO.get_out_bit(m_nInsertCyl[m_nTsiteNum][0], IO_ON));
					break;

				case 2:
					FAS_IO.set_out_bit(m_nInsertCyl[m_nTsiteNum][0], !FAS_IO.get_out_bit(m_nInsertCyl[m_nTsiteNum][0], IO_ON));
					break;

				case 3:
					FAS_IO.set_out_bit(m_nInsertCyl[m_nTsiteNum][0], !FAS_IO.get_out_bit(m_nInsertCyl[m_nTsiteNum][0], IO_ON));
					break;

				case 4:
					FAS_IO.set_out_bit(m_nInsertCyl[m_nTsiteNum][0], !FAS_IO.get_out_bit(m_nInsertCyl[m_nTsiteNum][0], IO_ON));
					break;

				case 5:
					FAS_IO.set_out_bit(m_nInsertCyl[m_nTsiteNum][1], !FAS_IO.get_out_bit(m_nInsertCyl[m_nTsiteNum][1], IO_ON));
					break;

				case 6:
					FAS_IO.set_out_bit(m_nInsertCyl[m_nTsiteNum][1], !FAS_IO.get_out_bit(m_nInsertCyl[m_nTsiteNum][1], IO_ON));
					break;

				case 7:
					FAS_IO.set_out_bit(m_nInsertCyl[m_nTsiteNum][1], !FAS_IO.get_out_bit(m_nInsertCyl[m_nTsiteNum][1], IO_ON));
					break;

				case 8:
					FAS_IO.set_out_bit(m_nInsertCyl[m_nTsiteNum][1], !FAS_IO.get_out_bit(m_nInsertCyl[m_nTsiteNum][1], IO_ON));
					break;

				case 9:
					FAS_IO.set_out_bit(m_nInsertCyl[m_nTsiteNum][2], !FAS_IO.get_out_bit(m_nInsertCyl[m_nTsiteNum][2], IO_ON));
					break;

				case 10:
					FAS_IO.set_out_bit(m_nInsertCyl[m_nTsiteNum][2], !FAS_IO.get_out_bit(m_nInsertCyl[m_nTsiteNum][2], IO_ON));
					break;

				case 11:
					FAS_IO.set_out_bit(m_nInsertCyl[m_nTsiteNum][2], !FAS_IO.get_out_bit(m_nInsertCyl[m_nTsiteNum][2], IO_ON));
					break;

				case 12:
					FAS_IO.set_out_bit(m_nInsertCyl[m_nTsiteNum][2], !FAS_IO.get_out_bit(m_nInsertCyl[m_nTsiteNum][2], IO_ON));
					break;
			}
			break;

		case 1:
			switch (nCol)
			{
				case 0:
					m_nTsiteNum = 1;
					OnDisplayTestSite(m_nTsiteNum);

					m_pGridTsite.SetItemBkColour(0, 0, ORANGE_C, YELLOW_C);
					m_pGridTsite.SetItemBkColour(2, 0, BLACK_L, YELLOW_C);
					m_pGridTsite.SetItemBkColour(4, 0, BLACK_L, YELLOW_C);
					m_pGridTsite.SetItemBkColour(6, 0, BLACK_L, YELLOW_C);
					break;
			}
			break;

		case 2:
			switch (nCol)
			{
				case 0:
					m_nTsiteNum = 1;
					OnDisplayTestSite(m_nTsiteNum);

					m_pGridTsite.SetItemBkColour(0, 0, BLACK_L, YELLOW_C);
					m_pGridTsite.SetItemBkColour(2, 0, ORANGE_C, YELLOW_C);
					m_pGridTsite.SetItemBkColour(4, 0, BLACK_L, YELLOW_C);
					m_pGridTsite.SetItemBkColour(6, 0, BLACK_L, YELLOW_C);
					break;

				case 1:
					FAS_IO.set_out_bit(m_nPogoCyl[m_nTsiteNum][0], !FAS_IO.get_out_bit(m_nPogoCyl[m_nTsiteNum][0], IO_ON));
					break;

				case 2:
					FAS_IO.set_out_bit(m_nPogoCyl[m_nTsiteNum][0], !FAS_IO.get_out_bit(m_nPogoCyl[m_nTsiteNum][0], IO_ON));
					break;

				case 3:
					FAS_IO.set_out_bit(m_nPogoCyl[m_nTsiteNum][1], !FAS_IO.get_out_bit(m_nPogoCyl[m_nTsiteNum][1], IO_ON));
					break;

				case 4:
					FAS_IO.set_out_bit(m_nPogoCyl[m_nTsiteNum][1], !FAS_IO.get_out_bit(m_nPogoCyl[m_nTsiteNum][1], IO_ON));
					break;

				case 5:
					FAS_IO.set_out_bit(m_nPogoCyl[m_nTsiteNum][2], !FAS_IO.get_out_bit(m_nPogoCyl[m_nTsiteNum][2], IO_ON));
					break;

				case 6:
					FAS_IO.set_out_bit(m_nPogoCyl[m_nTsiteNum][2], !FAS_IO.get_out_bit(m_nPogoCyl[m_nTsiteNum][2], IO_ON));
					break;

				case 7:
					FAS_IO.set_out_bit(m_nPogoCyl[m_nTsiteNum][3], !FAS_IO.get_out_bit(m_nPogoCyl[m_nTsiteNum][3], IO_ON));
					break;

				case 8:
					FAS_IO.set_out_bit(m_nPogoCyl[m_nTsiteNum][3], !FAS_IO.get_out_bit(m_nPogoCyl[m_nTsiteNum][3], IO_ON));
					break;

				case 9:
					FAS_IO.set_out_bit(m_nPogoCyl[m_nTsiteNum][4], !FAS_IO.get_out_bit(m_nPogoCyl[m_nTsiteNum][4], IO_ON));
					break;

				case 10:
					FAS_IO.set_out_bit(m_nPogoCyl[m_nTsiteNum][4], !FAS_IO.get_out_bit(m_nPogoCyl[m_nTsiteNum][4], IO_ON));
					break;

				case 11:
					FAS_IO.set_out_bit(m_nPogoCyl[m_nTsiteNum][5], !FAS_IO.get_out_bit(m_nPogoCyl[m_nTsiteNum][5], IO_ON));
					break;

				case 12:
					FAS_IO.set_out_bit(m_nPogoCyl[m_nTsiteNum][5], !FAS_IO.get_out_bit(m_nPogoCyl[m_nTsiteNum][5], IO_ON));
					break;
			}
			break;

		case 3:
			switch (nCol)
			{
				case 0:
					m_nTsiteNum = 1;
					OnDisplayTestSite(m_nTsiteNum);

					m_pGridTsite.SetItemBkColour(0, 0, BLACK_L, YELLOW_C);
					m_pGridTsite.SetItemBkColour(2, 0, ORANGE_C, YELLOW_C);
					m_pGridTsite.SetItemBkColour(4, 0, BLACK_L, YELLOW_C);
					m_pGridTsite.SetItemBkColour(6, 0, BLACK_L, YELLOW_C);
					break;
			}
			break;

		case 4:
			switch (nCol)
			{
				case 0:
					m_nTsiteNum = 2;
					OnDisplayTestSite(m_nTsiteNum);

					m_pGridTsite.SetItemBkColour(0, 0, BLACK_L, YELLOW_C);
					m_pGridTsite.SetItemBkColour(2, 0, BLACK_L, YELLOW_C);
					m_pGridTsite.SetItemBkColour(4, 0, ORANGE_C, YELLOW_C);
					m_pGridTsite.SetItemBkColour(6, 0, BLACK_L, YELLOW_C);
					break;

				case 1:
					FAS_IO.set_out_bit(m_nInsertCyl[m_nTsiteNum][3], !FAS_IO.get_out_bit(m_nInsertCyl[m_nTsiteNum][3], IO_ON));
					break;

				case 2:
					FAS_IO.set_out_bit(m_nInsertCyl[m_nTsiteNum][3], !FAS_IO.get_out_bit(m_nInsertCyl[m_nTsiteNum][3], IO_ON));
					break;

				case 3:
					FAS_IO.set_out_bit(m_nInsertCyl[m_nTsiteNum][3], !FAS_IO.get_out_bit(m_nInsertCyl[m_nTsiteNum][3], IO_ON));
					break;

				case 4:
					FAS_IO.set_out_bit(m_nInsertCyl[m_nTsiteNum][3], !FAS_IO.get_out_bit(m_nInsertCyl[m_nTsiteNum][3], IO_ON));
					break;

				case 5:
					FAS_IO.set_out_bit(m_nInsertCyl[m_nTsiteNum][4], !FAS_IO.get_out_bit(m_nInsertCyl[m_nTsiteNum][4], IO_ON));
					break;

				case 6:
					FAS_IO.set_out_bit(m_nInsertCyl[m_nTsiteNum][4], !FAS_IO.get_out_bit(m_nInsertCyl[m_nTsiteNum][4], IO_ON));
					break;

				case 7:
					FAS_IO.set_out_bit(m_nInsertCyl[m_nTsiteNum][4], !FAS_IO.get_out_bit(m_nInsertCyl[m_nTsiteNum][4], IO_ON));
					break;

				case 8:
					FAS_IO.set_out_bit(m_nInsertCyl[m_nTsiteNum][4], !FAS_IO.get_out_bit(m_nInsertCyl[m_nTsiteNum][4], IO_ON));
					break;

				case 9:
					FAS_IO.set_out_bit(m_nInsertCyl[m_nTsiteNum][5], !FAS_IO.get_out_bit(m_nInsertCyl[m_nTsiteNum][5], IO_ON));
					break;

				case 10:
					FAS_IO.set_out_bit(m_nInsertCyl[m_nTsiteNum][5], !FAS_IO.get_out_bit(m_nInsertCyl[m_nTsiteNum][5], IO_ON));
					break;

				case 11:
					FAS_IO.set_out_bit(m_nInsertCyl[m_nTsiteNum][5], !FAS_IO.get_out_bit(m_nInsertCyl[m_nTsiteNum][5], IO_ON));
					break;

				case 12:
					FAS_IO.set_out_bit(m_nInsertCyl[m_nTsiteNum][5], !FAS_IO.get_out_bit(m_nInsertCyl[m_nTsiteNum][5], IO_ON));
					break;
			}
			break;

		case 5:
			switch (nCol)
			{
				case 0:
					m_nTsiteNum = 2;
					OnDisplayTestSite(m_nTsiteNum);

					m_pGridTsite.SetItemBkColour(0, 0, BLACK_L, YELLOW_C);
					m_pGridTsite.SetItemBkColour(2, 0, BLACK_L, YELLOW_C);
					m_pGridTsite.SetItemBkColour(4, 0, ORANGE_C, YELLOW_C);
					m_pGridTsite.SetItemBkColour(6, 0, BLACK_L, YELLOW_C);
					break;
			}
			break;

		case 6:
			switch (nCol)
			{
				case 0:
					m_nTsiteNum = 3;
					OnDisplayTestSite(m_nTsiteNum);

					m_pGridTsite.SetItemBkColour(0, 0, BLACK_L, YELLOW_C);
					m_pGridTsite.SetItemBkColour(2, 0, BLACK_L, YELLOW_C);
					m_pGridTsite.SetItemBkColour(4, 0, BLACK_L, YELLOW_C);
					m_pGridTsite.SetItemBkColour(6, 0, ORANGE_C, YELLOW_C);
					break;

				case 1:
					FAS_IO.set_out_bit(m_nPogoCyl[m_nTsiteNum][6], !FAS_IO.get_out_bit(m_nPogoCyl[m_nTsiteNum][6], IO_ON));
					break;

				case 2:
					FAS_IO.set_out_bit(m_nPogoCyl[m_nTsiteNum][6], !FAS_IO.get_out_bit(m_nPogoCyl[m_nTsiteNum][6], IO_ON));
					break;

				case 3:
					FAS_IO.set_out_bit(m_nPogoCyl[m_nTsiteNum][7], !FAS_IO.get_out_bit(m_nPogoCyl[m_nTsiteNum][7], IO_ON));
					break;

				case 4:
					FAS_IO.set_out_bit(m_nPogoCyl[m_nTsiteNum][7], !FAS_IO.get_out_bit(m_nPogoCyl[m_nTsiteNum][7], IO_ON));
					break;

				case 5:
					FAS_IO.set_out_bit(m_nPogoCyl[m_nTsiteNum][8], !FAS_IO.get_out_bit(m_nPogoCyl[m_nTsiteNum][8], IO_ON));
					break;

				case 6:
					FAS_IO.set_out_bit(m_nPogoCyl[m_nTsiteNum][8], !FAS_IO.get_out_bit(m_nPogoCyl[m_nTsiteNum][8], IO_ON));
					break;

				case 7:
					FAS_IO.set_out_bit(m_nPogoCyl[m_nTsiteNum][9], !FAS_IO.get_out_bit(m_nPogoCyl[m_nTsiteNum][9], IO_ON));
					break;

				case 8:
					FAS_IO.set_out_bit(m_nPogoCyl[m_nTsiteNum][9], !FAS_IO.get_out_bit(m_nPogoCyl[m_nTsiteNum][9], IO_ON));
					break;

				case 9:
					FAS_IO.set_out_bit(m_nPogoCyl[m_nTsiteNum][10], !FAS_IO.get_out_bit(m_nPogoCyl[m_nTsiteNum][10], IO_ON));
					break;

				case 10:
					FAS_IO.set_out_bit(m_nPogoCyl[m_nTsiteNum][10], !FAS_IO.get_out_bit(m_nPogoCyl[m_nTsiteNum][10], IO_ON));
					break;

				case 11:
					FAS_IO.set_out_bit(m_nPogoCyl[m_nTsiteNum][11], !FAS_IO.get_out_bit(m_nPogoCyl[m_nTsiteNum][11], IO_ON));
					break;

				case 12:
					FAS_IO.set_out_bit(m_nPogoCyl[m_nTsiteNum][11], !FAS_IO.get_out_bit(m_nPogoCyl[m_nTsiteNum][11], IO_ON));
					break;
			}
			break;

		case 7:
			switch (nCol)
			{
				case 0:
					m_nTsiteNum = 3;
					OnDisplayTestSite(m_nTsiteNum);

					m_pGridTsite.SetItemBkColour(0, 0, BLACK_L, YELLOW_C);
					m_pGridTsite.SetItemBkColour(2, 0, BLACK_L, YELLOW_C);
					m_pGridTsite.SetItemBkColour(4, 0, BLACK_L, YELLOW_C);
					m_pGridTsite.SetItemBkColour(6, 0, ORANGE_C, YELLOW_C);
					break;
			}
			break;
	}

	m_pGridTsite.Invalidate(FALSE);
}

void CDialogManualIO::OnTRbtCellClick(NMHDR *pNotifyStruct, LRESULT* pResult)
{
	int nRow, nCol;
	CString strTmp;

	NM_GRIDVIEW* pItem	= (NM_GRIDVIEW*) pNotifyStruct;

	nRow				= pItem->iRow;
	nCol				= pItem->iColumn;

	switch (nRow)
	{
		case 2:
			switch (nCol)
			{
				case 2:
					FAS_IO.set_out_bit(m_nTsiteCyl[0], !FAS_IO.get_out_bit(m_nTsiteCyl[0], IO_ON));
					break;

				case 4:
					FAS_IO.set_out_bit(m_nTsiteCyl[1], !FAS_IO.get_out_bit(m_nTsiteCyl[1], IO_ON));
					break;

				case 6:
					FAS_IO.set_out_bit(m_nTsiteCyl[2], !FAS_IO.get_out_bit(m_nTsiteCyl[2], IO_ON));
					break;

				case 8:
					FAS_IO.set_out_bit(m_nTsiteCyl[3], !FAS_IO.get_out_bit(m_nTsiteCyl[3], IO_ON));
					break;
			}
			break;

		case 3:
			switch (nCol)
			{
				case 2:
					FAS_IO.set_out_bit(m_nTsiteCyl[0], !FAS_IO.get_out_bit(m_nTsiteCyl[0], IO_ON));
					break;

				case 4:
					FAS_IO.set_out_bit(m_nTsiteCyl[1], !FAS_IO.get_out_bit(m_nTsiteCyl[1], IO_ON));
					break;

				case 6:
					FAS_IO.set_out_bit(m_nTsiteCyl[2], !FAS_IO.get_out_bit(m_nTsiteCyl[2], IO_ON));
					break;

				case 8:
					FAS_IO.set_out_bit(m_nTsiteCyl[3], !FAS_IO.get_out_bit(m_nTsiteCyl[3], IO_ON));
					break;
			}
			break;

		case 4:
			switch (nCol)
			{
				case 2:
					FAS_IO.set_out_bit(m_nTsiteVac[0], !FAS_IO.get_out_bit(m_nTsiteVac[0], IO_ON));
					break;

				case 4:
					FAS_IO.set_out_bit(m_nTsiteVac[1], !FAS_IO.get_out_bit(m_nTsiteVac[1], IO_ON));
					break;

				case 6:
					FAS_IO.set_out_bit(m_nTsiteVac[2], !FAS_IO.get_out_bit(m_nTsiteVac[2], IO_ON));
					break;

				case 8:
					FAS_IO.set_out_bit(m_nTsiteVac[3], !FAS_IO.get_out_bit(m_nTsiteVac[3], IO_ON));
					break;
			}
			break;

		case 5:
			switch (nCol)
			{
				case 2:
					FAS_IO.set_out_bit(m_nTsiteEjc[0], !FAS_IO.get_out_bit(m_nTsiteEjc[0], IO_ON));
					break;

				case 4:
					FAS_IO.set_out_bit(m_nTsiteEjc[1], !FAS_IO.get_out_bit(m_nTsiteEjc[1], IO_ON));
					break;

				case 6:
					FAS_IO.set_out_bit(m_nTsiteEjc[2], !FAS_IO.get_out_bit(m_nTsiteEjc[2], IO_ON));
					break;

				case 8:
					FAS_IO.set_out_bit(m_nTsiteEjc[3], !FAS_IO.get_out_bit(m_nTsiteEjc[3], IO_ON));
					break;
			}
			break;
	}
}

void CDialogManualIO::OnLdRbtCellClick(NMHDR *pNotifyStruct, LRESULT* pResult)
{
	int nRow, nCol;
	CString strTmp;

	NM_GRIDVIEW* pItem	= (NM_GRIDVIEW*) pNotifyStruct;

	nRow				= pItem->iRow;
	nCol				= pItem->iColumn;

	switch (nRow)
	{
		case 2:
			switch (nCol)
			{
				case 2:
					FAS_IO.set_out_bit(m_nLdCyl[0], !FAS_IO.get_out_bit(m_nLdCyl[0], IO_ON));
					break;

				case 4:
					FAS_IO.set_out_bit(m_nLdCyl[1], !FAS_IO.get_out_bit(m_nLdCyl[1], IO_ON));
					break;
			}
			break;

		case 3:
			switch (nCol)
			{
				case 2:
					FAS_IO.set_out_bit(m_nLdCyl[0], !FAS_IO.get_out_bit(m_nLdCyl[0], IO_ON));
					break;

				case 4:
					FAS_IO.set_out_bit(m_nLdCyl[1], !FAS_IO.get_out_bit(m_nLdCyl[1], IO_ON));
					break;
			}
			break;

		case 4:
			switch (nCol)
			{
				case 2:
					FAS_IO.set_out_bit(m_nLdVac[0], !FAS_IO.get_out_bit(m_nLdVac[0], IO_ON));
					break;

				case 4:
					FAS_IO.set_out_bit(m_nLdVac[1], !FAS_IO.get_out_bit(m_nLdVac[1], IO_ON));
					break;
			}
			break;

		case 5:
			switch (nCol)
			{
				case 2:
					FAS_IO.set_out_bit(m_nLdEjc[0], !FAS_IO.get_out_bit(m_nLdEjc[0], IO_ON));
					break;

				case 4:
					FAS_IO.set_out_bit(m_nLdEjc[1], !FAS_IO.get_out_bit(m_nLdEjc[1], IO_ON));
					break;
			}
			break;
	}
}

void CDialogManualIO::OnUldRbtCellClick(NMHDR *pNotifyStruct, LRESULT* pResult)
{
	int nRow, nCol;
	CString strTmp;

	NM_GRIDVIEW* pItem	= (NM_GRIDVIEW*) pNotifyStruct;

	nRow				= pItem->iRow;
	nCol				= pItem->iColumn;

	switch (nRow)
	{
		case 2:
			switch (nCol)
			{
				case 2:
					FAS_IO.set_out_bit(m_nUnLdCyl[0], !FAS_IO.get_out_bit(m_nUnLdCyl[0], IO_ON));
					break;

				case 4:
					FAS_IO.set_out_bit(m_nUnLdCyl[1], !FAS_IO.get_out_bit(m_nUnLdCyl[1], IO_ON));
					break;
			}
			break;

		case 3:
			switch (nCol)
			{
				case 2:
					FAS_IO.set_out_bit(m_nUnLdCyl[0], !FAS_IO.get_out_bit(m_nUnLdCyl[0], IO_ON));
					break;

				case 4:
					FAS_IO.set_out_bit(m_nUnLdCyl[1], !FAS_IO.get_out_bit(m_nUnLdCyl[1], IO_ON));
					break;
			}
			break;

		case 4:
			switch (nCol)
			{
				case 2:
					FAS_IO.set_out_bit(m_nUnLdVac[0], !FAS_IO.get_out_bit(m_nUnLdVac[0], IO_ON));
					break;

				case 4:
					FAS_IO.set_out_bit(m_nUnLdVac[1], !FAS_IO.get_out_bit(m_nUnLdVac[1], IO_ON));
					break;
			}
			break;

		case 5:
			switch (nCol)
			{
				case 2:
					FAS_IO.set_out_bit(m_nUnLdEjc[0], !FAS_IO.get_out_bit(m_nUnLdEjc[0], IO_ON));
					break;

				case 4:
					FAS_IO.set_out_bit(m_nUnLdEjc[1], !FAS_IO.get_out_bit(m_nUnLdEjc[1], IO_ON));
					break;
			}
			break;
	}
}

void CDialogManualIO::OnInitButton()
{
	m_btnExit.SetBitmaps(IDC_BTN_EXIT, IDB_BITMAP_EXIT, WINDOW_DN, IDB_BITMAP_EXIT, WINDOW_UP);
	m_btnExit.SetColor(CButtonST::BTNST_COLOR_BK_IN, WINDOW_DN);
	m_btnExit.SetColor(CButtonST::BTNST_COLOR_BK_OUT, WINDOW_UP);
	m_btnExit.SetColor(CButtonST::BTNST_COLOR_BK_FOCUS, WINDOW_UP);
	m_btnExit.SetColor(CButtonST::BTNST_COLOR_FG_IN, BLACK_C);
	m_btnExit.SetColor(CButtonST::BTNST_COLOR_FG_OUT, BLUE_C);
	m_btnExit.SetColor(CButtonST::BTNST_COLOR_FG_FOCUS, BLUE_C);
	m_btnExit.SetFont(clsFunc.m_pFont[3]);
	m_btnExit.SetTooltipText(_T("Exit"));

// 	m_btnDoor.SetBitmaps(IDC_BTN_REFRESH, IDB_BITMAP_DOOR_OPEN, WINDOW_DN, IDB_BITMAP_DOOR_OPEN, WINDOW_UP);
// 	m_btnDoor.SetColor(CButtonST::BTNST_COLOR_BK_IN, WINDOW_DN);
// 	m_btnDoor.SetColor(CButtonST::BTNST_COLOR_BK_OUT, WINDOW_UP);
// 	m_btnDoor.SetColor(CButtonST::BTNST_COLOR_BK_FOCUS, WINDOW_UP);
// 	m_btnDoor.SetColor(CButtonST::BTNST_COLOR_FG_IN, BLACK_C);
// 	m_btnDoor.SetColor(CButtonST::BTNST_COLOR_FG_OUT, BLUE_C);
// 	m_btnDoor.SetColor(CButtonST::BTNST_COLOR_FG_FOCUS, BLUE_C);
// 	m_btnDoor.SetFont(clsFunc.m_pFont[3]);
// 	m_btnDoor.SetTooltipText(_T("Door Open"));
// 
// 	m_btnLeftMpClamp.SetBitmaps(IDC_BTN_LEFT_CLAMP, IDB_BITMAP_GEAR_DN, WINDOW_DN, IDB_BITMAP_GEAR_UP, WINDOW_UP);
// 	m_btnLeftMpClamp.SetColor(CButtonST::BTNST_COLOR_BK_IN, WINDOW_DN);
// 	m_btnLeftMpClamp.SetColor(CButtonST::BTNST_COLOR_BK_OUT, WINDOW_UP);
// 	m_btnLeftMpClamp.SetColor(CButtonST::BTNST_COLOR_BK_FOCUS, WINDOW_UP);
// 	m_btnLeftMpClamp.SetColor(CButtonST::BTNST_COLOR_FG_IN, BLACK_C);
// 	m_btnLeftMpClamp.SetColor(CButtonST::BTNST_COLOR_FG_OUT, BLUE_C);
// 	m_btnLeftMpClamp.SetColor(CButtonST::BTNST_COLOR_FG_FOCUS, BLUE_C);
// 	m_btnLeftMpClamp.SetFont(clsFunc.m_pFont[3]);
// 	m_btnLeftMpClamp.SetTooltipText(_T("Left Clamp"));
// 
// 	m_btnLeftMpUnClamp.SetBitmaps(IDC_BTN_LEFT_UNCLAMP, IDB_BITMAP_GEAR_DN, WINDOW_DN, IDB_BITMAP_GEAR_UP, WINDOW_UP);
// 	m_btnLeftMpUnClamp.SetColor(CButtonST::BTNST_COLOR_BK_IN, WINDOW_DN);
// 	m_btnLeftMpUnClamp.SetColor(CButtonST::BTNST_COLOR_BK_OUT, WINDOW_UP);
// 	m_btnLeftMpUnClamp.SetColor(CButtonST::BTNST_COLOR_BK_FOCUS, WINDOW_UP);
// 	m_btnLeftMpUnClamp.SetColor(CButtonST::BTNST_COLOR_FG_IN, BLACK_C);
// 	m_btnLeftMpUnClamp.SetColor(CButtonST::BTNST_COLOR_FG_OUT, BLUE_C);
// 	m_btnLeftMpUnClamp.SetColor(CButtonST::BTNST_COLOR_FG_FOCUS, BLUE_C);
// 	m_btnLeftMpUnClamp.SetFont(clsFunc.m_pFont[3]);
// 	m_btnLeftMpUnClamp.SetTooltipText(_T("Left UnClamp"));
// 
// 	m_btnRightMpClamp.SetBitmaps(IDC_BTN_RIGHT_CLAMP, IDB_BITMAP_GEAR_DN, WINDOW_DN, IDB_BITMAP_GEAR_UP, WINDOW_UP);
// 	m_btnRightMpClamp.SetColor(CButtonST::BTNST_COLOR_BK_IN, WINDOW_DN);
// 	m_btnRightMpClamp.SetColor(CButtonST::BTNST_COLOR_BK_OUT, WINDOW_UP);
// 	m_btnRightMpClamp.SetColor(CButtonST::BTNST_COLOR_BK_FOCUS, WINDOW_UP);
// 	m_btnRightMpClamp.SetColor(CButtonST::BTNST_COLOR_FG_IN, BLACK_C);
// 	m_btnRightMpClamp.SetColor(CButtonST::BTNST_COLOR_FG_OUT, BLUE_C);
// 	m_btnRightMpClamp.SetColor(CButtonST::BTNST_COLOR_FG_FOCUS, BLUE_C);
// 	m_btnRightMpClamp.SetFont(clsFunc.m_pFont[3]);
// 	m_btnRightMpClamp.SetTooltipText(_T("Right Clamp"));
// 
// 	m_btnRightMpUnClamp.SetBitmaps(IDC_BTN_RIGHT_UNCLAMP, IDB_BITMAP_GEAR_DN, WINDOW_DN, IDB_BITMAP_GEAR_UP, WINDOW_UP);
// 	m_btnRightMpUnClamp.SetColor(CButtonST::BTNST_COLOR_BK_IN, WINDOW_DN);
// 	m_btnRightMpUnClamp.SetColor(CButtonST::BTNST_COLOR_BK_OUT, WINDOW_UP);
// 	m_btnRightMpUnClamp.SetColor(CButtonST::BTNST_COLOR_BK_FOCUS, WINDOW_UP);
// 	m_btnRightMpUnClamp.SetColor(CButtonST::BTNST_COLOR_FG_IN, BLACK_C);
// 	m_btnRightMpUnClamp.SetColor(CButtonST::BTNST_COLOR_FG_OUT, BLUE_C);
// 	m_btnRightMpUnClamp.SetColor(CButtonST::BTNST_COLOR_FG_FOCUS, BLUE_C);
// 	m_btnRightMpUnClamp.SetFont(clsFunc.m_pFont[3]);
// 	m_btnRightMpUnClamp.SetTooltipText(_T("Right UnClamp"));
}

void CDialogManualIO::OnBnClickedBtnExit()
{
	// TODO: 여기에 컨트롤 알림 처리기 코드를 추가합니다.
//	CDialog::OnOK();
	if (st_handler_info.cWndMotor != NULL)
	{
		st_handler_info.cWndMotor->SendMessage(WM_WORK_COMMAND, MOTOR_IO_DELETE_REQ, 0);
	}
}


void CDialogManualIO::OnDisplayTestSite(int nNum)
{
	int i;
	CString strTemp;

	
}

void CDialogManualIO::OnLeftContactCellClick(NMHDR *pNotifyStruct, LRESULT* pResult)
{
	int nRow, nCol;
	CString strTmp;

	NM_GRIDVIEW* pItem	= (NM_GRIDVIEW*) pNotifyStruct;

	nRow				= pItem->iRow;
	nCol				= pItem->iColumn;

	switch (nRow)
	{
		case 1:
			switch (nCol)
			{
				case 1:
					FAS_IO.set_out_bit(m_nLfCokCyl[0], !FAS_IO.get_out_bit(m_nLfCokCyl[0], IO_ON));
					break;

				case 2:
					FAS_IO.set_out_bit(m_nLfCokCyl[0], !FAS_IO.get_out_bit(m_nLfCokCyl[0], IO_ON));
					break;

				case 3:
					FAS_IO.set_out_bit(m_nLfCokCyl[1], !FAS_IO.get_out_bit(m_nLfCokCyl[1], IO_ON));
					break;

				case 4:
					FAS_IO.set_out_bit(m_nLfCokCyl[1], !FAS_IO.get_out_bit(m_nLfCokCyl[1], IO_ON));
					break;
			}
			break;

		case 4:
			switch (nCol)
			{
				case 1:
					FAS_IO.set_out_bit(m_nLfContactFwdCyl[0], !FAS_IO.get_out_bit(m_nLfContactFwdCyl[0], IO_ON));
					break;

				case 2:
					FAS_IO.set_out_bit(m_nLfContactBwdCyl[0], !FAS_IO.get_out_bit(m_nLfContactBwdCyl[0], IO_ON));
					break;

				case 3:
					FAS_IO.set_out_bit(m_nLfContactFwdCyl[1], !FAS_IO.get_out_bit(m_nLfContactFwdCyl[1], IO_ON));
					break;

				case 4:
					FAS_IO.set_out_bit(m_nLfContactBwdCyl[1], !FAS_IO.get_out_bit(m_nLfContactBwdCyl[1], IO_ON));
					break;
			}
			break;

		case 7:
			switch (nCol)
			{
				case 1:
					FAS_IO.set_out_bit(m_nLfHifixFwdCyl, !FAS_IO.get_out_bit(m_nLfHifixFwdCyl, IO_ON));
					break;

				case 2:
					FAS_IO.set_out_bit(m_nLfHifixBwdCyl, !FAS_IO.get_out_bit(m_nLfHifixBwdCyl, IO_ON));
					break;
			}
			break;

		case 11:
			switch (nCol)
			{
				case 1:
					FAS_IO.set_out_bit(m_nLfMpFwdCyl, !FAS_IO.get_out_bit(m_nLfMpFwdCyl, IO_ON));
					break;

				case 2:
					FAS_IO.set_out_bit(m_nLfMpBwdCyl, !FAS_IO.get_out_bit(m_nLfMpBwdCyl, IO_ON));
					break;
			}
			break;
	}
}

void CDialogManualIO::OnRightContactCellClick(NMHDR *pNotifyStruct, LRESULT* pResult)
{
	int nRow, nCol;
	CString strTmp;

	NM_GRIDVIEW* pItem	= (NM_GRIDVIEW*) pNotifyStruct;

	nRow				= pItem->iRow;
	nCol				= pItem->iColumn;

	switch (nRow)
	{
		case 1:
			switch (nCol)
			{
				case 1:
					FAS_IO.set_out_bit(m_nRiCokCyl[0], !FAS_IO.get_out_bit(m_nRiCokCyl[0], IO_ON));
					break;

				case 2:
					FAS_IO.set_out_bit(m_nRiCokCyl[0], !FAS_IO.get_out_bit(m_nRiCokCyl[0], IO_ON));
					break;

				case 3:
					FAS_IO.set_out_bit(m_nRiCokCyl[1], !FAS_IO.get_out_bit(m_nRiCokCyl[1], IO_ON));
					break;

				case 4:
					FAS_IO.set_out_bit(m_nRiCokCyl[1], !FAS_IO.get_out_bit(m_nRiCokCyl[1], IO_ON));
					break;
			}
			break;

		case 4:
			switch (nCol)
			{
				case 1:
					FAS_IO.set_out_bit(m_nRiContactFwdCyl[0], !FAS_IO.get_out_bit(m_nRiContactFwdCyl[0], IO_ON));
					break;

				case 2:
					FAS_IO.set_out_bit(m_nRiContactBwdCyl[0], !FAS_IO.get_out_bit(m_nRiContactBwdCyl[0], IO_ON));
					break;

				case 3:
					FAS_IO.set_out_bit(m_nRiContactFwdCyl[1], !FAS_IO.get_out_bit(m_nRiContactFwdCyl[1], IO_ON));
					break;

				case 4:
					FAS_IO.set_out_bit(m_nRiContactBwdCyl[1], !FAS_IO.get_out_bit(m_nRiContactBwdCyl[1], IO_ON));
					break;
			}
			break;

		case 7:
			switch (nCol)
			{
				case 1:
					FAS_IO.set_out_bit(m_nRiHifixFwdCyl, !FAS_IO.get_out_bit(m_nRiHifixFwdCyl, IO_ON));
					break;

				case 2:
					FAS_IO.set_out_bit(m_nRiHifixBwdCyl, !FAS_IO.get_out_bit(m_nRiHifixBwdCyl, IO_ON));
					break;
			}
			break;

		case 11:
			switch (nCol)
			{
				case 1:
					FAS_IO.set_out_bit(m_nRiMpFwdCyl, !FAS_IO.get_out_bit(m_nRiMpFwdCyl, IO_ON));
					break;

				case 2:
					FAS_IO.set_out_bit(m_nRiMpBwdCyl, !FAS_IO.get_out_bit(m_nRiMpBwdCyl, IO_ON));
					break;
			}
			break;
	}
}

void CDialogManualIO::OnBufferCellClick(NMHDR *pNotifyStruct, LRESULT* pResult)
{
	int nRow, nCol;
	CString strTmp;

	NM_GRIDVIEW* pItem	= (NM_GRIDVIEW*) pNotifyStruct;

	nRow				= pItem->iRow;
	nCol				= pItem->iColumn;

	switch (nRow)
	{
		case 1:
			switch (nCol)
			{
				case 1:
					FAS_IO.set_out_bit(m_nRetestMvFwdCyl, !FAS_IO.get_out_bit(m_nRetestMvFwdCyl, IO_ON));
					break;

				case 2:
					FAS_IO.set_out_bit(m_nRetestMvBwdCyl, !FAS_IO.get_out_bit(m_nRetestMvBwdCyl, IO_ON));
					break;
			}
			break;

		case 2:
			switch (nCol)
			{
				case 1:
					FAS_IO.set_out_bit(m_nRetestAlignCyl, !FAS_IO.get_out_bit(m_nRetestAlignCyl, IO_ON));
					break;

				case 2:
					FAS_IO.set_out_bit(m_nRetestAlignCyl, !FAS_IO.get_out_bit(m_nRetestAlignCyl, IO_ON));
					break;
			}
			break;

		case 3:
			switch (nCol)
			{
				case 1:
					FAS_IO.set_out_bit(m_nRejectClampCyl, !FAS_IO.get_out_bit(m_nRejectClampCyl, IO_ON));
					break;

				case 2:
					FAS_IO.set_out_bit(m_nRejectClampCyl, !FAS_IO.get_out_bit(m_nRejectClampCyl, IO_ON));
					break;
			}
			break;

		case 4:
			switch (nCol)
			{
				case 1:
					FAS_IO.set_out_bit(m_nRejectUpDnCyl, !FAS_IO.get_out_bit(m_nRejectUpDnCyl, IO_ON));
					break;

				case 2:
					FAS_IO.set_out_bit(m_nRejectUpDnCyl, !FAS_IO.get_out_bit(m_nRejectUpDnCyl, IO_ON));
					break;
			}
			break;

		case 5:
			switch (nCol)
			{
				case 1:
					FAS_IO.set_out_bit(m_nRejectMvFwdCyl, !FAS_IO.get_out_bit(m_nRejectMvFwdCyl, IO_ON));
					break;

				case 2:
					FAS_IO.set_out_bit(m_nRejectMvBwdCyl, !FAS_IO.get_out_bit(m_nRejectMvBwdCyl, IO_ON));
					break;
			}
			break;
	}
}

void CDialogManualIO::OnDisplayLdRobot()
{
	int i;

	for (i=0; i<2; i++)
	{
		if (FAS_IO.get_in_bit(m_nLdFwdChk[i], IO_OFF) == IO_OFF)
		{
			m_pGridLdRbt.SetItemBkColour(m_nLdDnIn[0][i], m_nLdDnIn[1][i], YELLOW_D, BLACK_C);
		}
		else
		{
			m_pGridLdRbt.SetItemBkColour(m_nLdDnIn[0][i], m_nLdDnIn[1][i], YELLOW_C, BLACK_C);
		}

		if (FAS_IO.get_in_bit(m_nLdBwdChk[i], IO_OFF) == IO_OFF)
		{
			m_pGridLdRbt.SetItemBkColour(m_nLdUpIn[0][i], m_nLdUpIn[1][i], YELLOW_D, BLACK_C);
		}
		else
		{
			m_pGridLdRbt.SetItemBkColour(m_nLdUpIn[0][i], m_nLdUpIn[1][i], YELLOW_C, BLACK_C);
		}

		if (FAS_IO.get_in_bit(m_nLdVacChk[i], IO_OFF) == IO_OFF)
		{
			m_pGridLdRbt.SetItemBkColour(m_nLdVacIn[0][i], m_nLdVacIn[1][i], YELLOW_D, BLACK_C);
		}
		else
		{
			m_pGridLdRbt.SetItemBkColour(m_nLdVacIn[0][i], m_nLdVacIn[1][i], YELLOW_C, BLACK_C);
		}

		if (FAS_IO.get_out_bit(m_nLdCyl[i], IO_OFF) == IO_OFF)
		{
			m_pGridLdRbt.SetItemBkColour(m_nLdDnOut[0][i], m_nLdDnOut[1][i], GREEN_D, BLACK_C);
		}
		else
		{
			m_pGridLdRbt.SetItemBkColour(m_nLdDnOut[0][i], m_nLdDnOut[1][i], GREEN_C, BLACK_C);
		}

		if (FAS_IO.get_out_bit(m_nLdVac[i], IO_OFF) == IO_OFF)
		{
			m_pGridLdRbt.SetItemBkColour(m_nLdVacOut[0][i], m_nLdVacOut[1][i], GREEN_D, BLACK_C);
		}
		else
		{
			m_pGridLdRbt.SetItemBkColour(m_nLdVacOut[0][i], m_nLdVacOut[1][i], GREEN_C, BLACK_C);
		}

		if (FAS_IO.get_out_bit(m_nLdEjc[i], IO_OFF) == IO_OFF)
		{
			m_pGridLdRbt.SetItemBkColour(m_nLdEjcOut[0][i], m_nLdEjcOut[1][i], GREEN_D, BLACK_C);
		}
		else
		{
			m_pGridLdRbt.SetItemBkColour(m_nLdEjcOut[0][i], m_nLdEjcOut[1][i], GREEN_C, BLACK_C);
		}
	}

	m_pGridLdRbt.Invalidate(FALSE);
}

void CDialogManualIO::OnDisplayUnLdRobot()
{
	int i;

	for (i=0; i<2; i++)
	{
		if (FAS_IO.get_in_bit(m_nUnLdFwdChk[i], IO_OFF) == IO_OFF)
		{
			m_pGridUldRbt.SetItemBkColour(m_nUnLdDnIn[0][i], m_nUnLdDnIn[1][i], YELLOW_D, BLACK_C);
		}
		else
		{
			m_pGridUldRbt.SetItemBkColour(m_nUnLdDnIn[0][i], m_nUnLdDnIn[1][i], YELLOW_C, BLACK_C);
		}

		if (FAS_IO.get_in_bit(m_nUnLdBwdChk[i], IO_OFF) == IO_OFF)
		{
			m_pGridUldRbt.SetItemBkColour(m_nUnLdUpIn[0][i], m_nUnLdUpIn[1][i], YELLOW_D, BLACK_C);
		}
		else
		{
			m_pGridUldRbt.SetItemBkColour(m_nUnLdUpIn[0][i], m_nUnLdUpIn[1][i], YELLOW_C, BLACK_C);
		}

		if (FAS_IO.get_in_bit(m_nUnLdVacChk[i], IO_OFF) == IO_OFF)
		{
			m_pGridUldRbt.SetItemBkColour(m_nUnLdVacIn[0][i], m_nUnLdVacIn[1][i], YELLOW_D, BLACK_C);
		}
		else
		{
			m_pGridUldRbt.SetItemBkColour(m_nUnLdVacIn[0][i], m_nUnLdVacIn[1][i], YELLOW_C, BLACK_C);
		}

		if (FAS_IO.get_out_bit(m_nUnLdCyl[i], IO_OFF) == IO_OFF)
		{
			m_pGridUldRbt.SetItemBkColour(m_nUnLdDnOut[0][i], m_nUnLdDnOut[1][i], GREEN_D, BLACK_C);
		}
		else
		{
			m_pGridUldRbt.SetItemBkColour(m_nUnLdDnOut[0][i], m_nUnLdDnOut[1][i], GREEN_C, BLACK_C);
		}

		if (FAS_IO.get_out_bit(m_nUnLdVac[i], IO_OFF) == IO_OFF)
		{
			m_pGridUldRbt.SetItemBkColour(m_nUnLdVacOut[0][i], m_nUnLdVacOut[1][i], GREEN_D, BLACK_C);
		}
		else
		{
			m_pGridUldRbt.SetItemBkColour(m_nUnLdVacOut[0][i], m_nUnLdVacOut[1][i], GREEN_C, BLACK_C);
		}

		if (FAS_IO.get_out_bit(m_nUnLdEjc[i], IO_OFF) == IO_OFF)
		{
			m_pGridUldRbt.SetItemBkColour(m_nUnLdEjcOut[0][i], m_nUnLdEjcOut[1][i], GREEN_D, BLACK_C);
		}
		else
		{
			m_pGridUldRbt.SetItemBkColour(m_nUnLdEjcOut[0][i], m_nUnLdEjcOut[1][i], GREEN_C, BLACK_C);
		}
	}

	m_pGridUldRbt.Invalidate(FALSE);
}

void CDialogManualIO::OnDisplayTestSiteRobot()
{
	int i;

	for (i=0; i<4; i++)
	{
		if (FAS_IO.get_in_bit(m_nTsiteFwdChk[i], IO_OFF) == IO_OFF)
		{
			m_pGridTRbt.SetItemBkColour(m_nTsiteDnIn[0][i], m_nTsiteDnIn[1][i], YELLOW_D, BLACK_C);
		}
		else
		{
			m_pGridTRbt.SetItemBkColour(m_nTsiteDnIn[0][i], m_nTsiteDnIn[1][i], YELLOW_C, BLACK_C);
		}

		if (FAS_IO.get_in_bit(m_nTsiteBwdChk[i], IO_OFF) == IO_OFF)
		{
			m_pGridTRbt.SetItemBkColour(m_nTsiteUpIn[0][i], m_nTsiteUpIn[1][i], YELLOW_D, BLACK_C);
		}
		else
		{
			m_pGridTRbt.SetItemBkColour(m_nTsiteUpIn[0][i], m_nTsiteUpIn[1][i], YELLOW_C, BLACK_C);
		}

		if (FAS_IO.get_in_bit(m_nTsiteVacChk[i], IO_OFF) == IO_OFF)
		{
			m_pGridTRbt.SetItemBkColour(m_nTsiteVacIn[0][i], m_nTsiteVacIn[1][i], YELLOW_D, BLACK_C);
		}
		else
		{
			m_pGridTRbt.SetItemBkColour(m_nTsiteVacIn[0][i], m_nTsiteVacIn[1][i], YELLOW_C, BLACK_C);
		}

		if (FAS_IO.get_out_bit(m_nTsiteCyl[i], IO_OFF) == IO_OFF)
		{
			m_pGridTRbt.SetItemBkColour(m_nTsiteDnOut[0][i], m_nTsiteDnOut[1][i], GREEN_D, BLACK_C);
		}
		else
		{
			m_pGridTRbt.SetItemBkColour(m_nTsiteDnOut[0][i], m_nTsiteDnOut[1][i], GREEN_C, BLACK_C);
		}

		if (FAS_IO.get_out_bit(m_nTsiteVac[i], IO_OFF) == IO_OFF)
		{
			m_pGridTRbt.SetItemBkColour(m_nTsiteVacOut[0][i], m_nTsiteVacOut[1][i], GREEN_D, BLACK_C);
		}
		else
		{
			m_pGridTRbt.SetItemBkColour(m_nTsiteVacOut[0][i], m_nTsiteVacOut[1][i], GREEN_C, BLACK_C);
		}

		if (FAS_IO.get_out_bit(m_nTsiteEjc[i], IO_OFF) == IO_OFF)
		{
			m_pGridTRbt.SetItemBkColour(m_nTsiteEjcOut[0][i], m_nTsiteEjcOut[1][i], GREEN_D, BLACK_C);
		}
		else
		{
			m_pGridTRbt.SetItemBkColour(m_nTsiteEjcOut[0][i], m_nTsiteEjcOut[1][i], GREEN_C, BLACK_C);
		}
	}

	m_pGridTRbt.Invalidate(FALSE);
}

void CDialogManualIO::OnDisplayTestSite()
{
	int i;

	for (i=0; i<3; i++)
	{
		if (FAS_IO.get_out_bit(m_nInsertCyl[m_nTsiteNum][i], IO_OFF) == IO_OFF)
		{
			m_pGridTsite.SetItemBkColour(m_nTsiteInsOut[0][i], m_nTsiteInsOut[1][i], GREEN_D, BLACK_C);
		}
		else
		{
			m_pGridTsite.SetItemBkColour(m_nTsiteInsOut[0][i], m_nTsiteInsOut[1][i], GREEN_C, BLACK_C);
		}

		if (FAS_IO.get_in_bit(m_nInsertFwdChk[m_nTsiteNum][i], IO_OFF) == IO_OFF)
		{
			m_pGridTsite.SetItemBkColour(m_nTsiteInsFwd[0][i], m_nTsiteInsFwd[1][i], YELLOW_D, BLACK_C);
		}
		else
		{
			m_pGridTsite.SetItemBkColour(m_nTsiteInsFwd[0][i], m_nTsiteInsFwd[1][i], YELLOW_C, BLACK_C);
		}
		
		if (FAS_IO.get_in_bit(m_nInsertBwdChk[m_nTsiteNum][i], IO_OFF) == IO_OFF)
		{
			m_pGridTsite.SetItemBkColour(m_nTsiteInsBwd[0][i], m_nTsiteInsBwd[1][i], YELLOW_D, BLACK_C);
		}
		else
		{
			m_pGridTsite.SetItemBkColour(m_nTsiteInsBwd[0][i], m_nTsiteInsBwd[1][i], YELLOW_C, BLACK_C);
		}
		
		if (FAS_IO.get_out_bit(m_nInsertCyl[m_nTsiteNum][i + 3], IO_OFF) == IO_OFF)
		{
			m_pGridTsite.SetItemBkColour(m_nTsiteInsOut[0][i + 3], m_nTsiteInsOut[1][i + 3], GREEN_D, BLACK_C);
		}
		else
		{
			m_pGridTsite.SetItemBkColour(m_nTsiteInsOut[0][i + 3], m_nTsiteInsOut[1][i + 3], GREEN_C, BLACK_C);
		}
		
		if (FAS_IO.get_in_bit(m_nInsertFwdChk[m_nTsiteNum][i + 3], IO_OFF) == IO_OFF)
		{
			m_pGridTsite.SetItemBkColour(m_nTsiteInsFwd[0][i + 3], m_nTsiteInsFwd[1][i + 3], YELLOW_D, BLACK_C);
		}
		else
		{
			m_pGridTsite.SetItemBkColour(m_nTsiteInsFwd[0][i + 3], m_nTsiteInsFwd[1][i + 3], YELLOW_C, BLACK_C);
		}
		
		if (FAS_IO.get_in_bit(m_nInsertBwdChk[m_nTsiteNum][i + 3], IO_OFF) == IO_OFF)
		{
			m_pGridTsite.SetItemBkColour(m_nTsiteInsBwd[0][i + 3], m_nTsiteInsBwd[1][i + 3], YELLOW_D, BLACK_C);
		}
		else
		{
			m_pGridTsite.SetItemBkColour(m_nTsiteInsBwd[0][i + 3], m_nTsiteInsBwd[1][i + 3], YELLOW_C, BLACK_C);
		}
	}

	for (i=0; i<6; i++)
	{
		if (FAS_IO.get_out_bit(m_nPogoCyl[m_nTsiteNum][i], IO_OFF) == IO_OFF)
		{
			m_pGridTsite.SetItemBkColour(m_nTsitePogoOut[0][i], m_nTsitePogoOut[1][i], GREEN_D, BLACK_C);
		}
		else
		{
			m_pGridTsite.SetItemBkColour(m_nTsitePogoOut[0][i], m_nTsitePogoOut[1][i], GREEN_C, BLACK_C);
		}
		
		if (FAS_IO.get_in_bit(m_nPogoOnOffChk[m_nTsiteNum][i], IO_OFF) == IO_OFF)
		{
			m_pGridTsite.SetItemBkColour(m_nTsitePogoIn[0][i], m_nTsitePogoIn[1][i], YELLOW_D, BLACK_C);
		}
		else
		{
			m_pGridTsite.SetItemBkColour(m_nTsitePogoIn[0][i], m_nTsitePogoIn[1][i], YELLOW_C, BLACK_C);
		}
		
		if (FAS_IO.get_out_bit(m_nPogoCyl[m_nTsiteNum][i + 6], IO_OFF) == IO_OFF)
		{
			m_pGridTsite.SetItemBkColour(m_nTsitePogoOut[0][i + 6], m_nTsitePogoOut[1][i + 6], GREEN_D, BLACK_C);
		}
		else
		{
			m_pGridTsite.SetItemBkColour(m_nTsitePogoOut[0][i + 6], m_nTsitePogoOut[1][i + 6], GREEN_C, BLACK_C);
		}
		
		if (FAS_IO.get_in_bit(m_nPogoOnOffChk[m_nTsiteNum][i + 6], IO_OFF) == IO_OFF)
		{
			m_pGridTsite.SetItemBkColour(m_nTsitePogoIn[0][i + 6], m_nTsitePogoIn[1][i + 6], YELLOW_D, BLACK_C);
		}
		else
		{
			m_pGridTsite.SetItemBkColour(m_nTsitePogoIn[0][i + 6], m_nTsitePogoIn[1][i + 6], YELLOW_C, BLACK_C);
		}
	}

	m_pGridTsite.Invalidate(FALSE);
}

void CDialogManualIO::OnDisplayLeftContact()
{
	if (FAS_IO.get_out_bit(m_nLfCokCyl[0], IO_OFF) == IO_OFF)
	{
		m_pGridLfContact.SetItemBkColour(m_nLfBCokClampOut[0], m_nLfBCokClampOut[1], GREEN_D, BLACK_C);
	}
	else
	{
		m_pGridLfContact.SetItemBkColour(m_nLfBCokClampOut[0], m_nLfBCokClampOut[1], GREEN_C, BLACK_C);
	}

	if (FAS_IO.get_in_bit(m_nLfCokFwdChk[0][0], IO_OFF) == IO_OFF)
	{
		m_pGridLfContact.SetItemBkColour(m_nLfBCokClampFwd[0][0], m_nLfBCokClampFwd[1][0], YELLOW_D, BLACK_C);
	}
	else
	{
		m_pGridLfContact.SetItemBkColour(m_nLfBCokClampFwd[0][0], m_nLfBCokClampFwd[1][0], YELLOW_C, BLACK_C);
	}

	if (FAS_IO.get_in_bit(m_nLfCokFwdChk[0][1], IO_OFF) == IO_OFF)
	{
		m_pGridLfContact.SetItemBkColour(m_nLfBCokClampFwd[0][1], m_nLfBCokClampFwd[1][1], YELLOW_D, BLACK_C);
	}
	else
	{
		m_pGridLfContact.SetItemBkColour(m_nLfBCokClampFwd[0][1], m_nLfBCokClampFwd[1][1], YELLOW_C, BLACK_C);
	}
	
	if (FAS_IO.get_in_bit(m_nLfCokBwdChk[0][0], IO_OFF) == IO_OFF)
	{
		m_pGridLfContact.SetItemBkColour(m_nLfBCokClampBwd[0][0], m_nLfBCokClampBwd[1][0], YELLOW_D, BLACK_C);
	}
	else
	{
		m_pGridLfContact.SetItemBkColour(m_nLfBCokClampBwd[0][0], m_nLfBCokClampBwd[1][0], YELLOW_C, BLACK_C);
	}

	if (FAS_IO.get_in_bit(m_nLfCokBwdChk[0][1], IO_OFF) == IO_OFF)
	{
		m_pGridLfContact.SetItemBkColour(m_nLfBCokClampBwd[0][1], m_nLfBCokClampBwd[1][1], YELLOW_D, BLACK_C);
	}
	else
	{
		m_pGridLfContact.SetItemBkColour(m_nLfBCokClampBwd[0][1], m_nLfBCokClampBwd[1][1], YELLOW_C, BLACK_C);
	}
	// top
	if (FAS_IO.get_out_bit(m_nLfCokCyl[1], IO_OFF) == IO_OFF)
	{
		m_pGridLfContact.SetItemBkColour(m_nLfTCokClampOut[0], m_nLfTCokClampOut[1], GREEN_D, BLACK_C);
	}
	else
	{
		m_pGridLfContact.SetItemBkColour(m_nLfTCokClampOut[0], m_nLfTCokClampOut[1], GREEN_C, BLACK_C);
	}

	if (FAS_IO.get_in_bit(m_nLfCokFwdChk[1][0], IO_OFF) == IO_OFF)
	{
		m_pGridLfContact.SetItemBkColour(m_nLfTCokClampFwd[0][0], m_nLfTCokClampFwd[1][0], YELLOW_D, BLACK_C);
	}
	else
	{
		m_pGridLfContact.SetItemBkColour(m_nLfTCokClampFwd[0][0], m_nLfTCokClampFwd[1][0], YELLOW_C, BLACK_C);
	}
	
	if (FAS_IO.get_in_bit(m_nLfCokFwdChk[1][1], IO_OFF) == IO_OFF)
	{
		m_pGridLfContact.SetItemBkColour(m_nLfTCokClampFwd[0][1], m_nLfTCokClampFwd[1][1], YELLOW_D, BLACK_C);
	}
	else
	{
		m_pGridLfContact.SetItemBkColour(m_nLfTCokClampFwd[0][1], m_nLfTCokClampFwd[1][1], YELLOW_C, BLACK_C);
	}

	if (FAS_IO.get_in_bit(m_nLfCokBwdChk[1][0], IO_OFF) == IO_OFF)
	{
		m_pGridLfContact.SetItemBkColour(m_nLfTCokClampBwd[0][0], m_nLfTCokClampBwd[1][0], YELLOW_D, BLACK_C);
	}
	else
	{
		m_pGridLfContact.SetItemBkColour(m_nLfTCokClampBwd[0][0], m_nLfTCokClampBwd[1][0], YELLOW_C, BLACK_C);
	}

	if (FAS_IO.get_in_bit(m_nLfCokBwdChk[1][1], IO_OFF) == IO_OFF)
	{
		m_pGridLfContact.SetItemBkColour(m_nLfTCokClampBwd[0][1], m_nLfTCokClampBwd[1][1], YELLOW_D, BLACK_C);
	}
	else
	{
		m_pGridLfContact.SetItemBkColour(m_nLfTCokClampBwd[0][1], m_nLfTCokClampBwd[1][1], YELLOW_C, BLACK_C);
	}

	// left contact
	if (FAS_IO.get_out_bit(m_nLfContactFwdCyl[0], IO_OFF) == IO_OFF)
	{
		m_pGridLfContact.SetItemBkColour(m_nLfBContactOut[0][0], m_nLfBContactOut[1][0], GREEN_D, BLACK_C);
	}
	else
	{
		m_pGridLfContact.SetItemBkColour(m_nLfBContactOut[0][0], m_nLfBContactOut[1][0], GREEN_C, BLACK_C);
	}

	if (FAS_IO.get_out_bit(m_nLfContactBwdCyl[0], IO_OFF) == IO_OFF)
	{
		m_pGridLfContact.SetItemBkColour(m_nLfBContactOut[0][1], m_nLfBContactOut[1][1], GREEN_D, BLACK_C);
	}
	else
	{
		m_pGridLfContact.SetItemBkColour(m_nLfBContactOut[0][1], m_nLfBContactOut[1][1], GREEN_C, BLACK_C);
	}
	// left to left contact 
	if (FAS_IO.get_in_bit(m_nLfContactFwdChk[0][0], IO_OFF) == IO_OFF)
	{
		m_pGridLfContact.SetItemBkColour(m_nLfBContactFwd[0][0], m_nLfBContactFwd[1][0], YELLOW_D, BLACK_C);
	}
	else
	{
		m_pGridLfContact.SetItemBkColour(m_nLfBContactFwd[0][0], m_nLfBContactFwd[1][0], YELLOW_C, BLACK_C);
	}
	// left to right
	if (FAS_IO.get_in_bit(m_nLfContactFwdChk[0][1], IO_OFF) == IO_OFF)
	{
		m_pGridLfContact.SetItemBkColour(m_nLfBContactFwd[0][1], m_nLfBContactFwd[1][1], YELLOW_D, BLACK_C);
	}
	else
	{
		m_pGridLfContact.SetItemBkColour(m_nLfBContactFwd[0][1], m_nLfBContactFwd[1][1], YELLOW_C, BLACK_C);
	}
	// left to left
	if (FAS_IO.get_in_bit(m_nLfContactBwdChk[0][0], IO_OFF) == IO_OFF)
	{
		m_pGridLfContact.SetItemBkColour(m_nLfBContactBwd[0][0], m_nLfBContactBwd[1][0], YELLOW_D, BLACK_C);
	}
	else
	{
		m_pGridLfContact.SetItemBkColour(m_nLfBContactBwd[0][0], m_nLfBContactBwd[1][0], YELLOW_C, BLACK_C);
	}
	// left to right
	if (FAS_IO.get_in_bit(m_nLfContactBwdChk[0][1], IO_OFF) == IO_OFF)
	{
		m_pGridLfContact.SetItemBkColour(m_nLfBContactBwd[0][1], m_nLfBContactBwd[1][1], YELLOW_D, BLACK_C);
	}
	else
	{
		m_pGridLfContact.SetItemBkColour(m_nLfBContactBwd[0][1], m_nLfBContactBwd[1][1], YELLOW_C, BLACK_C);
	}
	
	////top
	if (FAS_IO.get_out_bit(m_nLfContactFwdCyl[1], IO_OFF) == IO_OFF)
	{
		m_pGridLfContact.SetItemBkColour(m_nLfTContactOut[0][0], m_nLfTContactOut[1][0], GREEN_D, BLACK_C);
	}
	else
	{
		m_pGridLfContact.SetItemBkColour(m_nLfTContactOut[0][0], m_nLfTContactOut[1][0], GREEN_C, BLACK_C);
	}
	
	if (FAS_IO.get_out_bit(m_nLfContactBwdCyl[1], IO_OFF) == IO_OFF)
	{
		m_pGridLfContact.SetItemBkColour(m_nLfTContactOut[0][1], m_nLfTContactOut[1][1], GREEN_D, BLACK_C);
	}
	else
	{
		m_pGridLfContact.SetItemBkColour(m_nLfTContactOut[0][1], m_nLfTContactOut[1][1], GREEN_C, BLACK_C);
	}
	// left to left
	if (FAS_IO.get_in_bit(m_nLfContactFwdChk[1][0], IO_OFF) == IO_OFF)
	{
		m_pGridLfContact.SetItemBkColour(m_nLfTContactFwd[0][0], m_nLfTContactFwd[1][0], YELLOW_D, BLACK_C);
	}
	else
	{
		m_pGridLfContact.SetItemBkColour(m_nLfTContactFwd[0][0], m_nLfTContactFwd[1][0], YELLOW_C, BLACK_C);
	}
	// left to right
	if (FAS_IO.get_in_bit(m_nLfContactFwdChk[1][1], IO_OFF) == IO_OFF)
	{
		m_pGridLfContact.SetItemBkColour(m_nLfTContactFwd[0][1], m_nLfTContactFwd[1][1], YELLOW_D, BLACK_C);
	}
	else
	{
		m_pGridLfContact.SetItemBkColour(m_nLfTContactFwd[0][1], m_nLfTContactFwd[1][1], YELLOW_C, BLACK_C);
	}
	// 
	if (FAS_IO.get_in_bit(m_nLfContactBwdChk[1][0], IO_OFF) == IO_OFF)
	{
		m_pGridLfContact.SetItemBkColour(m_nLfTContactBwd[0][0], m_nLfTContactBwd[1][0], YELLOW_D, BLACK_C);
	}
	else
	{
		m_pGridLfContact.SetItemBkColour(m_nLfTContactBwd[0][0], m_nLfTContactBwd[1][0], YELLOW_C, BLACK_C);
	}
	
	if (FAS_IO.get_in_bit(m_nLfContactBwdChk[1][1], IO_OFF) == IO_OFF)
	{
		m_pGridLfContact.SetItemBkColour(m_nLfTContactBwd[0][1], m_nLfTContactBwd[1][1], YELLOW_D, BLACK_C);
	}
	else
	{
		m_pGridLfContact.SetItemBkColour(m_nLfTContactBwd[0][1], m_nLfTContactBwd[1][1], YELLOW_C, BLACK_C);
	}
	
	// left hifix
	if (FAS_IO.get_out_bit(m_nLfHifixFwdCyl, IO_OFF) == IO_OFF)
	{
		m_pGridLfContact.SetItemBkColour(m_nLfHifixOut[0][0], m_nLfHifixOut[1][0], GREEN_D, BLACK_C);
	}
	else
	{
		m_pGridLfContact.SetItemBkColour(m_nLfHifixOut[0][0], m_nLfHifixOut[1][0], GREEN_C, BLACK_C);
	}
	
	if (FAS_IO.get_out_bit(m_nLfHifixBwdCyl, IO_OFF) == IO_OFF)
	{
		m_pGridLfContact.SetItemBkColour(m_nLfHifixOut[0][1], m_nLfHifixOut[1][1], GREEN_D, BLACK_C);
	}
	else
	{
		m_pGridLfContact.SetItemBkColour(m_nLfHifixOut[0][1], m_nLfHifixOut[1][1], GREEN_C, BLACK_C);
	}
	
	if (FAS_IO.get_in_bit(m_nLfHifixFwdChk[0], IO_OFF) == IO_OFF)
	{
		m_pGridLfContact.SetItemBkColour(m_nLfHifixFwd[0][0], m_nLfHifixFwd[1][0], YELLOW_D, BLACK_C);
	}
	else
	{
		m_pGridLfContact.SetItemBkColour(m_nLfHifixFwd[0][0], m_nLfHifixFwd[1][0], YELLOW_C, BLACK_C);
	}
	
	if (FAS_IO.get_in_bit(m_nLfHifixBwdChk[0], IO_OFF) == IO_OFF)
	{
		m_pGridLfContact.SetItemBkColour(m_nLfHifixBwd[0][0], m_nLfHifixBwd[1][0], YELLOW_D, BLACK_C);
	}
	else
	{
		m_pGridLfContact.SetItemBkColour(m_nLfHifixBwd[0][0], m_nLfHifixBwd[1][0], YELLOW_C, BLACK_C);
	}
	
	if (FAS_IO.get_in_bit(m_nLfHifixFwdChk[1], IO_OFF) == IO_OFF)
	{
		m_pGridLfContact.SetItemBkColour(m_nLfHifixFwd[0][1], m_nLfHifixFwd[1][1], YELLOW_D, BLACK_C);
	}
	else
	{
		m_pGridLfContact.SetItemBkColour(m_nLfHifixFwd[0][1], m_nLfHifixFwd[1][1], YELLOW_C, BLACK_C);
	}
	
	if (FAS_IO.get_in_bit(m_nLfHifixBwdChk[1], IO_OFF) == IO_OFF)
	{
		m_pGridLfContact.SetItemBkColour(m_nLfHifixBwd[0][1], m_nLfHifixBwd[1][1], YELLOW_D, BLACK_C);
	}
	else
	{
		m_pGridLfContact.SetItemBkColour(m_nLfHifixBwd[0][1], m_nLfHifixBwd[1][1], YELLOW_C, BLACK_C);
	}
	
	if (FAS_IO.get_in_bit(m_nLfHifixFwdChk[2], IO_OFF) == IO_OFF)
	{
		m_pGridLfContact.SetItemBkColour(m_nLfHifixFwd[0][2], m_nLfHifixFwd[1][2], YELLOW_D, BLACK_C);
	}
	else
	{
		m_pGridLfContact.SetItemBkColour(m_nLfHifixFwd[0][2], m_nLfHifixFwd[1][2], YELLOW_C, BLACK_C);
	}
	
	if (FAS_IO.get_in_bit(m_nLfHifixBwdChk[2], IO_OFF) == IO_OFF)
	{
		m_pGridLfContact.SetItemBkColour(m_nLfHifixBwd[0][2], m_nLfHifixBwd[1][2], YELLOW_D, BLACK_C);
	}
	else
	{
		m_pGridLfContact.SetItemBkColour(m_nLfHifixBwd[0][2], m_nLfHifixBwd[1][2], YELLOW_C, BLACK_C);
	}
	
	// left mp
	if (FAS_IO.get_out_bit(m_nLfMpFwdCyl, IO_OFF) == IO_OFF)
	{
		m_pGridLfContact.SetItemBkColour(m_nLfMpOut[0][0], m_nLfMpOut[1][0], GREEN_D, BLACK_C);
	}
	else
	{
		m_pGridLfContact.SetItemBkColour(m_nLfMpOut[0][0], m_nLfMpOut[1][0], GREEN_C, BLACK_C);
	}
	
	if (FAS_IO.get_out_bit(m_nLfMpBwdCyl, IO_OFF) == IO_OFF)
	{
		m_pGridLfContact.SetItemBkColour(m_nLfMpOut[0][1], m_nLfMpOut[1][1], GREEN_D, BLACK_C);
	}
	else
	{
		m_pGridLfContact.SetItemBkColour(m_nLfMpOut[0][1], m_nLfMpOut[1][1], GREEN_C, BLACK_C);
	}
	
	if (FAS_IO.get_in_bit(m_nLfMpFwdChk[0], IO_OFF) == IO_OFF)
	{
		m_pGridLfContact.SetItemBkColour(m_nLfMpFwd[0][0], m_nLfMpFwd[1][0], YELLOW_D, BLACK_C);
	}
	else
	{
		m_pGridLfContact.SetItemBkColour(m_nLfMpFwd[0][0], m_nLfMpFwd[1][0], YELLOW_C, BLACK_C);
	}
	
	if (FAS_IO.get_in_bit(m_nLfMpFwdChk[1], IO_OFF) == IO_OFF)
	{
		m_pGridLfContact.SetItemBkColour(m_nLfMpFwd[0][1], m_nLfMpFwd[1][1], YELLOW_D, BLACK_C);
	}
	else
	{
		m_pGridLfContact.SetItemBkColour(m_nLfMpFwd[0][1], m_nLfMpFwd[1][1], YELLOW_C, BLACK_C);
	}
	
	if (FAS_IO.get_in_bit(m_nLfMpBwdChk[0], IO_OFF) == IO_OFF)
	{
		m_pGridLfContact.SetItemBkColour(m_nLfMpBwd[0][0], m_nLfMpBwd[1][0], YELLOW_D, BLACK_C);
	}
	else
	{
		m_pGridLfContact.SetItemBkColour(m_nLfMpBwd[0][0], m_nLfMpBwd[1][0], YELLOW_C, BLACK_C);
	}
	
	if (FAS_IO.get_in_bit(m_nLfMpBwdChk[1], IO_OFF) == IO_OFF)
	{
		m_pGridLfContact.SetItemBkColour(m_nLfMpBwd[0][1], m_nLfMpBwd[1][1], YELLOW_D, BLACK_C);
	}
	else
	{
		m_pGridLfContact.SetItemBkColour(m_nLfMpBwd[0][1], m_nLfMpBwd[1][1], YELLOW_C, BLACK_C);
	}
	
	m_pGridLfContact.Invalidate(FALSE);
}

void CDialogManualIO::OnDisplayRightContact()
{
	if (FAS_IO.get_out_bit(m_nRiCokCyl[0], IO_OFF) == IO_OFF)
	{
		m_pGridRiContact.SetItemBkColour(m_nRiBCokClampOut[0], m_nRiBCokClampOut[1], GREEN_D, BLACK_C);
	}
	else
	{
		m_pGridRiContact.SetItemBkColour(m_nRiBCokClampOut[0], m_nRiBCokClampOut[1], GREEN_C, BLACK_C);
	}

	if (FAS_IO.get_in_bit(m_nRiCokFwdChk[0][0], IO_OFF) == IO_OFF)
	{
		m_pGridRiContact.SetItemBkColour(m_nRiBCokClampFwd[0][0], m_nRiBCokClampFwd[1][0], YELLOW_D, BLACK_C);
	}
	else
	{
		m_pGridRiContact.SetItemBkColour(m_nRiBCokClampFwd[0][0], m_nRiBCokClampFwd[1][0], YELLOW_C, BLACK_C);
	}

	if (FAS_IO.get_in_bit(m_nRiCokFwdChk[0][1], IO_OFF) == IO_OFF)
	{
		m_pGridRiContact.SetItemBkColour(m_nRiBCokClampFwd[0][1], m_nRiBCokClampFwd[1][1], YELLOW_D, BLACK_C);
	}
	else
	{
		m_pGridRiContact.SetItemBkColour(m_nRiBCokClampFwd[0][1], m_nRiBCokClampFwd[1][1], YELLOW_C, BLACK_C);
	}
	
	if (FAS_IO.get_in_bit(m_nRiCokBwdChk[0][0], IO_OFF) == IO_OFF)
	{
		m_pGridRiContact.SetItemBkColour(m_nRiBCokClampBwd[0][0], m_nRiBCokClampBwd[1][0], YELLOW_D, BLACK_C);
	}
	else
	{
		m_pGridRiContact.SetItemBkColour(m_nRiBCokClampBwd[0][0], m_nRiBCokClampBwd[1][0], YELLOW_C, BLACK_C);
	}

	if (FAS_IO.get_in_bit(m_nRiCokBwdChk[0][1], IO_OFF) == IO_OFF)
	{
		m_pGridRiContact.SetItemBkColour(m_nRiBCokClampBwd[0][1], m_nRiBCokClampBwd[1][1], YELLOW_D, BLACK_C);
	}
	else
	{
		m_pGridRiContact.SetItemBkColour(m_nRiBCokClampBwd[0][1], m_nRiBCokClampBwd[1][1], YELLOW_C, BLACK_C);
	}
	// top
	if (FAS_IO.get_out_bit(m_nRiCokCyl[1], IO_OFF) == IO_OFF)
	{
		m_pGridRiContact.SetItemBkColour(m_nRiTCokClampOut[0], m_nRiTCokClampOut[1], GREEN_D, BLACK_C);
	}
	else
	{
		m_pGridRiContact.SetItemBkColour(m_nRiTCokClampOut[0], m_nRiTCokClampOut[1], GREEN_C, BLACK_C);
	}

	if (FAS_IO.get_in_bit(m_nRiCokFwdChk[1][0], IO_OFF) == IO_OFF)
	{
		m_pGridRiContact.SetItemBkColour(m_nRiTCokClampFwd[0][0], m_nRiTCokClampFwd[1][0], YELLOW_D, BLACK_C);
	}
	else
	{
		m_pGridRiContact.SetItemBkColour(m_nRiTCokClampFwd[0][0], m_nRiTCokClampFwd[1][0], YELLOW_C, BLACK_C);
	}
	
	if (FAS_IO.get_in_bit(m_nRiCokFwdChk[1][1], IO_OFF) == IO_OFF)
	{
		m_pGridRiContact.SetItemBkColour(m_nRiTCokClampFwd[0][1], m_nRiTCokClampFwd[1][1], YELLOW_D, BLACK_C);
	}
	else
	{
		m_pGridRiContact.SetItemBkColour(m_nRiTCokClampFwd[0][1], m_nRiTCokClampFwd[1][1], YELLOW_C, BLACK_C);
	}

	if (FAS_IO.get_in_bit(m_nRiCokBwdChk[1][0], IO_OFF) == IO_OFF)
	{
		m_pGridRiContact.SetItemBkColour(m_nRiTCokClampBwd[0][0], m_nRiTCokClampBwd[1][0], YELLOW_D, BLACK_C);
	}
	else
	{
		m_pGridRiContact.SetItemBkColour(m_nRiTCokClampBwd[0][0], m_nRiTCokClampBwd[1][0], YELLOW_C, BLACK_C);
	}

	if (FAS_IO.get_in_bit(m_nRiCokBwdChk[1][1], IO_OFF) == IO_OFF)
	{
		m_pGridRiContact.SetItemBkColour(m_nRiTCokClampBwd[0][1], m_nRiTCokClampBwd[1][1], YELLOW_D, BLACK_C);
	}
	else
	{
		m_pGridRiContact.SetItemBkColour(m_nRiTCokClampBwd[0][1], m_nRiTCokClampBwd[1][1], YELLOW_C, BLACK_C);
	}

	// left contact
	if (FAS_IO.get_out_bit(m_nRiContactFwdCyl[0], IO_OFF) == IO_OFF)
	{
		m_pGridRiContact.SetItemBkColour(m_nRiBContactOut[0][0], m_nRiBContactOut[1][0], GREEN_D, BLACK_C);
	}
	else
	{
		m_pGridRiContact.SetItemBkColour(m_nRiBContactOut[0][0], m_nRiBContactOut[1][0], GREEN_C, BLACK_C);
	}

	if (FAS_IO.get_out_bit(m_nRiContactBwdCyl[0], IO_OFF) == IO_OFF)
	{
		m_pGridRiContact.SetItemBkColour(m_nRiBContactOut[0][1], m_nRiBContactOut[1][1], GREEN_D, BLACK_C);
	}
	else
	{
		m_pGridRiContact.SetItemBkColour(m_nRiBContactOut[0][1], m_nRiBContactOut[1][1], GREEN_C, BLACK_C);
	}
	
	if (FAS_IO.get_in_bit(m_nRiContactFwdChk[0][0], IO_OFF) == IO_OFF)
	{
		m_pGridRiContact.SetItemBkColour(m_nRiBContactFwd[0][0], m_nRiBContactFwd[1][0], YELLOW_D, BLACK_C);
	}
	else
	{
		m_pGridRiContact.SetItemBkColour(m_nRiBContactFwd[0][0], m_nRiBContactFwd[1][0], YELLOW_C, BLACK_C);
	}
	
	if (FAS_IO.get_in_bit(m_nRiContactFwdChk[0][1], IO_OFF) == IO_OFF)
	{
		m_pGridRiContact.SetItemBkColour(m_nRiBContactFwd[0][1], m_nRiBContactFwd[1][1], YELLOW_D, BLACK_C);
	}
	else
	{
		m_pGridRiContact.SetItemBkColour(m_nRiBContactFwd[0][1], m_nRiBContactFwd[1][1], YELLOW_C, BLACK_C);
	}
	
	if (FAS_IO.get_in_bit(m_nRiContactBwdChk[0][0], IO_OFF) == IO_OFF)
	{
		m_pGridRiContact.SetItemBkColour(m_nRiBContactBwd[0][0], m_nRiBContactBwd[1][0], YELLOW_D, BLACK_C);
	}
	else
	{
		m_pGridRiContact.SetItemBkColour(m_nRiBContactBwd[0][0], m_nRiBContactBwd[1][0], YELLOW_C, BLACK_C);
	}
	
	if (FAS_IO.get_in_bit(m_nRiContactBwdChk[0][1], IO_OFF) == IO_OFF)
	{
		m_pGridRiContact.SetItemBkColour(m_nRiBContactBwd[0][1], m_nRiBContactBwd[1][1], YELLOW_D, BLACK_C);
	}
	else
	{
		m_pGridRiContact.SetItemBkColour(m_nRiBContactBwd[0][1], m_nRiBContactBwd[1][1], YELLOW_C, BLACK_C);
	}
	
	////top
	if (FAS_IO.get_out_bit(m_nRiContactFwdCyl[1], IO_OFF) == IO_OFF)
	{
		m_pGridRiContact.SetItemBkColour(m_nRiTContactOut[0][0], m_nRiTContactOut[1][0], GREEN_D, BLACK_C);
	}
	else
	{
		m_pGridRiContact.SetItemBkColour(m_nRiTContactOut[0][0], m_nRiTContactOut[1][0], GREEN_C, BLACK_C);
	}
	
	if (FAS_IO.get_out_bit(m_nRiContactBwdCyl[1], IO_OFF) == IO_OFF)
	{
		m_pGridRiContact.SetItemBkColour(m_nRiTContactOut[0][1], m_nRiTContactOut[1][1], GREEN_D, BLACK_C);
	}
	else
	{
		m_pGridRiContact.SetItemBkColour(m_nRiTContactOut[0][1], m_nRiTContactOut[1][1], GREEN_C, BLACK_C);
	}
	
	if (FAS_IO.get_in_bit(m_nRiContactFwdChk[1][0], IO_OFF) == IO_OFF)
	{
		m_pGridRiContact.SetItemBkColour(m_nRiTContactFwd[0][0], m_nRiTContactFwd[1][0], YELLOW_D, BLACK_C);
	}
	else
	{
		m_pGridRiContact.SetItemBkColour(m_nRiTContactFwd[0][0], m_nRiTContactFwd[1][0], YELLOW_C, BLACK_C);
	}
	
	if (FAS_IO.get_in_bit(m_nRiContactFwdChk[1][1], IO_OFF) == IO_OFF)
	{
		m_pGridRiContact.SetItemBkColour(m_nRiTContactFwd[0][1], m_nRiTContactFwd[1][1], YELLOW_D, BLACK_C);
	}
	else
	{
		m_pGridRiContact.SetItemBkColour(m_nRiTContactFwd[0][1], m_nRiTContactFwd[1][1], YELLOW_C, BLACK_C);
	}
	
	if (FAS_IO.get_in_bit(m_nRiContactBwdChk[1][0], IO_OFF) == IO_OFF)
	{
		m_pGridRiContact.SetItemBkColour(m_nRiTContactBwd[0][0], m_nRiTContactBwd[1][0], YELLOW_D, BLACK_C);
	}
	else
	{
		m_pGridRiContact.SetItemBkColour(m_nRiTContactBwd[0][0], m_nRiTContactBwd[1][0], YELLOW_C, BLACK_C);
	}
	
	if (FAS_IO.get_in_bit(m_nRiContactBwdChk[1][1], IO_OFF) == IO_OFF)
	{
		m_pGridRiContact.SetItemBkColour(m_nRiTContactBwd[0][1], m_nRiTContactBwd[1][1], YELLOW_D, BLACK_C);
	}
	else
	{
		m_pGridRiContact.SetItemBkColour(m_nRiTContactBwd[0][1], m_nRiTContactBwd[1][1], YELLOW_C, BLACK_C);
	}
	
	// left hifix
	if (FAS_IO.get_out_bit(m_nRiHifixFwdCyl, IO_OFF) == IO_OFF)
	{
		m_pGridRiContact.SetItemBkColour(m_nRiHifixOut[0][0], m_nRiHifixOut[1][0], GREEN_D, BLACK_C);
	}
	else
	{
		m_pGridRiContact.SetItemBkColour(m_nRiHifixOut[0][0], m_nRiHifixOut[1][0], GREEN_C, BLACK_C);
	}
	
	if (FAS_IO.get_out_bit(m_nRiHifixBwdCyl, IO_OFF) == IO_OFF)
	{
		m_pGridRiContact.SetItemBkColour(m_nRiHifixOut[0][1], m_nRiHifixOut[1][1], GREEN_D, BLACK_C);
	}
	else
	{
		m_pGridRiContact.SetItemBkColour(m_nRiHifixOut[0][1], m_nRiHifixOut[1][1], GREEN_C, BLACK_C);
	}
	
	if (FAS_IO.get_in_bit(m_nRiHifixFwdChk[0], IO_OFF) == IO_OFF)
	{
		m_pGridRiContact.SetItemBkColour(m_nRiHifixFwd[0][0], m_nRiHifixFwd[1][0], YELLOW_D, BLACK_C);
	}
	else
	{
		m_pGridRiContact.SetItemBkColour(m_nRiHifixFwd[0][0], m_nRiHifixFwd[1][0], YELLOW_C, BLACK_C);
	}
	
	if (FAS_IO.get_in_bit(m_nRiHifixBwdChk[0], IO_OFF) == IO_OFF)
	{
		m_pGridRiContact.SetItemBkColour(m_nRiHifixBwd[0][0], m_nRiHifixBwd[1][0], YELLOW_D, BLACK_C);
	}
	else
	{
		m_pGridRiContact.SetItemBkColour(m_nRiHifixBwd[0][0], m_nRiHifixBwd[1][0], YELLOW_C, BLACK_C);
	}
	
	if (FAS_IO.get_in_bit(m_nRiHifixFwdChk[1], IO_OFF) == IO_OFF)
	{
		m_pGridRiContact.SetItemBkColour(m_nRiHifixFwd[0][1], m_nRiHifixFwd[1][1], YELLOW_D, BLACK_C);
	}
	else
	{
		m_pGridRiContact.SetItemBkColour(m_nRiHifixFwd[0][1], m_nRiHifixFwd[1][1], YELLOW_C, BLACK_C);
	}
	
	if (FAS_IO.get_in_bit(m_nRiHifixBwdChk[1], IO_OFF) == IO_OFF)
	{
		m_pGridRiContact.SetItemBkColour(m_nRiHifixBwd[0][1], m_nRiHifixBwd[1][1], YELLOW_D, BLACK_C);
	}
	else
	{
		m_pGridRiContact.SetItemBkColour(m_nRiHifixBwd[0][1], m_nRiHifixBwd[1][1], YELLOW_C, BLACK_C);
	}
	
	if (FAS_IO.get_in_bit(m_nRiHifixFwdChk[2], IO_OFF) == IO_OFF)
	{
		m_pGridRiContact.SetItemBkColour(m_nRiHifixFwd[0][2], m_nRiHifixFwd[1][2], YELLOW_D, BLACK_C);
	}
	else
	{
		m_pGridRiContact.SetItemBkColour(m_nRiHifixFwd[0][2], m_nRiHifixFwd[1][2], YELLOW_C, BLACK_C);
	}
	
	if (FAS_IO.get_in_bit(m_nRiHifixBwdChk[2], IO_OFF) == IO_OFF)
	{
		m_pGridRiContact.SetItemBkColour(m_nRiHifixBwd[0][2], m_nRiHifixBwd[1][2], YELLOW_D, BLACK_C);
	}
	else
	{
		m_pGridRiContact.SetItemBkColour(m_nRiHifixBwd[0][2], m_nRiHifixBwd[1][2], YELLOW_C, BLACK_C);
	}
	
	// left mp
	if (FAS_IO.get_out_bit(m_nRiMpFwdCyl, IO_OFF) == IO_OFF)
	{
		m_pGridRiContact.SetItemBkColour(m_nRiMpOut[0][0], m_nRiMpOut[1][0], GREEN_D, BLACK_C);
	}
	else
	{
		m_pGridRiContact.SetItemBkColour(m_nRiMpOut[0][0], m_nRiMpOut[1][0], GREEN_C, BLACK_C);
	}
	
	if (FAS_IO.get_out_bit(m_nRiMpBwdCyl, IO_OFF) == IO_OFF)
	{
		m_pGridRiContact.SetItemBkColour(m_nRiMpOut[0][1], m_nRiMpOut[1][1], GREEN_D, BLACK_C);
	}
	else
	{
		m_pGridRiContact.SetItemBkColour(m_nRiMpOut[0][1], m_nRiMpOut[1][1], GREEN_C, BLACK_C);
	}
	
	if (FAS_IO.get_in_bit(m_nRiMpFwdChk[0], IO_OFF) == IO_OFF)
	{
		m_pGridRiContact.SetItemBkColour(m_nRiMpFwd[0][0], m_nRiMpFwd[1][0], YELLOW_D, BLACK_C);
	}
	else
	{
		m_pGridRiContact.SetItemBkColour(m_nRiMpFwd[0][0], m_nRiMpFwd[1][0], YELLOW_C, BLACK_C);
	}
	
	if (FAS_IO.get_in_bit(m_nRiMpFwdChk[1], IO_OFF) == IO_OFF)
	{
		m_pGridRiContact.SetItemBkColour(m_nRiMpFwd[0][1], m_nRiMpFwd[1][1], YELLOW_D, BLACK_C);
	}
	else
	{
		m_pGridRiContact.SetItemBkColour(m_nRiMpFwd[0][1], m_nRiMpFwd[1][1], YELLOW_C, BLACK_C);
	}
	
	if (FAS_IO.get_in_bit(m_nRiMpBwdChk[0], IO_OFF) == IO_OFF)
	{
		m_pGridRiContact.SetItemBkColour(m_nRiMpBwd[0][0], m_nRiMpBwd[1][0], YELLOW_D, BLACK_C);
	}
	else
	{
		m_pGridRiContact.SetItemBkColour(m_nRiMpBwd[0][0], m_nRiMpBwd[1][0], YELLOW_C, BLACK_C);
	}
	
	if (FAS_IO.get_in_bit(m_nRiMpBwdChk[1], IO_OFF) == IO_OFF)
	{
		m_pGridRiContact.SetItemBkColour(m_nRiMpBwd[0][1], m_nRiMpBwd[1][1], YELLOW_D, BLACK_C);
	}
	else
	{
		m_pGridRiContact.SetItemBkColour(m_nRiMpBwd[0][1], m_nRiMpBwd[1][1], YELLOW_C, BLACK_C);
	}
	
	m_pGridRiContact.Invalidate(FALSE);
}

void CDialogManualIO::OnDisplayBuffer()
{
	// retest move
	if (FAS_IO.get_out_bit(m_nRetestMvFwdCyl, IO_OFF) == IO_OFF)
	{
		m_pGridBuf.SetItemBkColour(m_nRetestMvFwdOut[0], m_nRetestMvFwdOut[1], GREEN_D, BLACK_C);
	}
	else
	{
		m_pGridBuf.SetItemBkColour(m_nRetestMvFwdOut[0], m_nRetestMvFwdOut[1], GREEN_C, BLACK_C);
	}

	if (FAS_IO.get_out_bit(m_nRetestMvBwdCyl, IO_OFF) == IO_OFF)
	{
		m_pGridBuf.SetItemBkColour(m_nRetestMvBwdOut[0], m_nRetestMvBwdOut[1], GREEN_D, BLACK_C);
	}
	else
	{
		m_pGridBuf.SetItemBkColour(m_nRetestMvBwdOut[0], m_nRetestMvBwdOut[1], GREEN_C, BLACK_C);
	}

	if (FAS_IO.get_in_bit(m_nRetestMvFwdChk, IO_OFF) == IO_OFF)
	{
		m_pGridBuf.SetItemBkColour(m_nRetestMvFwd[0], m_nRetestMvFwd[1], YELLOW_D, BLACK_C);
	}
	else
	{
		m_pGridBuf.SetItemBkColour(m_nRetestMvFwd[0], m_nRetestMvFwd[1], YELLOW_C, BLACK_C);
	}

	if (FAS_IO.get_in_bit(m_nRetestMvBwdChk, IO_OFF) == IO_OFF)
	{
		m_pGridBuf.SetItemBkColour(m_nRetestMvBwd[0], m_nRetestMvBwd[1], YELLOW_D, BLACK_C);
	}
	else
	{
		m_pGridBuf.SetItemBkColour(m_nRetestMvBwd[0], m_nRetestMvBwd[1], YELLOW_C, BLACK_C);
	}
	
	// retest align
	if (FAS_IO.get_out_bit(m_nRetestAlignCyl, IO_OFF) == IO_OFF)
	{
		m_pGridBuf.SetItemBkColour(m_nRetestAlignOut[0], m_nRetestAlignOut[1], GREEN_D, BLACK_C);
	}
	else
	{
		m_pGridBuf.SetItemBkColour(m_nRetestAlignOut[0], m_nRetestAlignOut[1], GREEN_C, BLACK_C);
	}

	if (FAS_IO.get_in_bit(m_nRetestAlignFwdChk, IO_OFF) == IO_OFF)
	{
		m_pGridBuf.SetItemBkColour(m_nRetestAlignFwd[0], m_nRetestAlignFwd[1], YELLOW_D, BLACK_C);
	}
	else
	{
		m_pGridBuf.SetItemBkColour(m_nRetestAlignFwd[0], m_nRetestAlignFwd[1], YELLOW_C, BLACK_C);
	}

	if (FAS_IO.get_in_bit(m_nRetestAlignBwdChk, IO_OFF) == IO_OFF)
	{
		m_pGridBuf.SetItemBkColour(m_nRetestAlignBwd[0], m_nRetestAlignBwd[1], YELLOW_D, BLACK_C);
	}
	else
	{
		m_pGridBuf.SetItemBkColour(m_nRetestAlignBwd[0], m_nRetestAlignBwd[1], YELLOW_C, BLACK_C);
	}

	// reject clamp
	if (FAS_IO.get_out_bit(m_nRejectClampCyl, IO_OFF) == IO_OFF)
	{
		m_pGridBuf.SetItemBkColour(m_nRejectClampOut[0], m_nRejectClampOut[1], GREEN_D, BLACK_C);
	}
	else
	{
		m_pGridBuf.SetItemBkColour(m_nRejectClampOut[0], m_nRejectClampOut[1], GREEN_C, BLACK_C);
	}

	if (FAS_IO.get_in_bit(m_nRejectClampFwdChk, IO_OFF) == IO_OFF)
	{
		m_pGridBuf.SetItemBkColour(m_nRejectClampFwd[0], m_nRejectClampFwd[1], YELLOW_D, BLACK_C);
	}
	else
	{
		m_pGridBuf.SetItemBkColour(m_nRejectClampFwd[0], m_nRejectClampFwd[1], YELLOW_C, BLACK_C);
	}

	if (FAS_IO.get_in_bit(m_nRejectClampBwdChk, IO_OFF) == IO_OFF)
	{
		m_pGridBuf.SetItemBkColour(m_nRejectClampBwd[0], m_nRejectClampBwd[1], YELLOW_D, BLACK_C);
	}
	else
	{
		m_pGridBuf.SetItemBkColour(m_nRejectClampBwd[0], m_nRejectClampBwd[1], YELLOW_C, BLACK_C);
	}

	// reject up/dn
	if (FAS_IO.get_out_bit(m_nRejectUpDnCyl, IO_OFF) == IO_OFF)
	{
		m_pGridBuf.SetItemBkColour(m_nRejectUpDnOut[0], m_nRejectUpDnOut[1], GREEN_D, BLACK_C);
	}
	else
	{
		m_pGridBuf.SetItemBkColour(m_nRejectUpDnOut[0], m_nRejectUpDnOut[1], GREEN_C, BLACK_C);
	}

	if (FAS_IO.get_in_bit(m_nRejectUpChk, IO_OFF) == IO_OFF)
	{
		m_pGridBuf.SetItemBkColour(m_nRejectUp[0], m_nRejectUp[1], YELLOW_D, BLACK_C);
	}
	else
	{
		m_pGridBuf.SetItemBkColour(m_nRejectUp[0], m_nRejectUp[1], YELLOW_C, BLACK_C);
	}

	if (FAS_IO.get_in_bit(m_nRejectDnChk, IO_OFF) == IO_OFF)
	{
		m_pGridBuf.SetItemBkColour(m_nRejectDn[0], m_nRejectDn[1], YELLOW_D, BLACK_C);
	}
	else
	{
		m_pGridBuf.SetItemBkColour(m_nRejectDn[0], m_nRejectDn[1], YELLOW_C, BLACK_C);
	}

	// rejectmove
	if (FAS_IO.get_out_bit(m_nRejectMvFwdCyl, IO_OFF) == IO_OFF)
	{
		m_pGridBuf.SetItemBkColour(m_nRejectMvFwdOut[0], m_nRejectMvFwdOut[1], GREEN_D, BLACK_C);
	}
	else
	{
		m_pGridBuf.SetItemBkColour(m_nRejectMvFwdOut[0], m_nRejectMvFwdOut[1], GREEN_C, BLACK_C);
	}

	if (FAS_IO.get_out_bit(m_nRejectMvBwdCyl, IO_OFF) == IO_OFF)
	{
		m_pGridBuf.SetItemBkColour(m_nRejectMvBwdOut[0], m_nRejectMvBwdOut[1], GREEN_D, BLACK_C);
	}
	else
	{
		m_pGridBuf.SetItemBkColour(m_nRejectMvBwdOut[0], m_nRejectMvBwdOut[1], GREEN_C, BLACK_C);
	}

	if (FAS_IO.get_in_bit(m_nRejectMvFwdChk, IO_OFF) == IO_OFF)
	{
		m_pGridBuf.SetItemBkColour(m_nRejectMvFwd[0], m_nRejectMvFwd[1], YELLOW_D, BLACK_C);
	}
	else
	{
		m_pGridBuf.SetItemBkColour(m_nRejectMvFwd[0], m_nRejectMvFwd[1], YELLOW_C, BLACK_C);
	}

	if (FAS_IO.get_in_bit(m_nRejectMvBwdChk, IO_OFF) == IO_OFF)
	{
		m_pGridBuf.SetItemBkColour(m_nRejectMvBwd[0], m_nRejectMvBwd[1], YELLOW_D, BLACK_C);
	}
	else
	{
		m_pGridBuf.SetItemBkColour(m_nRejectMvBwd[0], m_nRejectMvBwd[1], YELLOW_C, BLACK_C);
	}

	m_pGridBuf.Invalidate(FALSE);
}

void CDialogManualIO::OnBnClickedBtnRefresh()
{
	// TODO: 여기에 컨트롤 알림 처리기 코드를 추가합니다.
	if (st_handler_info.nRunStatus != dSTOP) return;

	CDialog_Message dlgMsg;
}


void CDialogManualIO::OnBnClickedBtnLeftClamp()
{
	// TODO: 여기에 컨트롤 알림 처리기 코드를 추가합니다.
	if (st_handler_info.nMenuLock != FALSE) return;
	st_handler_info.nMenuLock = TRUE;
}


void CDialogManualIO::OnBnClickedBtnLeftUnclamp()
{
	// TODO: 여기에 컨트롤 알림 처리기 코드를 추가합니다.
	if (st_handler_info.nMenuLock != FALSE) return;
	st_handler_info.nMenuLock = TRUE;
}


void CDialogManualIO::OnBnClickedBtnRightClamp()
{
	// TODO: 여기에 컨트롤 알림 처리기 코드를 추가합니다.
	if (st_handler_info.nMenuLock != FALSE) return;
	st_handler_info.nMenuLock = TRUE;
}


void CDialogManualIO::OnBnClickedBtnRightUnclamp()
{
	// TODO: 여기에 컨트롤 알림 처리기 코드를 추가합니다.
	if (st_handler_info.nMenuLock != FALSE) return;
	st_handler_info.nMenuLock = TRUE;
}
