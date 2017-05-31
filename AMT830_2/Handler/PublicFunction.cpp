#include "StdAfx.h"
#include "PublicFunction.h"
#include "FastechPublic_IO.h"
#include "Variable.h"
#include "io.h"			// 파일 존재 유무 검사 함수 호출하기 위해서는 반드시 필요
#include "ComizoaPublic.h"
#include "Ctlbd_Variable.h"
#include "Cmmsdk.h"
//#include "InterfaceGms.h"
#include "Alg_Mysql.h"
#include "XgemClient.h"
#include "AlgMemory.h"
#include "CtlBd_Library.h"
#include "math.h"
#include "ACriticalSection.h"

CPublicFunction clsFunc;

CMutex mutex_f;

CPublicFunction::CPublicFunction(void)
{
	int i;
	
	for(i=0; i<20; i++)
	{
		m_pFont[i]	= NULL;
		m_pFont[i]	= new CFont;
		m_pFont[i]->CreateFont(i + 10,0,0,0,900,0,0,0,0,0,0,ANTIALIASED_QUALITY,0, _T("MS Sans Serif"));		//Bitstream Vera Sans Mono
	}

	m_ArLotHistory.RemoveAll();
}


CPublicFunction::~CPublicFunction(void)
{
	int i;
	
	for(i=0; i<20; i++)
	{
		if (m_pFont[i] != NULL)
		{
			delete m_pFont[i];
			m_pFont[i] = NULL;
		}
	}
}

void CPublicFunction::OnSerialize(CArchive &ar)
{
	CObject::Serialize(ar);

	CString strTemp;
	
// 	int i, j, k;
// 	int x, y;
//	int nYear, nMonth, nDay, nHour, nMinute, nSecond;
//	int nNum[5];

	if(ar.IsStoring())				// 저장하기
	{
		
	}
}

LOGFONT CPublicFunction::OnLogFont(int nFontSize)
{
	LOGFONT lf;
	::ZeroMemory(&lf,sizeof(LOGFONT));
	lf.lfHeight = nFontSize;
	lf.lfWeight = 10;
	lf.lfWeight = 10;
	lf.lfItalic = false;
	lf.lfUnderline = false;
	lf.lfStrikeOut = false;
	lf.lfCharSet=VIETNAMESE_CHARSET;

	return lf;
}


void CPublicFunction::OnTimeReset()
{
	CTime time;
//	int i,j;

	time = CTime::GetCurrentTime();

	st_count_info.nInCount[1][0]	= 0;
	st_count_info.nInCount[1][1]	= 0;
	st_count_info.nPassCount[1][0]	= 0;
	st_count_info.nPassCount[1][1]	= 0;
	st_count_info.nRejectCount[1][0]= 0;
	st_count_info.nRejectCount[1][1]= 0;
	st_count_info.nPrimeCount[1][0]	= 0;
	st_count_info.nPrimeCount[1][1]	= 0;


	st_alarm_info.nAlarmNum = 0;
//	st_count_info.nDailyUph = 0;

	st_handler_info.tRun		= 0;			// Run Time
	st_handler_info.tJam		= 0;			// Jam Time
	st_handler_info.tStop		= 0;			// Stop Time
	st_handler_info.tMaint		= 0;			// Maint Time
	st_handler_info.tDRun		= 0;			// Run Time
	st_handler_info.tDJam		= 0;			// Jam Time
	st_handler_info.tDStop		= 0;			// Stop Time
	st_handler_info.tDMaint		= 0;			// Maint Time


	
	
	
	
}


