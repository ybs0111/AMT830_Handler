#include "StdAfx.h"
#include "Run_Front_HeatSnk_Rbt.h"
#include "Variable.h"
#include "CtlBd_Library.h"
#include "ComizoaPublic.h"
#include "CtlBd_Variable.h"
#include "PublicFunction.h"
#include "FastechPublic_IO.h"



CRun_Front_HeatSnk_Rbt clsRunHsFrontRbt;
CRun_Front_HeatSnk_Rbt::CRun_Front_HeatSnk_Rbt(void)
{
	m_nAxisNum_Z = M_HS_F_RBT_Z;
	m_nAxisNum_Y = M_HS_F_RBT_Y;
	m_nInitStep = -1;
}


CRun_Front_HeatSnk_Rbt::~CRun_Front_HeatSnk_Rbt(void)
{
}
void CRun_Front_HeatSnk_Rbt::ThreadRun()
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

void CRun_Front_HeatSnk_Rbt::OnRunInit()
{

	int nRet_1;
	int nPicker[2] = {0,};
	if (st_sync_info.nInit_Flag[THD_HS_FRONT_RBT] != INIT_CLEAR)		return;	

	switch (m_nInitStep)
	{
	case -1:

		m_nInitStep = 0;
		break;

	case 0:		

		m_nInitStep = 100;
		break;

	case 100: 
		for (int i = 0; i<MAX_PICKER; i++)
		{
			nPicker[i] = YES;
			OnSetPickerOnOff(IO_OFF,nPicker);
		}
		m_nInitStep = 200;
		break;

	case 200:
		nRet_1 = OnGetPickerOnOff(IO_OFF,nPicker);
		if (nRet_1 == RET_GOOD)
		{
			m_nInitStep = 300;
		}
		break;

	case 300:
		for (int i = 0; i<MAX_PICKER; i++)
		{
			nPicker[i] = YES;
			OnSetPickerUpDn(IO_OFF,nPicker);
		}
		m_nInitStep = 400;
		break;

	case 400:
		nRet_1 = OnGetPickerUpDn(IO_OFF,nPicker);
		if (nRet_1 == RET_GOOD)
		{
			m_nInitStep = 1000;
		}
		else if (nRet_1 == RET_ERROR)
		{
			CTL_Lib.Alarm_Error_Occurrence(5, CTL_dWARNING, m_strAlarmCode);
			m_nInitStep = 300;
		}
		break;

	case 1000:
		nRet_1 = COMI.HomeCheck_Mot(m_nAxisNum_Z, MOT_SENS_ELM, MOT_TIMEOUT);
		if(nRet_1 == BD_GOOD)
		{
			COMI.mn_homechk_flag[m_nAxisNum_Z] = CTL_YES;
			m_nInitStep = 1100;
		}
		else if(nRet_1 == BD_ERROR)
		{
			CTL_Lib.Alarm_Error_Occurrence(10, CTL_dWARNING, COMI.m_strCode);
			m_nInitStep = 300;
		}	
		break;

	case 1100:
		nRet_1 = RET_GOOD;
		for (int i = 0; i<MAX_PICKER; i++)
		{
			if(FAS_IO.get_in_bit(st_io_info.i_hs_Front_rbt_picker_gripper_dvc_chk[i], IO_ON) == IO_OFF)
			{
				//410600 1 41 "Forward Heat Sink Picker #1 Module Off Check Error.[PS0400]."
				m_strAlarmCode.Format(_T("41060%d"),i);
				CTL_Lib.Alarm_Error_Occurrence(1100, CTL_dWARNING,m_strAlarmCode);
				nRet_1 = RET_ERROR;
				break;
			}
		}
		if (nRet_1 == RET_GOOD)
		{
			m_nInitStep = 1200;
		}
		break;

	case 1200:
		nRet_1 = COMI.HomeCheck_Mot(m_nAxisNum_Y, MOT_SENS_ELM, MOT_TIMEOUT);
		if(nRet_1 == BD_GOOD)
		{
			COMI.mn_homechk_flag[m_nAxisNum_Y] = CTL_YES;
			m_nInitStep = 1300;
		}
		else if(nRet_1 == BD_ERROR)
		{
			CTL_Lib.Alarm_Error_Occurrence(10, CTL_dWARNING, COMI.m_strCode);
		}	
		break;

	case 1300:
		st_sync_info.nInit_Flag[THD_HS_FRONT_RBT] = INIT_READY; 
		m_nInitStep = 0;
		break;	

	default :
		break;

	}
}

