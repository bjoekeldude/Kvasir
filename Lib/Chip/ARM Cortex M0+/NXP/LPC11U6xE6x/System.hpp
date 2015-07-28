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
#pragma once
#include "Register/Register.hpp"

namespace Kvasir{
namespace System{
namespace PowerConfiguration {
	using Address = Register::Address<
		0x40048238,
		Register::maskFromRange(9,9,12,11,31,14)>;

	static constexpr 	Register::RWBitLocT<Address, 0>		ircOscillatorOutputPoweredDown{};
	static constexpr 	Register::RWBitLocT<Address, 1>		ircOscillatorPoweredDown{};
	static constexpr 	Register::RWBitLocT<Address, 2>		flashPoweredDown{};
	static constexpr	Register::RWBitLocT<Address, 3>		brownOutDetectPoweredDown{};
	static constexpr 	Register::RWBitLocT<Address, 4>		adcPoweredDown{};
	static constexpr 	Register::RWBitLocT<Address, 5>		crystalOscillatorPoweredDown{};
	static constexpr 	Register::RWBitLocT<Address, 6>		watchdogOscillatorPoweredDown{};
	static constexpr 	Register::RWBitLocT<Address, 7>		systemPllPoweredDown{};
	static constexpr 	Register::RWBitLocT<Address, 8>		usbPllPoweredDown{};
	// bit  9 reserved
	static constexpr 	Register::RWBitLocT<Address, 10>		usbTransceiverPoweredDown{};
	// bits 12:11 reserved
	static constexpr 	Register::RWBitLocT<Address, 13>		temperaturSensorPoweredDown{};
	// bits 31:14 reserved

}

struct ClockControl{			//SYSAHBCLKCTRL register actions
	using Address = Register::Address<
		0x40048080,
		Register::maskFromRange(0,0,17,17)>;

	// bit  0 is sys which is always on
	static constexpr 	Register::RWBitLocT<Address, 1>			romClockEnabled{};
	static constexpr 	Register::RWBitLocT<Address, 2>			ram0ClockEnabled{};
	static constexpr 	Register::RWBitLocT<Address, 3>			flashRegClockEnabled{};
	static constexpr 	Register::RWBitLocT<Address, 4>			flashArrayClockEnabled{};
	static constexpr 	Register::RWBitLocT<Address, 5>			i2C0ClockEnabled{};
	static constexpr 	Register::RWBitLocT<Address, 6>			gpioClockEnabled{};
	static constexpr 	Register::RWBitLocT<Address, 7>			ct16B0ClockEnabled{};
	static constexpr 	Register::RWBitLocT<Address, 8>			ct16B1ClockEnabled{};
	static constexpr 	Register::RWBitLocT<Address, 9>			ct32B0ClockEnabled{};
	static constexpr 	Register::RWBitLocT<Address, 10>		ct32B1ClockEnabled{};
	static constexpr 	Register::RWBitLocT<Address, 11>		ssp0ClockEnabled{};
	static constexpr 	Register::RWBitLocT<Address, 12>		usart0ClockEnabled{};
	static constexpr 	Register::RWBitLocT<Address, 13>		adcClockEnabled{};
	static constexpr 	Register::RWBitLocT<Address, 14>		usbClockEnabled{};
	static constexpr 	Register::RWBitLocT<Address, 15>		wwdtClockEnabled{};
	static constexpr 	Register::RWBitLocT<Address, 16>		ioconClockEnabled{};
	// bit  17 is reserved
	static constexpr 	Register::RWBitLocT<Address, 18>		ssp1ClockEnabled{};
	static constexpr 	Register::RWBitLocT<Address, 19>		pintClockEnabled{};
	static constexpr 	Register::RWBitLocT<Address, 20>		usart1ClockEnabled{};
	static constexpr 	Register::RWBitLocT<Address, 21>		usart2ClockEnabled{};
	static constexpr 	Register::RWBitLocT<Address, 22>		usart3And4ClockEnabled{};
	static constexpr 	Register::RWBitLocT<Address, 23>		group0IntClockEnabled{};
	static constexpr 	Register::RWBitLocT<Address, 24>		group1IntClockEnabled{};
	static constexpr 	Register::RWBitLocT<Address, 25>		i2c1ClockEnabled{};
	static constexpr 	Register::RWBitLocT<Address, 26>		ram1ClockEnabled{};
	static constexpr 	Register::RWBitLocT<Address, 27>		usbRamClockEnabled{};
	static constexpr 	Register::RWBitLocT<Address, 28>		ctcClockEnabled{};
	static constexpr 	Register::RWBitLocT<Address, 29>		dmaClockEnabled{};
	static constexpr 	Register::RWBitLocT<Address, 30>		rtcClockEnabled{};
	static constexpr 	Register::RWBitLocT<Address, 31>		sctClockEnabled{};

