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
	m_nWork_StackerPos =  -1;
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
		OnReadyStackerMove();					
		OnWorkStackerMove();
		break;

	case dSTOP:

		break;

	case dWARNING:

		break;


	}
}
void CRun_Front_HeatSnk_Stacker::OnReadyStackerMove()
{
	int nRet = 0;
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
// 		if (FAS_IO.get_in_bit(st_io_info.i_hs_Front_Work_stacker_tray_chk,IO_OFF) == IO_OFF && 
// 			FAS_IO.get_in_bit(st_io_info.i_hs_Front_Ready_stacker_tray_chk,IO_OFF) == IO_OFF)
// 		{
// 			m_nRunStep = 300;
// 		}
// 		else
// 		{
// 			if (FAS_IO.get_in_bit(st_io_info.i_hs_Front_Work_stacker_tray_chk,IO_OFF) == IO_ON)
// 			{
// 				m_strCode.Format(_T("8%d%04d"), IO_ON, st_io_info.i_hs_Front_Work_stacker_tray_chk);
// 			}
// 			else if(FAS_IO.get_in_bit(st_io_info.i_hs_Front_Ready_stacker_tray_chk,IO_OFF) == IO_ON)
// 			{
// 				m_strCode.Format(_T("8%d%04d"), IO_ON, st_io_info.i_hs_Front_Ready_stacker_tray_chk);
// 			}
// 			CTL_Lib.Alarm_Error_Occurrence(30, CTL_dWARNING, m_strCode);
// 		}

		//kwlee 2017.0605
		if (FAS_IO.get_in_bit(st_io_info.i_hs_Front_Ready_stacker_tray_chk,IO_OFF) == IO_OFF) 
		{
			m_nRunStep = 300;
		}
		else
		{
			m_strCode.Format(_T("8%d%04d"), IO_ON, st_io_info.i_hs_Front_Ready_stacker_tray_chk);
			CTL_Lib.Alarm_Error_Occurrence(30, CTL_dWARNING, m_strCode);
		}
		break;

	case 300: //Tray Pusher 동작.
		OnSet_PusherFwdBwdCyl(IO_OFF);
		m_nRunStep = 400;
		break;

	case 400:
		nRet = OnGet_PusherFwdBwdCyl(IO_OFF);
		if (nRet == RET_GOOD)
		{
			m_nRunStep = 500;
		}
		else if (nRet == RET_ERROR)
		{
			CTL_Lib.Alarm_Error_Occurrence(30, CTL_dWARNING, m_strCode);
		}
		break;

	case 500://Ready Posision Tray Clamp Off
		OnSet_ReadyPos_TrayClampCyl(IO_OFF);
		m_nRunStep = 600;
		break;

	case 600:
		nRet = OnGet_ReadyPos_TrayClampCyl(IO_OFF);
		if (nRet == RET_GOOD)
		{
			m_nRunStep = 700;
		}
		else if (nRet == RET_ERROR)
		{
			CTL_Lib.Alarm_Error_Occurrence(30, CTL_dWARNING, m_strCode);
			m_nRunStep = 500;
		}
		break;

		//RailCylinder OnOff 동작
	case 700:
		OnSet_ReadyPos_RailFwdBwdCyl(IO_OFF);
		m_nRunStep = 800;
		break;

	case 800:
		nRet = OnGet_ReadyPos_RailFwdBwdCyl(IO_OFF);
		if (nRet == RET_GOOD)
		{
			m_nRunStep = 810;
		}
		else if (nRet == RET_ERROR)
		{
			CTL_Lib.Alarm_Error_Occurrence(30, CTL_dWARNING, m_strCode);
			m_nRunStep = 600;
		}
		break;

	case 810:
		OnSet_SeperateFwdBwdCyl(IO_OFF);
		m_nRunStep = 820;
		break;

	case 820:
		nRet = OnGet_SeperateFwdBwdCyl(IO_OFF);
		if (nRet == RET_GOOD)
		{
			m_nRunStep = 900;
		}
		else if (nRet == RET_ERROR)
		{
			CTL_Lib.Alarm_Error_Occurrence(30, CTL_dWARNING, m_strCode);
			m_nRunStep = 810;
		}
		break;

	case 900:
		OnSet_ReadyPos_StackerCylUpDn(IO_OFF);
		m_nRunStep = 910;
		break;

	case 910:
		nRet = OnGet_ReadyPos_StackerCylUpDn(IO_OFF);

		if (nRet == RET_GOOD)
		{
			m_nRunStep = 920;
		}
		else if (nRet == RET_ERROR)
		{
			CTL_Lib.Alarm_Error_Occurrence(30, CTL_dWARNING, m_strCode);
		}
		break;

		//SD Sensor 확인 하여 Tray 감지 되지 않아야 함 
	case 920:
		nRet = COMI.Get_MotIOSensor(m_nAxisNum_Ready,MOT_SENS_SD);
		if (nRet == RET_GOOD)
		{
			CTL_Lib.Alarm_Error_Occurrence(40, dWARNING, _T("900001"));
		}
		else
		{
			m_nRunStep = 930;
		}
		break;

		//대기 위치에 있어야 함.
	case 930:
		nRet = CTL_Lib.Single_Move(BOTH_MOVE_FINISH, m_nAxisNum_Ready, st_motor_info[m_nAxisNum_Ready].d_pos[P_ELV_TRAY_INOUT_POS], COMI.mn_runspeed_rate);  
		if (nRet == BD_GOOD) //좌측으로 이동  
		{			
			m_nRunStep = 1000;
		}
		else if (nRet == BD_RETRY)
		{
			m_nRunStep = 930;
		}
		else if (nRet == BD_ERROR || nRet == BD_SAFETY)
		{//모터 알람은 이미 처리했으니 이곳에서는 런 상태만 바꾸면 된다  
			CTL_Lib.Alarm_Error_Occurrence(60, dWARNING, st_alarm_info.strCode);
			m_nRunStep = 930;
		}
		break;

		//Stacker Rbt에서 요청. 
		//stacker에 Tray 있어야 함.
	case 1000:
// 		if (st_sync_info.nWorkRobot_Req[THD_HS_FRONT_STACKER_SITE][STACKER_WORK_POS] == CTL_REQ)
// 		{
// 			if (FAS_IO.get_in_bit(st_io_info.i_hs_Front_Ready_stacker_updn_pos_chk,IO_ON) == IO_ON)
// 			{
// 				m_nRunStep = 1100;
// 			}
// 			else
// 			{
// 				//"Front Heat Sink Ready Stacker Tray Up/Dn Pos Sensor Off Check Error."
// 				CTL_Lib.Alarm_Error_Occurrence(30, CTL_dWARNING, _T("800115"));
// 			}
// 		}
		//kwlee 2017.0605
		if (m_nWork_StackerPos == CTL_REQ)
		{
			if (FAS_IO.get_in_bit(st_io_info.i_hs_Front_Ready_stacker_updn_pos_chk,IO_ON) == IO_ON)
			{
				m_nRunStep = 1100;
			}
			else
			{
				//"Front Heat Sink Ready Stacker Tray Up/Dn Pos Sensor Off Check Error."
				CTL_Lib.Alarm_Error_Occurrence(30, CTL_dWARNING, _T("800115"));
			}
		}
		break;

	case 1100:
		OnSet_ReadyPos_StackerCylUpDn(IO_ON);
		m_nRunStep = 1200;
		break;

	case 1200:
		nRet = OnGet_ReadyPos_StackerCylUpDn(IO_ON);
		if (nRet == RET_GOOD)
		{
			m_nRunStep = 1300;
		}
		else if (nRet == RET_ERROR)
		{
			CTL_Lib.Alarm_Error_Occurrence(30, CTL_dWARNING,m_strCode);
		}
		break;

	case 1300:
		nRet = CTL_Lib.Stacker_Elevator_Move_Pos(0, m_nAxisNum_Ready,  P_ELV_SUPPLY_OFFSET);			
		if(nRet == RET_GOOD)
		{
			m_nRunStep = 1310;
		}
		break;

		//SD 센서 감지
	case 1310:
		nRet = COMI.Get_MotIOSensor(m_nAxisNum_Ready, MOT_SENS_SD);
		if (nRet == BD_GOOD)
		{
			m_nRunStep = 1400;
		}
		break;

		//1.Tray Clamp On 동작.
		//2.Seperate  On 동작.
		//3.Elevator Down
		//4. Stacker UpDn
		//5.Rail Clamp  On 동작.
		//6.Tray Clamp Off 동작.
	case 1400:
		OnSet_ReadyPos_TrayClampCyl(IO_ON);
		m_nRunStep = 1500;
		break;

	case 1500:
		nRet = OnGet_ReadyPos_TrayClampCyl(IO_ON);
		if (nRet == RET_GOOD)
		{
			m_nRunStep = 1600;
		}
		else if (nRet == RET_ERROR)
		{
			CTL_Lib.Alarm_Error_Occurrence(30, CTL_dWARNING,m_strCode);
			m_nRunStep = 1400;
		}
		break;

	case 1600:
		OnSet_SeperateFwdBwdCyl(IO_ON);
		m_nRunStep = 1700;
		break;

	case 1700:
		nRet = OnGet_SeperateFwdBwdCyl(IO_ON);
		if (nRet == RET_GOOD)
		{
			m_nRunStep = 1800;
		}
		else if (nRet == RET_ERROR)
		{
			CTL_Lib.Alarm_Error_Occurrence(30, CTL_dWARNING,m_strCode);
			m_nRunStep = 1600;
		}
		break;

	case 1800:
		nRet = CTL_Lib.Stacker_Elevator_Move_Pos(0, m_nAxisNum_Ready,  P_ELV_RECEIVE_OFFSET);			
		if(nRet == RET_GOOD)
		{
			m_nRunStep = 1900;
		}
		break;

	case 1900:
		nRet = COMI.Get_MotIOSensor(m_nAxisNum_Ready, MOT_SENS_SD);
		if (nRet == BD_ERROR)
		{
			m_nRunStep = 2000;
		}
		break;

	case 2000:
		OnSet_ReadyPos_RailFwdBwdCyl(IO_ON);
		m_nRunStep = 2100;
		break;

	case 2100:
		nRet = OnGet_ReadyPos_RailFwdBwdCyl(IO_ON);
		if (nRet == RET_GOOD)
		{
			m_nRunStep = 2200;
		}
		else if (nRet == RET_ERROR)
		{
			CTL_Lib.Alarm_Error_Occurrence(30, CTL_dWARNING,m_strCode);
			m_nRunStep = 2000;
		}
		break;

	case 2200:
		OnSet_SeperateFwdBwdCyl(IO_OFF);
		m_nRunStep = 2210;
		break;

	case 2210:
		nRet = OnGet_SeperateFwdBwdCyl(IO_OFF);
		if (nRet == RET_GOOD)
		{
			m_nRunStep = 2220;
		}
		else if (nRet == RET_ERROR)
		{
			CTL_Lib.Alarm_Error_Occurrence(30, CTL_dWARNING,m_strCode);
			m_nRunStep = 2200;
		}
		break;

	case 2220:
		OnSet_ReadyPos_TrayClampCyl(IO_OFF);
		m_nRunStep = 2230;
		break;

	case 2230:
		nRet = OnGet_ReadyPos_TrayClampCyl(IO_OFF);

		if (nRet == RET_GOOD)
		{
			m_nRunStep = 2400;
		}
		else if (nRet == RET_ERROR)
		{
			CTL_Lib.Alarm_Error_Occurrence(30, CTL_dWARNING,m_strCode);
			m_nRunStep = 2200;
		}
		break;

	case 2400:
		//Work Stacker에 Tray 없고 Ready Stacker에 Tray 준비 상태. Tray 요청.
// 		nRet = FAS_IO.get_in_bit(st_io_info.i_hs_Front_Ready_stacker_tray_chk,IO_ON);
// 		if (m_bWork_StackerPos_Req == true && nRet == IO_ON)

		//kwlee 2017.0605
		nRet = FAS_IO.get_in_bit(st_io_info.i_hs_Front_Ready_stacker_tray_chk,IO_ON);
		if (nRet == IO_ON)
		{
			OnSet_PusherFwdBwdCyl(IO_ON);
			m_nRunStep = 2500;
		}
		break;
	
	case 2500:
		nRet = OnGet_PusherFwdBwdCyl(IO_ON);
		if (nRet == RET_GOOD)
		{
			m_nRunStep = 2600;
		}
		else if (nRet == RET_ERROR)
		{
			CTL_Lib.Alarm_Error_Occurrence(30, CTL_dWARNING,m_strCode);
		}
		break;
	
	case 2600:
		//if (FAS_IO.get_in_bit(st_io_info.i_hs_Front_Work_stacker_tray_chk,IO_ON) == IO_ON)
		//kwlee 2017.0605
		if (FAS_IO.get_in_bit(st_io_info.i_hs_Front_Work_stacker_tray_chk,IO_ON) == IO_ON &&
			FAS_IO.get_in_bit(st_io_info.i_hs_Front_Ready_stacker_tray_chk,IO_OFF) == IO_OFF)
		{
			OnSet_PusherFwdBwdCyl(IO_OFF);
			//m_bWork_StackerPos_Req = false;
			m_nWork_StackerPos = CTL_READY;
			m_nRunStep = 2700;
		}
		break;

	case 2700:
		nRet = OnGet_PusherFwdBwdCyl(IO_OFF);
		if (nRet == RET_GOOD)
		{
			//m_nRunStep = 1000;
			//kwlee 2017.0605
			m_nRunStep = 100;
		}
		else if (nRet == RET_ERROR)
		{
			CTL_Lib.Alarm_Error_Occurrence(30, CTL_dWARNING,m_strCode);
		}
		break;

	}
}


