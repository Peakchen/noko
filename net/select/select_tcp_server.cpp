#include "select_tcp_server.h"
#include "select_message_handler.h"

namespace noko 
{
	namespace select_tcp_server
	{
		bool dispatchmessage(const void* outbuff, size_t nlength)
		{
			if (outbuff == nullptr || nlength <= 0)
			{
				return false;
			}

			const TESGHandler* pesgHandler = static_cast<const TESGHandler*>(outbuff);
			messageHandler handler = select_message_handler::instance().getmessagehandler(pesgHandler->nSID);
			if (handler)
			{
				return handler(pesgHandler->szbuff);
			}

			return false;
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