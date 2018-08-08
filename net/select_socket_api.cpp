
#include "select_socket_api.h"


#if __LINUX__
extern int32 errno;
#endif

char Error[_ESIZE] ;

namespace noko {

	namespace select_socket_api
	{
		nk_socket select_socket_api::socket_ex ( int32 domain , int32 type , int32 protocol )
		{
			nk_socket s = ::socket(domain,type,protocol);

			if ( s == INVALID_SOCKET ) 
			{
		#if __LINUX__
				switch ( errno ) 
				{
				case EPROTONOSUPPORT :
				case EMFILE : 
				case ENFILE : 
				case EACCES : 
				case ENOBUFS : 
				default : 
					{
						break;
					}
				}//end of switch
		#elif __WINDOWS__
				int32 iErr = WSAGetLastError() ;
				switch ( iErr ) 
				{
				case WSANOTINITIALISED : 
					strncpy_s( Error, "WSANOTINITIALISED", _ESIZE ) ;
					break ;
				case WSAENETDOWN : 
					strncpy_s( Error, "WSAENETDOWN", _ESIZE ) ;
					break ;
				case WSAEAFNOSUPPORT : 
					strncpy_s( Error, "WSAEAFNOSUPPORT", _ESIZE ) ;
					break ;
				case WSAEINPROGRESS : 
					strncpy_s( Error, "WSAEINPROGRESS", _ESIZE ) ;
					break ;
				case WSAEMFILE : 
					strncpy_s( Error, "WSAEMFILE", _ESIZE ) ;
					break ;
				case WSAENOBUFS : 
					strncpy_s( Error, "WSAENOBUFS", _ESIZE ) ;
					break ;
				case WSAEPROTONOSUPPORT : 
					strncpy_s( Error, "WSAEPROTONOSUPPORT", _ESIZE ) ;
					break ;
				case WSAEPROTOTYPE : 
					strncpy_s( Error, "WSAEPROTOTYPE", _ESIZE ) ;
					break ;
				case WSAESOCKTNOSUPPORT : 
					strncpy_s( Error, "WSAESOCKTNOSUPPORT", _ESIZE ) ;
					break ;
				default : 
					{
					strncpy_s( Error, "UNKNOWN", _ESIZE ) ;
					break ;
					};
				};//end of switch
		#endif
			}

			return s;

		}

		bool select_socket_api::bind_ex (nk_socket s , const struct sockaddr * addr , uint32 addrlen )
		{
			if ( bind ( s , addr , addrlen ) == SOCKET_ERROR ) 
			{
		#if __LINUX__
				switch ( errno ) 
				{
				case EADDRINUSE :
				case EINVAL : 
				case EACCES : 
				case ENOTSOCK : 
				case EBADF : 
				case EROFS : 
				case EFAULT : 
				case ENAMETOOLONG : 
				case ENOENT : 
				case ENOMEM : 
				case ENOTDIR : 
				case ELOOP : 
				default :
					{
						break;
					}
				}//end of switch
		#elif __WINDOWS__
				int32 iErr = WSAGetLastError() ;
				switch ( iErr ) 
				{
				case WSANOTINITIALISED : 
					strncpy_s( Error, "WSAESOCKTNOSUPPORT", _ESIZE ) ;
					break ;
				case WSAENETDOWN : 
					strncpy_s( Error, "WSAENETDOWN", _ESIZE ) ;
					break ;
				case WSAEADDRINUSE : 
					strncpy_s( Error, "WSAEADDRINUSE", _ESIZE ) ;
					break ;
				case WSAEADDRNOTAVAIL : 
					strncpy_s( Error, "WSAEADDRNOTAVAIL", _ESIZE ) ;
					break ;
				case WSAEFAULT : 
					strncpy_s( Error, "WSAEFAULT", _ESIZE ) ;
					break ;
				case WSAEINPROGRESS : 
					strncpy_s( Error, "WSAEINPROGRESS", _ESIZE ) ;
					break ;
				case WSAEINVAL : 
					strncpy_s( Error, "WSAEINVAL", _ESIZE ) ;
					break ;
				case WSAENOBUFS : 
					strncpy_s( Error, "WSAENOBUFS", _ESIZE ) ;
					break ;
				case WSAENOTSOCK : 
					strncpy_s( Error, "WSAENOTSOCK", _ESIZE ) ;
					break ;
				default :
					{
					strncpy_s( Error, "UNKNOWN", _ESIZE ) ;
					break ;
					};
				};//end of switch
		#endif

				return FALSE ;
			}
	
			return TRUE ;

		}

