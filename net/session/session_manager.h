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



#ifndef __SESSION_MANAGER__H__
#define __SESSION_MANAGER__H__
#pragma once


#include "session.h"
#include "Singleton.h"
#include "Netdefine.h"
#include <unordered_map>
#include "session_define.h"


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
		bool   startrun(uint32 nsessionid, cb_dispatchmessage ssp);
		bool   checktimeout();

		std::unordered_map<uint32, SessionPtr>& getSessionDic();

	private:
		uint32 autoAddSessionid();

	private:
		uint32 m_sessionid = 0U;
		std::unordered_map<uint32, SessionPtr> m_mapsession;

	};

}

#endif 