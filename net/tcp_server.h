#ifndef TCP_SERVER_H
#define TCP_SERVER_H

#include <memory>
#include <acceptor.h>
#include <inet_address.h>

namespace net{

class EventLoop;


class TcpServer{
public:
	TcpServer(EventLoop* loop, const InetAddress& addr);
	void Start(){
		if(acceptor.get() != NULL)
			acceptor->listen();
	}

private:
	void newConnect(int,const InetAddress&); 
	std::auto_ptr<Acceptor> acceptor;
};

}
#endif
