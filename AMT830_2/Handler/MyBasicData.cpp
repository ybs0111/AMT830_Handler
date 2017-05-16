// MyBasicData.cpp: implementation of the CMyBasicData class.
//
//////////////////////////////////////////////////////////////////////

#include "stdafx.h"
#include "handler.h"
#include "MyBasicData.h"
#include "Ctlbd_Variable.h"
#include "PublicFunction.h"
#include "FastechPublic_IO.h"

#ifdef _DEBUG
#undef THIS_FILE
static char THIS_FILE[]=__FILE__;
#define new DEBUG_NEW
#endif

CMyBasicData clsBasic;
//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////
CMyBasicData::CMyBasicData()
{

}

CMyBasicData::~CMyBasicData()
{

}

void CMyBasicData::OnPassWord_Load(CString strLoadLevel)
{
	CString strPass;
	CString strLoadFile;
	TCHAR chPass[25];

	(st_other_info.strPassword).Empty();		// ��ȣ ���� ���� �ʱ�ȭ

	strLoadFile = st_path_info.strBasic + st_basic_info.strDeviceName;

	if(strLoadLevel == _T("SysLock"))			// SYSTEM LOCK ��ȣ
	{
		:: GetPrivateProfileString(_T("Password"), _T("SysLock"), _T("M"), chPass, 20, strLoadFile);

	}
	else if (strLoadLevel == _T("Level1"))	// ����Ʈ ��ȣ
	{
		:: GetPrivateProfileString(_T("Password"), _T("Level_1"), _T("M"), chPass, 20, strLoadFile);
	}
	else if (strLoadLevel == _T("Level2"))	// ƼĪ ��ȣ
	{
		:: GetPrivateProfileString(_T("Password"), _T("Level_2"), _T("T"), chPass, 20, strLoadFile);
	}
	else  
	{
		return;
	}

	strPass.Format(_T("%s"), chPass);
	strPass.MakeUpper();     // ���ڿ� �빮�ڷ� ����
	strPass.TrimLeft(' ');   // ���� ���ڿ� ���� ����              
	strPass.TrimRight(' ');  // ���� ���ڿ� ���� ����

	st_other_info.strPassword = strPass;  // ��ȣ ���� ������ ����
}

void CMyBasicData::OnPassWord_Save(CString strSaveLevel, CString strPassData)
{
	CString strSaveFile;
	
	strSaveFile = st_path_info.strBasic + st_basic_info.strDeviceName;

	if (strSaveLevel=="SysLock")         // SYSTEM LOCK ��ȣ
	{
		:: WritePrivateProfileString(_T("Password"), _T("SysLock"), LPCTSTR(strPassData), strSaveFile);
	}
	else if (strSaveLevel=="Level1")  // ����Ʈ ��ȣ
	{
		:: WritePrivateProfileString(_T("Password"), _T("Level_1"), LPCTSTR(strPassData), strSaveFile);
	}
	else if (strSaveLevel=="Level2")  // ƼĪ ��ȣ
	{
		:: WritePrivateProfileString(_T("Password"), _T("Level_2"), LPCTSTR(strPassData), strSaveFile);
	}
}

CString CMyBasicData::OnStep_File_Index_Load()
{
	CString strLoadFile;
	char chLoad[20];

	strLoadFile = st_path_info.strBasic + st_basic_info.strDeviceName;

	:: GetPrivateProfileString(_T("Thread_Step_file"), _T("File_Index"), _T("00"), (LPWSTR)chLoad, 20, strLoadFile);
//	sprintf(chLoad,"%S", chLoad);
	strLoadFile = chLoad;
	strLoadFile.TrimLeft(' ');               
	strLoadFile.TrimRight(' ');

	return strLoadFile;  // ���� �ε��� ����
}

void CMyBasicData::OnStep_File_Index_Save(CString strIndex)
{
	CString strSaveFile;

	strSaveFile = st_path_info.strBasic + st_basic_info.strDeviceName;

	:: WritePrivateProfileString(_T("Thread_Step_file"), _T("File_Index"), LPCTSTR(strIndex), strSaveFile);
}

CString CMyBasicData::OnStep_File_Name_Load()
{
	CString strFileName;  // ���ϸ� ���� ����
	CString strLoadFile;
	char chLoad[20];

	strLoadFile = st_path_info.strBasic + st_basic_info.strDeviceName;

	:: GetPrivateProfileString(_T("Thread_Step_file"), _T("File_Name"), _T("DEFAULT"),(LPWSTR)chLoad, 20, strLoadFile);
//	sprintf(chLoad,"%S", chLoad);
	strFileName = chLoad;
	strFileName.TrimLeft(' ');               
	strFileName.TrimRight(' ');

	return strFileName;  // ���ϸ� ����
}

void CMyBasicData::OnStep_File_Name_Save(CString strFile)
{
	:: WritePrivateProfileString(_T("Thread_Step_file"), _T("File_Name"), LPCTSTR(strFile), st_path_info.strBasic);
}

void CMyBasicData::OnMotorSpeed_Set_Data_Load()
{
	int  nChk=0, i=0;
	double dChk;
	CString strTemp;       // �ӽ� ���� ����
	CString strMotorName;
	CString strLoadFile;	
	char chData[20];
	
	for(i = 0; i < MAXMOTOR; i++)
	{
		strMotorName.Format(_T("%02d_AXIS_SPEED"), i+1);
		:: GetPrivateProfileString(strMotorName, _T("ACC"), _T("100"), (LPWSTR)chData, 10, st_path_info.strFileBasic);
		strTemp.Format(_T("%s"), chData);
		dChk = _wtof(strTemp);
		st_motor_info[i].d_accel[0] = dChk;
		st_motor_info[i].d_spd_vel[1] = dChk;
		
		:: GetPrivateProfileString(strMotorName, _T("DEC"), _T("100"), (LPWSTR)chData, 10, st_path_info.strFileBasic);
		strTemp.Format(_T("%s"), chData);
		dChk = _wtof(strTemp);
		st_motor_info[i].d_decel[0] = dChk;
		st_motor_info[i].d_spd_vel[2] = dChk;
		
		:: GetPrivateProfileString(strMotorName, _T("MAX"), _T("100000"), (LPWSTR)chData, 10, st_path_info.strFileBasic);
		strTemp.Format(_T("%s"), chData);
		dChk = _wtof(strTemp);
		st_motor_info[i].d_spd_max[0] = dChk;
		
		:: GetPrivateProfileString(strMotorName, _T("VEL"), _T("1000"), (LPWSTR)chData, 10, st_path_info.strFileBasic);
		strTemp.Format(_T("%s"), chData);
		dChk = _wtof(strTemp);
		st_motor_info[i].d_spd_vel[0] = dChk;
		
		:: GetPrivateProfileString(strMotorName, _T("HOME"), _T("500"), (LPWSTR)chData, 10, st_path_info.strFileBasic);
		strTemp.Format(_T("%s"), chData);
		dChk = _wtof(strTemp);
		st_motor_info[i].d_spd_home[0] = dChk;
		
		:: GetPrivateProfileString(strMotorName, _T("JOG"), _T("300"), (LPWSTR)chData, 10, st_path_info.strFileBasic);
		strTemp.Format(_T("%s"), chData);
		dChk = _wtof(strTemp);
		st_motor_info[i].d_spd_jog[0] = dChk;
		
		:: GetPrivateProfileString(strMotorName, _T("VEL_PER"), _T("50"), (LPWSTR)chData, 10, st_path_info.strFileBasic);
		strTemp.Format(_T("%s"), chData);
		nChk = _wtoi(strTemp);
		st_motor_info[i].n_per_vel = nChk;
		
		:: GetPrivateProfileString(strMotorName, _T("HOME_PER"), _T("5"), (LPWSTR)chData, 10, st_path_info.strFileBasic);
		strTemp.Format(_T("%s"), chData);
		nChk = _wtoi(strTemp);
		st_motor_info[i].n_per_home = nChk;
		
		:: GetPrivateProfileString(strMotorName, _T("JOG_PER"), _T("5"), (LPWSTR)chData, 10, st_path_info.strFileBasic);
		strTemp.Format(_T("%s"), chData);
		nChk = _wtoi(strTemp);
		st_motor_info[i].n_per_jog = nChk;
		
		:: GetPrivateProfileString(strMotorName, _T("ALLOW"), _T("100"), (LPWSTR)chData, 10, st_path_info.strFileBasic);
		strTemp.Format(_T("%s"), chData);
		dChk = _wtof(strTemp);
		st_motor_info[i].d_allow = dChk;

		:: GetPrivateProfileString(strMotorName, _T("LIMIT_M"), _T("0"), (LPWSTR)chData, 10, st_path_info.strFileBasic);
		strTemp.Format(_T("%s"), chData);
		dChk = _wtof(strTemp);
		st_motor_info[i].d_limit_position[0] = dChk;

		:: GetPrivateProfileString(strMotorName, _T("LIMIT_P"), _T("3000"), (LPWSTR)chData, 10, st_path_info.strFileBasic);
		strTemp.Format(_T("%s"), chData);
		dChk = _wtof(strTemp);
		st_motor_info[i].d_limit_position[1] = dChk;
	}
	
	//Speed Rate
	:: GetPrivateProfileString(_T("SPEED_RATE"), _T("RUN"), _T("100"), (LPWSTR)chData, 10, st_path_info.strFileBasic);
	strTemp.Format(_T("%s"), chData);
	nChk = _wtoi(strTemp);
	st_handler_info.nRunSpeed = nChk;
	
	:: GetPrivateProfileString(_T("SPEED_RATE"), _T("MANUAL"), _T("80"), (LPWSTR)chData, 10, st_path_info.strFileBasic);
	strTemp.Format(_T("%s"), chData);
	nChk = _wtoi(strTemp);
	st_handler_info.nManualSpeed = nChk;
}