void CRun_Front_HeatSnk_Stacker::OnWorkStackerMove()
{
	int nRet = 0;
	switch(m_nRunWorkstackerStep)
	{
	case 0:
		m_nRunWorkstackerStep = 100;
		break;

	case 100:
		if (st_lot_info[LOT_CURR].nLotStatus == LOT_START)
		{
			//m_nRunWorkstackerStep = 200;
			//kwlee 2017.0605
			nRet = FAS_IO.get_in_bit(st_io_info.i_hs_Front_Work_stacker_updn_pos_chk,IO_OFF);
			if (nRet == IO_OFF)
			{
				m_nRunWorkstackerStep = 110;
			}
			else
			{
				m_strCode.Format(_T("8%d%04d"), IO_ON, st_io_info.i_hs_Front_Work_stacker_updn_pos_chk); 
				CTL_Lib.Alarm_Error_Occurrence(10, CTL_dWARNING, m_strCode);
			}	
		}
		break;

	case 110:
		OnSet_WorkPos_TrayClampCyl(IO_OFF);
		m_nRunWorkstackerStep = 200;
		break;

	case 200:
		nRet = OnGet_WorkPos_TrayClampCyl(IO_OFF);
		if (nRet == RET_GOOD)
		{
			m_nRunWorkstackerStep = 300;
		}
		else if (nRet == RET_ERROR)
		{
			CTL_Lib.Alarm_Error_Occurrence(20, CTL_dWARNING, m_strCode);
			m_nRunWorkstackerStep = 100;
		}
		break;

	case 300:
		OnSet_WorkPos_RailFwdBwdCyl(IO_OFF);
		m_nRunWorkstackerStep = 400;
		break;

	case 400:
		nRet = OnGet_WorkPos_RailFwdBwdCyl(IO_OFF);
		if (nRet == RET_GOOD)
		{
			m_nRunWorkstackerStep = 500;
		}
		else if (nRet == RET_ERROR)
		{
			CTL_Lib.Alarm_Error_Occurrence(30, CTL_dWARNING, m_strCode);
			m_nRunWorkstackerStep = 300;
		}
		break;

	case 500:
		OnSet_WorkPos_StackerCylUpDn(IO_OFF);
		m_nRunWorkstackerStep = 600;
		break;

	case 600:
		nRet = OnGet_WorkPos_StackerCylUpDn(IO_OFF);
		
		if (nRet == RET_GOOD)
		{
			m_nRunWorkstackerStep = 700;
		}
		else if (nRet == RET_ERROR)
		{
			CTL_Lib.Alarm_Error_Occurrence(40, CTL_dWARNING, m_strCode);
			m_nRunWorkstackerStep = 500;
		}
		break;

	case 700:
		if (FAS_IO.get_in_bit(st_io_info.i_hs_Front_Work_stacker_tray_chk,IO_OFF) == IO_OFF)
		{
			OnSet_WorkPos_RailFwdBwdCyl(IO_ON);
			m_nRunWorkstackerStep = 800;
		}
		else
		{
			m_strCode.Format(_T("8%d%04d"), IO_ON, st_io_info.i_hs_Front_Work_stacker_tray_chk); 
			CTL_Lib.Alarm_Error_Occurrence(50, CTL_dWARNING, m_strCode);
		}
		break;

	case 800:
		nRet = OnGet_WorkPos_RailFwdBwdCyl(IO_ON);
		if (nRet == RET_GOOD)
		{
			m_nRunWorkstackerStep = 900;
		}
		else
		{
			CTL_Lib.Alarm_Error_Occurrence(60, CTL_dWARNING, m_strCode);
			m_nRunWorkstackerStep = 700;
		}
		break;

		//Ready Stacker에 Tray 요청.
	case 900:
		//m_bWork_StackerPos_Req = true;
		//if (st_sync_info.nWorkRobot[THD_HS_FRONT_STACKER_SITE][STACKER_WORK_POS] == CTL_REQ)
		//kwlee 2017.0605
		if (st_sync_info.nFrontHsRbt == CTL_REQ)
		{
			m_nWork_StackerPos = CTL_REQ;
			m_nRunWorkstackerStep = 1000;
		}
		break;

		//Work Stacker에 Tray 투입 상태
	case 1000:
		//if (FAS_IO.get_in_bit(st_io_info.i_hs_Front_Work_stacker_tray_chk,IO_ON) == IO_ON)
		//kwlee 2017.0605
		if (FAS_IO.get_in_bit(st_io_info.i_hs_Front_Work_stacker_tray_chk,IO_ON) == IO_ON && m_nWork_StackerPos == CTL_READY)
		{
			//st_sync_info.nWorkRobot[THD_HS_FRONT_STACKER_SITE][STACKER_WORK_POS] = CTL_READY;
			//kwlee 2017.0605
			st_sync_info.nFrontHsRbt = CTL_READY;
			OnSet_WorkPos_TrayClampCyl(IO_ON);
			m_nRunWorkstackerStep = 1100;
		}
		break;

		//Work Stacker 준비 되었다고 Stacker Robot에게 알려 준다.
	case 1100:
		nRet = OnGet_WorkPos_TrayClampCyl(IO_ON);
		if (nRet == RET_GOOD)
		{
			m_nRunWorkstackerStep = 1200;
			m_nWork_StackerPos = CTL_CLEAR;
		}
		else if (nRet == RET_ERROR)
		{
			CTL_Lib.Alarm_Error_Occurrence(70, CTL_dWARNING,m_strCode);
		}
		break;

	case 1200:
		OnSet_WorkPos_StackerCylUpDn(IO_ON);
		m_nRunWorkstackerStep = 1300;
		break;

	case 1300:
		nRet = OnGet_WorkPos_StackerCylUpDn(IO_ON);
		if (nRet == RET_GOOD)
		{
			m_nRunWorkstackerStep = 1400;
		}
		else if (nRet == RET_ERROR)
		{
			CTL_Lib.Alarm_Error_Occurrence(90, CTL_dWARNING,m_strCode);
			m_nRunWorkstackerStep = 1200;
		}
		break;

		//마지막 자재 집었다. 빈트레이 처리 하자.
	case 1400:
		if (st_Picker_info.nLastPick[THD_HS_FRONT_RBT] == YES)
		{
			//m_nRunWorkstackerStep = 1300;
			m_nRunWorkstackerStep = 1410;
		}
		break;

	case 1410:
		OnSet_WorkPos_RailFwdBwdCyl(IO_OFF);
		m_nRunWorkstackerStep = 1420;
		break;

	case 1420:
		nRet = OnGet_WorkPos_RailFwdBwdCyl(IO_OFF);
		if (nRet == RET_GOOD)
		{
			m_nRunWorkstackerStep = 1500;
		}
		else if (nRet == RET_ERROR)
		{
			CTL_Lib.Alarm_Error_Occurrence(80, CTL_dWARNING,m_strCode);
		}
		break;

// 	case 1300:
// 		OnSet_WorkPos_StackerCylUpDn(IO_ON);
// 		m_nRunWorkstackerStep = 1400;
// 		break;
// 
// 	case 1400:
// 		nRet = OnGet_WorkPos_StackerCylUpDn(IO_ON);
// 		if (nRet == RET_GOOD)
// 		{
// 			m_nRunWorkstackerStep = 1500;
// 		}
// 		else if (nRet == RET_ERROR)
// 		{
// 			CTL_Lib.Alarm_Error_Occurrence(90, CTL_dWARNING,m_strCode);
// 			m_nRunWorkstackerStep = 1300;
// 		}
// 		break;

	case 1500:
		OnSet_WorkPos_TrayClampCyl(IO_OFF);
		m_nRunWorkstackerStep = 1600;
		break;

	case 1600:
		nRet = OnGet_WorkPos_TrayClampCyl(IO_OFF);
		if (nRet == RET_GOOD)
		{
			m_nRunWorkstackerStep = 1700;
		}
		else
		{
			CTL_Lib.Alarm_Error_Occurrence(100, CTL_dWARNING,m_strCode);
			m_nRunWorkstackerStep = 1500;
		}
		break;

	case 1700:
		OnSet_WorkPos_StackerCylUpDn(IO_OFF);
		m_nRunWorkstackerStep = 1800;
		break;

	case 1800:
		nRet = OnGet_WorkPos_StackerCylUpDn(IO_OFF);
		if (nRet == RET_GOOD)
		{
			m_nRunWorkstackerStep = 0;
		}
		else if (nRet == RET_ERROR)
		{
			CTL_Lib.Alarm_Error_Occurrence(110, CTL_dWARNING,m_strCode);
			m_nRunWorkstackerStep = 1700;
		}
		break; 
	}
}


