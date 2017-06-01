// Run_Rear_HeatSnk_Rbt.cpp : 구현 파일입니다.
//

#include "stdafx.h"
#include "Handler.h"
#include "Run_Rear_HeatSnk_Rbt.h"
#include "Variable.h"
#include "CtlBd_Library.h"
#include "ComizoaPublic.h"
#include "CtlBd_Variable.h"
#include "PublicFunction.h"
#include "FastechPublic_IO.h"

// CRun_Rear_HeatSnk_Rbt
CRun_Rear_HeatSnk_Rbt clsRunHsRearRbt;
CRun_Rear_HeatSnk_Rbt::CRun_Rear_HeatSnk_Rbt()
{
	m_nAxisNum_Z = M_HS_R_RBT_Z;
	m_nAxisNum_Y = M_HS_R_RBT_Y;
	m_nInitStep = -1;
	m_nTray_Dvc_Cnt = 0;
}

CRun_Rear_HeatSnk_Rbt::~CRun_Rear_HeatSnk_Rbt()
{
}
void CRun_Rear_HeatSnk_Rbt::ThreadRun()
{

}
void CRun_Rear_HeatSnk_Rbt::OnRunInit()
{

	int nRet_1;

	if (st_sync_info.nInit_Flag[THD_HS_REAR_RBT] != INIT_CLEAR)		return;	

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
			m_nPicker[i] = YES;
			OnSetPickerOnOff(IO_OFF,m_nPicker);
		}
		m_nInitStep = 200;
		break;

	case 200:
		nRet_1 = OnGetPickerOnOff(IO_OFF,m_nPicker);
		if(nRet_1 == RET_GOOD)
		{
			m_nInitStep = 300;
		}
		else if(nRet_1 == RET_ERROR)
		{
			CTL_Lib.Alarm_Error_Occurrence(200, CTL_dWARNING,m_strAlarmCode);
		}
		break;

	case 300:
		for (int i = 0; i<MAX_PICKER; i++)
		{
			m_nPicker[i] = YES;
			OnSetPickerUpDn(IO_OFF,m_nPicker);
		}
		m_nInitStep = 400;
		break;

	case 400:
		nRet_1 = OnGetPickerUpDn(IO_OFF,m_nPicker);
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
			if(FAS_IO.get_in_bit(st_io_info.i_hs_Rear_rbt_picker_gripper_dvc_chk[i], IO_ON) == IO_ON)
			{
				m_strAlarmCode.Format(_T("8%d%04d"), IO_OFF, st_io_info.i_hs_Rear_rbt_picker_gripper_dvc_chk); 
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
		nRet_1 = CTL_Lib.Single_Move(BOTH_MOVE_FINISH, m_nAxisNum_Z, st_motor_info[m_nAxisNum_Z].d_pos[P_WORKROBOT_SAFETY], COMI.mn_runspeed_rate);

		if (nRet_1 == RET_GOOD)
		{
			m_nInitStep = 1400;
		}
		else if (nRet_1 == BD_RETRY)
		{
			m_nInitStep = 1300;
		}
		else if (nRet_1 == BD_ERROR || nRet_1 == BD_SAFETY)
		{
			CTL_Lib.Alarm_Error_Occurrence(200, CTL_dWARNING,m_strAlarmCode);
		}
		break;

	case 1400:
		nRet_1 = CTL_Lib.Single_Move(BOTH_MOVE_FINISH, m_nAxisNum_Y, st_motor_info[m_nAxisNum_Y].d_pos[P_WORKROBOT_SAFETY], COMI.mn_runspeed_rate);

		if (nRet_1 == RET_GOOD)
		{
			m_nInitStep = 1500;
		}
		else if (nRet_1 == BD_RETRY)
		{
			m_nInitStep = 800;
		}
		else if (nRet_1 == BD_ERROR || nRet_1 == BD_SAFETY)
		{
			CTL_Lib.Alarm_Error_Occurrence(200, CTL_dWARNING,m_strAlarmCode);
		}
		break;


	case 1500:
		st_sync_info.nInit_Flag[THD_HS_REAR_RBT] = INIT_READY; 
		m_nInitStep = 0;
		break;	

	default :
		break;

	}

}

void CRun_Rear_HeatSnk_Rbt::OnRunMove()
{

}

void CRun_Rear_HeatSnk_Rbt::OnSetPickerOnOff(int nOnOff, int *nPickerInfo)
{
	int nNum = 2;

	for (int i =0; i<nNum; i++)
	{
		if (nPickerInfo[i] == YES)
		{
			FAS_IO.set_out_bit(st_io_info.o_hs_Rear_rbt_picker_gripper_onoff[i],nOnOff);
		}
		dwPickerOnOffWaitTime[i][0] = GetCurrentTime();
		m_bPickerOnOffFlag[i] = false;
	}
}

