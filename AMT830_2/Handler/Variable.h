#include <afxtempl.h>

#ifndef _VARIABLE_h__
#define _VARIABLE_h__

#include "Alg_Mysql.h"

// amt8562
//	Console application 프로그램을 위해서 아래 부분을 정의함
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
// 사용자 정의 메시지 ID 선언                                                   
// *****************************************************************************
#define WM_FORM_CHANGE			WM_USER+200   // 화면이 전환된 때 해당 전환 상태 정보를 전송하기 위한 사용자 정의 메시지 

#define WM_STATUS_CHANGE		WM_USER+201   // 타이틀 바 화면으로 전송된 메시지 출력시키기 위한 사용자 정의 메시지 추가 

#define WM_LIST_DATA			WM_USER + 6   // 통신 메시지 출력 리스트 대화 상자에 
                                              // 시리얼 포트를 통해 송/수신된 메시지를 출력하기 위한 사용자 정의 메시지 
#define WM_DATA_SEND			WM_USER + 7   // Data를 전송하기 위한 화면에서 정보를 전송하기 위해 정의한 사용자 정의 함수

#define WM_WORK_END				WM_USER + 8   // 테스트 작업 완료 시 정보를 메인 화면에 출력시키기 위한 사용자 정의 메시지 추가 

#define WM_BASIC_APPLY			WM_USER + 10  // BASIC DATA를 APPLY 시키기 위한 사용자 정의 메시지 추가 

#define WM_MAINTENANCE_APPLY	WM_USER + 11  // Maintenance DATA를 APPLY 시키기 위한 사용자 정의 메시지 추가
#define WM_INTERFACE_APPLY		WM_USER + 13
#define	WM_WAITTIME_APPLY		WM_USER + 15  // Wait Time DATA를 APPLY 시키기 위한 사용자 정의 메시지 추가 

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

#define WM_DATA_INIT_SAVE       WM_USER + 300 // apply버튼시 저장까지, 해당 화면의 데이터 적용(Init)
#define WM_DATA_CHANGE          WM_USER + 301 // apply버튼시 저장까지, 해당 화면의 데이터 적용(Init)

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
//  네트웍 메세지 정의 장비쪽에서 BPC로 보내는 메세지.
// *****************************************************************************
#define NW_LOT_START_RPY				1
#define NW_LOT_CANCEL_RPY				2

// *****************************************************************************
//  List Box 출력용 메세지 정의                                                 
// *****************************************************************************
#define RECEIVE_MSG			1
#define SEND_MSG			2
#define NORMAL_MSG			3
#define ABNORMAL_MSG		4
#define MACHINE_INFO		5
#define DEVICE_INFO			6

// *****************************************************************************
// *****************************************************************************
//  SCREEN_MAIN 출력용 메세지 정의                                                
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
//  Title Bar 출력용 메세지 정의                                                
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
// 장비 동작 제어 시 필요한 메시지 정의                                         
// *****************************************************************************
#define TIMECOUNT			5
#define ELEVATOR_STRATUMS	6
// *****************************************************************************

// *************************************************************************
// 장비 동작 제어 시 필요한 메시지 정의                                          
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
#define dREINSTATE			10	//복귀동작중
#define dRECOVERY			11
#define dMOTOR_WARNING		12 //이때는 알람은 발생시키지 않는다(run status를 바꾸지 않는다).thread 에서만 판단하여 알람 발생시킨다 

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
// RS-232C 시리얼 통신 시 사용되는 메시지 정의                                   
// -> MAX_PORT : 기본 포트 2개로 구성되어 있다						             
// *************************************************************************
#define MAX_PORT				2	// 생성할 시리얼 포트 갯수
#define COM_ERROR				-1	// 에러 메시지
#define CRI_BARCODE_PORT		0		// 현재 BCR READ 포트 번호
#define MPCB_BARCODE_PORT		1		// 현재 BCR READ 포트 번호
#define LIGHT_PORT				2
#define A_LIGHT_PORT			3

#define COM_PORT			0
#define COM_BAUDRATE		1
#define COM_DATA			2
#define COM_STOP			3
#define COM_PARITY			4

//#define TESTER_PORT	2		// 현재 Tester Communication 포트 번호
//#define COM_PORT   2	// 현재 사용 중인 시리얼 포트 번호
 
#define BUF_SIZE  1000	// 버퍼 크기
// *************************************************************************

