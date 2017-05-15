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
#include "Variable.h"		// ���� ����ü
#include "MyJamData.h"		// �˶� �߻� �� ó�� Ŭ����	
#include "RunTowerLamp.h"   // Ÿ�� ���� ���� Ŭ����
#include "RunReadIO.h"      // I/O ���� �б� Ŭ����
#include "RunHandlerCheck.h"	// KEY BOX S/W ���� Ŭ����

// ������ ���� Ŭ���� �ش����� �߰��� �� . 
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
// ���� ������ ����
//==================================================================//
UINT OnThreadHandlerCheck(LPVOID  lParam);		// m_thread[1]
UINT OnThreadReadIO(LPVOID lParam);				// m_thread[0]
UINT OnThreadTowerLamp(LPVOID lParam);			// m_thread[2]
UINT OnThreadAlarmDisplay(LPVOID lParam);		// m_thread[3]

//------------------------------------------------------------------//


CMutex mutex;
int AllStop[2];  // ������ ���� ���� �÷���


//==================================================================//
// I/O ����� ���� �б� ������
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
// I/O ����� ���� �б� ������
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
// Ÿ�� ���� ���� ���� ������
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
// �˶� ��� ������
//==================================================================//
UINT OnThreadAlarmDisplay(LPVOID lParam)
{
	CSingleLock sing(&mutex);
	
	while(!AllStop[0])
	{
		sing.Lock();
		
		clsMyJamData.OnAlarmDisplay();  // �˶� �߻��� ��� �˶� ȭ�� ��� �Լ�
		
		Sleep(0);
		sing.Unlock();
	}

	m_thrHandle[3] = NULL;
	return TRUE;
}
