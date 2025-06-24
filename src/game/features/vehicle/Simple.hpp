#include "core/backend/FiberPool.hpp"
#include "core/frontend/Notifications.hpp"
#include "core/util/Strings.hpp"
#include "game/backend/Self.hpp"
#include "game/gta/Natives.hpp"
#include "game/gta/data/VehicleValues.hpp"

namespace YimMenu::Features
{
	inline void EnterLastVehicle()
	{
		FiberPool::Push([] {
			if (auto last_veh = Self::GetPed().GetLastVehicle())
				Self::GetPed().SetInVehicle(last_veh);
		});
	}

	inline void RepairVehicle()
	{
		FiberPool::Push([] {
			if (Self::GetVehicle())
				Self::GetVehicle().Fix();
		});
	}

	inline void SpawnVehicle(std::string _model, bool spawn_in, bool max_upgade)
	{
		auto model = TrimString(_model);

		if (!model.length())
		{
			Notifications::Show("Spawn Vehicle", "No model name provided.", NotificationType::Error);
			return;
		}

		FiberPool::Push([model, spawn_in, max_upgade] {
			Hash modelHash = Joaat(model);
			if (STREAMING::IS_MODEL_IN_CDIMAGE(modelHash))
			{
				auto veh = Vehicle::Create(modelHash, Self::GetPed().GetPosition(), Self::GetPed().GetHeading());

				if (spawn_in)
					Self::GetPed().SetInVehicle(veh);

				if (max_upgade)
					veh.Upgrade();
			}
			else
			{
				Notifications::Show("Spawn Vehicle", "Invalid model name provided.", NotificationType::Error);
			}
		});
	}

}