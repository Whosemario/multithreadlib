#include "future.h"

namespace multithreads{

    FutureClass::FutureClass(){
       pthread_cond_init(&cond,NULL);
    }

    FutureClass::~FutureClass(){
        pthread_cond_destroy(&cond);
    }

    void FutureClass::Wait(){
        MutexLockGuard guard(mLock);
        pthread_cond_wait(&cond,&(mLock.mLock));
    }

    void FutureClass::Succeed(){
        MutexLockGuard guard(mLock);
        pthread_cond_signal(&cond);
    }

    void FutureClass::SucceedAll(){
        MutexLockGuard guard(mLock);
        pthread_cond_broadcast(&cond);
    }
}
