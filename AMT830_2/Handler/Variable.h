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
#define NW_PCBOX_START_RPY				3
#define NW_PCBOX_END_RPY				4
#define NW_PCBOX_CHANGE_RPY				5
#define NW_ENABLE_RPY					6
#define NW_DISABLE_RPY					7
#define NW_SLOT_MASK_RPY				8
#define NW_LOT_START_ENABLE_RPY			9
#define NW_PCBOX_REMOVE_RPY				10
#define NW_PCBOX_ERROR_RPY				11

#define NW_PCBOX_OFF					12
#define NW_UNLOAD_COMPT					13
#define NW_CANCEL_END					14
#define NW_LOT_END						15
#define NW_PCBOX_DISABLE				16
#define NW_VIDEO_TIMEOUT				17
#define NW_HOLD_TIMEOUT					18
#define NW_PCBOX_LOT_INFO				19
#define NW_FAIL_INFO_SEND				20
#define NW_FAIL_REGNUMBER_REQUEST		21
#define NW_FAIL_INFO_SERACH				22
#define NW_FAIL_INFO_SAVE				23
#define NW_FAIL_INFO_DELETE				24
// ���� �߰� ��.
#define NW_LOT_DISPLAY					25
#define NW_EQP_LOT_START				26
#define NW_EQP_LOT_CANCEL				27
#define NW_EQP_LOT_END					28

// *****************************************************************************
//  ��Ʈ�� �޼��� ���� BPC�ʿ��� ���� ������ �޼���.
// *****************************************************************************
#define NW_LOT_START					29
#define NW_LOT_CANCEL					30
#define NW_PCBOX_START					31
#define NW_PCBOX_END					32
#define NW_PCBOX_CHANGE					33
#define NW_ENABLE						34
#define NW_DISABLE						35
#define NW_SLOT_MASK					36
#define NW_LOT_START_ENABLE				37
#define NW_PCBOX_REMOVE					38
#define NW_PCBOX_ERROR					39

#define NW_PCBOX_LOT_INFO_RPY			40
#define NW_FAIL_INFO_SEND_RPY			41
#define NW_FAIL_REGNUMBER_REQUEST_RPY	42
#define NW_FAIL_INFO_SERACH_RPY			43
#define NW_FAIL_INFO_SAVE_RPY			44
#define NW_FAIL_INFO_DELETE_RPY			45
// ���� �߰� ��
#define NW_LOT_DISPLAY_RPY				46
#define NW_EQP_LOT_START_RPY			47
#define NW_EQP_LOT_CANCEL_RPY			48
#define NW_EQP_LOT_END_RPY				49
// *****************************************************************************

#define NW_PCBOX_ENABLE					50
#define NW_PGM_START					60
//#define NW_FAIL_REGNUMBER_REQUEST		61
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
#define MAIN_LF_INTERFACE_DISPLAY	102 //(left �׽�Ʈ ���� ǥ��)
#define MAIN_RI_INTERFACE_DISPLAY	103 //(right �׽�Ʈ ���� ǥ��)
#define MAIN_LD_PICKER_DISPLAY 		104 //(loader picker ���� ǥ��)
#define MAIN_LD_BUF_PICK_DISPLAY	105 //(loader buffer pick ���� ǥ��)
#define MAIN_LD_BUF_PLACE_DISPLAY	106 //(loader buffer place ����ǥ��)
#define MAIN_LD_TRAY_DISPLAY		107 //(loader tray ����ǥ��)
#define MAIN_UNLD_PICKER_DISPLAY	108 //(unloader picker ���� ǥ��)
#define MAIN_UNLD_BUF_PICK_DISPLAY	109 //(unloader buffer pick ����ǥ��)
#define MAIN_UNLD_BUF_PLACE_DISPLAY	110 //(unloader buffer place ����ǥ��)
#define MAIN_UNLD_TRAY_DISPLAY		111 //(unloader tray ���� ǥ��)
#define MAIN_RETEST_BUF_DISPLAY		112 //(retest buffer ���� ǥ��)
#define MAIN_REJECT_BUF_DISPLAY		113 //(reject buffer ���� ǥ��)
#define MAIN_PCB_TRANS_DISPLAY		114 //(pcb transfer ����ǥ��)
#define MAIN_CONVEYOR_DISPLAY		115 //(conveyor ����ǥ��)
#define MAIN_LOT_DISPLAY			116 //(conveyor ����ǥ��)
#define MAIN_BARCODE_DISPLAY		117 //(conveyor ����ǥ��) // jtkim 20150316

#define MAIN_PCB_INFO				200
#define MAIN_PCB_INFO_BACK			201
#define MAIN_PCB_INFO_NEXT			202

#define MAIN_PCB_PICKER_CREATE_MSG	300
#define MAIN_PCB_PICKER_DELETE_MSG	301
#define MAIN_PCB_BUFFER_CREATE_MSG	302
#define MAIN_PCB_BUFFER_DELETE_MSG	303
#define MAIN_PCB_TRAY_CREATE_MSG	304
#define MAIN_PCB_TRAY_DELETE_MSG	305
#define MAIN_PCB_INTER_CREATE_MSG	306
#define MAIN_PCB_INTER_DELETE_MSG	307

#define MAIN_BD_ERR_CREATE_MSG		400
#define MAIN_BD_ERR_DELETE_MSG		401

#define MAIN_MESSAGE_BOX_CREATE_REQ	100
#define MAIN_MESSAGE_BOX_DELETE_REQ	101

#define MAIN_BARCODE_BOX_CREATE_REQ	110
#define MAIN_BARCODE_BOX_DELETE_REQ	111

#define	MAIN_TRACK_OUT_CREATE_REQ	500
#define	MAIN_TRACK_OUT_DELETE_REQ	501

#define MAIN_LOT_HISTORY_CREATE_REQ 600
#define MAIN_LOT_HISTORY_DELETE_REQ 601

#define MAIN_PCB_DATA_CREATE_REQ	700
#define MAIN_PCB_DATA_DELETE_REQ	701

#define MAIN_NOTICE_CREATE_REQ		800
#define MAIN_NOTICE_DELETE_REQ		801

#define MOTOR_IO_CREATE_REQ			900
#define MOTOR_IO_DELETE_REQ			901

#define MAIN_COK_CREATE_REQ			902

#define MAIN_MESSAGE_VIEW_CREATE_REQ 1000
#define MAIN_MESSAGE_VIEW_DELETE_REQ 1001

#define MAIN_UNLD_CVY_CREATE_REQ	1100
#define MAIN_UNLD_CVY_DELETE_REQ    1101

