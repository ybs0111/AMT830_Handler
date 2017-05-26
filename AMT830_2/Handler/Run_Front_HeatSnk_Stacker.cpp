#include "StdAfx.h"
#include "Run_Front_HeatSnk_Stacker.h"
#include "Variable.h"
#include "CtlBd_Library.h"
#include "ComizoaPublic.h"
#include "CtlBd_Variable.h"
#include "PublicFunction.h"
#include "FastechPublic_IO.h"

CRun_Front_HeatSnk_Stacker clsRunHsFrontStacker;
CRun_Front_HeatSnk_Stacker::CRun_Front_HeatSnk_Stacker(void)
{
	m_nInitStep = -1;
	m_nRunStep = -1;

	m_nAxisNum_Ready = M_HS_F_STACKER_READY;

}

CRun_Front_HeatSnk_Stacker::~CRun_Front_HeatSnk_Stacker(void)
{
}
void CRun_Front_HeatSnk_Stacker::ThreadRun()
{	 
	if (st_handler_info.nSystemLock != FALSE)  return;	// 현재 시스템 Lock 상태인 경우 리턴

	switch(st_handler_info.nRunStatus)
	{
	case dINIT:
		OnRunInit();
		break;

	case dRUN:
		OnRunMove();					
		break;

	case dSTOP:

		break;

	case dWARNING:

		break;


	}
}
void CRun_Front_HeatSnk_Stacker::OnRunMove()
{
	switch(m_nRunStep)
	{
	case 0:
		
		
		break;

	}
}
void CRun_Front_HeatSnk_Stacker::OnRunInit()
{
	int nRet_1, nRet_2;

	if (st_sync_info.nInit_Flag[THD_HS_FRONT_STACKER] != INIT_CLEAR)		return;	

	switch (m_nInitStep)
	{
	case -1:

		m_nInitStep = 0;
		break;

	case 0:		
		m_nInitStep = 100;
		break;

	case 100: //up
		if (FAS_IO.get_in_bit(st_io_info.i_hs_Front_Work_stacker_tray_chk,IO_OFF) == IO_ON)
		{	
			CTL_Lib.Alarm_Error_Occurrence(10,CTL_dWARNING, _T("030202"));
		}
		else if (FAS_IO.get_in_bit(st_io_info.i_hs_Front_Ready_stacker_tray_chk,IO_OFF) == IO_ON)
		{
			
			CTL_Lib.Alarm_Error_Occurrence(11, CTL_dWARNING, _T("030202"));
		}
		else
		{
			m_nInitStep = 110;
		}
		break;

	case 110:
		OnSet_ReadyPos_TrayClampCyl(IO_OFF);
		m_nInitStep = 200;
		break;

	case 200:
		nRet_1 = OnGet_ReadyPos_TrayClampCyl(IO_OFF);
		if (nRet_1 == RET_GOOD)
		{
			m_nInitStep = 300;
		}
		else if (nRet_1 == RET_ERROR)
		{
			CTL_Lib.Alarm_Error_Occurrence(30, CTL_dWARNING, m_strCode);
		}
		break;

	case 300:
		OnSet_WorkPos_TrayClampCyl(IO_OFF);
		m_nInitStep = 310;
		break;

	case 310:
		nRet_1 = OnGet_WorkPos_TrayClampCyl(IO_OFF);
		if (nRet_1 == RET_GOOD)
		{
			m_nInitStep = 400;
		}
		else if (nRet_1 == RET_ERROR)
		{
			CTL_Lib.Alarm_Error_Occurrence(31, CTL_dWARNING, m_strCode);
		}
		break;

	case 400:
		OnSet_ReadyPos_RailFwdBwdCyl(IO_OFF);
		m_nInitStep = 410;
		break;

	case 410:
		nRet_1 = OnGet_ReadyPos_RailFwdBwdCyl(IO_OFF);

		if (nRet_1 == RET_GOOD)
		{
			m_nInitStep = 420;
		}
		else if (nRet_1 == RET_ERROR)
		{
			CTL_Lib.Alarm_Error_Occurrence(41, CTL_dWARNING, m_strCode);
		}
		break;

	case 420:
		 OnSet_WorkPos_RailFwdBwdCyl(IO_OFF);
		 m_nInitStep = 430;
		break;

	case 430:
		nRet_1 = OnGet_WorkPos_RailFwdBwdCyl(IO_OFF);
		if (nRet_1 == RET_GOOD)
		{
			m_nInitStep = 440;
		}
		else if (nRet_1 == RET_ERROR)
		{
			CTL_Lib.Alarm_Error_Occurrence(42, CTL_dWARNING, m_strCode);
		}
		break;

	case 440:
		OnSet_ReadyPos_StackerCylUpDn(IO_OFF);
		m_nInitStep = 450;
		break;

	case 450:
		nRet_1 = OnGet_ReadyPos_StackerCylUpDn(IO_OFF);
		if (nRet_1 == RET_GOOD)
		{
			m_nInitStep = 500;
		}
		else if (nRet_1 == RET_ERROR)
		{
			CTL_Lib.Alarm_Error_Occurrence(45, CTL_dWARNING, m_strCode);
		}
		break;

	case 500:
		OnSetPusherFwdBwdCyl(IO_OFF);
		m_nInitStep = 510;
		break;

	case 510:
		nRet_1 = OnGetPusherFwdBwdCyl(IO_OFF);
		if (nRet_1 == RET_GOOD)
		{
			m_nInitStep = 600;
		}
		else if (nRet_1 == RET_ERROR)
		{
			CTL_Lib.Alarm_Error_Occurrence(45, CTL_dWARNING, m_strCode);
		}

		break;
	case 600:
		OnSet_WorkPos_StackerCylUpDn(IO_OFF);
		m_nInitStep = 510;
		break;

	case 610:
		nRet_1 = OnGet_WorkPos_StackerCylUpDn(IO_OFF);
		if (nRet_1 == RET_GOOD)
		{
			m_nInitStep = 1000;
		}
		else if (nRet_1 == RET_ERROR)
		{
			CTL_Lib.Alarm_Error_Occurrence(51, CTL_dWARNING, m_strCode);
		}
		break;

	case 1000:
		nRet_1 = COMI.HomeCheck_Mot(m_nAxisNum_Ready, MOT_SENS_ELM, MOT_TIMEOUT) ; //
		if(nRet_1 == BD_GOOD)
		{
			COMI.mn_homechk_flag[m_nAxisNum_Ready] = CTL_YES;
			m_nInitStep = 1100;
		}
		else if(nRet_1 == BD_ERROR)
		{
			CTL_Lib.Alarm_Error_Occurrence(10, CTL_dWARNING, COMI.m_strCode);
		}	
		break;

	case 1100:
		st_sync_info.nInit_Flag[THD_HS_FRONT_STACKER] = INIT_READY; 

		m_nInitStep = 0;
		break;	

	default :
		break;

	}
}