// *************************************************************************
// *************************************************************************
// I/O 모듈 갯수 및 포트 최대 갯수 선언한다                                      
// *************************************************************************
#define MAX_IO				1315

#define MAX_MASTER_IO		1
#define MAX_PORT_IO			4
#define MAX_SLAVE_IO		8
// *************************************************************************
#define M_BARCODE_PORT		0
#define C_BARCODE_PORT		1
// *************************************************************************
//  MOTOR 보드 관련 변수 선언한다                                                
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
//  Main Screen 출력용 메세지 정의                                              
// *****************************************************************************

// *****************************************************************************
///// test bin  result
#define BIN_NOTUESD			0

#define BUTTON_MOUSE_DN		1100
#define BUTTON_MOUSE_UP		1000

// GRID TYPE
#define DFC_NOUSE       -1//원래시스템 그리기 사용함(0번컬럼을 원래대로 사용할때 이용하면됨)
#define DFC_STATIC       0
#define DFC_EDIT         1
#define DFC_COMBO        2
#define DFC_CHECK        3
#define DFC_DATE         4
#define DFC_TIME         5
#define DFC_PROGRESS     6
#define DFC_IMAGE        7

#define IMG_LISTHDCTRL_BG _T("배경2.jpg")//_T("smflower.jpg")
#define IMG_PICCTRL_BG _T("배경2.jpg") //_T("smflower.jpg")
#define IMG_LISTHDCTRL_BG1 _T("배경25.gif")//_T("smflower.jpg")
#define IMG_PICCTRL_BG1 _T("배경25.gif") //_T("smflower.jpg")

// 칼라 정의
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

// board 상태 정보
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

#define RET_PICKER_NOT_FIND		100  //피커에 더이상 작업할 공간이 없으면 
#define RET_TRAY_NOT_FIND		200  //트레이에 더이상 작업할 공간이 없으면 

/* ***************************************************************************** */
/* 화면 뷰 클래스 ID 설정 부분                                                   */
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

	BOOL bProgramExit;				//프로그램이 빠져나가는건지 확인한다.
	// **************************************************************************
	// LOT 처리 관련 플래그 설정 멤버 변수                                       
	// **************************************************************************
	bool bLoaderOnFlag;				// 로더 On : True    로더 Off : False
	bool bAllLotStartFlag;			// LOT 처음 시작 시 설정 됨
	// **************************************************************************

	int nMenuNum;					// 각 화면에 설정된 화면 번호 저장 변수 
	int nAlarmScreen;				// 현재 알람 화면이 출력되어져 있는지에 대한 정보 저장 변수 
	int nLoadState;					// 현재 로딩 버튼 관련 대화 상자 출력 여부 플래그 저장 변수 
	int nRetestRequest;				// 리젝 자재로 리테스트 하는건지 물어본다.
	// *************************************************************************
	// 원래 위치 복귀 기능 사용 시 사용되는 변수 선언                           
	// *************************************************************************
	int nHomingRequest[MAXMOTOR];	// 강제 Home Check 요청 플래그 설정 변수 
	int nMenuLock;					// 메뉴 사용 가능 상태 플래그 
	int nSystemLock;				// SYSTEM LOCK 상태 플래그
	int nSwitchLock;				// Dialog가 떠 있는 상태 플래그 (Start Switch Lock)	
	int nMaintMode;					// 메인트 모드 설정 플래그
	int nLevelMaint;				// 메인트 레벨(Level 1) 설정 플래그
	int nLevelTeach;				// 티칭 레벨(Level 2) 설정 플래그
	int nLevelAdmin;				// 관리자 레벨(Level 3) 설정 플래그
	int nLevelSpeed;
	int nIoBoardInitial;			// IO 보드 초기화 작업 완료 플래그
	int nMotorBoardInitial;			// 모션 보드 초기화 작업 완료 플래그
	int nMatroxBoardInitial;		// matrox 초기화
	int nIsAllSiteInitEnd;			// 모터 초기화 작업 완료 확인 플래그
	int nRunStatus;
	int nIdleStatus;
	int nManualSpeed;
	int nRunSpeed;
	int nMachineMode;
	int nLotStatus;					// Lot start 시작유무....
	int	nInitRetry;					// initialize retry 작업 유무.......
	int nInitialSuccess;			// Initialize 작업 성공유무.......	
	int nFtpVer;

	double dCurrCmdPos[MAXMOTOR];	// 현재 모터 위치 정보 저장 변수 
	// *************************************************************************
	COleDateTime tUph;
	// *************************************************************************
	// 화면에 대한 핸들 정보 저장 변수 선언                                     
	// *************************************************************************
	HWND hWnd;						// 메인 프레임 핸들 저장 변수

	CWnd *cWndMain;					// 메인 화면 핸들 저장 변수
	CWnd *cWndBasic;				// BASIC 화면 핸들 저장 변수
	CWnd *cWndInitial;
	CWnd *cWndMaintenance;			// Maintenance 화면 핸들 저장 변수	
	CWnd *cWndWaitTime;				// Wait Time 화면 핸들 저장 변수
	CWnd *cWndMotorSpeed;			// Motor Speed 화면 핸들 저장 변수
	CWnd *cWndIO;					// IO 화면 핸들 저장 변수
	CWnd *cWndMotor;
	CWnd *cWndTitle;				// 타이틀 출력 화면 핸들 저장 변수
	CWnd *cWndList;					// 리스트 출력 화면 핸들 저장 변수
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
// RS-232C 시리얼 통신 관련 저장 구조체 선언                                     
// *************************************************************************
struct tagSERIAL_INFO
{
	int	nConnect[MAX_PORT];
	int nSndChk[MAX_PORT];				// 메시지 송신 완료 플래그
	int nRecChk[MAX_PORT];				// 메시지 수신 완료 플래그
	
