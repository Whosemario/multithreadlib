#ifndef TIMER_UNIT_H
#define TIMER_UNIT_H

#include "noncopyable.h"
#include "timer.h"
#include <functional>

namespace net{

    class TimerUnit : public multithreads::noncopyable{

        public:
            typedef std::function<void()> TimerUnitCallback;
            TimerUnit(const TimerUnitCallback& cb,
                    const uint64_t expiration,
                    const uint64_t interval):mCallback(cb),mExpiration(expiration),
                    mInterval(interval),mIsRepeat(false){
                        if(mInterval > 0) mIsRepeat = true;
                    }

            void HandleCallback(){
                if(mCallback) mCallback();
            }

            bool isRepeat(){
                return mIsRepeat ? true : false;
            }

            const uint64_t getInterval(){
                return mInterval;
            }
        private:

            const TimerUnitCallback mCallback;
            const uint64_t mExpiration;
            const uint64_t mInterval;
            bool mIsRepeat;
    };
}
#endif
