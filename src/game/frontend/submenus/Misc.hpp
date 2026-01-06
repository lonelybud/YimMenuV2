#pragma once
#include "core/frontend/manager/Submenu.hpp"
#include "core/backend/FiberPool.hpp"
#include "game/gta/Stats.hpp"
#include "core/util/Strings.hpp"
#include "game/frontend/components/components.hpp"
#include "game/features/recovery/UnlockEverything.hpp"
// #include "game/backend/Tunables.hpp"

namespace YimMenu::Submenus
{
	class MiscStatEditorCategory : public SubmenuMenuCategory
	{
		using SubmenuMenuCategory::SubmenuMenuCategory;
		void Draw()
		{
			static std::string IntStatText{}, FloatStatText{}, BoolStatText{};
			static int IntStatValue{}, PackedIntStatIndex{}, PackedIntStatValue{}, PackedBoolStatIndex{}, PackedBoolRangeIndex1{}, PackedBoolRangeIndex2{};
			static float FloatStatValue{};
			static bool BoolStatValue{}, PackedBoolStatValue{};

			ImGui::SetNextItemWidth(300);
			ImGui::InputText("Int Stat Name",&IntStatText);
			ImGui::SetNextItemWidth(150);
			ImGui::InputInt("Int Stat Value",&IntStatValue);
			if(ImGui::Button("Get##Intstat"))
				FiberPool::Push([] {
					auto str = TrimString(IntStatText);
					IntStatValue = Stats::GetInt(str.c_str());
				});
			ImGui::SameLine();
			if(ImGui::Button("Set##Intstat"))
				FiberPool::Push([] {
					auto str = TrimString(IntStatText);
					Stats::SetInt(str.c_str(), IntStatValue);
				});
		
			components::ver_space();
			ImGui::SetNextItemWidth(300);
			ImGui::InputText("Float Stat Name",&FloatStatText);
			ImGui::SetNextItemWidth(150);
			ImGui::InputFloat("Float Stat Value",&FloatStatValue);
			if(ImGui::Button("Get##Floatstat"))
				FiberPool::Push([] {
					auto str = TrimString(FloatStatText);
					FloatStatValue = Stats::GetFloat(str.c_str());
				});
			ImGui::SameLine();
			if(ImGui::Button("Set##Floatstat"))
				FiberPool::Push([] {
					auto str = TrimString(FloatStatText);
					Stats::SetFloat(str.c_str(), FloatStatValue);
				});

			components::ver_space();
			ImGui::SetNextItemWidth(300);
			ImGui::InputText("Bool Stat Name",&BoolStatText);
			ImGui::Checkbox("Bool Stat Value",&BoolStatValue);
			if(ImGui::Button("Get##Boolstat"))
				FiberPool::Push([] {
					auto str = TrimString(BoolStatText);
					BoolStatValue = Stats::GetBool(str.c_str());
				});
			ImGui::SameLine();
			if(ImGui::Button("Set##Boolstat"))
				FiberPool::Push([] {
					auto str = TrimString(BoolStatText);
					Stats::SetBool(str.c_str(), BoolStatValue);
				});

			components::ver_space();
			ImGui::SetNextItemWidth(150);
			ImGui::InputInt("PackedInt Stat Index",&PackedIntStatIndex);
			ImGui::SetNextItemWidth(150);
			ImGui::InputInt("PackedInt Stat Value",&PackedIntStatValue);
			if(ImGui::Button("Get##PackedIntstat"))
				FiberPool::Push([] {
					PackedIntStatValue = Stats::GetPackedInt(PackedIntStatIndex);
				});
			ImGui::SameLine();
			if(ImGui::Button("Set##PackedIntstat"))
				FiberPool::Push([] {
					Stats::SetPackedInt(PackedIntStatIndex, PackedIntStatValue);
				});

			components::ver_space();
			ImGui::SetNextItemWidth(150);
			ImGui::InputInt("PackedBool Stat Index",&PackedBoolStatIndex);
			ImGui::Checkbox("PackedBool Stat Value",&PackedBoolStatValue);
			if(ImGui::Button("Get##PackedBoolstat"))
				FiberPool::Push([] {
					PackedBoolStatValue = Stats::GetPackedBool(PackedBoolStatIndex);
				});
			ImGui::SameLine();
			if(ImGui::Button("Set##PackedBoolstat"))
				FiberPool::Push([] {
					Stats::SetPackedBool(PackedBoolStatIndex, PackedBoolStatValue);
				});

			components::ver_space();
			ImGui::Text("PackedBoolRange -");
			ImGui::SameLine();
			ImGui::SetNextItemWidth(150);
			ImGui::InputInt("##PackedBoolRange1",&PackedBoolRangeIndex1);
			ImGui::SameLine();
			ImGui::SetNextItemWidth(150);
			ImGui::InputInt("##PackedBoolRange2",&PackedBoolRangeIndex2);
			ImGui::SameLine();
			if(ImGui::Button("Set##PackedBoolRange"))
				FiberPool::Push([] {
					unlock_packed_bools(PackedBoolRangeIndex1, PackedBoolRangeIndex2);
				});
		}
	};

	class MiscSubmenu : public Submenu
	{
	public:
		MiscSubmenu() :
		    Submenu("Misc")
		{
			auto statEditor = std::make_shared<MiscStatEditorCategory>("Stat Editor");
			AddCategory(std::move(statEditor));
		}
	};
}