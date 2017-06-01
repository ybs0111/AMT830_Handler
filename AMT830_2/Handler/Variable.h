#include <afxtempl.h>

#ifndef _VARIABLE_h__
#define _VARIABLE_h__

#include "Alg_Mysql.h"

// amt8562
//	Console application ���α׷��� ���ؼ� �Ʒ� �κ��� ������
typedef unsigned long int				DWORD;
typedef unsigned short int				WORD;
typedef unsigned char					BYTE;
typedef int								BOOL;
typedef void							*HANDLE;

#ifndef PASCAL
#define PASCAL						__stdcall
#endif	// PASCAL

// jtkim 20130520
/*
#ifndef EXPORT
//#define EXPORT
#endif	// EXPORT
*/
//typedef int							BOOL;			// 0(FALSE), 1(TRUE)
typedef signed char						INT8;			// -128 .. 127
typedef unsigned char					UINT8;			// 0 .. 255
typedef signed short int				INT16;			// -32768 .. 32767
typedef unsigned short int				UINT16;			// 0 .. 65535
typedef int								INT32;			// -2,147,483,648 .. 2,147,483,647
typedef unsigned int					UINT32;			// 0 .. 4,294,967,295

// *****************************************************************************
// ����� ���� �޽��� ID ����                                                   
// *****************************************************************************
#define WM_FORM_CHANGE			WM_USER+200   // ȭ���� ��ȯ�� �� �ش� ��ȯ ���� ������ �����ϱ� ���� ����� ���� �޽��� 

#define WM_STATUS_CHANGE		WM_USER+201   // Ÿ��Ʋ �� ȭ������ ���۵� �޽��� ��½�Ű�� ���� ����� ���� �޽��� �߰� 

#define WM_LIST_DATA			WM_USER + 6   // ��� �޽��� ��� ����Ʈ ��ȭ ���ڿ� 
                                              // �ø��� ��Ʈ�� ���� ��/���ŵ� �޽����� ����ϱ� ���� ����� ���� �޽��� 
#define WM_DATA_SEND			WM_USER + 7   // Data�� �����ϱ� ���� ȭ�鿡�� ������ �����ϱ� ���� ������ ����� ���� �Լ�

#define WM_WORK_END				WM_USER + 8   // �׽�Ʈ �۾� �Ϸ� �� ������ ���� ȭ�鿡 ��½�Ű�� ���� ����� ���� �޽��� �߰� 

#define WM_BASIC_APPLY			WM_USER + 10  // BASIC DATA�� APPLY ��Ű�� ���� ����� ���� �޽��� �߰� 

#define WM_MAINTENANCE_APPLY	WM_USER + 11  // Maintenance DATA�� APPLY ��Ű�� ���� ����� ���� �޽��� �߰�
#define WM_INTERFACE_APPLY		WM_USER + 13
#define	WM_WAITTIME_APPLY		WM_USER + 15  // Wait Time DATA�� APPLY ��Ű�� ���� ����� ���� �޽��� �߰� 

#define	WM_MODULESITE_APPLY		WM_USER + 16
#define	WM_HEATSINKSITE_APPLY	WM_USER + 17
#define	WM_MODULEROBOT_APPLY	WM_USER + 18
#define	WM_HEATSINKROBOT_APPLY	WM_USER + 19
#define	WM_DISPENSER_APPLY		WM_USER + 20
#define	WM_MOTORSPEED_APPLY		WM_USER + 21
#define WM_SERIAL_PORT			WM_USER + 25
#define	WM_TESTREFERENCE_MANUAL		WM_USER + 21

#define	WM_LOTOPEN_APPLY		WM_USER + 26
#define	WM_LOTSTART_APPLY		WM_USER + 27

#define WM_DATA_INIT_SAVE       WM_USER + 300 // apply��ư�� �������, �ش� ȭ���� ������ ����(Init)
#define WM_DATA_CHANGE          WM_USER + 301 // apply��ư�� �������, �ش� ȭ���� ������ ����(Init)

#define WM_WORK_DISPLAY			WM_USER + 400
#define WM_WORK_COMMAND			WM_USER + 401

#define WM_CLIENT_MSG			WM_USER + 500
#define WM_CLIENT_MSG_1			WM_USER + 500
#define WM_CLIENT_MSG_2			WM_USER + 501
#define WM_CLIENT_MSG_3			WM_USER + 502
#define WM_CLIENT_MSG_4			WM_USER + 503
#define WM_CLIENT_MSG_5			WM_USER + 504
#define WM_CLIENT_MSG_6			WM_USER + 505
#define WM_CLIENT_MSG_7			WM_USER + 506
#define WM_CLIENT_MSG_8			WM_USER + 507
#define WM_CLIENT_MSG_9			WM_USER + 508
#define WM_CLIENT_MSG_10		WM_USER + 509

#define WM_SERVER_MSG			WM_USER + 550
#define WM_SERVER_MSG_1			WM_USER + 550
#define WM_SERVER_MSG_2			WM_USER + 551
#define WM_SERVER_MSG_3			WM_USER + 552
#define WM_SERVER_MSG_4			WM_USER + 553
#define WM_SERVER_MSG_5			WM_USER + 554
#define WM_SERVER_MSG_6			WM_USER + 555
#define WM_SERVER_MSG_7			WM_USER + 556
#define WM_SERVER_MSG_8			WM_USER + 557
#define WM_SERVER_MSG_9			WM_USER + 558
#define WM_SERVER_MSG_10		WM_USER + 559

#define WM_GMS_MSG				WM_USER + 600

#define CLIENT_CONNECT			0
#define CLIENT_CLOSE			1
#define CLIENT_SEND				2
#define CLIENT_REV				3
#define CLIENT_ACCEPT			4

#define SERVER_CONNECT			0
#define SERVER_CLOSE			1
#define SERVER_SEND				2
#define SERVER_REV				3
#define SERVER_ACCEPT			4

#define INITIAL_INDEX_DUMP		0	
#define INITIAL_TEST_DUMP		1
#define INITIAL_INDEX_TABLE		2
// *****************************************************************************

// *****************************************************************************
//  ��Ʈ�� �޼��� ���� ����ʿ��� BPC�� ������ �޼���.
// *****************************************************************************
#define NW_LOT_START_RPY				1
#define NW_LOT_CANCEL_RPY				2

// *****************************************************************************
//  List Box ��¿� �޼��� ����                                                 
// *****************************************************************************
#define RECEIVE_MSG			1
#define SEND_MSG			2
#define NORMAL_MSG			3
#define ABNORMAL_MSG		4
#define MACHINE_INFO		5
#define DEVICE_INFO			6

// *****************************************************************************
// *****************************************************************************
//  SCREEN_MAIN ��¿� �޼��� ����                                                
// *****************************************************************************
#define MAIN_TIMEINFO				100
#define MAIN_COUNT_DISPLAY			101

#define MAIN_BD_ERR_CREATE_MSG		400
#define MAIN_BD_ERR_DELETE_MSG		401

#define MAIN_MESSAGE_BOX_CREATE_REQ	100
#define MAIN_MESSAGE_BOX_DELETE_REQ	101

#define MAIN_BARCODE_BOX_CREATE_REQ	110
#define MAIN_BARCODE_BOX_DELETE_REQ	111


#define MAIN_LOT_HISTORY_CREATE_REQ 600
#define MAIN_LOT_HISTORY_DELETE_REQ 601


#define MAIN_NOTICE_CREATE_REQ		800
#define MAIN_NOTICE_DELETE_REQ		801

#define MOTOR_IO_CREATE_REQ			900
#define MOTOR_IO_DELETE_REQ			901

#define MAIN_MESSAGE_VIEW_CREATE_REQ 1000
#define MAIN_MESSAGE_VIEW_DELETE_REQ 1001

#define ALARM_IO_CREATE_REQ 100
#define ALARM_IO_DELETE_REQ 101
#define ALARM_MOTOR_CREATE_REQ 200
#define ALARM_MOTOR_DELETE_REQ 201

