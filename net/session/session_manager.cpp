#include "session_manager.h"


namespace noko 
{
	
	uint32 SessionManager::add(const char* szHost, uint16 port)
	{
		uint32 inewid = autoAddSessionid();
		SessionPtr& session = m_mapsession[inewid];
		session = std::shared_ptr<select_session>();
		session.get()->init(szHost, port);
		return m_sessionid;
	}

	bool SessionManager::remove(uint32 nsessionid)
	{
		if (!hasSession(nsessionid))
		{
			return false;
		}

		m_mapsession.erase(nsessionid);
		return true;
	}

	bool SessionManager::startNewconnect(uint32 nsessionid, bool isReuse)
	{
		if (!hasSession(nsessionid))
		{
			return false;
		}

		SessionPtr session = m_mapsession[nsessionid];
		session.get()->create();
		session.get()->setReuseAddr(isReuse);
		session.get()->bind();
		session.get()->listen();
		session.get()->accept();
		return true;
	}

	bool SessionManager::closeConnect(uint32 nsessionid)
	{
		if (!hasSession(nsessionid))
		{
			return false;
		}

		SessionPtr session = m_mapsession[nsessionid];
		session.get()->close();
		m_mapsession.erase(nsessionid);
		return true;
	}

	bool SessionManager::dispatchmessage(uint32 nsessionid, void* pbuff, uint32 nsize)
	{
		if (!hasSession(nsessionid))
		{
			return false;
		}

		SessionPtr session = m_mapsession[nsessionid];
		session.get()->receive(pbuff, nsize);

		return true;
	}

	bool SessionManager::startrun(uint32 nsessionid, cb_dispatchmessage ssp)
	{
		if (!hasSession(nsessionid))
		{
			return false;
		}

		SessionPtr session = m_mapsession[nsessionid];
		return session.get()->startselect(ssp);
	}

	bool SessionManager::checktimeout()
	{
		for each (auto session in m_mapsession)
		{
			if (GetTime() - session.second.get()->getsessionTick() >= SELECT_TIME_COUT_TICK)
			{
				session.second.get()->close();
				break;
			}
		}

		return true;
	}

	std::unordered_map<uint32, SessionPtr>& SessionManager::getSessionDic()
	{
		return m_mapsession;
	}

	bool SessionManager::hasSession(uint32 nsessionid)
	{
		return (m_mapsession.find(nsessionid) != m_mapsession.end());
	}

	uint32 SessionManager::autoAddSessionid()
	{
		return m_sessionid > _MAX_SESSION_ID ? _MAX_SESSION_ID : m_sessionid + 1;
	}

}