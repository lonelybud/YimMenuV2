#include "core/backend/FiberPool.hpp"
#include "core/frontend/manager/SubmenuMenuCategory.hpp"
#include "game/backend/PersonalVehicles.hpp"
#include "core/util/Strings.hpp"

namespace YimMenu::Submenus
{
	class PVCategory : public SubmenuMenuCategory
	{
		using SubmenuMenuCategory::SubmenuMenuCategory;

		bool delivering_veh = false;
		std::string search{};

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
			ImGui::Text(" %d", (int)pvs.size());


			ImGui::Spacing();
			ImGui::SetNextItemWidth(300);
			if (ImGui::InputTextWithHint("###search", "Name", &search))
				LowerString(search);
			ImGui::Spacing();

			if (!delivering_veh && ImGui::BeginListBox("###personal_veh_list", {500, 300}))
			{
				for (const auto& it : pvs)
				{
					std::string name_lower = it.first;
					LowerString(name_lower);
					if (name_lower.contains(search) && !it.second->IsBlacklistedVehicle() && ImGui::Selectable(name_lower.c_str(), false))
						FiberPool::Push([&] {
							delivering_veh = true;
							it.second->Request();
							delivering_veh = false;
						});
				}

				ImGui::EndListBox();
			}
		}
	};
}