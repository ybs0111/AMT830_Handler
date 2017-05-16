#include "StdAfx.h"
#include "RunHandlerCheck.h"
#include "PublicFunction.h"
#include "Variable.h"
#include "FastechPublic_IO.h"
#include "ComizoaPublic.h"
#include "Ctlbd_Variable.h"
#include "math.h"
#include "CtlBd_Library.h"
#include "XgemClient.h"
#include "AlgMemory.h"

CRunHandlerCheck clsHdChk;

CRunHandlerCheck::CRunHandlerCheck(void)
{
	m_nStartStep			= 0;
	m_nStopStep				= 0;
	m_nResetStep			= 0;
	m_nBuzzerStep			= 0;
	m_nAutoStep				= 0;
	m_nManualStep			= 0;
	m_nOldHifixMode			= -1;
}


CRunHandlerCheck::~CRunHandlerCheck(void)
{
}

void CRunHandlerCheck::OnStartCheck()
{
	int nRet;


	CString mstr_temp; //2015.0407 james 

	if (st_handler_info.nSystemLock != NO)	
	{
		return;
	}

	if (st_handler_info.nMenuLock != NO)	
	{
		return;
	}

	if (st_handler_info.nSwitchLock != NO)	
	{
		return;
	}

	if (st_handler_info.nRunStatus == dRUN)	
	{
		return;
	}

	if (st_handler_info.nInitialSuccess != YES)	
	{
		return;
	}

	if(st_handler_info.nMachineMode	== MACHINE_MANUAL)
	{
	
		return;
	}

	

	switch(m_nStartStep)
	{
		case 0:
			// [STOP] 상태에서만 [START] 가능하도록 제한한다
			if (st_handler_info.nRunStatus == dSTOP)
			{
			
			}
			break;

		case 100: 
			
			m_nStartStep = 0;
			
			break;

		case 200:
			// =============================================================================
			// RUN 키 I/O 입력이 Off 되었는지 검사                                   
			// -> 알람 화면 출력 상태이면 알람 화면 종료 -> 메인 화면으로 전환       
			// =============================================================================
			
			break;

		case 240:

			if (nRet == RET_GOOD)
			{
				m_nRightMpStep = 0;

				m_nStartStep = 280;
			}
			else if (nRet == RET_ERROR)
			{
				m_nStartStep = 0;
			}
			break;

		case 280:

			if (nRet == RET_GOOD)
			{
				m_nStartStep = 300;
			}
			else if (nRet == RET_ERROR)
			{
				m_nStartStep = 0;
			}
			break;

		case 300:
			if(OnRunPossibleCheck() == RET_GOOD)
			{
				// 알람이 출력된 상태에서 START 버튼 누른 경우에는 알람을 먼저 종료시킨다
				if (st_handler_info.nMenuNum != IDW_SCREEN_MAIN)	
				{
					::SendMessage(st_handler_info.hWnd, WM_FORM_CHANGE, SCREEN_MAIN, 0);  // 메인 화면으로 전환 요청
				}

				if (st_basic_info.nModeInterface == EQP_ON_LINE)
				{
					m_nStartStep = 320;
				}
				else
				{
					m_nStartStep = 400;
				}
			}
			else
			{
				st_handler_info.nRunStatus = dWARNING;

				m_nStartStep = 0;
			}
			break;

		case 320:
			// 차후 테스트 예정
			// jtkim 20150714
			//nRet = clsFunc.OnTestSiteCokStatus();
			//if (nRet == RET_ERROR)
			
			break;

		//////////////////////////////////////////////////////////////
		// 2015.0407 james COK를 교체할때만 처음 한번 들어 온다 
		// 혹시 저장된 OLD HIFIX 값이 실제 장비 상태와 틀릴수 있어, 이떄는 st_work_info.nOldHifix 값을 st_recipe_info.nCOKBuff_IDNum_Type와 같게 해야 장비 가동이 가능하니, nOldHifix 값을 바꿀수 있는 기능이 추가되어야 한다
		//////////////////////////////////////////////////////////////
		case 330:
			st_other_info.nConfirmMsg	= -1;
			st_other_info.strConfirmMsg = _T("Do you want a COK Change?");

			if (st_handler_info.cWndMain != NULL)
			{
				st_handler_info.cWndMain->SendMessage(WM_WORK_COMMAND, MAIN_MESSAGE_VIEW_CREATE_REQ, 0);
			}
			m_nStartStep = 331;
			break;

		case 331:// 2015.0407 james 
			if (st_other_info.nConfirmMsg == YES)  //COK 교체 작업 지시 
			{
				if (st_handler_info.nMenuLock != FALSE)	
				{
					st_handler_info.nMenuLock = FALSE;
				}

				 
				m_dwStartWaitTime[0] = GetTickCount();

				if (st_handler_info.cWndList != NULL)  // 리스트 바 화면 존재
				{
					clsMem.OnAbNormalMessagWrite(_T("COK EXCHANGE Select OK....."));
					st_handler_info.cWndList->SendMessage(WM_LIST_DATA, 0, ABNORMAL_MSG);
				}

				m_nStartStep = 340;  
			}
			else if(st_other_info.nConfirmMsg == NO) //COK를 작업하지 않는다 
			{
				if (st_handler_info.cWndMain != NULL)
				{
					
					st_handler_info.cWndMain->SendMessage(WM_WORK_COMMAND, MAIN_MESSAGE_BOX_CREATE_REQ, 0);
				}

				if (st_handler_info.cWndList != NULL)  // 리스트 바 화면 존재
				{
					clsMem.OnAbNormalMessagWrite(_T("COK EXCHANGE Select CANCEL....."));
					st_handler_info.cWndList->SendMessage(WM_LIST_DATA, 0, ABNORMAL_MSG);
				}

				m_nStartStep = 0;
			}
			break;

		//////////////////////////////////////////////////////////////
		// COK를 교체할때만 처음 한번 들어 온다 
		//////////////////////////////////////////////////////////////
		case 340:
		
			break;

		case 400:
			clsFunc.OnMCRun();

			if (st_handler_info.cWndMain != NULL)
			{
//				st_handler_info.cWndMain->SendMessage(WM_WORK_COMMAND, MAIN_RECOVERY_CREATE_REQ, 0);
			}
			m_nStartStep = 500;
			break;

		case 500:
			
			m_nStartStep = 600;
			break;

		case 600:
			// jtkim 20150418
			if (clsXgem.m_nRunStatus == HOST_RUN)
			{
				m_nStartStep = 1200;
			}
			else if (clsXgem.m_nRunStatus == HOST_STOP)
			{
				st_other_info.nBuzYesNo = YES;
				st_other_info.strBoxMsg = _T("XGem RCMD Stop. \r\n RCMD Check");

				if (st_handler_info.cWndMain != NULL)
				{
					st_handler_info.cWndMain->SendMessage(WM_WORK_COMMAND, MAIN_MESSAGE_BOX_CREATE_REQ, 0);
				}

				// jtkim 20130625
				clsFunc.OnMCStop();

				m_nStartStep = 0;
			}
			else
			{
				m_dwStartWaitTime[1] = GetCurrentTime();
				m_dwStartWaitTime[2] = m_dwStartWaitTime[1] - m_dwStartWaitTime[0];

				if (m_dwStartWaitTime[2] <= (DWORD)0)
				{
					m_dwStartWaitTime[0] = GetCurrentTime();
					break;
				}

				if (m_dwStartWaitTime[2] > (DWORD)10000)
				{
					if (st_handler_info.cWndList != NULL)	
					{
						//clsFunc.OnStringToChar(_T("[XGEM] Start Check Error"), st_other_info.cNormalMsg);
						clsMem.OnAbNormalMessagWrite(_T("[XGEM] RCMD Start Check Error"));
						st_handler_info.cWndList->SendMessage(WM_LIST_DATA, 0, NORMAL_MSG);
					}

					st_other_info.nBuzYesNo = YES;
					st_other_info.strBoxMsg = _T("XGem RCMD TimeOut. \r\n RCMD Check");

					if (st_handler_info.cWndMain != NULL)
					{
						st_handler_info.cWndMain->SendMessage(WM_WORK_COMMAND, MAIN_MESSAGE_BOX_CREATE_REQ, 0);
					}
					// jtkim 20130625
					clsFunc.OnMCStop();

					m_nStartStep = 0;
				}
			}
			break;

		case 1000:
			st_handler_info.nRunStatus	= dRECOVERY;
			
			m_nStartStep = 1100;
			break;
			
		case 1100:
	
			break;

		case 1200:
			st_handler_info.nRunStatus = dRUN;

			if (st_handler_info.nMenuLock != FALSE)
			{
				st_handler_info.nMenuLock = FALSE;
			}

			if (st_handler_info.nAlarmScreen )
			{
				st_handler_info.nAlarmScreen = FALSE;
			}

			// 20140812 jtkim
			clsXgem.OnMcStatus(dRUN);

			if (CTL_Lib.m_nMcEmg == YES)
			{
				CTL_Lib.m_nMcEmg = NO;
			}

			if(st_handler_info.cWndTitle != NULL)
			{
				st_handler_info.cWndTitle->PostMessage(WM_STATUS_CHANGE, MACHINE_STATUS, st_handler_info.nRunStatus);
			}

			if (st_handler_info.cWndList != NULL)  // 리스트 바 화면 존재
			{
				clsMem.OnNormalMessageWrite(_T("MC Start Status...."));
				st_handler_info.cWndList->SendMessage(WM_LIST_DATA, 0, NORMAL_MSG);
			}
			m_nStartStep = 0;

			

			break;
	}
}


