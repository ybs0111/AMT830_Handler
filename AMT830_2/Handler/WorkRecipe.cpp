﻿// WorkRecipe.cpp : 구현 파일입니다.
//

#include "stdafx.h"
#include "Handler.h"
#include "WorkRecipe.h"
#include "afxdialogex.h"
#include "Dialog_KeyBoard.h"
#include "Dialog_KeyPad.h"
#include "Dialog_Message.h"
#include "PublicFunction.h"
#include "CtlBd_Variable.h"
#include "Dialog_Message.h"
#include "XgemClient.h"
#include ".\\Ctrl\\KeyBoard.h"

// CWorkRecipe 대화 상자입니다.
#define TM_INTERFACE	100

IMPLEMENT_DYNAMIC(CWorkRecipe, CDialog)

CWorkRecipe::CWorkRecipe(CWnd* pParent /*=NULL*/)
	: CDialog(CWorkRecipe::IDD, pParent)
{
	
}

CWorkRecipe::~CWorkRecipe()
{
}

void CWorkRecipe::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_BTN_APPLY,							m_btnApply);
	DDX_Control(pDX, IDC_BTN_RELOAD,						m_btnReLoad);
	DDX_Control(pDX, IDC_GROUP_TRAY_SIZE_SETTING, m_group_Tray_Size_Setting);
	DDX_Control(pDX, IDC_MSG_TRAY_X, m_msg_Tray_Size_x);
	DDX_Control(pDX, IDC_MSG_TRAY_Y, m_msg_Tray_Size_y);
	DDX_Control(pDX, IDC_DGT_TRAY_X, m_dgt_Tray_Size_x);
	DDX_Control(pDX, IDC_DGT_TRAY_Y, m_dgt_Tray_Size_y);
}


BEGIN_MESSAGE_MAP(CWorkRecipe, CDialog)
	ON_WM_ERASEBKGND()
	ON_BN_CLICKED(IDC_BTN_APPLY,							&CWorkRecipe::OnBnClickedBtnApply)
	ON_BN_CLICKED(IDC_BTN_RELOAD,							&CWorkRecipe::OnBnClickedBtnReload)
	ON_WM_DESTROY()
	ON_WM_TIMER()

	ON_STN_CLICKED(IDC_DGT_TRAY_X, &CWorkRecipe::OnStnClickedDgtTrayX)
	ON_STN_CLICKED(IDC_DGT_TRAY_Y, &CWorkRecipe::OnStnClickedDgtTrayY)
END_MESSAGE_MAP()


// CWorkRecipe 메시지 처리기입니다.


BOOL CWorkRecipe::DestroyWindow()
{
	// TODO: 여기에 특수화된 코드를 추가 및/또는 기본 클래스를 호출합니다.
/*	if (OnDataComparison() == RET_ERROR)
	{
		OnDataHistoryLog();
		OnDataApply();
	}*/
	return CDialog::DestroyWindow();
}


BOOL CWorkRecipe::OnInitDialog()
{
	CDialog::OnInitDialog();

	// TODO:  여기에 추가 초기화 작업을 추가합니다.
	OnDataInit();
	OnInitGroupBox();
	OnInitLabel();
	OnInitButton();
	OnInitDigit();
	OnDataDisplay();

	return TRUE;  // return TRUE unless you set the focus to a control
	// 예외: OCX 속성 페이지는 FALSE를 반환해야 합니다.
}

void CWorkRecipe::OnInitGroupBox()
{
	m_group_Tray_Size_Setting.SetFont(clsFunc.OnLogFont(16));
	m_group_Tray_Size_Setting.SetCatptionTextColor(BLUE_C);
	m_group_Tray_Size_Setting.SetBorderColor(ORANGE_C);
	m_group_Tray_Size_Setting.SetFontBold(TRUE);
	m_group_Tray_Size_Setting.SetBackgroundColor(WINDOW_UP);
}

void CWorkRecipe::OnInitLabel()
{
	m_msg_Tray_Size_x.SetFont(clsFunc.m_pFont[2]);
	m_msg_Tray_Size_x.SetWindowText(_T("X"));
	m_msg_Tray_Size_x.SetCenterText();
	m_msg_Tray_Size_x.SetColor(WHITE_C);
	m_msg_Tray_Size_x.SetGradientColor(GREEN_C);
	m_msg_Tray_Size_x.SetTextColor(BLACK_C);

	m_msg_Tray_Size_y.SetFont(clsFunc.m_pFont[2]);
	m_msg_Tray_Size_y.SetWindowText(_T("Y"));
	m_msg_Tray_Size_y.SetCenterText();
	m_msg_Tray_Size_y.SetColor(WHITE_C);
	m_msg_Tray_Size_y.SetGradientColor(GREEN_C);
	m_msg_Tray_Size_y.SetTextColor(BLACK_C);

	
}

void CWorkRecipe::OnInitDigit()
{
	m_dgt_Tray_Size_x.SetStyle(CDigit::DS_INT, 3, CDigit::DC_BGREEN, CDigit::DC_BDISABLE);
	m_dgt_Tray_Size_x.SetVal(m_nTraySize_X[1]);

	m_dgt_Tray_Size_y.SetStyle(CDigit::DS_INT, 3, CDigit::DC_BGREEN, CDigit::DC_BDISABLE);
	m_dgt_Tray_Size_y.SetVal(m_nTraySize_Y[1]);
}


