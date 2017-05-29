#pragma once
class CRun_Front_HeatSnk_Rbt
{
public:
	CRun_Front_HeatSnk_Rbt(void);
	~CRun_Front_HeatSnk_Rbt(void);
public:
	int m_nInitStep;
	int m_nRunStep;
	int m_nTray_Cnt;
	int	m_nAxisNum_Z;
	int	m_nAxisNum_Y;
	int m_nBufferNum;
	int m_nLastTrayPick;
	int m_nPicker[2];
	double m_dTray_Gap;

	DWORD dwPickerUpDnWaitTime[2][3];
	DWORD dwPickerOnOffWaitTime[2][3];

	
	bool m_bPickerOnOffFlag[2];
	bool m_bPickerUpDnFlag[2];

	CString m_strAlarmCode;

public:
	void ThreadRun();
	void OnRunInit();
	void OnRunMove();

	void OnSetPickerOnOff(int nOnOff,int *nPickerInfo);
	int  OnGetPickerOnOff(int nOnOff,int *nPickerInfo);

	void OnSetPickerUpDn(int nUpDn,int *nPickerInfo);
	int  OnGetPickerUpDn(int nUpDn,int *nPickerInfo);

	int nRobotPickPlace(int nMode, int *nPickerInfo);

	int nWorkBufferPlacePos(int nPos);
};
extern CRun_Front_HeatSnk_Rbt clsRunHsFrontRbt;
