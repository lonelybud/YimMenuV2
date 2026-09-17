#include "core/componentStates/LoopState.hpp"
#include "core/componentStates/CallCode.hpp"
#include "game/gta/Natives.hpp"
#include "core/backend/ScriptMgr.hpp"

namespace YimMenu::Features
{
	inline static int worldHour{}, worldMinute{}, worldSecond{};

	class FreezeNetworkTime : public LoopState
	{
		using LoopState::LoopState;

		virtual void OnTick() override
		{
			NETWORK::NETWORK_OVERRIDE_CLOCK_TIME(worldHour, worldMinute, worldSecond);
			ScriptMgr::Yield(1000ms);
		}

		virtual void OnDisable() override
		{
			NETWORK::NETWORK_CLEAR_CLOCK_TIME_OVERRIDE();
		}
	};

	inline FreezeNetworkTime _FreezeTime{"freezenetworktime", "Freeze Time", "Freezes the online clock at the selected time"};
}
