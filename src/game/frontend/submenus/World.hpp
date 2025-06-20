#pragma once
#include "core/frontend/manager/Submenu.hpp"
#include "game/features/world/Pedsignore.hpp"
#include "game/features/world/Kill.hpp"
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
			components::button(YimMenu::Features::_KillAll);
			components::button(YimMenu::Features::_KillAllEnemies);
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