void CMyBasicData::OnMotorSpeed_Set_Data_Save()
{
	CString strTemp;       // �ӽ� ���� ����
	CString strMotorName;
	CString strSaveFile;
//	char chBuf[20];

	for(int i = 0; i < MAXMOTOR; i++)
	{
		strMotorName.Format(_T("%02d_AXIS_SPEED"), i+1);
//		LPCTSTR(_itoa((int)(st_motor_info[i].d_accel[0]), chBuf, 10));
		strTemp.Format(_T("%.3f"), st_motor_info[i].d_accel[0]);
		:: WritePrivateProfileString(strMotorName, _T("ACC"), LPCTSTR(strTemp), st_path_info.strFileBasic);
		
//		LPCTSTR(_itoa((int)(st_motor_info[i].d_decel[0]), chBuf, 10));
//		strTemp = chBuf;
		strTemp.Format(_T("%.3f"), st_motor_info[i].d_decel[0]);
		:: WritePrivateProfileString(strMotorName, _T("DEC"), LPCTSTR(strTemp), st_path_info.strFileBasic);
		
//		LPCTSTR(_itoa((int)(st_motor_info[i].d_spd_max[0]), chBuf, 10));
//		strTemp = chBuf;
		strTemp.Format(_T("%.3f"), st_motor_info[i].d_spd_max[0]);
		:: WritePrivateProfileString(strMotorName, _T("MAX"), LPCTSTR(strTemp), st_path_info.strFileBasic);
		
//		LPCTSTR(_itoa((int)(st_motor_info[i].d_spd_vel[0]), chBuf, 10));
//		strTemp = chBuf;
		strTemp.Format(_T("%.3f"), st_motor_info[i].d_spd_vel[0]);
		:: WritePrivateProfileString(strMotorName, _T("VEL"), LPCTSTR(strTemp), st_path_info.strFileBasic);
		
//		LPCTSTR(_itoa((int)(st_motor_info[i].d_spd_home[0]), chBuf, 10));
//		strTemp = chBuf;
		strTemp.Format(_T("%.3f"), st_motor_info[i].d_spd_home[0]);
		:: WritePrivateProfileString(strMotorName, _T("HOME"), LPCTSTR(strTemp), st_path_info.strFileBasic);
		
//		LPCTSTR(_itoa((int)(st_motor_info[i].d_spd_jog[0]), chBuf, 10));
//		strTemp = chBuf;
		strTemp.Format(_T("%.3f"), st_motor_info[i].d_spd_jog[0]);
		:: WritePrivateProfileString(strMotorName, _T("JOG"), LPCTSTR(strTemp), st_path_info.strFileBasic);
		
//		LPCTSTR(_itoa((st_motor_info[i].n_per_vel), chBuf, 10));
//		strTemp = chBuf;
		strTemp.Format(_T("%d"), st_motor_info[i].n_per_vel);
		:: WritePrivateProfileString(strMotorName, _T("VEL_PER"), LPCTSTR(strTemp), st_path_info.strFileBasic);
		
//		LPCTSTR(_itoa((st_motor_info[i].n_per_home), chBuf, 10));
//		strTemp = chBuf;
		strTemp.Format(_T("%d"), st_motor_info[i].n_per_home);
		:: WritePrivateProfileString(strMotorName, _T("HOME_PER"), LPCTSTR(strTemp), st_path_info.strFileBasic);
		
//		LPCTSTR(_itoa((st_motor_info[i].n_per_jog), chBuf, 10));
//		strTemp = chBuf;
		strTemp.Format(_T("%d"), st_motor_info[i].n_per_jog);
		:: WritePrivateProfileString(strMotorName, _T("JOG_PER"), LPCTSTR(strTemp), st_path_info.strFileBasic);
		

		strTemp.Format(_T("%.2f"), st_motor_info[i].d_allow);
		:: WritePrivateProfileString(strMotorName, _T("ALLOW"), LPCTSTR(strTemp), st_path_info.strFileBasic);
		
//		LPCTSTR(_itoa((int)(st_motor_info[i].d_limit_position[0]), chBuf, 10));
//		strTemp = chBuf;
		strTemp.Format(_T("%.3f"), st_motor_info[i].d_limit_position[0]);
		:: WritePrivateProfileString(strMotorName, _T("LIMIT_M"), LPCTSTR(strTemp), st_path_info.strFileBasic);

//		LPCTSTR(_itoa((int)(st_motor_info[i].d_limit_position[1]), chBuf, 10));
//		strTemp = chBuf;
		strTemp.Format(_T("%.3f"), st_motor_info[i].d_limit_position[1]);
		:: WritePrivateProfileString(strMotorName, _T("LIMIT_P"), LPCTSTR(strTemp), st_path_info.strFileBasic);
	}
	
	// Speed Rate
//	LPCTSTR(_itoa((int)(st_handler_info.nRunSpeed), chBuf, 10));
//	strTemp = chBuf;
	strTemp.Format(_T("%d"), st_handler_info.nRunSpeed);
	:: WritePrivateProfileString(_T("SPEED_RATE"), _T("RUN"), LPCTSTR(strTemp), st_path_info.strFileBasic);
	
//	LPCTSTR(_itoa((int)(st_handler_info.nManualSpeed), chBuf, 10));
//	strTemp = chBuf;
	strTemp.Format(_T("%d"), st_handler_info.nManualSpeed);
	:: WritePrivateProfileString(_T("SPEED_RATE"), _T("MANUAL"), LPCTSTR(strTemp), st_path_info.strFileBasic);
}

void CMyBasicData::OnWaitTime_Data_Load()
{
	CString strTemp, strMsg, strHead;       // �ӽ� ���� ����
	CString strLoadFile, strOnName, strOffName, strLimitName;
	int nChk, i;
	char chData[20];

	for(i=0; i<MAX_WAIT_TIME; i++)
	{
		strHead.Format(_T("TIME_[%02d]"), i);
		
		strOnName.Format(_T("%s_ON"), strHead);
		:: GetPrivateProfileString(_T("ON_WAIT_TIME"), strOnName, _T("100"), (LPWSTR)chData, 10, st_path_info.strFileBasic);
		strTemp.Format(_T("%s"), chData);
		nChk = _wtoi(strTemp);
		st_wait_info.nOnWaitTime[i] = nChk;
		
		strOffName.Format(_T("%s_OFF"), strHead);
		:: GetPrivateProfileString(_T("OFF_WAIT_TIME"), strOffName, _T("100"), (LPWSTR)chData, 10, st_path_info.strFileBasic);
		strTemp.Format(_T("%s"), chData);
		nChk = _wtoi(strTemp);
		st_wait_info.nOffWaitTime[i] = nChk;
		
		strLimitName.Format(_T("%s_LIMIT"), strHead);
		:: GetPrivateProfileString(_T("LIMIT_TIME"), strLimitName, _T("100"), (LPWSTR)chData, 10, st_path_info.strFileBasic);
		strTemp.Format(_T("%s"), chData);
		nChk = _wtoi(strTemp);
		st_wait_info.nLimitWaitTime[i] = nChk;
	}
}

void CMyBasicData::OnWaitTime_Data_Save()
{
	CString strTemp, strPart;  // �ε� ���� �ӽ� ���� ����
	CString strSaveFile;
	CString strOnName, strOffName, strLimitName;
	CString strData;
	int i;
	
	for(i=0; i<MAX_WAIT_TIME; i++)
	{
		strTemp.Format(_T("TIME_[%02d]"), i);
		
		strOnName.Format(_T("%s_ON"), strTemp);
		strData.Format(_T("%d"), st_wait_info.nOnWaitTime[i]);
		:: WritePrivateProfileString(_T("ON_WAIT_TIME"), strOnName, LPCTSTR(strData), st_path_info.strFileBasic);
		
		strOffName.Format(_T("%s_OFF"), strTemp);
		strData.Format(_T("%d"), st_wait_info.nOffWaitTime[i]);
		:: WritePrivateProfileString(_T("OFF_WAIT_TIME"), strOffName, LPCTSTR(strData), st_path_info.strFileBasic);
		
		strLimitName.Format(_T("%s_LIMIT"), strTemp);
		strData.Format(_T("%d"), st_wait_info.nLimitWaitTime[i]);
		:: WritePrivateProfileString(_T("LIMIT_TIME"), strLimitName, LPCTSTR(strData), st_path_info.strFileBasic);	
	}
}

