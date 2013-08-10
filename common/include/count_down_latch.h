#ifndef COUNT_DOWN_LATCH_H
#define COUNT_DOWN_LATCH_H

#include "mutex.h"
#include "future.h"
#include "noncopyable.h"

namespace multithreads{

    class CountDownLatch : public noncopyable{
        public:
            CountDownLatch(uint32_t count):_count(count){}
            void Wait();
            void countDown();
            uint32_t getCount();
        private:
            MutexLock _lock;
            FutureClass _cond;
            uint32_t _count;
    };
}
#endif
