#include "thread.h"
#include <iostream>

using namespace std;

namespace multithreads{

struct ThreadData{
    typedef Thread::ThreadFunc ThreadFunc;
    const ThreadFunc mFunc;
    const string mName;
    explicit  ThreadData(const ThreadFunc& func,const string& name):
        mFunc(func),mName(name){}
    void run(){
        mFunc();
    }
};

void * MainFunc(void* obj){
    ThreadData *data = static_cast<ThreadData*>(obj);
    data->run();
    delete data;
    return NULL;
}

Thread::Thread(const ThreadFunc& threadFunc,const string& name):
    mFunc(threadFunc),mName(name),mRunning(false){}

void Thread::Start(){
    ThreadData* data = new ThreadData(mFunc,mName);
    mRunning = true;
    if(pthread_create(&mThread,NULL,MainFunc,data)){
        cout<<"Error: can not create thread "<<mName<<endl;
        mRunning = false;
        delete data;
    }
}

void Thread::Join(){
    if(mRunning)
        pthread_join(mThread,NULL);
}

}
