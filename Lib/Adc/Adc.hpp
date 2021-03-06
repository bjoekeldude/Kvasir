#pragma once
/**************************************************************************
Copyright 2015 Odin Holmes
Licensed under the Apache License, Version 2.0 (the "License");
you may not use this file except in compliance with the License.
You may obtain a copy of the License at
http://www.apache.org/licenses/LICENSE-2.0
Unless required by applicable law or agreed to in writing, software
distributed under the License is distributed on an "AS IS" BASIS,
WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
See the License for the specific language governing permissions and
limitations under the License.
****************************************************************************/
#include "Tags.hpp"
#include "Register.hpp"

namespace Kvasir{
namespace ADC{
	template<typename TDerived, typename TConfig>
	class Base{
	protected:
		void onConversion(int, Tag::ADCChannel){}
	using Config = TConfig;

	public:
		static constexpr auto init = MPL::list(
				Config::powerOn,
				Register::sequencePoint);

	};
}
}
