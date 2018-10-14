#include "Timer.h"
#include "../Core.h"

CTimer::CTimer()
{
}

CTimer::~CTimer()
{
}

bool CTimer::Init()
{
	// 1�ʿ� ó�� ������ tick�� ���´�.
	QueryPerformanceFrequency(&m_tSecond);

	m_fDeltaTime = 0.f;
	m_fFPS = 0.f;
	m_fFPSTime = 0.f;
	m_iFrame = 0;
	m_iFrameLimit = 60;
	m_bStartUpdate = false;

	return true;
}

void CTimer::Update()
{
	if (!m_bStartUpdate)
	{
		m_bStartUpdate = true;
		QueryPerformanceCounter(&m_tPrev);
		return;
	}

	LARGE_INTEGER	tTime;
	QueryPerformanceCounter(&tTime);

	m_fDeltaTime = (tTime.QuadPart - m_tPrev.QuadPart) / (float)m_tSecond.QuadPart;

	m_tPrev = tTime;

	m_fFPSTime += m_fDeltaTime;
	++m_iFrame;

	if (m_iFrame == m_iFrameLimit)
	{
		m_fFPS = m_iFrame / m_fFPSTime;
		m_iFrame = 0;
		m_fFPSTime = 0.f;

		char	str[128] = {};

		sprintf_s(str, "DeltaTime : %f FPS : %f", m_fDeltaTime, m_fFPS);
		SetWindowTextA(WINDOWHANDLE, str);
	}
}

void CTimer::Destroy()
{
	delete	this;
}