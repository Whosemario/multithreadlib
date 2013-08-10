#ifndef EVENT_LOOP_H
#define EVENT_LOOP_H

#include "noncopyable.h"
#include "poller.h"
#include "channel.h"

namespace net{
class EventLoop : multithreads::noncopyable
{
    public:
        EventLoop():mPollTimeout(-1),isRunning(false){}
        EventLoop(int timeout):mPollTimeout(timeout),isRunning(false){}

        void Start(){ isRunning = true; loop();}
        void Stop(){ isRunning = false; }

        void loop();
        void updateChannel(ChannelPtr& channel);

    private:
        Poller poller;
        int mPollTimeout ;
        volatile bool isRunning;
};
}

#endif
