#pragma once
#include "VehicleEditorCategory.hpp"
#include "SavedVehiclesCategory.hpp"
#include "core/frontend/Notifications.hpp"
#include "core/frontend/manager/Submenu.hpp"
#include "game/features/vehicle/Godmode.hpp"
#include "game/features/vehicle/Seatbelt.hpp"
#include "game/features/vehicle/Simple.hpp"
#include "game/features/vehicle/CallMechanic.hpp"
#include "game/features/vehicle/FixAllVehicles.hpp"
#include "game/frontend/components/components.hpp"
#include "misc/cpp/imgui_stdlib.h"
#include "core/backend/FiberPool.hpp"

namespace YimMenu::Submenus
{
	class VehicleMainCategory : public SubmenuMenuCategory
	{
		using SubmenuMenuCategory::SubmenuMenuCategory;
		void Draw()
		{
			ImGui::BeginGroup();
			{
				components::checkbox(YimMenu::Features::_VehicleGodmode);
				components::checkbox(YimMenu::Features::_Seatbelt);
			}
			ImGui::EndGroup();
			ImGui::SameLine();
			ImGui::BeginGroup();
			{
				if (ImGui::Button("Repair Vehicle"))
					YimMenu::Features::RepairVehicle();
				components::button(YimMenu::Features::_FixAllVehicles);
				if (ImGui::Button("Enter Last Vehicle"))
					YimMenu::Features::EnterLastVehicle();
				components::button(YimMenu::Features::_CallMechanic);
				if (ImGui::Button("Reset Vehicle Delivery Cooldown"))
					YimMenu::Features::ResetVehDeliveryCooldown();
			}
			ImGui::EndGroup();
		}
	};

	class VehicleSpawnCategory : public SubmenuMenuCategory
	{
		using SubmenuMenuCategory::SubmenuMenuCategory;
		void Draw()
		{
			ImGui::BeginGroup();
			{
				ImGui::TextWrapped("Input model of the car. For example Coquette D5 has 'coquette6'. Get 'Model ID' under 'Meta Section' from https://gtacars.net");
				ImGui::TextWrapped("Some vehicle have different models. For example Buccaneer & Buccaneer Custom are different.");
				static std::string veh_model_name;
				ImGui::InputTextWithHint("###veh_model_name", "model", &veh_model_name);
				components::ver_space();
				static bool spawn_in, max_upgrade;
				ImGui::Checkbox("Tp in after spawn", &spawn_in);
				ImGui::Checkbox("Spawn upgraded", &max_upgrade);
				components::ver_space();
				if (ImGui::Button("Spawn Vehicle"))
					YimMenu::Features::SpawnVehicle(veh_model_name, spawn_in, max_upgrade);
			}
			ImGui::EndGroup();
		}
	};

	class VehicleFunCategory : public SubmenuMenuCategory
	{
		using SubmenuMenuCategory::SubmenuMenuCategory;
		void Draw()
		{
			if (!Self::GetVehicle())
			{
				ImGui::Text("Please enter a vehicle.");
				return;
			}

			ImGui::Text("Lowrider Controls -");
			static float maxWheelRaiseFactor = 2;
			ImGui::SetNextItemWidth(150);
			ImGui::SliderFloat("Wheel Raise Factor", &maxWheelRaiseFactor, 1, 3);

			for (int i = 0; i < 4; ++i)
			{
				auto label = "Raise W" + std::to_string(i + 1);
				if (ImGui::Button(label.c_str()))
					FiberPool::Push([=] {
						Self::GetVehicle().RaiseHydraulicWheel(i, maxWheelRaiseFactor);
					});
				ImGui::SameLine();
			}
			ImGui::NewLine();
			for (int i = 0; i < 4; ++i)
			{
				auto label = "Lower W" + std::to_string(i + 1);
				if (ImGui::Button(label.c_str()))
					FiberPool::Push([=] {
						Self::GetVehicle().LowerHydraulicWheel(i, maxWheelRaiseFactor);
					});
				ImGui::SameLine();
			}
		}
	};

	class VehicleSubmenu : public Submenu
	{
	public:
		VehicleSubmenu() :
		    Submenu("Vehicle")
		{
			auto main = std::make_shared<VehicleMainCategory>("main");
			auto fun = std::make_shared<VehicleFunCategory>("Fun");
			auto spawn = std::make_shared<VehicleSpawnCategory>("spawn");
			auto vehicleEditor = std::make_shared<VehicleEditorCategory>();
			auto persistCar = std::make_shared<SavedVehiclesCategory>("Saved Vehicles");
			AddCategory(std::move(main));
			AddCategory(std::move(fun));
			AddCategory(std::move(spawn));
			AddCategory(std::move(vehicleEditor));
			AddCategory(std::move(persistCar));
		};
	};
}