void CMyBasicData::OnMaintenance_Data_Load()
{
	CString strTemp, strPart;  // �ε� ���� �ӽ� ���� ����
	int nChk;
	CString strLoadFile;
	
	char chData[20];
	
	// **************************************************************************
	// Ÿ�� ���� RED ���� �ε��Ͽ� ���� ������ �����Ѵ�                          
	// ->  STOP			= 0,
	// 		   RUN			= 1,
	// 		   ALARM		= 2,
	// 		   LOTEND		= 3,
	// 		   INIT			= 4,
	// 		   WARRING		= 5,
	// 		   LOCK			= 6,
	// 		   SELFCHECK	= 7														 
	// -> �ε� �� [0:OFF    1:ON    2:FLICKER]                                   
	// **************************************************************************
//	str_load_file = st_path.str_basic + st_basic.str_device_name;  // ƼĪ ������ ���� ���� ����
	strLoadFile = st_path_info.strBasic + _T("Maintenance.TXT");  // ƼĪ ������ ���� ���� ����

	:: GetPrivateProfileString(_T("TowerLampData_Red"), _T("Stop_State"), _T("0"), (LPWSTR)chData, 10, strLoadFile);
	strTemp.Format(_T("%s"), chData);
	nChk = _wtoi(strTemp);
	if (nChk<0 || nChk>2)
	{
		st_lamp_info.nLampR[0] = 0;
	}
	else
	{
		st_lamp_info.nLampR[0] = nChk;
	}
	
	:: GetPrivateProfileString(_T("TowerLampData_Red"), _T("Run_State"), _T("0"), (LPWSTR)chData, 10, strLoadFile);
	strTemp.Format(_T("%s"), chData);
	nChk = _wtoi(strTemp);
	if (nChk<0 || nChk>2)
	{
		st_lamp_info.nLampR[1] = 0;
	}
	else
	{
		st_lamp_info.nLampR[1] = nChk;
	}
	
	:: GetPrivateProfileString(_T("TowerLampData_Red"), _T("Alarm_State"), _T("0"), (LPWSTR)chData, 10, strLoadFile);
	strTemp.Format(_T("%s"), chData);
	nChk = _wtoi(strTemp);
	if (nChk<0 || nChk>2)
	{
		st_lamp_info.nLampR[2] = 2;
	}
	else
	{
		st_lamp_info.nLampR[2] = nChk;
	}

	:: GetPrivateProfileString(_T("TowerLampData_Red"), _T("LotEnd_State"), _T("0"), (LPWSTR)chData, 10, strLoadFile);
	strTemp.Format(_T("%s"), chData);
	nChk = _wtoi(strTemp);
	if (nChk<0 || nChk>2)
	{
		st_lamp_info.nLampR[3] = 2;
	}
	else
	{
		st_lamp_info.nLampR[3] = nChk;
	}

	:: GetPrivateProfileString(_T("TowerLampData_Red"), _T("Initial_State"), _T("0"), (LPWSTR)chData, 10, strLoadFile);
	strTemp.Format(_T("%s"), chData);
	nChk = _wtoi(strTemp);
	if (nChk<0 || nChk>2)
	{
		st_lamp_info.nLampR[4] = 2;
	}
	else
	{
		st_lamp_info.nLampR[4] = nChk;
	}

	:: GetPrivateProfileString(_T("TowerLampData_Red"), _T("Warring_State"), _T("0"), (LPWSTR)chData, 10, strLoadFile);
	strTemp.Format(_T("%s"), chData);
	nChk = _wtoi(strTemp);
	if (nChk<0 || nChk>2)
	{
		st_lamp_info.nLampR[5] = 2;
	}
	else
	{
		st_lamp_info.nLampR[5] = nChk;
	}

	:: GetPrivateProfileString(_T("TowerLampData_Red"), _T("Lock_State"), _T("0"), (LPWSTR)chData, 10, strLoadFile);
	strTemp.Format(_T("%s"), chData);
	nChk = _wtoi(strTemp);
	if (nChk<0 || nChk>2)
	{
		st_lamp_info.nLampR[6] = 2;
	}
	else
	{
		st_lamp_info.nLampR[6] = nChk;
	}

	:: GetPrivateProfileString(_T("TowerLampData_Red"), _T("SelfCheck_State"), _T("0"), (LPWSTR)chData, 10, strLoadFile);
	strTemp.Format(_T("%s"), chData);
	nChk = _wtoi(strTemp);
	if (nChk<0 || nChk>2)
	{
		st_lamp_info.nLampR[7] = 2;
	}
	else
	{
		st_lamp_info.nLampR[7] = nChk;
	}

	:: GetPrivateProfileString(_T("TowerLampData_Red"), _T("Idle_State"), _T("0"), (LPWSTR)chData, 10, strLoadFile);
	strTemp.Format(_T("%s"), chData);
	nChk = _wtoi(strTemp);
	if (nChk<0 || nChk>2)
	{
		st_lamp_info.nLampR[8] = 2;
	}
	else
	{
		st_lamp_info.nLampR[8] = nChk;
	}
	// **************************************************************************


	// **************************************************************************
	// Ÿ�� ���� YELLOW ���� �ε��Ͽ� ���� ������ �����Ѵ�                       
	// ->  STOP			= 0,
// 		   RUN			= 1,
// 		   ALARM		= 2,
// 		   LOTEND		= 3,
// 		   INIT			= 4,
// 		   WARRING		= 5,
// 		   LOCK			= 6,
// 		   SELFCHECK	= 7														 
	// -> �ε� �� [0:OFF    1:ON    2:FLICKER]                                   
	// **************************************************************************
	:: GetPrivateProfileString(_T("TowerLampData_Yellow"), _T("Stop_State"), _T("0"), (LPWSTR)chData, 10, strLoadFile);
	strTemp.Format(_T("%s"), chData);
	nChk = _wtoi(strTemp);
	if (nChk<0 || nChk>2)
	{
		st_lamp_info.nLampY[0] = 0;
	}
	else
	{
		st_lamp_info.nLampY[0] = nChk;
	}

	:: GetPrivateProfileString(_T("TowerLampData_Yellow"), _T("Run_State"), _T("0"), (LPWSTR)chData, 10, strLoadFile);
	strTemp.Format(_T("%s"), chData);
	nChk = _wtoi(strTemp);
	if (nChk<0 || nChk>2)
	{
		st_lamp_info.nLampY[1] = 1;
	}
	else
	{
		st_lamp_info.nLampY[1] = nChk;
	}

	:: GetPrivateProfileString(_T("TowerLampData_Yellow"), _T("Alarm_State"), _T("0"), (LPWSTR)chData, 10, strLoadFile);
	strTemp.Format(_T("%s"), chData);
	nChk = _wtoi(strTemp);
	if (nChk<0 || nChk>2)
	{
		st_lamp_info.nLampY[2] = 0;
	}
	else
	{
		st_lamp_info.nLampY[2] = nChk;
	}

	:: GetPrivateProfileString(_T("TowerLampData_Yellow"), _T("LotEnd_State"), _T("0"), (LPWSTR)chData, 10, strLoadFile);
	strTemp.Format(_T("%s"), chData);
	nChk = _wtoi(strTemp);
	if (nChk<0 || nChk>2)
	{
		st_lamp_info.nLampY[3] = 2;
	}
	else
	{
		st_lamp_info.nLampY[3] = nChk;
	}

	:: GetPrivateProfileString(_T("TowerLampData_Yellow"), _T("Initial_State"), _T("0"), (LPWSTR)chData, 10, strLoadFile);
	strTemp.Format(_T("%s"), chData);
	nChk = _wtoi(strTemp);
	if (nChk<0 || nChk>2)
	{
		st_lamp_info.nLampY[4] = 2;
	}
	else
	{
		st_lamp_info.nLampY[4] = nChk;
	}

	:: GetPrivateProfileString(_T("TowerLampData_Yellow"), _T("Warring_State"), _T("0"), (LPWSTR)chData, 10, strLoadFile);
	strTemp.Format(_T("%s"), chData);
	nChk = _wtoi(strTemp);
	if (nChk<0 || nChk>2)
	{
		st_lamp_info.nLampY[5] = 2;
	}
	else
	{
		st_lamp_info.nLampY[5] = nChk;
	}

	:: GetPrivateProfileString(_T("TowerLampData_Yellow"), _T("Lock_State"), _T("0"), (LPWSTR)chData, 10, strLoadFile);
	strTemp.Format(_T("%s"), chData);
	nChk = _wtoi(strTemp);
	if (nChk<0 || nChk>2)
	{
		st_lamp_info.nLampY[6] = 2;
	}
	else
	{
		st_lamp_info.nLampY[6] = nChk;
	}

	:: GetPrivateProfileString(_T("TowerLampData_Yellow"), _T("SelfCheck_State"), _T("0"), (LPWSTR)chData, 10, strLoadFile);
	strTemp.Format(_T("%s"), chData);
	nChk = _wtoi(strTemp);
	if (nChk<0 || nChk>2)
	{
		st_lamp_info.nLampY[7] = 2;
	}
	else
	{
		st_lamp_info.nLampY[7] = nChk;
	}

	:: GetPrivateProfileString(_T("TowerLampData_Yellow"), _T("Idle_State"), _T("0"), (LPWSTR)chData, 10, strLoadFile);
	strTemp.Format(_T("%s"), chData);
	nChk = _wtoi(strTemp);
	if (nChk<0 || nChk>2)
	{
		st_lamp_info.nLampY[8] = 2;
	}
	else
	{
		st_lamp_info.nLampY[8] = nChk;
	}
	// **************************************************************************

	// **************************************************************************
	// Ÿ�� ���� GREEN ���� �ε��Ͽ� ���� ������ �����Ѵ�                        
	// ->  STOP			= 0,
// 		   RUN			= 1,
// 		   ALARM		= 2,
// 		   LOTEND		= 3,
// 		   INIT			= 4,
// 		   WARRING		= 5,
// 		   LOCK			= 6,
// 		   SELFCHECK	= 7														 
	// -> �ε� �� [0:OFF    1:ON    2:FLICKER]                                   
	// **************************************************************************
	:: GetPrivateProfileString(_T("TowerLampData_Green"), _T("Stop_State"), _T("0"), (LPWSTR)chData, 10, strLoadFile);
	strTemp.Format(_T("%s"), chData);
	nChk = _wtoi(strTemp);
	if (nChk<0 || nChk>2)
	{
		st_lamp_info.nLampG[0] = 1;
	}
	else
	{
		st_lamp_info.nLampG[0] = nChk;
	}

	:: GetPrivateProfileString(_T("TowerLampData_Green"), _T("Run_State"), _T("0"), (LPWSTR)chData, 10, strLoadFile);
	strTemp.Format(_T("%s"), chData);
	nChk = _wtoi(strTemp);
	if (nChk<0 || nChk>2)
	{
		st_lamp_info.nLampG[1] = 0;
	}
	else
	{
		st_lamp_info.nLampG[1] = nChk;
	}

	:: GetPrivateProfileString(_T("TowerLampData_Green"), _T("Alarm_State"), _T("0"), (LPWSTR)chData, 10, strLoadFile);
	strTemp.Format(_T("%s"), chData);
	nChk = _wtoi(strTemp);
	if (nChk<0 || nChk>2)
	{
		st_lamp_info.nLampG[2] = 0;
	}
	else
	{
		st_lamp_info.nLampG[2] = nChk;
	}

	:: GetPrivateProfileString(_T("TowerLampData_Green"), _T("LotEnd_State"), _T("0"), (LPWSTR)chData, 10, strLoadFile);
	strTemp.Format(_T("%s"), chData);
	nChk = _wtoi(strTemp);
	if (nChk<0 || nChk>2)
	{
		st_lamp_info.nLampG[3] = 2;
	}
	else
	{
		st_lamp_info.nLampG[3] = nChk;
	}

	:: GetPrivateProfileString(_T("TowerLampData_Green"), _T("Initial_State"), _T("0"), (LPWSTR)chData, 10, strLoadFile);
	strTemp.Format(_T("%s"), chData);
	nChk = _wtoi(strTemp);
	if (nChk<0 || nChk>2)
	{
		st_lamp_info.nLampG[4] = 2;
	}
	else
	{
		st_lamp_info.nLampG[4] = nChk;
	}

	:: GetPrivateProfileString(_T("TowerLampData_Green"), _T("Warring_State"), _T("0"), (LPWSTR)chData, 10, strLoadFile);
	strTemp.Format(_T("%s"), chData);
	nChk = _wtoi(strTemp);
	if (nChk<0 || nChk>2)
	{
		st_lamp_info.nLampG[5] = 2;
	}
	else
	{
		st_lamp_info.nLampG[5] = nChk;
	}

	:: GetPrivateProfileString(_T("TowerLampData_Green"), _T("Lock_State"), _T("0"), (LPWSTR)chData, 10, strLoadFile);
	strTemp.Format(_T("%s"), chData);
	nChk = _wtoi(strTemp);
	if (nChk<0 || nChk>2)
	{
		st_lamp_info.nLampG[6] = 2;
	}
	else
	{
		st_lamp_info.nLampG[6] = nChk;
	}

	:: GetPrivateProfileString(_T("TowerLampData_Green"), _T("SelfCheck_State"), _T("0"), (LPWSTR)chData, 10, strLoadFile);
	strTemp.Format(_T("%s"), chData);
	nChk = _wtoi(strTemp);
	if (nChk<0 || nChk>2)
	{
		st_lamp_info.nLampG[7] = 2;
	}
	else
	{
		st_lamp_info.nLampG[7] = nChk;
	}

	:: GetPrivateProfileString(_T("TowerLampData_Green"), _T("Idle_State"), _T("0"), (LPWSTR)chData, 10, strLoadFile);
	strTemp.Format(_T("%s"), chData);
	nChk = _wtoi(strTemp);
	if (nChk<0 || nChk>2)
	{
		st_lamp_info.nLampG[8] = 2;
	}
	else
	{
		st_lamp_info.nLampG[8] = nChk;
	}
	// **************************************************************************

	// **************************************************************************
	// ���� ��� ��� �ε��Ͽ� ���� ������ ����                                  
	// -> 0:���    1:�̻��                                                     
	// **************************************************************************
	:: GetPrivateProfileString(_T("TowerLampData"), _T("n_buzzer_mode"), _T("0"), (LPWSTR)chData, 10, strLoadFile);
	strTemp.Format(_T("%s"), chData);
	nChk = _wtoi(strTemp);
	if (nChk<0 || nChk>1)
	{
		st_lamp_info.nBuzzerMode = 1;
	}
	else
	{
		st_lamp_info.nBuzzerMode = nChk;
	}
	// **************************************************************************

	// **************************************************************************
	// ��� ȣ�� �� ��� �ڵ� �ε��Ͽ� ���� ������ ����                          
	// -> �ε� �������� ��/�� ������ �����Ѵ�                                    
	// **************************************************************************
	:: GetPrivateProfileString(_T("TowerLampData"), _T("str_equip_no"), _T("AMT"), (LPWSTR)chData, 20, strLoadFile);
//	sprintf(chData,"%S", chData);
	st_lamp_info.strEquipNo.Format(_T("%s"), chData);
	(st_lamp_info.strEquipNo).TrimLeft(' ');               
	(st_lamp_info.strEquipNo).TrimRight(' ');

	:: GetPrivateProfileString(_T("TowerLampData"), _T("str_equip_code"), _T("AMT"), (LPWSTR)chData, 20, strLoadFile);
//	sprintf(chData,"%S", chData);
	st_lamp_info.strEquipCode.Format(_T("%s"), chData);
	(st_lamp_info.strEquipCode).TrimLeft(' ');               
	(st_lamp_info.strEquipCode).TrimRight(' ');
	// **************************************************************************

	// **************************************************************************
	// Ÿ�� ���� ON/OFF ��� �ð� �ε��Ͽ� ���� ������ ����                      
	// **************************************************************************
	:: GetPrivateProfileString(_T("TowerLampData"), _T("n_lamp_on_time_w"), _T("0"), (LPWSTR)chData, 10, strLoadFile);
	strTemp.Format(_T("%s"), chData);
	nChk = _wtoi(strTemp);
	if (nChk < 1)
	{
		st_lamp_info.nLampWaitTime = 500;
	}
	else
	{
		st_lamp_info.nLampWaitTime = nChk;
	}
	// ***************************************************************************/
}

