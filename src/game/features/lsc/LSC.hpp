#pragma once
#include "core/backend/FiberPool.hpp"
#include "core/backend/ScriptMgr.hpp"
#include "game/backend/Self.hpp"
#include "game/features/lsc/vehicle_helper.hpp"
#include "game/gta/Vehicle.hpp"
#include "game/gta/data/VehicleValues.hpp"
#include "game/gta/data/lsc_types.hpp"
#include "types/script/types.hpp"

namespace YimMenu::Features
{
	class LSC
	{
	public:
		inline static int current_veh    = 0;
		inline static bool preparing_veh = false;

		inline static std::map<int, int32_t> owned_mods{};
		inline static std::map<int, std::string> slot_display_names{};
		inline static std::map<int, std::map<int, std::string>> mod_display_names{};

		inline static std::map<std::string, std::vector<int>> front_wheel_map{};
		inline static std::map<std::string, std::vector<int>> rear_wheel_map{};
		inline static int front_wheel_stock_mod = -1;
		inline static int rear_wheel_stock_mod  = -1;

		inline static Hash model     = 0;
		inline static bool is_bennys = false;

		inline static int selected_slot = -1;

		static void prepare_vehicle()
		{
			if (current_veh != -1) // dont change selected slot when refreshing the current vehicle state
				selected_slot = -1;

			current_veh   = Self::GetVehicle().GetHandle();
			preparing_veh = true;
			model         = Self::GetVehicle().GetModel();

			FiberPool::Push([] {
				front_wheel_stock_mod = -1;
				rear_wheel_stock_mod  = -1;

				if (!HUD::HAS_THIS_ADDITIONAL_TEXT_LOADED("MOD_MNU", 10))
				{
					HUD::CLEAR_ADDITIONAL_TEXT(10, TRUE);
					HUD::REQUEST_ADDITIONAL_TEXT("MOD_MNU", 10);
					ScriptMgr::Yield();
				}

				owned_mods = Self::GetVehicle().get_owned_mods();
				is_bennys  = Self::GetVehicle().is_bennys();

				VEHICLE::SET_VEHICLE_MOD_KIT(current_veh, 0);

				std::map<int, std::string> tmp_slot_display_names;
				std::map<int, std::map<int, std::string>> tmp_mod_display_names;
				std::map<std::string, std::vector<int>> tmp_front_wheel_map;
				std::map<std::string, std::vector<int>> tmp_rear_wheel_map;

				tmp_slot_display_names[(int)CustomVehicleModType::MOD_PLATE_STYLE] = "Plate Style";
				tmp_slot_display_names[(int)CustomVehicleModType::MOD_WINDOW_TINT] = "Window Tint";
				tmp_slot_display_names[(int)CustomVehicleModType::MOD_WHEEL_TYPE]  = "Wheel Type";

				tmp_mod_display_names[(int)CustomVehicleModType::MOD_PLATE_STYLE].insert(lsc_plate_styles.begin(),
				    lsc_plate_styles.end());
				tmp_mod_display_names[(int)CustomVehicleModType::MOD_WINDOW_TINT].insert(lsc_window_tint_types.begin(),
				    lsc_window_tint_types.end());
				tmp_mod_display_names[(int)CustomVehicleModType::MOD_WHEEL_TYPE].insert(lsc_wheel_styles.begin(),
				    lsc_wheel_styles.end());

				for (int slot = (int)VehicleModType::MOD_SPOILERS; slot <= (int)VehicleModType::MOD_LIGHTBAR; slot++)
				{
					int count = VEHICLE::GET_NUM_VEHICLE_MODS(current_veh, slot);
					if (count > 0)
					{
						int owner_mod = owned_mods[slot];

						std::string slot_name = VehicleHelper::get_mod_slot_name(model, current_veh, slot);
						if (slot_name.empty())
							continue;

						slot_name.append("##" + std::to_string(slot));
						tmp_slot_display_names[slot] = slot_name;

						std::map<int, std::string> mod_names;

						for (int mod = -1; mod < count; mod++)
						{
							if (VehicleHelper::check_mod_blacklist(model, slot, mod))
								continue;

							bool is_repeated = false;

							std::string mod_name = VehicleHelper::get_mod_name(model, current_veh, slot, mod, count);

							if (mod_name.empty() || mod_name == "NULL")
								continue;

							if (slot == (int)VehicleModType::MOD_FRONTWHEEL)
							{
								if (is_bennys && mod_name.rfind("Chrome ", 0) == 0)
								{
									std::string new_mod_name = mod_name.substr(7);

									if (tmp_front_wheel_map[new_mod_name].size() > 0)
										mod_name = new_mod_name;
								}

								tmp_front_wheel_map[mod_name].push_back(mod);

								if (mod == owner_mod)
									front_wheel_stock_mod = tmp_front_wheel_map[mod_name][0];
								if (tmp_front_wheel_map[mod_name].size() > 1)
									is_repeated = true;
							}
							else if (slot == (int)VehicleModType::MOD_REARWHEEL)
							{
								if (is_bennys && mod_name.rfind("Chrome ", 0) == 0)
								{
									std::string new_mod_name = mod_name.substr(7);

									if (tmp_rear_wheel_map[new_mod_name].size() > 0)
										mod_name = new_mod_name;
								}

								tmp_rear_wheel_map[mod_name].push_back(mod);

								if (mod == owner_mod)
									rear_wheel_stock_mod = tmp_rear_wheel_map[mod_name][0];
								if (tmp_rear_wheel_map[mod_name].size() > 1)
									is_repeated = true;
							}

							if (!is_repeated)
								mod_names[mod] = mod_name;
						}

						tmp_mod_display_names[slot] = mod_names;
					}
				}

				if (tmp_mod_display_names.count((int)VehicleModType::MOD_HORNS) > 0)
					tmp_mod_display_names[(int)VehicleModType::MOD_HORNS].insert(lsc_missing_horns.begin(),
					    lsc_missing_horns.end());

				slot_display_names = tmp_slot_display_names;
				mod_display_names  = tmp_mod_display_names;
				front_wheel_map    = tmp_front_wheel_map;
				rear_wheel_map     = tmp_rear_wheel_map;

				preparing_veh = false;
			});
		}
	};
}