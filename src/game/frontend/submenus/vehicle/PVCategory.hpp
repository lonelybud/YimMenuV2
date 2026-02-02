#include "core/backend/FiberPool.hpp"
#include "core/frontend/manager/SubmenuMenuCategory.hpp"
#include "game/backend/PersonalVehicles.hpp"

namespace YimMenu::Submenus
{
	class PVCategory : public SubmenuMenuCategory
	{
		using SubmenuMenuCategory::SubmenuMenuCategory;

		bool delivering_veh = false;

		void Draw()
		{
			if (!*Pointers.IsSessionStarted)
			{
				ImGui::Text("Go online to see this view.");
				return;
			}

			auto& pvs = PersonalVehicles::GetPersonalVehicles();

			if (ImGui::Button("Refresh"))
				FiberPool::Push([] {
					PersonalVehicles::RegisterVehicles();
				});
			ImGui::SameLine();
			ImGui::Text(" %d", pvs.size());

			if (!delivering_veh && ImGui::BeginListBox("###personal_veh_list", {500, 300}))
			{
				for (const auto& it : pvs)
					if (!it.second->IsBlacklistedVehicle() && ImGui::Selectable(it.first.c_str(), false))
						FiberPool::Push([&] {
							delivering_veh = true;
							it.second->Request();
							delivering_veh = false;
						});

				ImGui::EndListBox();
			}
		}
	};
}