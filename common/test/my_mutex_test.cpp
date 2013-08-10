#include <iostream>
#include "mutex.h"

using namespace std;
using namespace multithreads;


int main()
{
    MutexLock lock;
    {
        MutexLockGuard mlg(lock);
        cout<<"Enter 1"<<endl;
    }

    {
        MutexLockGuard mlg1(lock);
        cout<<"Enter 2.1"<<endl;
        {
            MutexLockGuard mlg2(lock);
            cout<<"Enter 2.2"<<endl;
        }
    }

    return 0;
}

