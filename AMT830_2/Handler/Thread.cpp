///////////////////////////////////////////////////////////////////////////////
/* ************************************************************************* */
// FILE NAME : Thread.cpp
//
// Copyright (C) 2001 DEnT Corporation
// All rights reserved.
//
// CREATED BY  : Lee Kyu Il
// REVISION    :
//     1> 2000. 09. 14 : Created by Lee Kyu Il
// DESCRIPTION :
//     Implementation of the Thread and associated classes
//	   This code may be used in compiled form in any way you desire. This
//	   file may be redistributed unmodified by any means PROVIDING it is
//	   not sold for profit without the authors written consent, and
//	   providing that this notice and the authors name and all copyright
//	   notices remains intact.
//
//	   An email letting me know how you are using it would be nice as well.
/* ************************************************************************* */
///////////////////////////////////////////////////////////////////////////////

#include "stdafx.h"
#include <iostream>

#include "afxmt.h"
#include "Thread.h"

//==================================================================//
#include "Variable.h"		// 전역 구조체
#include "MyJamData.h"		// 알람 발생 시 처리 클래스	
#include "RunTowerLamp.h"   // 타워 램프 제어 클래스
#include "RunReadIO.h"      // I/O 상태 읽기 클래스
#include "RunHandlerCheck.h"	// KEY BOX S/W 제어 클래스

// 시퀀스 과련 클래스 해더파일 추가할 것 . 
//kwlee 2017.0524
#include "Run_Front_HeatSnk_Rbt.h"
#include "Run_Front_HeatSnk_Stacker.h"
#include "Run_Rear_HeatSnk_Rbt.h"
#include "Run_Rear_HeatSnk_Stacker.h"
//
//------------------------------------------------------------------//

#include "ClientEcFirst.h"
#include "ServerFront.h"


#ifdef _DEBUG
#undef THIS_FILE
static char THIS_FILE[]=__FILE__;
#define new DEBUG_NEW
#endif

CMyJamData	m_clsAlarm;

CWinThread *m_thread[40];
HANDLE m_thrHandle[40];


//==================================================================//
// 전역 쓰레드 선언
//==================================================================//
UINT OnThreadHandlerCheck(LPVOID  lParam);		// m_thread[1]
UINT OnThreadReadIO(LPVOID lParam);				// m_thread[0]
UINT OnThreadTowerLamp(LPVOID lParam);			// m_thread[2]
UINT OnThreadAlarmDisplay(LPVOID lParam);		// m_thread[3]

//------------------------------------------------------------------//


CMutex mutex;
int AllStop[2];  // 쓰레드 강제 멈춤 플래그


//==================================================================//
// I/O 입출력 상태 읽기 쓰레드
//==================================================================//
UINT OnThreadHandlerCheck(LPVOID lParam)
{
	CSingleLock sing(&mutex);
	
	while(!AllStop[0])
	{
		sing.Lock();
		
		clsHdChk.OnStartCheck();   
		clsHdChk.OnStopCheck();
		clsHdChk.OnResetCheck();
		clsHdChk.OnBuzzerCheck();
		clsHdChk.OnAutoCheck();
		clsHdChk.OnManualCheck();
		clsHdChk.OnLightCurtainCheck();
		Sleep(0);
		sing.Unlock();
	}

	m_thrHandle[1] = NULL;
	return TRUE;
}

//==================================================================//
// I/O 입출력 상태 읽기 쓰레드
//==================================================================//
UINT OnThreadReadIO(LPVOID lParam)
{
	CSingleLock sing(&mutex);
	
	while(!AllStop[0])
	{
		sing.Lock();
		
		clsReadIO.OnThreadRun();
		
		Sleep(0);
		sing.Unlock();
	}

	m_thrHandle[0] = NULL;
	return TRUE;
}

//==================================================================//
// 타워 램프 상태 변경 쓰레드
//==================================================================//
UINT OnThreadTowerLamp(LPVOID lParam)
{
	CSingleLock sing(&mutex);

	while(!AllStop[0])
	{
		sing.Lock();

		clsTowerLamp.OnThreadRun();

		Sleep(0);
		sing.Unlock();
	}

	m_thrHandle[2] = NULL;
	return TRUE;
}

//==================================================================//
// 알람 출력 쓰레드
//==================================================================//
UINT OnThreadAlarmDisplay(LPVOID lParam)
{
	CSingleLock sing(&mutex);
	
	while(!AllStop[0])
	{
		sing.Lock();
		
		clsMyJamData.OnAlarmDisplay();  // 알람 발생한 경우 알람 화면 출력 함수
		
		Sleep(0);
		sing.Unlock();
	}

	m_thrHandle[3] = NULL;
	return TRUE;
}

//kwlee 2017.0524
UINT OnThreadFrontHeatSinkStacker(LPVOID lParam)
{
	CSingleLock sing(&mutex);

	while(!AllStop[0])
	{
		sing.Lock();

		clsRunHsFrontStacker.ThreadRun();

		Sleep(0);
		sing.Unlock();
	}

	m_thrHandle[4] = NULL;
	return TRUE;
}

UINT OnThreadFrontHeatSinkRbt(LPVOID lParam)
{
	CSingleLock sing(&mutex);

	while(!AllStop[0])
	{
		sing.Lock();

		
		clsRunHsFrontRbt.ThreadRun();
		Sleep(0);
		sing.Unlock();
	}

	m_thrHandle[5] = NULL;
	return TRUE;
}
//kwlee 2017.0601
UINT OnThreadRearHeatSinkStacker(LPVOID lParam)
{
	CSingleLock sing(&mutex);

	while(!AllStop[0])
	{
		sing.Lock();

		clsRunHsRearStacker.ThreadRun();

		Sleep(0);
		sing.Unlock();
	}

	m_thrHandle[6] = NULL;
	return TRUE;
}

UINT OnThreadRearHeatSinkRbt(LPVOID lParam)
{
	CSingleLock sing(&mutex);

	while(!AllStop[0])
	{
		sing.Lock();


		clsRunHsRearRbt.ThreadRun();
		Sleep(0);
		sing.Unlock();
	}

	m_thrHandle[7] = NULL;
	return TRUE;
}