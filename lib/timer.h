#include <string>
using namespace std;

#ifndef TIMER_H
#define TIMER_H

enum State{initial,timing,pausing};

class Timer
{
private:
    int startTicks,pausedTicks;
    bool started,paused;
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
    State state() const;
    string clock() const;
};

#endif