void CRunHandlerCheck::OnStopCheck()
{
	if (st_handler_info.nSystemLock != NO)	
	{
		return;
	}

	if (st_handler_info.nSwitchLock != NO)	
	{
		return;
	}

	if (st_handler_info.nRunStatus == dSTOP)	
	{
		return;
	}

	switch(m_nStopStep)
	{
		case 0:
			
			break;

		case 100:
		
			break;

		case 200:
			
			break;
	}
}


void CRunHandlerCheck::OnResetCheck()
{
	if (st_handler_info.nSystemLock != NO)	
	{
		return;
	}

	if (st_handler_info.nSwitchLock != NO)	
	{
		return;
	}

	switch(m_nResetStep)
	{
		case 0:
			// **********************************************************************
			//  Reset 키 I/O 입력이 On 상태인지 확인                                 
			// **********************************************************************
			if(FAS_IO.get_in_bit(st_io_info.i_AlarmChk, IO_OFF) == IO_ON)
			{
				m_dwResetWaitTime[0] = GetCurrentTime();
				m_nResetStep = 100;
			}
			break;

		case 100: 
			if(FAS_IO.get_in_bit(st_io_info.i_AlarmChk, IO_OFF) == IO_ON)
			{
				m_dwResetWaitTime[1] = GetCurrentTime();
				m_dwResetWaitTime[2] = m_dwResetWaitTime[1] - m_dwResetWaitTime[0];

				if(m_dwResetWaitTime[2] <= 0)
				{
					m_dwResetWaitTime[0] = GetCurrentTime();
					break;
				}

				if(m_dwResetWaitTime[2] > (DWORD)100)
				{
					m_nResetStep = 200;
				}
			}
			else
			{
				m_nResetStep = 0;
			}
			break;

		case 200:
			if (FAS_IO.get_in_bit(st_io_info.i_AlarmChk, IO_ON) == IO_OFF)
			{
				st_alarm_info.nResetStatus = NO;

				if (st_alarm_info.nResetStatus == YES)
				{
					st_alarm_info.nResetStatus = NO;  // 알람 리셋 작업 필요 없음
					
					if (st_handler_info.cWndList != NULL)	
					{
						//wsprintfA(st_other_info.cNormalMsg, "%S", _T("[JAM RESET] JAM RESET."));
						//clsFunc.OnStringToChar(_T("[JAM RESET] JAM RESET."), st_other_info.cNormalMsg);
						clsMem.OnNormalMessageWrite(_T("[JAM RESET] JAM RESET."));
						st_handler_info.cWndList->SendMessage(WM_LIST_DATA, 0, NORMAL_MSG);
					}

					// 설비 상태가 RUN 상태이면 사운드만 종료하고 RUN 상태 아니면 [STOP] 상태로 변경한다
					// jtkim 20130625
					clsFunc.OnMCStop();  // 설비 STOP 상태에 대한 버튼 램프 상태 변경

					// 20140812 jtkim
					clsXgem.OnMcStatus(dSTOP);

					clsFunc.OnSound(IO_OFF);
				}
				else
				{
					if (st_handler_info.cWndList != NULL)	
					{
						//wsprintfA(st_other_info.cNormalMsg, "%S", _T("[SOUND] OFF."));
						//clsFunc.OnStringToChar(_T("[SOUND] OFF."), st_other_info.cNormalMsg);
						clsMem.OnNormalMessageWrite(_T("[SOUND] OFF."));
						st_handler_info.cWndList->SendMessage(WM_LIST_DATA, 0, NORMAL_MSG);
					}
					// jtkim 20130625
					clsFunc.OnSound(IO_OFF);  // 부저 사운드 ON/OFF
				}

				m_nResetStep = 0;
			}
			break;
	}
}


