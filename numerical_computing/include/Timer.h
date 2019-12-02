//
// Created by zahorack on 12/2/19.
//

#ifndef NUMERICAL_COMPUTING_TIMER_H
#define NUMERICAL_COMPUTING_TIMER_H

#include <chrono>
#include <string>

namespace Time {
enum Enum {
    Seconds = 0,
    Milliseconds,
    Microseconds,
    Nanoseconds,

    Size
};
}

using chrono_t = std::chrono::high_resolution_clock::time_point;


class Timer {

    chrono_t m_startTime, m_stopTime;
    Time::Enum m_timeBase;
    chrono_t measure();
public:
    Timer(Time::Enum);
    ~Timer();

    void start();
    void stop();
    void result();
};

#endif //NUMERICAL_COMPUTING_TIMER_H
