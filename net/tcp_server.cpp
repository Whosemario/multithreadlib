#include "tcp_server.h"
#include "eventloop.h"
#include <memory>
#include <functional>


using namespace std;
using namespace std::placeholders;
using namespace net;

TcpServer::TcpServer(EventLoop* loop, const InetAddress& addr)
	:acceptor(new Acceptor(loop,addr)){
	acceptor->setNewConnectionCallback(bind(&TcpServer::newConnect,this,_1,InetAddress(11)));
}

void TcpServer::newConnect(int connfd,const InetAddress& addr)
{
}
