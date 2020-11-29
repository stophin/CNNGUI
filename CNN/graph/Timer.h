//Timer.h
//
#ifndef TIMER_INCLUDE_H
#define TIMER_INCLUDE_H
#include <windows.h>
#include <math.h>
#pragma comment(lib,"winmm.lib")

//时钟类
class Timer
{
private:
	bool m_bUseLargeTime;				//使用精确时间标志
	__int64 m_int64OneSecondTicks;		//1s内的滴答次数（频率）
	__int64 m_int64TimeTickStartCounts;	//开始的滴答计数值
	unsigned long m_ulTimeStart;		//timeGetTime开始时间
	int m_iFrameCount;					//帧计数
	float m_fFPS;						//FPS帧频
	float m_fTime1,m_fTime2,m_fTimeSlice;//两个时间点及时间差
public:
	Timer();
	~Timer();
	void InitTime();		//初始化时钟
	float GetTime();		//取得运行时间（ms）
	void UpdateFPS();			//更新帧频计数
	inline float GetFPS()		//取得帧频
	{
		return m_fFPS;
	}
};
#endif		//ENGINE_TIMER_H