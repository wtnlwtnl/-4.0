// 程序名称：精确到微秒的延时类（基于多媒体定时器）

#pragma once
#include <windows.h>

class MyTimer
{
private:
	LARGE_INTEGER m_clk;
	
	// 保存时钟信息
	LONGLONG m_oldclk;
	
	
	// 保存开始时钟和结束时钟
	int m_freq;
	
	
	
	
	// 时钟频率(时钟时间换算率)，时间差

public:
	MyTimer();
	void Sleep(int ms);
	void Reset();
};

// 构造函数
MyTimer::MyTimer()
{
	QueryPerformanceFrequency(&m_clk);
	m_freq = (int)m_clk.QuadPart / 1000;
	
	// 获得计数器的时钟频率
	m_oldclk = 0;
}

// 延时
void MyTimer::Sleep(int ms)
{
	unsigned int c = ms * m_freq;

	if (m_oldclk == 0)
	{
	
	// 开始计时
	
	QueryPerformanceCounter(&m_clk);
	
	m_oldclk = m_clk.QuadPart;
	
	
	
	// 获得开始时钟
	}

	m_oldclk += c;

	QueryPerformanceCounter(&m_clk);

	if (m_clk.QuadPart > m_oldclk)
	
	m_oldclk = m_clk.QuadPart;
	else
	
	do
	
	{
	
	
	::Sleep(1);
	
	
	QueryPerformanceCounter(&m_clk);
	// 获得终止时钟
	
	}
	
	while(m_clk.QuadPart < m_oldclk);
}

// 重置延时器
void MyTimer::Reset()
{
	m_oldclk = 0;
}


//这段程序是一个实现精确延时的类，
// 基于 Windows 平台下的多媒体定时器（QueryPerformanceCounter 和 QueryPerformanceFrequency 函数）。
// 它的主要作用是提供一个延时功能，允许你以毫秒为单位精确地控制程序执行的时间间隔。

//将这段程序放在头文件中的主要目的是将类的声明和定义分离，以便在其他源文件中能够方便地引用和使用该类。