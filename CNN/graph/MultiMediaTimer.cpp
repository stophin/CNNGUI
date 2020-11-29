//MultiMediaTimer.cpp
//
#include "MultiMediaTimer.h"

//class multimediatimer functions
// 构造函数
MyTimer::MyTimer()
{
	QueryPerformanceFrequency(&m_clk);
	m_freq = (int)m_clk.QuadPart / 1000;		// 获得计数器的时钟频率
	m_oldclk = 0;
}

// 延时
void MyTimer::msSleep(int ms)
{
	unsigned int c = ms * m_freq;

	if (m_oldclk == 0)
	{
		// 开始计时
		QueryPerformanceCounter(&m_clk);
		m_oldclk = m_clk.QuadPart;				// 获得开始时钟
	}

	m_oldclk += c;

	QueryPerformanceCounter(&m_clk);

	if (m_clk.QuadPart > m_oldclk)
		m_oldclk = m_clk.QuadPart;
	else
		do
		{
			::Sleep(1);
			QueryPerformanceCounter(&m_clk);	// 获得终止时钟
		}
		while(m_clk.QuadPart < m_oldclk);
}

// 重置延时器
void MyTimer::Reset()
{
	m_oldclk = 0;
}

//end of multimediatimer class functions