void CRun_Front_HeatSnk_Stacker::OnRunInit()
{
	int nRet_1, nRet_2;

	if (st_sync_info.nInit_Flag[THD_HS_FRONT_STACKER_SITE] != INIT_CLEAR)		return;	

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
			CTL_Lib.Alarm_Error_Occurrence(10,CTL_dWARNING, _T("810208"));
		}
		else if (FAS_IO.get_in_bit(st_io_info.i_hs_Front_Ready_stacker_tray_chk,IO_OFF) == IO_ON)
		{
			
			CTL_Lib.Alarm_Error_Occurrence(11, CTL_dWARNING, _T("810114"));
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
		OnSet_PusherFwdBwdCyl(IO_OFF);
		m_nInitStep = 510;
		break;

	case 510:
		nRet_1 = OnGet_PusherFwdBwdCyl(IO_OFF);
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
		st_sync_info.nInit_Flag[THD_HS_FRONT_STACKER_SITE] = INIT_READY; 

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
				m_strCode.Format(_T("8%d%04d"), nUpDn, st_io_info.i_hs_Front_Ready_stacker_dn_chk); 
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
				m_strCode.Format(_T("8%d%04d"), nUpDn, st_io_info.i_hs_Front_Ready_stacker_up_chk); 
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
				if (FAS_IO.get_in_bit(st_io_info.i_hs_Front_Ready_stacker_Left_rail_fwd_chk,IO_ON) == IO_OFF)
				{
					m_strCode.Format(_T("8%d%04d"), nOnOff, st_io_info.i_hs_Front_Ready_stacker_Left_rail_fwd_chk); 
				}
				else if (FAS_IO.get_in_bit(st_io_info.i_hs_Front_Ready_stacker_Right_rail_fwd_chk,IO_ON) == IO_OFF)
				{
					m_strCode.Format(_T("8%d%04d"), nOnOff, st_io_info.i_hs_Front_Ready_stacker_Right_rail_fwd_chk); 
				}
				else
				{

				}
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
				if (FAS_IO.get_in_bit(st_io_info.i_hs_Front_Ready_stacker_Left_rail_bwd_chk,IO_ON) == IO_OFF)
				{
					m_strCode.Format(_T("8%d%04d"), nOnOff, st_io_info.i_hs_Front_Ready_stacker_Left_rail_bwd_chk); 
				}
				else if (FAS_IO.get_in_bit(st_io_info.i_hs_Front_Ready_stacker_Right_rail_bwd_chk,IO_ON) == IO_OFF)
				{
					m_strCode.Format(_T("8%d%04d"), nOnOff, st_io_info.i_hs_Front_Ready_stacker_Right_rail_bwd_chk); 
				}
				else
				{

				}
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
				m_strCode.Format(_T("8%d%04d"), nOnOff, st_io_info.i_hs_Front_Ready_stacker_guide_clamp_on_chk); 
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
				m_strCode.Format(_T("8%d%04d"), nOnOff, st_io_info.i_hs_Front_Ready_stacker_guide_unclamp_off_chk); 
				return RET_ERROR;
			}
		}
	}
	return nRet;
}

