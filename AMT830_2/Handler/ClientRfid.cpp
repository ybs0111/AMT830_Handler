#include "StdAfx.h"
#include "ClientRfid.h"
#include "Variable.h"
#include "AlgMemory.h"
#include "ClientSocket.h"
#include "CtlBd_Library.h"
#include "Ctlbd_Variable.h"
#include "PublicFunction.h"

CClientRfid clsRfid;

UINT OnClientRfidThread(LPVOID lParam);

CClientRfid::CClientRfid(void)
{
	int nRfid;

// 	nRfid				= RF_CARRIER_ID;
// 	m_nRfidPos[nRfid]	= 0;
// 	m_nRfidNum[nRfid]	= 8;
// 
// 	nRfid				= RF_EQP_ID;
// 	m_nRfidPos[nRfid]	= 8;
// 	m_nRfidNum[nRfid]	= 8;
// 
// 	nRfid				= RF_QTY;
// 	m_nRfidPos[nRfid]	= 16;
// 	m_nRfidNum[nRfid]	= 6;
// 
// 	nRfid				= RF_QTY_T;
// 	m_nRfidPos[nRfid]	= 22;
// 	m_nRfidNum[nRfid]	= 6;
// 
// 	nRfid				= RF_LOT_ID_J;
// 	m_nRfidPos[nRfid]	= 28;
// 	m_nRfidNum[nRfid]	= 12;
// 
// 	nRfid				= RF_STEP;
// 	m_nRfidPos[nRfid]	= 40;
// 	m_nRfidNum[nRfid]	= 6;
// 
// 	nRfid				= RF_LOT_TYPE;
// 	m_nRfidPos[nRfid]	= 46;
// 	m_nRfidNum[nRfid]	= 2;
// 
// 	nRfid				= RF_PART_ID;
// 	m_nRfidPos[nRfid]	= 48;
// 	m_nRfidNum[nRfid]	= 28;
// 	
// 	nRfid				= RF_PKG_CODE;
// 	m_nRfidPos[nRfid]	= 76;
// 	m_nRfidNum[nRfid]	= 3;
// 
// 	nRfid				= RF_NONE_1;
// 	m_nRfidPos[nRfid]	= 79;
// 	m_nRfidNum[nRfid]	= 1;
// 
// 	nRfid				= RF_LOT_ID_M;
// 	m_nRfidPos[nRfid]	= 80;
// 	m_nRfidNum[nRfid]	= 12;
// 
// 	nRfid				= RF_CNT;
// 	m_nRfidPos[nRfid]	= 92;
// 	m_nRfidNum[nRfid]	= 8;
// 
// 	nRfid				= RF_FLAG;
// 	m_nRfidPos[nRfid]	= 100;
// 	m_nRfidNum[nRfid]	= 2;
// 
// 	nRfid				= RF_REJECT;
// 	m_nRfidPos[nRfid]	= 102;
// 	m_nRfidNum[nRfid]	= 2;
// 
// 	nRfid				= RF_BIN;
// 	m_nRfidPos[nRfid]	= 104;
// 	m_nRfidNum[nRfid]	= 2;
// 
// 	nRfid				= RF_NONE_2;
// 	m_nRfidPos[nRfid]	= 106;
// 	m_nRfidNum[nRfid]	= 2;
// 
// 	nRfid				= RF_TRAY_QTY;
// 	m_nRfidPos[nRfid]	= 108;
// 	m_nRfidNum[nRfid]	= 4;
// 
// 	m_nCommStep			= 0;
}


CClientRfid::~CClientRfid(void)
{
	if (m_thrHandle) 
	{
		m_bThread = false;
		while(WaitForSingleObject(m_thrHandle, 5000) != WAIT_OBJECT_0)
		{
			if (m_thrHandle == NULL) break;
			Sleep(0);
		}
	}
}


void CClientRfid::OnCommunication()
{
	switch (m_nCommStep)
	{
		
	}
}

UINT OnClientRfidThread(LPVOID lParam)
{
	CClientRfid *pMsg = (CClientRfid *)lParam;

	CString strTemp;

	while(pMsg->m_bThread)
	{
		pMsg->OnCommunication();
	}

	pMsg->m_thrHandle = NULL;

	return 0;
}

CString	CClientRfid::OnCharToString(char chData[], int nLength)
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

void CClientRfid::OnStringToChar(CString strData, char chData[])
{
	int nCnt;
	wchar_t *chBuf;

	chBuf = strData.GetBuffer(strData.GetLength());
	nCnt  = WideCharToMultiByte(CP_ACP, 0, chBuf, -1, NULL, 0, NULL, NULL);
	WideCharToMultiByte(CP_ACP, 0, chBuf, -1, chData, nCnt, 0, 0);
}

void CClientRfid::OnDataReceive(CString strData)
{

}


int	CClientRfid::OnHexToDecimal(CString strHex)
{
	char chHex[10];
	int val;

	OnStringToChar(strHex, chHex);

	chHex[2] = '\0';
	val = strtoul(chHex, NULL, 16);

	return val;
}


bool	CClientRfid::OnMakeWriteCodeAll(int nChann, CString strCode[20])
{

	return true;
}


