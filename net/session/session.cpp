#include "session.h"


namespace noko {

	select_session::select_session():
		m_bIPv6(false),
		m_unPort(0),
		m_ucreatetime(0)
	{
		m_socketid[0] = INVALID_SOCKET;
		m_socketid[1] = INVALID_SOCKET;

		memset(&m_sockaddr, 0, sizeof(sockaddr_in));
		memset(m_szHost, 0, IP_SIZE);
	}

	select_session::~select_session()
	{

	}

	void select_session::init(const char* szhost, uint32 port)
	{
		m_bIPv6 = std::string(szhost).find(':') != std::string::npos;
		memmove(m_szHost, szhost, IP_SIZE - 1);
		m_unPort = port;
	}

	void select_session::create()
	{
		if (m_bIPv6)
		{
			m_socketid[0] = select_socket_api::socket_ex(AF_INET6, SOCK_STREAM , 0);
			m_socketid[1] = select_socket_api::socket_ex(AF_INET6, SOCK_STREAM, 0);
		}
		else
		{
			m_socketid[0] = select_socket_api::socket_ex(AF_INET, SOCK_STREAM, 0);
			m_socketid[1] = select_socket_api::socket_ex(AF_INET, SOCK_STREAM, 0);
		}
	}

	bool select_session::connect()
	{
		if (m_bIPv6)
		{
			m_sockaddrSix.sin6_family = AF_INET6;
			m_sockaddrSix.sin6_addr = in6addr_any;
			std::string szip6 = m_szHost;
			if (!szip6.empty() && szip6 != "::")
			{
				//inet_pton(AF_INET6, szip6.c_str(), &m_sockaddrSix.sin6_addr);
			}

			m_sockaddrSix.sin6_port = htons(m_unPort);
			bool bconn = select_socket_api::connect_ex(m_socketid[0], (const struct sockaddr*)&m_sockaddrSix, sizeof(m_sockaddrSix));
			if (!bconn)
			{
				return false;
			}

			return true;
		}
		else
		{
			m_sockaddr.sin_family = AF_INET;
			m_sockaddr.sin_addr.s_addr = inet_addr(m_szHost);
			m_sockaddr.sin_port = htons(m_unPort);

			bool bconn = select_socket_api::connect_ex(m_socketid[0], (const struct sockaddr*)&m_sockaddr, sizeof(m_sockaddr));
			if (!bconn)
			{
				close();
				return false;
			}

			return true;
		}

		return false;
	}

	// close previous connection and connect to another server socket
	bool select_session::reconnect()
	{

		// delete old socket impl object
		close();

		if (m_bIPv6)
		{
			m_socketid[0] = select_socket_api::socket_ex(AF_INET6, SOCK_STREAM, 0);
		}
		else
		{
			m_socketid[0] = select_socket_api::socket_ex(AF_INET, SOCK_STREAM, 0);
		}

		// try to connect
		return connect();
	}

	void select_session::close()
	{

		for (int i = 0; i < SELECT_SOCKET_NUM; ++i)
		{
			if (isValid(i) && !isSockError(i))
			{
				select_socket_api::closesocket_ex(m_socketid[i]);
			}

			m_socketid[i] = INVALID_SOCKET;
		}
		
		memset(&m_sockaddr, 0, sizeof(sockaddr_in));
		memset(m_szHost, 0, IP_SIZE);
		m_unPort = 0;

	}

	uint32 select_session::send(const void* buf, uint32 len, uint32 flags)
	{
		return select_socket_api::send_ex(m_socketid[1], buf, len, flags);
	}

	int32 select_session::receive(void* buf, uint32 len, uint32 flags)
	{
		return select_socket_api::recv_ex(m_socketid[1], buf, len, flags);
	}

	uint32 select_session::available()const
	{
		return select_socket_api::availablesocket_ex(m_socketid[0]);
	}

	uint32 select_session::getLinger()const
	{
		struct linger ling;
		uint32 len = sizeof(ling);

		select_socket_api::getsockopt_ex(m_socketid[0], SOL_SOCKET, SO_LINGER, &ling, &len);

		return ling.l_linger;
	}

	bool select_session::accept()
	{
		nk_socket fd = select_socket_api::accept_ex(m_socketid[0], (struct sockaddr*)&m_sockaddr, sizeof(m_sockaddr));
		if (fd  == SOCKET_ERROR)
		{
			return false;
		}

#ifdef __WINDOWS__ || __LINUX__
		m_ucreatetime = noko::GetTime();
#endif
	}

	bool select_session::setLinger(uint32 lingertime)
	{

		struct linger ling;

		ling.l_onoff = lingertime > 0 ? 1 : 0;
		ling.l_linger = lingertime;

		return select_socket_api::setsockopt_ex(m_socketid[0], SOL_SOCKET, SO_LINGER, &ling, sizeof(ling));
	}

	uint32 select_session::getSockError(int32 socketindex) const
	{
		return isSockError(socketindex);
	}

	bool select_session::isNonBlocking()const
	{
		return select_socket_api::getsocketnonblocking_ex(m_socketid[0]);
	}