#define INIT_RECOVERY_COMMAND		0
#define INIT_INITIALIZE_COMMAND		1

// *****************************************************************************
//  Title Bar ��¿� �޼��� ����                                                
// *****************************************************************************
#define FORM_NAME			1
#define MACHINE_STATUS		2
#define DEVICE_MODE			3
#define INTERFACE_MODE		4
#define LEVEL_MODE			5
#define FILE_MODE			6
#define MODEL_MODE			7
#define COMMUNICATION_MODE	8
#define XGEM_MODE			9
// *****************************************************************************

// *****************************************************************************
// ��� ���� ���� �� �ʿ��� �޽��� ����                                         
// *****************************************************************************
#define TIMECOUNT			5
#define ELEVATOR_STRATUMS	6
// *****************************************************************************

// *************************************************************************
// ��� ���� ���� �� �ʿ��� �޽��� ����                                          
// *************************************************************************
#define dSTOP				0
#define dRUN				1
#define dIDLE				2
#define dJAM				3
#define dLOTEND				4
#define dINIT				5
#define dWARNING			6
#define dLOCK				7
#define dSELFCHECK			8
#define dMAINT				9
#define dREINSTATE			10	//���͵�����
#define dRECOVERY			11
#define dMOTOR_WARNING		12 //�̶��� �˶��� �߻���Ű�� �ʴ´�(run status�� �ٲ��� �ʴ´�).thread ������ �Ǵ��Ͽ� �˶� �߻���Ų�� 

#define eWARNING			0
#define eRUNNING			1
#define eSTOP				2
#define eERROR				3

#define IO_CLEAR			-1
#define NO					0
#define YES					1
#define COVER_YES			2
#define READY				2
#define PROCEED				3

#define IO_ON				1
#define IO_OFF				0
#define IO_ERROR			2
#define IO_CHK_ERROR		4

#define IO_NONE				0
#define IO_IN				1
#define IO_OUT				2

#define IO_CLAMP			1
#define IO_UNCLAMP			0

#define IO_HOLD				0
#define IO_RELEASE			1

#define IO_DOWN				1
#define IO_UP				0

#define IO_PROCEED			2
#define IO_TIMEOUT			3

#define IO_LEFT				0
#define IO_RIGHT			1

#define IO_CLOSE			0
#define IO_OPEN				1

#define IO_GOOD				10
#define IO_FAIL				11

#define FUN_ING				0
#define FUN_END				1
#define FUN_ERR				2
#define FUN_CTU				3

#define PICKER				0
#define FINGER				1

#define TIMECOUNT			5
#define ELEVATOR_STRATUMS	6
// *************************************************************************

// *************************************************************************
// RS-232C �ø��� ��� �� ���Ǵ� �޽��� ����                                   
// -> MAX_PORT : �⺻ ��Ʈ 2���� �����Ǿ� �ִ�						             
// *************************************************************************
#define MAX_PORT				2	// ������ �ø��� ��Ʈ ����
#define COM_ERROR				-1	// ���� �޽���
#define CRI_BARCODE_PORT		0		// ���� BCR READ ��Ʈ ��ȣ
#define MPCB_BARCODE_PORT		1		// ���� BCR READ ��Ʈ ��ȣ
#define LIGHT_PORT				2
#define A_LIGHT_PORT			3

#define COM_PORT			0
#define COM_BAUDRATE		1
#define COM_DATA			2
#define COM_STOP			3
#define COM_PARITY			4

//#define TESTER_PORT	2		// ���� Tester Communication ��Ʈ ��ȣ
//#define COM_PORT   2	// ���� ��� ���� �ø��� ��Ʈ ��ȣ
 
#define BUF_SIZE  1000	// ���� ũ��
// *************************************************************************

// *************************************************************************
// *************************************************************************
// I/O ��� ���� �� ��Ʈ �ִ� ���� �����Ѵ�                                      
// *************************************************************************
#define MAX_IO				1315

#define MAX_MASTER_IO		1
#define MAX_PORT_IO			4
#define MAX_SLAVE_IO		8
// *************************************************************************
#define M_BARCODE_PORT		0
#define C_BARCODE_PORT		1
// *************************************************************************
//  MOTOR ���� ���� ���� �����Ѵ�                                                
// *************************************************************************
#define MOT_GOOD			1
#define MOT_PROGRESS		2
#define MOT_RETRY			3
#define MOT_ERROR			4

#define PLUS				1
#define MINUS				0
#define RUN_MODE			1
#define MANUAL_MODE			2

#define POWER_OFF			0
#define POWER_ON			1

#define ELM					0
#define ELP					1
#define HOME				2

#define MOT_ACC				0
#define MOT_DEC				1
#define MOT_JOG				2
#define MOT_ORG				3
#define MOT_FEEDRATE		4
#define MOT_INTERACC		5
#define MOT_ORGMETHOD		6
#define MOT_ORGACCDEC		7

#define MOT_FAST			10
#define MOT_SLOW			20
#define TSITE_SOCKET_CNT	48
// *************************************************************************

// *****************************************************************************
//  Main Screen ��¿� �޼��� ����                                              
// *****************************************************************************

// *****************************************************************************
///// test bin  result
#define BIN_NOTUESD			0

#define BUTTON_MOUSE_DN		1100
#define BUTTON_MOUSE_UP		1000

// GRID TYPE
#define DFC_NOUSE       -1//�����ý��� �׸��� �����(0���÷��� ������� ����Ҷ� �̿��ϸ��)
#define DFC_STATIC       0
#define DFC_EDIT         1
#define DFC_COMBO        2
#define DFC_CHECK        3
#define DFC_DATE         4
#define DFC_TIME         5
#define DFC_PROGRESS     6
#define DFC_IMAGE        7

#define IMG_LISTHDCTRL_BG _T("���2.jpg")//_T("smflower.jpg")
#define IMG_PICCTRL_BG _T("���2.jpg") //_T("smflower.jpg")
#define IMG_LISTHDCTRL_BG1 _T("���25.gif")//_T("smflower.jpg")
#define IMG_PICCTRL_BG1 _T("���25.gif") //_T("smflower.jpg")

// Į�� ����
#define SKY_C					RGB(187, 250, 255)
#define NOR_C					RGB(164, 164, 164)
#define NOR_L					RGB(190, 190, 190)
#define RED_C					RGB(255, 0, 0)
#define RED_L					RGB(255, 150, 150)
#define RED_D					RGB(80, 20, 0)
#define BLUE_C					RGB(0, 0, 255)
#define WHITE_C					RGB(255, 255, 255)
#define BLACK_C					RGB(25, 1, 1)
#define BLACK_L					RGB(62, 55, 55)
#define GRAY					RGB(90, 80, 80)
#define YELLOW_C				RGB(255,255,0)
#define YELLOW_D				RGB(128, 128, 0)
#define YELLOW_L				RGB(255, 255, 193)
#define GREEN_C					RGB(0,255,0)
#define GREEN_L					RGB(150,255,150)
#define GREEN_D					RGB(0,100,20)
#define DSERBLE_BC				RGB(210,210,230)
#define TEXT_BC					RGB(220,230,210)
#define OK_BC					RGB(0, 0, 255)
#define NG_BC					RGB(255, 0, 0)
#define RESULT_BC				RGB(40, 1, 1)
#define ORANGE_C				RGB(0xFF, 0x68, 0x20)
#define BLACK					RGB(0, 0, 0)
#define BLUE_D					RGB(0, 0, 128)
#define BLUE				    RGB(0, 0, 255)
#define PINK					RGB(255, 125, 225)
#define TEXT_BC_1				RGB(240, 240, 240210)
#define BLUE_L					RGB(124, 139, 252)
#define ON_C					RGB(0, 255, 0)
#define OFF_C					RGB(0, 150, 0)
#define NG_C					0x0000FF
#define OK_C					0xFF00
#define BLACK_GC				0x00
#define YELLOW_GC				0xFFFF
#define TEST_BC					RGB(194, 231, 150)
#define IN_BC					RGB(204, 153, 255)

