#include "core/componentStates/LoopState.hpp"
#include "game/backend/Self.hpp"

namespace YimMenu::Features
{
	class Godmode : public LoopState
	{
		using LoopState::LoopState;

		virtual void OnTick() override
		{
			if (!Self::GetPed())
				return;

			if (Self::GetPed().IsDead())
				Self::GetPed().SetInvincible(false);
			else
				Self::GetPed().SetInvincible(true);
		}

		virtual void OnDisable() override
		{
			if (!Self::GetPed())
				return;

			Self::GetPed().SetInvincible(false);
		}
	};

	inline Godmode _Godmode{"godmode", "God Mode", "Blocks all incoming damage"};
}