void CRun_Front_HeatSnk_Rbt::OnRunMove()
{
	switch(m_nRunStep)
	{
	case 0:
		m_nRunStep = 100;
		break;

	}
}

void CRun_Front_HeatSnk_Rbt::OnSetPickerOnOff(int nOnOff, int *nPickerInfo)
{
	int nNum = 2;

	for (int i =0; i<nNum; i++)
	{
		if (nPickerInfo[i] == YES)
		{
			FAS_IO.set_out_bit(st_io_info.o_hs_Front_rbt_picker_gripper_onoff[i],nOnOff);
		}
		dwPickerOnOffWaitTime[i][0] = GetCurrentTime();
		m_bPickerOnOffFlag[i] = false;
	}
}

int CRun_Front_HeatSnk_Rbt::OnGetPickerOnOff(int nOnOff, int *nPickerInfo)
{
	int nRet = RET_PROCEED;
	int nWaitTime = WAIT_PICKER_ON_OFF;

	for (int i = 0; i<MAX_PICKER; i++)
	{
		if (nOnOff == IO_ON)
		{
			if (m_bPickerOnOffFlag[i] == false)
			{
				dwPickerOnOffWaitTime[i][0] = GetCurrentTime();
				m_bPickerOnOffFlag[i] = true;
			}
			else if (m_bPickerOnOffFlag[i] == true)
			{
				dwPickerOnOffWaitTime[i][1] = GetCurrentTime();
				dwPickerOnOffWaitTime[i][2] = dwPickerOnOffWaitTime[i][1] - dwPickerOnOffWaitTime[i][0];

				if (dwPickerOnOffWaitTime[i][2] <= 0)
				{
					dwPickerOnOffWaitTime[i][0] = GetCurrentTime();
					return RET_PROCEED;
				}
				if (dwPickerOnOffWaitTime[i][2] > (DWORD)st_wait_info.nOnWaitTime[nWaitTime])
				{
					return RET_GOOD;
				}
			}
		}
		else
		{
			if (m_bPickerOnOffFlag[i] == false)
			{
				dwPickerOnOffWaitTime[i][0] = GetCurrentTime();
				m_bPickerOnOffFlag[i] = true;
			}
			else if (m_bPickerOnOffFlag[i] == true)
			{
				dwPickerOnOffWaitTime[i][1] = GetCurrentTime();
				dwPickerOnOffWaitTime[i][2] = dwPickerOnOffWaitTime[i][1] - dwPickerOnOffWaitTime[i][0];

				if (dwPickerOnOffWaitTime[i][2] <= 0)
				{
					dwPickerOnOffWaitTime[i][0] = GetCurrentTime();
					return RET_PROCEED;
				}
				if (dwPickerOnOffWaitTime[i][2] > (DWORD)st_wait_info.nOnWaitTime[nWaitTime])
				{
					return RET_GOOD;
				}
			}
		}
	}
	return nRet;
}

void CRun_Front_HeatSnk_Rbt::OnSetPickerUpDn(int nOnOff, int *nPickerInfo)
{
	int nNum = 2;

	for (int i =0; i<nNum; i++)
	{
		if (nPickerInfo[i] == YES)
		{
			FAS_IO.set_out_bit(st_io_info.o_hs_Front_rbt_picker_updn[i],nOnOff);
		}
		dwPickerUpDnWaitTime[i][0] = GetCurrentTime();
		m_bPickerUpDnFlag[i] = false;
	}
}

