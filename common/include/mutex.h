#ifndef MUTEX_H
#define MUTEX_H

#include <iostream>
#include <pthread.h>
#include <assert.h>
#include <cstring>
#include <errno.h>
#include <sys/time.h>
#include "noncopyable.h"

#define MULTITHREADS_LOCK_SAFE(x) \
    do{ \
        int r = (x); \
        if(r){ \
            int e = errno; \
            std::cerr << "MULTITHREADS_LOCK_SAFE abort at " << __FILE__ << ":" << __LINE__ << " in " << \
                __FUNCTION__ << std::endl << "Ret: " << r <<" errno: " << e << " (" << strerror(e) << ") " << std::endl; \
        } \
    }while(false)

namespace multithreads{
    /* invoke lock */
    class MutexLock : public noncopyable{
        friend class FutureClass;
        public:
            MutexLock(){
                MULTITHREADS_LOCK_SAFE(pthread_mutex_init(&mLock,NULL));
            }

            ~MutexLock(){
                MULTITHREADS_LOCK_SAFE(pthread_mutex_destroy(&mLock));
            }

            void lock(){
                MULTITHREADS_LOCK_SAFE(pthread_mutex_lock(&mLock));
            }

            void unlock(){
                MULTITHREADS_LOCK_SAFE(pthread_mutex_unlock(&mLock));
            }

            pthread_mutex_t&  get_origin_mutex() const {
                return mLock;
            }
        private:
            mutable pthread_mutex_t mLock;
    };

    class MutexLockGuard : public noncopyable{
        public:
            MutexLockGuard(MutexLock& lock):mLock(lock){
                mLock.lock();
            }

            ~MutexLockGuard(){
                mLock.unlock();
            }

        private:
            MutexLock& mLock;
    };

    /* thread lock */
    class PTRecursiveMutex : public noncopyable{
        public:
            PTRecursiveMutex(){
                pthread_mutexattr_t mta;
                MULTITHREADS_LOCK_SAFE(pthread_mutexattr_init(&mta));
                MULTITHREADS_LOCK_SAFE(pthread_mutexattr_settype(&mta,PTHREAD_MUTEX_RECURSIVE));
                MULTITHREADS_LOCK_SAFE(pthread_mutex_init(&_lock,&mta));
                MULTITHREADS_LOCK_SAFE(pthread_mutexattr_destroy(&mta));
            }

            ~PTRecursiveMutex(){
                MULTITHREADS_LOCK_SAFE(pthread_mutex_destroy(&_lock));
            }

            void lock(){
                MULTITHREADS_LOCK_SAFE(pthread_mutex_lock(&_lock));
            }

            void unlock(){
                MULTITHREADS_LOCK_SAFE(pthread_mutex_unlock(&_lock));
            }

            pthread_mutex_t& get_origin_mutex() const {
                return _lock;
            }
        private:
            mutable pthread_mutex_t _lock;
    };
    typedef PTRecursiveMutex PTMutexLock;

    class PTMutexLockGuard : public noncopyable{
        public:
            PTMutexLockGuard(PTMutexLock& lock):_lock(lock){
                _lock.lock();
            }

            ~PTMutexLockGuard(){
                _lock.unlock();
            }
        private:
            PTMutexLock& _lock;
    };

    class PTCond : public noncopyable{
        public:
            PTCond(){
                MULTITHREADS_LOCK_SAFE(pthread_cond_init(&_cond,NULL));
            }

            ~PTCond(){
                MULTITHREADS_LOCK_SAFE(pthread_cond_destroy(&_cond));
            }

            void signal(){
                MULTITHREADS_LOCK_SAFE(pthread_cond_signal(&_cond));
            }

            void broadcast(){
                MULTITHREADS_LOCK_SAFE(pthread_cond_broadcast(&_cond));
            }

            int wait(const PTMutexLock& lock, int64_t usec = -1){

                int ret = 0;

                if(usec == -1){
                    ret = pthread_cond_wait(&_cond,&lock.get_origin_mutex());
                }
                else{
                    if(usec < 0){
                        std::cerr << "usec is less than zero" << std::endl;
                        return -1;
                    }
                    struct timeval tv;
                    struct timespec ts;
                    gettimeofday(&tv,NULL);

#define MICROSECONDS_PER_SECOND 1000000
#define NANOSECONDS_PER_MICROSECONDS 1000

                    ts.tv_sec = tv.tv_sec + usec/MICROSECONDS_PER_SECOND;
                    int64_t tmp = tv.tv_usec + usec%MICROSECONDS_PER_SECOND;
                    ts.tv_sec += tmp/MICROSECONDS_PER_SECOND;
                    ts.tv_nsec = tmp%MICROSECONDS_PER_SECOND*NANOSECONDS_PER_MICROSECONDS;

                    ret = pthread_cond_timedwait(&_cond,&lock.get_origin_mutex(),&ts);
                }

                return ret;
            }

            pthread_cond_t& get_origin_cond(){
                return _cond;
            }
        private:
            pthread_cond_t _cond;
    };
}

#endif
