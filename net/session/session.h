
/*
* socket: select 
*
*
* CopyRight(C) StefanChen e-mail:2572915286@qq.com
*
*
*
*/

#ifndef __SESSION__H__
#define __SESSION__H__
#pragma once

#include "select_socket_api.h"
#include <ws2ipdef.h>

namespace noko {

	class select_session
	{
		public:
			select_session();
			virtual ~select_session();

			void create(const char* szhost, uint32 port);
			// close connection
			void close();
			// try connect to remote host
			bool connect();

			// close previous connection and connect to another socket
			bool reconnect();

			// send data to peer
			uint32 send(const void* buf, uint32 len, uint32 flags = 0);

			// receive data from peer
			uint32 receive(void* buf, uint32 len, uint32 flags = 0);

			uint32 available() const;

			nk_socket accept(struct sockaddr* addr, uint32* addrlen);

			bool bind();

			bool bind(uint32 port);

			bool listen(int32 backlog);

			// get/set socket's linger status
			uint32 getLinger()const;
			bool setLinger(uint32 lingertime);

			bool isReuseAddr()const;
			bool setReuseAddr(bool reuse = true);

			// get is Error
			uint32 getSockError()const;

			// get/set socket's nonblocking status
			bool isNonBlocking()const;
			bool setNonBlocking(bool on = true);

			// get/set receive buffer size
			uint32 getReceiveBufferSize()const;
			bool setReceiveBufferSize(uint32 size);

			// get/set send buffer size
			uint32 getSendBufferSize()const;
			bool setSendBufferSize(uint32 size);

			uint32 getPort()const;
			IP_t getHostIP()const;

			// check if socket is valid
			bool isValid()const;

			// get socket descriptor
			nk_socket getsocket()const;

			bool isSockError()const;

		private:

			nk_socket m_socketid;
			// socket address structure
			sockaddr_in6 m_sockaddrSix;  // ipv6 todo: ... left
			sockaddr_in  m_sockaddr;
			// peer host
			char m_szHost[IP_SIZE];
			// peer port
			uint16 m_unPort;

			bool m_bIPv6;
	};
}

#endif