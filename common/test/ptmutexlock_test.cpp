#include <iostream>
#include "mutex.h"

using namespace std;
using namespace multithreads;


PTMutexLock lock;

void func(){
    PTMutexLockGuard guard(lock);
    cout<< "lock 2" << endl;
}

int main(int argc, char* argv[])
{
    PTMutexLockGuard guard(lock);

    cout<< "lock 1" <<endl;

    func();
}
