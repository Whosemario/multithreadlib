#include <iostream>
#include "eventloop.h"

using namespace std;
using namespace net;

void func(){
    cout << "run in func" << endl;
}

int main(int argc, char* argv[])
{
    EventLoop elp;

    elp.runAt(3000,func);

    elp.Start();

    return 0;
}
