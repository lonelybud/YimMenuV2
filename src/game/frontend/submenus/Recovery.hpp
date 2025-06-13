#pragma once
#include "core/frontend/manager/Submenu.hpp"
#include "game/features/recovery/PlayAllMissionsSolo.hpp"
#include "game/features/recovery/Simple.hpp"
#include "game/features/recovery/UnlockGTAPlus.hpp"
#include "game/features/vehicle/SavePersonalVehicle.hpp"
#include "game/frontend/components/components.hpp"
#include "game/features/recovery/RpMultiplier.hpp"
#include "game/gta/ScriptFunction.hpp"
#include "game/features/recovery/LSCCustomsBypass.hpp"

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
			static std::pair<Features::eAppVinewoodMenuSafe, const char*> business_type = Features::businessNames[0];

			ImGui::SetNextItemWidth(200.f);
			if (ImGui::BeginCombo("Business##earnings", business_type.second))
			{
				for (auto& business : Features::businessNames)
					if (ImGui::Selectable(business.second, business_type.first == business.first))
						business_type = business;
				ImGui::EndCombo();
			}
			ImGui::SameLine();
			if (ImGui::Button("Claim Earnings"))
				Features::ClaimSafeEarnings(business_type.first);
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
		}
	};
}