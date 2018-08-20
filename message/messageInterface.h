#pragma once
#include "CommonDef.h"
#include "Netdefine.h"


namespace noko
{
	template<M>
	class messageInterface
	{

		private:
			std::map<int32, M> m_mapmessage;
	};
}