#define MAIN_SOCKET_COMMENT_CREATE_REQ	1200
#define MAIN_SOCKET_COMMENT_DELETE_REQ	1201

#define ALARM_IO_CREATE_REQ 100
#define ALARM_IO_DELETE_REQ 101
#define ALARM_MOTOR_CREATE_REQ 200
#define ALARM_MOTOR_DELETE_REQ 201

#define INIT_RECOVERY_COMMAND		0
#define INIT_INITIALIZE_COMMAND		1
#define INIT_COK_EXCHANGE_COMMAND	2 //2015.0407 james COK ��ü �۾����� �۾��ڿ��� Ȯ���� �޴´� 
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

//2015.0324 james 
#define SOCKET_CONTACT_ON			100
#define SOCKET_CONTACT_OFF			200
///////////////////////////////////////////////


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
#define BIN_LDBUFFERBIN		1
#define BIN_RETESTBIN		2
#define BIN_GOODBIN			3
#define BIN_REJECTBIN		4
#define BIN_REJECTBIN_1		5
#define BIN_REJECTBIN_2		6
#define BIN_REJECTBIN_3		7
#define BIN_REJECTBIN_4		8

///////////////////
#define RET_NOWHERE			-1000		// �ش� �����Ͱ� �������� ������ 
#define RET_NOSPACE			-2000		// ������ ������ 
#define RET_EMPTYDEVICE		-3000		// ����̽��� ��� ������ 
#define RET_FULLDEVICE		-4000		// ����̽��� FULL
#define RET_LOADTRAYSKIP	-10000		// loader key skip

#define RET_PICKERALLYES 	-5000	// ��Ŀ ������ �����϶� 
#define RET_PICKERALLNO 	-6000	// ��Ŀ ������ �����϶� 
#define RET_PICKERNOTFIND	-7000	// �� �ش��ϴ� ������ ����

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
#define IDW_SCREEN_SET_COK				308
#define IDW_SCREEN_SET_PART_NO			309
#define IDW_SCREEN_IO_FUNCTION			310
#define IDW_SCREEN_TEST_SITE			311

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

// Yasunaga ���� Define
#define Y_INITIALIZE					0//�ʱ�ȭ 0�̿Ϸ�: , 1:�Ϸ����
#define Y_MODELSELECT					1//�� ���� 0:�̿Ϸ�, 1: �Ϸ����
#define Y_RETURNTOORIGIN				2//�������� 0:�̿Ϸ�,1:�Ϸ����
#define Y_AUTOMODE						3//�ڵ� ��� 0:OFF, 1:ON
#define Y_CALIBRATION					4//calibration  0:�̿Ϸ�, 1:�Ϸ����
#define Y_PACKAGEDATA					5//��Ű�� ������0:�̿Ϸ�, 1:�۽ſϷ����
#define Y_AXISDATA						6//�൥����0:�̿Ϸ�, 1: �����Ϸ����

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

	int		nUldGoodTrayStack_Count; //��ε� ���¤�Ŀ�� �����ϴ� ���� ���� (�ܵ� ��� ���� ����)
	int     nPickerErrorSkipMode; //0:��ŵ���� ����, 1:�ڵ����� ��ŵ�ϸ鼭 �̵� 
	int		nCtrlMode;				// [Title Bar ���� ǥ��] < ONLINE, REMOTE, LOCAL.. ǥ��	> 
	int		nModeDevice;			// [Title Bar ���� ǥ��] < WHIT/WHIT OUT �� MODE ǥ��	>
	int		nModeWork;				// [Title Bar ���� ǥ��] < �۾� ��� ���� ǥ��			>
	int		nModeXgem;
	int		nModeInterface;
	int		nModeJigStack;			// unloader jig stack ���.....
	int		nModeRfid;				// rfid �������.....
	int		nModeBarcode;			// barcode read ����....
	int		nModeLdBcr;				// Load Barcode Read ����...
	int		nModeUnLdBcr;			// unloader barcode read ����.....
	int		nRetry;					// retry ����....
	int		nPartialPickCount;
	int		nModeJigLevel;
	int		nModeFrontSmema;
	int		nModeRearSmema;
	int		nModeFtpGms;			// GMS FTP ��������.....
	int		nVnRTime;
	int		nPcbArray;				// ���迭 ����.....
	int		nModeHook;
	int		nModeXgemRunChk;		// 20140806 jtkim..... rcmd check.....
	int		nModeXgemInterface;		// xgem interface [0] off line [1] on line local [2] on line remote.....
	int		nPartNoDgt;
	bool	bEnableFlag;

	CString strDeviceName;			// [Title Bar ���� ǥ��] < ��񿡼� ������ DEVICE ǥ��	>
	CString strModelName;			// [Title Bar ���� ǥ��] < �������� ������ JOB ���� ǥ�� >

	CString strNotice;				// Notice...

	CString	strEqp;					// eqp id.........
	CString strOperID;				// operator id.....
	CString strToolName;			// tool name.....
	CString strFtpUser;				// ftp ����ڸ�......
	CString strFtpPass;				// ftp ��ȣ......
	CString strDevice;
	CString strVnrSpec[2][8];
	CString strVnrUcl[2][8];
	CString strVnrLcl[2][8];

	//2015.0302 ���� �߰��� 
	int		nMp_Docking_Sensor_Disable; //2015.0302 CTL_YES: M/P�� ������ ���� ���·� ���� 
	int		nRotatorBuffer_IDCheck_Sensor_Disable; //2015.0302 CTL_YES: M/P�� ������ ���� ���·� ���� 

	CString strHifixType[10];

	int nLastMdlCount;	// jtkim 20150501 last mdl count....
	int nBcrRead;		// jtkim 20150508
	int nBcrFail;		// jtkim 20150514 ��â�ƾ� ��û

	CString strCodePath;
	// jtkim 20150529
	CString strScrapName;
	CString strScrapHead;

	CString strProcess;	// jtkim 20150623 in-line

	// jtkim 20150721
	int nSocketCount;

	// jtkim 20150930
	int nRecipeYesNo;	// recipe download.....
	int nBarcodeBlock;

	// jtkim 20151229
	int nRetestCount;
} ;
extern  tagBASIC_INFO  st_basic_info;
// ******************************************************************************