void CPublicFunction::OnDailyDataSave()
{
	CString strFileName;				// 마지막으로 생성된 파일 이름 저장 변수 
	CString strCreateFile;				// 알람 정보 저장할 파일에 대한 [폴더]+[파일명]+[확장자] 설정 변수 
	CString strListName, strTempData;	// 각 부분별 알람 발생 횟수 정보 저장할 로그 파일 정보 저장 변수 
	CString strContent;				// 한 라인에 출력할 문자열 정보 저장 변수 
	int nExistence;						// 파일 존재 유무 설정 플래그 
	char chFileName[256];				// 검색할 파일 정보 설정 함수 
	char chMsg[1000];
	FILE  *fp ;							// 파일에 대한 포인터 설정 변수 
	
	CString strTitleTime, strFileTime, strNewFile;		// 파일에 출력할 타이틀 시간 저장 변수
	int nCurYear, nCurMonth, nCurDay;					// 년, 월, 일 저장 변수
	int nCurHour, nCurMinute, nCurSecond;				// 년, 월, 일 저장 변수
	int nMtbi = 0;

	double dAve;
	
	COleDateTime otCurr;									// 현재 시간 저장 변수
	CTime tCurr;										// 타이틀 시간 저장 변수

	CString strTemp;

	CString strData, strTime;
	
	/* ************************************************************************** */
	/* 파일 이름으로 사용할 날짜 설정한다                                         */
	/* ************************************************************************** */
	otCurr = COleDateTime::GetCurrentTime();
	
	nCurYear		= otCurr.GetYear();  
	nCurMonth		= otCurr.GetMonth();  
    nCurDay			= otCurr.GetDay();  

	nCurHour		= otCurr.GetHour();
	nCurMinute		= otCurr.GetMinute();
	nCurSecond		= otCurr.GetSecond();
	
	strNewFile.Format(_T("DAY_DATA%04d%02d%02d"), nCurYear, nCurMonth, nCurDay);
	strTime.Format(_T("%04d/%02d/%02d %02d:%02d:%02d"), nCurYear, nCurMonth, nCurDay, nCurHour, nCurMinute, nCurSecond);
		
	strCreateFile = st_path_info.strData + strNewFile;
	strCreateFile += ".TXT";
	
	OnStringToChar(strCreateFile, chFileName);
	nExistence = _access(chFileName, 0);
	
	if (nExistence == -1)  /* 파일 미존재 */
	{
		strCreateFile = st_path_info.strData + strNewFile;
		strCreateFile += ".TXT";
		OnStringToChar(strCreateFile, chFileName);
	}
	
	/* ************************************************************************** */
	/* 알람 발생 횟수 정보 저장 파일에 추가 가능한 형태 파일로 생성               */
	/* ************************************************************************** */
	fopen_s(&fp, chFileName, "a+");
	if(!fp)
 	{
 //		AfxMessageBox(_T("The failure because we open the file."));
 		return;
 	}
	/* ************************************************************************** */

	/* ************************************************************************** */
	/* 파일에 타이틀 정보 출력한다                                                */
	/* ************************************************************************** */
	strContent = _T("********************************************************************************************************");
	OnStringToChar(strContent, chMsg);
	fprintf(fp, "%s\r\n", chMsg) ;
//	fprintf(fp, chMsg) ;
//	fprintf(fp, "\r\n") ;

	//strContent.Format(_T("| %-100s |"), _T("AMT8562 [SSD Interface] : "));
	//kwlee 2017.0510
	strContent.Format(_T("| %-100s |"), _T("AMT830 STD HeatSink : "));
	OnStringToChar(strContent, chMsg);
	fprintf(fp, "%s\r\n", chMsg);
//	fprintf(fp, chMsg) ; 
//	fprintf(fp, "\r\n") ;

	strContent.Format(_T("| %-100s |"), _T("Day Data Info File"));
	OnStringToChar(strContent, chMsg);
	fprintf(fp,"%s\r\n", chMsg) ;
//	fprintf(fp, chMsg) ;
//	fprintf(fp, "\r\n") ;

	strContent.Format(_T("| %-100s |"), _T("DIVISION  : AMT Coporation"));
	OnStringToChar(strContent, chMsg);
	fprintf(fp,"%s\n", chMsg) ;
//	fprintf(fp, chMsg) ;
//	fprintf(fp, "\r\n") ;

	strContent.Format(_T("| %-100s |"), _T("Save Time : "));
	strContent += strTime;
	OnStringToChar(strContent, chMsg);
	fprintf(fp,"%s\r\n", chMsg) ;
//	fprintf(fp, chMsg) ;
//	fprintf(fp, "\r\n") ;

	//strTemp.Format(_T("%02d:%02d:%02d"), st_handler_info.tRun.GetTotalHours(), st_handler_info.tRun.GetMinutes(), st_handler_info.tRun.GetSeconds() );
	strTemp.Format(_T("%02d:%02d:%02d"), st_handler_info.tRun.GetHours(), st_handler_info.tRun.GetMinutes(), st_handler_info.tRun.GetSeconds() );
	strContent.Format(_T("| %-100s |"), _T("Run Time : "));
	strContent += strTemp;
	OnStringToChar(strContent, chMsg);
	fprintf(fp,"%s\r\n", chMsg) ;
//	fprintf(fp, chMsg) ;
//	fprintf(fp, "\r\n") ;

	//strTemp.Format(_T("%02d:%02d:%02d"), st_handler_info.tStop.GetTotalHours(), st_handler_info.tStop.GetMinutes(), st_handler_info.tStop.GetSeconds() );
	strTemp.Format(_T("%02d:%02d:%02d"), st_handler_info.tStop.GetHours(), st_handler_info.tStop.GetMinutes(), st_handler_info.tStop.GetSeconds() );
	strContent.Format(_T("| %-100s |"), _T("Stop Time : "));
	strContent += strTemp;
	OnStringToChar(strContent, chMsg);
	fprintf(fp,"%s\r\n", chMsg) ;
//	fprintf(fp, chMsg) ;
//	fprintf(fp, "\r\n") ;

	//strTemp.Format(_T("%02d:%02d:%02d"), st_handler_info.tJam.GetTotalHours(), st_handler_info.tJam.GetMinutes(), st_handler_info.tJam.GetSeconds() );
	strTemp.Format(_T("%02d:%02d:%02d"), st_handler_info.tJam.GetHours(), st_handler_info.tJam.GetMinutes(), st_handler_info.tJam.GetSeconds() );
	strContent.Format(_T("| %-100s |"), _T("Alarm Time : "));
	strContent += strTemp;
	OnStringToChar(strContent, chMsg);
	fprintf(fp,"%s\r\n", chMsg) ;
//	fprintf(fp, chMsg) ;
//	fprintf(fp, "\r\n") ;

	strTemp.Format(_T("%d"), st_alarm_info.nAlarmNum);
	strContent.Format(_T("| %-100s |"), _T("Alarm Count : "));
	strContent += strTemp;
	OnStringToChar(strContent, chMsg);
	fprintf(fp,"%s\r\n", chMsg) ;
//	fprintf(fp, chMsg) ;
//	fprintf(fp, "\r\n") ;

	nMtbi = (int)st_handler_info.tRun.GetTotalHours() * 3600 + (int)st_handler_info.tRun.GetMinutes() * 60 + (int)st_handler_info.tRun.GetSeconds();
	if (st_alarm_info.nAlarmNum > 0)
	{
		nMtbi = nMtbi / st_alarm_info.nAlarmNum;
	}

	strTemp.Format(_T("%02d:%02d:%02d"), nMtbi / 3600, (nMtbi % 3600) / 60, nMtbi % 60 );
	strContent.Format(_T("| %-100s |"), _T("MTBI : "));
	strContent += strTemp;
	OnStringToChar(strContent, chMsg);
	fprintf(fp,"%s\r\n", chMsg) ;
//	fprintf(fp, chMsg) ;
//	fprintf(fp, "\r\n") ;

	strTemp.Format(_T("%d"), st_count_info.nInCount[1][0]);
	strContent.Format(_T("| %-100s |"), _T("TOTAL : "));
	strContent += strTemp;
	OnStringToChar(strContent, chMsg);
	fprintf(fp,"%s\r\n", chMsg) ;

	strTemp.Format(_T("%d"), st_count_info.nPrimeCount[1][0]);
	strContent.Format(_T("| %-100s |"), _T("PRIME PASS: "));
	strContent += strTemp;
	OnStringToChar(strContent, chMsg);
	fprintf(fp,"%s\r\n", chMsg) ;

	dAve = 0.0f;
	if (st_count_info.nPrimeCount[1][0] > 0) 
	{
		dAve = ((double)st_count_info.nPrimeCount[1][0] / (double)st_count_info.nInCount[1][0]) * (double)100;
	}
	strTemp.Format(_T("%.3f"), dAve);
	strContent.Format(_T("| %-100s |"), _T("PRIME YIELD: "));
	strContent += strTemp;
	OnStringToChar(strContent, chMsg);
	fprintf(fp,"%s\r\n", chMsg) ;
	
	strTemp.Format(_T("%d"), st_count_info.nPassCount[1][0]);
	strContent.Format(_T("| %-100s |"), _T("CUM : "));
	strContent += strTemp;
	OnStringToChar(strContent, chMsg);
	fprintf(fp,"%s\r\n", chMsg) ;

	dAve = 0.0f;
	if (st_count_info.nPassCount[1][0] > 0) 
	{
		dAve = ((double)st_count_info.nPassCount[1][0] / (double)st_count_info.nInCount[1][0]) * (double)100;
	}
	strTemp.Format(_T("%.3f"), dAve);
	strContent.Format(_T("| %-100s |"), _T("CUM YIELD : "));
	strContent += strTemp;
	OnStringToChar(strContent, chMsg);
	fprintf(fp,"%s\r\n", chMsg) ;

	dAve = 0.0f;
	if (st_count_info.nUphCnt > 0)
	{
		dAve = st_count_info.dDailyPer / (double)st_count_info.nUphCnt;
	}
	strTemp.Format(_T("%.3f"), dAve);
	strContent.Format(_T("| %-100s |"), _T("SOCKET YIELD : "));
	strContent += strTemp;
	OnStringToChar(strContent, chMsg);
	fprintf(fp,"%s\r\n", chMsg) ;

	strContent = _T("********************************************************************************************************");
	OnStringToChar(strContent, chMsg);
	fprintf(fp,"%s\r\n", chMsg) ;
//	fprintf(fp, chMsg) ;
//	fprintf(fp, "\r\n") ;

	if (ferror(fp))  
	{
//		Func.MsgLog("파일 저장 실패!..") ;
		fclose(fp); 

		return ;
	}

	fclose(fp); 
/*	
	strContent.Format("| %-100s |", "AMT8560 [SSD Interface Tester] : " + g_ver.GetDate() );
	fprintf(fp,"%s\r\n", mstr_content) ;
	
	mstr_content.Format("| %-100s |", "Day Data Info File");
	fprintf(fp,"%s\r\n", mstr_content) ;
	
	mstr_content.Format("| %-100s |", "DIVISION  : AMT Coporation");
	fprintf(fp,"%s\n", mstr_content) ;

	mstr_content.Format("| %-100s |", "File Name : " + st_path.str_lot_data_path + str_new_file);
	fprintf(fp,"%s\r\n", mstr_content) ;

	mstr_content.Format("| %-100s |", "Save Time : " + str_time);
	fprintf(fp,"%s\r\n", mstr_content) ;

	strTemp.Format("%06d", g_lotMgr.GetInputCnt(PRIME));
	mstr_content.Format("| %-100s |", "Input Prime : " + strTemp);
	fprintf(fp,"%s\r\n", mstr_content) ;

	strTemp.Format("%06d", g_lotMgr.GetPassCnt(PRIME));
	mstr_content.Format("| %-100s |", "Pass  Prime : " + strTemp);
	fprintf(fp,"%s\r\n", mstr_content) ;

	strTemp.Format("%06d", g_lotMgr.GetFailCnt(PRIME));
	mstr_content.Format("| %-100s |", "Fail Prime : " + strTemp);
	fprintf(fp,"%s\r\n", mstr_content);

	fMdlyield = 0;
	
	if (g_lotMgr.GetPassCnt(PRIME) == 0)
	{
		fMdlyield = 0;
	}
	else
	{
		fMdlyield = (double)g_lotMgr.GetPassCnt(PRIME) / (double)g_lotMgr.GetInputCnt(PRIME) * 100.0f;
	}
	
	strTemp.Format("%3.2f%%", fMdlyield);
	
	mstr_content.Format("| %-100s |", "Prime Yield  : " + strTemp);
	fprintf(fp,"%s\r\n", mstr_content) ;


	// CUM
	strTemp.Format("%06d", g_lotMgr.GetInputCnt(CUM));
	mstr_content.Format("| %-100s |", "Input Cum   : " + strTemp);
	fprintf(fp,"%s\r\n", mstr_content) ;
	
	strTemp.Format("%06d", g_lotMgr.GetPassCnt(CUM));
	mstr_content.Format("| %-100s |", "Pass  Cum   : " + strTemp);
	fprintf(fp,"%s\r\n", mstr_content) ;
	
	strTemp.Format("%06d", g_lotMgr.GetFailCnt(CUM));
	mstr_content.Format("| %-100s |", "Fail Cum  : " + strTemp);
	fprintf(fp,"%s\r\n", mstr_content) ;

	fMdlyield = 0;

	if (g_lotMgr.GetPassCnt(CUM) == 0)
	{
		fMdlyield = 0;
	}
	else
	{
		fMdlyield = (double)g_lotMgr.GetPassCnt(CUM) / (double)g_lotMgr.GetInputCnt(CUM) * 100.0f;
	}
	
	strTemp.Format("%3.2f%%", fMdlyield);
	
	mstr_content.Format("| %-100s |", "Cum   Yield  : " + strTemp);
	fprintf(fp,"%s\r\n", mstr_content) ;
	mstr_content.Format("| %-100s |", "");
	fprintf(fp,"%s\r\n", mstr_content) ;

	strTemp.Format( "%02d:%02d:%02d", st_handler.m_tDR.GetTotalHours(), st_handler.m_tDR.GetMinutes(), st_handler.m_tDR.GetSeconds() );
	mstr_content.Format("| %-100s |", "Run Time : " + strTemp);
	fprintf(fp,"%s\r\n", mstr_content) ;

	strTemp.Format( "%02d:%02d:%02d", st_handler.m_tDS.GetTotalHours(), st_handler.m_tDS.GetMinutes(), st_handler.m_tDS.GetSeconds() );
	mstr_content.Format("| %-100s |", "Stop Time : " + strTemp);
	fprintf(fp,"%s\r\n", mstr_content) ;

	strTemp.Format( "%02d:%02d:%02d", st_handler.m_tDJ.GetTotalHours(), st_handler.m_tDJ.GetMinutes(), st_handler.m_tDJ.GetSeconds() );
	mstr_content.Format("| %-100s |", "Alarm Time : " + strTemp);
	fprintf(fp,"%s\r\n", mstr_content) ;

	strTemp.Format( "%d", g_handler.GetAlarmCnt() );
	mstr_content.Format("| %-100s |", "Alarm Count : " + strTemp);
	fprintf(fp,"%s\r\n", mstr_content) ;

	int nSec_MTBI = st_handler.m_tDR.GetTotalHours() * 3600 + st_handler.m_tDR.GetMinutes() * 60 + st_handler.m_tDR.GetSeconds();
	if( g_handler.GetAlarmCnt() == 0 )
		nSec_MTBI = 0;
	else
	{
		nSec_MTBI /= g_handler.GetAlarmCnt();
	}

	strTemp.Format( "%02d:%02d:%02d", nSec_MTBI / 3600, (nSec_MTBI % 3600) / 60, nSec_MTBI % 60 );
	mstr_content.Format("| %-100s |", "MTBI : " + strTemp);
	fprintf(fp,"%s\r\n", mstr_content) ;

	mstr_content = "********************************************************************************************************";
	fprintf(fp,"%s\r\n", mstr_content) ;
	
	str_temp_data = "";
	
	if (ferror(fp))  
	{
		Func.MsgLog("파일 저장 실패!..") ;
		return ;
	}
	
	fclose(fp);  /* 파일 종료 */
}

