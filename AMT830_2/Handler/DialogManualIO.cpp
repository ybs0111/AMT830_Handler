// DialogManualIO.cpp : ���� �����Դϴ�.
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

// CDialogManualIO ��ȭ �����Դϴ�.
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


// CDialogManualIO �޽��� ó�����Դϴ�.

BOOL CDialogManualIO::Create()
{
	return CDialog::Create( CDialogManualIO::IDD );
}

BOOL CDialogManualIO::OnEraseBkgnd(CDC* pDC)
{
	// TODO: ���⿡ �޽��� ó���� �ڵ带 �߰� ��/�Ǵ� �⺻���� ȣ���մϴ�.
	CDC  memDC;                     // �޸� DC
	CBitmap * pOldBitmap = NULL;    // m_BackBitmap���� ���ο� �׸��� DC�� �׸� ��, ���� �׷����� DC(��, Bitmap)�� ����.
	BITMAP bitmapInfo;              // �׸��� ����(m_BackBitmap)
	m_bmGround.GetBitmap(&bitmapInfo); // Bitmap ũ�� ����.

	memDC.CreateCompatibleDC(pDC);  // �޸� DC ����
	pOldBitmap = memDC.SelectObject(&m_bmGround);
	pDC->BitBlt(0, 0, bitmapInfo.bmWidth, bitmapInfo.bmHeight, &memDC, 0, 0, SRCCOPY);   // �޸� DC�� �׸��� �׸�

	memDC.SelectObject(pOldBitmap);
	memDC.DeleteDC();

//	return CFormView::OnEraseBkgnd(pDC);
	return true;
}


BOOL CDialogManualIO::DestroyWindow()
{
	// TODO: ���⿡ Ư��ȭ�� �ڵ带 �߰� ��/�Ǵ� �⺻ Ŭ������ ȣ���մϴ�.
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

	// TODO:  ���⿡ �߰� �ʱ�ȭ �۾��� �߰��մϴ�.
	OnInitButton();
	SetTimer(100, 500, NULL);
	SetTimer(200, 500, NULL);
	SetTimer(300, 500, NULL);
	SetTimer(400, 500, NULL);
	SetTimer(500, 500, NULL);
	SetTimer(600, 500, NULL);
	SetTimer(700, 500, NULL);
	return TRUE;  // return TRUE unless you set the focus to a control
	// ����: OCX �Ӽ� �������� FALSE�� ��ȯ�ؾ� �մϴ�.
}


void CDialogManualIO::OnTimer(UINT_PTR nIDEvent)
{
	// TODO: ���⿡ �޽��� ó���� �ڵ带 �߰� ��/�Ǵ� �⺻���� ȣ���մϴ�.

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
	// TODO: ���⿡ ��Ʈ�� �˸� ó���� �ڵ带 �߰��մϴ�.
//	CDialog::OnOK();
	if (st_handler_info.cWndMotor != NULL)
	{
		st_handler_info.cWndMotor->SendMessage(WM_WORK_COMMAND, MOTOR_IO_DELETE_REQ, 0);
	}
}






void CDialogManualIO::OnBnClickedBtnRefresh()
{
	// TODO: ���⿡ ��Ʈ�� �˸� ó���� �ڵ带 �߰��մϴ�.
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
