#include <iostream>
#include "thread.h"
#include "future.h"

using namespace std;
using namespace multithreads;

FutureClass future;

void func1(){
    cout<<"In func1"<<endl;
    cout<<"Wait..."<<endl;
    future.Wait();
}

void func2(){
    cout<<"In func2\nSleep 5s"<<endl;
    sleep(5);
    cout<<"signal..."<<endl;
    future.SucceedAll();
}

void func3(){
    cout<<"In func3\nfunc3 Wait..."<<endl;
    future.Wait();
    cout<<"End func3"<<endl;
}

int main()
{
    Thread thread1(func1,"thread1");
    Thread thread2(func2,"thread2");
    Thread thread3(func3,"thread3");
    thread1.Start();
    thread2.Start();
    thread3.Start();

    thread1.Join();
    thread2.Join();
    thread3.Join();
    return 0;
}