		bool select_socket_api::connect_ex (nk_socket s , const struct sockaddr * addr , uint32 addrlen )
		{
			if ( connect(s,addr,addrlen) == SOCKET_ERROR ) 
			{
		#if __LINUX__
				switch ( errno ) {
				case EALREADY : 
				case EINPROGRESS : 
				case ECONNREFUSED : 
				case EISCONN : 
				case ETIMEDOUT : 
				case ENETUNREACH : 
				case EADDRINUSE : 
				case EBADF : 
				case EFAULT : 
				case ENOTSOCK : 
				default :
					{
						break;
					}
				}//end of switch
		#elif __WINDOWS__
				int32 iErr = WSAGetLastError() ;
				switch ( iErr ) 
				{
				case WSANOTINITIALISED : 
					strncpy_s( Error, "WSANOTINITIALISED", _ESIZE ) ;
					break ;
				case WSAENETDOWN : 
					strncpy_s( Error, "WSAENETDOWN", _ESIZE ) ;
					break ;
				case WSAEADDRINUSE : 
					strncpy_s( Error, "WSAEADDRINUSE", _ESIZE ) ;
					break ;
				case WSAEINTR : 
					strncpy_s( Error, "WSAEINTR", _ESIZE ) ;
					break ;
				case WSAEINPROGRESS : 
					strncpy_s( Error, "WSAEINPROGRESS", _ESIZE ) ;
					break ;
				case WSAEALREADY : 
					strncpy_s( Error, "WSAEALREADY", _ESIZE ) ;
					break ;
				case WSAEADDRNOTAVAIL : 
					strncpy_s( Error, "WSAEADDRNOTAVAIL", _ESIZE ) ;
					break ;
				case WSAEAFNOSUPPORT : 
					strncpy_s( Error, "WSAEAFNOSUPPORT", _ESIZE ) ;
					break ;
				case WSAECONNREFUSED : 
					strncpy_s( Error, "WSAECONNREFUSED", _ESIZE ) ;
					break ;
				case WSAEFAULT : 
					strncpy_s( Error, "WSAEFAULT", _ESIZE ) ;
					break ;
				case WSAEINVAL : 
					strncpy_s( Error, "WSAEINVAL", _ESIZE ) ;
					break ;
				case WSAEISCONN : 
					strncpy_s( Error, "WSAEISCONN", _ESIZE ) ;
					break ;
				case WSAENETUNREACH : 
					strncpy_s( Error, "WSAENETUNREACH", _ESIZE ) ;
					break ;
				case WSAENOBUFS : 
					strncpy_s( Error, "WSAENOBUFS", _ESIZE ) ;
					break ;
				case WSAENOTSOCK : 
					strncpy_s( Error, "WSAENOTSOCK", _ESIZE ) ;
					break ;
				case WSAETIMEDOUT : 
					strncpy_s( Error, "WSAETIMEDOUT", _ESIZE ) ;
					break ;
				case WSAEWOULDBLOCK  : 
					strncpy_s( Error, "WSAEWOULDBLOCK", _ESIZE ) ;
					break ;
				default :
					{
					strncpy_s( Error, "UNKNOWN", _ESIZE ) ;
					break ;
					};
				};//end of switch
		#endif
				return FALSE ;
			}

			return TRUE ;
		}

