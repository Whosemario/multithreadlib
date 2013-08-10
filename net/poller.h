#ifndef POLLER_H
#define POLLER_H

#include <map>
#include <vector>
#include <poll.h>
#include "global.h"
#include "channel.h"
namespace net{

class Poller{
    public:
        typedef std::vector<ChannelPtr> ChannelList;
        int poll(int timeout, ChannelList& activeChannels);
        void updateChannel(ChannelPtr& channel);

    private:

        void fillActiveChannel(int numEvents, ChannelList& activeChannels);

        typedef std::vector<struct pollfd> PollFdList;
        typedef std::map<int , ChannelPtr> Fd2ChannelMap;
        typedef std::map<int, uint32_t> Fd2IndexMap;

        PollFdList mPollList;
        Fd2ChannelMap mFd2Channel;
        Fd2IndexMap mFd2Index;
};
}
#endif