void CRun_Front_HeatSnk_Stacker::OnSet_PusherFwdBwdCyl(int nOnOff)
{
	FAS_IO.set_out_bit(st_io_info.o_hs_Front_stacker_tray_pusher_fwd_onoff,nOnOff);
	FAS_IO.set_out_bit(st_io_info.o_hs_Front_stacker_tray_pusher_bwd_onoff,!nOnOff);

	m_dwCylWaitTime[READY_PUSHER_ONOFF][0] = GetCurrentTime();
	m_bCylinderFlag[READY_PUSHER_ONOFF] = false;
}

int CRun_Front_HeatSnk_Stacker::OnGet_PusherFwdBwdCyl(int nOnOff)
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
				m_strCode.Format(_T("8%d%04d"), nOnOff, st_io_info.i_hs_Front_stacker_tray_pusher_fwd_chk);
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
				m_strCode.Format(_T("8%d%04d"), nOnOff, st_io_info.i_hs_Front_stacker_tray_pusher_bwd_chk);
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
				m_strCode.Format(_T("8%d%04d"), nUpDn, st_io_info.i_hs_Front_Work_stacker_dn_chk);
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
				m_strCode.Format(_T("8%d%04d"), nUpDn, st_io_info.i_hs_Front_Work_stacker_up_chk);
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
				if (FAS_IO.get_in_bit(st_io_info.i_hs_Front_Work_stacker_Left_rail_fwd_chk,IO_ON) == IO_OFF)
				{
					m_strCode.Format(_T("8%d%04d"), nOnOff, st_io_info.i_hs_Front_Work_stacker_Left_rail_fwd_chk); 
				}
				else if (FAS_IO.get_in_bit(st_io_info.i_hs_Front_Work_stacker_Right_rail_fwd_chk,IO_ON) == IO_OFF)
				{
					m_strCode.Format(_T("8%d%04d"), nOnOff, st_io_info.i_hs_Front_Work_stacker_Right_rail_fwd_chk); 
				}
				else
				{

				}
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
				if (FAS_IO.get_in_bit(st_io_info.i_hs_Front_Work_stacker_Left_rail_bwd_chk,IO_ON) == IO_OFF)
				{
					m_strCode.Format(_T("8%d%04d"), nOnOff, st_io_info.i_hs_Front_Work_stacker_Left_rail_bwd_chk); 
				}
				else if (FAS_IO.get_in_bit(st_io_info.i_hs_Front_Work_stacker_Right_rail_bwd_chk,IO_ON) == IO_OFF)
				{
					m_strCode.Format(_T("8%d%04d"), nOnOff, st_io_info.i_hs_Front_Work_stacker_Right_rail_bwd_chk); 
				}
				else
				{

				}
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
				m_strCode.Format(_T("8%d%04d"), nOnOff, st_io_info.i_hs_Front_Work_stacker_guide_clamp_on_chk); 
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
				m_strCode.Format(_T("8%d%04d"), nOnOff, st_io_info.i_hs_Front_Work_stacker_guide_unclamp_off_chk); 
				return RET_ERROR;
			}
		}
	}
	return nRet;
}