		bool select_socket_api::listen_ex (nk_socket s , uint32 backlog )
		{
			if ( listen( s , backlog ) == SOCKET_ERROR ) 
			{
		#if __LINUX__
				switch ( errno ) 
				{
				case EBADF : 
				case ENOTSOCK :
				case EOPNOTSUPP :
				default :
					{
						break;
					}
				}//end of switch
		#elif __WINDOWS__
				int32 iErr = WSAGetLastError() ;
				switch ( iErr ) 
				{
				case WSANOTINITIALISED : 
					strncpy_s( Error, "WSANOTINITIALISED", _ESIZE ) ;
					break ;
				case WSAENETDOWN : 
					strncpy_s( Error, "WSAENETDOWN", _ESIZE ) ;
					break ;
				case WSAEADDRINUSE : 
					strncpy_s( Error, "WSAEADDRINUSE", _ESIZE ) ;
					break ;
				case WSAEINPROGRESS : 
					strncpy_s( Error, "WSAEINPROGRESS", _ESIZE ) ;
					break ;
				case WSAEINVAL : 
					strncpy_s( Error, "WSAEINVAL", _ESIZE ) ;
					break ;
				case WSAEISCONN : 
					strncpy_s( Error, "WSAEISCONN", _ESIZE ) ;
					break ;
				case WSAEMFILE : 
					strncpy_s( Error, "WSAEMFILE", _ESIZE ) ;
					break ;
				case WSAENOBUFS : 
					strncpy_s( Error, "WSAENOBUFS", _ESIZE ) ;
					break ;
				case WSAENOTSOCK : 
					strncpy_s( Error, "WSAENOTSOCK", _ESIZE ) ;
					break ;
				case WSAEOPNOTSUPP : 
					strncpy_s( Error, "WSAEOPNOTSUPP", _ESIZE ) ;
					break ;
				default :
					{
					strncpy_s( Error, "UNKNOWN", _ESIZE ) ;
					break ;
					};
				};//end of switch
		#endif

				return FALSE ;
			}

			return TRUE ;
		}

		nk_socket select_socket_api::accept_ex (nk_socket s , struct sockaddr * addr , uint32 * addrlen )
		{
		#if __LINUX__
			nk_socket client = accept( s , addr , addrlen );
		#elif __WINDOWS__
			nk_socket client = accept( s , addr , (int32*)addrlen );
		#endif
	
			if ( client == INVALID_SOCKET ) 
			{
		#if __LINUX__
				switch ( errno ) 
				{

				case EWOULDBLOCK : 

				case ECONNRESET :
				case ECONNABORTED :
				case EPROTO :
				case EINTR :
					// from UNIX Network Programming 2nd, 15.6
					// with nonblocking-socket, ignore above errors

				case EBADF : 
				case ENOTSOCK : 
				case EOPNOTSUPP : 
				case EFAULT : 

				default :
					{
						break;
					}
				}//end of switch
		#elif __WINDOWS__
				int32 iErr = WSAGetLastError() ;
				switch ( iErr ) 
				{
				case WSANOTINITIALISED : 
					strncpy_s( Error, "WSANOTINITIALISED", _ESIZE ) ;
					break ;
				case WSAENETDOWN : 
					strncpy_s( Error, "WSAENETDOWN", _ESIZE ) ;
					break ;
				case WSAEFAULT : 
					strncpy_s( Error, "WSAEFAULT", _ESIZE ) ;
					break ;
				case WSAEINTR : 
					strncpy_s( Error, "WSAEINTR", _ESIZE ) ;
					break ;
				case WSAEINPROGRESS : 
					strncpy_s( Error, "WSAEINPROGRESS", _ESIZE ) ;
					break ;
				case WSAEINVAL : 
					strncpy_s( Error, "WSAEINVAL", _ESIZE ) ;
					break ;
				case WSAEMFILE : 
					strncpy_s( Error, "WSAEMFILE", _ESIZE ) ;
					break ;
				case WSAENOBUFS : 
					strncpy_s( Error, "WSAENOBUFS", _ESIZE ) ;
					break ;
				case WSAENOTSOCK : 
					strncpy_s( Error, "WSAENOTSOCK", _ESIZE ) ;
					break ;
				case WSAEOPNOTSUPP : 
					strncpy_s( Error, "WSAEOPNOTSUPP", _ESIZE ) ;
					break ;
				case WSAEWOULDBLOCK : 
					strncpy_s( Error, "WSAEWOULDBLOCK", _ESIZE ) ;
					break ;
				default :
					{
					strncpy_s( Error, "UNKNOWN", _ESIZE ) ;
					break ;
					};
				};//end of switch
		#endif
			} else {
			}

			return client;
		}

