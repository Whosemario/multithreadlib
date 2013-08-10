#include <poll.h>
#include "channel.h"

namespace net{
    void Channel::handleEvent(){

        if(mRevents & (POLLIN | POLLPRI)){
            if(readCallback) readCallback();
        }
        else if(mRevents & (POLLOUT)){
            if(writeCallback) writeCallback();
        }
    }
}