// **********************************************************************************
// ������ ȭ�� ȯ�� ���� ���� ���� ����ü ����                                   
// **********************************************************************************
struct tagRECIPE_INFO
{
	int		nTestRetest_Count;
	int		nBufferRotator_TestSite_Degrees; // ld/unld ���� ��� . 0:0��, 1:90��, 2:180��, 3:270�� ���� ���� ���� 
	int		nBufferRotator_PlateSite_Degrees; // ld/uld ���� ��� . ������ 0���� �����̴� 
	int		nFailCnt;						//���� Fail�϶� Socket Off �Ǵ� ī��Ʈ.
	// jtkim 20151017
	int	nBufferRotator_Barcode_Degrees; 
	int Buffer_DvcCheckSensor_Mode;    //���� ����̽�üũ ���� ��� ��/�� 
	int nCOKBuff_IDNum_Type;			////2015.0305 ������ 1�� ���� 4.:2.5" reverse, 3:2.5" Front, 2:Msata, 1:pogo type //���� �۾��� COK ID ����, buffer id�� �����Ѵ�, (COK Buff, Rotator Buff, Test site COK ������ �� ��ȣ�� ���� �����ؾ� �Ѵ� 	

	int nTsiteUse[2][2][12];		// test site socket on/off ����....[0]����(0)/����[1] [0]�ϴ�(0)���(1) [0]SLOT
	int	nTrayY;						// tray Y ����.......
	int nTrayX;						// tray X ����.......

	int nRetestTray_X; //2015.0222 retest tray�� ���� X �������� ����� Ʈ������ ����
	int nRejectTray_X; //2015.0222 reject tray�� ���� X �������� ����� Ʈ������ ����

	int nBufferY;					//buffer y ���� 
	int nBufferX;					//buffer x ����
	int nHifix;						// hifix ��ȣ.....
	int	nAbortTime;					// test timeout......
	int nCokType[4];

	double dTrayPitch_Y;			//Ʈ���� ��ġ���� 
	double dTrayPitch_X;			//Ʈ���� ��ġ���� 
	double dBufferPitch_Y;			//���� ��ġ���� 
	double dBufferPitch_X;			//���� ��ġ���� 
	double dTestPitch_X;			//���� ��ġ���� 

	double dCOKBuffPitch_X;			//COK ���� ��ġ���� 

	//2015.0206 ���͸� X �������� ���� double dLdUldPickerPitch_Y;		//picker pitch 
	double dLdUldPickerPitch_X;		//picker pitch 
	double dTestPickerPitch_X;		//picker pitch 

	double dTrayYOffset;			// tray Y pitch.......
	double dTrayXOffset;			// tray X pitch.......
	double dTSiteOffsetX;			// test site x offset.....

	double dRejTrayPick;			// Reject Tray Pick Offset...
	double dRejTrayPlace;			// Reject Tray Place Offset...

	CString strHifix;				// hifix name.....
	CString strCokTypeName[8];

	bool	bCokChk[8][3];

	BOOL	bUnldBcrFlag[2];		// Unload �� Barcode A, B ������� �÷���

	int		nBcrBank;				// barcode bank......

	double	dTsiteOffsetY[12];	// test site offset y.......

	CString strPartNo;

	// jtkim
	int		nAbortPer;
	int		nIndividualPick;

	double	d15TOffset;
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
	int		i_StartChk;						//PS0000
	int		i_StopChk;						//PS0001
	int		i_AlarmChk;						//PS0002
	int		i_BuzzChk;						//PS0003
	int		i_AutoModeChk;					//PS0004
	int		i_ManualModeChk;				//PS0005
	int		i_FrontSelectSwChk;				//PS0006
	int		i_RearSelectSwChk1;				//PS0007

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
	///////////////////////////////////////////////////////////////////////////////////////////////
	// Module No 02
	///////////////////////////////////////////////////////////////////////////////////////////////
	int		i_Door1Chk;						//PS0200
	int		i_Door2Chk;						//PS0201
	int		i_Door3Chk;						//PS0202
	int		i_Door4Chk;						//PS0203
	int		i_Door5Chk;						//PS0204
	int		i_Door6Chk;						//PS0205
	int		i_Door7Chk;						//PS0206
	int		i_Door8Chk;						//PS0207
	int		i_Door9Chk;						//PS0208
	int		i_Door10Chk;					//PS0209
	int		i_Door11Chk;					//PS0210
	int		i_Door12Chk;					//PS0211
	int		i_Door13Chk;					//PS0212
	int		i_Door14Chk;					//PS0213
	int		i_Door15Chk;					//PS0214	2015.01.29 �߰�.				
	int		i_Door16Chk;					//PS0215	2015.03.17 �߰�.//PS0215
	int		i_DoorChk[18];
	///////////////////////////////////////////////////////////////////////////////////////////////
	// Module No 03
	///////////////////////////////////////////////////////////////////////////////////////////////
	int		o_FrontRequest;					// S0300
	int		o_FrontComplete;				// S0301
	int		o_RearTransfer;					// S0302
	int		o_RearFlipper;					// S0303
	// S0304
	// S0305    
	// S0306    
	int		i_RearSelectSwChk2;				// S0307
	int		i_FrontTransfer;				//PS0300
	int		i_FrontFlipper;					//PS0301
	int		i_RearRequest;					//PS0302
	int		i_RearComplete;					//PS0303
	//PS0304
	//PS0305
	//PS0306
	//PS0307

	///////////////////////////////////////////////////////////////////////////////////////////////
	// Module No 04 //Loading Conveyor
	///////////////////////////////////////////////////////////////////////////////////////////////
	
	// S0404
	
	//PS0409
	//PS0410

	///////////////////////////////////////////////////////////////////////////////////////////////
	// Module No 05	//Loading Plate_1, 2
	///////////////////////////////////////////////////////////////////////////////////////////////
	
	// S0504
	
	//PS0510

	///////////////////////////////////////////////////////////////////////////////////////////////
	// Module No 06  ld index, low empty
	///////////////////////////////////////////////////////////////////////////////////////////////
	
	// S0603
	// S0604
	// S0605
	// S0606
	// S0607
	

	
	//PS0606
	

	///////////////////////////////////////////////////////////////////////////////////////////////
	// Module No 07 load empty tray 
	///////////////////////////////////////////////////////////////////////////////////////////////
	
	///////////////////////////////////////////////////////////////////////////////////////////////
	// Module No 10 unload rail and stacker
	///////////////////////////////////////////////////////////////////////////////////////////////
	
	// S1004
	
	
	///////////////////////////////////////////////////////////////////////////////////////////////
	// Module No 11 unload stacker
	///////////////////////////////////////////////////////////////////////////////////////////////
	
	// S1102
	// S1103
	// S1104
	// S1105
	
	//PS1105	2015.01.29 ����

	//PS1108
	//PS1109
	
	
	///////////////////////////////////////////////////////////////////////////////////////////////
	// Module No 12 move out conveyor
	///////////////////////////////////////////////////////////////////////////////////////////////
	
	// S1202
	// S1203
	// S1204
	// S1205
	
