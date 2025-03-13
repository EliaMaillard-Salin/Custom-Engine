#ifndef RENDER_TIMER_H_INCLUDED
#define RENDER_TIMER_H_INCLUDED

#include "define.h"

#include <chrono>


class Timer
{
public:
    Timer();
    ~Timer() = default;

    [[nodiscard]] float32 GetDeltaTime() const;
    // [[nodiscard]] float32 GetFixedDeltaTime() const;

    [[nodiscard]] float32 GetTotalTime() const;
    [[nodiscard]] float32 GetTimeScale() const;

    void SetTimeScale( float32 timeScale );

    void Reset(); // Call before message loop.
    // void Start(); // Call when unpaused.
    void Tick();  // Call every frame.
    // void Stop();  // Call when paused.

private:
    float32 m_timeScale = 1.0f;

    std::chrono::system_clock::time_point m_startTime;
    std::chrono::duration<float32> m_deltaTime = std::chrono::duration<float32>( 0.0f );
    
    // float32 m_secondsPerCount = 0.0f;
    //
    // uint32 m_baseTime = 0;
    // uint32 m_pausedTime = 0;
    // uint32 m_stopTime = 0;
    // uint32 m_previousTime = 0;
    // uint32 m_currentTime = 0;
};


#endif