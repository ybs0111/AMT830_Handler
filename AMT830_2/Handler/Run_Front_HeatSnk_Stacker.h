#pragma once
class CRun_Front_HeatSnk_Stacker
{
public:
	CRun_Front_HeatSnk_Stacker(void);
	~CRun_Front_HeatSnk_Stacker(void);

public:
	void ThreadRun();
	void OnRunInit();
	void OnRunMove();

	//Ready Pos
	void OnSet_ReadyPos_StackerCylUpDn(int nUpDn);
	int  OnGet_ReadyPos_StackerCylUpDn(int nUpDn);
	
	void OnSet_ReadyPos_RailFwdBwdCyl(int nOnOff);
	int OnGet_ReadyPos_RailFwdBwdCyl(int nOnOff);

	void OnSet_ReadyPos_TrayClampCyl(int nOnOff);
	int OnGet_ReadyPos_TrayClampCyl(int nOnOff);

	void  OnSetPusherFwdBwdCyl(int nOnOff);
	int  OnGetPusherFwdBwdCyl(int nOnOff);

	//Work Pos 
	void OnSet_WorkPos_StackerCylUpDn(int nUpDn);
	int  OnGet_WorkPos_StackerCylUpDn(int nUpDn);

	void OnSet_WorkPos_RailFwdBwdCyl(int nOnOff);
	int OnGet_WorkPos_RailFwdBwdCyl(int nOnOff);

	void OnSet_WorkPos_TrayClampCyl(int nOnOff);
	int OnGet_WorkPos_TrayClampCyl(int nOnOff);

	void  OnSetSeperateFwdBwdCyl(int nOnOff);
	int  OnGetSeperateFwdBwdCyl(int nOnOff);
	

public:
	int m_nInitStep;
	int m_nRunStep;
	int m_nAxisNum_Ready;
	int	m_nAxisNum_Work; 
	int m_nAxisNum_Move;
	
	bool m_bCylinderFlag[10];
	DWORD m_dwCylWaitTime[10][3];

	CString m_strCode;
};
extern CRun_Front_HeatSnk_Stacker clsRunHsFrontStacker;