void CPublicFunction::OnHourDataSave(CString strHourName, int nQty, double dSocketYield, int nStart, int nOn, int nOff, CString strOff, CString strOn)
{
	CString strFileName;				// 마지막으로 생성된 파일 이름 저장 변수 
	CString strCreateFile;				// 알람 정보 저장할 파일에 대한 [폴더]+[파일명]+[확장자] 설정 변수 
	CString strListName, strTempData;	// 각 부분별 알람 발생 횟수 정보 저장할 로그 파일 정보 저장 변수 
	CString strContent;				// 한 라인에 출력할 문자열 정보 저장 변수 
	int nExistence;						// 파일 존재 유무 설정 플래그 
	char chFileName[256];				// 검색할 파일 정보 설정 함수 
	char chMsg[1000];
	FILE  *fp ;							// 파일에 대한 포인터 설정 변수 
	
	CString strTitleTime, strFileTime, strNewFile;		// 파일에 출력할 타이틀 시간 저장 변수
	int nCurYear, nCurMonth, nCurDay;					// 년, 월, 일 저장 변수
	int nCurHour, nCurMinute, nCurSecond;				// 년, 월, 일 저장 변수


	double dAve;
	//double dTemp;
	//
	
	COleDateTime otCurr;									// 현재 시간 저장 변수
	CTime tCurr;										// 타이틀 시간 저장 변수

	CString strTemp;

	CString strData, strTime;
	
	/* ************************************************************************** */
	/* 파일 이름으로 사용할 날짜 설정한다                                         */
	/* ************************************************************************** */
	otCurr = COleDateTime::GetCurrentTime();
	
	nCurYear		= otCurr.GetYear();  
	nCurMonth		= otCurr.GetMonth();  
    nCurDay			= otCurr.GetDay();  

	nCurHour		= otCurr.GetHour();
	nCurMinute		= otCurr.GetMinute();
	nCurSecond		= otCurr.GetSecond();
	
	strNewFile.Format(_T("HOUR_DATA%04d%02d%02d"), nCurYear, nCurMonth, nCurDay);
	strTime.Format(_T("%04d/%02d/%02d %02d:%02d:%02d"), nCurYear, nCurMonth, nCurDay, nCurHour, nCurMinute, nCurSecond);
		
	strCreateFile = st_path_info.strData + strHourName;
	strCreateFile += ".TXT";
	
	OnStringToChar(strCreateFile, chFileName);
	nExistence = _access(chFileName, 0);
	
	if (nExistence == -1)  /* 파일 미존재 */
	{
		strCreateFile = st_path_info.strData + strHourName;
		strCreateFile += ".TXT";
		OnStringToChar(strCreateFile, chFileName);

		/* ************************************************************************** */
		/* 알람 발생 횟수 정보 저장 파일에 추가 가능한 형태 파일로 생성               */
		/* ************************************************************************** */
		fopen_s(&fp, chFileName, "a+");
		if(!fp)
		{
			//		AfxMessageBox(_T("The failure because we open the file."));
			return;
		}

		/* ************************************************************************** */
		/* 파일에 타이틀 정보 출력한다                                                */
		/* ************************************************************************** */
		strContent = _T("********************************************************************************************************");
		OnStringToChar(strContent, chMsg);
		fprintf(fp, "%s\r\n", chMsg) ;

		//strContent.Format(_T("| %-100s |"), _T("AMT8562 [SSD Interface] : "));
		//kwlee 2017.0510
		strContent.Format(_T("| %-100s |"), _T("AMT830 STD HeatSink : "));
		OnStringToChar(strContent, chMsg);
		fprintf(fp, "%s\r\n", chMsg);

		strContent.Format(_T("| %-100s |"), _T("Day Data Info File"));
		OnStringToChar(strContent, chMsg);
		fprintf(fp,"%s\r\n", chMsg) ;

		strContent.Format(_T("| %-100s |"), _T("DIVISION  : AMT Coporation"));
		OnStringToChar(strContent, chMsg);
		fprintf(fp,"%s\n", chMsg) ;
	}
	else
	{
		/* ************************************************************************** */
		/* 알람 발생 횟수 정보 저장 파일에 추가 가능한 형태 파일로 생성               */
		/* ************************************************************************** */
		fopen_s(&fp, chFileName, "a+");
		if(!fp)
		{
			//		AfxMessageBox(_T("The failure because we open the file."));
			return;
		}
	}

	strContent.Format(_T("| %-100s |"), _T("Save Time : "));
	strContent += strTime;
	OnStringToChar(strContent, chMsg);
	fprintf(fp,"%s\r\n", chMsg) ;

	strTemp.Format(_T("%d"), st_handler_info.tRunUph.GetTotalMinutes());
	strContent.Format(_T("| %-100s |"), _T("RUN TIME : "));
	strContent += strTemp;
	OnStringToChar(strContent, chMsg);
	fprintf(fp,"%s\r\n", chMsg) ;

	st_count_info.nDailyUph += nQty;
	st_count_info.nUphCnt++;

	strTemp.Format(_T("%d"), st_count_info.nDailyUph);
	strContent.Format(_T("| %-100s |"), _T("TOTAL : "));
	strContent += strTemp;
	OnStringToChar(strContent, chMsg);
	fprintf(fp,"%s\r\n", chMsg) ;

	strTemp.Format(_T("%d"), nQty);
	strContent.Format(_T("| %-100s |"), _T("QTY : "));
	strContent += strTemp;
	OnStringToChar(strContent, chMsg);
	fprintf(fp,"%s\r\n", chMsg) ;

	strTemp.Format(_T("%d"), nStart);
	strContent.Format(_T("| %-100s |"), _T("SOCKET : "));
	strContent += strTemp;
	OnStringToChar(strContent, chMsg);
	fprintf(fp,"%s\r\n", chMsg) ;

	st_count_info.dDailyPer += dSocketYield;
	dAve = 0.0f;
	if (st_count_info.nUphCnt > 0)
	{
		dAve = st_count_info.dDailyPer / (double)st_count_info.nUphCnt;
	}
	strTemp.Format(_T("Yield : %.2f/%.2f Count : %d Slot : %s"), dSocketYield, dAve, nOn, strOn);
	strContent.Format(_T("| %-100s |"), _T("SOCKET ON : "));
	strContent += strTemp;
	OnStringToChar(strContent, chMsg);
	fprintf(fp,"%s\r\n", chMsg) ;

	strTemp.Format(_T("%d Slot : %s"), nOff, strOff);
	strContent.Format(_T("| %-100s |"), _T("SOCKET OFF : "));
	strContent += strTemp;
	OnStringToChar(strContent, chMsg);
	fprintf(fp,"%s\r\n", chMsg) ;
	
	strContent = _T("********************************************************************************************************");
	OnStringToChar(strContent, chMsg);
	fprintf(fp,"%s\r\n", chMsg) ;

	if (ferror(fp))  
	{
//		Func.MsgLog("파일 저장 실패!..") ;
		fclose(fp); 

		return ;
	}

	fclose(fp); 
}