		bool select_socket_api::getsockopt_ex (nk_socket s , int32 level , int32 optname , void * optval , uint32 * optlen )
		{
		#if __LINUX__
			if ( getsockopt( s , level , optname , optval , optlen ) == SOCKET_ERROR ) 
			{
				switch ( errno ) 
				{
				case EBADF : 
				case ENOTSOCK : 
				case ENOPROTOOPT : 
				case EFAULT : 
				default :
					{
						break;
					}
				}//end of switch

				return FALSE ;
			}
		#elif __WINDOWS__
			if ( getsockopt( s , level , optname , (char*)optval , (int32*)optlen ) == SOCKET_ERROR ) 
			{
				int32 iErr = WSAGetLastError() ;
				switch ( iErr ) 
				{
				case WSANOTINITIALISED : 
					strncpy_s( Error, "WSANOTINITIALISED", _ESIZE ) ;
					break ;
				case WSAENETDOWN : 
					strncpy_s( Error, "WSAENETDOWN", _ESIZE ) ;
					break ;
				case WSAEFAULT : 
					strncpy_s( Error, "WSAEFAULT", _ESIZE ) ;
					break ;
				case WSAEINPROGRESS : 
					strncpy_s( Error, "WSAEINPROGRESS", _ESIZE ) ;
					break ;
				case WSAEINVAL : 
					strncpy_s( Error, "WSAEINVAL", _ESIZE ) ;
					break ;
				case WSAENOPROTOOPT : 
					strncpy_s( Error, "WSAENOPROTOOPT", _ESIZE ) ;
					break ;
				case WSAENOTSOCK : 
					strncpy_s( Error, "WSAENOTSOCK", _ESIZE ) ;
					break ;
				default : 
					{
					strncpy_s( Error, "UNKNOWN", _ESIZE ) ;
					break ;
					};
				};//end of switch

				return FALSE ;
			}
		#endif

			return TRUE ;

		}

		uint32 select_socket_api::getsockopt_ex2 (nk_socket s , int32 level , int32 optname , void * optval , uint32 * optlen )
		{

		#if __LINUX__
			if ( getsockopt( s , level , optname , optval , optlen ) == SOCKET_ERROR ) 
			{
				switch ( errno ) 
				{
				case EBADF : 
					return 1;
				case ENOTSOCK : 
					return 2;
				case ENOPROTOOPT : 
					return 3;
				case EFAULT : 
					return 4;
				default :
					return 5;
				}//end of switch
			}
			return 0;

		#elif __WINDOWS__
			if ( getsockopt( s , level , optname , (char*)optval , (int32*)optlen ) == SOCKET_ERROR ) 
			{
				int32 iErr = WSAGetLastError() ;
				switch ( iErr ) 
				{
				case WSANOTINITIALISED:
					strncpy_s( Error, "WSANOTINITIALISED", _ESIZE ) ;
					break ;
				case WSAENETDOWN:
					strncpy_s( Error, "WSAENETDOWN", _ESIZE ) ;
					break ;
				case WSAEFAULT:
					strncpy_s( Error, "WSAEFAULT", _ESIZE ) ;
					break ;
				case WSAEINPROGRESS:
					strncpy_s( Error, "WSAEINPROGRESS", _ESIZE ) ;
					break ;
				case WSAEINVAL:
					strncpy_s( Error, "WSAEINVAL", _ESIZE ) ;
					break ;
				case WSAENOPROTOOPT:
					strncpy_s( Error, "WSAENOPROTOOPT", _ESIZE ) ;
					break ;
				case WSAENOTSOCK:
					strncpy_s( Error, "WSAENOTSOCK", _ESIZE ) ;
					break ;
				default : 
					{
					strncpy_s( Error, "UNKNOWN", _ESIZE ) ;
					break ;
					};
				}
			}
		#endif

			return 0;
		}

