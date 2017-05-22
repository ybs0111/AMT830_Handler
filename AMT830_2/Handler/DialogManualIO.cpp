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
	DDX_Control(pDX, IDC_BTN_EXIT,						m_btnExit);
	DDX_Control(pDX, IDC_BTN_REFRESH,					m_btnDoor);
}


BEGIN_MESSAGE_MAP(CDialogManualIO, CDialog)
	ON_WM_ERASEBKGND()
	ON_WM_TIMER()
	ON_BN_CLICKED(IDC_BTN_EXIT,		&CDialogManualIO::OnBnClickedBtnExit)
	ON_BN_CLICKED(IDC_BTN_REFRESH, &CDialogManualIO::OnBnClickedBtnRefresh)
	
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
	SetTimer(100, 500, NULL);
	SetTimer(200, 500, NULL);
	SetTimer(300, 500, NULL);
	SetTimer(400, 500, NULL);
	SetTimer(500, 500, NULL);
	SetTimer(600, 500, NULL);
	SetTimer(700, 500, NULL);
	return TRUE;  // return TRUE unless you set the focus to a control
	// 예외: OCX 속성 페이지는 FALSE를 반환해야 합니다.
}


void CDialogManualIO::OnTimer(UINT_PTR nIDEvent)
{
	// TODO: 여기에 메시지 처리기 코드를 추가 및/또는 기본값을 호출합니다.
	switch (nIDEvent)
	{

	default:
		break;
	}
	
	CDialog::OnTimer(nIDEvent);
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

	m_btnDoor.SetBitmaps(IDC_BTN_REFRESH, IDB_BITMAP_DOOR_OPEN, WINDOW_DN, IDB_BITMAP_DOOR_OPEN, WINDOW_UP);
	m_btnDoor.SetColor(CButtonST::BTNST_COLOR_BK_IN, WINDOW_DN);
	m_btnDoor.SetColor(CButtonST::BTNST_COLOR_BK_OUT, WINDOW_UP);
	m_btnDoor.SetColor(CButtonST::BTNST_COLOR_BK_FOCUS, WINDOW_UP);
	m_btnDoor.SetColor(CButtonST::BTNST_COLOR_FG_IN, BLACK_C);
	m_btnDoor.SetColor(CButtonST::BTNST_COLOR_FG_OUT, BLUE_C);
	m_btnDoor.SetColor(CButtonST::BTNST_COLOR_FG_FOCUS, BLUE_C);
	m_btnDoor.SetFont(clsFunc.m_pFont[3]);
	m_btnDoor.SetTooltipText(_T("Door Open"));

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






void CDialogManualIO::OnBnClickedBtnRefresh()
{
	// TODO: 여기에 컨트롤 알림 처리기 코드를 추가합니다.
	if (st_handler_info.nRunStatus != dSTOP) return;

	CDialog_Message dlgMsg;

	//if (FAS_IO.get_in_bit(st_io_info.i_FrontSelectSwChk, IO_ON) == IO_OFF ||
	//	FAS_IO.get_in_bit(st_io_info.i_RearSelectSwChk, IO_ON)	== IO_OFF)
	if (FAS_IO.get_in_bit(st_io_info.i_ManualModeChk, IO_OFF) == IO_ON)
	{
		FAS_IO.set_out_bit(st_io_info.o_DoorLock, IO_OFF);
	}
	else
	{
		dlgMsg.m_nMessageType	= 0;
		dlgMsg.m_strMessage		= _T("Manual Key Status Check");

		dlgMsg.DoModal();
	}
}
