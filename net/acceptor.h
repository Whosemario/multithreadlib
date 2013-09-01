#ifndef ACCEPTOR_H
#define ACCEPTOR_H

#include <tr1/functional>
#include "channel.h"
#include "socket.h"
#include "inet_address.h"

namespace net{
	class EventLoop;
	class Acceptor{
		public:
			typedef std::tr1::function<void(int,const InetAddress&)> NewConnectionCallback;
			Acceptor(EventLoop*,const InetAddress&);
			void listen();
		private:
			void handleRead();
			Socket mSocket;
			ChannelPtr mChannel;	
			NewConnectionCallback mCallback;
	};
}

#endif
