#include <iostream>
#include <tr1/functional>
#include <string>
#include "thread.h"
#include "count_down_latch.h"
using namespace std;
using namespace multithreads;

CountDownLatch counter(5);

void func(string str,uint32_t s){
    sleep(s+1);
    counter.countDown();
    cout<<str;
    cout<<s<<" ends."<<endl;
}


int main(){

    for(uint32_t i=0;i<5;i++){
        Thread thread(tr1::bind(&func,string("thread"),i),"thread");
        thread.Start();
    }

    counter.Wait();

    cout<<"All end."<<endl;
    return 0;
}
