#pragma once
#include "core/frontend/manager/Submenu.hpp"
#include "game/frontend/components/components.hpp"
#include "game/features/recovery/DailyActivities.hpp"

namespace YimMenu::Submenus
{
	class DailyActivitiesCategory : public SubmenuMenuCategory
	{
		using SubmenuMenuCategory::SubmenuMenuCategory;
		void Draw()
		{
			components::checkbox(YimMenu::Features::_EnableTreasureChestInLS);
			components::checkbox(YimMenu::Features::_EnableBuriedStashInLS);

			components::ver_space();

			components::button(YimMenu::Features::_CollectShipwrecked);
			components::button(YimMenu::Features::_CompleteAllChallenges);
			components::button(YimMenu::Features::_DeliverNextExoticExportsVehicle);
			components::button(YimMenu::Features::_CollectDeadDrop);
			components::button(YimMenu::Features::_EnterStashHouseSafeCode);

			components::ver_space();

			ImGui::SetNextItemWidth(200);
			ImGui::SliderInt("Index###hiddenCacheIndex", &YimMenu::Features::_CollectHiddenCache.hiddenCacheIndex, 0, 9);
			ImGui::SameLine();
			components::button(YimMenu::Features::_CollectHiddenCache);

			components::ver_space();

			ImGui::SetNextItemWidth(200);
			ImGui::SliderInt("Index###treasureChestIndex", &YimMenu::Features::_CollectTreasureChest.treasureChestIndex, 0, 1);
			ImGui::SameLine();
			components::button(YimMenu::Features::_CollectTreasureChest);

			components::ver_space();

			ImGui::SetNextItemWidth(200);
			ImGui::SliderInt("Index###buriedStashIndex", &YimMenu::Features::_CollectBuriedStash.buriedStashIndex, 0, 1);
			ImGui::SameLine();
			components::button(YimMenu::Features::_CollectBuriedStash);

			components::ver_space();

			ImGui::SetNextItemWidth(200);
			ImGui::SliderInt("Index###skydiveIndex", &YimMenu::Features::_CompleteSkydive.skydiveIndex, 0, 9);
			ImGui::SameLine();
			components::button(YimMenu::Features::_CompleteSkydive);

			components::ver_space();

			ImGui::SetNextItemWidth(200);
			ImGui::SliderInt("Index###timeTrialIndex", &YimMenu::Features::_BeatTimeTrial.timeTrialIndex, 0, 2);
			ImGui::SameLine();
			components::button(YimMenu::Features::_BeatTimeTrial);

			components::ver_space();

			ImGui::SetNextItemWidth(200);
			ImGui::SliderInt("Index###lsTagIndex", &YimMenu::Features::_SprayLSTag.lsTagIndex, 0, 4);
			ImGui::SameLine();
			components::button(YimMenu::Features::_SprayLSTag);

			components::ver_space();

			ImGui::SetNextItemWidth(200);
			ImGui::SliderInt("Index###animalIndex", &YimMenu::Features::_PhotographAnimal.animalIndex, 0, 2);
			ImGui::SameLine();
			components::button(YimMenu::Features::_PhotographAnimal);

			components::ver_space();

			ImGui::SetNextItemWidth(200);
			ImGui::SliderInt("Index###productIndex", &YimMenu::Features::_CollectProduct.productIndex, 0, 9);
			ImGui::SameLine();
			components::button(YimMenu::Features::_CollectProduct);
		}
	};
}