		bool select_socket_api::setsockopt_ex (nk_socket s , int32 level , int32 optname , const void * optval , uint32 optlen )
		{

		#if __LINUX__
			if ( setsockopt( s , level , optname , optval , optlen ) == SOCKET_ERROR ) 
			{
				switch ( errno ) 
				{
					case EBADF : 
					case ENOTSOCK : 
					case ENOPROTOOPT : 
					case EFAULT : 
					default :
						{
							break;
						}
				}//end of switch

				return FALSE ;
			}
		#elif __WINDOWS__
			if ( setsockopt( s , level , optname , (CHAR*)optval , optlen ) == SOCKET_ERROR ) 
			{
				int32 iErr = WSAGetLastError() ;
				switch ( iErr ) 
				{
				case WSANOTINITIALISED : 
					strncpy_s( Error, "WSANOTINITIALISED", _ESIZE ) ;
					break ;
				case WSAENETDOWN : 
					strncpy_s( Error, "WSAENETDOWN", _ESIZE ) ;
					break ;
				case WSAEFAULT : 
					strncpy_s( Error, "WSAEFAULT", _ESIZE ) ;
					break ;
				case WSAEINPROGRESS : 
					strncpy_s( Error, "WSAEINPROGRESS", _ESIZE ) ;
					break ;
				case WSAEINVAL : 
					strncpy_s( Error, "WSAEINVAL", _ESIZE ) ;
					break ;
				case WSAENETRESET : 
					strncpy_s( Error, "WSAENETRESET", _ESIZE ) ;
					break ;
				case WSAENOPROTOOPT : 
					strncpy_s( Error, "WSAENOPROTOOPT", _ESIZE ) ;
					break ;
				case WSAENOTCONN : 
					strncpy_s( Error, "WSAENOTCONN", _ESIZE ) ;
					break ;
				case WSAENOTSOCK : 
					strncpy_s( Error, "WSAENOTSOCK", _ESIZE ) ;
					break ;
				default :
					{
					strncpy_s( Error, "UNKNOWN", _ESIZE ) ;
					break ;
					};
				};//end of switch

				return FALSE ;
			}
		#endif

			return TRUE ;
		}

		uint32 select_socket_api::send_ex (nk_socket s , const void * buf , uint32 len , uint32 flags )
		{
			int32 nSent;


		#if __LINUX__
			nSent = send(s,buf,len,flags);
		#elif __WINDOWS__
			nSent = send(s,(const char *)buf,len,flags);
		#endif

			if ( nSent == SOCKET_ERROR ) 
			{
		#if __LINUX__
				switch ( errno ) 
				{

				case EWOULDBLOCK : 
					return SOCKET_ERROR_WOULDBLOCK;

				case ECONNRESET :
				case EPIPE :

				case EBADF : 
				case ENOTSOCK : 
				case EFAULT : 
				case EMSGSIZE : 
				case ENOBUFS : 

				default : 
					{
						break;
					}
				}//end of switch
		#elif __WINDOWS__
				int32 iErr = WSAGetLastError() ;
				switch ( iErr ) 
				{
				case WSANOTINITIALISED : 
					strncpy_s( Error, "WSANOTINITIALISED", _ESIZE ) ;
					break ;
				case WSAENETDOWN : 
					strncpy_s( Error, "WSAENETDOWN", _ESIZE ) ;
					break ;
				case WSAEACCES : 
					strncpy_s( Error, "WSAEACCES", _ESIZE ) ;
					break ;
				case WSAEINTR : 
					strncpy_s( Error, "WSAEINTR", _ESIZE ) ;
					break ;
				case WSAEINPROGRESS : 
					strncpy_s( Error, "WSAEINPROGRESS", _ESIZE ) ;
					break ;
				case WSAEFAULT : 
					strncpy_s( Error, "WSAEFAULT", _ESIZE ) ;
					break ;
				case WSAENETRESET : 
					strncpy_s( Error, "WSAENETRESET", _ESIZE ) ;
					break ;
				case WSAENOBUFS : 
					strncpy_s( Error, "WSAENOBUFS", _ESIZE ) ;
					break ;
				case WSAENOTCONN : 
					strncpy_s( Error, "WSAENOTCONN", _ESIZE ) ;
					break ;
				case WSAENOTSOCK : 
					strncpy_s( Error, "WSAENOTSOCK", _ESIZE ) ;
					break ;
				case WSAEOPNOTSUPP : 
					strncpy_s( Error, "WSAEOPNOTSUPP", _ESIZE ) ;
					break ;
				case WSAESHUTDOWN : 
					strncpy_s( Error, "WSAESHUTDOWN", _ESIZE ) ;
					break ;
				case WSAEWOULDBLOCK : 
		//			strncpy_s( Error, "WSAEWOULDBLOCK", _ESIZE ) ;
					return SOCKET_ERROR_WOULDBLOCK ;
					break ;
				case WSAEMSGSIZE : 
					strncpy_s( Error, "WSAEMSGSIZE", _ESIZE ) ;
					break ;
				case WSAEHOSTUNREACH : 
					strncpy_s( Error, "WSAEHOSTUNREACH", _ESIZE ) ;
					break ;
				case WSAEINVAL : 
					strncpy_s( Error, "WSAEINVAL", _ESIZE ) ;
					break ;
				case WSAECONNABORTED : 
					strncpy_s( Error, "WSAECONNABORTED", _ESIZE ) ;
					break ;
				case WSAECONNRESET : 
					strncpy_s( Error, "WSAECONNRESET", _ESIZE ) ;
					break ;
				case WSAETIMEDOUT : 
					strncpy_s( Error, "WSAETIMEDOUT", _ESIZE ) ;
					break ;
				default :
					{
					strncpy_s( Error, "UNKNOWN", _ESIZE ) ;
					break ;
					};
				};//end of switch
		#endif
			} 
			else if ( nSent == 0 )
			{
			}
			return nSent;
		}