#define DVC_READY_C				RGB(153, 153, 255)
#define DVC_LOAD_C				RGB(239, 214, 198)
#define DVC_NOVIDEO_C			RGB(0,100,20)
#define DVC_PGM_C				RGB(255, 255, 0)
#define DVC_UNLOAD_C			RGB(255, 255, 204)
#define DVC_NONE_C				RGB(150, 150, 150)
#define DVC_START_C				RGB(150, 255, 150)
#define DVC_NO_C				RGB(128, 128, 0)

#define THICKNESS_FAIL			RGB(255,255,0)
#define LENGTH_FAIL				RGB(0xFF, 0x68, 0x20)
#define BARCODE_FAIL			RGB(255, 0, 0)

#define WINDOW_DN				RGB(219, 255, 210)
#define WINDOW_UP				RGB(250, 255, 244)

#define WINDOW_DN1				RGB(219, 255, 210)
#define WINDOW_UP1				RGB(250, 250, 250)

#define BLUE_L					RGB(124, 139, 252)
#define BLACK_GC				0x00
#define YELLOW_GC				0xFFFF
#define PINK_D					RGB(252, 233, 218)
#define COL_PUPLE				RGB(204,102,204)

// board ���� ����
#define BIN_OFF					RGB(164, 164, 164)
#define BIN_NONE				RGB(62,	55, 55)
#define BIN_LOAD				RGB(187, 250, 255)
#define BIN_READY				RGB(150, 255, 150)
#define BIN_START				RGB(255, 255, 0)
#define BIN_ABORT				RGB(204, 102, 204)
#define BIN_GOOD				RGB(124, 139, 252)
#define BIN_FAIL				RGB(255, 0, 0)
#define BIN_RELOAD				RGB(255, 150, 150)

#define NORMAL_MODE				0
#define THRESHOLD_MODE			1

#define HOMING					1
#define MOVING					2
#define MULTI_MOVING			3
#define POS_MOVING				4

#define RET_ERROR				-1
#define RET_READY				0
#define RET_PROCEED				1
#define RET_GOOD				2
#define RET_RETRY				3
#define RET_SAFETY				4
#define RET_ABORT				5
#define RET_SKIP				6
#define RET_RACKSKIP			7

#define RET_PICKER_NOT_FIND		100  //��Ŀ�� ���̻� �۾��� ������ ������ 
#define RET_TRAY_NOT_FIND		200  //Ʈ���̿� ���̻� �۾��� ������ ������ 

/* ***************************************************************************** */
/* ȭ�� �� Ŭ���� ID ���� �κ�                                                   */
/* ***************************************************************************** */
#define IDW_SCREEN_MAIN					101
#define IDW_SCREEN_INIT					102

#define IDW_SCREEN_BASIC		 		201

#define IDW_SCREEN_WORK_INFO			301
#define IDW_SCREEN_SET_MAINTENANCE		302
#define IDW_SCREEN_SET_INTERFACE		303
#define IDW_SCREEN_SET_MEASURE			304
#define IDW_SCREEN_SET_RECIPE			305
#define IDW_SCREEN_SET_RFID				306
#define IDW_SCREEN_SET_FTP				307
#define IDW_SCREEN_SET_PART_NO			309
#define IDW_SCREEN_IO_FUNCTION			310

#define IDW_SCREEN_WAIT_TIME			401

#define IDW_SCREEN_MOTOR				501
#define IDW_SCREEN_MOTOR_SPEED			502

#define IDW_SCREEN_LIST					601
#define IDW_SCREEN_LIST_WORK			602
#define IDW_SCREEN_LIST_ALARM			603
#define IDW_SCREEN_LIST_STEP			605
#define IDW_SCREEN_LIST_ERROR			606
#define IDW_SCREEN_LIST_DATA_VIEW		607

#define IDW_SCREEN_IO_MAP				701

#define IDW_SCREEN_LOCK					801

#define IDW_SCREEN_ALARM				901

#define IDW_SCREEN_PGM_INFO				1001

#define SCREEN_MAIN						0
#define SCREEN_INITIAL					1
#define SCREEN_BASIC					2
#define SCREEN_SETTING					3
#define SCREEN_MOTOR					4
#define SCREEN_IO						5
#define SCREEN_LIST						6
#define SCREEN_ALARM					7
#define SCREEN_LOCK						8

#define L_BUTTON_DOWN					0
#define L_BUTTON_UP						1

#define MACHINE_MANUAL					0
#define MACHINE_AUTO					1

#define LOT_CLEAR						0 //2015.0303 james -1
#define LOT_START						1
#define LOT_END_START					2
#define LOT_END							3

#define HOST_WAIT						0
#define HOST_STOP						1
#define HOST_RUN						2

#define MAXMOTOR						29

//kwlee 2017.0525
#define MAX_PICKER                       2 
#define MAX_BUFFER_SITE                  4
#define MAX_WORK_SITE                    9
#define MAX_WORK_JOB                     10

//kwlee 2017.0529
#define WORK_BUFFER_1				0
#define WORK_BUFFER_2				1
#define WORK_BUFFER_3				2
#define WORK_BUFFER_4				3

#define STACKER_READY_POS			4
#define STACKER_WORK_POS			5
#define MAX_STACKER_POS             2

#define READY_STACKER_UPDN          0
#define READY_RAIL_FWDBWD           1
#define READY_TRAYCLAMP_ONOFF       2
#define READY_PUSHER_ONOFF          3
#define WORK_STACKER_UPDN           4
#define WORK_RAIL_FWDBWD            5
#define WORK_TRAY_CLAMP_ONOFF       6
#define WORK_TRAY_SEPERATE_ONOFF     7

struct tagHANDLER_INFO
{
	CBitmap m_TitleBackBitmap;
	CBitmap m_BackBitmap;
	CBitmap m_BackDlgBitmap;

	BOOL bProgramExit;				//���α׷��� ���������°��� Ȯ���Ѵ�.
	// **************************************************************************
	// LOT ó�� ���� �÷��� ���� ��� ����                                       
	// **************************************************************************
	bool bLoaderOnFlag;				// �δ� On : True    �δ� Off : False
	bool bAllLotStartFlag;			// LOT ó�� ���� �� ���� ��
	// **************************************************************************

	int nMenuNum;					// �� ȭ�鿡 ������ ȭ�� ��ȣ ���� ���� 
	int nAlarmScreen;				// ���� �˶� ȭ���� ��µǾ��� �ִ����� ���� ���� ���� ���� 
	int nLoadState;					// ���� �ε� ��ư ���� ��ȭ ���� ��� ���� �÷��� ���� ���� 
	int nRetestRequest;				// ���� ����� ���׽�Ʈ �ϴ°��� �����.
	// *************************************************************************
	// ���� ��ġ ���� ��� ��� �� ���Ǵ� ���� ����                           
	// *************************************************************************
	int nHomingRequest[MAXMOTOR];	// ���� Home Check ��û �÷��� ���� ���� 
	int nMenuLock;					// �޴� ��� ���� ���� �÷��� 
	int nSystemLock;				// SYSTEM LOCK ���� �÷���
	int nSwitchLock;				// Dialog�� �� �ִ� ���� �÷��� (Start Switch Lock)	
	int nMaintMode;					// ����Ʈ ��� ���� �÷���
	int nLevelMaint;				// ����Ʈ ����(Level 1) ���� �÷���
	int nLevelTeach;				// ƼĪ ����(Level 2) ���� �÷���
	int nLevelAdmin;				// ������ ����(Level 3) ���� �÷���
	int nLevelSpeed;
	int nIoBoardInitial;			// IO ���� �ʱ�ȭ �۾� �Ϸ� �÷���
	int nMotorBoardInitial;			// ��� ���� �ʱ�ȭ �۾� �Ϸ� �÷���
	int nMatroxBoardInitial;		// matrox �ʱ�ȭ
	int nIsAllSiteInitEnd;			// ���� �ʱ�ȭ �۾� �Ϸ� Ȯ�� �÷���
	int nRunStatus;
	int nIdleStatus;
	int nManualSpeed;
	int nRunSpeed;
	int nMachineMode;
	int nLotStatus;					// Lot start ��������....
	int	nInitRetry;					// initialize retry �۾� ����.......
	int nInitialSuccess;			// Initialize �۾� ��������.......	
	int nFtpVer;