	//PS1209
	
	///////////////////////////////////////////////////////////////////////////////////////////////
	//  Module No 13
	///////////////////////////////////////////////////////////////////////////////////////////////
	
	//PS1307
	
	//PS1315
	
	
	///////////////////////////////////////////////////////////////////////////////////////////////
	// Module No 14
	///////////////////////////////////////////////////////////////////////////////////////////////
	
	// S1403
	// S1404
	// S1405
	// S1406
	// S1407
	
	//PS1405
	
	
	///////////////////////////////////////////////////////////////////////////////////////////////
	//  Module No 15
	///////////////////////////////////////////////////////////////////////////////////////////////
	
	// S1506
	// S1507
	
	///////////////////////////////////////////////////////////////////////////////////////////////
	//  Module No 16
	///////////////////////////////////////////////////////////////////////////////////////////////
	
	// S1614
	
	///////////////////////////////////////////////////////////////////////////////////////////////
	//  Module No 17
	///////////////////////////////////////////////////////////////////////////////////////////////
	
	///////////////////////////////////////////////////////////////////////////////////////////////
	//  Module No 20
	///////////////////////////////////////////////////////////////////////////////////////////////
	
	// S2006
	// S2007
	
	///////////////////////////////////////////////////////////////////////////////////////////////
	//  Module No 21
	///////////////////////////////////////////////////////////////////////////////////////////////
	
	// S2109
	// S2110
	
	//PS2104


	///////////////////////////////////////////////////////////////////////////////////////////////
	//  Module No 22
	///////////////////////////////////////////////////////////////////////////////////////////////

	///////////////////////////////////////////////////////////////////////////////////////////////
	//  Module No 23
	///////////////////////////////////////////////////////////////////////////////////////////////
	
	///////////////////////////////////////////////////////////////////////////////////////////////
	//  Module No 24
	///////////////////////////////////////////////////////////////////////////////////////////////
	
	// S2402	2015.01.29 ����
	// S2403	2015.01.29 ����
	// S2404
	// S2405
	// S2406
	// S2407
	
	//int		i_LfTsiteRiBtmHiFixContactFwdChk;	//PS2406
	
	///////////////////////////////////////////////////////////////////////////////////////////////
	//  Module No 25
	///////////////////////////////////////////////////////////////////////////////////////////////
	
	// S2509
	// S2510
	
	//PS2504

	
	///////////////////////////////////////////////////////////////////////////////////////////////
	//  Module No 26
	///////////////////////////////////////////////////////////////////////////////////////////////
	

	///////////////////////////////////////////////////////////////////////////////////////////////
	//  Module No 27
	///////////////////////////////////////////////////////////////////////////////////////////////
	
	//PS2712
	//PS2713
	//PS2714
	//PS2715

	
	///////////////////////////////////////////////////////////////////////////////////////////////
	//  Module No 30
	///////////////////////////////////////////////////////////////////////////////////////////////
	
	// S3009
	// S3010
	
	// S3004

	
	///////////////////////////////////////////////////////////////////////////////////////////////
	//  Module No 31
	///////////////////////////////////////////////////////////////////////////////////////////////
	
	///////////////////////////////////////////////////////////////////////////////////////////////
	//  Module No 32
	///////////////////////////////////////////////////////////////////////////////////////////////
	
	///////////////////////////////////////////////////////////////////////////////////////////////
	//  Module No 33
	///////////////////////////////////////////////////////////////////////////////////////////////
	
	// S3302	2015.01.29 ����
	// S3303	2015.01.29 ����
	// S3304
	// S3305
	// S3306
	// S3307
	
	//int		i_RiTsiteRiBtmHiFixContactFwdChk;	//PS3306
	
	///////////////////////////////////////////////////////////////////////////////////////////////
	//  Module No 34
	///////////////////////////////////////////////////////////////////////////////////////////////
	
	// S3409
	// S3410
	
	//PS3404


	///////////////////////////////////////////////////////////////////////////////////////////////
	//  Module No 35
	///////////////////////////////////////////////////////////////////////////////////////////////
	
	///////////////////////////////////////////////////////////////////////////////////////////////
	//  Module No 36
	///////////////////////////////////////////////////////////////////////////////////////////////
	
	//PS3612
	//PS3613
	//PS3614
	//PS3615

	
	///////////////////////////////////////////////////////////////////////////////////////////////
	//  Module No 37
	///////////////////////////////////////////////////////////////////////////////////////////////
	
	// S3704
	// S3705
	// S3706
	// S3707
	

	///////////////////////////////////////////////////////////////////////////////////////////////
	//  Module No 40
	///////////////////////////////////////////////////////////////////////////////////////////////
	
	// S4002
	// S4003
	// S4004
	// S4005

	///////////////////////////////////////////////////////////////////////////////////////////////
	//  Module No 41
	///////////////////////////////////////////////////////////////////////////////////////////////
	
	// S4104
	// S4105
	// S4106
	// S4107
	// S4101
	// S4102
	// S4103
	// S4104
	// S4105
	// S4106
	// S4107

	//PS4105
	//PS4106
	//PS4107

	///////////////////////////////////////////////////////////////////////////////////////////////
	//  Module No 42
	///////////////////////////////////////////////////////////////////////////////////////////////
	
	//PS4211

	///////////////////////////////////////////////////////////////////////////////////////////////
	//  Module No 43	2015.01.29 �߰�
	///////////////////////////////////////////////////////////////////////////////////////////////
	// S4301
	// S4302
	// S4303
	// S4304
	// S4305
	// S4306
	// S4307

	///////////////////////////////////////////////////////////////////////////////////////////////
	//  Module No 50
	///////////////////////////////////////////////////////////////////////////////////////////////

	///////////////////////////////////////////////////////////////////////////////////////////////
	//  Module No 51
	///////////////////////////////////////////////////////////////////////////////////////////////
	
	///////////////////////////////////////////////////////////////////////////////////////////////
	//  Module No 52
	///////////////////////////////////////////////////////////////////////////////////////////////
	
	///////////////////////////////////////////////////////////////////////////////////////////////
	//  Module No 53
	///////////////////////////////////////////////////////////////////////////////////////////////
	
	///////////////////////////////////////////////////////////////////////////////////////////////
	//  Module No 54
	///////////////////////////////////////////////////////////////////////////////////////////////

	///////////////////////////////////////////////////////////////////////////////////////////////
	//  Module No 55
	///////////////////////////////////////////////////////////////////////////////////////////////
	
	///////////////////////////////////////////////////////////////////////////////////////////////

	int		i_LoDoorSafetyChk[7];

