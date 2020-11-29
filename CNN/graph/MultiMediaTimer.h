//MultiMediaTimer.h
// 程序名称：精确到微秒的延时类（基于多媒体定时器）
// 程序编写：yangw80 <yw80@qq.com>
// 最后修改：2011-5-4
//
#ifndef MULTIMEDIATIMER_H
#define MULTIMEDIATIMER_H

#include <windows.h>

class MyTimer
{
private:
	LARGE_INTEGER m_clk;		// 保存时钟信息
	LONGLONG m_oldclk;			// 保存开始时钟和结束时钟
	int m_freq;					// 时钟频率(时钟时间换算率)，时间差

public:
	MyTimer();
	void msSleep(int ms);
	void Reset();
};

#endif	//end of MULTIMEDIATIMER_H