	double dCurrCmdPos[MAXMOTOR];	// ���� ���� ��ġ ���� ���� ���� 
	// *************************************************************************
	COleDateTime tUph;
	// *************************************************************************
	// ȭ�鿡 ���� �ڵ� ���� ���� ���� ����                                     
	// *************************************************************************
	HWND hWnd;						// ���� ������ �ڵ� ���� ����

	CWnd *cWndMain;					// ���� ȭ�� �ڵ� ���� ����
	CWnd *cWndBasic;				// BASIC ȭ�� �ڵ� ���� ����
	CWnd *cWndInitial;
	CWnd *cWndMaintenance;			// Maintenance ȭ�� �ڵ� ���� ����	
	CWnd *cWndWaitTime;				// Wait Time ȭ�� �ڵ� ���� ����
	CWnd *cWndMotorSpeed;			// Motor Speed ȭ�� �ڵ� ���� ����
	CWnd *cWndIO;					// IO ȭ�� �ڵ� ���� ����
	CWnd *cWndMotor;
	CWnd *cWndTitle;				// Ÿ��Ʋ ��� ȭ�� �ڵ� ���� ����
	CWnd *cWndList;					// ����Ʈ ��� ȭ�� �ڵ� ���� ����
	CWnd *cWndAlarm;
	CWnd *cWndLock;
	CWnd *cWndWork;
	CWnd *cWndFtp;
	// *************************************************************************

	CString	strUserId;
	
	CTime		tRef;
	
	CTimeSpan	tRun;				// Run Time
	CTimeSpan	tJam;				// Jam Time
	CTimeSpan	tStop;				// Stop Time
	CTimeSpan	tMaint;				// Maint Time
	CTimeSpan	tDRun;				// Run Time
	CTimeSpan	tDJam;				// Jam Time
	CTimeSpan	tDStop;				// Stop Time
	CTimeSpan	tDMaint;			// Maint Time
	CTimeSpan	tWork[20][2];		// Work Time
	// jtkim 20150529
	CTimeSpan	tRunUph;
	CString		strHourUph;


};
extern  tagHANDLER_INFO  st_handler_info;
// *****************************************************************************
// *************************************************************************
// RS-232C �ø��� ��� ���� ���� ����ü ����                                     
// *************************************************************************
struct tagSERIAL_INFO
{
	int	nConnect[MAX_PORT];
	int nSndChk[MAX_PORT];				// �޽��� �۽� �Ϸ� �÷���
	int nRecChk[MAX_PORT];				// �޽��� ���� �Ϸ� �÷���
	
	CString strPortChk[MAX_PORT];		// �ø��� ��Ʈ ���� ���� ���� ����

	CString strSnd[MAX_PORT];			// �۽� �޽��� ���� ����
	CString strRec[MAX_PORT];			// ���� �޽��� ���� ����

	CString strCommSnd[MAX_PORT];		// ����Ʈ ȭ�� ��� �۽� �޽��� ���� ����
	CString strCommRec[MAX_PORT];		// ����Ʈ ȭ�� ��� ���� �޽��� ���� ����
	CString strCommErr[MAX_PORT];		// ����Ʈ ȭ�� ��� ���� �޽��� ���� ����

	int nSerialPort[10];
	int nSerialBaudrate[10];
	int nSerialData[10];
	int nSerialParity[10];
	int nSerialStop[10];
};
extern  tagSERIAL_INFO  st_serial_info;
// *************************************************************************

#define _MAX_ALARM_CNT		2000

// *************************************************************************
// �߻��� �˶� ���� ������ ���� ����ü ����                                      
// *************************************************************************
struct tagALARM_INFO
{
	// **************************************************************************
	// �˶� ���� ǥ�� ��ũ [��� ��ġ], [ũ��], [Į��] ���� ����                 
	// **************************************************************************
	int nOffset;
	int nCy;
	int nCx;
	int nLineWidth;
	int nR;
	int nG;
	int nB;
	// **************************************************************************

	// **************************************************************************
	// ���Ͽ� ����� �˶� ���� ���� ����                                         
	// **************************************************************************
	CString strEContent[_MAX_ALARM_CNT];  // ���Ͽ��� �ε��� �� ���� ���� ���� ����
	CString strECode[_MAX_ALARM_CNT];     // �˶� �ڵ� ���� ����
	CString strEState[_MAX_ALARM_CNT];    // �˶� ���� ���� ����
	CString strEPart[_MAX_ALARM_CNT];     // �˶� �߻� ���� ���� ����
	CString strEMsg[_MAX_ALARM_CNT];      // ���� ���� �˶� �޽��� ���� ����
	// **************************************************************************

	// **************************************************************************
	// ȭ�鿡 ����� �˶� ���� ���� ����                                         
	// **************************************************************************
	int nActionCnt;            // ����� �˶� ��ġ ���� ���� ���� ����
	CString strStyle;           // �˶� ��� ���� ���� ����
	CString strBmpFile;        // �˶� ǥ�� �׸� ���� ���� ����
	CString strRepairMsg;      // �˶� ��ġ ���� ���� ����
	// **************************************************************************

	CStringList strListJam;		// �߻��� Jam Code�� ����Ʈ
	CString strCode;			// �߻��� �˶� �ڵ� ���� ����
	CString strPcode;			// �߻��� �˶� �ڵ� ���� ����
	CString strCurrMsg;
	CString strCurPart;
	CString strContent;

	int nCountMode;				// �˶� ī��Ʈ �÷��� (0:�˶� ī��Ʈ ������    1:�˶� ī��Ʈ ����)
	int nTypeMode;				// �˶� ���� ���� ���� (0:���    1:���༺    2:��� ����)

	long stl_cur_alarm_time;	// �˶� �߻� �ð� ���� ����
	int stl_prev_code;			// �ٷ� �� �߻��� �˶� �ڵ� ���� ����
	long stl_prev_alarm_time;	// �ٷ� �� �߻��� �˶� �߻� �ð� ���� ����

	int nAlarmOccured;			// �˶� �߻� Ƚ�� ���� ����
	int nAlarmOccuredDay;		// �˶� �߻� Ƚ�� ���� ����
	int nArmLotContinue;		// LOT ��� ���� �÷���
	int nResetStatus;			// Alarm Reset Status
	int nSkipMode;
	int nMotorAlarm;			// MOTOR���� �˶��� �ѹ��� �߻��ϵ��� �ϱ� ����!!  --> run�õ������� �ٽ� �︮�� ����!
	int nAlarmAssignSection;	//�˶��� �߻��� ���� ���ݴ� ���� ã�� ����
	int nCurState;
	int nAlarmClear;
	int nAlarmNum;

	int nAlarmCountClear;			// alarm ���� clear
};	
extern  tagALARM_INFO  st_alarm_info;
// *************************************************************************

// *************************************************************************
// �˶� ������ ���� ����ü ����                                                  
// *************************************************************************
struct tagALARM_DISPLAY_INFO
{
	// **************************************************************************
	// �˶� ���� ǥ�� ��ũ [��� ��ġ], [ũ��], [Į��] ���� ����                 
	// **************************************************************************
	int nOffset;
	int nCy;
	int nCx;
	int nLineWidth;
	int nR;
	int nG;
	int nB;
	// **************************************************************************