void CPublicFunction::OnLogFileAdd(int nMsgSelect, CString strMsg)
{
	CFileFind filefind;
	CString mstr_cur_year, mstr_cur_month, mstr_cur_day, str_display_time; // 현재 년, 월, 일 정보 문자형으로 변환하여 저장할 변수 
	int mn_cur_year, mn_cur_month, mn_cur_day, mn_cur_hour; // 현재 년, 월, 일 정보 저장 변수 
	CString mstr_file_name;		// 마지막으로 생성된 파일 이름 저장 변수 
	CString mstr_create_file;	// 알람 정보 저장할 파일에 대한 [폴더]+[파일명]+[확장자] 설정 변수 
	CString mstr_list_name, mstr_temp_data;  // 각 부분별 알람 발생 횟수 정보 저장할 로그 파일 정보 저장 변수 
	CString mstr_content;		// 한 라인에 출력할 문자열 정보 저장 변수 
	COleDateTime time_cur;		// 검사할 시간 정보 저장 변수 
	CTime m_time_current;		// 간략한 헝식의 현재 시간 정보 저장 변수
	int mn_existence;			// 파일 존재 유무 설정 플래그 
	char fileName[256];			// 검색할 파일 정보 설정 함수 
	char chFileName[256];
	char chBackName[256];
	FILE  *fp ;					// 파일에 대한 포인터 설정 변수

	CString BackupName;
	CString mstr_cur_hour, mstr_cur_min, mstr_cur_sec;
	int Ret;

	if (strMsg.IsEmpty() == TRUE)  
	{
		return;
	}

	CSingleLock sing(&mutex_f);

	sing.Lock();
	// **************************************************************************
	// 파일 이름으로 사용할 날짜 정보를 얻는다                                   
	// **************************************************************************
	time_cur = COleDateTime::GetCurrentTime();  // 현재 시간 정보를 얻는다. 

	m_time_current = CTime::GetCurrentTime() ;  // 간략한 형식의 현재 시간 정보 얻는다. 

	mn_cur_year = time_cur.GetYear();  

	mn_cur_month = time_cur.GetMonth();  

    mn_cur_day = time_cur.GetDay();  

	mn_cur_hour = time_cur.GetHour();
	// **************************************************************************

	// **************************************************************************
	// 날짜 정보를 문자형으로 변환하여 변수에 설정한다                           
	// **************************************************************************
	mstr_cur_year.Format(_T("%04d"), mn_cur_year);  
	mstr_cur_month.Format(_T("%02d"), mn_cur_month);
	mstr_cur_day.Format(_T("%02d"), mn_cur_day);

	// **************************************************************************
	// 현재 시간 정보 얻는다                                                     
	// **************************************************************************
	mn_cur_hour = time_cur.GetHour();				// 현재 시간 정보를 설정한다. 
	mstr_cur_hour.Format(_T("%d"),time_cur.GetHour());	// 현재 시간 정보를 설정한다.
	mstr_cur_min.Format(_T("%d"),time_cur.GetMinute());	// 현재 분 정보를 설정한다. 
	mstr_cur_sec.Format(_T("%d"),time_cur.GetSecond());	// 현재 초 정보를 설정한다. 
	str_display_time = m_time_current.Format(_T("%c"));	// 리스트 파일에 출력할 타이틀 시간 정보 설정 
	// **************************************************************************

	switch(nMsgSelect)			// Operation Setting
	{		
		case 0:
		case 1:
			mstr_file_name = _T("OP") + mstr_cur_year;
			mstr_file_name += mstr_cur_month; 
			mstr_file_name += mstr_cur_day; 
			mstr_create_file = st_path_info.strOperation + mstr_file_name;
			break;
		case 2:							// 장비 동작 관련.
			mstr_file_name = _T("MA") + mstr_cur_year;
			mstr_file_name += mstr_cur_month; 
			mstr_file_name += mstr_cur_day; 
			mstr_create_file = st_path_info.strMachine + mstr_file_name;
			break;
		case 3:							// 장비 디버깅 관련.
			mstr_file_name = _T("DEBUG") + mstr_cur_year;
			mstr_file_name += mstr_cur_month; 
			mstr_file_name += mstr_cur_day; 
			mstr_create_file = st_path_info.strMachine + mstr_file_name;
			break;
		case 4:							// 장비 디버깅 관련.
			mstr_file_name = _T("IT") + mstr_cur_year;
			mstr_file_name += mstr_cur_month; 
			mstr_file_name += mstr_cur_day; 
			mstr_create_file = st_path_info.strInterface + mstr_file_name;
			break;
		case 99:						// 전체 메세지.
			mstr_file_name = _T("TO") + mstr_cur_year;
			mstr_file_name += mstr_cur_month; 
			mstr_file_name += mstr_cur_day; 
			mstr_create_file = st_path_info.strTotal + mstr_file_name;
			break;
	}

	mstr_create_file += _T(".TXT");

	//wsprintfA(fileName, "%S", mstr_create_file);
	clsFunc.OnStringToChar(mstr_create_file, fileName);

	mn_existence = filefind.FindFile(mstr_create_file,0);
	
	if (mn_existence == -1)
	{
		switch(nMsgSelect)			// Operation Setting
		{		
			case 0:
			case 1:
				mstr_file_name = _T("OP") + mstr_cur_year;
				mstr_file_name += mstr_cur_month; 
				mstr_file_name += mstr_cur_day; 
				mstr_create_file = st_path_info.strOperation + mstr_file_name;
				break;

			case 2:							// 장비 동작 관련.
				mstr_file_name = _T("MA") + mstr_cur_year;
				mstr_file_name += mstr_cur_month; 
				mstr_file_name += mstr_cur_day; 
				mstr_create_file = st_path_info.strMachine + mstr_file_name;
				break;

			case 3:							// 장비 디버깅 관련.
				mstr_file_name = _T("DEBUG") + mstr_cur_year;
				mstr_file_name += mstr_cur_month; 
				mstr_file_name += mstr_cur_day; 
				mstr_create_file = st_path_info.strMachine + mstr_file_name;
				break;

			case 4:							// 장비 디버깅 관련.
				mstr_file_name = _T("IT") + mstr_cur_year;
				mstr_file_name += mstr_cur_month; 
				mstr_file_name += mstr_cur_day; 
				mstr_create_file = st_path_info.strInterface + mstr_file_name;
				break;

			case 99:						// 전체 메세지.
				mstr_file_name = _T("TOT") + mstr_cur_year;
				mstr_file_name += mstr_cur_month; 
				mstr_file_name += mstr_cur_day; 
				mstr_create_file = st_path_info.strTotal + mstr_file_name;
				break;
		}
		mstr_create_file += _T(".TXT");
		// **********************************************************************
	}

	Ret = OnFileSizeCheck(mstr_create_file, 1048576, YES); //size and rename
	
	if(Ret == 1) //file size over
	{
		//
		BackupName = mstr_create_file + mstr_cur_hour + mstr_cur_min +  mstr_cur_sec + _T(".bak") ;
		
//		wsprintfA(chFileName, "%S", mstr_create_file);
		clsFunc.OnStringToChar(mstr_create_file, chFileName);
//		wsprintfA(chBackName, "%S", BackupName);
		clsFunc.OnStringToChar(BackupName, chBackName);
		rename(chFileName, chBackName);
	}

	// **************************************************************************
	// 알람 발생 횟수 정보 저장 파일에 추가 가능한 형태 파일로 생성              
	// **************************************************************************
	char chMode[10];
//	wsprintfA(chMode, "%S", _T("a+"));
	clsFunc.OnStringToChar(_T("a+"), chMode);
// jtkim 20130704
//	if ((fp = fopen(fileName, chMode)) == NULL) 
//	if ((fp = fopen_s(&fp,fileName, chMode)) == NULL) 
	fopen_s(&fp, fileName, "a+");
	if(!fp)
	{
//		AfxMessageBox(_T("File open failure!.."));

		return;
	}
	// **************************************************************************

	// **************************************************************************
	// 로그 파일에 현재 발생한 알람 정보 저장한다                                
	// **************************************************************************
	if (st_handler_info.strUserId != _T(""))
	{
		mstr_content += "[";
		mstr_content += st_handler_info.strUserId;
		mstr_content += "] ";
	}
	
	mstr_content += str_display_time;
	mstr_content += _T(" , ") + strMsg;
	mstr_content += _T("\n");

	char chData[20000];
//	wsprintfA(chData, "%S", mstr_content);
	if (mstr_content.GetLength() > 20000) 
	{
		fclose(fp);

		return ;
	}

	clsFunc.OnStringToChar(mstr_content, chData);
//	fprintf(fp,_T("%s\n"),mstr_content) ;
	
	fprintf(fp, chData) ;
	if (ferror(fp))  
	{
		if (st_handler_info.cWndList != NULL)  // 리스트 바 화면 존재
		{
//			st_other.str_op_msg = _T(_T("File save failure."));
//			wsprintfA(st_other_info.cNormalMsg, "%S", _T("File save failure."));
			//clsFunc.OnStringToChar(_T("File save failure."), st_other_info.cNormalMsg);
			clsMem.OnNormalMessageWrite(_T("File save failure."));
			st_handler_info.cWndList->PostMessage(WM_LIST_DATA, 0, NORMAL_MSG);
		}

		sing.Unlock();
		fclose(fp);

		return ;
	}
	// **************************************************************************
	fclose(fp);  // 파일을 종료한다.

	sing.Unlock();
}

int CPublicFunction::OnFileSizeCheck(CString strFileName, long lSize, int nCheck)
{
	CFileFind finder;
	long Len=0, flag=0;
	BOOL bContinue;

	if(bContinue = finder.FindFile(strFileName))
	{	
		if (nCheck == YES)			// Size를 체크하는것이면...
		{
			finder.FindFile(strFileName);
			finder.FindNextFile();
			finder.GetFileName();
			Len = (long)finder.GetLength();
			if(Len > lSize)
			{
				flag = 1;
			}
			finder.Close();	
		}
		else						// Size를 확인하는것이면...
		{
			finder.FindFile(strFileName);
			finder.FindNextFile();
			finder.GetFileName();
			Len = (long)finder.GetLength();
			
			flag = Len;
			
			finder.Close();	
		}
	}
	
	return flag;
}


int CPublicFunction::OnLightCurtainCheck()
{
	return RET_GOOD;
}

int	CPublicFunction::OnMpCheck()
{
	long dwMotionDone=0;//2015.0308 
	int nFlag = 0;

	//left m/p 
	
	return RET_GOOD;
}

int CPublicFunction::OnDoorOpenCheck()
{
	CString strTemp;
//	int i;

	/*for (i=0; i<15; i++)
	{
		if (FAS_IO.get_in_bit(st_io_info.i_DoorChk[i], IO_ON) == IO_OFF)
		{
			strTemp.Format(_T("81%04d"), st_io_info.i_Door1Chk + i);
			CTL_Lib.Alarm_Error_Occurrence(6000+i, dWARNING, strTemp);

			return RET_ERROR;
		}
	}
	return RET_GOOD;*/

	return RET_GOOD;
}

int CPublicFunction::OnEmoCheck()
{
	if (FAS_IO.get_in_bit(st_io_info.i_Emo1SwChk, IO_OFF) == IO_ON)
	{
		CTL_Lib.Alarm_Error_Occurrence(7000, dRUN, _T("810112"));

		return RET_ERROR;
	}

	if (FAS_IO.get_in_bit(st_io_info.i_Emo2SwChk, IO_OFF) == IO_ON)
	{
		CTL_Lib.Alarm_Error_Occurrence(7001, dRUN, _T("810113"));

		return RET_ERROR;
	}

	if (FAS_IO.get_in_bit(st_io_info.i_Emo3SwChk, IO_OFF) == IO_ON)
	{
		CTL_Lib.Alarm_Error_Occurrence(7002, dRUN, _T("810114"));

		return RET_ERROR;
	}

	if (FAS_IO.get_in_bit(st_io_info.i_Emo4SwChk, IO_OFF) == IO_ON)
	{
		CTL_Lib.Alarm_Error_Occurrence(7003, dRUN, _T("810115"));

		return RET_ERROR;
	}

	return RET_GOOD;
}

// jtkim 20130625
void CPublicFunction::OnDoorClose()
{
	if (OnDoorOpenCheck() == RET_GOOD)
	{
		FAS_IO.set_out_bit(st_io_info.o_DoorLock, IO_ON);
		
		if (st_handler_info.cWndList != NULL)
		{
			//wsprintfA(st_other_info.cNormalMsg, "%S", _T("Door LOCK Close"));
			//clsFunc.OnStringToChar(_T("Door LOCK Close"), st_other_info.cNormalMsg);
			clsMem.OnNormalMessageWrite(_T("Door LOCK Close"));
			st_handler_info.cWndList->PostMessage(WM_LIST_DATA, 0, NORMAL_MSG);
		}
	}
	else 
	{
		st_handler_info.nRunStatus = dWARNING;
	}
}

