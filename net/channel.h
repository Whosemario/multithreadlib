#ifndef CHANNEL_H
#define CHANNEL_H

#include <tr1/functional>
#include <tr1/memory>
#include "poll.h"

namespace net{
class Channel{
    public:
        typedef std::tr1::function<void()> EventCallback;
        void setReadCallback(EventCallback cb){
            readCallback = cb;
        }
        void setWriteCallback(EventCallback cb){
            writeCallback = cb;
        }
        void handleEvent();

        int getFd(){return mFd;}
        short getEvents(){return mEvents;}
        short getREvents(){return mRevents;}

        void setChannel2Read(){mEvents |= rEvent;}
        void setChannel2Write(){mEvents |= wEvent;}
    private:
        int mFd;
        short mEvents;
        short mRevents;

        EventCallback readCallback;
        EventCallback writeCallback;

        const static short rEvent = POLLIN | POLLPRI;
        const static short wEvent = POLLOUT;
};

typedef std::tr1::shared_ptr<Channel> ChannelPtr;
}
#endif
