#pragma once
#include "core/frontend/manager/Submenu.hpp"
#include "core/backend/FiberPool.hpp"
#include "game/gta/Stats.hpp"
#include "core/util/Strings.hpp"
#include "game/frontend/components/components.hpp"
#include "game/features/recovery/UnlockEverything.hpp"
#include "game/gta/Network.hpp"
#include "game/features/misc.hpp"
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
			ImGui::InputText("Int Stat Name", &IntStatText);
			ImGui::SetNextItemWidth(150);
			ImGui::InputInt("Int Stat Value", &IntStatValue);
			if (ImGui::Button("Get##Intstat"))
				FiberPool::Push([] {
					auto str = TrimString(IntStatText);
					IntStatValue = Stats::GetInt(str.c_str());
				});
			ImGui::SameLine();
			if (ImGui::Button("Set##Intstat"))
				FiberPool::Push([] {
					auto str = TrimString(IntStatText);
					Stats::SetInt(str.c_str(), IntStatValue);
				});

			components::ver_space();
			ImGui::SetNextItemWidth(300);
			ImGui::InputText("Float Stat Name", &FloatStatText);
			ImGui::SetNextItemWidth(150);
			ImGui::InputFloat("Float Stat Value", &FloatStatValue);
			if (ImGui::Button("Get##Floatstat"))
				FiberPool::Push([] {
					auto str = TrimString(FloatStatText);
					FloatStatValue = Stats::GetFloat(str.c_str());
				});
			ImGui::SameLine();
			if (ImGui::Button("Set##Floatstat"))
				FiberPool::Push([] {
					auto str = TrimString(FloatStatText);
					Stats::SetFloat(str.c_str(), FloatStatValue);
				});

			components::ver_space();
			ImGui::SetNextItemWidth(300);
			ImGui::InputText("Bool Stat Name", &BoolStatText);
			ImGui::Checkbox("Bool Stat Value", &BoolStatValue);
			if (ImGui::Button("Get##Boolstat"))
				FiberPool::Push([] {
					auto str = TrimString(BoolStatText);
					BoolStatValue = Stats::GetBool(str.c_str());
				});
			ImGui::SameLine();
			if (ImGui::Button("Set##Boolstat"))
				FiberPool::Push([] {
					auto str = TrimString(BoolStatText);
					Stats::SetBool(str.c_str(), BoolStatValue);
				});

			components::ver_space();
			ImGui::SetNextItemWidth(150);
			ImGui::InputInt("PackedInt Stat Index", &PackedIntStatIndex);
			ImGui::SetNextItemWidth(150);
			ImGui::InputInt("PackedInt Stat Value", &PackedIntStatValue);
			if (ImGui::Button("Get##PackedIntstat"))
				FiberPool::Push([] {
					PackedIntStatValue = Stats::GetPackedInt(PackedIntStatIndex);
				});
			ImGui::SameLine();
			if (ImGui::Button("Set##PackedIntstat"))
				FiberPool::Push([] {
					Stats::SetPackedInt(PackedIntStatIndex, PackedIntStatValue);
				});

			components::ver_space();
			ImGui::SetNextItemWidth(150);
			ImGui::InputInt("PackedBool Stat Index", &PackedBoolStatIndex);
			ImGui::Checkbox("PackedBool Stat Value", &PackedBoolStatValue);
			if (ImGui::Button("Get##PackedBoolstat"))
				FiberPool::Push([] {
					PackedBoolStatValue = Stats::GetPackedBool(PackedBoolStatIndex);
				});
			ImGui::SameLine();
			if (ImGui::Button("Set##PackedBoolstat"))
				FiberPool::Push([] {
					Stats::SetPackedBool(PackedBoolStatIndex, PackedBoolStatValue);
				});

			components::ver_space();
			ImGui::Text("PackedBoolRange -");
			ImGui::SameLine();
			ImGui::SetNextItemWidth(150);
			ImGui::InputInt("##PackedBoolRange1", &PackedBoolRangeIndex1);
			ImGui::SameLine();
			ImGui::SetNextItemWidth(150);
			ImGui::InputInt("##PackedBoolRange2", &PackedBoolRangeIndex2);
			ImGui::SameLine();
			if (ImGui::Button("Set##PackedBoolRange"))
				FiberPool::Push([] {
					unlock_packed_bools(PackedBoolRangeIndex1, PackedBoolRangeIndex2);
				});
		}
	};

	class MiscGlobalEditorCategory : public SubmenuMenuCategory
	{
		using SubmenuMenuCategory::SubmenuMenuCategory;
		void Draw()
		{
			static std::string TunableName{};
			static int GlobalIndex{}, GlobalValue{}, GlobalType{}, TunableValue{}, TunableType{};

			ImGui::Text("Global -");
			ImGui::SetNextItemWidth(150);
			ImGui::InputInt("Index##global", &GlobalIndex);
			ImGui::RadioButton("Int##globaltype", &GlobalType, 0);
			ImGui::SameLine();
			ImGui::RadioButton("Float##globaltype", &GlobalType, 1);
			ImGui::SetNextItemWidth(150);
			ImGui::InputInt("Value##global", &GlobalValue);
			if (ImGui::Button("Get##global"))
				FiberPool::Push([] {
					if (GlobalType == 0)
						GlobalValue = *ScriptGlobal(GlobalIndex).As<int*>();
					else
						GlobalValue = *ScriptGlobal(GlobalIndex).As<float*>();
				});
			ImGui::SameLine();
			if (ImGui::Button("Set##global"))
				FiberPool::Push([] {
					if (GlobalType == 0)
						*ScriptGlobal(GlobalIndex).As<int*>() = GlobalValue;
					else
						*ScriptGlobal(GlobalIndex).As<float*>() = GlobalValue;
				});

			components::ver_space();
			ImGui::SetNextItemWidth(300);
			ImGui::InputText("Tunable Name", &TunableName);
			ImGui::RadioButton("Int##tunabletype", &TunableType, 0);
			ImGui::SameLine();
			ImGui::RadioButton("Float##tunabletype", &TunableType, 1);
			ImGui::SetNextItemWidth(150);
			ImGui::InputInt("Value##tunable", &TunableValue);
			if (ImGui::Button("Get##tunable"))
				FiberPool::Push([] {
					auto t = Tunable(Joaat(TunableName));
					if (TunableType == 0)
						TunableValue = t.Get<int>();
					else
						TunableValue = t.Get<float>();
				});
			ImGui::SameLine();
			if (ImGui::Button("Set##tunable"))
				FiberPool::Push([] {
					auto t = Tunable(Joaat(TunableName));
					if (TunableType == 0)
						t.Set<int>(TunableValue);
					else
						t.Set<float>(TunableValue);
				});
		}
	};

	class MiscScriptEditorCategory : public SubmenuMenuCategory
	{
		using SubmenuMenuCategory::SubmenuMenuCategory;
		void Draw()
		{
			static std::string ScriptName{};
			static int ScriptIndex{}, ScriptIndexValue{}, ScriptIndexType{};

			components::ver_space();
			ImGui::SetNextItemWidth(300);
			ImGui::InputText("Script Name", &ScriptName);
			ImGui::SetNextItemWidth(150);
			ImGui::InputInt("Index##script", &ScriptIndex);
			ImGui::RadioButton("Int##scripttype", &ScriptIndexType, 0);
			ImGui::SameLine();
			ImGui::RadioButton("Float##scripttype", &ScriptIndexType, 1);
			ImGui::SetNextItemWidth(150);
			ImGui::InputInt("Value##script", &ScriptIndexValue);
			if (ImGui::Button("Get##script"))
				FiberPool::Push([] {
					if (ScriptIndexType == 0)
						ScriptIndexValue = *ScriptLocal(Joaat(ScriptName), ScriptIndex).As<int*>();
					else
						ScriptIndexValue = *ScriptLocal(Joaat(ScriptName), ScriptIndex).As<float*>();
				});
			ImGui::SameLine();
			if (ImGui::Button("Set##script"))
				FiberPool::Push([] {
					if (ScriptIndexType == 0)
						*ScriptLocal(Joaat(ScriptName), ScriptIndex).As<int*>() = ScriptIndexValue;
					else
						*ScriptLocal(Joaat(ScriptName), ScriptIndex).As<float*>() = ScriptIndexValue;
				});
		}
	};

	class MiscMainCategory : public SubmenuMenuCategory
	{
		using SubmenuMenuCategory::SubmenuMenuCategory;
		void Draw()
		{
			if (ImGui::Button("Join Invite Only Session"))
				FiberPool::Push([] {
					Network::LaunchJoinType(Network::JoinType::INVITE_ONLY);
				});
			ImGui::Spacing();
			if (ImGui::Button("Leave Session"))
				FiberPool::Push([] {
					Network::LaunchJoinType(Network::JoinType::LEAVE_ONLINE);
				});
			ImGui::Spacing();
			ImGui::Checkbox("Allow Player Communication", &YimMenu::Features::allowMultiPlayerCommun);
		}
	};

	class MiscSubmenu : public Submenu
	{
	public:
		MiscSubmenu() :
		    Submenu("Misc")
		{
			auto main = std::make_shared<MiscMainCategory>("Main");
			auto statEditor = std::make_shared<MiscStatEditorCategory>("Stat Editor");
			auto globalEditor = std::make_shared<MiscGlobalEditorCategory>("Global Editor");
			auto scriptEditor = std::make_shared<MiscScriptEditorCategory>("Script Editor");
			AddCategory(std::move(main));
			AddCategory(std::move(statEditor));
			AddCategory(std::move(globalEditor));
			AddCategory(std::move(scriptEditor));
		}
	};
}