	// **************************************************************************
	// ȭ�鿡 ����� �˶� ���� ���� ����                                         
	// **************************************************************************
	int nActionCnt;            // ����� �˶� ��ġ ���� ���� ���� ����
	CString strStyle;           // �˶� ��� ���� ���� ����
	CString strBmpFile;        // �˶� ǥ�� �׸� ���� ���� ����
	CString strRepairMsg;      // �˶� ��ġ ���� ���� ����
	// **************************************************************************

	// **************************************************************************
	// ���Ͽ� ����� �˶� ���� ���� ����                                         
	// **************************************************************************
	CString strContent[2000];  // ���Ͽ��� �ε��� �� ���� ���� ���� ����
	CString strCode[2000];     // �˶� �ڵ� ���� ����
	CString strState[2000];    // �˶� ���� ���� ����
	CString strPart[2000];     // �˶� �߻� ���� ���� ����
	CString strMsg[2000];      // ���� ���� �˶� �޽��� ���� ����
	// **************************************************************************

	// **************************************************************************
	// ���� �߻��� �˶� ���� ����                                                
	// **************************************************************************
	int nCurrState;             // �˶� ���� ���� �÷���
	CString strCurrMsg;         // �߻��� �˶� �޽��� ���� ����
	// **************************************************************************
};
extern  tagALARM_DISPLAY_INFO  st_alarm_display_info;


// **********************************************************************************
// ������ ȭ�� ȯ�� ���� ���� ���� ����ü ����                                   
// **********************************************************************************
struct tagBASIC_INFO
{
	//int		nModeTesterDisable; //teser �����/��(0:tester���, 1:������� ����(���Ͽ������� ��������)
	
	int		nCtrlMode;				// [Title Bar ���� ǥ��] < ONLINE, REMOTE, LOCAL.. ǥ��	> 
	int		nModeDevice;			// [Title Bar ���� ǥ��] < WHIT/WHIT OUT �� MODE ǥ��	>
	int		nModeWork;				// [Title Bar ���� ǥ��] < �۾� ��� ���� ǥ��			>
	int		nModeXgem;
	int     nRetry;
	int     nModeInterface;
	int		nModeXgemInterface;		// xgem interface [0] off line [1] on line local [2] on line remote.....
	CString strDeviceName;			// [Title Bar ���� ǥ��] < ��񿡼� ������ DEVICE ǥ��	>
	CString strModelName;			// [Title Bar ���� ǥ��] < �������� ������ JOB ���� ǥ�� >

	CString strNotice;				// Notice...
	CString	strEqp;					// eqp id.........
	CString strOperID;				// operator id.....
	CString strDevice;
	//kwlee 2017.0523

	int  nModeCapRemoveUse;
	int  nModeSorterPickerUse;
	int  nModeModuleDirCheck;
	int  nModeHeatSinkDirCheck;

	int  nPrinterVisionPapper;
	int  nPrintBinPapper;
	int  nLabelErrCnt;

	int nDeviceCnt;
	int nRepickCnt;

	int nShift_Robot_Skip[4];
	////
} ;
extern  tagBASIC_INFO  st_basic_info;
// ******************************************************************************

// **********************************************************************************
// ������ ȭ�� ȯ�� ���� ���� ���� ����ü ����                                   
// **********************************************************************************
struct tagRECIPE_INFO
{	
	int nTrayX;
	int nTrayY;

	double dPickGapModuleLoad;
	double dPickGapHeatSinkLeft;
	double dPickGapHeatSinkRight;
};
extern tagRECIPE_INFO	st_recipe_info;
// ******************************************************************************

// *****************************************************************************
//  Tower Lamp ȭ�鿡 ���� ���� ���� ����ü ���� ����                           
// *****************************************************************************
struct tagLAMP_INFO
{
	int nTFlick;
	int nLampR[9];				// RED ���� ���� ���� ����
	int nLampY[9];				// YELLOW ���� ���� ���� ����
	int nLampG[9];				// GREEN ���� ���� ���� ����
	int nLampB[9];				// GREEN ���� ���� ���� ����

	int nInterest;				// BLUE ���� ���� ���� ����

	CString strEquipNo;			// ��� ȣ�� ���� ����
	CString strEquipCode;		// ��� �ڵ� ���� ����

	int nBuzzerMode;			// ���� ��� ��� ���� ����
	int nStatusBuzzerRing;		// ���� �︮�� �ִ� ���� ���� 
	long lBuzzerOffWait[3];		// ���� ���� �ð� �︮�� ���ߵ��� �ϴ� ���� 

	int nLampWaitTime;			// ���� FLACKER �ð� ���� ����

	int nModeLampBlue;			// ������� ���� ���� ��뿩��
	int nModeLampBlueFlicker;	// ������� ���� ���� FLACKER ����
};
extern  tagLAMP_INFO st_lamp_info;
// *****************************************************************************

enum LAMP_CTRL
{
	LAMP_ON		= 1,
	LAMP_OFF	= 2,
	LAMP_FLICK	= 3,
};

struct tagIO_INFO
{
	///////////////////////////////////////////////////////////////////////////////////////////////
	// Module No 00
	///////////////////////////////////////////////////////////////////////////////////////////////
	int		o_StartLamp;					// S0000
	int		o_StopLamp;						// S0001
	int		o_AlarmLamp;					// S0002
	int		o_BuzzLamp;						// S0003
	int		o_DoorLock;						// S0004
	//S0005									
	//S0006									
	//S0007									
	int		i_StartChk;						
	int		i_StopChk;						
	int		i_AlarmChk;						
	int		i_BuzzChk;						
	int		i_AutoModeChk;					
	int		i_ManualModeChk;				
	int		i_FrontSelectSwChk;				
	int		i_RearSelectSwChk1;				

	///////////////////////////////////////////////////////////////////////////////////////////////
	// Module No 01
	//////////////////////////////////////////////////////////////////////////////////////////////
	int		o_MainAir;						// S0100
	int		o_TwGreenLamp;					// S0101
	int		o_TwYellowLamp;					// S0102
	int		o_TwRedLamp;					// S0103
	int		o_Buzz1OnOff;					// S0104
	int		o_Buzz2OnOff;					// S0105
	int		o_Buzz3OnOff;					// S0106
	//S0107									
	int		i_MainMcChk;					//PS0100
	int		i_MainAirChk;					//PS0101
	int		i_LfTsiteDockSafetyChk;			//PS0102
	int		i_RiTsiteDockSafetyChk;			//PS0103
	int		i_Emo1SwChk;					//PS0104
	int		i_Emo2SwChk;					//PS0105
	int		i_Emo3SwChk;					//PS0106
	int		i_Emo4SwChk;					//PS0107

	int		o_TwLamp[3];
	int		o_BuzzOnOff[3];
	int		i_EmoChk[4];
	
	//kwlee 2017.0524
	//Ready_output
	int	o_hs_Front_Ready_stacker_guide_clamp_onoff;
	int o_hs_Front_Ready_stacker_guide_unclamp_onoff;

	int o_hs_Front_Ready_stacker_Left_rail_fwd_onoff;
	int o_hs_Front_Ready_stacker_Left_rail_bwd_onoff;
	int o_hs_Front_Ready_stacker_Right_rail_fwd_onoff;
	int o_hs_Front_Ready_stacker_Right_rail_bwd_onoff;

	int o_hs_Front_stacker_tray_pusher_bwd_onoff;
	int o_hs_Front_stacker_tray_pusher_fwd_onoff;

	int o_hs_Front_Ready_stacker_updn;
	int o_hs_Front_stacker_tray_Seperate_onoff;

	//Ready_input
	int i_hs_Front_stacker_tray_Seperate_fwd_chk;
	int i_hs_Front_stacker_tray_Seperate_bwd_chk;

	int i_hs_Front_Ready_stacker_guide_clamp_on_chk;
	int i_hs_Front_Ready_stacker_guide_unclamp_off_chk;