	///////////////////////////////////////////////////////////////////////////////////////////////
	int		oMotPwr[MAXMOTOR];
};
extern  tagIO_INFO  st_io_info;
// *****************************************************************************

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
	CString strpathLabel;
	CString strpathModel;

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

	CString strTool; // 20140811 jtkim

	// jtkim 20150414
	CString strBarcode;
	CString strBarcodeNg;

	// jtkim 20150607
	CString strPathLotWork;
	CString strPathLotPcb;

	// jtkim 20150721
	CString strPathCycle;

	// jtkim 20160107
	CString strPathTestSite;
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

	int nSocket[3];				// Socket Comment 20150804...
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
	// tray site
	THD_PLATE_CV_LDTRAY_INPUT_SITE		=  0, //ld smema ���ó�� , //2015.0303 james ������� ���� 

	THREAD_MAX_SITE							,
};




//#define LOADTRAY_PALTE_NUM			2
//#define UNLOADTRAY_PLATE_NUM       2

//#define TESTROBOT_INFO_REQ			2	//0:req ����, 1:�۾� ������ġ  

//
//#define MAX_ROBOT_SITE				3 //0:load robot, 1:unload robot, 2:test robot 
//#define PICKER_DATA_INFO			5//[0]:dvc ��/��, [1]:������, [2]:retest cnt, [3]:screen �� ����, [4]:���� ����̽� ��/�� ���� �ӽ� ����, �Ǵ� �������� Ȯ��
//#define MAX_PICKER_PARA				4



struct tagSYNC_INFO
{
	int			nInitializeError;
	int			nLotEnd[50];					// lot end flag ����.....

	int			nInitializeSuccess;
	//2015.0104
	//////////////////////////////////////////////////////////////////////////////////////////////////////
	//������ ó������� ������ ����Ʈ�� DATA_SET, �޴� ����Ʈ�� DATA_CLEAR ������ �����͸� ó���Ѵ� 
	//////////////////////////////////////////////////////////////////////////////////////////////////////
	
	int nTray_Exist_Data[THREAD_MAX_SITE];		//���� ����� 0 ~ 10������ ����� ����
	int nPlate_Tray_Supply_Req[THREAD_MAX_SITE];		//Ʈ���� ����Ʈ�� ld/uld index shift�� ������ ����Ʈ�� �̼��� ��û�ϴ� ���� 
	
	int nSmema_Tray_Input_Req; //lable ��� 
	int nSmema_Tray_Output_Req; //AOI Vision ���

	int nBcrRbtSafetyZ;		// 20150203 jtkim barcode robot z ������ġ Ȯ�� 
	int nLdRbtSafetyZ;
	int nUnLdRbtSafetyZ;
	int nTSiteRbtSafetyZ;

	int nFrontTrayIn;		// front ���񿡼� buffer in data �Ϸ�....

	int nBcrTestStart[4]; //[0]:test start(BD_START)/end(BD_END), [1] :bin ����(good(BD_DATA_GOOD)/reject(BD_DATA_REJECT)������(�ҷ��� retry ��񿡼� ����), [2]:tray Y pos, [3]:tray X pos. 

	//COK Buffer �۾� �����̴� 
	int nCOK_BufferExchange_Req[7]; //[0]:req(�۾� ��û), [1]:pick(0, COK buffer PICK)/place(1, COK Buffer Place), [2]:�۾� ��ġ#1(0~3), [3]:�۾� ��ġ#2(0~3) ===>2�� ������ �����ؾ� ��, [4]:#1�۾� �ϷῩ�� YES/NO, [5]:#2�� �۾��Ϸ� ����, [6]:���� Z �۾� ��ġ  

	////////////////////////////////////////////////////////
	// �Ʒ������� 2015.0225 ���� ���� 
	////////////////////////////////////////////////////////
	int nRejectTransfer_Safety_Flag; 
	int nUnloadRbot_BcrRead_Flag; //unloading Robot ���ڵ� �б� ����� ��� 

	int nUnloadTray_LotEnd_TrayOut_Flag; //2015.0307 lot end�� ��ε� Ʈ���̿� ���簡 �������� ������ ���� ���� �����
	int nUnLdRbtDownZ;	// jtkim 20150608
};
extern tagSYNC_INFO	st_sync_info;


struct tagVARIABLE_INFO
{
	int			nForce_LOTEND;//2015.0224 james ������ lot end�� ����ÿ� ����Ѵ� 
	int			nLotExchange_CurrentLotNum; //0,1 �� ������ ������ 0 -> 1 -> 0 ���� �ݺ� (���� �۾����� lot�� ������ update �ϴ� ��Ȱ�� �� 	

	//2015.0323 
	int n_SocketOff_Seperator_Mode_Flag; //4�� ������ 0 �Ǵ� 2�� ���� ��ġ�� �� �� �ִ�, �� 2�� ������ ���� ����, 1:4���� �����߿��� �ϳ� ������ ���� ���� ����
	
	//2015.0324 james test socket auto socket on/off ó���� ��� 
	int n_Auto_Socket_Open_WorkPos_Num;
	int n_Auto_Socket_Close_WorkPos_Num;
	

	// jtkim 20150826 
	int nPlateFlag;			// unloading plate 1.....
	int nRejectFlag;		// reject stacker....
	int nRetestFlag;		// retest.....
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

struct tagGMS_INFO
{
	CString		strValVolt[MAX_GMS_CHANNEL];
	CString		strValRes[MAX_GMS_CHANNEL];
	CString		strEqpID[MAX_GMS_CHANNEL];
	CString		strDateTime[MAX_GMS_CHANNEL];

	CStringArray	ArValVolt[MAX_GMS_CHANNEL];
	CStringArray	ArValRes[MAX_GMS_CHANNEL];

	COleDateTime oleTime[MAX_GMS_CHANNEL];
};
extern tagGMS_INFO	st_gms_info;

#define RCVR_CLEAR						0
#define RCVR_PICK_UP_COMMAND			1
#define RCVR_PICK_UP_COMPLETE			2
#define RCVR_MOVE_COMMAND				3
#define RCVR_MOVE_COMPLETE				4

#define MOVE_FORWARD					0
#define MOVE_BACKWARD					1

#define LOW_SPEED						0
#define HIGH_SPEED						1

struct	tagRECOVERY_INFO
{
	double	dRecoveryPos[100];	// ������ recovery position......

	int		nRecoveryStep[100];	// recovery step......
	int		nRecoveryFlag[100];	// recovery �Ϸ� ����........
	
	int		nMcRecoveryUsed;
	int		nMcDataRecovery;

