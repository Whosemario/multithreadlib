#include "inet_address.h"
#include "socket_operation.h"
#include <string.h>


using namespace std;
using namespace net;

InetAddress::InetAddress(uint16_t port)
{
	bzero(&mAddr, sizeof(mAddr));
	mAddr.sin_family = AF_INET;
	mAddr.sin_port = sockets::Host2Network16(port); 
	mAddr.sin_addr.s_addr = sockets::Host2Network32(INADDR_ANY);
}

InetAddress::InetAddress(const string& ip, uint16_t port)
{
	bzero(&mAddr, sizeof(mAddr));
	mAddr.sin_family = AF_INET;
	mAddr.sin_port = sockets::Host2Network16(port);
	sockets::IPAddr2NetworkForm(ip.c_str(),&mAddr);
}