void CMyBasicData::OnMaintenance_Data_Save()
{
	CString strTemp, strPart;  // �ε� ���� �ӽ� ���� ����
	CString strSaveFile;;

	// **************************************************************************
	// Ÿ�� ���� RED ���� ������ ���Ͽ� �����Ѵ�                                 
	// ->  STOP			= 0,
// 		   RUN			= 1,
// 		   ALARM		= 2,
// 		   LOTEND		= 3,
// 		   INIT			= 4,
// 		   WARRING		= 5,
// 		   LOCK			= 6,
// 		   SELFCHECK	= 7														 
	// -> �ε� �� [0:OFF    1:ON    2:FLICKER]                                   
	// **************************************************************************
//	str_save_file = st_path.str_basic + st_basic.str_device_name;  // ƼĪ ������ ���� ���� ����
	strSaveFile = st_path_info.strBasic + _T("Maintenance.TXT");

	strTemp.Format(_T("%d"), st_lamp_info.nLampR[0]) ;
	:: WritePrivateProfileString(_T("TowerLampData_Red"), _T("Stop_State"), LPCTSTR(strTemp), strSaveFile);

	strTemp.Format(_T("%d"),st_lamp_info.nLampR[1]) ;
	:: WritePrivateProfileString(_T("TowerLampData_Red"), _T("Run_State"), LPCTSTR(strTemp), strSaveFile);

	strTemp.Format(_T("%d"),st_lamp_info.nLampR[2]) ;
	:: WritePrivateProfileString(_T("TowerLampData_Red"), _T("Alarm_State"), LPCTSTR(strTemp), strSaveFile);

	strTemp.Format(_T("%d"),st_lamp_info.nLampR[3]) ;
	:: WritePrivateProfileString(_T("TowerLampData_Red"), _T("LotEnd_State"), LPCTSTR(strTemp), strSaveFile);

	strTemp.Format(_T("%d"),st_lamp_info.nLampR[4]) ;
	:: WritePrivateProfileString(_T("TowerLampData_Red"), _T("Initial_State"), LPCTSTR(strTemp), strSaveFile);

	strTemp.Format(_T("%d"),st_lamp_info.nLampR[5]) ;
	:: WritePrivateProfileString(_T("TowerLampData_Red"), _T("Warring_State"), LPCTSTR(strTemp), strSaveFile);

	strTemp.Format(_T("%d"),st_lamp_info.nLampR[6]) ;
	:: WritePrivateProfileString(_T("TowerLampData_Red"), _T("Lock_State"), LPCTSTR(strTemp), strSaveFile);

	strTemp.Format(_T("%d"),st_lamp_info.nLampR[7]) ;
	:: WritePrivateProfileString(_T("TowerLampData_Red"), _T("SelfCheck_State"), LPCTSTR(strTemp), strSaveFile);

	strTemp.Format(_T("%d"),st_lamp_info.nLampR[8]) ;
	:: WritePrivateProfileString(_T("TowerLampData_Red"), _T("Idle_State"), LPCTSTR(strTemp), strSaveFile);
	// **************************************************************************


	// **************************************************************************
	// Ÿ�� ���� YELLOW ���� ������ ���Ͽ� �����Ѵ�                              
	// ->  STOP			= 0,
// 		   RUN			= 1,
// 		   ALARM		= 2,
// 		   LOTEND		= 3,
// 		   INIT			= 4,
// 		   WARRING		= 5,
// 		   LOCK			= 6,
// 		   SELFCHECK	= 7														 
	// -> �ε� �� [0:OFF    1:ON    2:FLICKER]                                   
	// **************************************************************************
	strTemp.Format(_T("%d"),st_lamp_info.nLampY[0]) ;
	:: WritePrivateProfileString(_T("TowerLampData_Yellow"), _T("Stop_State"), LPCTSTR(strTemp), strSaveFile);

	strTemp.Format(_T("%d"),st_lamp_info.nLampY[1]) ;
	:: WritePrivateProfileString(_T("TowerLampData_Yellow"), _T("Run_State"), LPCTSTR(strTemp), strSaveFile);

	strTemp.Format(_T("%d"),st_lamp_info.nLampY[2]) ;
	:: WritePrivateProfileString(_T("TowerLampData_Yellow"), _T("Alarm_State"), LPCTSTR(strTemp), strSaveFile);

	strTemp.Format(_T("%d"),st_lamp_info.nLampY[3]) ;
	:: WritePrivateProfileString(_T("TowerLampData_Yellow"), _T("LotEnd_State"), LPCTSTR(strTemp), strSaveFile);

	strTemp.Format(_T("%d"),st_lamp_info.nLampY[4]) ;
	:: WritePrivateProfileString(_T("TowerLampData_Yellow"), _T("Initial_State"), LPCTSTR(strTemp), strSaveFile);

	strTemp.Format(_T("%d"),st_lamp_info.nLampY[5]) ;
	:: WritePrivateProfileString(_T("TowerLampData_Yellow"), _T("Warring_State"), LPCTSTR(strTemp), strSaveFile);

	strTemp.Format(_T("%d"),st_lamp_info.nLampY[6]) ;
	:: WritePrivateProfileString(_T("TowerLampData_Yellow"), _T("Lock_State"), LPCTSTR(strTemp), strSaveFile);

	strTemp.Format(_T("%d"),st_lamp_info.nLampY[7]) ;
	:: WritePrivateProfileString(_T("TowerLampData_Yellow"), _T("SelfCheck_State"), LPCTSTR(strTemp), strSaveFile);

	strTemp.Format(_T("%d"),st_lamp_info.nLampY[8]) ;
	:: WritePrivateProfileString(_T("TowerLampData_Yellow"), _T("Idle_State"), LPCTSTR(strTemp), strSaveFile);

	// **************************************************************************

	// **************************************************************************
	// Ÿ�� ���� GREEN ���� ������ ���Ͽ� �����Ѵ�                               
	// ->  STOP			= 0,
// 		   RUN			= 1,
// 		   ALARM		= 2,
// 		   LOTEND		= 3,
// 		   INIT			= 4,
// 		   WARRING		= 5,
// 		   LOCK			= 6,
// 		   SELFCHECK	= 7														 
	// -> �ε� �� [0:OFF    1:ON    2:FLICKER]                                   
	// **************************************************************************
	strTemp.Format(_T("%d"),st_lamp_info.nLampG[0]) ;
	:: WritePrivateProfileString(_T("TowerLampData_Green"), _T("Stop_State"), LPCTSTR(strTemp), strSaveFile);

	strTemp.Format(_T("%d"),st_lamp_info.nLampG[1]) ;
	:: WritePrivateProfileString(_T("TowerLampData_Green"), _T("Run_State"), LPCTSTR(strTemp), strSaveFile);

	strTemp.Format(_T("%d"),st_lamp_info.nLampG[2]) ;
	:: WritePrivateProfileString(_T("TowerLampData_Green"), _T("Alarm_State"), LPCTSTR(strTemp), strSaveFile);

	strTemp.Format(_T("%d"),st_lamp_info.nLampG[3]) ;
	:: WritePrivateProfileString(_T("TowerLampData_Green"), _T("LotEnd_State"), LPCTSTR(strTemp), strSaveFile);

	strTemp.Format(_T("%d"),st_lamp_info.nLampG[4]) ;
	:: WritePrivateProfileString(_T("TowerLampData_Green"), _T("Initial_State"), LPCTSTR(strTemp), strSaveFile);

	strTemp.Format(_T("%d"),st_lamp_info.nLampG[5]) ;
	:: WritePrivateProfileString(_T("TowerLampData_Green"), _T("Warring_State"), LPCTSTR(strTemp), strSaveFile);

	strTemp.Format(_T("%d"),st_lamp_info.nLampG[6]) ;
	:: WritePrivateProfileString(_T("TowerLampData_Green"), _T("Lock_State"), LPCTSTR(strTemp), strSaveFile);

	strTemp.Format(_T("%d"),st_lamp_info.nLampG[7]) ;
	:: WritePrivateProfileString(_T("TowerLampData_Green"), _T("SelfCheck_State"), LPCTSTR(strTemp), strSaveFile);

	strTemp.Format(_T("%d"),st_lamp_info.nLampG[8]) ;
	:: WritePrivateProfileString(_T("TowerLampData_Green"), _T("Idle_State"), LPCTSTR(strTemp), strSaveFile);
	// **************************************************************************

	// **************************************************************************
	// ���� ��� ��� �ε��Ͽ� ���� ������ ����                                  
	// -> 0:���    1:�̻��                                                     
	// **************************************************************************
	strTemp.Format(_T("%d"),st_lamp_info.nBuzzerMode) ;
	:: WritePrivateProfileString(_T("TowerLampData"), _T("n_buzzer_mode"), LPCTSTR(strTemp), strSaveFile);
	// **************************************************************************

	// **************************************************************************
	// ��� ȣ�� �� ��� �ڵ� �ε��Ͽ� ���� ������ ����                          
	// -> �ε� �������� ��/�� ������ �����Ѵ�                                    
	// **************************************************************************
	:: WritePrivateProfileString(_T("TowerLampData"), _T("str_equip_no"), LPCTSTR(st_lamp_info.strEquipNo), strSaveFile);
	:: WritePrivateProfileString(_T("TowerLampData"), _T("str_equip_code"), LPCTSTR(st_lamp_info.strEquipCode), strSaveFile);
	// **************************************************************************

	// **************************************************************************
	// Ÿ�� ���� ON/OFF ��� �ð� �ε��Ͽ� ���� ������ ����                      
	// **************************************************************************
	strTemp.Format(_T("%d"),st_lamp_info.nLampWaitTime);
	:: WritePrivateProfileString(_T("TowerLampData"), _T("n_lamp_on_time_w"), LPCTSTR(strTemp), strSaveFile);
}

void CMyBasicData::OnModuleRobot_Teach_Data_Save()
{
	CString strTemp, strMsg, strSaveFail;       // �ӽ� ���� ����
	CString strPos;
	CString strHead, strItem;
	int i, j;
	
	strSaveFail = st_path_info.strFileMotor + st_basic_info.strDeviceName;
	
	for(i=0; i<MAXMOTOR; i++)
	{
		strHead.Format(_T("Motor%d"),i+1);
		for(j=0; j<M_MAX_POS; j++)
		{
			strItem.Format(_T("%02d_Axis_[%02d]"), i+1, j+1); 
			strTemp.Format(_T("%.3f"), st_motor_info[i].d_pos[j]);
			:: WritePrivateProfileString(strHead, strItem, LPCTSTR(strTemp), strSaveFail);
		}
	}
}

void CMyBasicData::OnModuleRobot_Teach_Data_Load()
{
	CString strTemp, strMsg, strSaveFail;       // �ӽ� ���� ����
	CString strPos;
	CString strHead, strItem;
	int i, j;
	char chData[100];

	strSaveFail = st_path_info.strFileMotor + st_basic_info.strDeviceName;
	
	for(i=0; i<MAXMOTOR; i++)
	{
		strHead.Format(_T("Motor%d"),i+1);
		for(j=0; j<M_MAX_POS; j++)
		{
			strItem.Format(_T("%02d_Axis_[%02d]"), i+1, j+1); 
			:: GetPrivateProfileString(strHead, strItem, _T("0.0"), (LPWSTR)chData, 10, strSaveFail);
			strTemp.Format(_T("%s"), chData);
			st_motor_info[i].d_pos[j] = _wtof(strTemp);;
		}
	}
}

void CMyBasicData::OnModuleRobot_Teach_Data_Load(CString strDeviceName)
{
	CString strTemp, strMsg, strSaveFail;       // �ӽ� ���� ����
	CString strPos;
	CString strHead, strItem;
	int i, j;
	char chData[100];

	strSaveFail = st_path_info.strFileMotor + strDeviceName;
	
	for(i=0; i<MAXMOTOR; i++)
	{
		strHead.Format(_T("Motor%d"),i+1);
		for(j=0; j<M_MAX_POS; j++)
		{
			strItem.Format(_T("%02d_Axis_[%02d]"), i+1, j+1); 
			:: GetPrivateProfileString(strHead, strItem, _T("0.0"), (LPWSTR)chData, 10, strSaveFail);
			strTemp.Format(_T("%s"), chData);
			st_motor_info[i].d_pos[j] = _wtof(strTemp);;
		}
	}
}