void CRun_Front_HeatSnk_Stacker::OnSet_ReadyPos_StackerCylUpDn(int nUpDn)
{
	FAS_IO.set_out_bit(st_io_info.o_hs_Front_Ready_stacker_updn,nUpDn);
	m_dwCylWaitTime[READY_STACKER_UPDN][0] = GetCurrentTime();
	m_bCylinderFlag[READY_STACKER_UPDN] = false;
}

int CRun_Front_HeatSnk_Stacker::OnGet_ReadyPos_StackerCylUpDn(int nUpDn)
{
	int nRet = RET_PROCEED;
	int nWaitTime = WAIT_STACKER_UP_DN;

	if (nUpDn == IO_ON)
	{
		if (m_bCylinderFlag[READY_STACKER_UPDN] == false && 
			FAS_IO.get_in_bit(st_io_info.i_hs_Front_Ready_stacker_dn_chk, IO_ON) == IO_ON &&
			FAS_IO.get_in_bit(st_io_info.i_hs_Front_Ready_stacker_up_chk, IO_OFF) == IO_OFF)
		{
			m_bCylinderFlag[READY_STACKER_UPDN] = true;
			m_dwCylWaitTime[READY_STACKER_UPDN][0] = GetCurrentTime();
		}
		else if (m_bCylinderFlag[READY_STACKER_UPDN] == true &&
			FAS_IO.get_in_bit(st_io_info.i_hs_Front_Ready_stacker_dn_chk, IO_ON) == IO_ON &&
			FAS_IO.get_in_bit(st_io_info.i_hs_Front_Ready_stacker_up_chk, IO_OFF) == IO_OFF)
		{
			m_dwCylWaitTime[READY_STACKER_UPDN][1] = GetCurrentTime();
			m_dwCylWaitTime[READY_STACKER_UPDN][2] = m_dwCylWaitTime[READY_STACKER_UPDN][1] - m_dwCylWaitTime[READY_STACKER_UPDN][0];

			if (m_dwCylWaitTime[READY_STACKER_UPDN][2] <= 0)
			{
				m_dwCylWaitTime[READY_STACKER_UPDN][0] = GetCurrentTime();
				return RET_PROCEED;
			}
			if (m_dwCylWaitTime[READY_STACKER_UPDN][2] > (DWORD)st_wait_info.nOnWaitTime[nWaitTime])
			{
				return RET_GOOD;
			}
		}
		else
		{
			m_dwCylWaitTime[READY_STACKER_UPDN][1] = GetCurrentTime();
			m_dwCylWaitTime[READY_STACKER_UPDN][2] = m_dwCylWaitTime[READY_STACKER_UPDN][1] - m_dwCylWaitTime[READY_STACKER_UPDN][0];

			if (m_dwCylWaitTime[READY_STACKER_UPDN][2] <= 0)
			{
				m_dwCylWaitTime[READY_STACKER_UPDN][0] = GetCurrentTime();
				return RET_PROCEED;
			}
			if (m_dwCylWaitTime[READY_STACKER_UPDN][2] > (DWORD)st_wait_info.nLimitWaitTime[nWaitTime])
			{
				m_strCode.Format(_T("1401%d"),nUpDn);
				return RET_ERROR;
			}
		}
	}
	else //(nUpDn == IO_OFF)
	{
		if (m_bCylinderFlag[READY_STACKER_UPDN] == false && 
			FAS_IO.get_in_bit(st_io_info.i_hs_Front_Ready_stacker_dn_chk, IO_OFF) == IO_OFF &&
			FAS_IO.get_in_bit(st_io_info.i_hs_Front_Ready_stacker_up_chk, IO_ON) == IO_ON)
		{
			m_bCylinderFlag[READY_STACKER_UPDN] = true;
			m_dwCylWaitTime[READY_STACKER_UPDN][0] = GetCurrentTime();
		}
		else if (m_bCylinderFlag[READY_STACKER_UPDN] == true &&
			FAS_IO.get_in_bit(st_io_info.i_hs_Front_Ready_stacker_dn_chk, IO_OFF) == IO_OFF &&
			FAS_IO.get_in_bit(st_io_info.i_hs_Front_Ready_stacker_up_chk, IO_ON) == IO_ON)
		{
			m_dwCylWaitTime[READY_STACKER_UPDN][1] = GetCurrentTime();
			m_dwCylWaitTime[READY_STACKER_UPDN][2] = m_dwCylWaitTime[READY_STACKER_UPDN][1] - m_dwCylWaitTime[READY_STACKER_UPDN][0];

			if (m_dwCylWaitTime[READY_STACKER_UPDN][2] <= 0)
			{
				m_dwCylWaitTime[READY_STACKER_UPDN][0] = GetCurrentTime();
				return RET_PROCEED;
			}
			if (m_dwCylWaitTime[READY_STACKER_UPDN][2] > (DWORD)st_wait_info.nOnWaitTime[nWaitTime])
			{
				return RET_GOOD;
			}
		}
		else
		{
			m_dwCylWaitTime[READY_STACKER_UPDN][1] = GetCurrentTime();
			m_dwCylWaitTime[READY_STACKER_UPDN][2] = m_dwCylWaitTime[READY_STACKER_UPDN][1] - m_dwCylWaitTime[READY_STACKER_UPDN][0];

			if (m_dwCylWaitTime[READY_STACKER_UPDN][2] <= 0)
			{
				m_dwCylWaitTime[READY_STACKER_UPDN][0] = GetCurrentTime();
				return RET_PROCEED;
			}
			if (m_dwCylWaitTime[READY_STACKER_UPDN][2] > (DWORD)st_wait_info.nLimitWaitTime[nWaitTime])
			{
				m_strCode.Format(_T("1401%d"),nUpDn);
				return RET_ERROR;
			}
		}
	}
	return nRet;
}

void CRun_Front_HeatSnk_Stacker::OnSet_ReadyPos_RailFwdBwdCyl(int nOnOff)
{
	
	FAS_IO.set_out_bit(st_io_info.o_hs_Front_Ready_stacker_Left_rail_fwd_onoff,nOnOff);
	FAS_IO.set_out_bit(st_io_info.o_hs_Front_Ready_stacker_Right_rail_fwd_onoff,nOnOff);

	FAS_IO.set_out_bit(st_io_info.o_hs_Front_Ready_stacker_Left_rail_bwd_onoff,!nOnOff);
	FAS_IO.set_out_bit(st_io_info.o_hs_Front_Ready_stacker_Right_rail_bwd_onoff,!nOnOff);
	
	m_dwCylWaitTime[READY_RAIL_FWDBWD][0] = GetCurrentTime();
	m_bCylinderFlag[READY_RAIL_FWDBWD] = false;
}

