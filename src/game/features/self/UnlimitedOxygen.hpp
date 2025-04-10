#include "core/componentStates/LoopState.hpp"
#include "game/backend/Self.hpp"

namespace YimMenu::Features
{
	class UnlimitedOxygen : public LoopState
	{
		using LoopState::LoopState;

		virtual void OnTick() override
		{
			Self::GetPed().SetMaxTimeUnderwater(INT_MAX);
		}

		virtual void OnDisable() override
		{
			Self::GetPed().SetMaxTimeUnderwater(-1.0f); // default value
		}
	};

	inline UnlimitedOxygen _UnlimitedOxygen{"unlimitedoxygen", "Unlimited Oxygen", "Allows you to stay underwater without losing oxygen."};
}