	// jtkim �Ǹ��� recovery ����
	int		nRecoveryCyl[100];
};
extern tagRECOVERY_INFO st_recovery_info;

#define MAX_PICKER				4
#define MAX_BUF_ROW_Y				10
#define MAX_BUF_COL_X				10
#define MAX_TRAY_ROW			20
#define MAX_TRAY_COL			20
#define MAX_SITE_PICKER		4
#define MAX_SITE				12

#define LD_ULD_PICKER_PARA			2
#define TEST_PICKER_PARA			4

#define VACUUM_WAIT_TIME			100  //100ms ���� üũ�ð� Ȯ�� 

#define MAX_RETEST_COUNT			5

struct tagPCB_INFO
{
	int nTestBdStart;						//�׽�Ʈ ���۰� ���� �˼� �ִ� 
	int nEnable;							//�ش� ��ġ �����/�� 
	int nYesNo;								// ssd ����.....
	int nBin;								// ssd �׽�Ʈ ���.....
	int nRetestCnt;							// retest �׽�Ʈ Ƚ��......
	int nRetest;
	int	nBinNum;							// ssd �׽�Ʈ ���.....
	int	nRetestSite[MAX_RETEST_COUNT];		// retest ������ site ��ȣ....
	int nBdNum;								// ������ �׽�Ʈ �׽�Ʈ Board ��ȣ.......
	int nScrCode;							// scrap code.....
	int nStatusChang;						// �������� ����.........
	int nOldBin;							// barcode....
	DWORD dwBdTime;							// test time......

	CString strLotNo;						// pcb Lot number.....
	CString strSerialNo;					// Lot���� pcb�� ������ȣ......
	CString strCSerialNo2;
	CString strBarcode;						// pcb 2D barcode......
	CString strPartNo;						// part no.....
	CString strArrNo;						// array serial....
	CString strPPID;						// ppid.....
	CString strPSID;						// psid....
	CString strWWN;							// wwn.....
	CString strCSerialNo;					// c_serial......
	CString strBin;							// strBin......
	// jtkim 20150707
	CString strOldSerial;

	// jtkim 20150805
	CString strComment;

	COleDateTime tStart;					// �׽�Ʈ ���۽ð�...
	// jtkim 20151027
	CTime tStandBy;
	// jtkim 20151028
	int nReworkNg;							// rework mode check......

	// jtkim 20160106
	int nCntInfo;							// count info......

	// jtkim 20160108
	DWORD dwCycle[10];						// log add...
};

///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

struct tag_PICKER_INFO
{
	tagPCB_INFO st_pcb_info[MAX_PICKER]; // pcb ����ü ����.....
};
extern tag_PICKER_INFO st_picker[THREAD_MAX_SITE];

//////////////////////////////////////////////////////////////////////////////////////////////
//2015.0106 ��ü plate�� ����Ʈ�� Ʈ���� ���� ������ �����Ѵ� 
//////////////////////////////////////////////////////////////////////////////////////////////
struct tagALL_TRAY_INFO
{
	int nNewLotIn;            
	int nLastModule;				// ������ �������� üũ
	int nModuleCnt;					// tray �ȿ� �ִ� ������.
	int nTrayExist;					//tray ���� ��/�� �߰� 2015.0226 james
	// jtkim 20150811
	int nReworkMode;				// rework mode......

	//2015.0226 �߰� 
	CString strLotNo;				// lot no......
	CString strPartNo;				// part no......
	CString strProcess;				// process id.....

	// jtkim 2015127
	CTime tStandBy;

	tagPCB_INFO st_pcb_info[MAX_TRAY_ROW][MAX_TRAY_COL]; // pcb ����ü ����..... 
};
extern tagALL_TRAY_INFO st_tray_info[THREAD_MAX_SITE];
extern tagALL_TRAY_INFO st_buffer_info[THREAD_MAX_SITE]; //2015.0114 ������Ʈ ���۶����� �ӽ� ������ ������ ���� Ʈ���� ������ �����Ѵ�  


struct tagREJECT_TRAY_INFO
{
	int nYesNo;				// reject tray ����.....

	tagPCB_INFO st_pcb_info[MAX_TRAY_ROW][MAX_TRAY_COL]; // pcb ����ü ����..... 
};
extern tagREJECT_TRAY_INFO	st_reject_info[THREAD_MAX_SITE];
// test site ����ü
//[0][0] left bottom [0][1] left top [1][0] right bottom [1][1] rigth top
struct tagTEST_SITE_INFO
{
	tagPCB_INFO st_pcb_info[MAX_SITE]; // pcb ����ü ����.....
};
extern tagTEST_SITE_INFO st_test_site_info[THREAD_MAX_SITE][2]; //2015.0216 [2][2];


//2015.0316 james COK
struct tagCOK_INFO
{ 
	int nWorkEnable;						//�ش� ��ġ ��� ��/��, ����ϸ� 1, ������� ������ 0��
	int nCOK_IDNum;							//cok ���� 1~7���� 
	int nYesNo[24];							// cok ����.....	
};

//2015.0316 james COK
struct tagCOKBUFF_SITE_INFO
{
	// jtkim 20150330
	int	nCokCount; // cok ����.......

	tagCOK_INFO st_pcb_info; // pcb ����ü ����.....
};
extern tagCOKBUFF_SITE_INFO st_Cok_Buff_info[4]; //cok 4�� ����Ʈ ���� 



//////////////////////////////////////////////////////////////////////////////////////////////

//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////


struct tagTRACK_INFO
{
	CString	strLotNo;
	CString strPartNo;

	long	nIn;
	long	nPrimePass;
	long	nPrimeReject;
	long	nCumPass;
	long	nCumReject;

	int		nTestEndBin;
	int		nStatus;		// track ����........
};
extern struct tagTRACK_INFO st_track_info;

enum PICKER_PICKPLACE_INFO
{
	 PICKER_PICK_MODE	= 0,
	 PICKER_PLACE_MODE	   ,
};

#define	BD_READY_CHK_TIME	20		// board ready ����� �Ϸ�üũ �ð�

enum BOARD_INFO
{
	BD_NONE							= 0,
	BD_START						,
	BD_END							,
	BD_READY_CHK 					,
	BD_READY_OK						,
	BD_TEST_START_CHK				,
	BD_TEST_START_OK				,
	BD_TEST_BIN_CHK					,
	BD_SLOT_OFF						,
	BD_SLOT_ON						,
	BD_DATA_GOOD					= 200,
	BD_DATA_REJECT					,
	BD_DATA_ABORT					,
	BD_DATA_RETEST					, //2015.0120
	BD_CONT_TIMEOUT					,
	BD_SEND_TIMEOUT					,
	BD_RCV_TIMEOUT					,
	BD_PCB_CHK_TIMEOUT				,
	BD_DATA_ABORT_CHK				, // 20150819
};

// test site board ����
struct tagBOARD_INFO
{
	long nBdTestCnt[12];			// board �׽�Ʈ Ƚ��.....
	long nBdPassCnt[12];			// pass Ƚ��......
	long nBdInfo[12];				// board ����...... 0(Clear) 1(Start) 2.......
	long nBdBin[12];				// board ��� ����...... 
	long nBdFailContiCnt[12];		// ���� fail ����.....