	bool select_session::setNonBlocking(bool on)
	{
		return select_socket_api::setsocketnonblocking_ex(m_socketid[0], on);
	}

	uint32 select_session::getReceiveBufferSize() const
	{

		uint32 ReceiveBufferSize;
		uint32 size = sizeof(ReceiveBufferSize);

		select_socket_api::getsockopt_ex(m_socketid[1], SOL_SOCKET, SO_RCVBUF, &ReceiveBufferSize, &size);

		return ReceiveBufferSize;
	}

	bool select_session::setReceiveBufferSize(uint32 size)
	{
		return (bool)(select_socket_api::setsockopt_ex(m_socketid[1], SOL_SOCKET, SO_RCVBUF, &size, sizeof(uint32)));
	}

	uint32 select_session::getSendBufferSize() const
	{
		uint32 SendBufferSize;
		uint32 size = sizeof(SendBufferSize);

		select_socket_api::getsockopt_ex(m_socketid[1], SOL_SOCKET, SO_SNDBUF, &SendBufferSize, &size);

		return SendBufferSize;
	}

	bool select_session::setSendBufferSize(uint32 nsize)
	{
		return select_socket_api::setsockopt_ex(m_socketid[1], SOL_SOCKET, SO_SNDBUF, &nsize, sizeof(uint32));
	}

	uint32 select_session::getPort() const
	{
		return m_unPort;
	}

	IP_t select_session::getHostIP() const
	{
		return (IP_t)(m_sockaddr.sin_addr.s_addr);;
	}

	bool select_session::isValid(int32 socketindex) const
	{
		if (socketindex >= sizeof(m_socketid))
			return false;

		return m_socketid[socketindex] != INVALID_SOCKET;
	}

	SOCKET select_session::getsocket(int32 socketindx) const
	{
		if (socketindx >= sizeof(m_socketid))
			return INVALID_SOCKET;

		return m_socketid[socketindx];
	}

	bool select_session::isSockError(int32 socketindx)const
	{
		if (socketindx >= sizeof(m_socketid))
			return false;

		int32 error;
		uint32 len = sizeof(error);

		int32 Result = select_socket_api::getsockopt_ex2(m_socketid[socketindx], SOL_SOCKET, SO_ERROR, &error, &len);

		if (Result == 0)
			return false;
		else
			return true;
	}

	uint64 select_session::getsessionTick()
	{
		return m_ucreatetime;
	}

	bool select_session::bind()
	{
		m_sockaddr.sin_addr.s_addr = htonl(INADDR_ANY);
		m_sockaddr.sin_port = htons(m_unPort);

		bool result = select_socket_api::bind_ex(m_socketid[0], (const struct sockaddr *)&m_sockaddr, sizeof(m_sockaddr));
		if (result)
			return true;
		else
			return false;
	}

	bool select_session::bind(uint32 port)
	{
		m_unPort = port;

		m_sockaddr.sin_addr.s_addr = htonl(INADDR_ANY);
		m_sockaddr.sin_port = htons(m_unPort);

		bool result = select_socket_api::bind_ex(m_socketid[0], (const struct sockaddr *)&m_sockaddr, sizeof(m_sockaddr));
		if (result)
			return TRUE;
		else
			return FALSE;
	}

	bool select_session::listen(int32 backlog)
	{
		return select_socket_api::listen_ex(m_socketid[0], backlog);
	}

	bool select_session::startselect(cb_dispatchmessage ssp)
	{
		for (;;)
		{
			fd_set fdr;
			fd_set fdw;
			fd_set fde;
			memmove(&fdr, &m_fdreads, sizeof(m_fdreads));
			memmove(&fdw, &m_fdwrites, sizeof(m_fdwrites));
			memmove(&fde, &m_fderrors, sizeof(m_fderrors));

			timeval tv;
			tv.tv_sec = SELECT_TV_SEC;
			tv.tv_usec = SELECT_TV_USEC;

			int32 result = select_socket_api::select_ex(m_maxfd + 1, &fdr, &fdw, &fde, &tv);
			switch (result)
			{
				case SOCKET_ERROR:
				case 0:
					continue;
			}

			if (FD_ISSET(m_socketid[1], &fdr))
			{
				char outbuff[em_buffer_1024] = {0};
				int32 revLen = receive(outbuff, sizeof(outbuff));
				if (revLen == SOCKET_ERROR || revLen == 0)
				{
					continue;
				}
				else
				{
					//dispatch normal message package
					if (ssp)
					{
						ssp(outbuff,sizeof(outbuff));
					}
				}
			}
		}

		return true;
	}

	bool select_session::isReuseAddr()const
	{

		int32 reuse;
		uint32 len = sizeof(reuse);

		select_socket_api::getsockopt_ex(m_socketid[0], SOL_SOCKET, SO_REUSEADDR, &reuse, &len);

		return reuse == 1;
	}

	bool select_session::setReuseAddr(bool reuse)
	{
		int32 opt = reuse == TRUE ? 1 : 0;

		return select_socket_api::setsockopt_ex(m_socketid[0], SOL_SOCKET, SO_REUSEADDR, &opt, sizeof(opt));
	}

}