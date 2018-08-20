#include "select_message_handler.h"
#include "Netdefine.h"

namespace noko 
{

#define SELECT_MESSAGE_REGISTER(id, handler) if(m_mapMessageHandler.find(id) != m_mapMessageHandler.end()) return; \
		else {m_mapMessageHandler[id] = handler; }

	messageHandler select_message_handler::getmessagehandler(int32 id)
	{
		if (m_mapMessageHandler.find(id) == m_mapMessageHandler.end())
		{
			return nullptr;
		}
		else {
			return m_mapMessageHandler[id];
		}
	}

	void select_message_handler::registermessage()
	{
		SELECT_MESSAGE_REGISTER(em_SID_LOGIN, dispatchLoginMessage);
	}

	
	bool select_message_handler::dispatchLoginMessage(const void* szbuff)
	{

	}

	bool select_message_handler::dispatchDBMessage(const void* szbuff)
	{

	}

}