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

//kwlee 2017.0611
void CRun_Rear_HeatSnk_Rbt::OnRunMove()
{
	int nCnt,nPicker[2] = {0,};
	int nRet = 0;
	int nWorkBuff;
	bool bLast_Pick;
	double m_dPos;

	switch(m_nRunStep)
	{
	case 0:
		m_nRunStep = 100;
		break;

	case 100:
		if (st_lot_info[LOT_CURR].nLotStatus == LOT_START)
		{
			m_nRunStep = 200;
		}
		break;

	case 200:
		nRet = RET_GOOD;
		for (int i = 0; i<MAX_PICKER; i++)
		{
			if(FAS_IO.get_in_bit(st_io_info.i_hs_Rear_rbt_picker_gripper_dvc_chk[i], IO_ON) == IO_ON)
			{
				m_strAlarmCode.Format(_T("8%d%04d"), IO_OFF, st_io_info.i_hs_Rear_rbt_picker_gripper_dvc_chk[i]); 
				CTL_Lib.Alarm_Error_Occurrence(100, CTL_dWARNING,m_strAlarmCode);
				nRet = RET_ERROR;
				break;
			}
		}
		if (nRet == RET_GOOD)
		{
			m_nRunStep = 300;
		}
		break;

	case 300:
		for (int i = 0; i<MAX_PICKER; i++)
		{
			m_nPicker[i] = YES;
			OnSetPickerOnOff(IO_OFF,m_nPicker);
		}
		m_nRunStep = 400;
		break;

	case 400:
		nRet = OnGetPickerOnOff(IO_OFF,m_nPicker);
		if (nRet == RET_GOOD)
		{
			m_nRunStep = 500;
		}
		else if(nRet == RET_ERROR)
		{
			CTL_Lib.Alarm_Error_Occurrence(200, CTL_dWARNING,m_strAlarmCode);
			m_nRunStep = 300;
		}
		break;

	case 500:
		for (int i = 0; i<MAX_PICKER; i++)
		{
			m_nPicker[i] = YES;
			OnSetPickerUpDn(IO_OFF,m_nPicker);
			m_nRunStep = 600;
		}
		break;

	case 600:
		nRet = OnGetPickerUpDn(IO_OFF,m_nPicker);

		if (nRet == RET_GOOD)
		{
			m_nRunStep = 700;
		}
		else if (nRet == RET_ERROR)
		{
			CTL_Lib.Alarm_Error_Occurrence(300, CTL_dWARNING,m_strAlarmCode);
			m_nRunStep = 500;
		}
		break;

	case 700:
		nRet = CTL_Lib.Single_Move(BOTH_MOVE_FINISH, m_nAxisNum_Z, st_motor_info[m_nAxisNum_Z].d_pos[P_WORKROBOT_SAFETY], COMI.mn_runspeed_rate);

		if (nRet == RET_GOOD)
		{
			m_nRunStep = 800;
		}
		else if (nRet == BD_RETRY)
		{
			m_nRunStep = 700;
		}
		else if (nRet == BD_ERROR || nRet == BD_SAFETY)
		{
			CTL_Lib.Alarm_Error_Occurrence(400, CTL_dWARNING,m_strAlarmCode);
		}
		break;

	case 800:
		nRet = CTL_Lib.Single_Move(BOTH_MOVE_FINISH, m_nAxisNum_Y, st_motor_info[m_nAxisNum_Y].d_pos[P_WORKROBOT_SAFETY], COMI.mn_runspeed_rate);

		if (nRet == RET_GOOD)
		{
			m_nRunStep = 1000;
		}
		else if (nRet == BD_RETRY)
		{
			m_nRunStep = 800;
		}
		else if (nRet == BD_ERROR || nRet == BD_SAFETY)
		{
			CTL_Lib.Alarm_Error_Occurrence(500, CTL_dWARNING,m_strAlarmCode);
		}
		break;

		//Buffer에서 요청
	case 1000:
		m_nBufferNum = -1;
		for (int i = 0; i<MAX_BUFFER_SITE; i++)
		{
			if (st_sync_info.nShiftWork_Rbt[i] == CTL_REQ)
			{
				m_nBufferNum = i;
				m_nRunStep = 1100;
				break;
			}
		}

		if (m_nRunStep == -1)
		{
			break;
		}
		break;

		//Tray 있고 Picker Pick 가능 시 Stacker에 요청.
	case 1100:
		nCnt = 0;
		for (int i = 0; i< MAX_PICKER; i++)
		{
			if (FAS_IO.get_in_bit(st_io_info.i_hs_Rear_rbt_picker_gripper_dvc_chk[i],IO_OFF) == IO_OFF)
			{
				nCnt++;
			}
		}

		if (FAS_IO.get_in_bit(st_io_info.i_hs_Rear_Work_stacker_tray_chk,IO_ON) == IO_ON && nCnt > 0)
		{
			//st_sync_info.nWorkRobot[THD_HS_FRONT_STACKER_SITE][STACKER_WORK_POS] = CTL_REQ;
			//kwlee 2017.0605
			st_sync_info.nRearHsRbt = CTL_REQ;
			m_nRunStep = 1300;
		}
		break;

	case 1300:
		//if (st_sync_info.nWorkRobot[THD_HS_FRONT_STACKER_SITE][STACKER_WORK_POS] == CTL_READY) //Stacker 준비 완료 
		//kwlee 2017.0605
		if (st_sync_info.nRearHsRbt == CTL_READY)
		{
			m_nRunStep = 1400;
		}
		break;


	case 1400:
		m_dPos = st_motor_info[m_nAxisNum_Y].d_pos[P_WORKROBOT_WORK_POS] - (m_dTray_Gap * m_nTray_Dvc_Cnt);
		nRet = CTL_Lib.Single_Move(BOTH_MOVE_FINISH, m_nAxisNum_Y,m_dPos , COMI.mn_runspeed_rate);

		if (nRet == RET_GOOD)
		{
			m_nRunStep = 1500;
		}
		else if (nRet == BD_RETRY)
		{
			m_nRunStep = 1400;
		}
		else if (nRet == BD_ERROR || nRet == BD_SAFETY)
		{
			CTL_Lib.Alarm_Error_Occurrence(600, CTL_dWARNING,m_strAlarmCode);
		}
		break;

	case 1500:
		m_nPicker[m_nPick_Cnt] = YES;
		OnSetPickerUpDn(IO_ON,m_nPicker);
		m_nRunStep = 1600;
		break;

	case 1600:
		nRet = OnGetPickerUpDn(IO_ON,m_nPicker);
		if (nRet == RET_GOOD)
		{
			m_nRunStep = 1700;
		}
		else if(nRet == RET_ERROR)
		{
			CTL_Lib.Alarm_Error_Occurrence(700, CTL_dWARNING,m_strAlarmCode);
			m_nRunStep = 1500;
		}
		break;

	case 1700:
		nRet = CTL_Lib.Single_Move(BOTH_MOVE_FINISH, m_nAxisNum_Z,st_motor_info[m_nAxisNum_Z].d_pos[P_WORKROBOT_WORK_POS] , COMI.mn_runspeed_rate);
		if (nRet == RET_GOOD)
		{
			m_nRunStep = 1800;
		}
		else if (nRet == BD_RETRY)
		{
			m_nRunStep = 1700;
		}
		else if (nRet == BD_ERROR || nRet == BD_SAFETY)
		{
			CTL_Lib.Alarm_Error_Occurrence(800, CTL_dWARNING,m_strAlarmCode);
		}
		break;

	case 1800:
		OnSetPickerOnOff(IO_ON,m_nPicker);
		m_nRunStep = 1900;
		break;

	case 1900:
		nRet = OnGetPickerOnOff(IO_ON,m_nPicker);
		if (nRet == RET_GOOD)
		{
			m_nRunStep = 2000;
		}
		else if (nRet == RET_ERROR)
		{
			CTL_Lib.Alarm_Error_Occurrence(1000, CTL_dWARNING,m_strAlarmCode);
			m_nRunStep = 1800;
		}
		break;

	case 2000:
		OnSetPickerUpDn(IO_OFF,m_nPicker);
		m_nRunStep = 2100;
		break;

	case 2100:
		nRet = OnGetPickerUpDn(IO_OFF,m_nPicker);
		if (nRet == RET_GOOD)
		{
			m_nRunStep = 2200;
		}
		else if(nRet == RET_ERROR)
		{
			CTL_Lib.Alarm_Error_Occurrence(1100, CTL_dWARNING,m_strAlarmCode);
			m_nRunStep = 2000;
		}
		break;

	case 2200:
		nRet = CTL_Lib.Single_Move(BOTH_MOVE_FINISH, m_nAxisNum_Z,st_motor_info[m_nAxisNum_Z].d_pos[P_WORKROBOT_SAFETY] , COMI.mn_runspeed_rate);
		if (nRet == RET_GOOD)
		{
			m_nRunStep = 2300;
		}
		else if (nRet == BD_RETRY)
		{
			m_nRunStep = 2100;
		}
		else if (nRet == BD_ERROR || nRet == BD_SAFETY)
		{
			CTL_Lib.Alarm_Error_Occurrence(1200, CTL_dWARNING,m_strAlarmCode);
		}
		break;

	case 2300:
		nCnt = 0;
		for (int i = 0; i< MAX_PICKER; i++)
		{
			if (FAS_IO.get_in_bit(st_io_info.i_hs_Rear_rbt_picker_gripper_dvc_chk[i],IO_ON) == IO_ON)
			{
				st_Picker_info.nEnable[THD_HS_REAR_RBT][i] = NO;
				st_Picker_info.nExist[THD_HS_REAR_RBT][i] = YES;
				m_nPick_Cnt++;
				m_nTray_Dvc_Cnt++;
			}
		}
		bLast_Pick = false;
		if (m_nTray_Dvc_Cnt >= st_recipe_info.nTrayY)
		{	
			//Robot이 Work Stacker Pos에게 Tray Last Pick 자재 알려 준다.
			st_Picker_info.nLastPick[THD_HS_REAR_RBT] = YES;
			bLast_Pick = true;
			m_nTray_Dvc_Cnt = 0;
		}

		if (m_nPick_Cnt > MAX_PICKER || bLast_Pick == true)
		{
			st_sync_info.nShiftWork_Rbt[m_nBufferNum] = CTL_READY; 
			m_nRunStep = 2400;
			m_nPick_Cnt = 0;
		}
		else
		{
			m_nRunStep = 500;
		}
		break;

	case 2400:
		nWorkBuff = nWorkBufferPlacePos(m_nBufferNum);
		nRet = CTL_Lib.Single_Move(BOTH_MOVE_FINISH, m_nAxisNum_Y,st_motor_info[m_nAxisNum_Y].d_pos[nWorkBuff] , COMI.mn_runspeed_rate);
		if (nRet == RET_GOOD)
		{
			m_nRunStep = 2600;
		}
		else if (nRet == BD_RETRY)
		{
			m_nRunStep = 2400;
		}
		else if (nRet == BD_ERROR || nRet == BD_SAFETY)
		{
			CTL_Lib.Alarm_Error_Occurrence(1300, CTL_dWARNING,m_strAlarmCode);
		}
		break;

		//Robot이 Buffer에 투입
	case 2600:
		nCnt = 0;
		for (int i =0; i<MAX_PICKER; i++)
		{
			if (st_Picker_info.nEnable[THD_HS_REAR_RBT][i] == NO && st_Picker_info.nExist[THD_HS_REAR_RBT][i] == YES)
			{
				nCnt++;
			}
		}

		if (nCnt > 0)
		{
			m_nRunStep = 2700;
		}	
		break;

	case 2700:
		for (int i =0; i<MAX_PICKER; i++)
		{
			if (FAS_IO.get_in_bit(st_io_info.i_hs_Rear_rbt_picker_gripper_dvc_chk[i],IO_ON) == IO_ON && 
				st_Picker_info.nEnable[THD_HS_REAR_RBT][i] == NO && st_Picker_info.nExist[THD_HS_REAR_RBT][i] == YES)
			{
				st_Picker_info.nEnable[THD_HS_REAR_RBT][i] = YES;
				st_Picker_info.nExist[THD_HS_REAR_RBT][i] = NO;
				m_nPicker[i] = YES;
				break;
			}
		}
		OnSetPickerUpDn(IO_ON,m_nPicker);
		m_nRunStep = 2800;
		break;

	case 2800:
		nRet = OnGetPickerUpDn(IO_ON,m_nPicker);

		if (nRet == RET_GOOD)
		{
			m_nRunStep = 2900;
		}
		else  if (nRet == RET_ERROR)
		{
			CTL_Lib.Alarm_Error_Occurrence(1400, CTL_dWARNING,m_strAlarmCode);
		}
		break;

		//
	case 2900:
		nWorkBuff = nWorkBufferPlacePos(m_nBufferNum);
		nRet = CTL_Lib.Single_Move(BOTH_MOVE_FINISH, m_nAxisNum_Z,st_motor_info[m_nAxisNum_Z].d_pos[nWorkBuff] , COMI.mn_runspeed_rate);
		if (nRet == RET_GOOD)
		{
			m_nRunStep = 3000;
		}
		else if (nRet == BD_RETRY)
		{
			m_nRunStep = 3000;
		}
		else if (nRet == BD_ERROR || nRet == BD_SAFETY)
		{
			CTL_Lib.Alarm_Error_Occurrence(1500, CTL_dWARNING,m_strAlarmCode);
		}
		break;

	case 3100:
		OnSetPickerOnOff(IO_OFF,m_nPicker);
		m_nRunStep = 3200;
		break;

	case 3200:
		nRet = OnGetPickerOnOff(IO_OFF,m_nPicker);
		if (nRet == RET_GOOD)
		{
			m_nRunStep = 3300;
		}
		else if (nRet == RET_ERROR)
		{
			CTL_Lib.Alarm_Error_Occurrence(1600, CTL_dWARNING,m_strAlarmCode);
		}
		break;

	case 3300:
		nCnt = 0;
		for (int i =0; i< MAX_PICKER; i++)
		{
			if (st_Picker_info.nEnable[THD_HS_REAR_RBT][i] == NO && st_Picker_info.nExist[THD_HS_REAR_RBT][m_nPick_Cnt] == YES)
			{
				nCnt++;
			}
		}
		if (nCnt > 0)
		{
			m_nRunStep = 2700;
		}
		else
		{
			m_nRunStep = 0;
		}
		break;
	}
}
//
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