int CRun_Front_HeatSnk_Stacker::OnGet_ReadyPos_RailFwdBwdCyl(int nOnOff)
{
	int nWaitTime = WAIT_STACKER_CYL_ON_OFF;
	int nRet = RET_PROCEED;

	if (nOnOff == IO_ON)
	{
		if (m_bCylinderFlag[READY_RAIL_FWDBWD] ==  false && 
			FAS_IO.get_in_bit(st_io_info.i_hs_Front_Ready_stacker_Left_rail_fwd_chk,IO_ON) == IO_ON &&
			FAS_IO.get_in_bit(st_io_info.i_hs_Front_Ready_stacker_Left_rail_bwd_chk,IO_OFF) == IO_OFF &&
			FAS_IO.get_in_bit(st_io_info.i_hs_Front_Ready_stacker_Right_rail_fwd_chk,IO_ON) == IO_ON &&
			FAS_IO.get_in_bit(st_io_info.i_hs_Front_Ready_stacker_Right_rail_bwd_chk,IO_OFF) == IO_OFF)
		{
			m_bCylinderFlag[READY_RAIL_FWDBWD] = true;
			m_dwCylWaitTime[READY_RAIL_FWDBWD][0] = GetCurrentTime();
		}
		else if (m_bCylinderFlag[READY_RAIL_FWDBWD] ==  true && 
			FAS_IO.get_in_bit(st_io_info.i_hs_Front_Ready_stacker_Left_rail_fwd_chk,IO_ON) == IO_ON &&
			FAS_IO.get_in_bit(st_io_info.i_hs_Front_Ready_stacker_Left_rail_bwd_chk,IO_OFF) == IO_OFF &&
			FAS_IO.get_in_bit(st_io_info.i_hs_Front_Ready_stacker_Right_rail_fwd_chk,IO_ON) == IO_ON &&
			FAS_IO.get_in_bit(st_io_info.i_hs_Front_Ready_stacker_Right_rail_bwd_chk,IO_OFF) == IO_OFF)
		{
			m_dwCylWaitTime[READY_RAIL_FWDBWD][1] = GetCurrentTime();
			m_dwCylWaitTime[READY_RAIL_FWDBWD][2] = m_dwCylWaitTime[READY_RAIL_FWDBWD][1] - m_dwCylWaitTime[READY_RAIL_FWDBWD][0];

			if (m_dwCylWaitTime[READY_RAIL_FWDBWD][2] <= 0)
			{
				m_dwCylWaitTime[READY_RAIL_FWDBWD][0] = GetCurrentTime();
				return RET_PROCEED;
			}
			if (m_dwCylWaitTime[READY_RAIL_FWDBWD][2] > (DWORD)st_wait_info.nOnWaitTime[nWaitTime])
			{
				return RET_GOOD;
			}
		}
		else
		{
			m_dwCylWaitTime[READY_RAIL_FWDBWD][1] = GetCurrentTime();
			m_dwCylWaitTime[READY_RAIL_FWDBWD][2] = m_dwCylWaitTime[READY_RAIL_FWDBWD][1] - m_dwCylWaitTime[READY_RAIL_FWDBWD][0];

			if (m_dwCylWaitTime[READY_RAIL_FWDBWD][2] <= 0)
			{
				m_dwCylWaitTime[READY_RAIL_FWDBWD][0] = GetCurrentTime();
				return RET_PROCEED;
			}
			if (m_dwCylWaitTime[READY_RAIL_FWDBWD][2] > (DWORD)st_wait_info.nLimitWaitTime[nWaitTime])
			{
				m_strCode.Format(_T("1401%d"),nOnOff);
				return RET_ERROR;
			}
		}
	}
	else //(nOnOff == IO_OFF)
	{
		if (m_bCylinderFlag[READY_RAIL_FWDBWD] ==  false && 
			FAS_IO.get_in_bit(st_io_info.i_hs_Front_Ready_stacker_Left_rail_fwd_chk,IO_OFF) == IO_OFF &&
			FAS_IO.get_in_bit(st_io_info.i_hs_Front_Ready_stacker_Left_rail_bwd_chk,IO_ON) == IO_ON &&
			FAS_IO.get_in_bit(st_io_info.i_hs_Front_Ready_stacker_Right_rail_fwd_chk,IO_OFF) == IO_OFF &&
			FAS_IO.get_in_bit(st_io_info.i_hs_Front_Ready_stacker_Right_rail_bwd_chk,IO_ON) == IO_ON)
		{
			m_bCylinderFlag[READY_RAIL_FWDBWD] = true;
			m_dwCylWaitTime[READY_RAIL_FWDBWD][0] = GetCurrentTime();
		}
		else if (m_bCylinderFlag[READY_RAIL_FWDBWD] ==  true && 
			FAS_IO.get_in_bit(st_io_info.i_hs_Front_Ready_stacker_Left_rail_fwd_chk,IO_OFF) == IO_OFF &&
			FAS_IO.get_in_bit(st_io_info.i_hs_Front_Ready_stacker_Left_rail_bwd_chk,IO_ON) == IO_ON &&
			FAS_IO.get_in_bit(st_io_info.i_hs_Front_Ready_stacker_Right_rail_fwd_chk,IO_OFF) == IO_OFF &&
			FAS_IO.get_in_bit(st_io_info.i_hs_Front_Ready_stacker_Right_rail_bwd_chk,IO_ON) == IO_ON)
		{
			m_dwCylWaitTime[READY_RAIL_FWDBWD][1] = GetCurrentTime();
			m_dwCylWaitTime[READY_RAIL_FWDBWD][2] = m_dwCylWaitTime[READY_RAIL_FWDBWD][1] - m_dwCylWaitTime[READY_RAIL_FWDBWD][0];

			if (m_dwCylWaitTime[READY_RAIL_FWDBWD][2] <= 0)
			{
				m_dwCylWaitTime[READY_RAIL_FWDBWD][0] = GetCurrentTime();
				return RET_PROCEED;
			}
			if (m_dwCylWaitTime[READY_RAIL_FWDBWD][2] > (DWORD)st_wait_info.nOnWaitTime[nWaitTime])
			{
				return RET_GOOD;
			}
		}
		else
		{
			m_dwCylWaitTime[READY_RAIL_FWDBWD][1] = GetCurrentTime();
			m_dwCylWaitTime[READY_RAIL_FWDBWD][2] = m_dwCylWaitTime[READY_RAIL_FWDBWD][1] - m_dwCylWaitTime[READY_RAIL_FWDBWD][0];

			if (m_dwCylWaitTime[READY_RAIL_FWDBWD][2] <= 0)
			{
				m_dwCylWaitTime[READY_RAIL_FWDBWD][0] = GetCurrentTime();
				return RET_PROCEED;
			}
			if (m_dwCylWaitTime[READY_RAIL_FWDBWD][2] > (DWORD)st_wait_info.nLimitWaitTime[nWaitTime])
			{
				m_strCode.Format(_T("1401%d"),nOnOff);
				return RET_ERROR;
			}
		}
	}
	return nRet;
}

