#pragma once
#include "core/frontend/manager/Submenu.hpp"
#include "game/features/recovery/PlayAllMissionsSolo.hpp"
#include "game/features/recovery/Simple.hpp"
#include "game/features/recovery/UnlockEverything.hpp"
#include "game/features/recovery/UnlockGTAPlus.hpp"
#include "game/features/vehicle/SavePersonalVehicle.hpp"
#include "game/frontend/components/components.hpp"
#include "game/features/recovery/RpMultiplier.hpp"
#include "game/gta/ScriptFunction.hpp"
#include "game/features/recovery/LSCCustomsBypass.hpp"
#include "Recovery/DailyActivitiesCategory.hpp"
#include "game/features/recovery/ClaimSafeEarnings.hpp"

namespace YimMenu::Submenus
{

	class RecoveryGeneralCategory : public SubmenuMenuCategory
	{
		using SubmenuMenuCategory::SubmenuMenuCategory;
		void Draw()
		{
			components::checkbox(YimMenu::Features::_UnlockGTAPlus);

			components::checkbox(YimMenu::Features::_OverrideRPMultiplier);
			if (YimMenu::Features::_OverrideRPMultiplier.m_State)
			{
				ImGui::SameLine();
				ImGui::SetNextItemWidth(200);
				ImGui::SliderFloat("Value###rp_mult_val", &YimMenu::Features::_OverrideRPMultiplier._RpMultiplierInput, 1, 10);
			}
		}
	};

	class RecoveryShoppingCategory : public SubmenuMenuCategory
	{
		using SubmenuMenuCategory::SubmenuMenuCategory;
		void Draw()
		{
			if (ImGui::Button("Save This Vehicle as Personal Vehicle"))
				Features::SavePersonalVehicle::Save();

			components::ver_space();

			components::checkbox(YimMenu::Features::_LSCCustomsBypass);

			components::ver_space();

			ImGui::Text("Gun Van -");
			static int selected_slot = 0, selected_weap_slot = 0;
			ImGui::SetNextItemWidth(200.f);
			if (ImGui::BeginCombo("Slot##allowedGunVanSlots", Features::allowedGunVanSlots[selected_slot]))
			{
				for (int i = 0; i < Features::allowedGunVanSlots.size(); ++i)
					if (ImGui::Selectable(Features::allowedGunVanSlots[i], selected_slot == i))
						selected_slot = i;
				ImGui::EndCombo();
			}
			ImGui::SetNextItemWidth(300.f);
			if (ImGui::BeginCombo("Weapon##allowedGunVanWeapons", Features::allowedGunVanWeapons[selected_weap_slot]))
			{
				for (int i = 0; i < Features::allowedGunVanWeapons.size(); ++i)
					if (ImGui::Selectable(Features::allowedGunVanWeapons[i], selected_weap_slot == i))
						selected_weap_slot = i;
				ImGui::EndCombo();
			}
			if (ImGui::Button("Set Gun Van Weapon"))
				Features::SetGunvanWeapon(Features::allowedGunVanWeapons[selected_weap_slot], selected_slot + 1);
		}
	};

