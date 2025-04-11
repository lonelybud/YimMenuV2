#include "Vehicle.hpp"

#include "core/backend/ScriptMgr.hpp"
#include "game/gta/Natives.hpp"
#include "game/gta/data/VehicleValues.hpp"
#include "game/pointers/Pointers.hpp"

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

	void Vehicle::SetPlateText(const char* plate)
	{
		ENTITY_ASSERT_VALID();
		ENTITY_ASSERT_CONTROL();

		if (plate != nullptr && plate[0] != 0)
			VEHICLE::SET_VEHICLE_NUMBER_PLATE_TEXT(GetHandle(), plate);
	}

	bool Vehicle::IsSeatFree(int seat)
	{
		ENTITY_ASSERT_VALID();

		return VEHICLE::IS_VEHICLE_SEAT_FREE(GetHandle(), seat, true);
	}

	bool Vehicle::is_bennys()
	{
		auto v = (WheelTypes)VEHICLE::GET_VEHICLE_WHEEL_TYPE(GetHandle());
		return v == WheelTypes::WHEEL_TYPE_BENNYS_ORIGINAL || v == WheelTypes::WHEEL_TYPE_BENNYS_BESPOKE || v == WheelTypes::WHEEL_TYPE_OPEN_WHEEL || v == WheelTypes::WHEEL_TYPE_STREET || v == WheelTypes::WHEEL_TYPE_TRACK;
	}

	std::map<int, int32_t> Vehicle::get_owned_mods()
	{
		auto vehicle = GetHandle();
		std::map<int, int32_t> owned_mods;

		for (int i = (int)CustomVehicleModType::MOD_SECONDARY_CUSTOM; i <= (int)CustomVehicleModType::MOD_MODEL_HASH; i++)
		{
			owned_mods[i] = 0;
		}

		owned_mods[(int)CustomVehicleModType::MOD_MODEL_HASH] = ENTITY::GET_ENTITY_MODEL(vehicle);

		owned_mods[(int)CustomVehicleModType::MOD_PLATE_STYLE] = VEHICLE::GET_VEHICLE_NUMBER_PLATE_TEXT_INDEX(vehicle);
		owned_mods[(int)CustomVehicleModType::MOD_WINDOW_TINT] = VEHICLE::GET_VEHICLE_WINDOW_TINT(vehicle);
		owned_mods[(int)CustomVehicleModType::MOD_WHEEL_TYPE]  = VEHICLE::GET_VEHICLE_WHEEL_TYPE(vehicle);

		VEHICLE::GET_VEHICLE_COLOURS(vehicle, &owned_mods[(int)CustomVehicleModType::MOD_PRIMARY_COL], &owned_mods[(int)CustomVehicleModType::MOD_SECONDARY_COL]);
		VEHICLE::GET_VEHICLE_EXTRA_COLOURS(vehicle, &owned_mods[(int)CustomVehicleModType::MOD_PEARLESCENT_COL], &owned_mods[(int)CustomVehicleModType::MOD_WHEEL_COL]);
		VEHICLE::GET_VEHICLE_EXTRA_COLOUR_5(vehicle, &owned_mods[(int)CustomVehicleModType::MOD_INTERIOR_COL]);
		VEHICLE::GET_VEHICLE_EXTRA_COLOUR_6(vehicle, &owned_mods[(int)CustomVehicleModType::MOD_DASHBOARD_COL]);

		owned_mods[(int)CustomVehicleModType::MOD_PRIMARY_CUSTOM] = VEHICLE::GET_IS_VEHICLE_PRIMARY_COLOUR_CUSTOM(vehicle);
		if (owned_mods[(int)CustomVehicleModType::MOD_PRIMARY_CUSTOM])
		{
			VEHICLE::GET_VEHICLE_CUSTOM_PRIMARY_COLOUR(vehicle, &owned_mods[(int)CustomVehicleModType::MOD_PRIMARY_COL_R], &owned_mods[(int)CustomVehicleModType::MOD_PRIMARY_COL_G], &owned_mods[(int)CustomVehicleModType::MOD_PRIMARY_COL_B]);
		}

		owned_mods[(int)CustomVehicleModType::MOD_SECONDARY_CUSTOM] = VEHICLE::GET_IS_VEHICLE_SECONDARY_COLOUR_CUSTOM(vehicle);
		if (owned_mods[(int)CustomVehicleModType::MOD_SECONDARY_CUSTOM])
		{
			VEHICLE::GET_VEHICLE_CUSTOM_SECONDARY_COLOUR(vehicle, &owned_mods[(int)CustomVehicleModType::MOD_SECONDARY_COL_R], &owned_mods[(int)CustomVehicleModType::MOD_SECONDARY_COL_G], &owned_mods[(int)CustomVehicleModType::MOD_SECONDARY_COL_B]);
		}

		owned_mods[(int)VehicleModType::MOD_TYRE_SMOKE] = VEHICLE::IS_TOGGLE_MOD_ON(vehicle, (int)VehicleModType::MOD_TYRE_SMOKE);
		if (owned_mods[(int)VehicleModType::MOD_TYRE_SMOKE])
		{
			VEHICLE::GET_VEHICLE_TYRE_SMOKE_COLOR(vehicle, &owned_mods[(int)CustomVehicleModType::MOD_TIRESMOKE_COL_R], &owned_mods[(int)CustomVehicleModType::MOD_TIRESMOKE_COL_G], &owned_mods[(int)CustomVehicleModType::MOD_TIRESMOKE_COL_B]);
		}

		owned_mods[(int)VehicleModType::MOD_XENON_LIGHTS] = VEHICLE::IS_TOGGLE_MOD_ON(vehicle, (int)VehicleModType::MOD_XENON_LIGHTS);
		if (owned_mods[(int)VehicleModType::MOD_XENON_LIGHTS])
		{
			owned_mods[(int)CustomVehicleModType::MOD_XENON_COL] = (int8_t)VEHICLE::GET_VEHICLE_XENON_LIGHT_COLOR_INDEX(vehicle);
		}

		owned_mods[(int)CustomVehicleModType::MOD_NEON_LEFT_ON]  = VEHICLE::GET_VEHICLE_NEON_ENABLED(vehicle, (int)NeonLightLocations::NEON_LEFT);
		owned_mods[(int)CustomVehicleModType::MOD_NEON_RIGHT_ON] = VEHICLE::GET_VEHICLE_NEON_ENABLED(vehicle, (int)NeonLightLocations::NEON_RIGHT);
		owned_mods[(int)CustomVehicleModType::MOD_NEON_FRONT_ON] = VEHICLE::GET_VEHICLE_NEON_ENABLED(vehicle, (int)NeonLightLocations::NEON_FRONT);
		owned_mods[(int)CustomVehicleModType::MOD_NEON_BACK_ON]  = VEHICLE::GET_VEHICLE_NEON_ENABLED(vehicle, (int)NeonLightLocations::NEON_BACK);
		VEHICLE::GET_VEHICLE_NEON_COLOUR(vehicle, &owned_mods[(int)CustomVehicleModType::MOD_NEON_COL_R], &owned_mods[(int)CustomVehicleModType::MOD_NEON_COL_G], &owned_mods[(int)CustomVehicleModType::MOD_NEON_COL_B]);

		owned_mods[(int)CustomVehicleModType::MOD_TIRE_CAN_BURST] = VEHICLE::GET_VEHICLE_TYRES_CAN_BURST(vehicle);
		owned_mods[(int)CustomVehicleModType::MOD_DRIFT_TIRE]     = VEHICLE::GET_DRIFT_TYRES_SET(vehicle);
		owned_mods[(int)VehicleModType::MOD_TURBO]          = VEHICLE::IS_TOGGLE_MOD_ON(vehicle, (int)VehicleModType::MOD_TURBO);

		owned_mods[(int)CustomVehicleModType::MOD_FRONTWHEEL_VAR] = VEHICLE::GET_VEHICLE_MOD_VARIATION(vehicle, (int)VehicleModType::MOD_FRONTWHEEL);
		owned_mods[(int)CustomVehicleModType::MOD_REARWHEEL_VAR]  = VEHICLE::GET_VEHICLE_MOD_VARIATION(vehicle, (int)VehicleModType::MOD_REARWHEEL);

		for (int slot = (int)VehicleModType::MOD_SPOILERS; slot <= (int)VehicleModType::MOD_LIGHTBAR; slot++)
			if (VEHICLE::GET_NUM_VEHICLE_MODS(vehicle, slot) > 0)
				owned_mods[slot] = VEHICLE::GET_VEHICLE_MOD(vehicle, slot);

		for (int extra = (int)CustomVehicleModType::MOD_EXTRA_14; extra <= (int)CustomVehicleModType::MOD_EXTRA_1; ++extra)
			if (auto id = (extra -(int)CustomVehicleModType:: MOD_EXTRA_1) * -1; VEHICLE::DOES_EXTRA_EXIST(vehicle, id))
				owned_mods[extra] = VEHICLE::IS_VEHICLE_EXTRA_TURNED_ON(vehicle, id);

		return owned_mods;
	}


}