#ifndef EVENT_LOOP_H
#define EVENT_LOOP_H

#include "noncopyable.h"
#include "poller.h"
#include "channel.h"
#include "timer_queue.h"

namespace net{
class EventLoop : multithreads::noncopyable
{
    public:
        EventLoop():mPollTimeout(-1),isRunning(false),mTimerQueue(this){}
        EventLoop(int timeout):mPollTimeout(timeout),isRunning(false),mTimerQueue(this){}

        void Start(){ isRunning = true; loop();}
        void Stop(){ isRunning = false; }

        void loop();
        void updateChannel(ChannelPtr& channel);

        /* time is ms */
        void runAt(uint64_t time, const TimerUnit::TimerUnitCallback& cb){
            mTimerQueue.AddTimerUnit(cb,time*1000,0);
        }

    private:
        Poller poller;
        int mPollTimeout ;
        volatile bool isRunning;
        TimerQueue mTimerQueue;
};
}

#endif