	class UnlockEverythingCategory : public SubmenuMenuCategory
	{
		using SubmenuMenuCategory::SubmenuMenuCategory;
		void Draw()
		{
			if (ImGui::Button("unlock_packed_bools_simple"))
				UnlockEverything::unlock_packed_bools_simple();

			if (ImGui::Button("unlock_paints"))
				UnlockEverything::unlock_paints();

			if (ImGui::Button("set_misc"))
				UnlockEverything::set_misc();

			static int int_index = 0, bool_index = 0, float_index = 0,
			           packed_stat_int_index = 0, packed_stat_bool_index = 0,
			           packed_stat_bool_range_index, int_bit_index, ints_bit_range_index;

			if (ImGui::Button("set_int"))
				UnlockEverything::set_int(int_index);
			ImGui::SameLine();
			ImGui::Text("Done: %d/%llu", int_index, UnlockEverything::_ints.size());

			if (ImGui::Button("set_bool"))
				UnlockEverything::set_bool(bool_index);
			ImGui::SameLine();
			ImGui::Text("Done: %d/%llu", bool_index, UnlockEverything::_bools.size());

			if (ImGui::Button("set_float"))
				UnlockEverything::set_float(float_index);
			ImGui::SameLine();
			ImGui::Text("Done: %d/%llu", float_index, UnlockEverything::_floats.size());

			if (ImGui::Button("set_packed_stat_int"))
				UnlockEverything::set_packed_stat_int(packed_stat_int_index);
			ImGui::SameLine();
			ImGui::Text("Done: %d/%llu", packed_stat_int_index, UnlockEverything::_packed_stat_ints.size());

			if (ImGui::Button("set_packed_stat_bool"))
				UnlockEverything::set_packed_stat_bool(packed_stat_bool_index);
			ImGui::SameLine();
			ImGui::Text("Done: %d/%llu", packed_stat_bool_index, UnlockEverything::_packed_stat_bools.size());

			if (ImGui::Button("set_packed_stat_bool_range"))
				UnlockEverything::set_packed_stat_bool_range(packed_stat_bool_range_index);
			ImGui::SameLine();
			ImGui::Text("Done: %d/%llu", packed_stat_bool_range_index, UnlockEverything::_packed_stat_bools_range.size());

			// if (ImGui::Button("set_int_bit"))
			// 	UnlockEverything::set_int_bit(int_bit_index);
			// ImGui::SameLine();
			// ImGui::Text("Done: %d/%llu", int_bit_index, UnlockEverything::_ints_bits.size());

			// if (ImGui::Button("set_ints_bit_range"))
			// 	UnlockEverything::set_ints_bit_range(ints_bit_range_index);
			// ImGui::SameLine();
			// ImGui::Text("Done: %d/%llu", ints_bit_range_index, UnlockEverything::_ints_bits_range.size());
		}
	};

	class RecoveryHeistCategory : public SubmenuMenuCategory
	{
		using SubmenuMenuCategory::SubmenuMenuCategory;
		void Draw()
		{
			components::checkbox(YimMenu::Features::_PlayAllMissionsSolo);
			static int team;
			ImGui::SetNextItemWidth(150);
			ImGui::InputInt("Team", &team);
			ImGui::SameLine();
			if (ImGui::Button("DoTeamSwap"))
				FiberPool::Push([] {
					static ScriptFunction DoTeamSwap("fm_mission_controller"_J, ScriptPointer("DoTeamSwap", "2D 02 04 00 00 38 00 50"));
					DoTeamSwap.Call<void>(team, true);
				});
		}
	};

	class RecoveryBusinessCategory : public SubmenuMenuCategory
	{
		using SubmenuMenuCategory::SubmenuMenuCategory;
		void Draw()
		{
			ImGui::SetNextItemWidth(200.f);
			if (ImGui::BeginCombo("Business##earnings", Features::_ClaimSafeEarnings.selected_business.second))
			{
				for (auto& business : Features::businessNames)
					if (ImGui::Selectable(business.second, Features::_ClaimSafeEarnings.selected_business.first == business.first))
						Features::_ClaimSafeEarnings.selected_business = business;
				ImGui::EndCombo();
			}
			ImGui::SameLine();
			components::button(YimMenu::Features::_ClaimSafeEarnings);
		}
	};

	class RecoverySubmenu : public Submenu
	{
	public:
		RecoverySubmenu() :
		    Submenu("Recovery")
		{
			auto general = std::make_shared<RecoveryGeneralCategory>("General");
			AddCategory(std::move(general));
			auto shopping = std::make_shared<RecoveryShoppingCategory>("Shopping");
			AddCategory(std::move(shopping));
			auto heist = std::make_shared<RecoveryHeistCategory>("Heist");
			AddCategory(std::move(heist));
			auto business = std::make_shared<RecoveryBusinessCategory>("Business");
			AddCategory(std::move(business));
			auto dailyActivities = std::make_shared<DailyActivitiesCategory>("DailyActivities");
			AddCategory(std::move(dailyActivities));
			auto unlockEverything = std::make_shared<UnlockEverythingCategory>("UnlockEverything");
			AddCategory(std::move(unlockEverything));
		}
	};
}