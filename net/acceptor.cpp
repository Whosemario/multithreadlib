#include <iostream>
#include "acceptor.h"
#include "eventloop.h"
#include "inet_address.h"
#include "socket_operation.h"

using namespace std;
using namespace net;

Acceptor::Acceptor(EventLoop* loop,const InetAddress& addr):
	mSocket(sockets::CreateNonblockingOrDie()),mChannel(new Channel(mSocket.getSocketFd())){
	mSocket.setReuseAddr(true);
	mSocket.bindAddress(addr);
	mChannel->setReadCallback(bind(&Acceptor::handleRead,this));
	mChannel->setChannel2Read();	
	loop->updateChannel(mChannel);
}	

void Acceptor::handleRead(){
	InetAddress peerAddr(0);
	int connFd = mSocket.accept(peerAddr);
	if(connFd >= 0){
		if(mCallback) mCallback(connFd);//mCallback(connFd,peerAddr);
		else sockets::Close(connFd);
	}
}

void Acceptor::listen(){
	mSocket.listen();
}