// jtkim 20130625
void CPublicFunction::OnDoorOpen()
{
	if (st_handler_info.nRunStatus		== dSTOP &&
		st_handler_info.nMachineMode	== MACHINE_MANUAL)
	{
		FAS_IO.set_out_bit(st_io_info.o_DoorLock, IO_OFF);
		
		if (st_handler_info.cWndList != NULL)
		{
			//wsprintfA(st_other_info.cNormalMsg, "%S", _T("DOOR LOCK Open"));
			//clsFunc.OnStringToChar(_T("DOOR LOCK Open"), st_other_info.cNormalMsg);
			clsMem.OnNormalMessageWrite(_T("DOOR LOCK Open"));
			st_handler_info.cWndList->PostMessage(WM_LIST_DATA, 0, NORMAL_MSG);
		}
	}
	else
	{
		if (st_handler_info.cWndList != NULL)
		{
			//wsprintfA(st_other_info.cNormalMsg, "%S", _T("[STOP] + [MANUAL] Status Action"));
			//clsFunc.OnStringToChar(_T("[STOP] + [MANUAL] Status Action"), st_other_info.cNormalMsg);
			clsMem.OnAbNormalMessagWrite(_T("[STOP] + [MANUAL] Status Action"));
			st_handler_info.cWndList->PostMessage(WM_LIST_DATA, 0, ABNORMAL_MSG);
		}
	}
}


int CPublicFunction::OnEncoderCheck(double dPos)
{
	CString strMsg;
	
	int nRet = NO;
	
//	CDialog_Message	dlgMsg;
		
//	dlgMsg.DoModal();
//	str_msg.Format("Now Reading Value is %ld, Setting?", (long)d_pos);
//	st_other.str_confirm_msg = _T(str_msg);
//	n_response = select_dlg.DoModal();
//	if (n_response == IDOK) 
//	{
//		Ret = YES;
//	}
//	else
//	{
//		Ret = NO;
//	}
	
	return nRet;
}

bool CPublicFunction::OnCreateFolder(CString strPath)
{
	int nRet = 0;
	char chfilename[100];

    do
	{
        nRet = strPath.Find('\\' , nRet + 1);
        if (nRet > 0 )
        {
            CString strTemp = strPath.Left(nRet+1);
			
			//wsprintfA(chfilename, "%S", strTemp);
			clsFunc.OnStringToChar(strTemp, chfilename);
            if (_access(chfilename.operator LPCTSTR(), 00) == -1)
			{
				CreateDirectory(strTemp , NULL);
			}
        }
    }while (nRet != -1);
	
    return true;
}
//==================================================================//
// 설비 상태를 RUN 상태로 변경
//==================================================================//
// jtkim 20130625
void CPublicFunction::OnMCRun() 
{
	// [LIGHT CURTAIN] 감지로 인해 파워 OFF된 축들이 존재할 수 있으므로 파워 OFF된 축들을 ON 시키도록 한다
	// - 문제가 되는 축들이 있는데 피치 가변과 관련된 축들이다
	// - 이 축들은 초기화 시 또는 새로운 LOT 시작 시 한번만 동작하기 때문이다
	// OnPowerOnAxisAll();  // 전체 모터축 파워 ON

	//==============================================================//
	// 알람 리셋 상태 보고 [ CIM 관련 ] 추후 작업 예정 
	//==============================================================//
	//--------------------------------------------------------------//

	//==============================================================//
	// 프로세스 상태 보고 [ CIM 관련 ] 추후 작업 예정 
	//==============================================================//
	//--------------------------------------------------------------//

	// 암호 레벨 초기화
	st_handler_info.nLevelTeach = FALSE;
	st_handler_info.nLevelMaint = FALSE;

	// 버튼 램프 설정
	FAS_IO.set_out_bit(st_io_info.o_StartLamp, IO_ON);   // S1500
	FAS_IO.set_out_bit(st_io_info.o_StopLamp,  IO_OFF);  // S1501
	FAS_IO.set_out_bit(st_io_info.o_AlarmLamp, IO_OFF);
	
	if (st_handler_info.cWndTitle != NULL)	
	{
		st_handler_info.cWndTitle->PostMessage(WM_STATUS_CHANGE, MACHINE_STATUS, st_handler_info.nRunStatus);
	}

	// 20140812 jtkim
	if (st_alarm_info.nAlarmClear == YES)
	{
		st_alarm_info.strCode		= _T("");
		st_alarm_info.nAlarmClear	= NO;
				
		clsXgem.OnMcAlarm(st_alarm_info.strCode, 0);
	}
	// 모션 보드 함수에서 RUN 상태일 경우에만 위치값 저장하게 되어 있다
	// 헌데, 현재 설비 상태를 설정해주는 곳이 없어 이곳에 추가한다
	// jtkim 20150818
	

	COMI.mn_run_status = dRUN;
}

//==================================================================//
// 설비 STOP 상태에 대한 버튼 램프 상태 변경
//==================================================================//
// jtkim 20130625
void CPublicFunction::OnMCStop() 
{
	//==============================================================//
	// 설비 상태 보고
	//==============================================================//
	// 매뉴얼 모드에서 STOP 버튼 눌린 경우는 상태 변경 없도록 하자
	if (st_work_info.nStatusEqp != PROC_MAINT)
	{
		// 자재가 걸리지 않은 상태에서 STOP 키 눌린 경우에는 [PROC_MAINT]로 설정한다
		st_work_info.nStatusEqp = PROC_MAINT;
	}
	//--------------------------------------------------------------//
	// 플래그 오동작한 경우 대비하여 추가함
	st_handler_info.nMenuLock = NO;

	// 버튼 램프 설정
	FAS_IO.set_out_bit(st_io_info.o_StartLamp, IO_OFF);  // S1500
	FAS_IO.set_out_bit(st_io_info.o_StopLamp,  IO_ON);   // S1501

	st_handler_info.nRunStatus = dSTOP;  // 설비 상태 플래그 변경 [STOP]
	if (st_handler_info.cWndTitle != NULL)	
	{
		st_handler_info.cWndTitle->PostMessage(WM_STATUS_CHANGE, MACHINE_STATUS, st_handler_info.nRunStatus);
	}
	// 모션 보드 함수에서 RUN 상태일 경우에만 위치값 저장하게 되어 있다
	// 헌데, 현재 설비 상태를 설정해주는 곳이 없어 이곳에 추가한다
	
	// recovery data save
	OnRecoveryReadWrite(0, 0);


	COMI.mn_run_status = dSTOP;
}

//==================================================================//
// 부저 사운드 ON/OFF
//==================================================================//
// jtkim 20130625
void CPublicFunction::OnSound(int nOnOff) 
{
	switch(nOnOff)
	{
		case IO_OFF:  // SOUND OFF
			FAS_IO.set_out_bit(st_io_info.o_Buzz1OnOff, IO_OFF);  //
			FAS_IO.set_out_bit(st_io_info.o_Buzz2OnOff, IO_OFF);  //
			FAS_IO.set_out_bit(st_io_info.o_Buzz3OnOff, IO_OFF);  //

			// 사운드 OFF 램프 꺼준다
			FAS_IO.set_out_bit(st_io_info.o_BuzzLamp, IO_OFF);  // 

			// 부저 사운드 OFF 되었다고 설정
			// : 해당 플래그 설정 시 일정 시간 후에 자동으로 OFF 시키기 위한 플래그 정보이다
			st_lamp_info.nStatusBuzzerRing = FALSE;
			break;

		case IO_ON:  // SOUND ON
			// 부저 사용 모드에서만 부저 사용한다
			if (st_lamp_info.nBuzzerMode == YES)
			{
				// 부저는 하나만 사용하도록 한다
				FAS_IO.set_out_bit(st_io_info.o_Buzz1OnOff, IO_ON);
				FAS_IO.set_out_bit(st_io_info.o_Buzz2OnOff, IO_ON);
				FAS_IO.set_out_bit(st_io_info.o_Buzz3OnOff, IO_ON);  //

				// 사운드 OFF 램프 켜준다
				FAS_IO.set_out_bit(st_io_info.o_BuzzLamp, IO_ON);

				st_lamp_info.lBuzzerOffWait[0] = GetCurrentTime();
				st_lamp_info.nStatusBuzzerRing = TRUE;
			}
			break;
	}
}

// jtkim 20130625
void CPublicFunction::OnInitVariable()
{
	st_sync_info.nInitializeError		= NO;
}


void CPublicFunction::OnIOPortClear()
{
	if (FAS_IO.get_out_bit(st_io_info.o_MainAir, IO_ON) == IO_OFF)
	{
		FAS_IO.set_out_bit(st_io_info.o_MainAir, IO_ON);
	}
}