int CRun_Front_HeatSnk_Rbt::OnGetPickerUpDn(int nOnOff, int *nPickerInfo)
{
	int nRet = RET_PROCEED;
	int nWaitTime = WAIT_PICKER_UP_DN;

	for (int i = 0; i<MAX_PICKER; i++)
	{
		if (nOnOff == IO_ON)
		{
			if (m_bPickerUpDnFlag[i] == false && 
				FAS_IO.get_in_bit(st_io_info.i_hs_Front_rbt_picker_dn_chk[i], IO_ON) == IO_ON &&
				 FAS_IO.get_in_bit(st_io_info.i_hs_Front_rbt_picker_up_chk[i], IO_OFF) == IO_OFF)
			{
				dwPickerUpDnWaitTime[i][0] = GetCurrentTime();
				m_bPickerUpDnFlag[i] = true;
			}
			else if (m_bPickerUpDnFlag[i] == true && 
				FAS_IO.get_in_bit(st_io_info.i_hs_Front_rbt_picker_dn_chk[i], IO_ON) == IO_ON &&
				FAS_IO.get_in_bit(st_io_info.i_hs_Front_rbt_picker_up_chk[i], IO_OFF) == IO_OFF)
			{
				dwPickerUpDnWaitTime[i][1] = GetCurrentTime();
				dwPickerUpDnWaitTime[i][2] = dwPickerUpDnWaitTime[i][1] - dwPickerUpDnWaitTime[i][0];

				if (dwPickerUpDnWaitTime[i][2] <= 0)
				{
					dwPickerUpDnWaitTime[i][0] = GetCurrentTime();
					return RET_PROCEED;
				}
				if (dwPickerUpDnWaitTime[i][2] > (DWORD)st_wait_info.nOnWaitTime[nWaitTime])
				{
					return RET_GOOD;
				}
			}
			else
			{
				dwPickerUpDnWaitTime[i][1] = GetCurrentTime();
				dwPickerUpDnWaitTime[i][2] = dwPickerUpDnWaitTime[i][1] - dwPickerUpDnWaitTime[i][0];

				if (dwPickerUpDnWaitTime[i][2] <= 0)
				{
					dwPickerUpDnWaitTime[i][0] = GetCurrentTime();
					return RET_PROCEED;
				}
				if (dwPickerUpDnWaitTime[i][2] > (DWORD)st_wait_info.nLimitWaitTime[nWaitTime])
				{
					m_strAlarmCode.Format(_T("1401%d"),nOnOff);
					return RET_ERROR;
				}
			}
		}
		else
		{
			if (m_bPickerUpDnFlag[i] == false && 
				FAS_IO.get_in_bit(st_io_info.i_hs_Front_rbt_picker_dn_chk[i], IO_OFF) == IO_OFF &&
				FAS_IO.get_in_bit(st_io_info.i_hs_Front_rbt_picker_up_chk[i], IO_ON) == IO_ON)
			{
				dwPickerUpDnWaitTime[i][0] = GetCurrentTime();
				m_bPickerUpDnFlag[i] = true;
			}
			else if (m_bPickerUpDnFlag[i] == true && 
				FAS_IO.get_in_bit(st_io_info.i_hs_Front_rbt_picker_dn_chk[i], IO_OFF) == IO_OFF &&
				FAS_IO.get_in_bit(st_io_info.i_hs_Front_rbt_picker_up_chk[i], IO_ON) == IO_ON)
			{
				dwPickerUpDnWaitTime[i][1] = GetCurrentTime();
				dwPickerUpDnWaitTime[i][2] = dwPickerUpDnWaitTime[i][1] - dwPickerUpDnWaitTime[i][0];

				if (dwPickerUpDnWaitTime[i][2] <= 0)
				{
					dwPickerUpDnWaitTime[i][0] = GetCurrentTime();
					return RET_PROCEED;
				}
				if (dwPickerUpDnWaitTime[i][2] > (DWORD)st_wait_info.nOnWaitTime[nWaitTime])
				{
					return RET_GOOD;
				}
			}
			else
			{
				dwPickerUpDnWaitTime[i][1] = GetCurrentTime();
				dwPickerUpDnWaitTime[i][2] = dwPickerUpDnWaitTime[i][1] - dwPickerUpDnWaitTime[i][0];

				if (dwPickerUpDnWaitTime[i][2] <= 0)
				{
					dwPickerUpDnWaitTime[i][0] = GetCurrentTime();
					return RET_PROCEED;
				}
				if (dwPickerUpDnWaitTime[i][2] > (DWORD)st_wait_info.nLimitWaitTime[nWaitTime])
				{
					m_strAlarmCode.Format(_T("1401%d"),nOnOff);
					return RET_ERROR;
				}
			}
		}
	}
	return nRet;
}