	CString strPortChk[MAX_PORT];		// 시리얼 포트 생성 정보 저장 변수

	CString strSnd[MAX_PORT];			// 송신 메시지 저장 변수
	CString strRec[MAX_PORT];			// 수신 메시지 저장 변수

	CString strCommSnd[MAX_PORT];		// 리스트 화면 출력 송신 메시지 저장 변수
	CString strCommRec[MAX_PORT];		// 리스트 화면 출력 수신 메시지 저장 변수
	CString strCommErr[MAX_PORT];		// 리스트 화면 출력 에러 메시지 저장 변수

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
// 발생한 알람 관련 데이터 저장 구조체 선언                                      
// *************************************************************************
struct tagALARM_INFO
{
	// **************************************************************************
	// 알람 부위 표시 마크 [출력 위치], [크기], [칼라] 저장 변수                 
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
	// 파일에 저장된 알람 정보 저장 변수                                         
	// **************************************************************************
	CString strEContent[_MAX_ALARM_CNT];  // 파일에서 로딩한 한 라인 정보 저장 변수
	CString strECode[_MAX_ALARM_CNT];     // 알람 코드 저장 변수
	CString strEState[_MAX_ALARM_CNT];    // 알람 상태 저장 변수
	CString strEPart[_MAX_ALARM_CNT];     // 알람 발생 부위 저장 변수
	CString strEMsg[_MAX_ALARM_CNT];      // 공백 제거 알람 메시지 저장 변수
	// **************************************************************************

	// **************************************************************************
	// 화면에 출력할 알람 정보 저장 변수                                         
	// **************************************************************************
	int nActionCnt;            // 출력할 알람 조치 사항 갯수 저장 변수
	CString strStyle;           // 알람 출력 형태 저장 변수
	CString strBmpFile;        // 알람 표시 그림 파일 저장 변수
	CString strRepairMsg;      // 알람 조치 사항 저장 변수
	// **************************************************************************

	CStringList strListJam;		// 발생한 Jam Code의 리스트
	CString strCode;			// 발생한 알람 코드 저장 변수
	CString strPcode;			// 발생한 알람 코드 저장 변수
	CString strCurrMsg;
	CString strCurPart;
	CString strContent;

	int nCountMode;				// 알람 카운트 플래그 (0:알람 카운트 미진행    1:알람 카운트 진행)
	int nTypeMode;				// 알람 종류 저장 변수 (0:경고성    1:진행성    2:장비 정지)

	long stl_cur_alarm_time;	// 알람 발생 시간 저장 변수
	int stl_prev_code;			// 바로 전 발생한 알람 코드 저장 변수
	long stl_prev_alarm_time;	// 바로 전 발생한 알람 발생 시간 저장 변수

