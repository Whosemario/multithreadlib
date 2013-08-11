#include "timer.h"

using namespace multithreads;


        uint64_t timing::GetCurrentTimeInMicroSecond(){
            struct timeval val;
            gettimeofday(&val,NULL);
            uint64_t ret = val.tv_sec*1000000+val.tv_usec;
            return ret;
        }

        uint64_t timing::GetCurrentTimeInMilliSecond(){
            return GetCurrentTimeInMicroSecond()/1000;
        }

        uint64_t timing::GetCurrentTimeInSecond(){
            return GetCurrentTimeInMicroSecond()/1000000;
        }
