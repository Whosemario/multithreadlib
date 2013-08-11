#ifndef TIMER_QUEUE_H
#define TIMER_QUEUE_H

#include "channel.h"
#include "timer_unit.h"
#include <set>
namespace net{
    class EventLoop;
    class TimerQueue{
        public:

            TimerQueue(EventLoop*);

            void AddTimerUnit(const TimerUnit::TimerUnitCallback&,uint64_t expiration,uint64_t interval);

            void HandleTimerUnit();

        private:

            int TimerFdCreate();
            void updateExpiration(uint64_t exp);

            typedef std::pair<uint64_t,TimerUnit*> Entry;
            typedef std::set<Entry> TimerUnitSet;
            int mTimerFd;
            ChannelPtr timerChannel;
            TimerUnitSet timerUnitSet;
    };
}
#endif
