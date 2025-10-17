#include "core/backend/FiberPool.hpp"
#include "core/frontend/manager/SubmenuMenuCategory.hpp"
#include "game/backend/Self.hpp"
// #include "core/frontend/Notifications.hpp"
// #include "core/util/Strings.hpp"
// #include "misc/cpp/imgui_stdlib.h"

namespace YimMenu::Submenus
{
	class VehicleFunCategory : public SubmenuMenuCategory
	{
		using SubmenuMenuCategory::SubmenuMenuCategory;

		int current_veh = 0;
		bool preparing_veh = false;
		int passengers = 0;

		inline void prepare_vehicle()
		{
			preparing_veh = true;
			FiberPool::Push([this] {
				current_veh = Self::GetVehicle().GetHandle();
				passengers = Self::GetVehicle().GetMaxNumOfPassengers();
				preparing_veh = false;
			});
		}

		inline void low_rider_controls()
		{
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

		inline void seats()
		{
			ImGui::Text("Seats -");
			for (int i = -1; i < passengers; i++)
			{
				std::string label = i >= 0 ? ("S_" + std::to_string(i + 1)) : "S_0";
				if (ImGui::Button(label.c_str()))
					FiberPool::Push([=] {
						if (Self::GetVehicle().IsSeatFree(i))
							Self::GetPed().SetInVehicle(Self::GetVehicle(), i);
					});
				ImGui::SameLine();
			}
			ImGui::NewLine();
		}

		inline void doors()
		{
			ImGui::Text("Doors -");

			if (ImGui::Button("Open all doors"))
				FiberPool::Push([=] {
					Self::GetVehicle().ToggleAllDoors(true);
				});
			ImGui::SameLine();
			if (ImGui::Button("Close all doors"))
				FiberPool::Push([=] {
					Self::GetVehicle().ToggleAllDoors(false);
				});
			ImGui::NewLine();
		}

		void Draw()
		{
			if (!Self::GetVehicle())
			{
				ImGui::Text("Please enter a vehicle.");
				current_veh = 0;
				return;
			}

			if (preparing_veh)
				return;

			if (current_veh != Self::GetVehicle().GetHandle())
			{
				prepare_vehicle();
				return;
			}

			seats();
			doors();
			low_rider_controls();
		}
	};
}