	int nAlarmOccured;			// 알람 발생 횟수 저장 변수
	int nAlarmOccuredDay;		// 알람 발생 횟수 저장 변수
	int nArmLotContinue;		// LOT 계속 진행 플래그
	int nResetStatus;			// Alarm Reset Status
	int nSkipMode;
	int nMotorAlarm;			// MOTOR관련 알람은 한번만 발생하도록 하기 위함!!  --> run시도이전엔 다시 울리지 말자!
	int nAlarmAssignSection;	//알람이 발생한 곳을 조금더 쉽게 찾기 위함
	int nCurState;
	int nAlarmClear;
	int nAlarmNum;

	int nAlarmCountClear;			// alarm 정보 clear
};	
extern  tagALARM_INFO  st_alarm_info;
// *************************************************************************

// *************************************************************************
// 알람 데이터 저장 구조체 선언                                                  
// *************************************************************************
struct tagALARM_DISPLAY_INFO
{
	// **************************************************************************
	// 알람 부위 표시 마크 [출력 위치], [크기], [칼라] 저장 변수                 
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
	// 화면에 출력할 알람 정보 저장 변수                                         
	// **************************************************************************
	int nActionCnt;            // 출력할 알람 조치 사항 갯수 저장 변수
	CString strStyle;           // 알람 출력 형태 저장 변수
	CString strBmpFile;        // 알람 표시 그림 파일 저장 변수
	CString strRepairMsg;      // 알람 조치 사항 저장 변수
	// **************************************************************************

	// **************************************************************************
	// 파일에 저장된 알람 정보 저장 변수                                         
	// **************************************************************************
	CString strContent[2000];  // 파일에서 로딩한 한 라인 정보 저장 변수
	CString strCode[2000];     // 알람 코드 저장 변수
	CString strState[2000];    // 알람 상태 저장 변수
	CString strPart[2000];     // 알람 발생 부위 저장 변수
	CString strMsg[2000];      // 공백 제거 알람 메시지 저장 변수
	// **************************************************************************

	// **************************************************************************
	// 현재 발생한 알람 저장 변수                                                
	// **************************************************************************
	int nCurrState;             // 알람 저장 여부 플래그
	CString strCurrMsg;         // 발생한 알람 메시지 저장 변수
	// **************************************************************************
};
extern  tagALARM_DISPLAY_INFO  st_alarm_display_info;


// **********************************************************************************
// 베이직 화면 환경 설정 정보 저장 구조체 선언                                   
// **********************************************************************************
struct tagBASIC_INFO
{
	//int		nModeTesterDisable; //teser 사용유/무(0:tester사용, 1:사용하지 않음(소켓오프여부 보지않음)
	
	int		nCtrlMode;				// [Title Bar 상태 표시] < ONLINE, REMOTE, LOCAL.. 표시	> 
	int		nModeDevice;			// [Title Bar 상태 표시] < WHIT/WHIT OUT ㅡ MODE 표시	>
	int		nModeWork;				// [Title Bar 상태 표시] < 작업 모드 설정 표시			>
	int		nModeXgem;
	int     nRetry;
	int     nModeInterface;
	int		nModeXgemInterface;		// xgem interface [0] off line [1] on line local [2] on line remote.....
	CString strDeviceName;			// [Title Bar 상태 표시] < 장비에서 설정한 DEVICE 표시	>
	CString strModelName;			// [Title Bar 상태 표시] < 비젼에서 설정한 JOB 정보 표시 >

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
// 레시피 화면 환경 설정 정보 저장 구조체 선언                                   
// **********************************************************************************
struct tagRECIPE_INFO
{	
	int nTrayX;
	int nTrayY;

	double dPickGapModuleLoad;
	double dPickGapHeatSinkLeft;
	double dPickGapHeatSinkRight;
	double dTrayDeviceGap;
};
extern tagRECIPE_INFO	st_recipe_info;
// ******************************************************************************

// *****************************************************************************
//  Tower Lamp 화면에 대한 정보 저장 구조체 변수 선언                           
// *****************************************************************************
struct tagLAMP_INFO
{
	int nTFlick;
	int nLampR[9];				// RED 램프 상태 저장 변수
	int nLampY[9];				// YELLOW 램프 상태 저장 변수
	int nLampG[9];				// GREEN 램프 상태 저장 변수
	int nLampB[9];				// GREEN 램프 상태 저장 변수

	int nInterest;				// BLUE 램프 상태 저장 변수

	CString strEquipNo;			// 장비 호기 저장 변수
	CString strEquipCode;		// 장비 코드 저장 변수

