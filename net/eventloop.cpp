#include "eventloop.h"
#include "poll.h"
#include <iostream>

using namespace std;

namespace net{
    void EventLoop::loop(){
        vector<ChannelPtr> activeChannels;
        while(isRunning){

            activeChannels.clear();
            poller.poll(mPollTimeout,activeChannels);

            for(uint32_t i = 0; i<activeChannels.size() ;++i){
                activeChannels[i]->handleEvent();
            }
        }
    }

    void EventLoop::updateChannel(ChannelPtr& channel){
        poller.updateChannel(channel);
    }
}