void CMyBasicData::OnBasic_Data_Load(int nMode)
{
	CString str_load_device;	// �ε� ����̽��� ���� ����
	CString str_load_pgm;		// �ε� ����̽��� ���� ����
	CString str_load_file;
	CString str_chk_ext;		// ���� Ȯ���� ���� ����
	CString str_temp, stemp;	// ������ ���� �ӽ� ���� ���� 
	CString strTemp;
	CString str_pos;
	TCHAR chr_data[50], chr_buf[20];
	TCHAR chData[50];
	int mn_chk, i, j;
	double md_chk;

	memset(&chr_data, 0, sizeof(chr_data));
	memset(&chr_buf, 0, sizeof(chr_buf));

	// ���� ���ϸ� ��������
	if(st_basic_info.strDeviceName == "")
	{
		GetPrivateProfileString(_T("FILE_NAME"), _T("Device_Type"), _T("DEFAULT.TXT"), chr_data, sizeof(chr_data), st_path_info.strFileBasic);
		st_basic_info.strDeviceName = (LPCTSTR)chr_data;
	}
	// ���� ��� 
	str_load_file = st_path_info.strBasic + st_basic_info.strDeviceName;  // ƼĪ ������ ���� ���� ����

	//st_basic_info.nCtrlMode = EQP_OFF_LINE;

	GetPrivateProfileString(_T("BASIC_SCREEN"), _T("strEqp"), _T(""), chr_data, sizeof(chr_data), st_path_info.strFileBasic);
	st_basic_info.strEqp = (LPCTSTR)chr_data;

	if (nMode == 0)
	{
		GetPrivateProfileString(_T("BASIC_SCREEN"), _T("nModeInterface"), _T("1"), chr_data, sizeof(chr_data), st_path_info.strFileBasic);
		str_temp.Format(_T("%s"), chr_data);
		mn_chk = _wtoi(str_temp);
		if (mn_chk < 0)
		{
			st_basic_info.nModeInterface = 1;
		}
		else  st_basic_info.nModeInterface = mn_chk;

		GetPrivateProfileString(_T("BASIC_SCREEN"), _T("nModeXgem"), _T("1"), chr_data, sizeof(chr_data), st_path_info.strFileBasic);
		str_temp.Format(_T("%s"), chr_data);
		mn_chk = _wtoi(str_temp);
		if (mn_chk < 0)
		{
			st_basic_info.nModeXgem = 1;
		}
		else  st_basic_info.nModeXgem = mn_chk;

	

		GetPrivateProfileString(_T("BASIC_SCREEN"), _T("nModeXgemInterface"), _T("1"), chr_data, sizeof(chr_data), st_path_info.strFileBasic);
		str_temp.Format(_T("%s"), chr_data);
		mn_chk = _wtoi(str_temp);
		if (mn_chk < 0)
		{
			st_basic_info.nModeXgemInterface = 1;
		}
		else  st_basic_info.nModeXgemInterface = mn_chk;

		GetPrivateProfileString(_T("BASIC_SCREEN"), _T("nModeDevice"), _T("1"), chr_data, sizeof(chr_data), st_path_info.strFileBasic);
		str_temp.Format(_T("%s"), chr_data);
		mn_chk = _wtoi(str_temp);
		if (mn_chk < 0)
		{
			st_basic_info.nModeDevice = 1;
		}
		else  st_basic_info.nModeDevice = mn_chk;

	}

	
	
	if (nMode == 0)
	{
		GetPrivateProfileString(_T("ALARM"), _T("COUNT"), _T("1"), chr_data, sizeof(chr_data), st_path_info.strFileBasic);
		str_temp.Format(_T("%s"), chr_data);
		mn_chk = _wtoi(str_temp);
		if (mn_chk < 0)
		{
			st_alarm_info.nAlarmNum = 0;
		}
		else st_alarm_info.nAlarmNum = mn_chk;

		GetPrivateProfileString(_T("TIME"), _T("RUN_TIME"), _T("1"), chr_data, sizeof(chr_data), st_path_info.strFileBasic);
		str_temp.Format(_T("%s"), chr_data);
		mn_chk = _wtoi(str_temp);
		if (mn_chk < 0)
		{
			st_handler_info.tRun = 0;
		}
		st_handler_info.tRun = mn_chk;

		GetPrivateProfileString(_T("TIME"), _T("STOP_TIME"), _T("1"), chr_data, sizeof(chr_data), st_path_info.strFileBasic);
		str_temp.Format(_T("%s"), chr_data);
		mn_chk = _wtoi(str_temp);
		if (mn_chk < 0)
		{
			st_handler_info.tStop = 0;
		}
		st_handler_info.tStop = mn_chk;

		GetPrivateProfileString(_T("TIME"), _T("JAM_TIME"), _T("1"), chr_data, sizeof(chr_data), st_path_info.strFileBasic);
		str_temp.Format(_T("%s"), chr_data);
		mn_chk = _wtoi(str_temp);
		if (mn_chk < 0)
		{
			st_handler_info.tJam = 0;
		}
		st_handler_info.tJam = mn_chk;

	}

	int nYear, nMonth, nDay, nHour, nMinute, nSecond;

	if (nMode == 0)
	{
		GetPrivateProfileString(_T("TIME"), _T("CREATE_YEAR"), _T("2014"), chr_data, sizeof(chr_data), st_path_info.strFileBasic);
		str_temp.Format(_T("%s"), chr_data);
		mn_chk = _wtoi(str_temp);
		if (mn_chk < 0)
		{
			nYear = 2014;
		}
		else  nYear = mn_chk;

		GetPrivateProfileString(_T("TIME"), _T("CREATE_MONTH"), _T("1"), chr_data, sizeof(chr_data), st_path_info.strFileBasic);
		str_temp.Format(_T("%s"), chr_data);
		mn_chk = _wtoi(str_temp);
		if (mn_chk < 0)
		{
			nMonth = 1;
		}
		else  nMonth = mn_chk;

		GetPrivateProfileString(_T("TIME"), _T("CREATE_DAY"), _T("1"), chr_data, sizeof(chr_data), st_path_info.strFileBasic);
		str_temp.Format(_T("%s"), chr_data);
		mn_chk = _wtoi(str_temp);
		if (mn_chk < 0)
		{
			nDay = 1;
		}
		else  nDay = mn_chk;

		GetPrivateProfileString(_T("TIME"), _T("CREATE_HOUR"), _T("22"), chr_data, sizeof(chr_data), st_path_info.strFileBasic);
		str_temp.Format(_T("%s"), chr_data);
		mn_chk = _wtoi(str_temp);
		if (mn_chk < 0)
		{
			nHour = 22;
		}
		else  nHour = mn_chk;

		GetPrivateProfileString(_T("TIME"), _T("CREATE_MINUTE"), _T("0"), chr_data, sizeof(chr_data), st_path_info.strFileBasic);
		str_temp.Format(_T("%s"), chr_data);
		mn_chk = _wtoi(str_temp);
		if (mn_chk < 0)
		{
			nMinute = 0;
		}
		else  nMinute = mn_chk;

		GetPrivateProfileString(_T("TIME"), _T("CREATE_SECOND"), _T("0"), chr_data, sizeof(chr_data), st_path_info.strFileBasic);
		str_temp.Format(_T("%s"), chr_data);
		mn_chk = _wtoi(str_temp);
		if (mn_chk < 0)
		{
			nSecond = 0;
		}
		else  nSecond = mn_chk;

		
	}


	if (nMode == 0)
	{
		for (i=0; i<HSSI_MAX_IO; i++)
		{
			strTemp.Format(_T("OUT_STATUS_%06d"), i);
			GetPrivateProfileString(_T("IO_DATA"), strTemp, _T(""), chr_data, sizeof(chr_data), st_path_info.strFileBasic);
			str_temp.Format(_T("%s"), chr_data);
			mn_chk = _wtoi(str_temp);
			if (mn_chk < 0)
			{
				FAS_IO.n_out[i] = 0;
			}
			else  FAS_IO.n_out[i] = mn_chk;
		}
	}

	:: GetPrivateProfileString(_T("BASIC"), _T("nUph"), _T(""), (LPWSTR)chData, 30, st_path_info.strFileBasic);
	strTemp.Format(_T("%s"), chData);
	st_count_info.nUph = _wtoi(strTemp);
	if (st_count_info.nUph < 0) st_count_info.nUph = 0;

	//str_load_file]
	if (nMode == 0)
	{
		for (i=0; i<2; i++)
		{
			for (j=0; j<2; j++)
			{
				strTemp.Format(_T("COUNT_IN_%02d_%02d"), i+1, j+1);
				GetPrivateProfileString(_T("BASIC_SCREEN"), strTemp, _T(""), chr_data, sizeof(chr_data), st_path_info.strFileBasic);
				str_temp.Format(_T("%s"), chr_data);
				mn_chk = _wtoi(str_temp);
				if (mn_chk < 0)
				{
					st_count_info.nInCount[i][j] = 0;
				}
				else  st_count_info.nInCount[i][j] = mn_chk;

				strTemp.Format(_T("COUNT_PRIME_%02d_%02d"), i+1, j+1);
				GetPrivateProfileString(_T("BASIC_SCREEN"), strTemp, _T(""), chr_data, sizeof(chr_data), st_path_info.strFileBasic);
				str_temp.Format(_T("%s"), chr_data);
				mn_chk = _wtoi(str_temp);
				if (mn_chk < 0)
				{
					st_count_info.nPrimeCount[i][j] = 0;
				}
				else  st_count_info.nPrimeCount[i][j] = mn_chk;

				strTemp.Format(_T("COUNT_PASS_%02d_%02d"), i+1, j+1);
				GetPrivateProfileString(_T("BASIC_SCREEN"), strTemp, _T(""), chr_data, sizeof(chr_data), st_path_info.strFileBasic);
				str_temp.Format(_T("%s"), chr_data);
				mn_chk = _wtoi(str_temp);
				if (mn_chk < 0)
				{
					st_count_info.nPassCount[i][j] = 0;
				}
				else  st_count_info.nPassCount[i][j] = mn_chk;

				strTemp.Format(_T("COUNT_REJECT_%02d_%02d"), i+1, j+1);
				GetPrivateProfileString(_T("BASIC_SCREEN"), strTemp, _T(""), chr_data, sizeof(chr_data), st_path_info.strFileBasic);
				str_temp.Format(_T("%s"), chr_data);
				mn_chk = _wtoi(str_temp);
				if (mn_chk < 0)
				{
					st_count_info.nRejectCount[i][j] = 0;
				}
				else  st_count_info.nRejectCount[i][j] = mn_chk;
			}
		}
	}

	if (nMode == 0)
	{
		// jtkim 20150709
		GetPrivateProfileString(_T("BASIC_SCREEN"), _T("UPH_COUNT"), _T(""), chr_data, sizeof(chr_data), st_path_info.strFileBasic);
		str_temp.Format(_T("%s"), chr_data);
		mn_chk = _wtoi(str_temp);
		if (mn_chk < 0)
		{
			st_count_info.nUph = 0;
		}
		else  st_count_info.nUph = mn_chk;

		// jtkim 20150709
		GetPrivateProfileString(_T("BASIC_SCREEN"), _T("DAILY_UPH_COUNT"), _T(""), chr_data, sizeof(chr_data), st_path_info.strFileBasic);
		str_temp.Format(_T("%s"), chr_data);
		mn_chk = _wtoi(str_temp);
		if (mn_chk < 0)
		{
			st_count_info.nDailyUph = 0;
		}
		else  st_count_info.nDailyUph = mn_chk;

		// jtkim 20150709
		GetPrivateProfileString(_T("BASIC_SCREEN"), _T("dHourPer"), _T(""), chr_data, sizeof(chr_data), st_path_info.strFileBasic);
		str_temp.Format(_T("%s"), chr_data);
		md_chk = _wtof(str_temp);
		if (mn_chk < 0)
		{
			st_count_info.dHourPer = 0.0f;
		}
		else  st_count_info.dHourPer = md_chk;

		GetPrivateProfileString(_T("BASIC_SCREEN"), _T("dDailyPer"), _T(""), chr_data, sizeof(chr_data), st_path_info.strFileBasic);
		str_temp.Format(_T("%s"), chr_data);
		md_chk = _wtof(str_temp);
		if (mn_chk < 0)
		{
			st_count_info.dDailyPer = 0.0f;
		}
		else  st_count_info.dDailyPer = md_chk;
	}
}

