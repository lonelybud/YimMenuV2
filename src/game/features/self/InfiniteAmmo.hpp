#include "core/componentStates/LoopState.hpp"
#include "game/backend/Self.hpp"

namespace YimMenu::Features
{
	class InfiniteAmmo : public LoopState
	{
		using LoopState::LoopState;

		virtual void OnTick() override
		{
			if (Self::GetPed())
				Self::GetPed().SetInfiniteAmmo(true);
		}

		virtual void OnDisable() override
		{
			if (Self::GetPed())
				Self::GetPed().SetInfiniteAmmo(false);
		}
	};

	// https://github.com/YimMenu/YimMenu/discussions/2177
	inline InfiniteAmmo _InfiniteAmmo{"infiniteammo", "Freeze Ammo", "(clip + refill) = ammo = constant"};
}	