	int i_hs_Front_Ready_stacker_Left_rail_fwd_chk;
	int i_hs_Front_Ready_stacker_Left_rail_bwd_chk;
	int i_hs_Front_Ready_stacker_Right_rail_fwd_chk;
	int i_hs_Front_Ready_stacker_Right_rail_bwd_chk;

	int i_hs_Front_stacker_tray_pusher_fwd_chk;
	int i_hs_Front_stacker_tray_pusher_bwd_chk;
	
	int i_hs_Front_Ready_stacker_up_chk;
	int i_hs_Front_Ready_stacker_dn_chk;

	int i_hs_Front_Ready_stacker_tray_chk; //���� Tray Check Sensor
	int i_hs_Front_Ready_stacker_updn_pos_chk; //Stacker UpDn Cylinder ���� Tray ���� Check

	///Work_output
	int	o_hs_Front_Work_stacker_guide_clamp_onoff;
	int o_hs_Front_Work_stacker_guide_unclamp_onoff;

	int o_hs_Front_Work_stacker_Right_rail_fwd_onoff;
	int o_hs_Front_Work_stacker_Right_rail_bwd_onoff;
	int o_hs_Front_Work_stacker_Left_rail_fwd_onoff;
	int o_hs_Front_Work_stacker_Left_rail_bwd_onoff;

	int o_hs_Front_Work_stacker_updn;
	

	///Work_input
	int i_hs_Front_Work_stacker_guide_clamp_on_chk;
	int i_hs_Front_Work_stacker_guide_unclamp_off_chk;

	int i_hs_Front_Work_stacker_Right_rail_fwd_chk;
	int i_hs_Front_Work_stacker_Right_rail_bwd_chk;
	int i_hs_Front_Work_stacker_Left_rail_fwd_chk;
	int i_hs_Front_Work_stacker_Left_rail_bwd_chk;

	int i_hs_Front_Work_stacker_up_chk;
	int i_hs_Front_Work_stacker_dn_chk;
	
	int i_hs_Front_Work_stacker_tray_chk; //���� Tray Check Sensor
	int i_hs_Front_Work_stacker_updn_pos_chk;

	/////////////
	//Robot outPut
	int o_hs_Front_rbt_picker_Fwd_updn;
	int o_hs_Front_rbt_picker_Fwd_gripper_onoff;

	int o_hs_Front_rbt_picker_Bwd_updn;
	int o_hs_Front_rbt_picker_Bwd_gripper_onoff;
	
	int o_hs_Front_rbt_picker_gripper_onoff[2];
	int o_hs_Front_rbt_picker_updn[2];

	//Robot Input
	int i_hs_Front_rbt_picker_Fwd_up_chk;
	int i_hs_Front_rbt_picker_Fwd_dn_chk;
	int i_hs_Front_rbt_picker_Fwd_gripper_dvc_chk; 

	int i_hs_Front_rbt_picker_Bwd_up_chk;
	int i_hs_Front_rbt_picker_Bwd_dn_chk;
	int i_hs_Front_rbt_picker_Bwd_gripper_dvc_chk;

	int i_hs_Front_rbt_picker_up_chk[2];
	int i_hs_Front_rbt_picker_dn_chk[2];
	int i_hs_Front_rbt_picker_gripper_dvc_chk[2];

	//kwlee 2017.0530 Rear Stacker & Robot
	
	int	o_hs_Rear_Ready_stacker_guide_clamp_onoff;
	int o_hs_Rear_Ready_stacker_guide_unclamp_onoff;

	int o_hs_Rear_Ready_stacker_Left_rail_fwd_onoff;
	int o_hs_Rear_Ready_stacker_Left_rail_bwd_onoff;
	int o_hs_Rear_Ready_stacker_Right_rail_fwd_onoff;
	int o_hs_Rear_Ready_stacker_Right_rail_bwd_onoff;

	int o_hs_Rear_stacker_tray_pusher_bwd_onoff;
	int o_hs_Rear_stacker_tray_pusher_fwd_onoff;

	int o_hs_Rear_Ready_stacker_updn;
	int o_hs_Rear_stacker_tray_Seperate_onoff;

	
	//Ready_input
	int i_hs_Rear_stacker_tray_Seperate_fwd_chk;
	int i_hs_Rear_stacker_tray_Seperate_bwd_chk;

	int i_hs_Rear_Ready_stacker_guide_clamp_on_chk;
	int i_hs_Rear_Ready_stacker_guide_unclamp_off_chk;

	int i_hs_Rear_Ready_stacker_Left_rail_fwd_chk;
	int i_hs_Rear_Ready_stacker_Left_rail_bwd_chk;
	int i_hs_Rear_Ready_stacker_Right_rail_fwd_chk;
	int i_hs_Rear_Ready_stacker_Right_rail_bwd_chk;

	int i_hs_Rear_stacker_tray_pusher_fwd_chk;
	int i_hs_Rear_stacker_tray_pusher_bwd_chk;

	int i_hs_Rear_Ready_stacker_up_chk;
	int i_hs_Rear_Ready_stacker_dn_chk;

	int i_hs_Rear_Ready_stacker_tray_chk; //���� Tray Check Sensor
	int i_hs_Rear_Ready_stacker_updn_pos_chk; //Stacker UpDn Cylinder ���� Tray ���� Check

	///Work_output
	int	o_hs_Rear_Work_stacker_guide_clamp_onoff;
	int o_hs_Rear_Work_stacker_guide_unclamp_onoff;

	int o_hs_Rear_Work_stacker_Right_rail_fwd_onoff;
	int o_hs_Rear_Work_stacker_Right_rail_bwd_onoff;
	int o_hs_Rear_Work_stacker_Left_rail_fwd_onoff;
	int o_hs_Rear_Work_stacker_Left_rail_bwd_onoff;

	int o_hs_Rear_Work_stacker_updn;


	///Work_input
	int i_hs_Rear_Work_stacker_guide_clamp_on_chk;
	int i_hs_Rear_Work_stacker_guide_unclamp_off_chk;

	int i_hs_Rear_Work_stacker_Right_rail_fwd_chk;
	int i_hs_Rear_Work_stacker_Right_rail_bwd_chk;
	int i_hs_Rear_Work_stacker_Left_rail_fwd_chk;
	int i_hs_Rear_Work_stacker_Left_rail_bwd_chk;

	int i_hs_Rear_Work_stacker_up_chk;
	int i_hs_Rear_Work_stacker_dn_chk;

	int i_hs_Rear_Work_stacker_tray_chk; //���� Tray Check Sensor
	int i_hs_Rear_Work_stacker_updn_pos_chk;

	/////////////
	//Robot outPut
	int o_hs_Rear_rbt_picker_Fwd_updn;
	int o_hs_Rear_rbt_picker_Fwd_gripper_onoff;

	int o_hs_Rear_rbt_picker_Bwd_updn;
	int o_hs_Rear_rbt_picker_Bwd_gripper_onoff;

	int o_hs_Rear_rbt_picker_gripper_onoff[2];
	int o_hs_Rear_rbt_picker_updn[2];

	//Robot Input
	int i_hs_Rear_rbt_picker_Fwd_up_chk;
	int i_hs_Rear_rbt_picker_Fwd_dn_chk;
	int i_hs_Rear_rbt_picker_Fwd_gripper_dvc_chk; 

	int i_hs_Rear_rbt_picker_Bwd_up_chk;
	int i_hs_Rear_rbt_picker_Bwd_dn_chk;
	int i_hs_Rear_rbt_picker_Bwd_gripper_dvc_chk;

	int i_hs_Rear_rbt_picker_up_chk[2];
	int i_hs_Rear_rbt_picker_dn_chk[2];
	int i_hs_Rear_rbt_picker_gripper_dvc_chk[2];

	int	i_LoDoorSafetyChk[7];
	///////////////////////////////////////////////////////////////////////////////////////////////

