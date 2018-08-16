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

