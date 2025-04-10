#include "core/componentStates/LoopState.hpp"
#include "game/backend/Self.hpp"

namespace YimMenu::Features
{
	class InfiniteClip : public LoopState
	{
		using LoopState::LoopState;

		virtual void OnTick() override
		{
			if (Self::GetPed())
				Self::GetPed().SetInfiniteClip(true);
		}

		virtual void OnDisable() override
		{
			if (Self::GetPed())
				Self::GetPed().SetInfiniteClip(false);
		}
	};

	// https://github.com/YimMenu/YimMenu/discussions/2177
	inline InfiniteClip _InfiniteClip{"infiniteclip", "Freeze Clip", "Freeze clip ammo (no reload)"};
}