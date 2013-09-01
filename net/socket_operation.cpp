#include "socket_operation.h"
#include <iostream>
#include <unistd.h>
#include <errno.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <string.h>

using namespace std;
using namespace net;

void sockets::IPAddr2NetworkForm(const char* ip, struct sockaddr_in* addr){
	if(::inet_pton(AF_INET,ip,&(addr->sin_addr)) <= 0){
		cerr << "Error : inet_pton()" << endl;
	}
	return ;
}

void sockets::Close(int socketfd){
	if(::close(socketfd)){
		cerr << "Error: sockets::Close() , errno: " << strerror(errno) << endl;
	}
}

void sockets::BindOrDie(int sockfd,const struct sockaddr_in& addr){
	if(::bind(sockfd,reinterpret_cast<const struct sockaddr*>(&addr),sizeof(addr))){
		cerr << "Error: sockets::BindOrDie(), errno: " << strerror(errno) << endl;
	}
}

void sockets::ListenOrDie(int sockfd){
	if(::listen(sockfd,SOMAXCONN)){
		cerr << "Error: sockets::ListenOrDie(), errno: " << strerror(errno) << endl;
	}
} 

int sockets::AcceptOrDie(int sockfd,struct sockaddr_in& addr){
	bzero(&addr,sizeof(addr));
	socklen_t len = sizeof(addr);
	int ret = ::accept(sockfd,reinterpret_cast<struct sockaddr*>(&addr),&len);
	if(ret < 0){
		cerr << "Error: sockets::AcceptOrDie(), errno: " << strerror(errno) << endl;
	}	
	return ret;
}

int sockets::CreateNonblockingOrDie(){
	int sockfd = ::socket(AF_INET,SOCK_STREAM | SOCK_NONBLOCK | SOCK_CLOEXEC,IPPROTO_TCP);
	if(sockfd < 0){
		cerr << "Error: sockets::CreateNonblockingOrDie(), errno: " << strerror(errno) << endl;	
	}
}