void CRun_Front_HeatSnk_Stacker::OnSet_ReadyPos_TrayClampCyl(int nOnOff)
{
	FAS_IO.set_out_bit(st_io_info.o_hs_Front_Ready_stacker_guide_clamp_onoff,nOnOff);
	FAS_IO.set_out_bit(st_io_info.o_hs_Front_Ready_stacker_guide_unclamp_onoff,!nOnOff);

	m_dwCylWaitTime[READY_TRAYCLAMP_ONOFF][0] = GetCurrentTime();
	m_bCylinderFlag[READY_TRAYCLAMP_ONOFF] = false;
}

int CRun_Front_HeatSnk_Stacker::OnGet_ReadyPos_TrayClampCyl(int nOnOff)
{
	int nWaitTime = WAIT_STACKER_CYL_ON_OFF;
	int nRet = RET_PROCEED;
	if (nOnOff == IO_ON)
	{
		if (m_bCylinderFlag[READY_TRAYCLAMP_ONOFF] ==  false && 
			FAS_IO.get_in_bit(st_io_info.i_hs_Front_Ready_stacker_guide_clamp_on_chk,IO_ON) == IO_ON &&
			FAS_IO.get_in_bit(st_io_info.i_hs_Front_Ready_stacker_guide_unclamp_off_chk,IO_OFF) == IO_OFF)
			
		{
			m_bCylinderFlag[READY_TRAYCLAMP_ONOFF] = true;
			m_dwCylWaitTime[READY_TRAYCLAMP_ONOFF][0] = GetCurrentTime();
		}
		else if (m_bCylinderFlag[READY_TRAYCLAMP_ONOFF] ==  true && 
			FAS_IO.get_in_bit(st_io_info.i_hs_Front_Ready_stacker_guide_clamp_on_chk,IO_ON) == IO_ON &&
			FAS_IO.get_in_bit(st_io_info.i_hs_Front_Ready_stacker_guide_unclamp_off_chk,IO_OFF) == IO_OFF)
		{
			m_dwCylWaitTime[READY_TRAYCLAMP_ONOFF][1] = GetCurrentTime();
			m_dwCylWaitTime[READY_TRAYCLAMP_ONOFF][2] = m_dwCylWaitTime[READY_TRAYCLAMP_ONOFF][1] - m_dwCylWaitTime[READY_TRAYCLAMP_ONOFF][0];

			if (m_dwCylWaitTime[READY_TRAYCLAMP_ONOFF][2] <= 0)
			{
				m_dwCylWaitTime[READY_TRAYCLAMP_ONOFF][0] = GetCurrentTime();
				return RET_PROCEED;
			}
			if (m_dwCylWaitTime[READY_TRAYCLAMP_ONOFF][2] > (DWORD)st_wait_info.nOnWaitTime[nWaitTime])
			{
				return RET_GOOD;
			}
		}
		else
		{
			m_dwCylWaitTime[READY_TRAYCLAMP_ONOFF][1] = GetCurrentTime();
			m_dwCylWaitTime[READY_TRAYCLAMP_ONOFF][2] = m_dwCylWaitTime[READY_TRAYCLAMP_ONOFF][1] - m_dwCylWaitTime[READY_TRAYCLAMP_ONOFF][0];

			if (m_dwCylWaitTime[READY_TRAYCLAMP_ONOFF][2] <= 0)
			{
				m_dwCylWaitTime[READY_TRAYCLAMP_ONOFF][0] = GetCurrentTime();
				return RET_PROCEED;
			}
			if (m_dwCylWaitTime[READY_TRAYCLAMP_ONOFF][2] > (DWORD)st_wait_info.nLimitWaitTime[nWaitTime])
			{
				m_strCode.Format(_T("1401%d"),nOnOff);
				return RET_ERROR;
			}
		}
	}
	else //(nOnOff == IO_OFF)
	{
		if (m_bCylinderFlag[READY_TRAYCLAMP_ONOFF] ==  false && 
			FAS_IO.get_in_bit(st_io_info.i_hs_Front_Ready_stacker_guide_clamp_on_chk,IO_OFF) == IO_OFF &&
			FAS_IO.get_in_bit(st_io_info.i_hs_Front_Ready_stacker_guide_unclamp_off_chk,IO_ON) == IO_ON)

		{
			m_bCylinderFlag[READY_TRAYCLAMP_ONOFF] = true;
			m_dwCylWaitTime[READY_TRAYCLAMP_ONOFF][0] = GetCurrentTime();
		}
		else if (m_bCylinderFlag[READY_TRAYCLAMP_ONOFF] ==  true && 
			FAS_IO.get_in_bit(st_io_info.i_hs_Front_Ready_stacker_guide_clamp_on_chk,IO_OFF) == IO_OFF &&
			FAS_IO.get_in_bit(st_io_info.i_hs_Front_Ready_stacker_guide_unclamp_off_chk,IO_ON) == IO_ON)
		{
			m_dwCylWaitTime[READY_TRAYCLAMP_ONOFF][1] = GetCurrentTime();
			m_dwCylWaitTime[READY_TRAYCLAMP_ONOFF][2] = m_dwCylWaitTime[READY_TRAYCLAMP_ONOFF][1] - m_dwCylWaitTime[READY_TRAYCLAMP_ONOFF][0];

			if (m_dwCylWaitTime[READY_TRAYCLAMP_ONOFF][2] <= 0)
			{
				m_dwCylWaitTime[READY_TRAYCLAMP_ONOFF][0] = GetCurrentTime();
				return RET_PROCEED;
			}
			if (m_dwCylWaitTime[READY_TRAYCLAMP_ONOFF][2] > (DWORD)st_wait_info.nOnWaitTime[nWaitTime])
			{
				return RET_GOOD;
			}
		}
		else
		{
			m_dwCylWaitTime[READY_TRAYCLAMP_ONOFF][1] = GetCurrentTime();
			m_dwCylWaitTime[READY_TRAYCLAMP_ONOFF][2] = m_dwCylWaitTime[READY_TRAYCLAMP_ONOFF][1] - m_dwCylWaitTime[READY_TRAYCLAMP_ONOFF][0];

			if (m_dwCylWaitTime[READY_TRAYCLAMP_ONOFF][2] <= 0)
			{
				m_dwCylWaitTime[READY_TRAYCLAMP_ONOFF][0] = GetCurrentTime();
				return RET_PROCEED;
			}
			if (m_dwCylWaitTime[READY_TRAYCLAMP_ONOFF][2] > (DWORD)st_wait_info.nLimitWaitTime[nWaitTime])
			{
				m_strCode.Format(_T("1401%d"),nOnOff);
				return RET_ERROR;
			}
		}
	}
	return nRet;
}