int CRun_Rear_HeatSnk_Rbt::OnGetPickerOnOff(int nOnOff, int *nPickerInfo)
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
			else
			{
				dwPickerOnOffWaitTime[i][1] = GetCurrentTime();
				dwPickerOnOffWaitTime[i][2] = dwPickerOnOffWaitTime[i][1] - dwPickerOnOffWaitTime[i][0];

				if (dwPickerOnOffWaitTime[i][2] <= 0)
				{
					dwPickerOnOffWaitTime[i][0] = GetCurrentTime();
					return RET_PROCEED;
				}
				if (dwPickerOnOffWaitTime[i][2] > (DWORD)st_wait_info.nLimitWaitTime[nWaitTime])
				{
					m_strAlarmCode.Format(_T("8%d%04d"), IO_OFF, st_io_info.o_hs_Rear_rbt_picker_gripper_onoff[i]); 
					return RET_ERROR;
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
			else
			{
				dwPickerOnOffWaitTime[i][1] = GetCurrentTime();
				dwPickerOnOffWaitTime[i][2] = dwPickerOnOffWaitTime[i][1] - dwPickerOnOffWaitTime[i][0];

				if (dwPickerOnOffWaitTime[i][2] <= 0)
				{
					dwPickerOnOffWaitTime[i][0] = GetCurrentTime();
					return RET_PROCEED;
				}
				if (dwPickerOnOffWaitTime[i][2] > (DWORD)st_wait_info.nLimitWaitTime[nWaitTime])
				{
					m_strAlarmCode.Format(_T("8%d%04d"), IO_OFF, st_io_info.o_hs_Rear_rbt_picker_gripper_onoff[i]); 
					return RET_ERROR;
				}
			}
		}
	}
	return nRet;
}
int CRun_Rear_HeatSnk_Rbt::nRobotPickPlace(int nMode, int *nPickerInfo)
{
	int nRect = RET_PROCEED;

	return nRect;
}
int CRun_Rear_HeatSnk_Rbt::nWorkBufferPlacePos(int nPos)
{
	int nRect;
	if(nPos == WORK_BUFFER_1)
	{
		nRect = P_WORKROBOT_WORK_BUFF_1_POS;
	}
	else if(nPos == WORK_BUFFER_2)
	{
		nRect = P_WORKROBOT_WORK_BUFF_2_POS;
	}
	else if(nPos == WORK_BUFFER_3)
	{
		nRect = P_WORKROBOT_WORK_BUFF_3_POS;
	} 
	else if(nPos == WORK_BUFFER_4)
	{
		nRect = P_WORKROBOT_WORK_BUFF_4_POS;
	}	
	else
	{

	}
	return nRect;
}
void CRun_Rear_HeatSnk_Rbt::OnSetPickerUpDn(int nOnOff, int *nPickerInfo)
{
	int nNum = 2;

	for (int i =0; i<nNum; i++)
	{
		if (nPickerInfo[i] == YES)
		{
			FAS_IO.set_out_bit(st_io_info.o_hs_Rear_rbt_picker_updn[i],nOnOff);
		}
		dwPickerUpDnWaitTime[i][0] = GetCurrentTime();
		m_bPickerUpDnFlag[i] = false;
	}
}

int CRun_Rear_HeatSnk_Rbt::OnGetPickerUpDn(int nOnOff, int *nPickerInfo)
{
	int nRet = RET_PROCEED;
	int nWaitTime = WAIT_PICKER_UP_DN;

	for (int i = 0; i<MAX_PICKER; i++)
	{
		if (nOnOff == IO_ON)
		{
			if (m_bPickerUpDnFlag[i] == false && 
				FAS_IO.get_in_bit(st_io_info.i_hs_Rear_rbt_picker_dn_chk[i], IO_ON) == IO_ON &&
				FAS_IO.get_in_bit(st_io_info.i_hs_Rear_rbt_picker_up_chk[i], IO_OFF) == IO_OFF)
			{
				dwPickerUpDnWaitTime[i][0] = GetCurrentTime();
				m_bPickerUpDnFlag[i] = true;
			}
			else if (m_bPickerUpDnFlag[i] == true && 
				FAS_IO.get_in_bit(st_io_info.i_hs_Rear_rbt_picker_dn_chk[i], IO_ON) == IO_ON &&
				FAS_IO.get_in_bit(st_io_info.i_hs_Rear_rbt_picker_up_chk[i], IO_OFF) == IO_OFF)
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

					m_strAlarmCode.Format(_T("8%d%04d"), nOnOff, st_io_info.i_hs_Rear_rbt_picker_dn_chk); 
					return RET_ERROR;
				}
			}
		}
		else
		{
			if (m_bPickerUpDnFlag[i] == false && 
				FAS_IO.get_in_bit(st_io_info.i_hs_Rear_rbt_picker_dn_chk[i], IO_OFF) == IO_OFF &&
				FAS_IO.get_in_bit(st_io_info.i_hs_Rear_rbt_picker_up_chk[i], IO_ON) == IO_ON)
			{
				dwPickerUpDnWaitTime[i][0] = GetCurrentTime();
				m_bPickerUpDnFlag[i] = true;
			}
			else if (m_bPickerUpDnFlag[i] == true && 
				FAS_IO.get_in_bit(st_io_info.i_hs_Rear_rbt_picker_dn_chk[i], IO_OFF) == IO_OFF &&
				FAS_IO.get_in_bit(st_io_info.i_hs_Rear_rbt_picker_up_chk[i], IO_ON) == IO_ON)
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
					m_strAlarmCode.Format(_T("8%d%04d"), nOnOff, st_io_info.i_hs_Rear_rbt_picker_up_chk); 
					return RET_ERROR;
				}
			}
		}
	}
	return nRet;
}