#include "count_down_latch.h"

namespace multithreads{

    void CountDownLatch::Wait(){
        while(_count > 0){
            _cond.Wait();
        }
    }

    void CountDownLatch::countDown(){
        MutexLockGuard guard(_lock);
        --_count;
        if(_count==0)
            _cond.Succeed();
    }

    uint32_t CountDownLatch::getCount(){
        MutexLockGuard guard(_lock);
        return _count;
    }
}
