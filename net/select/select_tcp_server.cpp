#include "select_tcp_server.h"

namespace noko 
{
	namespace select_tcp_server
	{
		bool dispatchmessage(const void* outbuff, size_t nlength)
		{

			return true;
		}

		bool start(const char* szip, const uint16 port)
		{

			uint32 unsessionid = SessionManager::instance().add(szip, port);
			SessionManager::instance().startNewconnect(unsessionid);
			SessionManager::instance().startrun(unsessionid, dispatchmessage);

			return true;
		}

		bool disconnect()
		{
			std::unordered_map<uint32, SessionPtr>& mSessionDic = SessionManager::instance().getSessionDic();
			for each (auto sessionItem in mSessionDic)
			{
				sessionItem.second.get()->close();
			}

			mSessionDic.clear();
			return true;
		}
	}
}