	int nBuzzerMode;			// 부저 사용 모드 저장 변수
	int nStatusBuzzerRing;		// 사운드 울리고 있는 상태 변수 
	long lBuzzerOffWait[3];		// 사운드 일정 시간 울리고 멈추도록 하는 변수 

	int nLampWaitTime;			// 램프 FLACKER 시간 저장 변수

	int nModeLampBlue;			// 관심장비 설정 램프 사용여부
	int nModeLampBlueFlicker;	// 관심장비 설정 램프 FLACKER 여부
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

	int i_hs_Front_Ready_stacker_tray_chk; //앞쪽 Tray Check Sensor
	int i_hs_Front_Ready_stacker_updn_pos_chk; //Stacker UpDn Cylinder 위에 Tray 유무 Check

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
	
	int i_hs_Front_Work_stacker_tray_chk; //뒤쪽 Tray Check Sensor
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

	int i_hs_Rear_Ready_stacker_tray_chk; //앞쪽 Tray Check Sensor
	int i_hs_Rear_Ready_stacker_updn_pos_chk; //Stacker UpDn Cylinder 위에 Tray 유무 Check

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

	int i_hs_Rear_Work_stacker_tray_chk; //뒤쪽 Tray Check Sensor
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
// 파일 경로명 저장 구조체 변수 선언                                             
// *************************************************************************
struct tagPATH_INFO
{
	CString strBasic;			// 기본 셋팅 정보 저장 폴더+파일명 설정 변수
	CString strPathDvc;			// 디바이스별 티칭 정보 저장 파일 생성 폴더 설정 변수
	CString strSocket;			// 소켓별...
	CString strPathAlarm;		// 출력 알람 정보 존재 폴더 설정 변수
	CString strPathOp;			// 오퍼레이터 정보 저장 폴더 설정 변수
	CString strPathTray;		// Tray별 정보 저장 파일 생성 폴더 설정 변수
	
	CString strPathFile;		// 파일 생성 폴더 설정 변수
	CString strPathBack;		// BACKUP 파일 생성 폴더 설정 변수

	//kwlee 2017.0511
	CString strPath_Label;
	CString strPath_Model;

	CString strPathRecipe;
	CString strPathFtpGms;		// ftp path 경로.....

	CString strPathRecovery;	// recoverydata........

	CString strFileBasic;		// 기본 셋팅 정보 저장 파일명 설정 변수
	CString strFileWait;		// 대기 시간 정보 저장 파일명 설정 변수
	CString strFileMotor;

	CString strOperation;		//Operation Log 파일 폴더 설정.
	CString strInterface;		//Interface Log 파일 폴더 설정.
	CString strMachine;			//Machine Log 파일 폴더 설정.
	CString strTotal;			//Total Log 파일 폴더 설정.
	CString strData;			//Data Log 파일 폴더 설정.
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

	int		nRemoveInfo[10];		// alarm skip 정보.....
	int		nRemoveYesNo[10];		// alarm skip 유무.....

	int		nLfTsiteBin[2][12];
	int		nRiTsiteBin[2][12];

	int		nBcrX;					// barcode x 좌표.....
	int     nBcrY;					// barcode y 좌표.....
	int		nBdReadyChk;			//


};
extern  tagWORK_INFO  st_work_info;


// *************************************************************************
// 기타 정보 저장 구조체 선언                                                    
// *************************************************************************
struct tagOTHER_INFO
{
	CString strOpMsg;			// 리스트 화면 출력 동작 에러 메시지 저장 변수
	CString strNormalMsg;		// 리스트 화면 출력 동작 에러 메시지 저장 변수
	CString strAbnormalMsg;		// 리스트 화면 출력 동작 에러 메시지 저장 변수
	CString strSndMsg;			// 리스트 화면 테스터 SEND 메시지 저장 변수
	CString strRcvMsg;			// 리스트 화면 테스터 RECIVE 메시지 저장 변수
	CString strBcrRcvMsg;		// 리스트 화면 바코드 RECIVE 메시지 저장 변수
	CString strBoxMsg;

	CString strFallacyMsg;		// 오류 메시지 대화 상자 타이틀 저장 변수
	CString strConfirmMsg;		// 확인 메시지 대화 상자 타이틀 저장 변수
	CString strTypingMsg;		// 키보드 대화 상자 타이틀 저장 변수

