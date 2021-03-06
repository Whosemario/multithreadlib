#ifndef CHANNEL_H
#define CHANNEL_H

#include <functional>
#include <memory>
#include "global.h"
#include "poll.h"

namespace net{
class Channel{
    public:
        typedef std::function<void()> EventCallback;

        Channel(int fd):mFd(fd){}
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
        void setREvents(short _revents){mRevents = _revents;}

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

typedef std::shared_ptr<Channel> ChannelPtr;
}
#endif
