//Timer.cpp
//
#include "Timer.h"
//���캯��
Timer::Timer():m_iFrameCount(0),m_fFPS(0),m_fTime1(0),m_fTime2(0),m_fTimeSlice(0)
{
	InitTime();
}

Timer::~Timer()
{
}

//��ʼ��ʱ�ӣ���ͬ��Ӳ���Ͳ���ϵͳ����ʱ���ľ��Ⱥ�Ƶ�ʶ���ͬ����Щ������ʹ�ø߾��ȼ�ʱ�������Ҫʹ��m_bUseLargeTime��������
void Timer::InitTime()
{
	if (QueryPerformanceFrequency((LARGE_INTEGER*)&m_int64OneSecondTicks))
	{
		m_bUseLargeTime=true;
		QueryPerformanceCounter((LARGE_INTEGER*)&m_int64TimeTickStartCounts);
	}
	else
	{
		m_bUseLargeTime=false;
		m_ulTimeStart=timeGetTime();
	}
}

//ȡ����Ϸ�ѽ��е�ʱ��
float Timer::GetTime()
{
	if (m_bUseLargeTime)
	{
		__int64 int64TimeCurrentCounts;
		QueryPerformanceCounter((LARGE_INTEGER*)&int64TimeCurrentCounts);
		return ((float)(int64TimeCurrentCounts-m_int64TimeTickStartCounts)*(1.0f/m_int64OneSecondTicks)*1000.0f);	//sת��Ϊms
	}
	else
	{
		//timeGetTime�ķ���ʱ�䵥λΪms
		return ((float)(timeGetTime()-m_ulTimeStart));
	}
}

//����Ƶ��
void Timer::UpdateFPS()
{
	int fpsCount=5;
	m_iFrameCount++;						//����һ������һ��
	if (m_iFrameCount%fpsCount==1)					//ÿ������Ϊ1����¼��ǰʱ����m_fTime1
		m_fTime1=GetTime()/1000;	//msתs
	else if (m_iFrameCount%fpsCount==0)			//ÿ������Ϊ5����¼��ǰʱ����m_fTime2
	{
		m_fTime2=GetTime()/1000;	//msתs
		m_fTimeSlice=(float)fabs(m_fTime1-m_fTime2);	//����ʱ������
	}
	//����FPS
	m_fFPS=fpsCount/m_fTimeSlice;	//5��֡����m_fTimeSliceʱ��
}