void CRun_Front_HeatSnk_Stacker::OnSetPusherFwdBwdCyl(int nOnOff)
{
	FAS_IO.set_out_bit(st_io_info.o_hs_Front_stacker_tray_pusher_fwd_onoff,nOnOff);
	FAS_IO.set_out_bit(st_io_info.o_hs_Front_stacker_tray_pusher_bwd_onoff,!nOnOff);

	m_dwCylWaitTime[READY_PUSHER_ONOFF][0] = GetCurrentTime();
	m_bCylinderFlag[READY_PUSHER_ONOFF] = false;
}

int CRun_Front_HeatSnk_Stacker::OnGetPusherFwdBwdCyl(int nOnOff)
{
	int nWaitTime = WAIT_STACKER_CYL_ON_OFF;
	int nRet = RET_PROCEED;
	if (nOnOff == IO_ON)
	{
		if (m_bCylinderFlag[READY_PUSHER_ONOFF] ==  false && 
			FAS_IO.get_in_bit(st_io_info.i_hs_Front_stacker_tray_pusher_fwd_chk,IO_ON) == IO_ON &&
			FAS_IO.get_in_bit(st_io_info.i_hs_Front_stacker_tray_pusher_bwd_chk,IO_OFF) == IO_OFF)

		{
			m_bCylinderFlag[READY_PUSHER_ONOFF] = true;
			m_dwCylWaitTime[READY_PUSHER_ONOFF][0] = GetCurrentTime();
		}
		else if (m_bCylinderFlag[READY_PUSHER_ONOFF] ==  true && 
			FAS_IO.get_in_bit(st_io_info.i_hs_Front_stacker_tray_pusher_fwd_chk,IO_ON) == IO_ON &&
			FAS_IO.get_in_bit(st_io_info.i_hs_Front_stacker_tray_pusher_bwd_chk,IO_OFF) == IO_OFF)
		{
			m_dwCylWaitTime[READY_PUSHER_ONOFF][1] = GetCurrentTime();
			m_dwCylWaitTime[READY_PUSHER_ONOFF][2] = m_dwCylWaitTime[READY_PUSHER_ONOFF][1] - m_dwCylWaitTime[READY_PUSHER_ONOFF][0];

			if (m_dwCylWaitTime[READY_PUSHER_ONOFF][2] <= 0)
			{
				m_dwCylWaitTime[READY_PUSHER_ONOFF][0] = GetCurrentTime();
				return RET_PROCEED;
			}
			if (m_dwCylWaitTime[READY_PUSHER_ONOFF][2] > (DWORD)st_wait_info.nOnWaitTime[nWaitTime])
			{
				return RET_GOOD;
			}
		}
		else
		{
			m_dwCylWaitTime[READY_PUSHER_ONOFF][1] = GetCurrentTime();
			m_dwCylWaitTime[READY_PUSHER_ONOFF][2] = m_dwCylWaitTime[READY_PUSHER_ONOFF][1] - m_dwCylWaitTime[READY_PUSHER_ONOFF][0];

			if (m_dwCylWaitTime[READY_PUSHER_ONOFF][2] <= 0)
			{
				m_dwCylWaitTime[READY_PUSHER_ONOFF][0] = GetCurrentTime();
				return RET_PROCEED;
			}
			if (m_dwCylWaitTime[READY_PUSHER_ONOFF][2] > (DWORD)st_wait_info.nLimitWaitTime[nWaitTime])
			{
				m_strCode.Format(_T("1401%d"),nOnOff);
				return RET_ERROR;
			}
		}
	}
	else //(nOnOff == IO_OFF)
	{
		if (m_bCylinderFlag[READY_PUSHER_ONOFF] ==  false && 
			FAS_IO.get_in_bit(st_io_info.i_hs_Front_stacker_tray_pusher_fwd_chk,IO_OFF) == IO_OFF &&
			FAS_IO.get_in_bit(st_io_info.i_hs_Front_stacker_tray_pusher_bwd_chk,IO_ON) == IO_ON)

		{
			m_bCylinderFlag[READY_PUSHER_ONOFF] = true;
			m_dwCylWaitTime[READY_PUSHER_ONOFF][0] = GetCurrentTime();
		}
		else if (m_bCylinderFlag[READY_PUSHER_ONOFF] ==  true && 
			FAS_IO.get_in_bit(st_io_info.i_hs_Front_stacker_tray_pusher_fwd_chk,IO_OFF) == IO_OFF &&
			FAS_IO.get_in_bit(st_io_info.i_hs_Front_stacker_tray_pusher_bwd_chk,IO_ON) == IO_ON)
		{
			m_dwCylWaitTime[READY_PUSHER_ONOFF][1] = GetCurrentTime();
			m_dwCylWaitTime[READY_PUSHER_ONOFF][2] = m_dwCylWaitTime[READY_PUSHER_ONOFF][1] - m_dwCylWaitTime[READY_PUSHER_ONOFF][0];

			if (m_dwCylWaitTime[READY_PUSHER_ONOFF][2] <= 0)
			{
				m_dwCylWaitTime[READY_PUSHER_ONOFF][0] = GetCurrentTime();
				return RET_PROCEED;
			}
			if (m_dwCylWaitTime[READY_PUSHER_ONOFF][2] > (DWORD)st_wait_info.nOnWaitTime[nWaitTime])
			{
				return RET_GOOD;
			}
		}
		else
		{
			m_dwCylWaitTime[READY_PUSHER_ONOFF][1] = GetCurrentTime();
			m_dwCylWaitTime[READY_PUSHER_ONOFF][2] = m_dwCylWaitTime[READY_PUSHER_ONOFF][1] - m_dwCylWaitTime[READY_PUSHER_ONOFF][0];

			if (m_dwCylWaitTime[READY_PUSHER_ONOFF][2] <= 0)
			{
				m_dwCylWaitTime[READY_PUSHER_ONOFF][0] = GetCurrentTime();
				return RET_PROCEED;
			}
			if (m_dwCylWaitTime[READY_PUSHER_ONOFF][2] > (DWORD)st_wait_info.nLimitWaitTime[nWaitTime])
			{
				m_strCode.Format(_T("1401%d"),nOnOff);
				return RET_ERROR;
			}
		}
	}
	return nRet;
}

void CRun_Front_HeatSnk_Stacker::OnSet_WorkPos_StackerCylUpDn(int nUpDn)
{
	FAS_IO.set_out_bit(st_io_info.o_hs_Front_Work_stacker_updn,nUpDn);
	m_dwCylWaitTime[WORK_STACKER_UPDN][0] = GetCurrentTime();
	m_bCylinderFlag[WORK_STACKER_UPDN] = false;
}