		uint32 select_socket_api::sendto_ex (nk_socket s , const void * buf , int32 len , uint32 flags , const struct sockaddr * to , int32 tolen )
		{
		#if __LINUX__
			int32 nSent = sendto(s,buf,len,flags,to,tolen);
		#elif __WINDOWS__
			int32 nSent = sendto(s,(const char *)buf,len,flags,to,tolen);
		#endif

			if ( nSent == SOCKET_ERROR ) 
			{
		#if __LINUX__
				switch ( errno ) 
				{

				case EWOULDBLOCK : 
					return 0;

				case ECONNRESET :
				case EPIPE :

				case EBADF : 
				case ENOTSOCK : 
				case EFAULT : 
				case EMSGSIZE : 
				case ENOBUFS : 

				default : 
					{
						break;
					}
				}	
		#elif __WINDOWS__
		#endif
			}

			return nSent;
		}

		uint32 select_socket_api::recv_ex (nk_socket s , void * buf , uint32 len , uint32 flags )
		{

		#if __LINUX__
			int32 nrecv = recv(s,buf,len,flags);
		#elif __WINDOWS__
			int32 nrecv = recv(s,(CHAR*)buf,len,flags);
		#endif

			if ( nrecv == SOCKET_ERROR ) 
			{
		#if __LINUX__
				switch ( errno ) 
				{

				case EWOULDBLOCK : 
					return SOCKET_ERROR_WOULDBLOCK;

				case ECONNRESET :
				case EPIPE :

				case EBADF : 
				case ENOTCONN : 
				case ENOTSOCK : 
				case EINTR : 
				case EFAULT : 

				default : 
					{
						break;
					}
				}//end of switch

		#elif __WINDOWS__
				int32 iErr = WSAGetLastError() ;
				switch ( iErr ) 
				{
				case WSANOTINITIALISED : 
					strncpy_s( Error, "WSANOTINITIALISED", _ESIZE ) ;
					break ;
				case WSAENETDOWN : 
					strncpy_s( Error, "WSAENETDOWN", _ESIZE ) ;
					break ;
				case WSAEFAULT : 
					strncpy_s( Error, "WSAEFAULT", _ESIZE ) ;
					break ;
				case WSAENOTCONN : 
					strncpy_s( Error, "WSAENOTCONN", _ESIZE ) ;
					break ;
				case WSAEINTR : 
					strncpy_s( Error, "WSAEINTR", _ESIZE ) ;
					break ;
				case WSAEINPROGRESS : 
					strncpy_s( Error, "WSAEINPROGRESS", _ESIZE ) ;
					break ;
				case WSAENETRESET : 
					strncpy_s( Error, "WSAENETRESET", _ESIZE ) ;
					break ;
				case WSAENOTSOCK : 
					strncpy_s( Error, "WSAENOTSOCK", _ESIZE ) ;
					break ;
				case WSAEOPNOTSUPP : 
					strncpy_s( Error, "WSAEOPNOTSUPP", _ESIZE ) ;
					break ;
				case WSAESHUTDOWN : 
					strncpy_s( Error, "WSAESHUTDOWN", _ESIZE ) ;
					break ;
				case WSAEWOULDBLOCK : 
		//			strncpy_s( Error, "WSAEWOULDBLOCK", _ESIZE ) ;
					return SOCKET_ERROR_WOULDBLOCK ;
					break ;
				case WSAEMSGSIZE : 
					strncpy_s( Error, "WSAEMSGSIZE", _ESIZE ) ;
					break ;
				case WSAEINVAL : 
					strncpy_s( Error, "WSAEINVAL", _ESIZE ) ;
					break ;
				case WSAECONNABORTED : 
					strncpy_s( Error, "WSAECONNABORTED", _ESIZE ) ;
					break ;
				case WSAETIMEDOUT : 
					strncpy_s( Error, "WSAETIMEDOUT", _ESIZE ) ;
					break ;
				case WSAECONNRESET : 
					strncpy_s( Error, "WSAECONNRESET", _ESIZE ) ;
					break ;
				default :
					{
					strncpy_s( Error, "UNKNOWN", _ESIZE ) ;
					break ;
					};
				};//end of switch
		#endif
			} 

			return nrecv;
	
		}


