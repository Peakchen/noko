
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

