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
#include "Register/Register.hpp"
#include "Io/Io.hpp"
#include "StartUp/SystemClock.hpp"
#include "Common/Tags.hpp"

#define LPC11U68_BOARD
//#define LPC1768_BOARD
//#define LPC1549_BOARD

#ifdef LPC11U68_BOARD
#include "Chip/Lpc11u68.hpp"
#else
#ifdef LPC1768_BOARD
#include "Chip/Lpc1768.hpp"
#else
#ifdef LPC1549_BOARD
#include "Chip/Lpc1549.hpp"
#else

#endif
#endif
#endif


namespace Hardware{
#ifdef LPC11U68_BOARD
	constexpr Kvasir::Io::PinLocationT<2,16> ledPin{};
	using Clock = Kvasir::SystemClock::ExternalOsciRawSettings<Kvasir::System::ClockConfig,3,1>;
	using TimerDefaultConfig = Kvasir::Timer::TC16B0DefaultConfig;
#else
#ifdef LPC1768_BOARD
	constexpr Kvasir::Io::PinLocationT<0,22> ledPin{};
	struct MyOsciSettings{
		static void init(){
			using namespace Kvasir;
			using namespace Kvasir::System;
			apply(ControlStatus::mainOscillatorEnable);
			/* Wait for osc to stabilize */
			while(ControlStatus::MainOscilatorStatus::read() == false){}
			apply(CpuClockConfig::Divider::makeAction<3>());
			apply(CpuClockConfig::PllSourceSelect::mainOscillator);
			apply(CpuClockConfig::PllConfiguration::makeMultiplierAction<11>());
			apply(CpuClockConfig::PllControl::enable);
			apply(CpuClockConfig::PllFeed::firstStep);
			apply(CpuClockConfig::PllFeed::secondStep);

			while(CpuClockConfig::PllStatus::LockStatus::read() == false){}
			apply(CpuClockConfig::Flash::fourSysclock);
			apply(CpuClockConfig::PllControl::connect);
			apply(CpuClockConfig::PllFeed::firstStep);
			apply(CpuClockConfig::PllFeed::secondStep);
		}
	};
	using Clock = MyOsciSettings;
	using TimerDefaultConfig = Kvasir::Timer::TC0DefaultConfig;
#else
#ifdef LPC1549_BOARD
	constexpr Kvasir::Io::PinLocationT<0,25> ledPin{};
	struct MyOsciSettings{
		static void init(){
			using namespace Kvasir::System;
			using Kvasir::Register::value;
			apply(clear(PowerConfiguration::systemOscillatorPoweredDown));
			for (volatile int i = 0; i < 2500; i++) {} //wait for oscillator to stabilize
			apply(Pll::ClockSource::systemOscillator);
			apply(set(PowerConfiguration::systemPllPoweredDown));
			apply(write(Pll::Control::feedbackDivider,value<5>()),
				write(Pll::Control::postDivider,value<Pll::PostDividerRatio,Pll::PostDividerRatio::div4>()));
			apply(clear(PowerConfiguration::systemPllPoweredDown));
			while(!apply(read(Pll::statusLocked))){};
			apply(
				write(AHBClock::divider,value<1>()),
				Flash::threeSysclock);
			apply(ClockSource::Main::pllOutput);
		}
	};

	using Clock = MyOsciSettings;
	using TimerDefaultConfig = Kvasir::Timer::Timer0DefaultConfig;
#else

#endif
#endif
#endif
}

KVASIR_CLOCK(Hardware::Clock)