int CRun_Front_HeatSnk_Stacker::OnGet_WorkPos_StackerCylUpDn(int nUpDn)
{
	int nWaitTime = WAIT_STACKER_UP_DN;
	int nRet = RET_PROCEED;
	if (nUpDn == IO_ON)
	{
		if (m_bCylinderFlag[WORK_STACKER_UPDN] == false && 
			FAS_IO.get_in_bit(st_io_info.i_hs_Front_Work_stacker_dn_chk, IO_ON) == IO_ON &&
			FAS_IO.get_in_bit(st_io_info.i_hs_Front_Work_stacker_up_chk, IO_OFF) == IO_OFF)
		{
			m_bCylinderFlag[WORK_STACKER_UPDN] = true;
			m_dwCylWaitTime[WORK_STACKER_UPDN][0] = GetCurrentTime();
		}
		else if (m_bCylinderFlag[WORK_STACKER_UPDN] == true &&
			FAS_IO.get_in_bit(st_io_info.i_hs_Front_Work_stacker_dn_chk, IO_ON) == IO_ON &&
			FAS_IO.get_in_bit(st_io_info.i_hs_Front_Work_stacker_up_chk, IO_OFF) == IO_OFF)
		{
			m_dwCylWaitTime[WORK_STACKER_UPDN][1] = GetCurrentTime();
			m_dwCylWaitTime[WORK_STACKER_UPDN][2] = m_dwCylWaitTime[WORK_STACKER_UPDN][1] - m_dwCylWaitTime[WORK_STACKER_UPDN][0];

			if (m_dwCylWaitTime[WORK_STACKER_UPDN][2] <= 0)
			{
				m_dwCylWaitTime[WORK_STACKER_UPDN][0] = GetCurrentTime();
				return RET_PROCEED;
			}
			if (m_dwCylWaitTime[WORK_STACKER_UPDN][2] > (DWORD)st_wait_info.nOnWaitTime[nWaitTime])
			{
				return RET_GOOD;
			}
		}
		else
		{
			m_dwCylWaitTime[WORK_STACKER_UPDN][1] = GetCurrentTime();
			m_dwCylWaitTime[WORK_STACKER_UPDN][2] = m_dwCylWaitTime[WORK_STACKER_UPDN][1] - m_dwCylWaitTime[WORK_STACKER_UPDN][0];

			if (m_dwCylWaitTime[WORK_STACKER_UPDN][2] <= 0)
			{
				m_dwCylWaitTime[WORK_STACKER_UPDN][0] = GetCurrentTime();
				return RET_PROCEED;
			}
			if (m_dwCylWaitTime[WORK_STACKER_UPDN][2] > (DWORD)st_wait_info.nLimitWaitTime[nWaitTime])
			{
				m_strCode.Format(_T("1401%d"),nUpDn);
				return RET_ERROR;
			}
		}
	}
	else //(nUpDn == IO_OFF)
	{
		if (m_bCylinderFlag[WORK_STACKER_UPDN] == false && 
			FAS_IO.get_in_bit(st_io_info.i_hs_Front_Work_stacker_dn_chk, IO_OFF) == IO_OFF &&
			FAS_IO.get_in_bit(st_io_info.i_hs_Front_Work_stacker_up_chk, IO_ON) == IO_ON)
		{
			m_bCylinderFlag[WORK_STACKER_UPDN] = true;
			m_dwCylWaitTime[WORK_STACKER_UPDN][0] = GetCurrentTime();
		}
		else if (m_bCylinderFlag[WORK_STACKER_UPDN] == true &&
			FAS_IO.get_in_bit(st_io_info.i_hs_Front_Work_stacker_dn_chk, IO_OFF) == IO_OFF &&
			FAS_IO.get_in_bit(st_io_info.i_hs_Front_Work_stacker_up_chk, IO_ON) == IO_ON)
		{
			m_dwCylWaitTime[WORK_STACKER_UPDN][1] = GetCurrentTime();
			m_dwCylWaitTime[WORK_STACKER_UPDN][2] = m_dwCylWaitTime[WORK_STACKER_UPDN][1] - m_dwCylWaitTime[WORK_STACKER_UPDN][0];

			if (m_dwCylWaitTime[WORK_STACKER_UPDN][2] <= 0)
			{
				m_dwCylWaitTime[WORK_STACKER_UPDN][0] = GetCurrentTime();
				return RET_PROCEED;
			}
			if (m_dwCylWaitTime[WORK_STACKER_UPDN][2] > (DWORD)st_wait_info.nOnWaitTime[nWaitTime])
			{
				return RET_GOOD;
			}
		}
		else
		{
			m_dwCylWaitTime[WORK_STACKER_UPDN][1] = GetCurrentTime();
			m_dwCylWaitTime[WORK_STACKER_UPDN][2] = m_dwCylWaitTime[WORK_STACKER_UPDN][1] - m_dwCylWaitTime[WORK_STACKER_UPDN][0];

			if (m_dwCylWaitTime[WORK_STACKER_UPDN][2] <= 0)
			{
				m_dwCylWaitTime[WORK_STACKER_UPDN][0] = GetCurrentTime();
				return RET_PROCEED;
			}
			if (m_dwCylWaitTime[WORK_STACKER_UPDN][2] > (DWORD)st_wait_info.nLimitWaitTime[nWaitTime])
			{
				m_strCode.Format(_T("1401%d"),nUpDn);
				return RET_ERROR;
			}
		}
	}
	return nRet;
}

void CRun_Front_HeatSnk_Stacker::OnSet_WorkPos_RailFwdBwdCyl(int nOnOff)
{
	FAS_IO.set_out_bit(st_io_info.o_hs_Front_Work_stacker_Left_rail_fwd_onoff,nOnOff);
	FAS_IO.set_out_bit(st_io_info.o_hs_Front_Work_stacker_Right_rail_fwd_onoff,nOnOff);

	FAS_IO.set_out_bit(st_io_info.o_hs_Front_Work_stacker_Left_rail_bwd_onoff,!nOnOff);
	FAS_IO.set_out_bit(st_io_info.o_hs_Front_Work_stacker_Right_rail_bwd_onoff,!nOnOff);

	m_dwCylWaitTime[WORK_RAIL_FWDBWD][0] = GetCurrentTime();
	m_bCylinderFlag[WORK_RAIL_FWDBWD] = false;
}

