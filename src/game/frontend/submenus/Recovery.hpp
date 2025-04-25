#pragma once
#include "core/frontend/manager/Submenu.hpp"
#include "game/features/recovery/GiveVehicleReward.hpp"
#include "game/features/recovery/PlayAllMissionsSolo.hpp"
#include "game/frontend/components/components.hpp"
#include "game/gta/ScriptFunction.hpp"

namespace YimMenu::Submenus
{
	class RecoveryShoppingCategory : public SubmenuMenuCategory
	{
		using SubmenuMenuCategory::SubmenuMenuCategory;
		void Draw()
		{
			if (ImGui::Button("Save This Vehicle as Personal Vehicle"))
				if (GiveVehicleReward::IsSafeToRunScript())
					GiveVehicleReward::SetShouldRunScript(true);
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

	class RecoverySubmenu : public Submenu
	{
	public:
		RecoverySubmenu() :
		    Submenu("Recovery")
		{
			auto shopping = std::make_shared<RecoveryShoppingCategory>("Shopping");
			AddCategory(std::move(shopping));
			auto heist = std::make_shared<RecoveryHeistCategory>("Heist");
			AddCategory(std::move(heist));
		}
	};
}