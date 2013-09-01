#ifndef SOCKET_OPERATION_H
#define SOCKET_OPERATION_H

#include "global.h"
#include <arpa/inet.h> 
#include <netinet/in.h>

namespace net{
	namespace sockets{
		inline uint32_t Host2Network32(uint32_t host){ return htonl(host);}
		inline uint16_t Host2Network16(uint16_t host){ return htons(host);}
		inline uint32_t Network2Host32(uint32_t net){ return ntohl(net);}	
		inline uint16_t Network2Host16(uint16_t net){ return ntohs(net);}

		void IPAddr2NetworkForm(const char* , struct sockaddr_in* ); 
		void Close(int);
		void BindOrDie(int sockfd,const struct sockaddr_in& addr);
		void ListenOrDie(int sockfd); 
		int AcceptOrDie(int sockfd,struct sockaddr_in& addr);
		int CreateNonblockingOrDie();
	}
}
#endif
