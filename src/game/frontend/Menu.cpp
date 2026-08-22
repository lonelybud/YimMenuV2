#include "Menu.hpp"
#include "core/frontend/manager/UIManager.hpp"
#include "core/frontend/manager/styles/Themes.hpp"
#include "core/renderer/Renderer.hpp"
#include "submenus/Recovery.hpp"
#include "submenus/Self/Self.hpp"
#include "submenus/Teleport/Teleport.hpp"
#include "submenus/vehicle/Vehicle.hpp"
#include "submenus/World.hpp"
#include "submenus/Misc.hpp"

namespace YimMenu
{
	void Menu::Init()
	{
		// Arguably the only place this file should be edited at for more menus
		UIManager::AddSubmenu(std::make_shared<Submenus::SelfSubmenu>());
		UIManager::AddSubmenu(std::make_shared<Submenus::TeleportSubmenu>());
		UIManager::AddSubmenu(std::make_shared<Submenus::VehicleSubmenu>());
		UIManager::AddSubmenu(std::make_shared<Submenus::RecoverySubmenu>());
		UIManager::AddSubmenu(std::make_shared<Submenus::WorldSubmenu>());
		UIManager::AddSubmenu(std::make_shared<Submenus::MiscSubmenu>());

		Renderer::AddRendererCallback(
		    [&] {
			    if (!GUI::IsOpen())
				    return;

			    ImGui::PushFont(Font::g_DefaultFont);
			    ImGui::PushStyleColor(ImGuiCol_WindowBg, ImU32(ImColor(15, 15, 15)));

			    ImGui::SetNextWindowPos({10.f, 50.f});
			    ImGui::SetNextWindowSize({0.f, 0.f});
			    ImGui::SetNextWindowSizeConstraints({10.f, 50.f}, {(float)*Pointers.ScreenResX - 10.f, (float)*Pointers.ScreenResY - 50.f});
			    if (ImGui::Begin("Main", nullptr, ImGuiWindowFlags_NoDecoration))
			    {
				    UIManager::Draw();
			    }
			    ImGui::End();

			    ImGui::PopStyleColor();
			    ImGui::PopFont();
		    },
		    -1);
	}
}
