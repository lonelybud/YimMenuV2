#include "Vehicle.hpp"
#include "Natives.hpp"
#include "core/backend/ScriptMgr.hpp"
#include "game/pointers/Pointers.hpp"
#include "game/gta/data/VehicleValues.hpp"

namespace YimMenu
{
	Vehicle Vehicle::Create(std::uint32_t model, rage::fvector3 coords, float heading)
	{
		ENTITY_ASSERT_SCRIPT_CONTEXT();
		if (!STREAMING::IS_MODEL_IN_CDIMAGE(model))
		{
			LOGF(WARNING, "Invalid model passed to Vehicle::Create: 0x{:X}", model);
			return nullptr;
		}

		for (int i = 0; !STREAMING::HAS_MODEL_LOADED(model); i++)
		{
			STREAMING::REQUEST_MODEL(model);
			ScriptMgr::Yield();

			if (i > 30)
			{
				LOGF(WARNING, "Model 0x{:X} failed to load after 30 ticks, bailing out", model);
				return nullptr;
			}
		}

		Pointers.SpectatePatch->Apply();
		auto veh = Vehicle(VEHICLE::CREATE_VEHICLE(model, coords.x, coords.y, coords.z, heading, true, false, false));
		Pointers.SpectatePatch->Restore();

		if (!veh)
		{
			LOGF(WARNING, "CREATE_VEHICLE failed when creating a vehicle with model {:X}", model);
			return nullptr;
		}

		DECORATOR::DECOR_SET_INT(veh.GetHandle(), "MPBitset", 0);
		NETWORK::SET_NETWORK_ID_EXISTS_ON_ALL_MACHINES(NETWORK::VEH_TO_NET(veh.GetHandle()), true);
		VEHICLE::SET_VEHICLE_ON_GROUND_PROPERLY(veh.GetHandle(), 0);
		STREAMING::SET_MODEL_AS_NO_LONGER_NEEDED(model);

		return veh;
	}

	void Vehicle::Fix()
	{
		ENTITY_ASSERT_VALID();
		ENTITY_ASSERT_CONTROL();
		ENTITY_ASSERT_SCRIPT_CONTEXT();

		if (VEHICLE::GET_DOES_VEHICLE_HAVE_DAMAGE_DECALS(GetHandle()))
		{
			VEHICLE::SET_VEHICLE_FIXED(GetHandle());
			VEHICLE::SET_VEHICLE_DIRT_LEVEL(GetHandle(), 0);
		}
	}

	void Vehicle::Upgrade()
	{
		ENTITY_ASSERT_VALID();
		ENTITY_ASSERT_CONTROL();
		ENTITY_ASSERT_SCRIPT_CONTEXT();

		auto veh = GetHandle();

		VEHICLE::SET_VEHICLE_MOD_KIT(veh, 0);

		for (int t = (int)VehicleModType::MOD_SPOILERS; t < (int)VehicleModType::MOD_LIGHTBAR; t++)
		{
			VEHICLE::SET_VEHICLE_MOD(veh, t, VEHICLE::GET_NUM_VEHICLE_MODS(veh, t) - 1, false);
		}

		VEHICLE::SET_VEHICLE_TYRES_CAN_BURST(veh, false);
	}

	void Vehicle::SetPlateText(std::string_view text)
	{
		ENTITY_ASSERT_VALID();
		ENTITY_ASSERT_CONTROL();

		if (text.length() > 8)
		{
			return;
		}

		VEHICLE::SET_VEHICLE_NUMBER_PLATE_TEXT(GetHandle(), text.data());
	}

	bool Vehicle::IsSeatFree(int seat)
	{
		ENTITY_ASSERT_VALID();

		return VEHICLE::IS_VEHICLE_SEAT_FREE(GetHandle(), seat, true);
	}
}