void CRunHandlerCheck::OnBuzzerCheck()
{
	if (st_handler_info.nSystemLock != NO)	
	{
		return;
	}

	if (st_handler_info.nSwitchLock != NO)	
	{
		return;
	}

	switch(m_nBuzzerStep)
	{
		case 0:
			if(FAS_IO.get_in_bit(st_io_info.i_BuzzChk, IO_OFF) == IO_ON)
			{
				m_dwBuzzerWaitTime[0] = GetCurrentTime();
				m_nBuzzerStep = 100;
			}
			break;
			
		case 100: 
			if(FAS_IO.get_in_bit(st_io_info.i_BuzzChk, IO_ON) == IO_ON)
			{
				m_dwBuzzerWaitTime[1] = GetCurrentTime();
				m_dwBuzzerWaitTime[2] = m_dwBuzzerWaitTime[1] - m_dwBuzzerWaitTime[0];

				if(m_dwBuzzerWaitTime[2] <= 0)
				{
					m_dwBuzzerWaitTime[0] = GetCurrentTime();
					break;
				}

				if(m_dwBuzzerWaitTime[2] > (DWORD)100)
				{
					m_nBuzzerStep = 200;
				}
			}
			else
			{
				m_nBuzzerStep = 0;
			}
			break;
			
		case 200:
			if (FAS_IO.get_in_bit(st_io_info.i_BuzzChk, IO_OFF) == IO_OFF)
			{
				if (st_handler_info.cWndList != NULL)	
				{
					//wsprintfA(st_other_info.cNormalMsg, "%S", _T("[SOUND] OFF."));
					//clsFunc.OnStringToChar(_T("[SOUND] OFF."), st_other_info.cNormalMsg);
					clsMem.OnNormalMessageWrite(_T("[SOUND] OFF."));
					st_handler_info.cWndList->SendMessage(WM_LIST_DATA, 0, NORMAL_MSG);
				}
				// jtkim 20130625
				clsFunc.OnSound(IO_OFF);  // 부저 사운드 ON/OFF
				
				m_nBuzzerStep = 0;
			}
			break;
	}
}


