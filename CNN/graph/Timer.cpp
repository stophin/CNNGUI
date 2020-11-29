//Timer.cpp
//
#include "Timer.h"
//构造函数
Timer::Timer():m_iFrameCount(0),m_fFPS(0),m_fTime1(0),m_fTime2(0),m_fTimeSlice(0)
{
	InitTime();
}

Timer::~Timer()
{
}

//初始化时钟，不同的硬件和操作系统，定时器的精度和频率都不同，有些还不能使用高精度计时器，因此要使用m_bUseLargeTime加以区分
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

//取得游戏已进行的时间
float Timer::GetTime()
{
	if (m_bUseLargeTime)
	{
		__int64 int64TimeCurrentCounts;
		QueryPerformanceCounter((LARGE_INTEGER*)&int64TimeCurrentCounts);
		return ((float)(int64TimeCurrentCounts-m_int64TimeTickStartCounts)*(1.0f/m_int64OneSecondTicks)*1000.0f);	//s转换为ms
	}
	else
	{
		//timeGetTime的返回时间单位为ms
		return ((float)(timeGetTime()-m_ulTimeStart));
	}
}

//更新频率
void Timer::UpdateFPS()
{
	int fpsCount=5;
	m_iFrameCount++;						//调用一次增加一次
	if (m_iFrameCount%fpsCount==1)					//每当余数为1，记录当前时间如m_fTime1
		m_fTime1=GetTime()/1000;	//ms转s
	else if (m_iFrameCount%fpsCount==0)			//每当余数为5，记录当前时间入m_fTime2
	{
		m_fTime2=GetTime()/1000;	//ms转s
		m_fTimeSlice=(float)fabs(m_fTime1-m_fTime2);	//计算时间差，正数
	}
	//更新FPS
	m_fFPS=fpsCount/m_fTimeSlice;	//5个帧用了m_fTimeSlice时间
}

