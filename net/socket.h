#ifndef SOCKET_H
#define SOCKET_H

#include "noncopyable.h"
#include "socket_operation.h"
#include "inet_address.h"

namespace net{

	class Socket : multithreads::noncopyable{
		public:
			Socket(int fd):mSocketFd(fd){}
			~Socket(){sockets::Close(mSocketFd);}
			void bindAddress(const InetAddress&);
			void listen();
			int accept(InetAddress& peerAddr);
			void setReuseAddr(bool on);
			int getSocketFd(){ return mSocketFd;}
		private:
			const int mSocketFd;
	};
}
#endif
