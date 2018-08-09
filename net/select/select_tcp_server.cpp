#include "select_tcp_server.h"

namespace noko 
{

	select_tcp_server::select_tcp_server()
	{

	}

	select_tcp_server::~select_tcp_server()
	{

	}

	bool select_tcp_server::start(const char* szip, const uint16 port)
	{

		uint32 unsessionid = SessionManager::instance().add(szip, port);
		SessionManager::instance().startNewconnect(unsessionid);
		SessionManager::instance().startrun(unsessionid);

		return true;
	}

	bool select_tcp_server::disconnect()
	{
		return true;
	}

}