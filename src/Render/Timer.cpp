#include "pch.h"
#include "Timer.h"


Timer::Timer() { Reset(); }


float32 Timer::GetDeltaTime() const { return m_deltaTime.count(); }

float32 Timer::GetTimeScale() const { return m_timeScale; }


void Timer::SetTimeScale( float32 const timeScale ) { m_timeScale = timeScale; }



void Timer::Reset() { m_startTime = std::chrono::system_clock::now(); }

void Timer::Tick()
{
    m_deltaTime = std::chrono::system_clock::now() - m_startTime;
}
