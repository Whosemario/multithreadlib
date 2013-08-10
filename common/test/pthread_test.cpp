#include <iostream>
#include <pthread.h>
using namespace std;

void * func(void * unused){
    cout<<"Thread in...."<<endl;
}

pthread_t thread1;


int main(int argc, char* argv[])
{
    int ret = pthread_create(&thread1,NULL,func,NULL);
    if(ret) cout<<"create fail"<<endl;

    cout<<"main in"<<endl;

    return 0;
}
