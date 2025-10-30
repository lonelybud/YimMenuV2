#pragma once
#include "core/frontend/manager/Submenu.hpp"
#include "game/features/teleport/TpToObjective.hpp"
#include "game/features/teleport/TpToWaypoint.hpp"
#include "SavedLocTeleport.hpp"
#include "game/frontend/components/components.hpp"

namespace YimMenu::Submenus
{

	class SimpleTelCategory : public SubmenuMenuCategory
	{
		using SubmenuMenuCategory::SubmenuMenuCategory;
		void Draw()
		{
			components::button(YimMenu::Features::_TpToWaypoint);
			ImGui::SameLine();
			components::button(YimMenu::Features::_TpToObjective);
			ImGui::Spacing();

			ImGui::SeparatorText("Teleport in Direction");
			ImGui::Spacing();
			static float increment = 1;
			ImGui::SetNextItemWidth(100);
			ImGui::InputFloat("Teleport forward distance", &increment);
			ImGui::SameLine();
			if (ImGui::Button("Tel. Hor."))
				FiberPool::Push([] {
					auto location = ENTITY::GET_OFFSET_FROM_ENTITY_IN_WORLD_COORDS(Self::GetPed().GetHandle(), 0, increment, 0);
					Self::GetPed().TeleportTo(location);
				});
			ImGui::SameLine();
			if (ImGui::Button("Tel. Ver."))
				FiberPool::Push([] {
					auto location = ENTITY::GET_OFFSET_FROM_ENTITY_IN_WORLD_COORDS(Self::GetPed().GetHandle(), 0, 0, increment);
					Self::GetPed().TeleportTo(location);
				});

			ImGui::SeparatorText("Teleport to Copied Location");
			ImGui::Spacing();
			static rage::fvector3 temp_location{};
			if (ImGui::Button("Set Loc"))
				FiberPool::Push([] {
					temp_location = Self::GetPed().GetPosition();
				});
			ImGui::SameLine();
			if (ImGui::Button("Tel to Loc"))
				FiberPool::Push([] {
					Self::GetPed().TeleportTo(temp_location);
				});
		}
	};

	class TeleportSubmenu : public Submenu
	{
	public:
		TeleportSubmenu() :
		    Submenu("Teleport")
		{
			auto main = std::make_shared<SimpleTelCategory>("Main");
			auto saved = std::make_shared<SavedLocTeleport>("Saved");
			AddCategory(std::move(main));
			AddCategory(std::move(saved));
		};
	};
}