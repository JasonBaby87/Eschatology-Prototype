#include <string>
using namespace std;

#ifndef TIMER_H
#define TIMER_H

class Timer
{
public:
    Timer();
    void start();
    void stop();
    void pause();
    void resume();
    //@return 逝去的時間
    int restart();
    //@return 逝去的時間
    int ticks() const;
    ///Check if Timer is started
    int state() const;
    string clock() const;

private:
    int startTicks,pausedTicks;
    bool started,paused;
};

#endif
