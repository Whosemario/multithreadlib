#include <iostream>
#include "eventloop.h"

using namespace std;
using namespace net;

int main(int argc, char * argv[])
{
    cout << "Start" << endl;

    EventLoop el;
    el.loop();

    return 0;
}
