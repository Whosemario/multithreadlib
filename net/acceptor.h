#ifndef ACCEPTOR_H
#define ACCEPTOR_H

#include <functional>
#include "channel.h"
#include "socket.h"
#include "inet_address.h"

namespace net{
	class EventLoop;
	class Acceptor{
		public:
			typedef std::function<void(int)> NewConnectionCallback;
			Acceptor(EventLoop*,const InetAddress&);
			void listen();
			void setNewConnectionCallback(NewConnectionCallback cb){mCallback=cb;}
		private:
			void handleRead();
			Socket mSocket;
			ChannelPtr mChannel;	
			NewConnectionCallback mCallback;
	};
}

#endif
