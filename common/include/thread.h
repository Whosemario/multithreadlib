#ifndef THREAD_H
#define THREAD_H

#include <pthread.h>
#include <tr1/functional>
#include <string>
#include "noncopyable.h"
namespace multithreads{

    class Thread : noncopyable {
        public:
            typedef std::tr1::function<void ()> ThreadFunc;
            explicit Thread(const ThreadFunc& threadFunc, const std::string& name="");
            virtual ~Thread(){mRunning = false;}
            void Start();
            void Join();
        private:
            pthread_t mThread;
            const ThreadFunc mFunc;
            const std::string mName;
            bool mRunning;
    };
}
#endif