	CString strBinHistory[12];		// jtkim 20150320......
	CString strSocketComment[12];	// Socket Off Comment 20150804
};
extern tagBOARD_INFO st_bd_info[2][2];

enum LOT_INFO
{
	LOT_CURR						= 0,
	LOT_NEXT						,
	LOT_CURR_BACKUP					, //2015.0302 james LOT_CURR�� lot end �� Ŭ�������� ��� �����͸� �޴´� 
};
// lot ����.....
struct tagLOT_INFO
{
	/*
	//////
	//LOT ���� ���� ����, Max 10������ ������ ������ �ÿ��� �ִ� 3�� ������ ���� �����ϰ� �ϰ�, 3�� �̻��϶��� Input smema ����Ʈ���� ����ϰ� ����  
	int			nLotWork_Count; //���� ��� ������ �������� lot�� ����, Max 10������ ������ ������ �ÿ��� �ִ� 3�� ������ ���� �����ϰ� �ϰ�, 3�� �̻��϶��� Input smema ����Ʈ���� ����ϰ� ����  
	int			nLot_LastModule[10]; //�� LOT�� LAST MODULE ����
    CString     strLot_Name[10];     //�� LOT�� NAME
	CString		strCurrent_LotName; //���� ���ʷ� �۾����̴� �ֽ� lot �� ����(nLot_LastModule[0] ��° �迭�� ������ ���ƾ� �Ѵ� )
	*/
	CString strLotNo;				// lot no......
	CString strPartNo;				// part no......
	CString strProcess;				// process id.....
	CString strProPerty;			// property end....
	CString strBypass;				// bypass.....

	
	int     nLotStatus; //0:clear, 1:set
	int		nLotEnd[THREAD_MAX_SITE]; //�ش� ����Ʈ lot end �÷��� 
	int		nNewLotIn;				//[0]Label ��� new lot in , [1]:AOI ��� ����
	int		nLastModule;			// last module....//[0]Label ��� new lot in , [1]:AOI ��� ����
	int		nNewLotComplete;		// new lot check ����.....
	int		nTotalCnt;				// total count....
	int		nLane;					// ......
	int		nLdTrayCnt;				// loading tray ����.....
	int		nUnLdTrayCnt;			// unloading tray 
	int		nBinSortCnt[3];			//0:good, 1:reject, 2:retest ���� //2015.0225 james 
	int		nLdCnt;
	int		nTrayRunMode_StandAlone; //Ʈ���̸� �� �������� �������ʰ� ��ε� ����Ŀ�� �����ϴ� ��� 
	int		nScrapCode;				// scrap code check.....

	COleDateTime	tStart;			// jtkim 20150408

	// jtkim 20160108
	CTime	tLotStart;

	// jtkim 20160124
	int		nAbortTime;
	int		nAbortTotal;
	int		nAbortCount;
	int		nAbortUsed;
};
extern tagLOT_INFO st_lot_info[3]; //2015.0302 james [2] -> [3] 

struct tagANIMATE_INFO
{
	double	dMaxPos[30];		// animate �ִ� pulse.....
	double  dMovePos[30];		// ���� motor pulse .......
	double	dMotorDistance[30];
	double	dMoveOffset[30];

	int		nMoveDistance[30];
	int		nMoveOffset[30];
	int		nImgNum[30];		// image ��ȣ......
	int		nDistance[30];

	bool	bTrayFlag[9];		// Conveyor Assy ���� Tray ǥ�� Flag 0=LdCvyFr 1=LdCvyRe 2=LdRailFr 3=LdRailRe 4=EmptyStk 5=UnldRail 6=UnldElv 7=UnldCvy 8=MvCvy;
};
extern tagANIMATE_INFO st_animate_info;

struct tagCOUNT_INFO
{
	int nCokBufferCount[4]; //cok buffer�� cok ���� ����
	int nPcbQty;
	int nBadPcbQty;
	int	nPcbLotMoveCount[10];		// ���޵� Pcb ����......
	int	nJigCount;					// jig ����......
	int	nPcbLotMove;				// Lot Count.......
	int	nLatestUph[24];				// Uph.......

	int nSSD_Input[2];				//loading tray [0]:lot ����, [1]:DAILY ���� 
	int nTest_Site[2][2][12];		//test site �۾� ���� 
	int nSSD_Output[2][20];			//��ε� �� ���� //[0]:lot ����, [1]:DAILY ���� 

	int nEmptyStackerTray;			//����� Ʈ���� ���� 
	int nUnldStackerTray;			//Ʈ���� ���� 
	int nRejectTray;				// reject tray����....

	// count ǥ���ϱ� ����
	long nInCount[2][2];			// [0][0]:lot ����, [0][1]:lot ���� [1][0]:DAILY ���� 
	long nPassCount[2][2];			// ��ǰ����.....
	long nPrimeCount[2][2];			// nPrimeCount........
	long nRejectCount[2][2];
	// jtkim 20150307
	long nPrimeRejectCount[2][2];

	int nUph;
	int nDailyUph;
	// jtkim 20160106
	int nUphCnt;

	// jtkim 20160111
	int nSocketStart;
	int nSocketOff;
	int nSocketOn;

	double dDailyPer;
	double dHourPer;

	int nHourSocket;
};
extern struct tagCOUNT_INFO st_count_info;


struct tagWORKER_INFO
{
	CString strWorker_Name;
	CString strWorker_Crem;
	CString strWorker_Num;
};
extern struct tagWORKER_INFO st_worker_info;

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
	CString strScrapSerial[1000];
	CString strScrapCode[1000];
	CString strArray[1000];
	
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
	WAIT_STOPPER_UP_DN						= 0,
	
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
	M_BARCODE_X						= 0,
	M_MAX_MOTOR_NUM					, //29
};

enum M_BARCODE_X_POS
{
	P_BARCODE_X_SAFETY				= 0,	
	P_BARCODE_X_TRAY_FIRST			   ,
};

enum M_BARCODE_Y_POS
{
	P_BARCODE_Y_SAFETY				= 0,
	P_BARCODE_Y_TRAY_FIRST			   ,
};

