#include "core/backend/FiberPool.hpp"
#include "core/frontend/manager/SubmenuMenuCategory.hpp"
#include "game/backend/PersonalVehicles.hpp"

namespace YimMenu::Submenus
{
	class PVCategory : public SubmenuMenuCategory
	{
		using SubmenuMenuCategory::SubmenuMenuCategory;

		bool delivering_veh;

		void Draw()
		{
			if (ImGui::Button("Refresh"))
				FiberPool::Push([] {
					PersonalVehicles::RegisterVehicles();
				});

			if (!delivering_veh && ImGui::BeginListBox("###personal_veh_list", {500, 300}))
			{
				for (const auto& it : PersonalVehicles::GetPersonalVehicles())
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