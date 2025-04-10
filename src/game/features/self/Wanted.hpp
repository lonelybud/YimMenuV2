#include "core/componentStates/LoopState.hpp"
#include "game/backend/Self.hpp"
// #include "game/gta/Natives.hpp"

namespace YimMenu::Features
{
	class NeverWanted : public LoopState
	{
		using LoopState::LoopState;

		virtual void OnTick() override
		{
			Self::GetPlayer().SetWantedLevel(0);
			// PLAYER::SET_MAX_WANTED_LEVEL(0);
		}

		// virtual void OnDisable() override
		// {
		// 	PLAYER::SET_MAX_WANTED_LEVEL(6);		
		// }
	};

	inline NeverWanted _NeverWanted{"neverwanted", "Never Wanted", "Never gain a wanted level"};
}