int CRun_Front_HeatSnk_Stacker::OnGet_WorkPos_RailFwdBwdCyl(int nOnOff)
{
	int nWaitTime = WAIT_STACKER_CYL_ON_OFF;
	int nRet = RET_PROCEED;
	if (nOnOff == IO_ON)
	{
		if (m_bCylinderFlag[WORK_RAIL_FWDBWD] ==  false && 
			FAS_IO.get_in_bit(st_io_info.i_hs_Front_Work_stacker_Left_rail_fwd_chk,IO_ON) == IO_ON &&
			FAS_IO.get_in_bit(st_io_info.i_hs_Front_Work_stacker_Left_rail_bwd_chk,IO_OFF) == IO_OFF &&
			FAS_IO.get_in_bit(st_io_info.i_hs_Front_Work_stacker_Right_rail_fwd_chk,IO_ON) == IO_ON &&
			FAS_IO.get_in_bit(st_io_info.i_hs_Front_Work_stacker_Right_rail_bwd_chk,IO_OFF) == IO_OFF)
		{
			m_bCylinderFlag[WORK_RAIL_FWDBWD] = true;
			m_dwCylWaitTime[WORK_RAIL_FWDBWD][0] = GetCurrentTime();
		}
		else if (m_bCylinderFlag[WORK_RAIL_FWDBWD] ==  true && 
			FAS_IO.get_in_bit(st_io_info.i_hs_Front_Work_stacker_Left_rail_fwd_chk,IO_ON) == IO_ON &&
			FAS_IO.get_in_bit(st_io_info.i_hs_Front_Work_stacker_Left_rail_bwd_chk,IO_OFF) == IO_OFF &&
			FAS_IO.get_in_bit(st_io_info.i_hs_Front_Work_stacker_Right_rail_fwd_chk,IO_ON) == IO_ON &&
			FAS_IO.get_in_bit(st_io_info.i_hs_Front_Work_stacker_Right_rail_bwd_chk,IO_OFF) == IO_OFF)
		{
			m_dwCylWaitTime[WORK_RAIL_FWDBWD][1] = GetCurrentTime();
			m_dwCylWaitTime[WORK_RAIL_FWDBWD][2] = m_dwCylWaitTime[WORK_RAIL_FWDBWD][1] - m_dwCylWaitTime[WORK_RAIL_FWDBWD][0];

			if (m_dwCylWaitTime[WORK_RAIL_FWDBWD][2] <= 0)
			{
				m_dwCylWaitTime[WORK_RAIL_FWDBWD][0] = GetCurrentTime();
				return RET_PROCEED;
			}
			if (m_dwCylWaitTime[WORK_RAIL_FWDBWD][2] > (DWORD)st_wait_info.nOnWaitTime[nWaitTime])
			{
				return RET_GOOD;
			}
		}
		else
		{
			m_dwCylWaitTime[WORK_RAIL_FWDBWD][1] = GetCurrentTime();
			m_dwCylWaitTime[WORK_RAIL_FWDBWD][2] = m_dwCylWaitTime[WORK_RAIL_FWDBWD][1] - m_dwCylWaitTime[WORK_RAIL_FWDBWD][0];

			if (m_dwCylWaitTime[WORK_RAIL_FWDBWD][2] <= 0)
			{
				m_dwCylWaitTime[WORK_RAIL_FWDBWD][0] = GetCurrentTime();
				return RET_PROCEED;
			}
			if (m_dwCylWaitTime[WORK_RAIL_FWDBWD][2] > (DWORD)st_wait_info.nLimitWaitTime[nWaitTime])
			{
				m_strCode.Format(_T("1401%d"),nOnOff);
				return RET_ERROR;
			}
		}
	}
	else //(nOnOff == IO_OFF)
	{
		if (m_bCylinderFlag[WORK_RAIL_FWDBWD] ==  false && 
			FAS_IO.get_in_bit(st_io_info.i_hs_Front_Work_stacker_Left_rail_fwd_chk,IO_OFF) == IO_OFF &&
			FAS_IO.get_in_bit(st_io_info.i_hs_Front_Work_stacker_Left_rail_bwd_chk,IO_ON) == IO_ON &&
			FAS_IO.get_in_bit(st_io_info.i_hs_Front_Work_stacker_Right_rail_fwd_chk,IO_OFF) == IO_OFF &&
			FAS_IO.get_in_bit(st_io_info.i_hs_Front_Work_stacker_Right_rail_bwd_chk,IO_ON) == IO_ON)
		{
			m_bCylinderFlag[WORK_RAIL_FWDBWD] = true;
			m_dwCylWaitTime[WORK_RAIL_FWDBWD][0] = GetCurrentTime();
		}
		else if (m_bCylinderFlag[WORK_RAIL_FWDBWD] ==  true && 
			FAS_IO.get_in_bit(st_io_info.i_hs_Front_Work_stacker_Left_rail_fwd_chk,IO_OFF) == IO_OFF &&
			FAS_IO.get_in_bit(st_io_info.i_hs_Front_Work_stacker_Left_rail_bwd_chk,IO_ON) == IO_ON &&
			FAS_IO.get_in_bit(st_io_info.i_hs_Front_Work_stacker_Right_rail_fwd_chk,IO_OFF) == IO_OFF &&
			FAS_IO.get_in_bit(st_io_info.i_hs_Front_Work_stacker_Right_rail_bwd_chk,IO_ON) == IO_ON)
		{
			m_dwCylWaitTime[WORK_RAIL_FWDBWD][1] = GetCurrentTime();
			m_dwCylWaitTime[WORK_RAIL_FWDBWD][2] = m_dwCylWaitTime[WORK_RAIL_FWDBWD][1] - m_dwCylWaitTime[WORK_RAIL_FWDBWD][0];

			if (m_dwCylWaitTime[WORK_RAIL_FWDBWD][2] <= 0)
			{
				m_dwCylWaitTime[WORK_RAIL_FWDBWD][0] = GetCurrentTime();
				return RET_PROCEED;
			}
			if (m_dwCylWaitTime[WORK_RAIL_FWDBWD][2] > (DWORD)st_wait_info.nOnWaitTime[nWaitTime])
			{
				return RET_GOOD;
			}
		}
		else
		{
			m_dwCylWaitTime[WORK_RAIL_FWDBWD][1] = GetCurrentTime();
			m_dwCylWaitTime[WORK_RAIL_FWDBWD][2] = m_dwCylWaitTime[WORK_RAIL_FWDBWD][1] - m_dwCylWaitTime[WORK_RAIL_FWDBWD][0];

			if (m_dwCylWaitTime[WORK_RAIL_FWDBWD][2] <= 0)
			{
				m_dwCylWaitTime[WORK_RAIL_FWDBWD][0] = GetCurrentTime();
				return RET_PROCEED;
			}
			if (m_dwCylWaitTime[WORK_RAIL_FWDBWD][2] > (DWORD)st_wait_info.nLimitWaitTime[nWaitTime])
			{
				m_strCode.Format(_T("1401%d"),nOnOff);
				return RET_ERROR;
			}
		}
	}
	return nRet;
}
void CRun_Front_HeatSnk_Stacker::OnSet_WorkPos_TrayClampCyl(int nOnOff)
{
	FAS_IO.set_out_bit(st_io_info.o_hs_Front_Work_stacker_guide_clamp_onoff,nOnOff);
	FAS_IO.set_out_bit(st_io_info.o_hs_Front_Work_stacker_guide_unclamp_onoff,!nOnOff);

	m_dwCylWaitTime[WORK_TRAY_CLAMP_ONOFF][0] = GetCurrentTime();
	m_bCylinderFlag[WORK_TRAY_CLAMP_ONOFF] = false;
}

