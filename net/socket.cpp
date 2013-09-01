#include "socket.h"
#include <string.h>
#include <sys/types.h>
#include <sys/socket.h>

using namespace net;


void Socket::bindAddress(const InetAddress& addr){
	sockets::BindOrDie(mSocketFd,addr.getSocketAddress());	
}

void Socket::listen(){
	sockets::ListenOrDie(mSocketFd);
}

int Socket::accept(InetAddress& peerAddr){
	struct sockaddr_in addr;
	bzero(&addr,sizeof(addr));
	socklen_t len = sizeof(addr);
	int ret = ::accept(mSocketFd,reinterpret_cast<struct sockaddr*>(&addr),&len);
	if(ret >= 0){
		peerAddr.setSocketAddress(addr);
	}	
	return ret;
}

void Socket::setReuseAddr(bool on){
	int optval = on ? 1:0;
	::setsockopt(mSocketFd,SOL_SOCKET,SO_REUSEADDR,&optval, sizeof(optval));
}
