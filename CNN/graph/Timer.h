//Timer.h
//
#ifndef TIMER_INCLUDE_H
#define TIMER_INCLUDE_H
#include <windows.h>
#include <math.h>
#pragma comment(lib,"winmm.lib")

//ʱ����
class Timer
{
private:
	bool m_bUseLargeTime;				//ʹ�þ�ȷʱ���־
	__int64 m_int64OneSecondTicks;		//1s�ڵĵδ������Ƶ�ʣ�
	__int64 m_int64TimeTickStartCounts;	//��ʼ�ĵδ����ֵ
	unsigned long m_ulTimeStart;		//timeGetTime��ʼʱ��
	int m_iFrameCount;					//֡����
	float m_fFPS;						//FPS֡Ƶ
	float m_fTime1,m_fTime2,m_fTimeSlice;//����ʱ��㼰ʱ���
public:
	Timer();
	~Timer();
	void InitTime();		//��ʼ��ʱ��
	float GetTime();		//ȡ������ʱ�䣨ms��
	void UpdateFPS();			//����֡Ƶ����
	inline float GetFPS()		//ȡ��֡Ƶ
	{
		return m_fFPS;
	}
};
#endif		//ENGINE_TIMER_H