int CRun_Front_HeatSnk_Stacker::OnGet_WorkPos_TrayClampCyl(int nOnOff)
{
	int nWaitTime = WAIT_STACKER_CYL_ON_OFF;
	int nRet = RET_PROCEED;
	if (nOnOff == IO_ON)
	{
		if (m_bCylinderFlag[WORK_TRAY_CLAMP_ONOFF] ==  false && 
			FAS_IO.get_in_bit(st_io_info.i_hs_Front_Work_stacker_guide_clamp_on_chk,IO_ON) == IO_ON &&
			FAS_IO.get_in_bit(st_io_info.i_hs_Front_Work_stacker_guide_unclamp_off_chk,IO_OFF) == IO_OFF)
		{
			m_bCylinderFlag[WORK_TRAY_CLAMP_ONOFF] = true;
			m_dwCylWaitTime[WORK_TRAY_CLAMP_ONOFF][0] = GetCurrentTime();
		}
		else if (m_bCylinderFlag[WORK_TRAY_CLAMP_ONOFF] ==  true && 
			FAS_IO.get_in_bit(st_io_info.i_hs_Front_Work_stacker_guide_clamp_on_chk,IO_ON) == IO_ON &&
			FAS_IO.get_in_bit(st_io_info.i_hs_Front_Work_stacker_guide_unclamp_off_chk,IO_OFF) == IO_OFF)
		{
			m_dwCylWaitTime[WORK_TRAY_CLAMP_ONOFF][1] = GetCurrentTime();
			m_dwCylWaitTime[WORK_TRAY_CLAMP_ONOFF][2] = m_dwCylWaitTime[WORK_TRAY_CLAMP_ONOFF][1] - m_dwCylWaitTime[WORK_TRAY_CLAMP_ONOFF][0];

			if (m_dwCylWaitTime[WORK_TRAY_CLAMP_ONOFF][2] <= 0)
			{
				m_dwCylWaitTime[WORK_TRAY_CLAMP_ONOFF][0] = GetCurrentTime();
				return RET_PROCEED;
			}
			if (m_dwCylWaitTime[WORK_TRAY_CLAMP_ONOFF][2] > (DWORD)st_wait_info.nOnWaitTime[nWaitTime])
			{
				return RET_GOOD;
			}
		}
		else
		{
			m_dwCylWaitTime[WORK_TRAY_CLAMP_ONOFF][1] = GetCurrentTime();
			m_dwCylWaitTime[WORK_TRAY_CLAMP_ONOFF][2] = m_dwCylWaitTime[WORK_TRAY_CLAMP_ONOFF][1] - m_dwCylWaitTime[WORK_TRAY_CLAMP_ONOFF][0];

			if (m_dwCylWaitTime[WORK_TRAY_CLAMP_ONOFF][2] <= 0)
			{
				m_dwCylWaitTime[WORK_TRAY_CLAMP_ONOFF][0] = GetCurrentTime();
				return RET_PROCEED;
			}
			if (m_dwCylWaitTime[WORK_TRAY_CLAMP_ONOFF][2] > (DWORD)st_wait_info.nLimitWaitTime[nWaitTime])
			{
				m_strCode.Format(_T("1401%d"),nOnOff);
				return RET_ERROR;
			}
		}
	}
	else //(nOnOff == IO_OFF)
	{
		if (m_bCylinderFlag[WORK_TRAY_CLAMP_ONOFF] ==  false && 
			FAS_IO.get_in_bit(st_io_info.i_hs_Front_Work_stacker_guide_clamp_on_chk,IO_OFF) == IO_OFF &&
			FAS_IO.get_in_bit(st_io_info.i_hs_Front_Work_stacker_guide_unclamp_off_chk,IO_ON) == IO_ON)

		{
			m_bCylinderFlag[WORK_TRAY_CLAMP_ONOFF] = true;
			m_dwCylWaitTime[WORK_TRAY_CLAMP_ONOFF][0] = GetCurrentTime();
		}
		else if (m_bCylinderFlag[WORK_TRAY_CLAMP_ONOFF] ==  true && 
			FAS_IO.get_in_bit(st_io_info.i_hs_Front_Work_stacker_guide_clamp_on_chk,IO_OFF) == IO_OFF &&
			FAS_IO.get_in_bit(st_io_info.i_hs_Front_Work_stacker_guide_unclamp_off_chk,IO_ON) == IO_ON)
		{
			m_dwCylWaitTime[WORK_TRAY_CLAMP_ONOFF][1] = GetCurrentTime();
			m_dwCylWaitTime[WORK_TRAY_CLAMP_ONOFF][2] = m_dwCylWaitTime[WORK_TRAY_CLAMP_ONOFF][1] - m_dwCylWaitTime[WORK_TRAY_CLAMP_ONOFF][0];

			if (m_dwCylWaitTime[WORK_TRAY_CLAMP_ONOFF][2] <= 0)
			{
				m_dwCylWaitTime[WORK_TRAY_CLAMP_ONOFF][0] = GetCurrentTime();
				return RET_PROCEED;
			}
			if (m_dwCylWaitTime[WORK_TRAY_CLAMP_ONOFF][2] > (DWORD)st_wait_info.nOnWaitTime[nWaitTime])
			{
				return RET_GOOD;
			}
		}
		else
		{
			m_dwCylWaitTime[WORK_TRAY_CLAMP_ONOFF][1] = GetCurrentTime();
			m_dwCylWaitTime[WORK_TRAY_CLAMP_ONOFF][2] = m_dwCylWaitTime[WORK_TRAY_CLAMP_ONOFF][1] - m_dwCylWaitTime[WORK_TRAY_CLAMP_ONOFF][0];

			if (m_dwCylWaitTime[WORK_TRAY_CLAMP_ONOFF][2] <= 0)
			{
				m_dwCylWaitTime[WORK_TRAY_CLAMP_ONOFF][0] = GetCurrentTime();
				return RET_PROCEED;
			}
			if (m_dwCylWaitTime[WORK_TRAY_CLAMP_ONOFF][2] > (DWORD)st_wait_info.nLimitWaitTime[nWaitTime])
			{
				m_strCode.Format(_T("1401%d"),nOnOff);
				return RET_ERROR;
			}
		}
	}
	return nRet;
}


