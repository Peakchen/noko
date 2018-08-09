
/*
*  CopyRight(C) stefanchen e-mail:2572915486@qq.com 
*  
*  select
*/
#pragma once

#include "session.h"
#include "Singleton.h"
#include "Netdefine.h"
#include <unordered_map>
#include "session_define.h"

#ifndef __SESSION_MANAGER__H__
#define __SESSION_MANAGER__H__

namespace noko {

	class SessionManager
	{
		SINGLETON(SessionManager)
	public:

		uint32 add(const char* szHost, uint16 port);
		bool   remove(uint32 nsessionid);
		bool   hasSession(uint32 nessionid);

		bool   startNewconnect(uint32 nsessionid, bool isReuse = false);
		bool   closeConnect(uint32 nsessionid);
		bool   dispatchmessage(uint32 nsessionid, void* pbuff, uint32 nsize);
		bool   startrun(uint32 nsessionid);
		bool   checktimeout();

	private:
		uint32 autoAddSessionid();

	private:
		uint32 m_sessionid = 0U;
		std::unordered_map<uint32, SessionPtr> m_mapsession;

	};

}

#endif 