enum M_BARCODE_Z_POS
{
	P_BARCODE_Z_SAFETY				= 0,
	P_BARCODE_Z_WORK				  ,
									
};




enum M_EMPTY_TRAY_ELV_POS
{	
	P_EMPTY_TRAY_ELV_SAFETY		  = 0,//���� ��ġ (down limit ��ġ�ϰ���)
	P_EMPTY_TRAY_ELV_UP_LIMIT			,  //high rail ���� �� Ʈ���� ���� �Ǵ� Ʈ���̸� ������  ���� ���ʱ��� �ø��� üũ
	P_EMPTY_TRAY_ELV_DOWN_LIMIT		,  //���ô� Ʈ���� ���� �� soflEo dncl tkdyd, �Ǵ� ���� �ظ�, Ʈ���� ���� üũ �Ǵ� Full�� ��ü�� �������� 	
	P_EMPTY_TRAY_ELV_SDSENSOR		, //sd sensor ���� ��ġ(Ʈ���̰� ���� �̻� ������ ������. �ϳ��� ������ �������� ���� 	

	//SD ���� ���������� ���� �̵��ϴ� ��ġ 
	P_EMPTY_TRAY_ELV_RAIL_HIGH_SUPPLY_OFFSET	, // SD pos + high Up Ʈ���̸� �����ϴ� 
	P_EMPTY_TRAY_ELV_RAIL_HIGH_RECEIVE_OFFSET	, // SD pos + high Up Ʈ���̸� ����Ʈ���� �޴� ��ġ( �ʱ�ȭ�� Ʈ���̸� ����Ŀ�� ������ ���) 
	P_EMPTY_TRAY_ELV_RAIL_LOW_RECEIVE_OFFSET	, // SD pos + up + Low up Ʈ���̸� �޴� ��ġ, �⺻ ����ġ�� �̰����� ���� �������� ��� �̵��Ѵ� 
	P_EMPTY_TRAY_ELV_REFERENCE_POSITION_OFFSET	, //SD pos - down	��ġ�� �� ������ �۾��ϴ� �������̴�(SD ������ Down�Ͽ� SD�� ���� �ȵǴ� ��ġ�� �۾� �������̴�)

};


enum M_LD_BUFF_Y_POS
{
	P_LD_BUFF_Y_SAFETY				= 0,	
	P_LD_BUFF_Y_PLATE_LOAD			,	
	P_LD_BUFF_Y_TEST_UNLOAD			,	
	P_LD_BUFF_Y_ROTATOR				,
};



enum M_UNLD_BUFF_Y_POS
{
	P_UNLD_BUFF_Y_SAFETY				= 0,	
	P_UNLD_BUFF_Y_TEST_LOAD				,	
	P_UNLD_BUFF_Y_PLATE_UNLOAD			,	
	P_UNLD_BUFF_Y_ROTATOR				,
};





enum M_LD_RBT_X_POS
{
	P_LD_RBT_X_SAFETY				= 0,
	P_LD_RBT_X_LD1TRAY_FIRST		,
	P_LD_RBT_X_LD2TRAY_FIRST		, 
	P_LD_RBT_X_BUFFER_FIRST			, 
	P_LD_RBT_X_RETESTTRAY_FIRST		, 
};

enum M_LD_RBT_Y_POS
{
	P_LD_RBT_Y_SAFETY				= 0,
	P_LD_RBT_Y_LD1TRAY_FIRST		,
	P_LD_RBT_Y_LD2TRAY_FIRST		, 
	P_LD_RBT_Y_BUFFER_FIRST			, 
	P_LD_RBT_Y_RETESTTRAY_FIRST		, 
};

enum M_LD_RBT_Z_POS
{
	P_LD_RBT_Z_SAFETY				= 0,
	P_LD_RBT_Z_LD1TRAY_PICK			,
	P_LD_RBT_Z_LD2TRAY_PICK			,
	P_LD_RBT_Z_BUFFER_PLACE			,
	P_LD_RBT_Z_RETESTTRAY_PICK		,

};

enum M_UNLD_RBT_X_POS
{
	P_UNLD_RBT_X_SAFETY				= 0,
	P_UNLD_RBT_X_ULD1TRAY_FIRST		,
	P_UNLD_RBT_X_ULD2TRAY_FIRST		,
	P_UNLD_RBT_X_BUFFER_FIRST		,
	P_UNLD_RBT_X_REJECT_FIRST		,
	P_UNLD_RBT_X_RETEST_FIRST		,
	P_UNLD_RBT_X_BARCODE_FIRST		,
};

enum M_UNLD_RBT_Y_POS
{
	P_UNLD_RBT_Y_SAFETY				= 0,
	P_UNLD_RBT_Y_ULD1TRAY_FIRST		,
	P_UNLD_RBT_Y_ULD2TRAY_FIRST		,
	P_UNLD_RBT_Y_BUFFER_FIRST		,
	P_UNLD_RBT_Y_REJECT_FIRST		,
	P_UNLD_RBT_Y_RETEST_FIRST		,
	P_UNLD_RBT_Y_BARCODE_FIRST		,
};
enum M_UNLD_RBT_Z_POS
{
	P_UNLD_RBT_Z_SAFETY				= 0,
	P_UNLD_RBT_Z_ULD1TRAY_PLACE		,
	P_UNLD_RBT_Z_ULD2TRAY_PLACE		,
	P_UNLD_RBT_Z_BUFFER_PICK		,
	P_UNLD_RBT_Z_RETESTTRAY_PLACE	,
	P_UNLD_RBT_Z_REJECTTRAY_PLACE	,
	P_UNLD_RBT_Z_BARCODE_READ		,
};

enum M_UNLD_RBT_P_POS
{
	P_UNLD_RBT_P_SAFETY				= 0,
	P_UNLD_RBT_P_TRAY				,
	P_UNLD_RBT_P_BUFFER				,
};


enum M_MVTRAYOUT_CV_X_POS
{
	P_MVOUT_CVY_SAFETY					= 0,
	P_MVOUT_CVY_IN					,
	P_MVOUT_CVY_OUT					,
};


enum RFID_POS
{
	RF_CARRIER_ID					= 0,
	RF_EQP_ID						,
	RF_QTY							,
	RF_QTY_T						,
	RF_LOT_ID_J						, 
	RF_STEP							,
	RF_LOT_TYPE						,
	RF_PART_ID						,
	RF_PKG_CODE						,
	RF_NONE_1						,
	RF_LOT_ID_M						,
	RF_CNT							,
	RF_FLAG							,
	RF_REJECT						,
	RF_BIN							,
	RF_NONE_2						,
	RF_TRAY_QTY						,
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