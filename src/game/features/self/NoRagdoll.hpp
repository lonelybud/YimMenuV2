#include "core/componentStates/LoopState.hpp"
#include "game/backend/Self.hpp"

namespace YimMenu::Features
{
	class NoRagdoll : public LoopState
	{
		using LoopState::LoopState;

		virtual void OnTick() override
		{
			if (!Self::GetPed())
				return;
			
			Self::GetPed().SetRagdoll(false);
			Self::GetPlayer().SetFallDistanceOverride(99999.0f);

			// standonvehicles: Prevents you from ragdolling when standing on top of vehicles.
			// PED::SET_PED_RESET_FLAG(Self::GetPed().GetHandle(), 274, true);
		}

		virtual void OnDisable() override
		{
			if (!Self::GetPed())
				return;

			Self::GetPed().SetRagdoll(true);
			Self::GetPlayer().SetFallDistanceOverride(0.0f);
		}
	};

	inline NoRagdoll _NoRagdoll{"noragdoll", "No Ragdoll", "Prevents your ped from ragdolling"};
}