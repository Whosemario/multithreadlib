#ifndef TIMER_H
#define TIMER_H

#include "global.h"
#include <sys/time.h>
#include <iostream>

namespace multithreads{
    namespace timing{

        typedef uint64_t Timestamp;

        uint64_t GetCurrentTimeInMicroSecond();

        uint64_t GetCurrentTimeInMilliSecond();

        uint64_t GetCurrentTimeInSecond();
    }
}
#endif
