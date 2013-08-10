#include <iostream>
#include <sys/timerfd.h>
#include <string.h>
#include "poll.h"
#include "eventloop.h"

using namespace std;
using namespace net;

EventLoop * elp = NULL;

void func(){
    cout << "In Callback" <<endl;
    if(elp!=NULL) elp->Stop();
}


int main(int argc, char* argv[])
{
    int fd = timerfd_create(CLOCK_MONOTONIC,TFD_NONBLOCK | TFD_CLOEXEC);

    ChannelPtr channel(new Channel(fd));
    channel->setChannel2Read();
    channel->setReadCallback(func);

    EventLoop loop;
    loop.updateChannel(channel);

    elp = &loop;

    struct itimerspec howlog;

    bzero(&howlog, sizeof(howlog));

    howlog.it_value.tv_sec = 5;

    timerfd_settime(fd,0,&howlog,NULL);

    cout << "begin" <<endl;

    loop.Start();

    close(fd);

    return 0;
}