void CMyBasicData::OnBasic_Data_Load(CString strDeviceName)
{
	CString str_load_device;	// �ε� ����̽��� ���� ����
	CString str_load_pgm;		// �ε� ����̽��� ���� ����
	CString str_load_file;
	CString str_chk_ext;		// ���� Ȯ���� ���� ����
	CString str_temp, stemp;	// ������ ���� �ӽ� ���� ���� 
	CString str_pos;
	TCHAR chr_data[50], chr_buf[20];
//	int mn_chk;

	memset(&chr_data, 0, sizeof(chr_data));
	memset(&chr_buf, 0, sizeof(chr_buf));

	

	// ���� ��� 
	str_load_file = st_path_info.strBasic + strDeviceName;  // ƼĪ ������ ���� ���� ����
}

void CMyBasicData::OnBasic_Data_Save()
{
	CString mstr_temp;  // ������ ���� �ӽ� ���� ���� 
	CString str_save_file;
	CString str_part, str_chk_ext;
	CString str_pos, str_tmp;
	COleDateTime time_cur;

	int i, j;

	/* ************************************************************************** */
	/*  ������ ������ ���� �����Ѵ� [���� Ȯ���� �˻�]                               */
	/* ************************************************************************** */
	:: WritePrivateProfileString(_T("FILE_NAME"), _T("Device_Type"), LPCTSTR(st_basic_info.strDeviceName), st_path_info.strFileBasic);

	str_save_file = st_path_info.strBasic + st_basic_info.strDeviceName;  // ƼĪ ������ ���� ���� ����

	:: WritePrivateProfileString(_T("BASIC_SCREEN"), _T("strEqp"), LPCTSTR(st_basic_info.strEqp), st_path_info.strFileBasic);

	mstr_temp.Format(_T("%d"), st_basic_info.nModeInterface);
	:: WritePrivateProfileString(_T("BASIC_SCREEN"), _T("nModeInterface"), LPCTSTR(mstr_temp), st_path_info.strFileBasic);

	mstr_temp.Format(_T("%d"), st_basic_info.nModeXgem);
	:: WritePrivateProfileString(_T("BASIC_SCREEN"), _T("nModeXgem"), LPCTSTR(mstr_temp), st_path_info.strFileBasic);

	mstr_temp.Format(_T("%d"), st_basic_info.nModeXgemRunChk);
	:: WritePrivateProfileString(_T("BASIC_SCREEN"), _T("nModeXgemRunChk"), LPCTSTR(mstr_temp), st_path_info.strFileBasic);

	mstr_temp.Format(_T("%d"), st_basic_info.nModeXgemInterface);
	:: WritePrivateProfileString(_T("BASIC_SCREEN"), _T("nModeXgemInterface"), LPCTSTR(mstr_temp), st_path_info.strFileBasic);

	mstr_temp.Format(_T("%d"), st_basic_info.nModeDevice);
	:: WritePrivateProfileString(_T("BASIC_SCREEN"), _T("nModeDevice"), LPCTSTR(mstr_temp), st_path_info.strFileBasic);

	:: WritePrivateProfileString(_T("BASIC_SCREEN"), _T("ModelName"), LPCTSTR(st_basic_info.strModelName), str_save_file);
	
	mstr_temp.Format(_T("%d"), st_basic_info.nRetry);
	:: WritePrivateProfileString(_T("BASIC_SCREEN"), _T("nRetry"), LPCTSTR(mstr_temp), st_path_info.strFileBasic);

	:: WritePrivateProfileString(_T("BASIC_SCREEN"), _T("strDevice"), LPCTSTR(st_basic_info.strDevice), st_path_info.strFileBasic);

	mstr_temp.Format(_T("%d"), st_alarm_info.nAlarmNum);
	:: WritePrivateProfileString(_T("ALARM"), _T("COUNT"), LPCTSTR(mstr_temp), st_path_info.strFileBasic);

	mstr_temp.Format(_T("%d"), st_handler_info.tRun);
	:: WritePrivateProfileString(_T("TIME"), _T("RUN_TIME"), LPCTSTR(mstr_temp), st_path_info.strFileBasic);

	mstr_temp.Format(_T("%d"), st_handler_info.tStop);
	:: WritePrivateProfileString(_T("TIME"), _T("STOP_TIME"), LPCTSTR(mstr_temp), st_path_info.strFileBasic);

	mstr_temp.Format(_T("%d"), st_handler_info.tJam);
	:: WritePrivateProfileString(_T("TIME"), _T("JAM_TIME"), LPCTSTR(mstr_temp), st_path_info.strFileBasic);

	
	mstr_temp.Format(_T("%d"), st_lot_info[LOT_CURR].nLotStatus);
	:: WritePrivateProfileString(_T("LOT_INFO"), _T("LOT_CURR_STATUS"), LPCTSTR(mstr_temp), st_path_info.strFileBasic);

	mstr_temp.Format(_T("%d"), st_lot_info[LOT_NEXT].nLotStatus);
	:: WritePrivateProfileString(_T("LOT_INFO"), _T("LOT_NEXT_STATUS"), LPCTSTR(mstr_temp), st_path_info.strFileBasic);


	for (i=0; i<HSSI_MAX_IO; i++)
	{
		str_tmp.Format(_T("OUT_STATUS_%06d"), i);
		mstr_temp.Format(_T("%d"), FAS_IO.n_out[i]);
		:: WritePrivateProfileString(_T("IO_DATA"), str_tmp, LPCTSTR(mstr_temp), st_path_info.strFileBasic);
	}

	mstr_temp.Format(_T("%d"), st_count_info.nUph);
	:: WritePrivateProfileString(_T("BASIC"), _T("nUph"), LPCTSTR(mstr_temp), st_path_info.strFileBasic);


	for (i=0; i<2; i++)
	{
		for (j=0; j<2; j++)
		{
			mstr_temp.Format(_T("COUNT_IN_%02d_%02d"), i+1, j+1);
			str_tmp.Format(_T("%d"), st_count_info.nInCount[i][j]);
			:: WritePrivateProfileString(_T("BASIC_SCREEN"), mstr_temp, str_tmp, st_path_info.strFileBasic);

			mstr_temp.Format(_T("COUNT_PRIME_%02d_%02d"), i+1, j+1);
			str_tmp.Format(_T("%d"), st_count_info.nPrimeCount[i][j]);
			:: WritePrivateProfileString(_T("BASIC_SCREEN"), mstr_temp, str_tmp, st_path_info.strFileBasic);

			mstr_temp.Format(_T("COUNT_PASS_%02d_%02d"), i+1, j+1);
			str_tmp.Format(_T("%d"), st_count_info.nPassCount[i][j]);
			:: WritePrivateProfileString(_T("BASIC_SCREEN"), mstr_temp, str_tmp, st_path_info.strFileBasic);

			mstr_temp.Format(_T("COUNT_REJECT_%02d_%02d"), i+1, j+1);
			str_tmp.Format(_T("%d"), st_count_info.nRejectCount[i][j]);
			:: WritePrivateProfileString(_T("BASIC_SCREEN"), mstr_temp, str_tmp, st_path_info.strFileBasic);
		}
	}

	str_tmp.Format(_T("%d"), st_count_info.nUph);
	:: WritePrivateProfileString(_T("BASIC_SCREEN"), _T("UPH_COUNT"), str_tmp, st_path_info.strFileBasic);

	str_tmp.Format(_T("%d"), st_count_info.nDailyUph);
	:: WritePrivateProfileString(_T("BASIC_SCREEN"), _T("DAILY_UPH_COUNT"), str_tmp, st_path_info.strFileBasic);

	str_tmp.Format(_T("%.2f"), st_count_info.dHourPer);
	:: WritePrivateProfileString(_T("BASIC_SCREEN"), _T("dHourPer"), str_tmp, st_path_info.strFileBasic);

	str_tmp.Format(_T("%.2f"), st_count_info.dDailyPer);
	:: WritePrivateProfileString(_T("BASIC_SCREEN"), _T("dDailyPer"), str_tmp, st_path_info.strFileBasic);
}

CString CMyBasicData::OnGet_File_Name()
{
	CString strTemp;       // �ӽ� ���� ����
	CString strSaveFile;  // ���� ���� �ӽ� ���� ����
	CString strChkExt;    // ���� Ȯ���� ���� ����
	CString strPart, strPart2;
	CString strNewSaveFile;
	int nPos;
	
	// **************************************************************************
    // Socket Contact Count ������ ������ ���� �����Ѵ� [���� Ȯ���� �˻�]        
    // **************************************************************************
	strSaveFile = st_path_info.strPathDvc + st_basic_info.strDeviceName;  // ƼĪ ������ ���� ���� ����
	
	nPos = strSaveFile.Find(_T("."));  // Ȯ���� ��ġ �˻�
	
	if (nPos == -1)
	{
		strSaveFile += _T(".DAT");  // Ȯ���� �߰�
	}
	else 
	{
		strChkExt = strSaveFile.Mid(nPos);  // ���� Ȯ���� ����

		if (strChkExt != _T(".TXT"))  
		{
			strSaveFile = st_path_info.strPathDvc + _T("DEFAULT.TXT");  // ƼĪ ������ ���� ���ο� ���� ����
/*			
			if (st_handler.cwnd_list != NULL)	// ����Ʈ �� ȭ�� ����
			{
				st_other.str_abnormal_msg = _T("[DEVICE FILE] The error happened at a file extension.");
				sprintf(st_other.c_abnormal_msg, st_other.str_abnormal_msg);
				st_handler.cwnd_list->PostMessage(WM_LIST_DATA, 0, ABNORMAL_MSG);  // ���� ��� ��û
			}*/
		}
	}
	// **************************************************************************
	
	return strSaveFile;  // ���ϸ� ���� 
}

void CMyBasicData::OnDeviec_Folder_Load()
{

}

void CMyBasicData::OnDevice_Folder_Save()
{
	
}

