// �������ƣ���ȷ��΢�����ʱ�ࣨ���ڶ�ý�嶨ʱ����

#pragma once
#include <windows.h>

class MyTimer
{
private:
	LARGE_INTEGER m_clk;
	
	// ����ʱ����Ϣ
	LONGLONG m_oldclk;
	
	
	// ���濪ʼʱ�Ӻͽ���ʱ��
	int m_freq;
	
	
	
	
	// ʱ��Ƶ��(ʱ��ʱ�任����)��ʱ���

public:
	MyTimer();
	void Sleep(int ms);
	void Reset();
};

// ���캯��
MyTimer::MyTimer()
{
	QueryPerformanceFrequency(&m_clk);
	m_freq = (int)m_clk.QuadPart / 1000;
	
	// ��ü�������ʱ��Ƶ��
	m_oldclk = 0;
}

// ��ʱ
void MyTimer::Sleep(int ms)
{
	unsigned int c = ms * m_freq;

	if (m_oldclk == 0)
	{
	
	// ��ʼ��ʱ
	
	QueryPerformanceCounter(&m_clk);
	
	m_oldclk = m_clk.QuadPart;
	
	
	
	// ��ÿ�ʼʱ��
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
	// �����ֹʱ��
	
	}
	
	while(m_clk.QuadPart < m_oldclk);
}

// ������ʱ��
void MyTimer::Reset()
{
	m_oldclk = 0;
}


//��γ�����һ��ʵ�־�ȷ��ʱ���࣬
// ���� Windows ƽ̨�µĶ�ý�嶨ʱ����QueryPerformanceCounter �� QueryPerformanceFrequency ��������
// ������Ҫ�������ṩһ����ʱ���ܣ��������Ժ���Ϊ��λ��ȷ�ؿ��Ƴ���ִ�е�ʱ������

//����γ������ͷ�ļ��е���ҪĿ���ǽ���������Ͷ�����룬�Ա�������Դ�ļ����ܹ���������ú�ʹ�ø��ࡣ