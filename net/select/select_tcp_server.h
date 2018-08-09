
/************************************************************************/
/* 
	CopyRight(C) StefanChen e-mail: 2572915286@qq.com
	purpose: select socket server manager module.
*/
/************************************************************************/

#ifndef __SELECT_TCP_SERVER__H__
#define __SELECT_TCP_SERVER__H__

#pragma once
#include "CommonDef.h"
#include "session/session_manager.h"

namespace noko {


	class select_tcp_server
	{

	public:
		select_tcp_server();
		~select_tcp_server();


		bool	start(const char* szip, const uint16 port);
		
		bool	recv();

		bool    disconnect();
	};

}

#endif // __SELECT_TCP_SERVER__H__