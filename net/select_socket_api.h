//

#ifndef __SOCKET_API_H__
#define __SOCKET_API_H__

#include "CommonDef.h"
#include "nk_file_api.h"

namespace noko{
	namespace select_socket_api 
	{

		nk_socket socket_ex (int32 domain, int32 type, int32 protocol) ;
		bool bind_ex (nk_socket s, const struct sockaddr* name, uint32 namelen) ;
		bool connect_ex (nk_socket s, const struct sockaddr* name, uint32 namelen) ;
		bool listen_ex (nk_socket s, uint32 backlog) ;
		nk_socket accept_ex (nk_socket s, struct sockaddr* addr, uint32* addrlen) ;
		bool getsockopt_ex (nk_socket s, int32 level, int32 optname, void* optval, uint32* optlen) ;
	
		uint32 getsockopt_ex2 (nk_socket s, int32 level, int32 optname, void* optval, uint32* optlen) ;
		bool setsockopt_ex (nk_socket s, int32 level, int32 optname, const void* optval, uint32 optlen) ;
		
		uint32 send_ex (nk_socket s, const void* buf, uint32 len, uint32 flags) ;
		uint32 sendto_ex (nk_socket s, const void* buf, int32 len, uint32 flags, const struct sockaddr* to, int32 tolen) ;
		
		uint32 recv_ex (nk_socket s, void* buf, uint32 len, uint32 flags) ;
		uint32 recvfrom_ex (nk_socket s, void* buf, int32 len, uint32 flags, struct sockaddr* from, uint32* fromlen) ;
		
		bool closesocket_ex (nk_socket s) ;

		bool ioctlsocket_ex (nk_socket s, long cmd, ulong* argp) ;
		
		bool getsocketnonblocking_ex (nk_socket s) ;
		bool setsocketnonblocking_ex (nk_socket s, bool on) ;

		uint32 availablesocket_ex (nk_socket s) ;

		bool shutdown_ex (nk_socket s, uint32 how) ;

		int32 select_ex (int32 maxfdp1, fd_set* readset, fd_set* writeset, fd_set* exceptset, struct timeval* timeout) ;


	};//end of namespace 
};// end of noko


#endif