void CMyBasicData::OnInterface_Data_Load()
{
	int i;
	CString str_temp, str_name;
	char ch_data[100];
//	char ch_tmp;

	for(i=0; i<10; i++)
	{
		str_name.Format(_T("%02d_CLIENT_IP"), i);
		:: GetPrivateProfileString(_T("INTERFACE_SCREEN"), str_name, _T(""), (LPWSTR)ch_data, 100, st_path_info.strFileBasic);
//		sprintf(ch_data,"%S", ch_data);
//		clsFunc.OnCharToString(ch_data, 100);
		str_temp.Format(_T("%s"), ch_data);
		st_client_info[i].strIp = str_temp;

		str_name.Format(_T("%02d_CLIENT_PORT"), i);
		:: GetPrivateProfileString(_T("INTERFACE_SCREEN"), str_name, _T(""), (LPWSTR)ch_data, 100, st_path_info.strFileBasic);
		str_temp.Format(_T("%s"), ch_data);
		st_client_info[i].nPort = _wtoi(str_temp);

		str_name.Format(_T("%02d_SERVER_PORT"), i);
		:: GetPrivateProfileString(_T("INTERFACE_SCREEN"), str_name, _T(""), (LPWSTR)ch_data, 100, st_path_info.strFileBasic);
		str_temp.Format(_T("%s"), ch_data);
		st_server_info[i].nPort = _wtoi(str_temp);

		str_name.Format(_T("PORT_%02d"), i+1);
		:: GetPrivateProfileString(_T("SERIAL"), str_name, _T("1"), (LPWSTR)ch_data, 100, st_path_info.strFileBasic);
		str_temp.Format(_T("%s"), ch_data);
		st_serial_info.nSerialPort[i] = _wtoi(str_temp);
		if(st_serial_info.nSerialPort[i] < 1)
			st_serial_info.nSerialPort[i] = 1;
		
		str_name.Format(_T("BAUDRATE_%02d"), i+1);
		:: GetPrivateProfileString(_T("SERIAL"), str_name, _T("9600"), (LPWSTR)&ch_data, 100, st_path_info.strFileBasic);
		str_temp.Format(_T("%s"), ch_data);
		st_serial_info.nSerialBaudrate[i] = _wtoi(str_temp);

		
		str_name.Format(_T("DATA_%02d"), i+1);
		:: GetPrivateProfileString(_T("SERIAL"), str_name, _T("8"), (LPWSTR)ch_data, 100, st_path_info.strFileBasic);
		str_temp.Format(_T("%s"), ch_data);
		st_serial_info.nSerialData[i] = _wtoi(str_temp);
		
		str_name.Format(_T("STOP_%02d"), i+1);
		:: GetPrivateProfileString(_T("SERIAL"), str_name, _T("1"), (LPWSTR)ch_data, 100, st_path_info.strFileBasic);
		str_temp.Format(_T("%s"), ch_data);
		st_serial_info.nSerialStop[i] = _wtoi(str_temp);
		
		str_name.Format(_T("PARITY_%02d"), i+1);
		:: GetPrivateProfileString(_T("SERIAL"), str_name, _T("0"), (LPWSTR)ch_data, 100, st_path_info.strFileBasic);
		str_temp.Format(_T("%s"), ch_data);
		st_serial_info.nSerialParity[i] = _wtoi(str_temp);	
	}
}

void CMyBasicData::OnInterface_Data_Save()
{
	int i;
	CString str_tmp, str_name;

	for(i=0; i<10; i++)
	{
		str_name.Format(_T("%02d_CLIENT_IP"), i);
		str_tmp.Format(_T("%s"), st_client_info[i].strIp);
		:: WritePrivateProfileString(_T("INTERFACE_SCREEN"), str_name, LPCTSTR(str_tmp), st_path_info.strFileBasic);

		str_name.Format(_T("%02d_CLIENT_PORT"), i);
		str_tmp.Format(_T("%d"), st_client_info[i].nPort);
		:: WritePrivateProfileString(_T("INTERFACE_SCREEN"), str_name, LPCTSTR(str_tmp), st_path_info.strFileBasic);

		str_name.Format(_T("%02d_SERVER_PORT"), i);
		str_tmp.Format(_T("%d"), st_server_info[i].nPort);
		:: WritePrivateProfileString(_T("INTERFACE_SCREEN"), str_name, LPCTSTR(str_tmp), st_path_info.strFileBasic);

		str_name.Format(_T("PORT_%02d"), i+1);
		str_tmp.Format(_T("%d"), st_serial_info.nSerialPort[i]);
		:: WritePrivateProfileString(_T("SERIAL"), str_name, LPCTSTR(str_tmp), st_path_info.strFileBasic);

		str_name.Format(_T("BAUDRATE_%02d"), i+1);
		str_tmp.Format(_T("%d"), st_serial_info.nSerialBaudrate[i]);
		:: WritePrivateProfileString(_T("SERIAL"), str_name, LPCTSTR(str_tmp), st_path_info.strFileBasic);

		str_name.Format(_T("DATA_%02d"), i+1);
		str_tmp.Format(_T("%d"), st_serial_info.nSerialData[i]);
		:: WritePrivateProfileString(_T("SERIAL"), str_name, LPCTSTR(str_tmp), st_path_info.strFileBasic);

		str_name.Format(_T("STOP_%02d"), i+1);
		str_tmp.Format(_T("%d"), st_serial_info.nSerialStop[i]);
		:: WritePrivateProfileString(_T("SERIAL"), str_name, LPCTSTR(str_tmp), st_path_info.strFileBasic);

		str_name.Format(_T("PARITY_%02d"), i+1);
		str_tmp.Format(_T("%d"), st_serial_info.nSerialParity[i]);
		:: WritePrivateProfileString(_T("SERIAL"), str_name, LPCTSTR(str_tmp), st_path_info.strFileBasic);
	}
}

void CMyBasicData::OnInterface_Data_Save_As(CString strDeviceName)
{
	int i;
	CString str_tmp, str_name;

	for(i=0; i<10; i++)
	{
		str_name.Format(_T("%02d_CLIENT_IP"), i);
		str_tmp.Format(_T("%s"), st_client_info[i].strIp);
		:: WritePrivateProfileString(_T("INTERFACE_SCREEN"), str_name, LPCTSTR(str_tmp), st_path_info.strFileBasic);

		str_name.Format(_T("%02d_CLIENT_PORT"), i);
		str_tmp.Format(_T("%d"), st_client_info[i].nPort);
		:: WritePrivateProfileString(_T("INTERFACE_SCREEN"), str_name, LPCTSTR(str_tmp), st_path_info.strFileBasic);

		str_name.Format(_T("%02d_SERVER_PORT"), i);
		str_tmp.Format(_T("%d"), st_server_info[i].nPort);
		:: WritePrivateProfileString(_T("INTERFACE_SCREEN"), str_name, LPCTSTR(str_tmp), st_path_info.strFileBasic);

		str_name.Format(_T("PORT_%02d"), i+1);
		str_tmp.Format(_T("%d"), st_serial_info.nSerialPort[i]);
		:: WritePrivateProfileString(_T("SERIAL"), str_name, LPCTSTR(str_tmp), st_path_info.strFileBasic);

		str_name.Format(_T("BAUDRATE_%02d"), i+1);
		str_tmp.Format(_T("%d"), st_serial_info.nSerialBaudrate[i]);
		:: WritePrivateProfileString(_T("SERIAL"), str_name, LPCTSTR(str_tmp), st_path_info.strFileBasic);

		str_name.Format(_T("DATA_%02d"), i+1);
		str_tmp.Format(_T("%d"), st_serial_info.nSerialData[i]);
		:: WritePrivateProfileString(_T("SERIAL"), str_name, LPCTSTR(str_tmp), st_path_info.strFileBasic);

		str_name.Format(_T("STOP_%02d"), i+1);
		str_tmp.Format(_T("%d"), st_serial_info.nSerialStop[i]);
		:: WritePrivateProfileString(_T("SERIAL"), str_name, LPCTSTR(str_tmp), st_path_info.strFileBasic);

		str_name.Format(_T("PARITY_%02d"), i+1);
		str_tmp.Format(_T("%d"), st_serial_info.nSerialParity[i]);
		:: WritePrivateProfileString(_T("SERIAL"), str_name, LPCTSTR(str_tmp), st_path_info.strFileBasic);
	}
}

void CMyBasicData::OnBasic_Data_Save_As(CString strDeviceName)
{
	CString mstr_temp;  // ������ ���� �ӽ� ���� ���� 
	CString str_save_file;
	CString str_part, str_chk_ext;
	CString str_pos;
	COleDateTime time_cur;

	/* ************************************************************************** */
	/*  ������ ������ ���� �����Ѵ� [���� Ȯ���� �˻�]                            */
	/* ************************************************************************** */
	:: WritePrivateProfileString(_T("FILE_NAME"), _T("Device_Type"), LPCWSTR(strDeviceName), st_path_info.strFileBasic);

	//str_save_file = st_path_info.strBasic + strDeviceName;  // ƼĪ ������ ���� ���� ����
	//kwlee 2017.0511
	str_save_file = st_path_info.strpathModel + strDeviceName;  // ƼĪ ������ ���� ���� ����

	mstr_temp.Format(_T("%d"), st_basic_info.nModeDevice);
	:: WritePrivateProfileString(_T("BASIC"), _T("DEVICE_MODE"), LPCWSTR(strDeviceName), str_save_file);
}

