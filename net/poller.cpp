#include "poller.h"
#include <iostream>
using namespace std;
namespace net{
    int Poller::poll(int timeout, ChannelList& activeChannels){
        int numEvents = ::poll(&*mPollList.begin(),mPollList.size(),timeout);
        if(numEvents > 0){
            fillActiveChannel(numEvents,activeChannels);
        }
        return numEvents;
    }

    void Poller::fillActiveChannel(int numEvents, ChannelList& activeChannels){
        for(uint32_t i=0;i<mPollList.size()&&numEvents;i++){
            struct pollfd & pfd = mPollList[i];
            if(pfd.revents > 0){
                --numEvents;
                Fd2ChannelMap::iterator iter = mFd2Channel.find(pfd.fd);
                if(iter != mFd2Channel.end()){
                    iter->second->setREvents(pfd.revents);
                    activeChannels.push_back(iter->second);
                }
            }
        }
    }

    void Poller::updateChannel(ChannelPtr& channel){
        int fd = channel->getFd();
        if(mFd2Channel.find(fd)==mFd2Channel.end()){ // new channel
            struct pollfd pfd;
            pfd.fd = fd;
            pfd.events = channel->getEvents();
            pfd.revents = 0;
            mPollList.push_back(pfd);
            mFd2Channel.insert(make_pair(fd,channel));
            mFd2Index.insert(make_pair(fd,mPollList.size()-1));
        }
        else{  // update channel
            uint32_t index = mFd2Index[fd];
            mPollList[index].fd = channel->getFd();
            mPollList[index].events = channel->getEvents();
            mFd2Channel[fd] = channel;
        }
    }
}
