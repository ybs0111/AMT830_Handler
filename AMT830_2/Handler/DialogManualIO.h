#pragma once

#include "XPGroupBox.h"
#include "xShadeButton.h"	// 조그 버튼 생성 클래스 추가
#include ".\\Union\\Grid\\GridCtrl.h"
#include ".\\Union\\Grid\\GridURLCell.h"
#include ".\\Union\\Grid\\GridCellCombo.h"
#include ".\\Union\\Grid\\GridCellCheck.h"
#include ".\\Union\\Grid\\GridCellNumeric.h"
#include ".\\Union\\Grid\\GridCellDateTime.h"
#include "Digit.h"
#include "BtnST.h"
#include "Variable.h"
#include "GradientStatic.h"
// CDialogManualIO 대화 상자입니다.

class CDialogManualIO : public CDialog
{
	DECLARE_DYNAMIC(CDialogManualIO)

public:
	CButtonST		m_btnExit;
	CButtonST		m_btnDoor;
	CButtonST		m_btnLeftMpClamp;
	CButtonST		m_btnLeftMpUnClamp;
	CButtonST		m_btnRightMpClamp;
	CButtonST		m_btnRightMpUnClamp;

	CGridCtrl		m_pGridTsite;
	CGridCtrl		m_pGridTRbt;
	CGridCtrl		m_pGridLdRbt;
	CGridCtrl		m_pGridUldRbt;
	CGridCtrl		m_pGridLfContact;
	CGridCtrl		m_pGridRiContact;
	CGridCtrl		m_pGridBuf;

	int				m_nTsiteNum;

	CBitmap			m_bmGround;

	DWORD			m_dwWaitTime[3];

	// retest buffer
	int				m_nRetestMvFwdCyl;
	int				m_nRetestMvBwdCyl;
	int				m_nRetestMvFwdChk;
	int				m_nRetestMvBwdChk;

	int				m_nRetestMvFwdOut[2];
	int				m_nRetestMvBwdOut[2];
	int				m_nRetestMvFwd[2];
	int				m_nRetestMvBwd[2];

	int				m_nRetestAlignCyl;
	int				m_nRetestAlignFwdChk;
	int				m_nRetestAlignBwdChk;

	int				m_nRetestAlignOut[2];
	int				m_nRetestAlignFwd[2];
	int				m_nRetestAlignBwd[2];

	// reject buffer
	int				m_nRejectClampCyl;
	int				m_nRejectClampFwdChk;
	int				m_nRejectClampBwdChk;

	int				m_nRejectClampOut[2];
	int				m_nRejectClampFwd[2];
	int				m_nRejectClampBwd[2];

	int				m_nRejectUpDnCyl;
	int				m_nRejectUpChk;
	int				m_nRejectDnChk;

	int				m_nRejectUpDnOut[2];
	int				m_nRejectUp[2];
	int				m_nRejectDn[2];

	int				m_nRejectMvFwdCyl;
	int				m_nRejectMvBwdCyl;
	int				m_nRejectMvFwdChk;
	int				m_nRejectMvBwdChk;

	int				m_nRejectMvFwdOut[2];
	int				m_nRejectMvBwdOut[2];
	int				m_nRejectMvFwd[2];
	int				m_nRejectMvBwd[2];

	// left cok clamp
	int				m_nLfCokCyl[2];
	int				m_nLfCokFwdChk[2][2];
	int				m_nLfCokBwdChk[2][2];

	int				m_nLfTCokClampOut[2];
	int				m_nLfTCokClampFwd[2][2];
	int				m_nLfTCokClampBwd[2][2];

	int				m_nLfBCokClampOut[2];
	int				m_nLfBCokClampFwd[2][2];
	int				m_nLfBCokClampBwd[2][2];
	// left contact
	int				m_nLfContactFwdCyl[2];
	int				m_nLfContactBwdCyl[2];
	int				m_nLfContactFwdChk[2][2];
	int				m_nLfContactBwdChk[2][2];

	int				m_nLfBContactOut[2][2];
	int				m_nLfBContactFwd[2][2];
	int				m_nLfBContactBwd[2][2];

	int				m_nLfTContactOut[2][2];
	int				m_nLfTContactFwd[2][2];
	int				m_nLfTContactBwd[2][2];
	// left hifix
	int				m_nLfHifixFwdCyl;
	int				m_nLfHifixBwdCyl;
	int				m_nLfHifixFwdChk[3];
	int				m_nLfHifixBwdChk[3];

	int				m_nLfHifixOut[2][2];
	int				m_nLfHifixFwd[2][3];
	int				m_nLfHifixBwd[2][3];
	// left mp
	int				m_nLfMpFwdCyl;
	int				m_nLfMpBwdCyl;
	int				m_nLfMpFwdChk[2];
	int				m_nLfMpBwdChk[2];

	int				m_nLfMpOut[2][2];
	int				m_nLfMpFwd[2][2];
	int				m_nLfMpBwd[2][2];
	// right cok clamp
	int				m_nRiCokCyl[2];
	int				m_nRiCokFwdChk[2][2];
	int				m_nRiCokBwdChk[2][2];

	int				m_nRiBCokClampOut[2];
	int				m_nRiBCokClampFwd[2][2];
	int				m_nRiBCokClampBwd[2][2];

	int				m_nRiTCokClampOut[2];
	int				m_nRiTCokClampFwd[2][2];
	int				m_nRiTCokClampBwd[2][2];
	// right contact
	int				m_nRiContactFwdCyl[2];
	int				m_nRiContactBwdCyl[2];
	int				m_nRiContactFwdChk[2][2];
	int				m_nRiContactBwdChk[2][2];

