//MultiMediaTimer.h
// �������ƣ���ȷ��΢�����ʱ�ࣨ���ڶ�ý�嶨ʱ����
// �����д��yangw80 <yw80@qq.com>
// ����޸ģ�2011-5-4
//
#ifndef MULTIMEDIATIMER_H
#define MULTIMEDIATIMER_H

#include <windows.h>

class MyTimer
{
private:
	LARGE_INTEGER m_clk;		// ����ʱ����Ϣ
	LONGLONG m_oldclk;			// ���濪ʼʱ�Ӻͽ���ʱ��
	int m_freq;					// ʱ��Ƶ��(ʱ��ʱ�任����)��ʱ���

public:
	MyTimer();
	void msSleep(int ms);
	void Reset();
};

#endif	//end of MULTIMEDIATIMER_H
