
/*
* CoptRight(C) StefanChen e-mail(2572915286@qq.com)
*
* Licensed under the Apache License, Version 2.0 (the "License");
* you may not use this file except in compliance with the License.
* You may obtain a copy of the License at
*
* http://www.apache.org/licenses/LICENSE-2.0
*
* Unless required by applicable law or agreed to in writing, software
* distributed under the License is distributed on an "AS IS" BASIS,
* WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
* See the License for the specific language governing permissions and
* limitations under the License.
*/


#ifndef __SESSION__H__
#define __SESSION__H__
#pragma once

#include "select/select_socket_api.h"
#include <ws2ipdef.h>
#include "Netdefine.h"
#include "TimerHelper.h"
#include "Function.h"
#include "session_define.h"

namespace noko {

	class select_session
	{
		public:
			select_session();
			virtual ~select_session();

			void init(const char* szhost, uint32 port);
			void create();
			// close connection
			void close();
			// try connect to remote host
			bool connect();

			// close previous connection and connect to another socket
			bool reconnect();

			// send data to peer
			uint32 send(const void* buf, uint32 len, uint32 flags = 0);

			// receive data from peer
			int32 receive(void* buf, uint32 len, uint32 flags = 0);

			uint32 available() const;

			bool accept(struct sockaddr* addr, uint32 addrlen) {}
			bool accept();

			bool bind();

			bool bind(uint32 port);

			bool listen(int32 backlog = SOCKET_LISTEN_BASE_BLOCK_SIZE);

			bool startselect(cb_dispatchmessage ssp);

			// get/set socket's linger status
			uint32 getLinger()const;
			bool setLinger(uint32 lingertime);

			bool isReuseAddr()const;
			bool setReuseAddr(bool reuse = true);

			// get is Error
			uint32 getSockError(int32 socketindex)const;

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
			bool isValid(int32 socketindex)const;

			// get socket descriptor
			nk_socket getsocket(int32 socketindx)const;

			bool isSockError(int32 socketindx)const;

			uint64 getsessionTick();
		public:

			nk_socket m_socketid[SELECT_SOCKET_NUM];
			// socket address structure
			sockaddr_in6 m_sockaddrSix;  // ipv6 todo: ... left
			sockaddr_in  m_sockaddr;
			// peer host
			char m_szHost[IP_SIZE];
			// peer port
			uint16 m_unPort;

			bool m_bIPv6;

			fd_set m_fdreads;
			fd_set m_fdwrites;
			fd_set m_fderrors;

			int32  m_maxfd;
			uint64 m_ucreatetime;
	};
}

#endif