#include "core/componentStates/LoopState.hpp"
#include "core/componentStates/CallCode.hpp"
#include "game/gta/Natives.hpp"

namespace YimMenu::Features
{
	inline static int worldHour{}, worldMinute{}, worldSecond{};

	class SetNetworkTime : public CallCode
	{
		using CallCode::CallCode;

		virtual void OnCall() override
		{
			NETWORK::NETWORK_OVERRIDE_CLOCK_TIME(worldHour, worldMinute, worldSecond);
		}
	};

	class ClearNetworkTime : public CallCode
	{
		using CallCode::CallCode;

		virtual void OnCall() override
		{
			NETWORK::NETWORK_CLEAR_CLOCK_TIME_OVERRIDE();
		}
	};

	// class FreezeNetworkTime : public LoopState
	// {
	// 	using LoopState::LoopState;

	// 	virtual void OnTick() override
	// 	{
	// 		NETWORK::NETWORK_OVERRIDE_CLOCK_TIME(worldHour, worldMinute, worldSecond);
	// 	}

	// 	virtual void OnDisable() override
	// 	{
	// 		NETWORK::NETWORK_CLEAR_CLOCK_TIME_OVERRIDE();
	// 	}
	// };

	inline SetNetworkTime _SetNetworkTime{"setnetworktime", "Set Time", "Sets the current online time"};
	inline ClearNetworkTime _ClearNetworkTime{"clearnetworktime", "Clear Time", "Clear the overrided online time"};
	// inline FreezeNetworkTime _FreezeTime{"freezenetworktime", "Freeze Time", "Freezes the online clock at the selected time"};
}
