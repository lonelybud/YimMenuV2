#pragma once
#include "core/frontend/manager/Submenu.hpp"
#include "game/features/world/Pedsignore.hpp"
#include "game/features/world/Kill.hpp"
#include "game/frontend/components/components.hpp"
#include "game/features/network/ForceThunder.hpp"
#include "game/features/world/TimeControl.hpp"
#include "game/features/world/Weather.hpp"

namespace YimMenu::Submenus
{
	class WorldCategory : public SubmenuMenuCategory
	{
		using SubmenuMenuCategory::SubmenuMenuCategory;
		void Draw()
		{
			ImGui::Text("Local Time -");
			ImGui::SliderInt("Hour", &YimMenu::Features::worldHour, 0, 23);
			ImGui::SliderInt("Minute", &YimMenu::Features::worldMinute, 0, 59);
			ImGui::SliderInt("Second", &YimMenu::Features::worldSecond, 0, 59);
			components::button(YimMenu::Features::_SetNetworkTime);
			ImGui::SameLine();
			components::button(YimMenu::Features::_ClearNetworkTime);

			components::ver_space();

			ImGui::Text("Local Weather -");
			ImGui::SetNextItemWidth(200.f);
			if (ImGui::BeginCombo("Select##weather", Features::_SetWeather.weatherType))
			{
				for (auto weatherType : Features::g_WeatherCodes)
					if (ImGui::Selectable(weatherType, weatherType == Features::_SetWeather.weatherType))
						Features::_SetWeather.weatherType = weatherType;
				ImGui::EndCombo();
			}
			ImGui::SameLine();
			components::button(YimMenu::Features::_SetWeather);

			components::ver_space();

			components::checkbox(YimMenu::Features::_ForceThunder);
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