#include <iostream>
#include "mutex.h"
#include "thread.h"

using namespace std;
using namespace multithreads;

PTMutexLock mutex;
PTCond cond;

void func(){
    sleep(2);
    PTMutexLockGuard guard(mutex);
    cond.signal();
}
int main(int argc, char* argv[])
{
    Thread thread(func,"thread");
    thread.Start();
    PTMutexLockGuard guard(mutex);
    cond.wait(mutex,10*10000000);

    return 0;
}
