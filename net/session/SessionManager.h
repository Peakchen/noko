
/*
*  CopyRight(C) stefanchen e-mail:2572915486@qq.com 
*  
*  select
*/
#pragma once

#include "session.h"
#include "Singleton.h"

#ifndef __SESSION_MANAGER__H__
#define __SESSION_MANAGER__H__

namespace noko {

	class SessionManager
	{
		SINGLETON(SessionManager)
	public:

		void add();
		void remove();

	private:

	};

}

#endif 