#define __USE_MINGW_ANSI_STDIO 0 //在minGW下，stdio.h和libmingwex.a會打架，這行禁用他們的definition

#include "timer.h"

Timer::Timer():startTicks(0),pausedTicks(0),started(false),paused(false)
{}

void Timer::start()
{
    started=true;
    paused =false;
    startTicks=SDL_GetTicks();
}

void Timer::stop()
{
    started=false;
    paused =false;
}

void Timer::pause()
{
    if (started && !paused) //如果根本還沒開始，那就完全不用暫停
    {
        paused=true;
        pausedTicks=SDL_GetTicks()-startTicks;
    }
}

void Timer::resume()
{
    if (paused)
    {
        paused=false;
        startTicks=SDL_GetTicks()-pausedTicks;
        pausedTicks=0;
    }
}

Uint32 Timer::restart()
{
    start();
    return ticks();
}

Uint32 Timer::ticks() const
{
    if (started)
    {
        if (paused)
            return pausedTicks;
        else
            return SDL_GetTicks()-startTicks;
    }
    return 0;
}

State Timer::state() const
{
    if(started && !paused) //開始了而且沒有暫停正在計時
        return timing;
    else if(started && paused) //開始了但暫停
        return pausing;
    return initial; //根本沒開始
}

std::string Timer::clock() const //ticks是毫秒
{
    int tickNum=ticks();
    if(tickNum>=60*1000) //大於一分鐘的話
        tickNum=tickNum/(60*1000)*100000+tickNum%(60*1000);
    if(tickNum>=60*100000) //大於一小時的話，注意這裡不是60*60*1000因為上一步驟已經分鐘的部分轉為十進位
        tickNum=tickNum/(60*100000)*10000000+tickNum%(60*100000);

    std::string clockStr=std::to_string(tickNum);

    if(clockStr.size()>3)
        clockStr.insert(clockStr.size()-3,".");
    if(clockStr.size()>6) //如果需要用到分鐘了(要考慮上一步加的「點」，所以加上「分鐘」2位，共多3個字元的長度)
        clockStr.insert(clockStr.size()-6,":");
    if(clockStr.size()>9)
        clockStr.insert(clockStr.size()-9,":");
    return clockStr;
}