		/////////////////////////////////////////////////////////////////////
		// exception version of recvfrom()
		/////////////////////////////////////////////////////////////////////
		uint32 select_socket_api::recvfrom_ex (nk_socket s , void * buf , int32 len , uint32 flags , struct sockaddr * from , uint32 * fromlen )
		{
		#if __LINUX__
			int32 nReceived = recvfrom(s,buf,len,flags,from,fromlen);

		#elif __WINDOWS__
			int32 nReceived = recvfrom(s,(char*)buf,len,flags,from,(int32*)fromlen);
		#endif

			if ( nReceived == SOCKET_ERROR ) 
			{
		#if __LINUX__
				switch ( errno ) 
				{

				case EWOULDBLOCK : 
					return SOCKET_ERROR_WOULDBLOCK;

				case ECONNRESET :
				case EPIPE :

				case EBADF : 
				case ENOTCONN : 
				case ENOTSOCK : 
				case EINTR : 
				case EFAULT : 

				default : 
					{
						break;
					}
				}//end of switch
		#elif __WINDOWS__
		#endif
			}

			return nReceived;
		}

		bool select_socket_api::closesocket_ex (nk_socket s )
		{

		#if __LINUX__
			close(s);
		#elif __WINDOWS__
			if ( closesocket(s) == SOCKET_ERROR ) 
			{
				int32 iErr = WSAGetLastError() ;
				switch ( iErr ) 
				{
				case WSANOTINITIALISED : 
					strncpy_s( Error, "WSANOTINITIALISED", _ESIZE ) ;
					break ;
				case WSAENETDOWN : 
					strncpy_s( Error, "WSAENETDOWN", _ESIZE ) ;
					break ;
				case WSAENOTSOCK : 
					strncpy_s( Error, "WSAENOTSOCK", _ESIZE ) ;
					break ;
				case WSAEINPROGRESS : 
					strncpy_s( Error, "WSAEINPROGRESS", _ESIZE ) ;
					break ;
				case WSAEINTR : 
					strncpy_s( Error, "WSAEINTR", _ESIZE ) ;
					break ;
				case WSAEWOULDBLOCK : 
					strncpy_s( Error, "WSAEWOULDBLOCK", _ESIZE ) ;
					break ;
				default : 
					{
					strncpy_s( Error, "UNKNOWN", _ESIZE ) ;
					break ;
					};
				};//end of switch

				return FALSE ;
			}
		#endif

			return TRUE ;
		}

		bool select_socket_api::ioctlsocket_ex (nk_socket s , long cmd , ulong * argp )
		{
		#if __LINUX__
		#elif __WINDOWS__
			if ( ioctlsocket(s,cmd,argp) == SOCKET_ERROR ) 
			{
				int32 iErr = WSAGetLastError() ;
				switch ( iErr ) 
				{
				case WSANOTINITIALISED : 
					strncpy_s( Error, "WSANOTINITIALISED", _ESIZE ) ;
					break ;
				case WSAENETDOWN : 
					strncpy_s( Error, "WSAENETDOWN", _ESIZE ) ;
					break ;
				case WSAEINPROGRESS : 
					strncpy_s( Error, "WSAEINPROGRESS", _ESIZE ) ;
					break ;
				case WSAENOTSOCK : 
					strncpy_s( Error, "WSAENOTSOCK", _ESIZE ) ;
					break ;
				case WSAEFAULT : 
					strncpy_s( Error, "WSAEFAULT", _ESIZE ) ;
					break ;
				default :
					{
					strncpy_s( Error, "UNKNOWN", _ESIZE ) ;
					break ;
					};
				};

				return FALSE ;
			}
		#endif

			return TRUE ;
		}
 