void CPublicFunction::OnMotorSpeed()
{
	int i = 0, j = 0, nRet = 0;
	int nMotor[2]={0,};

	CString strMsg;
/*
	// loader magazine x
	nMotor[0] = M_LD_MGZ_X;
	// 1mm 이동하는데 필요한 pulse
	COMI.Set_MotUnitDist(nMotor[0], 250);
	// 10mm 이동하는데 필요한 pulse (속도는 1Cm/초로 세팅하게 된다.)
	COMI.Set_MotUnitSpeed(nMotor[0], 250);
	// motor 종류
	COMI.m_nMotInfo[nMotor[0]] = MOT_SERVO;
	COMI.mn_homecheck_method[nMotor[0]]= 6;

	// loader magazine z
	nMotor[0] = M_LD_MGZ_Z;
	// 1mm 이동하는데 필요한 pulse
	COMI.Set_MotUnitDist(nMotor[0], 2000);
	// 10mm 이동하는데 필요한 pulse (속도는 1Cm/초로 세팅하게 된다.)
	COMI.Set_MotUnitSpeed(nMotor[0], 2000);
	// motor 종류
	COMI.m_nMotInfo[nMotor[0]] = MOT_SERVO;
	COMI.mn_homecheck_method[nMotor[0]]= 1;

	// pcb shuttle x
	nMotor[0] = M_PCB_MOVE_X;
	// 1mm 이동하는데 필요한 pulse
	COMI.Set_MotUnitDist(nMotor[0], 500);
	// 10mm 이동하는데 필요한 pulse (속도는 1Cm/초로 세팅하게 된다.)
	COMI.Set_MotUnitSpeed(nMotor[0], 500);
	// motor 종류
	COMI.m_nMotInfo[nMotor[0]] = MOT_SERVO;
	COMI.mn_homecheck_method[nMotor[0]]= 6;

	// pcb shuttle left y
	nMotor[0] = M_PCB_MOVE_LF_Y;
	// 1mm 이동하는데 필요한 pulse
	COMI.Set_MotUnitDist(nMotor[0], 500);
	// 10mm 이동하는데 필요한 pulse (속도는 1Cm/초로 세팅하게 된다.)
	COMI.Set_MotUnitSpeed(nMotor[0], 500);
	// motor 종류
	COMI.m_nMotInfo[nMotor[0]] = MOT_STEP;
	st_io_info.oMotPwr[nMotor[0]] = st_io_info.oPcbLfCvyStepMotOnOff;
	COMI.mn_homecheck_method[nMotor[0]]= 6;

	// pcb shuttle right y
	nMotor[0] = M_PCB_MOVE_RI_Y;
	// 1mm 이동하는데 필요한 pulse
	COMI.Set_MotUnitDist(nMotor[0], 500);
	// 10mm 이동하는데 필요한 pulse (속도는 1Cm/초로 세팅하게 된다.)
	COMI.Set_MotUnitSpeed(nMotor[0], 500);
	// motor 종류
	COMI.m_nMotInfo[nMotor[0]] = MOT_STEP;
	st_io_info.oMotPwr[nMotor[0]] = st_io_info.oPcbRiCvyStepMotOnOff;
	COMI.mn_homecheck_method[nMotor[0]]= 6;

	// pcb shuttle move
	nMotor[0] = M_PCB_MOVE_Y;
	// 1mm 이동하는데 필요한 pulse
	COMI.Set_MotUnitDist(nMotor[0], 59.974);
	// 10mm 이동하는데 필요한 pulse (속도는 1Cm/초로 세팅하게 된다.)
	COMI.Set_MotUnitSpeed(nMotor[0], 59.974);
	// motor 종류
	COMI.m_nMotInfo[nMotor[0]] = MOT_STEP;
	st_io_info.oMotPwr[nMotor[0]] = st_io_info.oPcbHookStepMotOnOff;
	COMI.mn_homecheck_method[nMotor[0]]= 1;

	// pcb transfer y
	nMotor[0] = M_PCB_RBT_Y;
	// 1mm 이동하는데 필요한 pulse
	COMI.Set_MotUnitDist(nMotor[0], 500);
	// 10mm 이동하는데 필요한 pulse (속도는 1Cm/초로 세팅하게 된다.)
	COMI.Set_MotUnitSpeed(nMotor[0], 500);
	// motor 종류
	COMI.m_nMotInfo[nMotor[0]] = MOT_SERVO;
	COMI.mn_homecheck_method[nMotor[0]]= 6;

	// pcb transfer z
	nMotor[0] = M_PCB_RBT_Z;
	// 1mm 이동하는데 필요한 pulse
	COMI.Set_MotUnitDist(nMotor[0], 2000);
	// 10mm 이동하는데 필요한 pulse (속도는 1Cm/초로 세팅하게 된다.)
	COMI.Set_MotUnitSpeed(nMotor[0], 2000);
	// motor 종류
	COMI.m_nMotInfo[nMotor[0]] = MOT_SERVO;
	COMI.mn_homecheck_method[nMotor[0]]= 1;

	// pcb transfer rotator
	nMotor[0] = M_PCB_RBT_ROT;
	// 1mm 이동하는데 필요한 pulse
	COMI.Set_MotUnitDist(nMotor[0], 555.7964007);
	// 10mm 이동하는데 필요한 pulse (속도는 1Cm/초로 세팅하게 된다.)
	COMI.Set_MotUnitSpeed(nMotor[0], 555.7964007);
	// motor 종류
	COMI.m_nMotInfo[nMotor[0]] = MOT_SERVO;
	COMI.mn_homecheck_method[nMotor[0]]= 1;

	// jig align y
	nMotor[0] = M_JIG_ALIGN_Y;
	// 1mm 이동하는데 필요한 pulse
	COMI.Set_MotUnitDist(nMotor[0], 5000);
	// 10mm 이동하는데 필요한 pulse (속도는 1Cm/초로 세팅하게 된다.)
	COMI.Set_MotUnitSpeed(nMotor[0], 5000);
	// motor 종류
	COMI.m_nMotInfo[nMotor[0]] = MOT_SERVO;
	COMI.mn_homecheck_method[nMotor[0]]= 6;

	// jig transfer x
	nMotor[0] = M_JIG_RBT_X;
	// 1mm 이동하는데 필요한 pulse
	COMI.Set_MotUnitDist(nMotor[0], 500);
	// 10mm 이동하는데 필요한 pulse (속도는 1Cm/초로 세팅하게 된다.)
	COMI.Set_MotUnitSpeed(nMotor[0], 500);
	// motor 종류
	COMI.m_nMotInfo[nMotor[0]] = MOT_SERVO;
	COMI.mn_homecheck_method[nMotor[0]]= 6;

	// jig transfer z
	nMotor[0] = M_JIG_RBT_Z;
	// 1mm 이동하는데 필요한 pulse
	COMI.Set_MotUnitDist(nMotor[0], 2000);
	// 10mm 이동하는데 필요한 pulse (속도는 1Cm/초로 세팅하게 된다.)e
	COMI.Set_MotUnitSpeed(nMotor[0], 2000);
	// motor 종류
	COMI.m_nMotInfo[nMotor[0]] = MOT_SERVO;
	COMI.mn_homecheck_method[nMotor[0]]= 1;

	// jig stacker 
	nMotor[0] = M_JIG_STK;
	// 1mm 이동하는데 필요한 pulse
	COMI.Set_MotUnitDist(nMotor[0], 6000);
	// 10mm 이동하는데 필요한 pulse (속도는 1Cm/초로 세팅하게 된다.)
	COMI.Set_MotUnitSpeed(nMotor[0], 6000);
	// motor 종류
	COMI.m_nMotInfo[nMotor[0]] = MOT_SERVO;
	COMI.mn_homecheck_method[nMotor[0]]= 6;

	COMI.mn_max_home_limit_time = 120000;
	COMI.mn_max_move_limit_time = 120000;

	for (i = 0; i < MAXMOTOR; i++)
	{
		COMI.md_limit_position[i][0] = st_motor_info[i].d_limit_position[0];
		COMI.md_limit_position[i][1] = st_motor_info[i].d_limit_position[1];

		COMI.md_spd_vel[i][0]			= st_motor_info[i].d_spd_vel[0];
		COMI.md_spd_vel[i][1]			= st_motor_info[i].d_spd_vel[1];
		COMI.md_spd_vel[i][2]			= st_motor_info[i].d_spd_vel[2];

		COMI.md_spd_home[i]				= st_motor_info[i].d_spd_home[0];
		COMI.md_spd_jog[i]				= st_motor_info[i].d_spd_jog[0];

		COMI.mn_allow_value[i]			= st_motor_info[i].n_allow; 

//		COMI.mn_homecheck_method[i]		= 6;	//el on-> stop-> back-> el off - > stop 
		nRet = COMI.Set_HomeSetConfig(i, COMI.mn_homecheck_method[i], 0, 2, 1);
		if (nRet != BD_GOOD)
		{
			if (st_handler_info.cWndList != NULL)
			{
				strMsg.Format(_T("Set_HomeSet_Config Error [MotNum[%d]]"), i);
				//wsprintfA(st_other_info.cAbnormalMsg, "%S", strMsg);
				//clsFunc.OnStringToChar(strMsg, st_other_info.cAbnormalMsg);
				clsMem.OnAbNormalMessagWrite(strMsg);
				st_handler_info.cWndList->PostMessage(WM_LIST_DATA, 0, ABNORMAL_MSG);  // 동작 완료 출력 요청
			}
		}
	}

	//////////////////////////////////////////////////////
	//SD Sensor 관련 변수 테스트 
	//////////////////////////////////////////////////////
	COMI.Set_Motor_IO_Property(M_JIG_STK, cmSD_MODE, cmTRUE);
	COMI.Set_Motor_IO_Property(M_JIG_STK, cmSD_EN, cmFALSE);    //cmSD_EN=14 //cmFALSE = 0 SD 비활성, cmTRUE = 1 SD 활성 	
	COMI.Set_Motor_IO_Property(M_JIG_STK, cmSD_LOGIC, cmLOGIC_B); //cmSD_LOGIC=15, 0 (cmLOGIC_A) : A접점 방식,1 (cmLOGIC_B) : B접점 방식
	COMI.Set_Motor_IO_Property(M_JIG_STK, cmSD_LATCH, cmFALSE);//16

	COMI.mn_runspeed_rate		= st_handler_info.nRunSpeed;
	COMI.mn_manualspeed_rate	= st_handler_info.nManualSpeed;*/
}


int CPublicFunction::OnMainAirCheck()
{
	if (FAS_IO.get_in_bit(st_io_info.i_MainAirChk, IO_OFF) == IO_OFF)
	{
		CTL_Lib.Alarm_Error_Occurrence(6319, dWARNING, _T("800109"));

		return RET_ERROR;
	}

	return RET_GOOD;
}


int CPublicFunction::OnMainPowerCheck()		//2014.01.21 주석처리
{
	/*if (FAS_IO.get_in_bit(st_io_info.iMainPwrChk, IO_OFF) == IO_ON)
	{
		st_alarm_info.strCode		= _T("900314"); 
		st_alarm_info.nCountMode	= 0;	
		st_alarm_info.nTypeMode		= eWARNING;
		st_alarm_info.nAlarmAssignSection = 87;

		return RET_ERROR;
	}*/

	return RET_GOOD;
}


int CPublicFunction::OnMotorPowerCheck()	//2014.01.21 주석처리
{
/*	if (FAS_IO.get_in_bit(st_io_info.iMc1OnChk, IO_ON) == IO_OFF)
	{
		st_alarm_info.strCode		= _T("900311"); 
		st_alarm_info.nCountMode	= 0;	
		st_alarm_info.nTypeMode		= eWARNING;
		st_alarm_info.nAlarmAssignSection = 88;

		return RET_ERROR;
	}

	if (FAS_IO.get_in_bit(st_io_info.iMc2OnChk, IO_ON) == IO_OFF)
	{
		st_alarm_info.strCode		= _T("900312"); 
		st_alarm_info.nCountMode	= 0;	
		st_alarm_info.nTypeMode		= eWARNING;
		st_alarm_info.nAlarmAssignSection = 88;

		return RET_ERROR;
	}*/

	// jtkim 20150406
	if (FAS_IO.get_in_bit(st_io_info.i_MainMcChk, IO_ON) == IO_OFF)
	{
		CTL_Lib.Alarm_Error_Occurrence(6000, dWARNING, _T("800108"));

		return RET_ERROR;
	}
	return RET_GOOD;
}


