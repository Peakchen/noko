

#ifndef __SINGLETON__H__
#define __SINGLETON__H__

#include "boost\smart_ptr\shared_ptr.hpp"

namespace noko {
#define SINGLETON(T) \
	public:\
		static T& instance() {	\
			static std::shared_ptr<T> _ins;\
			if (!_ins) {			\
				_ins = std::make_shared<T>();\
			}\
			return *_ins;	\
	}\
	public:\
		T() = default;\
		~T() = default;
}

#endif

