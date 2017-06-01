#pragma once

class CRun_Rear_HeatSnk_Stacker : public CObject
{
public:
	CRun_Rear_HeatSnk_Stacker();
	virtual ~CRun_Rear_HeatSnk_Stacker();

public:
	void ThreadRun();
	void OnRunInit();

	//kwlee 2017.0601
	void OnReadyStackerMove();
	void OnWorkStackerMove();

	//Ready Pos
	void OnSet_ReadyPos_StackerCylUpDn(int nUpDn);
	int  OnGet_ReadyPos_StackerCylUpDn(int nUpDn);

	void OnSet_ReadyPos_RailFwdBwdCyl(int nOnOff);
	int OnGet_ReadyPos_RailFwdBwdCyl(int nOnOff);

	void OnSet_ReadyPos_TrayClampCyl(int nOnOff);
	int OnGet_ReadyPos_TrayClampCyl(int nOnOff);

	void  OnSet_PusherFwdBwdCyl(int nOnOff);
	int  OnGet_PusherFwdBwdCyl(int nOnOff);

	//Work Pos 
	void OnSet_WorkPos_StackerCylUpDn(int nUpDn);
	int  OnGet_WorkPos_StackerCylUpDn(int nUpDn);

	void OnSet_WorkPos_RailFwdBwdCyl(int nOnOff);
	int OnGet_WorkPos_RailFwdBwdCyl(int nOnOff);

	void OnSet_WorkPos_TrayClampCyl(int nOnOff);
	int OnGet_WorkPos_TrayClampCyl(int nOnOff);

	void  OnSet_SeperateFwdBwdCyl(int nOnOff);
	int  OnGet_SeperateFwdBwdCyl(int nOnOff);

public:
	int m_nInitStep;
	int m_nRunStep;

	int m_nRunWorkstackerStep;
	bool m_bWork_StackerPos_Req;

	int m_nAxisNum_Ready;
	int	m_nAxisNum_Work; 
	int m_nAxisNum_Move;

	CString m_strCode;

	bool m_bCylinderFlag[10];
	DWORD m_dwCylWaitTime[10][3];	
};
extern CRun_Rear_HeatSnk_Stacker clsRunHsRearStacker;