		bool select_socket_api::getsocketnonblocking_ex(nk_socket s )
		{

		#if __LINUX__
				int32 flags = nk_file_api::fcntl_ex( s , F_GETFL , 0 );

			return flags | O_NONBLOCK;
		#elif __WINDOWS__
			return FALSE ;
		#endif
		}


		bool select_socket_api::setsocketnonblocking_ex(nk_socket s, bool on)
		{
#if __LINUX__
			int32 flags = nk_file_api::fcntl_ex(s, F_GETFL, 0);

			if (on)
				// make nonblocking fd
				flags |= O_NONBLOCK;
			else
				// make blocking fd
				flags &= ~O_NONBLOCK;

			nk_file_api::fcntl_ex(s, F_SETFL, flags);

			return TRUE;
#elif __WINDOWS__

			ULONG argp = (on == TRUE) ? 1 : 0;
			return ioctlsocket_ex(s, FIONBIO, &argp);

#endif
		}


		uint32 select_socket_api::availablesocket_ex(nk_socket s)
		{

#if __LINUX__
			return nk_file_api::availablefile_ex(s);
#elif __WINDOWS__
			ULONG argp = 0;
			ioctlsocket_ex(s, FIONREAD, &argp);
			return argp;
#endif
		}

		bool select_socket_api::shutdown_ex(nk_socket s, uint32 how)
		{
			if (shutdown(s, how) < 0)
			{
#if __LINUX__
				switch (errno) {
				case EBADF:
				case ENOTSOCK:
				case ENOTCONN:
				default:
				{
					break;
				}
				}
#elif __WINDOWS__
			int32 iErr = WSAGetLastError();
			switch (iErr)
			{
			case WSANOTINITIALISED:
				strncpy_s(Error, "WSANOTINITIALISED", _ESIZE);
				break;
			case WSAENETDOWN:
				strncpy_s(Error, "WSAENETDOWN", _ESIZE);
				break;
			case WSAEINVAL:
				strncpy_s(Error, "WSAEINVAL", _ESIZE);
				break;
			case WSAEINPROGRESS:
				strncpy_s(Error, "WSAEINPROGRESS", _ESIZE);
				break;
			case WSAENOTCONN:
				strncpy_s(Error, "WSAENOTCONN", _ESIZE);
				break;
			case WSAENOTSOCK:
				strncpy_s(Error, "WSAENOTSOCK", _ESIZE);
				break;
			default:
				{
					strncpy_s(Error, "UNKNOWN", _ESIZE);
					break;
				};
			};
#endif

			return FALSE;
			}

			return TRUE;
		}


		int32 select_socket_api::select_ex(int32 maxfdp1, fd_set * readset, fd_set * writeset, fd_set * exceptset, struct timeval * timeout)
		{

			int32 result;

			result = select(maxfdp1 , readset , writeset , exceptset , timeout);
			if (result == SOCKET_ERROR)
			{
	#if __LINUX__

	#elif __WINDOWS__
			int32 iErr = WSAGetLastError();
			switch (iErr)
			{
			case WSANOTINITIALISED:
				strncpy_s(Error, "WSANOTINITIALISED", _ESIZE);
				break;
			case WSAEFAULT:
				strncpy_s(Error, "WSAEFAULT", _ESIZE);
				break;
			case WSAENETDOWN:
				strncpy_s(Error, "WSAENETDOWN", _ESIZE);
				break;
			case WSAEINVAL:
				strncpy_s(Error, "WSAEINVAL", _ESIZE);
				break;
			case WSAEINTR:
				strncpy_s(Error, "WSAEINTR", _ESIZE);
				break;
			case WSAEINPROGRESS:
				strncpy_s(Error, "WSAEINPROGRESS", _ESIZE);
				break;
			case WSAENOTSOCK:
				strncpy_s(Error, "WSAENOTSOCK", _ESIZE);
				break;
			default:
				{
				strncpy_s(Error, "UNKNOWN", _ESIZE);
				break;
				};
			};
	#endif
			}//end if
			

			return result;

		}

	}
}


