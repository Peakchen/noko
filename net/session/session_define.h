
/*
* CopyRight(C) add by stefanchen 
* 
*/

#ifndef __SESSION_DEFINE__H__
#define __SESSION_DEFINE__H__
#pragma once

#include "CommonDef.h"

namespace noko {

#define _MAX_SESSION_ID 100000

	//connect callback
	typedef std::function<bool()> cb_connect;
	typedef std::function<bool()> cb_close;
	typedef std::function<bool(uint32, byte*)> cb_dispatchmessage;

	struct TSession
	{
		char   szIP[IP_SIZE];
		uint16 nPort;

		// connect, close, dispatch message (recv,accept...)
		cb_connect _fconn;
		cb_close _fclose;
		cb_dispatchmessage _fdispatchmessage;

		TSession()
		{
			memset(this, 0, sizeof(*this));
		}
	};

	using SessionPtr = std::shared_ptr<select_session>;
}

#endif // !__SESSION_DEFINE__H__

