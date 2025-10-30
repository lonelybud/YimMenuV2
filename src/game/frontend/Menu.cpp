#include "Menu.hpp"
#include "imgui.h"
#include "imgui_internal.h"
#include "core/backend/FiberPool.hpp"
#include "core/backend/ScriptMgr.hpp"
#include "core/frontend/manager/UIManager.hpp"
#include "core/renderer/Renderer.hpp"
#include "game/frontend/fonts/Fonts.hpp"
#include "game/pointers/Pointers.hpp"
#include "submenus/Recovery.hpp"
#include "submenus/Self/Self.hpp"
#include "submenus/Teleport/Teleport.hpp"
#include "submenus/vehicle/Vehicle.hpp"
#include "submenus/World.hpp"

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

		Renderer::AddRendererCallBack(
		    [&] {
			    if (!GUI::IsOpen())
				    return;

			    ImGui::PushFont(Menu::Font::g_DefaultFont);
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

	void Menu::SetupStyle()
	{
		ImGuiStyle& style = ImGui::GetStyle();

		style.Colors[ImGuiCol_Text]         = ImVec4(0.90f, 0.90f, 0.90f, 1.00f);
		style.Colors[ImGuiCol_TextDisabled] = ImVec4(0.50f, 0.50f, 0.50f, 1.00f);

		style.Colors[ImGuiCol_WindowBg] = ImVec4(0.10f, 0.10f, 0.12f, 1.00f);
		style.Colors[ImGuiCol_ChildBg]  = ImVec4(0.12f, 0.12f, 0.14f, 1.00f);
		style.Colors[ImGuiCol_PopupBg]  = ImVec4(0.08f, 0.08f, 0.10f, 0.95f);

		style.Colors[ImGuiCol_Border]         = ImVec4(0.28f, 0.28f, 0.28f, 0.25f);
		style.Colors[ImGuiCol_FrameBg]        = ImVec4(0.18f, 0.18f, 0.20f, 1.00f);
		style.Colors[ImGuiCol_FrameBgHovered] = ImVec4(0.35f, 0.40f, 0.50f, 0.75f);
		style.Colors[ImGuiCol_FrameBgActive]  = ImVec4(0.45f, 0.50f, 0.60f, 0.85f);

		style.Colors[ImGuiCol_Button]        = ImVec4(0.40f, 0.25f, 0.50f, 1.00f);
		style.Colors[ImGuiCol_ButtonHovered] = ImVec4(0.50f, 0.35f, 0.60f, 1.00f);
		style.Colors[ImGuiCol_ButtonActive]  = ImVec4(0.60f, 0.45f, 0.75f, 1.00f);

		style.Colors[ImGuiCol_TitleBg]          = ImVec4(0.08f, 0.08f, 0.10f, 1.00f);
		style.Colors[ImGuiCol_TitleBgActive]    = ImVec4(0.10f, 0.12f, 0.14f, 1.00f);
		style.Colors[ImGuiCol_TitleBgCollapsed] = ImVec4(0.05f, 0.05f, 0.06f, 1.00f);

		style.Colors[ImGuiCol_Tab]        = ImVec4(0.25f, 0.20f, 0.45f, 0.85f);
		style.Colors[ImGuiCol_TabHovered] = ImVec4(0.35f, 0.30f, 0.65f, 0.85f);
		style.Colors[ImGuiCol_TabActive]  = ImVec4(0.40f, 0.35f, 0.75f, 1.00f);

		style.Colors[ImGuiCol_Header]        = ImVec4(0.20f, 0.25f, 0.35f, 1.00f);
		style.Colors[ImGuiCol_HeaderHovered] = ImVec4(0.35f, 0.40f, 0.50f, 1.00f);
		style.Colors[ImGuiCol_HeaderActive]  = ImVec4(0.45f, 0.50f, 0.60f, 1.00f);

		style.Colors[ImGuiCol_PlotLines]            = ImVec4(0.80f, 0.80f, 0.00f, 0.00f);
		style.Colors[ImGuiCol_PlotLinesHovered]     = ImVec4(1.00f, 0.85f, 0.00f, 1.00f);
		style.Colors[ImGuiCol_PlotHistogram]        = ImVec4(0.90f, 0.70f, 0.20f, 1.00f);
		style.Colors[ImGuiCol_PlotHistogramHovered] = ImVec4(1.00f, 0.80f, 0.40f, 1.00f);

		style.GrabRounding = style.FrameRounding = style.ChildRounding = style.WindowRounding = 8.0f;
	}

	static const ImWchar* GetGlyphRangesCyrillicOnly()
	{
		static const ImWchar ranges[] =
		    {
		        0x0400,
		        0x052F, // Cyrillic + Cyrillic Supplement
		        0x2DE0,
		        0x2DFF, // Cyrillic Extended-A
		        0xA640,
		        0xA69F, // Cyrillic Extended-B
		        0,
		    };
		return &ranges[0];
	}

	static ImFont* CreateFontWithCyrillicSupport(ImGuiIO& io, float size)
	{
		ImFontConfig FontCfg{};
		FontCfg.FontDataOwnedByAtlas = false;

		auto font = io.Fonts->AddFontFromMemoryTTF(const_cast<std::uint8_t*>(Fonts::MainFont), sizeof(Fonts::MainFont), size, &FontCfg, io.Fonts->GetGlyphRangesDefault());

		// just use Arial for Cyrillic

		FontCfg.MergeMode = true;
		io.Fonts->AddFontFromFileTTF((std::filesystem::path(std::getenv("SYSTEMROOT")) / "Fonts" / "arial.ttf").string().c_str(), size, &FontCfg, GetGlyphRangesCyrillicOnly());

		io.Fonts->Build();

		return font;
	}

	void Menu::SetupFonts()
	{
		auto& IO = ImGui::GetIO();
		IO.IniFilename = NULL;
		IO.LogFilename = NULL;
		ImFontConfig FontCfg{};
		FontCfg.FontDataOwnedByAtlas = false;

		IO.Fonts->Clear();
		Menu::Font::g_DefaultFont = CreateFontWithCyrillicSupport(IO, Menu::Font::g_DefaultFontSize);
		Menu::Font::g_OptionsFont = CreateFontWithCyrillicSupport(IO, Menu::Font::g_OptionsFontSize);
		Menu::Font::g_ChildTitleFont = CreateFontWithCyrillicSupport(IO, Menu::Font::g_ChildTitleFontSize);

		UIManager::SetOptionsFont(Menu::Font::g_OptionsFont);
		Renderer::SetFontsUpdated();
	}
}