void CRun_Front_HeatSnk_Stacker::OnSet_SeperateFwdBwdCyl(int nOnOff)
{
	FAS_IO.set_out_bit(st_io_info.o_hs_Front_stacker_tray_Seperate_onoff,nOnOff);

	m_dwCylWaitTime[WORK_TRAY_SEPERATE_ONOFF][0] = GetCurrentTime();
	m_bCylinderFlag[WORK_TRAY_SEPERATE_ONOFF] = false;
}

int CRun_Front_HeatSnk_Stacker::OnGet_SeperateFwdBwdCyl(int nOnOff)
{
	int nWaitTime = WAIT_STACKER_CYL_ON_OFF;
	int nRet = RET_PROCEED;
	if (nOnOff == IO_ON)
	{
		if (m_bCylinderFlag[WORK_TRAY_SEPERATE_ONOFF] ==  false && 
			FAS_IO.get_in_bit(st_io_info.i_hs_Front_stacker_tray_Seperate_fwd_chk,IO_ON) == IO_ON &&
			FAS_IO.get_in_bit(st_io_info.i_hs_Front_stacker_tray_Seperate_bwd_chk,IO_OFF) == IO_OFF)
		{
			m_bCylinderFlag[WORK_TRAY_SEPERATE_ONOFF] = true;
			m_dwCylWaitTime[WORK_TRAY_SEPERATE_ONOFF][0] = GetCurrentTime();
		}
		else if (m_bCylinderFlag[WORK_TRAY_SEPERATE_ONOFF] ==  true && 
			FAS_IO.get_in_bit(st_io_info.i_hs_Front_stacker_tray_Seperate_fwd_chk,IO_ON) == IO_ON &&
			FAS_IO.get_in_bit(st_io_info.i_hs_Front_stacker_tray_Seperate_bwd_chk,IO_OFF) == IO_OFF)
		{
			m_dwCylWaitTime[WORK_TRAY_SEPERATE_ONOFF][1] = GetCurrentTime();
			m_dwCylWaitTime[WORK_TRAY_SEPERATE_ONOFF][2] = m_dwCylWaitTime[WORK_TRAY_SEPERATE_ONOFF][1] - m_dwCylWaitTime[WORK_TRAY_SEPERATE_ONOFF][0];

			if (m_dwCylWaitTime[WORK_TRAY_SEPERATE_ONOFF][2] <= 0)
			{
				m_dwCylWaitTime[WORK_TRAY_SEPERATE_ONOFF][0] = GetCurrentTime();
				return RET_PROCEED;
			}
			if (m_dwCylWaitTime[WORK_TRAY_SEPERATE_ONOFF][2] > (DWORD)st_wait_info.nOnWaitTime[nWaitTime])
			{
				return RET_GOOD;
			}
		}
		else
		{
			m_dwCylWaitTime[WORK_TRAY_SEPERATE_ONOFF][1] = GetCurrentTime();
			m_dwCylWaitTime[WORK_TRAY_SEPERATE_ONOFF][2] = m_dwCylWaitTime[WORK_TRAY_SEPERATE_ONOFF][1] - m_dwCylWaitTime[WORK_TRAY_SEPERATE_ONOFF][0];

			if (m_dwCylWaitTime[WORK_TRAY_SEPERATE_ONOFF][2] <= 0)
			{
				m_dwCylWaitTime[WORK_TRAY_SEPERATE_ONOFF][0] = GetCurrentTime();
				return RET_PROCEED;
			}
			if (m_dwCylWaitTime[WORK_TRAY_SEPERATE_ONOFF][2] > (DWORD)st_wait_info.nLimitWaitTime[nWaitTime])
			{
				m_strCode.Format(_T("8%d%04d"), nOnOff, st_io_info.i_hs_Front_stacker_tray_Seperate_fwd_chk); 
				return RET_ERROR;
			}
		}
	}
	else //(nOnOff == IO_OFF)
	{
		if (m_bCylinderFlag[WORK_TRAY_SEPERATE_ONOFF] ==  false && 
			FAS_IO.get_in_bit(st_io_info.i_hs_Front_stacker_tray_Seperate_fwd_chk,IO_OFF) == IO_OFF &&
			FAS_IO.get_in_bit(st_io_info.i_hs_Front_stacker_tray_Seperate_bwd_chk,IO_ON) == IO_ON)

		{
			m_bCylinderFlag[WORK_TRAY_SEPERATE_ONOFF] = true;
			m_dwCylWaitTime[WORK_TRAY_SEPERATE_ONOFF][0] = GetCurrentTime();
		}
		else if (m_bCylinderFlag[WORK_TRAY_SEPERATE_ONOFF] ==  true && 
			FAS_IO.get_in_bit(st_io_info.i_hs_Front_stacker_tray_Seperate_fwd_chk,IO_OFF) == IO_OFF &&
			FAS_IO.get_in_bit(st_io_info.i_hs_Front_stacker_tray_Seperate_bwd_chk,IO_ON) == IO_ON)
		{
			m_dwCylWaitTime[WORK_TRAY_SEPERATE_ONOFF][1] = GetCurrentTime();
			m_dwCylWaitTime[WORK_TRAY_SEPERATE_ONOFF][2] = m_dwCylWaitTime[WORK_TRAY_SEPERATE_ONOFF][1] - m_dwCylWaitTime[WORK_TRAY_SEPERATE_ONOFF][0];

			if (m_dwCylWaitTime[WORK_TRAY_SEPERATE_ONOFF][2] <= 0)
			{
				m_dwCylWaitTime[WORK_TRAY_SEPERATE_ONOFF][0] = GetCurrentTime();
				return RET_PROCEED;
			}
			if (m_dwCylWaitTime[WORK_TRAY_SEPERATE_ONOFF][2] > (DWORD)st_wait_info.nOnWaitTime[nWaitTime])
			{
				return RET_GOOD;
			}
		}
		else
		{
			m_dwCylWaitTime[WORK_TRAY_SEPERATE_ONOFF][1] = GetCurrentTime();
			m_dwCylWaitTime[WORK_TRAY_SEPERATE_ONOFF][2] = m_dwCylWaitTime[WORK_TRAY_SEPERATE_ONOFF][1] - m_dwCylWaitTime[WORK_TRAY_SEPERATE_ONOFF][0];

			if (m_dwCylWaitTime[WORK_TRAY_SEPERATE_ONOFF][2] <= 0)
			{
				m_dwCylWaitTime[WORK_TRAY_SEPERATE_ONOFF][0] = GetCurrentTime();
				return RET_PROCEED;
			}
			if (m_dwCylWaitTime[WORK_TRAY_SEPERATE_ONOFF][2] > (DWORD)st_wait_info.nLimitWaitTime[nWaitTime])
			{
				m_strCode.Format(_T("8%d%04d"), nOnOff, st_io_info.i_hs_Front_stacker_tray_Seperate_bwd_chk); 
				return RET_ERROR;
			}
		}
	}
	return nRet;
}