	int		oMotPwr[MAXMOTOR];
};
extern  tagIO_INFO  st_io_info;
// *************************************************************************
// ���� ��θ� ���� ����ü ���� ����                                             
// *************************************************************************
struct tagPATH_INFO
{
	CString strBasic;			// �⺻ ���� ���� ���� ����+���ϸ� ���� ����
	CString strPathDvc;			// ����̽��� ƼĪ ���� ���� ���� ���� ���� ���� ����
	CString strSocket;			// ���Ϻ�...
	CString strPathAlarm;		// ��� �˶� ���� ���� ���� ���� ����
	CString strPathOp;			// ���۷����� ���� ���� ���� ���� ����
	CString strPathTray;		// Tray�� ���� ���� ���� ���� ���� ���� ����
	
	CString strPathFile;		// ���� ���� ���� ���� ����
	CString strPathBack;		// BACKUP ���� ���� ���� ���� ����

	//kwlee 2017.0511
	CString strPath_Label;
	CString strPath_Model;

	CString strPathRecipe;
	CString strPathFtpGms;		// ftp path ���.....

	CString strPathRecovery;	// recoverydata........

	CString strFileBasic;		// �⺻ ���� ���� ���� ���ϸ� ���� ����
	CString strFileWait;		// ��� �ð� ���� ���� ���ϸ� ���� ����
	CString strFileMotor;

	CString strOperation;		//Operation Log ���� ���� ����.
	CString strInterface;		//Interface Log ���� ���� ����.
	CString strMachine;			//Machine Log ���� ���� ����.
	CString strTotal;			//Total Log ���� ���� ����.
	CString strData;			//Data Log ���� ���� ����.
	CString strAlarmDay;
	CString strAlarmMonth;

	CString strIoMap;
	CString strPartIoMap;
	CString strIoPartMap;
	CString strMotorAxisMap;
	CString strMotorPartMap;
	CString strWaitTimeMap;

	

};
extern  tagPATH_INFO st_path_info;
// *************************************************************************

struct tagWORK_INFO
{
	int		nPgmInfo;
	int		nSimulationMode;
	int		nMessageInfo;
	int		nStatusEqp;
	int		nRearSafetyChk;
	int		nTowerStatus[5];

	int		nRemoveInfo[10];		// alarm skip ����.....
	int		nRemoveYesNo[10];		// alarm skip ����.....

	int		nLfTsiteBin[2][12];
	int		nRiTsiteBin[2][12];

	int		nBcrX;					// barcode x ��ǥ.....
	int     nBcrY;					// barcode y ��ǥ.....
	int		nBdReadyChk;			//


};
extern  tagWORK_INFO  st_work_info;


// *************************************************************************
// ��Ÿ ���� ���� ����ü ����                                                    
// *************************************************************************
struct tagOTHER_INFO
{
	CString strOpMsg;			// ����Ʈ ȭ�� ��� ���� ���� �޽��� ���� ����
	CString strNormalMsg;		// ����Ʈ ȭ�� ��� ���� ���� �޽��� ���� ����
	CString strAbnormalMsg;		// ����Ʈ ȭ�� ��� ���� ���� �޽��� ���� ����
	CString strSndMsg;			// ����Ʈ ȭ�� �׽��� SEND �޽��� ���� ����
	CString strRcvMsg;			// ����Ʈ ȭ�� �׽��� RECIVE �޽��� ���� ����
	CString strBcrRcvMsg;		// ����Ʈ ȭ�� ���ڵ� RECIVE �޽��� ���� ����
	CString strBoxMsg;

	CString strFallacyMsg;		// ���� �޽��� ��ȭ ���� Ÿ��Ʋ ���� ����
	CString strConfirmMsg;		// Ȯ�� �޽��� ��ȭ ���� Ÿ��Ʋ ���� ����
	CString strTypingMsg;		// Ű���� ��ȭ ���� Ÿ��Ʋ ���� ����

	CString strKeypadMsg;		// Ű�е� ��ȭ ���� Ÿ��Ʋ ���� ����
	CString strPadVal;			// Ű�е� ��ȭ ���ڿ� ����� ������ ���� ����

	CString strPadHighLimit;
	CString strPadLowLimit;

	CString strPassLevel;		// ��ȣ ���� ���� ����
	CString strPassword;		// ��ȣ ���� ����
	
	CString strParentMenu;		// �ָ޴� �̸� ���� ����

	CString strMsgBuf[10];

	char cNormalMsg[4096];
	char cAbnormalMsg[4096];
	char cOpMsg[4096];

	int nBuzYesNo;				// jtkim 20150410
	int nConfirmMsg;
	int nConfirmType;
	////////////////////////////////2K10/02/09/ViboX////////////////////////////////////////
	int		nPrevStep[100];			// ���� step (���� �Ǿ����� ���� ����)
	CString	strHistoryStep[100];		// step_history �� 50���� �ش��ϴ� step�� ����
	CString strLastChangeDate[100];	// ���� step���� ����Ǵ� ������ �ð�
};
extern  tagOTHER_INFO  st_other_info;
// *************************************************************************

// *************************************************************************

#define INIT_CLEAR					0
#define INIT_READY					1
#define INIT_COMPLETE				2

#define WORK_CLEAR					0



//////////////////////////////////////////////////////////////////////////////////////////////////////////////
// 
//////////////////////////////////////////////////////////////////////////////////////////////////////////////


enum TEST_SITE_HIGH_LOW_INFO  //test site high / low ���� 
{
	 TESTSITE_LOW							=  0,
     TESTSITE_HIGH						    , 
};

enum THREAD_SYNC_VARIBLE_SITE_INFO  //��ġ�� Ʈ���� ���� ������ ��ġ���� ������ ����  
{
	THD_HS_FRONT_STACKER_SITE          =  0,
	THD_HS_REAR_STACKER_SITE        ,
	LDMODULE_STACKER_SITE           ,
	THD_HS_FRONT_RBT ,
	THD_HS_REAR_RBT,
	THREAD_MAX_SITE							,
};


struct tagSYNC_INFO
{
	int			nInitializeError;
	int			nLotEnd[50];					// lot end flag ����.....

	int			nInitializeSuccess;
	int         nInit_Flag[50];
	
	int         nShiftWork_Rbt_Req[MAX_BUFFER_SITE];				 //Buffer���� Robot���� �۾� ��û
	int         nWorkRobot_Req[MAX_WORK_SITE][MAX_WORK_JOB]; //Robot�� Stacker�� ��û.
	int         nStacker_Site_Req[MAX_WORK_SITE][MAX_STACKER_POS]; //Stacker�� Robot���� �۾� ��û.
};
extern tagSYNC_INFO	st_sync_info;

//kwlee 2017.0529
struct tagPICKER_INFO
{
	int nEnable[MAX_WORK_SITE][MAX_PICKER];
	int nExist[MAX_WORK_SITE][MAX_PICKER];
	CString strLotNum;
	CString strPartNum;
};
extern tagPICKER_INFO st_Picker_info;

struct tagTRAY_INFO
{
	int nExist[MAX_WORK_SITE][MAX_PICKER];
	int nTray_X;
	int nTray_Y;
};
extern tagTRAY_INFO st_Tray_info;

struct tagVARIABLE_INFO
{
	

};
extern tagVARIABLE_INFO	st_var;

//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////// 2015.0102 
#define MAX_GMS_CHANNEL					8

struct tagCLIENT_INFO
{
	CString		strIp;			// ip address......
	
	int			nPort;			// port.....
	int			nConnect;		// client �������......
	int			nSendLength;	// �۽� ���� ����......
	int			nRevLength;		// ���� ���� ����......
	int			nClientReady;	// ������ ������...
	int			nRevInfo;		// client ���� ���..... (0:�ٷ� 1: ������)

	char		chRev[8196];	// ���ų���....
	CString     strRev;
	char		chSend[8196];   // �۽ų���....
	CString		strSend;
};
extern tagCLIENT_INFO st_client_info[10];

struct tagSERVER_INFO
{
	CString		strIp;			// ip address......
	
	int			nPort;			// port.....
	int			nConnect;		// client �������......
	int			nSendLength;	// �۽� ���� ����......
	int			nRevLength;		// ���� ���� ����......
	