	CString strKeypadMsg;		// 키패드 대화 상자 타이틀 저장 변수
	CString strPadVal;			// 키패드 대화 상자에 출력할 데이터 저장 변수

	CString strPadHighLimit;
	CString strPadLowLimit;

	CString strPassLevel;		// 암호 레벨 저장 변수
	CString strPassword;		// 암호 저장 변수
	
	CString strParentMenu;		// 주메뉴 이름 저장 변수

	CString strMsgBuf[10];

	char cNormalMsg[4096];
	char cAbnormalMsg[4096];
	char cOpMsg[4096];

	int nBuzYesNo;				// jtkim 20150410
	int nConfirmMsg;
	int nConfirmType;
	////////////////////////////////2K10/02/09/ViboX////////////////////////////////////////
	int		nPrevStep[100];			// 이전 step (변경 되었는지 보기 위함)
	CString	strHistoryStep[100];		// step_history 약 50개에 해당하는 step을 저장
	CString strLastChangeDate[100];	// 최종 step으로 변경되는 시점의 시간
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


enum TEST_SITE_HIGH_LOW_INFO  //test site high / low 정보 
{
	 TESTSITE_LOW							=  0,
     TESTSITE_HIGH						    , 
};

enum THREAD_SYNC_VARIBLE_SITE_INFO  //위치별 트레이 존재 유무를 위치별로 정의해 놓음  
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
	int			nLotEnd[50];					// lot end flag 상태.....

	int			nInitializeSuccess;
	int         nInit_Flag[50];
	
	int         nShiftWork_Rbt[MAX_BUFFER_SITE];				 //Buffer에서 Robot으로 작업 요청
	//int         nWorkRobot[MAX_WORK_SITE][MAX_WORK_JOB]; //Robot이 Stacker에 요청.
	int         nStacker_Site[MAX_WORK_SITE][MAX_STACKER_POS]; //Stacker에 Robot으로 작업 요청.

	int			nFrontHsRbt;
	int         nFrontHsStacker;

	int			nRearHsRbt;
	int         nRearHsStacker;

};
extern tagSYNC_INFO	st_sync_info;

//kwlee 2017.0529
struct tagPICKER_INFO
{
	int nEnable[MAX_WORK_SITE][MAX_PICKER];
	int nExist[MAX_WORK_SITE][MAX_PICKER];
	int nLastPick[MAX_WORK_SITE];
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
	int			nConnect;		// client 연결상태......
	int			nSendLength;	// 송신 문자 길이......
	int			nRevLength;		// 수신 문자 길이......
	int			nClientReady;	// 데이터 전송중...
	int			nRevInfo;		// client 종료 방법..... (0:바로 1: 수신후)

	char		chRev[8196];	// 수신내용....
	CString     strRev;
	char		chSend[8196];   // 송신내용....
	CString		strSend;
};
extern tagCLIENT_INFO st_client_info[10];

struct tagSERVER_INFO
{
	CString		strIp;			// ip address......
	
	int			nPort;			// port.....
	int			nConnect;		// client 연결상태......
	int			nSendLength;	// 송신 문자 길이......
	int			nRevLength;		// 수신 문자 길이......
	
	char		chRev[8196];	// 수신내용....
	CString     strRev;
	char		chSend[8196];   // 송신내용....
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

#define	BD_READY_CHK_TIME	20		// board ready 명령후 완료체크 시간

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
	LOT_CURR_BACKUP					, //2015.0302 james LOT_CURR을 lot end 시 클리어전에 백업 데이터를 받는다 
};
// lot 정보.....
struct tagLOT_INFO
{
	CString strLotNo;				// lot no......
	CString strPartNo;				// part no......
	CString strProcess;				// process id.....
	CString strProPerty;			// property end....
	CString strBypass;				// bypass.....

	
	int     nLotStatus; //0:clear, 1:set
	int		nLotEnd[THREAD_MAX_SITE]; //해당 사이트 lot end 플레그 


	COleDateTime	tStart;			// jtkim 20150408
};
extern tagLOT_INFO st_lot_info[3]; //2015.0302 james [2] -> [3] 

struct tagCOUNT_INFO
{
	// count 표시하기 위해
	long nInCount[2][2];			// [0][0]:lot 수량, [0][1]:lot 수량 [1][0]:DAILY 수량 
	long nPassCount[2][2];			// 양품수량.....
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
// I/O 동작 대기 시간 및 리미트 시간 저장 구조체 선언                            
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
	

	