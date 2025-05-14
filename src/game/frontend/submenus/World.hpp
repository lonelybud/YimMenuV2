#pragma once
#include "core/frontend/manager/Submenu.hpp"
#include "game/features/world/Pedsignore.hpp"
#include "game/features/world/Simple.hpp"
#include "game/frontend/components/components.hpp"

namespace YimMenu::Submenus
{
	class WorldCategory : public SubmenuMenuCategory
	{
		using SubmenuMenuCategory::SubmenuMenuCategory;
		void Draw()
		{
			components::checkbox(YimMenu::Features::_PedIgnore);
			components::ver_space();
			if (ImGui::Button("Kill all"))
				YimMenu::Features::KillAllPeds();
			if (ImGui::Button("Kill enemies"))
				YimMenu::Features::KillAllEnemies();
			components::ver_space();
			if (ImGui::Button("Bring all peds"))
				YimMenu::Features::BringAllPeds();
			if (ImGui::Button("Bring objects"))
				YimMenu::Features::BringAllObjs();
			if (ImGui::Button("Bring vehicles"))
				YimMenu::Features::BringAllVehs();
		}
	};

	class WorldSubmenu : public Submenu
	{
	public:
		WorldSubmenu() :
		    Submenu("World")
		{
			auto world = std::make_shared<WorldCategory>("Main");
			AddCategory(std::move(world));
		}
	};
}