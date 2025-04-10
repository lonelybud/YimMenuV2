#include "core/componentStates/LoopState.hpp"
#include "game/backend/Self.hpp"

namespace YimMenu::Features
{
	class VehicleGodmode : public LoopState
	{
		using LoopState::LoopState;

		virtual void OnTick() override
		{
			auto veh = Self::GetVehicle();
			if (veh)
			{
				veh.SetInvincible(true);
			}
		}

		virtual void OnDisable() override
		{
			auto veh = Self::GetVehicle();
			if (veh)
			{
				veh.SetInvincible(false);
			}
		}
	};

	inline VehicleGodmode _VehicleGodmode{"vehiclegodmode", "Vehicle God Mode", "Blocks all incoming damage to your current vehicle"};
}