bool CClientRfid::OnMakeReadCodeAll(int nChann)
{
// 	int		i;
// 	int		nLength;
// 	int		nSum = 0;
// 	int		nBcc;
// 
// 	CString strRfid = _T("");
// 	CString strMake = _T("");
// 	CString strLength;
// 	CString strTemp;
// 	CString strData;
// 	CString strLog = _T("[HANDLER >> RFID] ");
// 
// 	BYTE	byBuf[100];
// 
// 	m_strData	= _T("");
// 	
// 	if (m_bThread) return false;
// 	
// 	m_bThread	= true;
// 	m_nCommBin	= BD_NONE;
// 
// 	strLength.Format(_T("%02x%02x"), m_nRfidPos[RF_CARRIER_ID],  112);
// 	strMake.Format(_T("%c01%2d%s"), 0x05, 80 + (nChann - 1), strLength);
// 
// 	nLength = strMake.GetLength();
// 	OnStringToChar(strMake, (char*) byBuf);
// 
// 	for(i=0; i<nLength; i++)
// 	{
// 		nSum += byBuf[i];
// 	}
// 
// 	nBcc = (nSum % 256);
// 	strTemp.Format(_T("%x"), nSum);
// 	strTemp.MakeUpper();
// 
// 	nLength = strTemp.GetLength();
// 
// 	strRfid.Format(_T("%s%s"), strMake, strTemp.Mid(nLength - 2, 2));
// 	m_strSendMsg = strRfid;
// 
// 	strLog += strRfid;
// 	clsFunc.OnLogFileAdd(4, strLog);
// 
// 	m_thrHandle = AfxBeginThread(OnClientRfidThread, this);

	return true;
}

bool CClientRfid::OnMakeReadCode(int nCode, int nChann)
{
	int		i;
	int		nLength;
	int		nSum = 0;
	int		nBcc;

	CString strRfid = _T("");
	CString strMake = _T("");
	CString strLength;
	CString strTemp;
	CString strData;
	CString strLog = _T("[HANDLER >> RFID] ");

	BYTE	byBuf[100];

	m_strData	= _T("");

	if (m_bThread) return false;

	m_bThread	= true;
	m_nCommBin	= BD_NONE;

	strLength.Format(_T("%02x%02x"), m_nRfidPos[nCode], m_nRfidNum[nCode]);
	strMake.Format(_T("%c01%2d%s"), 0x05, 80 + (nChann - 1), strLength);

	nLength = strMake.GetLength();
	OnStringToChar(strMake, (char*) byBuf);

	for(i=0; i<nLength; i++)
	{
		nSum += byBuf[i];
	}

	nBcc = (nSum % 256);
	strTemp.Format(_T("%x"), nSum);
	strTemp.MakeUpper();

	nLength = strTemp.GetLength();

	strRfid.Format(_T("%s%s"), strMake, strTemp.Mid(nLength - 2, 2));
	m_strSendMsg = strRfid;

	strLog += strRfid;
	clsFunc.OnLogFileAdd(4, strLog);

	m_thrHandle = AfxBeginThread(OnClientRfidThread, this);

	return true;
}


bool CClientRfid::OnMakeWriteCode(int nCode, int nChann, CString strCode)
{
	int		i;
	int		nLength;
	int		nSum = 0;
	int		nBcc;

	CString strRfid = _T("");
	CString strMake = _T("");
	CString strLength;
	CString strTemp;
	CString strData;
	CString strLog = _T("[HANDLER >> RFID]");

	BYTE	byBuf[1024];

	m_strData	= _T("");
	
	if (m_bThread) return false;
	
	m_bThread	= true;
	m_nCommBin	= BD_NONE;

	strLength.Format(_T("%02x%02x"), m_nRfidPos[nCode], m_nRfidNum[nCode]);
	strMake.Format(_T("%c01%d%s"), 0x05, 90 + (nChann - 1), strLength);

	if(strCode.GetLength() > m_nRfidNum[nCode])
	{
		strData = strCode.Mid(0, m_nRfidNum[nCode]);
	}
	else
	{
		strData = strCode;
	}
	strTemp.Format(_T("%-8s"), strData);
	OnStringToChar(strTemp, (char*) byBuf);

	for(i=0; i<m_nRfidNum[nCode]; i++)
	{
		strTemp.Format(_T("%x"), byBuf[i]);
		strMake += strTemp;
	}
	
	nLength = strMake.GetLength();
	OnStringToChar(strMake, (char*) byBuf);

	for(i=0; i<nLength; i++)
	{
		nSum += byBuf[i];
	}

	nBcc = (nSum % 256);
	strTemp.Format(_T("%x"), nBcc);
	strTemp.MakeUpper();
	nLength = strTemp.GetLength();

	strRfid.Format(_T("%s%s"), strMake, strTemp.Mid(nLength - 2, 2));
	m_strSendMsg = strRfid;

	strLog += strRfid;
	clsFunc.OnLogFileAdd(4, strLog);

	m_thrHandle = AfxBeginThread(OnClientRfidThread, this);

	return true;
}
