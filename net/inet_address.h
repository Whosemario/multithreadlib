#ifndef INET_ADDRESS_H
#define INET_ADDRESS_H

#include <netinet/in.h>
#include <string>
#include "global.h"

namespace net{
	class InetAddress{
		public:
			explicit InetAddress(uint16_t port);
			InetAddress(const std::string& ip, uint16_t port);
			InetAddress(const struct sockaddr_in& addr):mAddr(addr){}

			InetAddress(const InetAddress& oth):mAddr(oth.mAddr){}
			InetAddress& operator=(const InetAddress& oth){
				mAddr = oth.mAddr;
				return *this;
			}

			const struct sockaddr_in& getSocketAddress() const { return mAddr;}
			void setSocketAddress(struct sockaddr_in& addr){mAddr=addr;}

		private:
			struct sockaddr_in mAddr;
	};
}
#endif