void CRunHandlerCheck::OnAutoCheck()
{
	int nRet;

	if (st_handler_info.nSystemLock != NO)	
	{
		return;
	}

	if (st_handler_info.nSwitchLock != NO)	
	{
		return;
	}

	if(st_handler_info.nRunStatus	== dRUN || st_handler_info.nRunStatus	== dINIT)
	{
		return;
	}

	if(st_handler_info.nMachineMode	== MACHINE_AUTO)
	{
		return;
	}

	switch(m_nAutoStep)
	{
		case 0:		//2014.01.21 주석처리
		
			break;

		case 100:	//2014.01.21 주석처리
		
			break;

		case 200:
			nRet = clsFunc.OnDoorOpenCheck();

			if(nRet == RET_GOOD)
			{
				m_nAutoStep = 400;
			}
			else if(nRet != RET_PROCEED)
			{
				st_handler_info.nRunStatus			= dWARNING;
				st_alarm_info.nAlarmAssignSection	= 6000;

				m_nAutoStep = 300;
			}
			break;

		case 300:
			nRet = clsFunc.OnDoorOpenCheck();

			if(nRet == RET_GOOD)
			{
				m_nAutoStep = 0;
			}
			break;

		case 400:
			m_dwAutoWaitTime[0] = GetTickCount();
			m_nAutoStep = 500;
			break;

		case 500:
			m_dwAutoWaitTime[1] = GetTickCount();
			m_dwAutoWaitTime[2] = m_dwAutoWaitTime[1] - m_dwAutoWaitTime[0];
			
			if(m_dwAutoWaitTime[2] <= 0)
			{
				m_dwAutoWaitTime[0] = GetTickCount();
				break;
			}

			if(m_dwAutoWaitTime[2] > (DWORD)500)
			{
				m_nAutoStep = 600;
			}
			break;

		case 600:
			// jtkim 20130625
			clsFunc.OnDoorClose();

			st_handler_info.nMachineMode = MACHINE_AUTO;
			m_nAutoStep = 0;
			break;
	}
}