void CPublicFunction::OnAxisEncoderReset(int nAxis)
{
	if(st_work_info.nSimulationMode == 1)
	{// 
		return;
	}

	cmmStSetPosition(nAxis, cmCNT_COMM, (double)0);
	cmmStSetPosition(nAxis, cmCNT_FEED, (double)0);
}


void CPublicFunction::OnThreadFunctionStepTrace(int nPos, int nStep)
{
	if (nStep == st_other_info.nPrevStep[nPos])
	{
		return;
	}

	st_other_info.nPrevStep[nPos]			= nStep;
	m_tThreadTime[nPos]						= CTime::GetCurrentTime();
	st_other_info.strLastChangeDate[nPos]	= m_tThreadTime[nPos].Format("%y/%m/%d %H:%M:%S");

	if (st_other_info.strHistoryStep[nPos].GetLength() == 114 ||
		st_other_info.strHistoryStep[nPos].GetLength() == 278)
	{
		m_strThreadStep[nPos].Format(_T("%05d|"), nStep);
		st_other_info.strHistoryStep[nPos] += m_strThreadStep[nPos];
		st_other_info.strHistoryStep[nPos] += "\r\n|                                        |";
	}
	else if (st_other_info.strHistoryStep[nPos].GetLength() == 442)
	{
		m_strThreadStep[nPos].Format(_T("%05d|"), nStep);
		st_other_info.strHistoryStep[nPos] += m_strThreadStep[nPos];
	}
	else if (st_other_info.strHistoryStep[nPos].GetLength() >= 448)
	{
		m_strThreadStep[nPos].Format(_T("%05d,"), nStep);
		st_other_info.strHistoryStep[nPos] = m_strThreadStep[nPos];
	}
	else
	{
		m_strThreadStep[nPos].Format(_T("%05d,"), nStep);
		st_other_info.strHistoryStep[nPos] += m_strThreadStep[nPos];
	}
}


void CPublicFunction::OnLotStartClear()
{

}


CString	CPublicFunction::OnCharToString(char chData[], int nLength)
{
	CString strTmp;
	BSTR	buf;
	int		nCnt;

	nCnt	= MultiByteToWideChar(CP_ACP, 0, chData, nLength, NULL, NULL);
	buf		= SysAllocStringLen(NULL, nCnt);
	MultiByteToWideChar(CP_ACP, 0, chData, nLength, buf, nCnt);
	strTmp.Format(_T("%s"), buf);

	SysFreeString(buf);

	return strTmp;
}


void CPublicFunction::OnStringToChar(CString strData, char chData[])
{
	int nCnt;
	wchar_t *chBuf;

	chBuf = strData.GetBuffer(strData.GetLength());
	nCnt  = WideCharToMultiByte(CP_ACP, 0, chBuf, -1, NULL, 0, NULL, NULL);
	WideCharToMultiByte(CP_ACP, 0, chBuf, -1, chData, nCnt, 0, 0);
}


//2015.02.10
CString CPublicFunction::ThreadID(int nID)
{
	CString strTmp = _T("");

	switch(nID+1)
	{
		case  1:
			strTmp.Format(_T("BarcodeRobot Run"));
			break;

		case 2:
			strTmp.Format(_T("BarcodeRobot BCRReading"));
			break;

		case  3:
			strTmp.Format(_T("CokRobot Run"));
			break;

		case  4:
			strTmp.Format(_T("CokRobot Move"));
			break;

		case  5:
			strTmp.Format(_T("EmptyStacker Run"));
			break;

		case  6:
			strTmp.Format(_T("EmptyStacker Move"));
			break;

		case  7:
			strTmp.Format(_T("LoadRobot Run"));
			break;

		case  8:
			strTmp.Format(_T("LoadRobot Buffer Place"));
			break;

		case  9:
			strTmp.Format(_T("LoadRobot TrayPick"));
			break;

		case  10:
			strTmp.Format(_T("LoadRotatorBuffer Run"));
			break;

		case  11:
			strTmp.Format(_T("LoadTrayConveyor Run"));
			break;

		case  12:
			strTmp.Format(_T("LoadTrayConveyor LdTrayBCR"));
			break;

		case  13:
			strTmp.Format(_T("LoadTrayConveyor LdTrayInput"));
			break;

		case  14:
			strTmp.Format(_T("LoadTrayConveyor Smema"));
			break;

		case  15:
			strTmp.Format(_T("LoadTrayPlate LoadTray_1"));
			break;

		case  16:
			strTmp.Format(_T("LoadTrayPlate LoadTray_2"));
			break;

		case  17:
			strTmp.Format(_T("LoadTrayPlate LoadTray_2_EmtyTray"));
			break;

		case  18:
			strTmp.Format(_T("LoadTrayShifter Run"));
			break;

		case  19:
			strTmp.Format(_T("LoadTrayShifter TrayPick"));
			break;

		case  20:
			strTmp.Format(_T("LoadTrayShifter TrayPlace"));
			break;

		case  21:
			strTmp.Format(_T("LeftMp Run"));
			break;

		case  22:
			strTmp.Format(_T("RejectTray Run"));
			break;

		case  23:
			strTmp.Format(_T("RejectTray Pick"));
			break;

		case  24:
			strTmp.Format(_T("RejectTray Place"));
			break;

		case  25:
			strTmp.Format(_T("RejectTray TrayUp"));
			break;

		case  26:
			strTmp.Format(_T("RejectTray TrayDn"));
			break;

		case  27:
			strTmp.Format(_T("RetestTray Run"));
			break;

		case  28:
			strTmp.Format(_T("RightMp Run"));
			break;

		case  29:
			strTmp.Format(_T("TestSiteRobot Run"));
			break;

		case  30:
			strTmp.Format(_T("TestSiteRobot BufferPick"));
			break;

		case  31:
			strTmp.Format(_T("TestSiteRobot BufferPlace"));
			break;

		case  32:
			strTmp.Format(_T("TestSiteRobot Cok Buff Pick"));
			break;

		case  33:
			strTmp.Format(_T("TestSiteRobot Cok Buff Place"));
			break;

		case  34:
			strTmp.Format(_T("TestSiteRobot CokExchange"));
			break;

		case  35:
			strTmp.Format(_T("TestSiteRobot Cok_TestPick"));
			break;

		case  36:
			strTmp.Format(_T("TestSiteRobot Cok_TestPlace"));
			break;

		case  37:
			strTmp.Format(_T("TestSiteRobot Test Pick"));
			break;

		case  38:
			strTmp.Format(_T("TestSiteRobot Test Place"));
			break;

		case  39:
			strTmp.Format(_T("UldRobot Run"));
			break;

		case  40:
			strTmp.Format(_T("UldRobot Buff Pick"));
			break;

		case  41:
			strTmp.Format(_T("UldRobot TrayPlace"));
			break;

		case  42:
			strTmp.Format(_T("UldRotatorBuffer Run"));
			break;

		case  43:
			strTmp.Format(_T("UldTrayConveyor Run"));
			break;

		case  44:
			strTmp.Format(_T("UldTrayConveyor Smema"));
			break;

		case  45:
			strTmp.Format(_T("UldTrayShifter Run"));
			break;

		case  46:
			strTmp.Format(_T("UldTrayShifter TrayPick"));
			break;

		case  47:
			strTmp.Format(_T("UldTrayShifter TrayPlace"));
			break;

		case  48:
			strTmp.Format(_T("UldTrayStacker Run"));
			break;

		case  49:
			strTmp.Format(_T("UldTrayStacker Move"));
			break;
	}

	return strTmp;
}

BOOL CPublicFunction::IsNum(CString strData)
{
	int nCnt = strData.GetLength();
	int i;
	char cTemp;

	for (i=0; i<nCnt; i++)
	{
		cTemp = (char)strData.GetAt(i);

		if(i==0 && cTemp == '-') continue; 

		if(cTemp >= '0' && cTemp <= '9') continue; 
		else break; 
	}
	if (i==nCnt) return TRUE;
	else return FALSE;
}

int	CPublicFunction::OnIoSafetyCheck(int nIO)
{
//	int nRet[5];


	return RET_GOOD;
}

int CPublicFunction::OnRecoveryReadWrite(int nMode, int nReadWrite)
{
	CFile file;

	CString strFileName;
	CTime time;

	int nArchive;

	if (nMode == 0)
	{
		strFileName = st_path_info.strPathRecovery + _T("Handler.DAT");
	}
	else 
	{
		time = CTime::GetCurrentTime();
		strFileName.Format(_T("%sHandler_%04d%02d%02d%02d%02d.DAT"), st_path_info.strPathRecovery,
																	 time.GetYear(),
																	 time.GetMonth(),
																	 time.GetDay(),
																	 time.GetHour(),
																	 time.GetMinute());
	}

	if (nReadWrite == 0)
	{
		if (!file.Open(strFileName, CFile::modeWrite | CFile::modeCreate))
		{
			return RET_ERROR;
		}
		nArchive = CArchive::store;
	}
	else
	{
		if (!file.Open(strFileName, CFile::modeRead))
		{
			return RET_ERROR;
		}
		nArchive = CArchive::load;
	}

	CArchive ar(&file, nArchive);

	OnSerialize(ar);

	ar.Close();
	file.Close();
	return RET_GOOD;
}