void CWorkRecipe::OnInitButton()
{
	m_btnApply.SetBitmaps(IDC_BTN_APPLY, IDB_BITMAP_APPLY_DN1, WINDOW_DN1, IDB_BITMAP_APPLY_UP1, WINDOW_UP1);
	m_btnApply.SetColor(CButtonST::BTNST_COLOR_BK_IN, WINDOW_DN1);
	m_btnApply.SetColor(CButtonST::BTNST_COLOR_BK_OUT, WINDOW_UP1);
	m_btnApply.SetColor(CButtonST::BTNST_COLOR_BK_FOCUS, WINDOW_UP1);
	m_btnApply.SetColor(CButtonST::BTNST_COLOR_FG_IN, BLACK_C);
	m_btnApply.SetColor(CButtonST::BTNST_COLOR_FG_OUT, BLUE_C);
	m_btnApply.SetFont(clsFunc.m_pFont[2]);
	m_btnApply.SetTooltipText(_T("Recipe Data Apply"));

	m_btnReLoad.SetBitmaps(IDC_BTN_RELOAD, IDB_BITMAP_RELOAD_DN1, WINDOW_DN1, IDB_BITMAP_RELOAD_UP1, WINDOW_UP1);
	m_btnReLoad.SetColor(CButtonST::BTNST_COLOR_BK_IN, WINDOW_DN1);
	m_btnReLoad.SetColor(CButtonST::BTNST_COLOR_BK_OUT, WINDOW_UP1);
	m_btnReLoad.SetColor(CButtonST::BTNST_COLOR_BK_FOCUS, WINDOW_UP1);
	m_btnReLoad.SetColor(CButtonST::BTNST_COLOR_FG_IN, BLACK_C);
	m_btnReLoad.SetColor(CButtonST::BTNST_COLOR_FG_OUT, BLUE_C);
	m_btnReLoad.SetFont(clsFunc.m_pFont[2]);
	m_btnReLoad.SetTooltipText(_T("Recipe Data ReLoad"));
}


void CWorkRecipe::OnDataHistoryLog()
{	
	
}


void CWorkRecipe::OnDataRecovery()
{
	
}


int CWorkRecipe::OnDataComparison()
{


	return RET_GOOD;
}


void CWorkRecipe::OnDataApply()
{
	
}


void CWorkRecipe::OnDataBackup()
{

}


void CWorkRecipe::OnDataInit()
{

	OnDataBackup();  // 현재 클래스 변수 설정 상태 백업
}


BOOL CWorkRecipe::OnEraseBkgnd(CDC* pDC)
{
	CDC  memDC;                     // 메모리 DC
	CBitmap * pOldBitmap = NULL;    // m_BackBitmap으로 새로운 그림을 DC에 그릴 때, 이전 그려졌던 DC(즉, Bitmap)을 저장.
	BITMAP bitmapInfo;              // 그림의 정보(m_BackBitmap)
	st_handler_info.m_BackDlgBitmap.GetBitmap(&bitmapInfo); // Bitmap 크기 구함.

	memDC.CreateCompatibleDC(pDC);  // 메모리 DC 생성
	pOldBitmap = memDC.SelectObject(&st_handler_info.m_BackDlgBitmap);
	pDC->BitBlt(0, 0, bitmapInfo.bmWidth, bitmapInfo.bmHeight, &memDC, 0, 0, SRCCOPY);   // 메모리 DC에 그림을 그림

	memDC.SelectObject(pOldBitmap);
	memDC.DeleteDC();

	return true; // 흰 부러쉬가 아닌 배경을 그려야 하기 때문에 true
}


void CWorkRecipe::OnBnClickedBtnApply()
{
	CDialog_Message dlgMsg;
	int nResponse;

	dlgMsg.m_nMessageType	= 1;
	dlgMsg.m_strMessage		= _T("Do you want to change the existing value to the current value?");

	nResponse = (int)dlgMsg.DoModal();

	if (nResponse == IDOK)
	{
		if (OnDataComparison() == RET_ERROR)
		{
			OnDataHistoryLog();
			OnDataApply();
			OnDataBackup();  // 현재 클래스 변수 설정 상태 백업
		}
	}
}


void CWorkRecipe::OnBnClickedBtnReload()
{
	OnDataBackup();  // 현재 클래스 변수 설정 상태 백업
}


void CWorkRecipe::OnDataDisplay()
{
	
}


void CWorkRecipe::PostNcDestroy()
{
	// TODO: 여기에 특수화된 코드를 추가 및/또는 기본 클래스를 호출합니다.
	if (OnDataComparison() == RET_ERROR)
	{
		OnDataHistoryLog();
		OnDataApply();
	}
	CDialog::PostNcDestroy();
}


void CWorkRecipe::OnDestroy()
{
	CDialog::OnDestroy();

	// TODO: 여기에 메시지 처리기 코드를 추가합니다.
	if (OnDataComparison() == RET_ERROR)
	{
		OnDataHistoryLog();
		OnDataApply();
	}
}

void CWorkRecipe::OnTimer(UINT_PTR nIDEvent)
{
	// TODO: 여기에 메시지 처리기 코드를 추가 및/또는 기본값을 호출합니다.
	
	
	CDialog::OnTimer(nIDEvent);
}





void CWorkRecipe::OnStnClickedDgtTrayX()
{
	int nKey = m_nTraySize_X[1];

	KeyPadI(1, 100, &nKey);

	m_nTraySize_X[1] = nKey;
	m_dgt_Tray_Size_x.SetVal(nKey);
}


void CWorkRecipe::OnStnClickedDgtTrayY()
{
	int nKey = m_nTraySize_Y[1];

	KeyPadI(1, 100, &nKey);

	m_nTraySize_Y[1] = nKey;
	m_dgt_Tray_Size_y.SetVal(nKey);
}
