#ifndef FUTURE_H
#define FUTURE_H

#include <tr1/memory>
#include <pthread.h>
#include "mutex.h"
#include "noncopyable.h"
namespace multithreads{

    class FutureClass : public noncopyable {
        public:
            FutureClass();
            virtual ~FutureClass();
            void Wait();
            void Succeed();
            void SucceedAll();
        private:
            MutexLock mLock;
            pthread_cond_t cond;
    };

    typedef std::tr1::shared_ptr<FutureClass> FuturePtr;
}

#endif