void CPublicFunction::OnLogBarcode(CString strMsg)
{
	CString strFileName;				// 마지막으로 생성된 파일 이름 저장 변수 
	CString strCreateFile;				// 알람 정보 저장할 파일에 대한 [폴더]+[파일명]+[확장자] 설정 변수 
	CString strListName, strTempData;	// 각 부분별 알람 발생 횟수 정보 저장할 로그 파일 정보 저장 변수 
	CString strContent;				// 한 라인에 출력할 문자열 정보 저장 변수 
	//int nExistence;						// 파일 존재 유무 설정 플래그 
//	char chFileName[256];				// 검색할 파일 정보 설정 함수 
	//char chMsg[1000];
//	FILE  *fp ;							// 파일에 대한 포인터 설정 변수 
	
	CString strTitleTime, strFileTime, strNewFile;		// 파일에 출력할 타이틀 시간 저장 변수
	int nCurYear, nCurMonth, nCurDay;					// 년, 월, 일 저장 변수
	int nCurHour, nCurMinute, nCurSecond;				// 년, 월, 일 저장 변수
	int nMtbi = 0;

	//double dAve;
	//double dTemp;
	//
	
	COleDateTime otCurr;									// 현재 시간 저장 변수
	CTime tCurr;										// 타이틀 시간 저장 변수

	CString strTemp;

	CString strData, strTime;
	
	/* ************************************************************************** */
	/* 파일 이름으로 사용할 날짜 설정한다                                         */
	/* ************************************************************************** */
	otCurr = COleDateTime::GetCurrentTime();

	nCurYear		= otCurr.GetYear();  
	nCurMonth		= otCurr.GetMonth();  
	nCurDay			= otCurr.GetDay();  

	nCurHour		= otCurr.GetHour();
	nCurMinute		= otCurr.GetMinute();
	nCurSecond		= otCurr.GetSecond();

// 	strNewFile.Format(_T("BARCODE_DATA%04d%02d%02d"), nCurYear, nCurMonth, nCurDay);
// 	strTime.Format(_T("%04d/%02d/%02d %02d:%02d:%02d"), nCurYear, nCurMonth, nCurDay, nCurHour, nCurMinute, nCurSecond);
// 
// 	strCreateFile = st_path_info.strBarcode + strNewFile;
// 	strCreateFile += ".TXT";
// 
// 	OnStringToChar(strCreateFile, chFileName);
// 	nExistence = _access(chFileName, 0);
// 
// 	if (nExistence == -1)  /* 파일 미존재 */
// 	{
// 		strCreateFile = st_path_info.strBarcode + strNewFile;
// 		strCreateFile += ".TXT";
// 		OnStringToChar(strCreateFile, chFileName);
// 	}
// 
// 	/* ************************************************************************** */
// 	/* 알람 발생 횟수 정보 저장 파일에 추가 가능한 형태 파일로 생성               */
// 	/* ************************************************************************** */
// 	fopen_s(&fp, chFileName, "a+");
// 	if(!fp)
// 	{
// 		//		AfxMessageBox(_T("The failure because we open the file."));
// 		return;
// 	}
// 	/* ************************************************************************** */
// 	strContent += strTime;
// 	strContent += _T(" : ");
// 	strContent += strMsg;
// 	clsFunc.OnStringToChar(strContent, chMsg);
// 	fprintf(fp,"%s\r\n", chMsg) ;
// 
// 	if (ferror(fp))  
// 	{
// 		//		Func.MsgLog("파일 저장 실패!..") ;
// 		fclose(fp); 
// 
// 		return ;
// 	}
// 
// 	fclose(fp); 
}


void CPublicFunction::OnLogBarcodeNg(CString strMsg)
{
	CString strFileName;				// 마지막으로 생성된 파일 이름 저장 변수 
	CString strCreateFile;				// 알람 정보 저장할 파일에 대한 [폴더]+[파일명]+[확장자] 설정 변수 
	CString strListName, strTempData;	// 각 부분별 알람 발생 횟수 정보 저장할 로그 파일 정보 저장 변수 
	CString strContent;				// 한 라인에 출력할 문자열 정보 저장 변수 
	//int nExistence;						// 파일 존재 유무 설정 플래그 
//	char chFileName[256];				// 검색할 파일 정보 설정 함수 
	//char chMsg[1000];
//	FILE  *fp ;							// 파일에 대한 포인터 설정 변수 

	CString strTitleTime, strFileTime, strNewFile;		// 파일에 출력할 타이틀 시간 저장 변수
	int nCurYear, nCurMonth, nCurDay;					// 년, 월, 일 저장 변수
	int nCurHour, nCurMinute, nCurSecond;				// 년, 월, 일 저장 변수
	int nMtbi = 0;

	//double dAve;
	//double dTemp;
	//

	COleDateTime otCurr;									// 현재 시간 저장 변수
	CTime tCurr;										// 타이틀 시간 저장 변수

	CString strTemp;

	CString strData, strTime;

	/* ************************************************************************** */
	/* 파일 이름으로 사용할 날짜 설정한다                                         */
	/* ************************************************************************** */
	otCurr = COleDateTime::GetCurrentTime();

	nCurYear		= otCurr.GetYear();  
	nCurMonth		= otCurr.GetMonth();  
	nCurDay			= otCurr.GetDay();  

	nCurHour		= otCurr.GetHour();
	nCurMinute		= otCurr.GetMinute();
	nCurSecond		= otCurr.GetSecond();

	strNewFile.Format(_T("BARCODE_NG_DATA%04d%02d%02d"), nCurYear, nCurMonth, nCurDay);
	strTime.Format(_T("%04d/%02d/%02d %02d:%02d:%02d"), nCurYear, nCurMonth, nCurDay, nCurHour, nCurMinute, nCurSecond);

// 	strCreateFile = st_path_info.strBarcodeNg + strNewFile;
// 	strCreateFile += ".TXT";
// 
// 	OnStringToChar(strCreateFile, chFileName);
// 	nExistence = _access(chFileName, 0);
// 
// 	if (nExistence == -1)  /* 파일 미존재 */
// 	{
// 		strCreateFile = st_path_info.strBarcodeNg + strNewFile;
// 		strCreateFile += ".TXT";
// 		OnStringToChar(strCreateFile, chFileName);
// 	}
// 
// 	/* ************************************************************************** */
// 	/* 알람 발생 횟수 정보 저장 파일에 추가 가능한 형태 파일로 생성               */
// 	/* ************************************************************************** */
// 	fopen_s(&fp, chFileName, "a+");
// 	if(!fp)
// 	{
// 		//		AfxMessageBox(_T("The failure because we open the file."));
// 		return;
// 	}
// 	/* ************************************************************************** */
// 	strContent += strTime;
// 	strContent += _T(" : ");
// 	strContent += strMsg;
// 	clsFunc.OnStringToChar(strContent, chMsg);
// 	fprintf(fp,"%s\r\n", chMsg) ;
// 
// 	if (ferror(fp))  
// 	{
// 		//		Func.MsgLog("파일 저장 실패!..") ;
// 		fclose(fp); 
// 
// 		return ;
// 	}
// 
// 	fclose(fp); 
}

void CPublicFunction::OnDailyCycleData(CString strLotNo, CString strPartNo, double dTime, CTime tStart, CTime tEnd)
{
	CString strFileName;				// 마지막으로 생성된 파일 이름 저장 변수 
	CString strCreateFile;				// 알람 정보 저장할 파일에 대한 [폴더]+[파일명]+[확장자] 설정 변수 
	CString strListName, strTempData;	// 각 부분별 알람 발생 횟수 정보 저장할 로그 파일 정보 저장 변수 
	CString strContent;				// 한 라인에 출력할 문자열 정보 저장 변수 
//	int nExistence;						// 파일 존재 유무 설정 플래그 
	//char chFileName[256];				// 검색할 파일 정보 설정 함수 
	//char chMsg[1000];
//	FILE  *fp ;							// 파일에 대한 포인터 설정 변수 

	CString strTitleTime, strFileTime;		// 파일에 출력할 타이틀 시간 저장 변수
	int nCurYear, nCurMonth, nCurDay;					// 년, 월, 일 저장 변수
	int nCurHour, nCurMinute, nCurSecond;				// 년, 월, 일 저장 변수
	int nMtbi = 0;

	COleDateTime otCurr;									// 현재 시간 저장 변수
	CTime tCurr;										// 타이틀 시간 저장 변수

	CString strTemp;

	CString strData, strTime;

	/* ************************************************************************** */
	/* 파일 이름으로 사용할 날짜 설정한다                                         */
	/* ************************************************************************** */
	otCurr = COleDateTime::GetCurrentTime();

	nCurYear		= otCurr.GetYear();  
	nCurMonth		= otCurr.GetMonth();  
	nCurDay			= otCurr.GetDay();  

	nCurHour		= otCurr.GetHour();
	nCurMinute		= otCurr.GetMinute();
	nCurSecond		= otCurr.GetSecond();

// 	strTime.Format(_T("D_CYCLE_%04d%02d%02d"), nCurYear, nCurMonth, nCurDay);
// 	strCreateFile = st_path_info.strPathCycle + strTime;
// 	strCreateFile += ".TXT";
// 
// 	OnStringToChar(strCreateFile, chFileName);
// 	nExistence = _access(chFileName, 0);
// 
// 	if (nExistence == -1)  /* 파일 미존재 */
// 	{
// 		strCreateFile = st_path_info.strPathCycle + strTime;
// 		strCreateFile += ".TXT";
// 		OnStringToChar(strCreateFile, chFileName);
// 	}
// 
// 	/* ************************************************************************** */
// 	/* 알람 발생 횟수 정보 저장 파일에 추가 가능한 형태 파일로 생성               */
// 	/* ************************************************************************** */
// 	fopen_s(&fp, chFileName, "a+");
// 	if(!fp)
// 	{
// 		//		AfxMessageBox(_T("The failure because we open the file."));
// 		return;
// 	}
// 	/* ************************************************************************** */
// 
// 	strTemp.Format(_T("[%04d%02d%02d %02d:%02d:%02d] : START : [%04d%02d%02d %02d:%02d:%02d] END :[%04d%02d%02d %02d:%02d:%02d] PARTNO : [%s] LOTNO : [%s] Cycle Time [%.2f]"), nCurYear,
// 																																										        nCurMonth,																																											dTime);
// 	strContent.Format(_T("%s"), strTemp);
// 	OnStringToChar(strContent, chMsg);
// 	fprintf(fp,"%s\r\n", chMsg) ;
// 
// 	if (ferror(fp))  
// 	{
// 		//		Func.MsgLog("파일 저장 실패!..") ;
// 		fclose(fp); 
// 
// 		return ;
// 	}
// 
// 	fclose(fp); 
}