void CRunHandlerCheck::OnManualCheck()
{
	if (st_handler_info.nSystemLock != NO)	
	{
		return;
	}

	if (st_handler_info.nSwitchLock != NO)	
	{
		return;
	}

//	if(st_handler_info.nRunStatus	!= dSTOP)
	if(st_handler_info.nRunStatus	== dRUN || st_handler_info.nRunStatus	== dINIT)
	{
		return;
	}

	if(st_handler_info.nMachineMode	== MACHINE_MANUAL)
	{
		return;
	}

	switch(m_nManualStep)
	{
		case 0:		
		
			m_nManualStep = 100;
			break;

		case 100:	
			m_nManualStep = 200;
			break;

		case 200:
			m_dwManualWaitTime[0] = GetTickCount();
			m_nManualStep = 300;
			break;

		case 300:
			m_dwManualWaitTime[1] = GetTickCount();
			m_dwManualWaitTime[2] = m_dwManualWaitTime[1] - m_dwManualWaitTime[0];
			
			if(m_dwManualWaitTime[2] <= 0)
			{
				m_dwManualWaitTime[0] = GetTickCount();
				break;
			}

			if(m_dwManualWaitTime[2] > (DWORD)500)
			{
				m_nManualStep = 400;
			}
			break;

		case 400:
			st_handler_info.nMachineMode = MACHINE_MANUAL;

			// 매뉴얼 모드로 변경되면 안전상 STOP 상태로 변경한다
			// jtkim 20130625
			clsFunc.OnMCStop();  // 설비 STOP 상태에 대한 버튼 램프 상태 변경
			//clsFunc.OnDoorOpen();  // SAFETY DOOR LOCK 해제
			m_nManualStep = 0;
			break;
	}
}


int CRunHandlerCheck::OnRunPossibleCheck()
{
	int i;
	CString strAlram;

	if (FAS_IO.get_in_bit(st_io_info.i_MainMcChk, IO_ON) == IO_OFF)
	{
		CTL_Lib.Alarm_Error_Occurrence(6000, dWARNING, _T("800108"));

		return RET_ERROR;
	}

	if (clsFunc.OnDoorOpenCheck() == RET_ERROR)
	{
		return RET_ERROR;
	}

	if (clsFunc.OnLightCurtainCheck() == RET_ERROR)
	{
		return RET_ERROR;
	}

	if (clsFunc.OnMpCheck() == RET_ERROR)
	{
		return RET_ERROR;
	}



	// 20150404 jtkim
	for (i=0; i<M_MAX_MOTOR_NUM; i++)
	{
		if(i == 10 || i == 11 || i == 23 || i == 24) continue; 

		if (COMI.mn_homechk_flag[i] == BD_NO)
		{
			strAlram.Format(_T("%02d0001"), i); 
			CTL_Lib.Alarm_Error_Occurrence(6000, dMOTOR_WARNING, strAlram);
			
			return BD_ERROR;
		}
	}

	return RET_GOOD;
}


void CRunHandlerCheck::OnLightCurtainCheck()
{
	int nRet;
	

	if (st_handler_info.nRunStatus == dSTOP) return;

	nRet = clsFunc.OnLightCurtainCheck();
}


