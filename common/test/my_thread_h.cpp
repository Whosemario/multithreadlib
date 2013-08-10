#include<iostream>
#include"thread.h"

using namespace std;
using namespace multithreads;

void func(){
    cout<<"Thread..."<<endl;
}
int main()
{
    cout<<"Start"<<endl;
    Thread thread(func,"my thread");
    thread.Start();
    cout<<"End"<<endl;
    thread.Join();
    cout<<"Join"<<endl;
    return 0;
}