	int				m_nRiBContactOut[2][2];
	int				m_nRiBContactFwd[2][2];
	int				m_nRiBContactBwd[2][2];

	int				m_nRiTContactOut[2][2];
	int				m_nRiTContactFwd[2][2];
	int				m_nRiTContactBwd[2][2];
	// right hifix
	int				m_nRiHifixFwdCyl;
	int				m_nRiHifixBwdCyl;
	int				m_nRiHifixFwdChk[3];
	int				m_nRiHifixBwdChk[3];

	int				m_nRiHifixOut[2][2];
	int				m_nRiHifixFwd[2][3];
	int				m_nRiHifixBwd[2][3];
	// right mp
	int				m_nRiMpFwdCyl;
	int				m_nRiMpBwdCyl;
	int				m_nRiMpFwdChk[2];
	int				m_nRiMpBwdChk[2];

	int				m_nRiMpOut[2][2];
	int				m_nRiMpFwd[2][2];
	int				m_nRiMpBwd[2][2];
	// test site insert
	int				m_nInsertCyl[4][6];
	int				m_nInsertFwdChk[4][6];
	int				m_nInsertBwdChk[4][6];

	int				m_nTsiteInsFwd[2][6];
	int				m_nTsiteInsBwd[2][6];
	int				m_nTsiteInsOut[2][6];

	int				m_nPogoCyl[4][12];
	int			    m_nPogoOnOffChk[4][12];

	int				m_nTsitePogoIn[2][12];
	int				m_nTsitePogoOut[2][12];
	// test site robot
	int				m_nTsiteCyl[4];
	int				m_nTsiteFwdChk[4];
	int				m_nTsiteBwdChk[4];
	int				m_nTsiteVac[4];
	int				m_nTsiteEjc[4];
	int				m_nTsiteVacChk[4];

	int				m_nTsiteUpIn[2][4];
	int				m_nTsiteUpOut[2][4];
	int				m_nTsiteDnIn[2][4];
	int				m_nTsiteDnOut[2][4];
	int				m_nTsiteVacIn[2][4];
	int				m_nTsiteVacOut[2][4];
	int				m_nTsiteEjcOut[2][4];
	// load robot
	int				m_nLdCyl[2];
	int				m_nLdFwdChk[2];
	int				m_nLdBwdChk[2];
	int				m_nLdVac[2];
	int				m_nLdEjc[2];
	int				m_nLdVacChk[2];

	int				m_nLdUpIn[2][2];
	int				m_nLdUpOut[2][2];
	int				m_nLdDnIn[2][2];
	int				m_nLdDnOut[2][2];
	int				m_nLdVacIn[2][2];
	int				m_nLdVacOut[2][2];
	int				m_nLdEjcOut[2][2];
	// unload robot
	int				m_nUnLdCyl[2];
	int				m_nUnLdFwdChk[2];
	int				m_nUnLdBwdChk[2];
	int				m_nUnLdVac[2];
	int				m_nUnLdEjc[2];
	int				m_nUnLdVacChk[2];

	int				m_nUnLdUpIn[2][2];
	int				m_nUnLdUpOut[2][2];
	int				m_nUnLdDnIn[2][2];
	int				m_nUnLdDnOut[2][2];
	int				m_nUnLdVacIn[2][2];
	int				m_nUnLdVacOut[2][2];
	int				m_nUnLdEjcOut[2][2];

	BOOL			Create();
	void			OnDisplayTestSite(int nNum);
	void			OnDisplayLdRobot();
	void			OnDisplayUnLdRobot();
	void			OnDisplayTestSiteRobot();
	void			OnDisplayLeftContact();
	void			OnDisplayRightContact();
	void			OnDisplayBuffer();
	void			OnDisplayTestSite();
	void			OnInitGridTsite();
	void			OnInitGridTsiteRbt();
	void			OnInitGridLdRbt();
	void			OnInitGridUldRbt();
	void			OnInitGridLfContact();
	void			OnInitGridRiContact();
	void			OnInitGridBuffer();
	void			OnInitButton();
public:
	CDialogManualIO(CWnd* pParent = NULL);   // 표준 생성자입니다.
	virtual ~CDialogManualIO();

// 대화 상자 데이터입니다.
	enum { IDD = IDD_DIALOG_MANUAL_IO };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 지원입니다.

	DECLARE_MESSAGE_MAP()
public:
	afx_msg BOOL OnEraseBkgnd(CDC* pDC);
	virtual BOOL DestroyWindow();
	virtual BOOL OnInitDialog();
	afx_msg void OnTimer(UINT_PTR nIDEvent);
	afx_msg void OnLdRbtCellClick(NMHDR *pNotifyStruct, LRESULT* pResult);
	afx_msg void OnUldRbtCellClick(NMHDR *pNotifyStruct, LRESULT* pResult);
	afx_msg void OnTRbtCellClick(NMHDR *pNotifyStruct, LRESULT* pResult);
	afx_msg void OnTsiteCellClick(NMHDR *pNotifyStruct, LRESULT* pResult);
	afx_msg void OnLeftContactCellClick(NMHDR *pNotifyStruct, LRESULT* pResult);
	afx_msg void OnRightContactCellClick(NMHDR *pNotifyStruct, LRESULT* pResult);
	afx_msg void OnBufferCellClick(NMHDR *pNotifyStruct, LRESULT* pResult);
	afx_msg void OnBnClickedBtnExit();
	afx_msg void OnBnClickedBtnRefresh();
	afx_msg void OnBnClickedBtnLeftClamp();
	afx_msg void OnBnClickedBtnLeftUnclamp();
	afx_msg void OnBnClickedBtnRightClamp();
	afx_msg void OnBnClickedBtnRightUnclamp();
};
