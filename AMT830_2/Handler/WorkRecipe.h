#pragma once


// CWorkRecipe 대화 상자입니다.
#include "Variable.h"
#include "xShadeButton.h"	// 조그 버튼 생성 클래스 추가
#include "XPGroupBox.h"
#include ".\\Union\\Grid\\GridCtrl.h"
#include ".\\Union\\Grid\\GridURLCell.h"
#include ".\\Union\\Grid\\GridCellCombo.h"
#include ".\\Union\\Grid\\GridCellCheck.h"
#include ".\\Union\\Grid\\GridCellNumeric.h"
#include ".\\Union\\Grid\\GridCellDateTime.h"
#include "GradientStatic.h"  
#include "Digit.h"
#include "BtnST.h"

class CDialogSocketComment;		//SOCKET COMMENT 2015.08.04
class CWorkRecipe : public CDialog
{
	DECLARE_DYNAMIC(CWorkRecipe)

public:
	

	CButtonST			m_btnApply;
	CButtonST			m_btnReLoad;
	//kwlee 22017.0523
	CXPGroupBox			m_group_Picker_Gap;
	CXPGroupBox			m_group_Tray_Size_Setting;

	CGradientStatic		m_msg_Tray_Size_x;
	CGradientStatic		m_msg_Tray_Size_y;
	
	CGradientStatic		m_msg_Picker_gap_Module_Load;
	CGradientStatic		m_msg_Picker_gap_HeatSink_Left;
	CGradientStatic		m_msg_Picker_gap_HeatSink_Right;
	
	CDigit				m_dgt_Picker_gap_Module_load;
	CDigit				m_dgt_Picker_gap_HeatSink_Left;
	CDigit				m_dgt_Picker_gap_HeatSink_Right;

	CDigit				m_dgt_Tray_Size_x;
	CDigit				m_dgt_Tray_Size_y;

	double				m_dPicker_Gap_Module_Load[2];
	double				m_dPicker_Gap_HeatSink_Left[2];
	double				m_dPicker_Gap_HeatSink_Right[2];
	
	int					m_nTraySize_X[2];
	int					m_nTraySize_Y[2];

	int					OnDataComparison();
	void				OnInitGroupBox();
	void				OnInitLabel();
	void				OnInitButton();
	void				OnInitDigit();
	void				OnDataHistoryLog();
	void				OnDataRecovery();
	
	void				OnDataApply();
	void				OnDataBackup();
	void				OnDataInit();
	void				OnDataDisplay();

public:
	CWorkRecipe(CWnd* pParent = NULL);   // 표준 생성자입니다.
	virtual ~CWorkRecipe();

// 대화 상자 데이터입니다.
	enum { IDD = IDD_WORK_RECIPE };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 지원입니다.

	DECLARE_MESSAGE_MAP()
public:
	virtual BOOL DestroyWindow();
	virtual BOOL OnInitDialog();
	afx_msg BOOL OnEraseBkgnd(CDC* pDC);
	afx_msg void OnBnClickedBtnApply();
	afx_msg void OnBnClickedBtnReload();
	virtual void PostNcDestroy();
	afx_msg void OnDestroy();
	afx_msg void OnTimer(UINT_PTR nIDEvent);
	afx_msg void OnStnClickedDgtPickerGapModuleLoad();
	afx_msg void OnStnClickedDgtPickerGapHeatsinkLeft();
	afx_msg void OnStnClickedDgtPickerGapHeatsinkRight();
	
	afx_msg void OnStnClickedDgtTrayX();
	afx_msg void OnStnClickedDgtTrayY();
};