void CMyBasicData::OnMaintenance_Data_Save_As(CString strDevice)
{
	CString strTemp, strPart;  // �ε� ���� �ӽ� ���� ����
//	char chBuf[20] ;
	CString strSaveFile;;

	// **************************************************************************
	// Ÿ�� ���� RED ���� ������ ���Ͽ� �����Ѵ�                                 
	// ->  STOP			= 0,
	// 		   RUN			= 1,
	// 		   ALARM		= 2,
	// 		   LOTEND		= 3,
	// 		   INIT			= 4,
	// 		   WARRING		= 5,
	// 		   LOCK			= 6,
	// 		   SELFCHECK	= 7														 
	// -> �ε� �� [0:OFF    1:ON    2:FLICKER]                                   
	// **************************************************************************
//	str_save_file = st_path.str_basic + str_device;  // ƼĪ ������ ���� ���� ����
	strSaveFile = st_path_info.strBasic + _T("Maintenance.TXT");

	strTemp.Format(_T("%d"), st_lamp_info.nLampR[0]) ;
	:: WritePrivateProfileString(_T("TowerLampData_Red"), _T("Stop_State"), LPCTSTR(strTemp), strSaveFile);

	strTemp.Format(_T("%d"),st_lamp_info.nLampR[1]) ;
	:: WritePrivateProfileString(_T("TowerLampData_Red"), _T("Run_State"), LPCTSTR(strTemp), strSaveFile);

	strTemp.Format(_T("%d"),st_lamp_info.nLampR[2]) ;
	:: WritePrivateProfileString(_T("TowerLampData_Red"), _T("Alarm_State"), LPCTSTR(strTemp), strSaveFile);

	strTemp.Format(_T("%d"),st_lamp_info.nLampR[3]) ;
	:: WritePrivateProfileString(_T("TowerLampData_Red"), _T("LotEnd_State"), LPCTSTR(strTemp), strSaveFile);

	strTemp.Format(_T("%d"),st_lamp_info.nLampR[4]) ;
	:: WritePrivateProfileString(_T("TowerLampData_Red"), _T("Initial_State"), LPCTSTR(strTemp), strSaveFile);

	strTemp.Format(_T("%d"),st_lamp_info.nLampR[5]) ;
	:: WritePrivateProfileString(_T("TowerLampData_Red"), _T("Warring_State"), LPCTSTR(strTemp), strSaveFile);

	strTemp.Format(_T("%d"),st_lamp_info.nLampR[6]) ;
	:: WritePrivateProfileString(_T("TowerLampData_Red"), _T("Lock_State"), LPCTSTR(strTemp), strSaveFile);

	strTemp.Format(_T("%d"),st_lamp_info.nLampR[7]) ;
	:: WritePrivateProfileString(_T("TowerLampData_Red"), _T("SelfCheck_State"), LPCTSTR(strTemp), strSaveFile);

	strTemp.Format(_T("%d"),st_lamp_info.nLampR[8]) ;
	:: WritePrivateProfileString(_T("TowerLampData_Red"), _T("Idle_State"), LPCTSTR(strTemp), strSaveFile);
	// **************************************************************************


	// **************************************************************************
	// Ÿ�� ���� YELLOW ���� ������ ���Ͽ� �����Ѵ�                              
	// ->  STOP			= 0,
// 		   RUN			= 1,
// 		   ALARM		= 2,
// 		   LOTEND		= 3,
// 		   INIT			= 4,
// 		   WARRING		= 5,
// 		   LOCK			= 6,
// 		   SELFCHECK	= 7														 
	// -> �ε� �� [0:OFF    1:ON    2:FLICKER]                                   
	// **************************************************************************
	strTemp.Format(_T("%d"),st_lamp_info.nLampY[0]) ;
	:: WritePrivateProfileString(_T("TowerLampData_Yellow"), _T("Stop_State"), LPCTSTR(strTemp), strSaveFile);

	strTemp.Format(_T("%d"),st_lamp_info.nLampY[1]) ;
	:: WritePrivateProfileString(_T("TowerLampData_Yellow"), _T("Run_State"), LPCTSTR(strTemp), strSaveFile);

	strTemp.Format(_T("%d"),st_lamp_info.nLampY[2]) ;
	:: WritePrivateProfileString(_T("TowerLampData_Yellow"), _T("Alarm_State"), LPCTSTR(strTemp), strSaveFile);

	strTemp.Format(_T("%d"),st_lamp_info.nLampY[3]) ;
	:: WritePrivateProfileString(_T("TowerLampData_Yellow"), _T("LotEnd_State"), LPCTSTR(strTemp), strSaveFile);

	strTemp.Format(_T("%d"),st_lamp_info.nLampY[4]) ;
	:: WritePrivateProfileString(_T("TowerLampData_Yellow"), _T("Initial_State"), LPCTSTR(strTemp), strSaveFile);

	strTemp.Format(_T("%d"),st_lamp_info.nLampY[5]) ;
	:: WritePrivateProfileString(_T("TowerLampData_Yellow"), _T("Warring_State"), LPCTSTR(strTemp), strSaveFile);

	strTemp.Format(_T("%d"),st_lamp_info.nLampY[6]) ;
	:: WritePrivateProfileString(_T("TowerLampData_Yellow"), _T("Lock_State"), LPCTSTR(strTemp), strSaveFile);

	strTemp.Format(_T("%d"),st_lamp_info.nLampY[7]) ;
	:: WritePrivateProfileString(_T("TowerLampData_Yellow"), _T("SelfCheck_State"), LPCTSTR(strTemp), strSaveFile);

	strTemp.Format(_T("%d"),st_lamp_info.nLampY[8]) ;
	:: WritePrivateProfileString(_T("TowerLampData_Yellow"), _T("Idle_State"), LPCTSTR(strTemp), strSaveFile);

	// **************************************************************************

	// **************************************************************************
	// Ÿ�� ���� GREEN ���� ������ ���Ͽ� �����Ѵ�                               
	// ->  STOP			= 0,
// 		   RUN			= 1,
// 		   ALARM		= 2,
// 		   LOTEND		= 3,
// 		   INIT			= 4,
// 		   WARRING		= 5,
// 		   LOCK			= 6,
// 		   SELFCHECK	= 7														 
	// -> �ε� �� [0:OFF    1:ON    2:FLICKER]                                   
	// **************************************************************************
	strTemp.Format(_T("%d"),st_lamp_info.nLampG[0]) ;
	:: WritePrivateProfileString(_T("TowerLampData_Green"), _T("Stop_State"), LPCTSTR(strTemp), strSaveFile);

	strTemp.Format(_T("%d"),st_lamp_info.nLampG[1]) ;
	:: WritePrivateProfileString(_T("TowerLampData_Green"), _T("Run_State"), LPCTSTR(strTemp), strSaveFile);

	strTemp.Format(_T("%d"),st_lamp_info.nLampG[2]) ;
	:: WritePrivateProfileString(_T("TowerLampData_Green"), _T("Alarm_State"), LPCTSTR(strTemp), strSaveFile);

	strTemp.Format(_T("%d"),st_lamp_info.nLampG[3]) ;
	:: WritePrivateProfileString(_T("TowerLampData_Green"), _T("LotEnd_State"), LPCTSTR(strTemp), strSaveFile);

	strTemp.Format(_T("%d"),st_lamp_info.nLampG[4]) ;
	:: WritePrivateProfileString(_T("TowerLampData_Green"), _T("Initial_State"), LPCTSTR(strTemp), strSaveFile);

	strTemp.Format(_T("%d"),st_lamp_info.nLampG[5]) ;
	:: WritePrivateProfileString(_T("TowerLampData_Green"), _T("Warring_State"), LPCTSTR(strTemp), strSaveFile);

	strTemp.Format(_T("%d"),st_lamp_info.nLampG[6]) ;
	:: WritePrivateProfileString(_T("TowerLampData_Green"), _T("Lock_State"), LPCTSTR(strTemp), strSaveFile);

	strTemp.Format(_T("%d"),st_lamp_info.nLampG[7]) ;
	:: WritePrivateProfileString(_T("TowerLampData_Green"), _T("SelfCheck_State"), LPCTSTR(strTemp), strSaveFile);

	strTemp.Format(_T("%d"),st_lamp_info.nLampG[8]) ;
	:: WritePrivateProfileString(_T("TowerLampData_Green"), _T("Idle_State"), LPCTSTR(strTemp), strSaveFile);
	// **************************************************************************

	// **************************************************************************
	// ���� ��� ��� �ε��Ͽ� ���� ������ ����                                  
	// -> 0:���    1:�̻��                                                     
	// **************************************************************************
	strTemp.Format(_T("%d"),st_lamp_info.nBuzzerMode) ;
	:: WritePrivateProfileString(_T("TowerLampData"), _T("n_buzzer_mode"), LPCTSTR(strTemp), strSaveFile);
	// **************************************************************************

	// **************************************************************************
	// ��� ȣ�� �� ��� �ڵ� �ε��Ͽ� ���� ������ ����                          
	// -> �ε� �������� ��/�� ������ �����Ѵ�                                    
	// **************************************************************************
	:: WritePrivateProfileString(_T("TowerLampData"), _T("str_equip_no"), LPCTSTR(st_lamp_info.strEquipNo), strSaveFile);
	:: WritePrivateProfileString(_T("TowerLampData"), _T("str_equip_code"), LPCTSTR(st_lamp_info.strEquipCode), strSaveFile);
	// **************************************************************************

	// **************************************************************************
	// Ÿ�� ���� ON/OFF ��� �ð� �ε��Ͽ� ���� ������ ����                      
	// **************************************************************************
	strTemp.Format(_T("%d"),st_lamp_info.nLampWaitTime);
	:: WritePrivateProfileString(_T("TowerLampData"), _T("n_lamp_on_time_w"), LPCTSTR(strTemp), strSaveFile);
	// **************************************************************************
}

void CMyBasicData::OnModuleRobot_Teach_Data_Save_As(CString strDeviceName)
{
	CString strTemp, strMsg, strSaveFail;       // �ӽ� ���� ����
	CString strPos;
	CString strHead, strItem;
	int i, j;
	
	strSaveFail = st_path_info.strFileMotor + strDeviceName;
	
	for(i=0; i<MAXMOTOR; i++)
	{
		strHead.Format(_T("Motor%d"),i+1);
		for(j=0; j<M_MAX_POS; j++)
		{
			strItem.Format(_T("%02d_Axis_[%02d]"), i+1, j+1); 
			strTemp.Format(_T("%.3f"), st_motor_info[i].d_pos[j]);
			:: WritePrivateProfileString(strHead, strItem, LPCTSTR(strTemp), strSaveFail);
		}
	}
}





CString CMyBasicData::GetWaitTimeName(int n_mode)
{
	CString strName;

	strName = "";

	switch(n_mode)
	{
		case 0:
			strName = "0";
			break;

		case 1:
			strName = "1";
			break;

		case 2:
			strName = "2";
			break;

		case 3:
			strName = "3";
			break;

		case 4:
			strName = "4";
			break;

		case 5:
			strName = "5";
			break;

		case 6:
			strName = "6";
			break;

		case 7:
			strName = "7";
			break;

		case 8:
			strName = "8";
			break;

		case 9:
			strName = "9";
			break;

		case 10:
			strName = "10";
			break;

		case 11:
			strName = "11";
			break;

		case 12:
			strName = "12";
			break;

		case 13:
			strName = "13";
			break;

		case 14:
			strName = "14";
			break;

		case 15:
			strName = "15";
			break;

		case 16:
			strName = "16";
			break;

		case 17:
			strName = "17";
			break;

		case 18:
			strName = "18";
			break;

		case 19:
			strName = "19";
			break;
	}

	return strName;
}

void CMyBasicData::OnRecipe_Data_Load()
{
	CString strTemp;  // �ε� ���� �ӽ� ���� ����
	CString strHead;
	CString strLoadFile;

//	char chData[200];

	// ���� ��� 
	strLoadFile = st_path_info.strBasic + st_basic_info.strDeviceName;  

}


void CMyBasicData::OnRecipe_Data_Load(CString strDeviceName)
{
	CString strTemp;  // �ε� ���� �ӽ� ���� ����
	CString strLoadFile;
	CString strHead;

	char chData[200];

	// ���� ���  
	strLoadFile = st_path_info.strBasic + strDeviceName; 
}


void CMyBasicData::OnRecipe_Data_Save()
{
	CString strTemp;  // ������ ���� �ӽ� ���� ���� 
	CString strSaveFile;
	CString strPart, strChkExt;
	CString strPos;
	CString strHead;

	COleDateTime time_cur;

	strSaveFile = st_path_info.strBasic + st_basic_info.strDeviceName;  // ƼĪ ������ ���� ���� ����

}

void CMyBasicData::OnRecipe_Data_Save_As(CString strDeviceName)
{
	CString strTemp;  // ������ ���� �ӽ� ���� ���� 
	CString strSaveFile;
	CString strPart, strChkExt;
	CString strPos;
	CString strHead;

	COleDateTime time_cur;

	strSaveFile = st_path_info.strBasic + strDeviceName;  // ƼĪ ������ ���� ���� ����

	
}

void CMyBasicData::OnRecoveryDataLoad()
{

}


void CMyBasicData::OnRecoveryDataSave()
{
	
}


void CMyBasicData::OnAnimateDataLoad()
{
	CString str_load_device;	// �ε� ����̽��� ���� ����
	CString str_load_file;
	CString str_temp, stemp;	// ������ ���� �ӽ� ���� ���� 
	CString str_pos;
	TCHAR chr_data[50], chr_buf[20];
	int nVal;
	int i;
	double dVal;

	memset(&chr_data, 0, sizeof(chr_data));
	memset(&chr_buf, 0, sizeof(chr_buf));

	// ���� ���ϸ� ��������
	if(st_basic_info.strDeviceName == "")
	{
		GetPrivateProfileString(_T("FILE_NAME"), _T("Device_Type"), _T("DEFAULT.TXT"), chr_data, sizeof(chr_data), st_path_info.strFileBasic);
		st_basic_info.strDeviceName = (LPCTSTR)chr_data;
	}
	// ���� ��� 
	str_load_file = st_path_info.strBasic + st_basic_info.strDeviceName;  // ƼĪ ������ ���� ���� ����

	for (i=0; i<20; i++)
	{
		str_pos.Format(_T("MAX_POS_%02d"), i);
		GetPrivateProfileString(_T("ANIMATE_MAX"), str_pos, _T("1"), chr_data, sizeof(chr_data), st_path_info.strFileBasic);
		str_temp.Format(_T("%s"), chr_data);
		dVal = _wtof(str_temp);
		if (dVal < 0.0)
		{
			st_animate_info.dMaxPos[i] = 0.0;
		}
		else
		{
			st_animate_info.dMaxPos[i] = dVal;
		}

		str_pos.Format(_T("LENGTH_POS_%02d"), i);
		GetPrivateProfileString(_T("ANIMATE_LENGTH"), str_pos, _T("1"), chr_data, sizeof(chr_data), st_path_info.strFileBasic);
		str_temp.Format(_T("%s"), chr_data);
		nVal = _wtoi(str_temp);
		if (nVal < 0.0)
		{
			st_animate_info.nDistance[i] = 0;
		}
		else
		{
			st_animate_info.nDistance[i] = nVal;
		}
	}
}


void CMyBasicData::OnAnimateDataSave()
{

}