	static constexpr 	Register::RWFieldLocT<Register::Address<
		0x40048094,	Register::maskFromRange(31,6)>,5,0> feedbackDivider{};
};

struct ClockConfig{
private:
	using Address1 = Register::Address<
			0x400440F0,
			Register::maskFromRange(9,9,31,16)>;
	using Address2 = Register::Address<
			0x400440F4,
			Register::maskFromRange(9,9,31,16)>;
	static constexpr Register::RWFieldLocT<Address1,2,0> 		xtalinFunction{};
	static constexpr Register::RWFieldLocT<Address2,2,0> 		xtaloutFunction{};
	static constexpr Register::RWFieldLocT<Address1,4,3> 		xtalinMode{};
	static constexpr Register::RWFieldLocT<Address2,4,3> 		xtaloutMode{};
	static constexpr Register::RWBitLocT<Address1,7>			xtalinIsDigitalMode{};
	static constexpr Register::RWBitLocT<Address2,7> 			xtaloutIsDigitalMode{};
public:
	static constexpr auto externalCrystalInit = MPL::list(
			set(ClockControl::ioconClockEnabled),
			Register::sequencePoint,
			write(xtalinFunction,Register::value<1>()),
			write(xtaloutFunction,Register::value<1>()),
			write(xtalinMode,Register::value<0>()),
			write(xtaloutMode,Register::value<0>()),
			clear(xtalinIsDigitalMode),
			clear(xtaloutIsDigitalMode)
			);
	static constexpr auto crystalOscillatorPowerOn = clear(PowerConfiguration::crystalOscillatorPoweredDown);
	static constexpr auto systemPllPowerOff = set(PowerConfiguration::systemPllPoweredDown);
	static constexpr auto systemPllPowerOn = clear(PowerConfiguration::systemPllPoweredDown);

	struct FlashConfiguration{
		using Address = Register::Address<
				0x4003C010,
				Register::maskFromRange(31,2)>;
		enum class Config {oneSysclock, twoSysclock};
		static constexpr Register::RWFieldLocT<Address, 1, 0, Config> config{};
		static constexpr auto defaultConfig = write(config,Register::value<Config,Config::twoSysclock>());
	};
	struct MainClock{
		using Address1 = Register::Address<
				0x40048070,
				Register::maskFromRange(31,2)>;

		using Address2 = Register::Address<
				0x40048074,
				Register::maskFromRange(31,1)>;

		enum class Source {internalRc, pllInput, warchdogOscillator, pllOutput};
		static constexpr Register::RWFieldLocT<Address1, 1, 0, Source>	source{};
		template<Source S>
		static constexpr decltype(write(source,Register::value<Source,S>())) writeSource(){ return{}; };

		static constexpr	Register::RWBitLocT<Address2, 0>		sourceUpdater{};
		static constexpr auto updateSourceSequence =
				MPL::list(clear(sourceUpdater),Register::sequencePoint,set(sourceUpdater));
	};
	struct SystemPllClock{
		using Address1 = Register::Address<
				0x40048040,
				Register::maskFromRange(31,2)>;
		using Address2 = Register::Address<
				0x40048044,
				Register::maskFromRange(31,1)>;

		enum class Source {internalRc, systemOscillator, clock32khz};
		static constexpr Register::RWFieldLocT<Address1, 1, 0, Source>	source{};
		template<Source S>
		static constexpr decltype(write(source,Register::value<Source,S>())) writeSource(){ return {}; };

		static constexpr	Register::RWBitLocT<Address2, 0>		sourceUpdater{};
		static constexpr auto updateSourceSequence =
				MPL::list(clear(sourceUpdater),Register::sequencePoint,set(sourceUpdater));
	};
	struct SystemPLLControl{
		using Address = Register::Address<
				0x40048008,
				Register::maskFromRange(31,7)>;
		enum class PostDividerRatio {div1, div2, div4, div8};
		static constexpr Register::RWFieldLocT<Address,4,0> feedbackDivider{};
		static constexpr Register::RWFieldLocT<Address,6,5,PostDividerRatio> postDivider{};
	};
	static constexpr Register::RWBitLocT<
		Register::Address<0x4004800C,Register::maskFromRange(31,1)>,0> systemPllStatusLocked{};
	struct SystemAHBClock{
		using Address = Register::Address<
				0x40048078,
				Register::maskFromRange(31,8)>;
		static constexpr Register::RWFieldLocT<Address,7,0> divider{};
	};
};
}
}