	char		chRev[8196];	// ���ų���....
	CString     strRev;
	char		chSend[8196];   // �۽ų���....
	CString		strSend;
};
extern tagSERVER_INFO st_server_info[10];

struct tagRS232_INFO
{
	int			nSerialPort[10];		// serial port....
	int			nSerialBaudrate[10];	// serial baudrate....
	int			nSerialData[10];		// serial data....
	int			nSerialParity[10];		// serial parity.....
	int			nSerialStop[10];		// serial stop....
};
extern tagRS232_INFO st_rs232_info;


enum PICKER_PICKPLACE_INFO
{
	 PICKER_PICK_MODE	= 0,
	 PICKER_PLACE_MODE	   ,
};

#define	BD_READY_CHK_TIME	20		// board ready ����� �Ϸ�üũ �ð�

enum BOARD_INFO
{
	BD_NONE							= 0,
	
};
//kwlee 2017.0529
enum M_TRAY_STACKER_ELEVATOR 
{
	P_ELV_SAFETY		  = 0,
	P_ELV_UP_LIMIT		    ,  
	P_ELV_DN_LIMIT		    ,  
	P_ELV_SD_SENSOR			,

	P_ELV_TRAY_INOUT_POS   ,		
	P_ELV_SUPPLY_OFFSET		,
	P_ELV_RECEIVE_OFFSET	, 
};

enum M_WORK_RBT_Y_Z
{
	P_WORKROBOT_SAFETY				= 0,	
	P_WORKROBOT_WORK_POS			, 
	P_WORKROBOT_READY_POS			, 

	P_WORKROBOT_WORK_BUFF_1_POS		, 
	P_WORKROBOT_WORK_BUFF_2_POS		, 
	P_WORKROBOT_WORK_BUFF_3_POS		, 
	P_WORKROBOT_WORK_BUFF_4_POS		, 

};


enum LOT_INFO
{
	LOT_CURR						= 0,
	LOT_NEXT						,
	LOT_CURR_BACKUP					, //2015.0302 james LOT_CURR�� lot end �� Ŭ�������� ��� �����͸� �޴´� 
};
// lot ����.....
struct tagLOT_INFO
{
	CString strLotNo;				// lot no......
	CString strPartNo;				// part no......
	CString strProcess;				// process id.....
	CString strProPerty;			// property end....
	CString strBypass;				// bypass.....

	
	int     nLotStatus; //0:clear, 1:set
	int		nLotEnd[THREAD_MAX_SITE]; //�ش� ����Ʈ lot end �÷��� 


	COleDateTime	tStart;			// jtkim 20150408
};
extern tagLOT_INFO st_lot_info[3]; //2015.0302 james [2] -> [3] 

struct tagCOUNT_INFO
{
	// count ǥ���ϱ� ����
	long nInCount[2][2];			// [0][0]:lot ����, [0][1]:lot ���� [1][0]:DAILY ���� 
	long nPassCount[2][2];			// ��ǰ����.....
	long nPrimeCount[2][2];			// nPrimeCount........
	long nRejectCount[2][2];
	
	int nUph;
	int nDailyUph;
	// jtkim 20160106
	int nUphCnt;
	double dDailyPer;
	double dHourPer;

};
extern struct tagCOUNT_INFO st_count_info;


struct tagPART_INFO
{
	CString strPartNo[30];
	CString strType[30];
	CString strDate[30];

	int nDataCnt;
};
extern struct tagPART_INFO st_part_info;

struct tagTYPE_INFO
{
	CString strType[30];
	CString strDate[30];

	int nDataCnt;
};
extern struct tagTYPE_INFO st_type_info;

struct tagLOT_DISPLAY_INFO
{
	CString strLotNo;
	CString strPartNo;
	CString strLotState;
	CString strLotType;
	CString strMainState;
	CString strProCid;
	CString strStep;
	CString strComplot;
	CString strLine;
	
	int nQty;
	int nScrapCnt;
};
extern struct tagLOT_DISPLAY_INFO st_lot_display_info;

struct tagLOT_HISTORY_INFO
{
	CString strLotNo;
	CString strPartNo;
	int		nTotalCnt;
	int		nPassCnt;
};
extern struct tagLOT_HISTORY_INFO st_lot_history_info;

enum WAIT_TIME
{
	WAIT_PICKER_UP_DN						= 0,
	WAIT_PICKER_ON_OFF						,
	WAIT_STACKER_UP_DN                      ,
	WAIT_STACKER_CYL_ON_OFF                 ,
	MAX_WAIT_TIME							,
};

// *************************************************************************
// I/O ���� ��� �ð� �� ����Ʈ �ð� ���� ����ü ����                            
// *************************************************************************

struct tagWAIT_INFO
{
	int	nOnWaitTime[MAX_WAIT_TIME];
	int nOffWaitTime[MAX_WAIT_TIME];
	int nLimitWaitTime[MAX_WAIT_TIME];

	//at loader
	int nGripOnOffWaitTime;
	int nPickUpDnWaitTime;
};
extern  tagWAIT_INFO  st_wait_info;


struct tagSCRAP_CODE
{
	int		m_nScrapCode[10000][2]; //scrap code data.....
	int		m_nScrapBin;			// scrap code bin......
};
extern tagSCRAP_CODE st_code_info[2];




enum RECOVERY_CYL
{
	RECO_LD_CVY_BUFF_STOPPER					= 0,
	RECO_MAX_COUNT								,
};

enum EQP_MCMD
{
	EQP_OFF_LINE					= 1,
	EQP_ON_LINE						= 4,
};

enum MES_MCMD
{
	MES_OFF_LINE					= 0,
	MES_ON_LINE_LOCAL				= 4,
	MES_ON_LINE_REMOTE				= 5,
};


enum LINK_STATUS
{
	LINK_DISCONNECT					= 0,
	LINK_CONNECT					= 1,
};


enum PROC_STATE
{
	PROC_UNKNOWN					= 0,
	PROC_IDLE						,
	PROC_RUN						,
	PROC_DOWN						,
	PROC_MAINT						,
};

enum  THREAD_PART
{
	PART_MGZ_ELV					= 0,

	
};


enum EQ_WITH_MODE_STATE
{
	WITHOUT_DVC						= 0,
	WITH_DVC						= 1,
	WITHOUT_TRAY					= 3,
};


enum EQ_WORK_MODE_STATE
{
	WORK_BYPASS						= 0,
	WORK_JIG						= 1,
	WORK_MAGAZINE					= 2,
};

#define DN							0
#define UP							1

#define MOVE_FORWARD				0
#define MOVE_BACKWARD				1

enum MOTOR_NUM
{
	M_HS_F_STACKER_READY		= 0,
	M_HS_R_STACKER_READY		= 0,
	M_HS_F_RBT_Y				,
	M_HS_F_RBT_Z				,
	M_HS_R_RBT_Z                ,
	M_HS_R_RBT_Y                ,
	M_MAX_MOTOR_NUM					, //29
};

enum COMM_PORT
{
	LD_BCR_PORT						= 0,
	UNLD_BCR_A_PORT					,
	UNLD_BCR_B_PORT					,
};

#define WAIT_CONNECT					5000
#define WAIT_RCV						30000
#define WAIT_CLOSE						300

enum NETWORK_NUM
{
	EC_FIRST_NETWORK				= 0,
	XGEM_NETWORK					,
	INTERFACE_NETWORK				,
	FRONT_NETWORK					,
	REAR_NETWORK					,
	RFID_NETWORK					,
	FTP_NETWORK						,
	GMS_NETWORK						,
	EC_SECOND_NETWORK				,
};

enum CUSTOM_IO_FUNCTION_PICKER
{
	ALL_PICKER			= -1,
	PICKER_1			,
	PICKER_2			,

};

#define SLOT_DISABLE				0
#define SLOT_ENABLE					1

#endif
	

	