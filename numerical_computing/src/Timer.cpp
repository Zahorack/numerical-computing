//
// Created by zahorack on 12/2/19.
//

#include "Timer.h"
#include <iostream>

namespace Time {
    static const std::string Names[Enum::Size] = {"s", "ms", "us", "ns"};
}

Timer::Timer(Time::Enum time):
    m_timeBase(time)
{}

Timer::~Timer()
{}


chrono_t Timer::measure()
{
    return std::chrono::high_resolution_clock::now();
}

void Timer::start()
{
    m_startTime = measure();
}

void Timer::stop()
{
    m_stopTime = measure();
}

void Timer::result()
{
    using namespace std;

    double duration;
    switch(m_timeBase){
        case Time::Seconds:
            duration = (chrono::duration_cast<chrono::seconds>(m_stopTime - m_startTime)).count(); break;
        case Time::Milliseconds:
            duration = (chrono::duration_cast<chrono::milliseconds>(m_stopTime - m_startTime)).count(); break;
        case Time::Microseconds:
            duration = (chrono::duration_cast<chrono::microseconds>(m_stopTime - m_startTime)).count(); break;
        case Time::Nanoseconds:
            duration = (chrono::duration_cast<chrono::nanoseconds>(m_stopTime - m_startTime)).count(); break;
    }
    cout<<"Executing time: "<<duration<<" ["<<Time::Names[m_timeBase]<<"]\n";
}