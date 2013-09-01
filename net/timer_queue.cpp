#include "timer_queue.h"
#include "eventloop.h"
#include <sys/timerfd.h>
#include <functional>
#include <string.h>
#include <unistd.h>
#include "global.h"

using namespace std;
using namespace net;
using namespace multithreads;

TimerQueue::TimerQueue(EventLoop* evtLoop):
    mTimerFd(TimerFdCreate()),timerChannel(new Channel(mTimerFd)){
        timerChannel->setChannel2Read();
        timerChannel->setReadCallback(
                bind(&TimerQueue::HandleTimerUnit,this));
        evtLoop->updateChannel(timerChannel);
    }

int TimerQueue::TimerFdCreate(){
    int ret = timerfd_create(CLOCK_MONOTONIC,
            TFD_NONBLOCK|TFD_CLOEXEC);

    return ret;
}

void TimerQueue::HandleTimerUnit(){

    //read
    uint64_t buf;
    int len = ::read(mTimerFd,(void *)&buf,sizeof(buf));
    if(len < sizeof(buf)) cerr << "Read Less" <<endl;

    uint64_t now = timing::GetCurrentTimeInMicroSecond();

    TimerUnitSet::iterator iter = timerUnitSet.lower_bound(make_pair(now,reinterpret_cast<TimerUnit*>(UINTPTR_MAX)));
    vector<TimerUnit*> timers;
    for(TimerUnitSet::iterator it = timerUnitSet.begin();it != iter ;++it)
        timers.push_back(it->second);
    timerUnitSet.erase(timerUnitSet.begin(),iter);

    for(int i=0; i<timers.size(); ++i) timers[i]->HandleCallback();

    //FIXME
    for(int i=0;i<timers.size();++i) delete timers[i];
}

void TimerQueue::AddTimerUnit(const TimerUnit::TimerUnitCallback& callback,
        uint64_t expiration, uint64_t interval){
    TimerUnit* tp = new TimerUnit(callback,expiration,interval);
    if(timerUnitSet.size()==0 ||
            timerUnitSet.begin()->first<=expiration){
        timerUnitSet.insert(make_pair(expiration,tp));
    }
    else{
        timerUnitSet.insert(make_pair(expiration,tp));
        updateExpiration(expiration);
    }
}

void TimerQueue::updateExpiration(uint64_t exp){
    uint64_t offset = exp - timing::GetCurrentTimeInMicroSecond();
    struct itimerspec val;
    bzero(&val, sizeof(val));
    val.it_value.tv_sec = offset/1000000;
    val.it_value.tv_nsec = offset%1000000*1000;
    timerfd_settime(mTimerFd,0,&val,NULL);
}
