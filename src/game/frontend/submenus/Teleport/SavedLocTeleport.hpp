#include "core/backend/FiberPool.hpp"
#include "core/frontend/manager/SubmenuMenuCategory.hpp"
#include "game/backend/SavedLocations.hpp"
#include "core/frontend/Notifications.hpp"

namespace YimMenu::Submenus
{
	class SavedLocTeleport : public SubmenuMenuCategory
	{
		using SubmenuMenuCategory::SubmenuMenuCategory;

		std::vector<SavedLocation> telelocations{};
		std::vector<std::string> categories{};

		std::string new_locname{}, search{}, selected_category = "";
		SavedLocation selected_telloc;
		bool delete_modal = false;

		void update_telelocations()
		{
			auto& t = SavedLocations::GetAllSavedLocations();
			if (t.find(selected_category) != t.end())
				telelocations = t[selected_category];
			else
				telelocations.clear();
		}

		void refresh_data()
		{
			SavedLocations::FetchSavedLocations();
			auto& t = SavedLocations::GetAllSavedLocations();
			categories = t | std::views::keys | std::ranges::to<std::vector<std::string>>();
			update_telelocations();
		}

		void Draw()
		{
			if (delete_modal)
				ImGui::OpenPopup("##deletelocation");
			if (ImGui::BeginPopupModal("##deletelocation", nullptr, ImGuiWindowFlags_NoTitleBar | ImGuiWindowFlags_NoMove))
			{
				ImGui::Text("Are you sure you want to delete %s?", selected_telloc.name.c_str());
				ImGui::Spacing();
				if (ImGui::Button("Yes"))
				{
					FiberPool::Push([this] {
						SavedLocations::DeleteSavedLocation(selected_category, selected_telloc.name);
						selected_telloc = {};
						refresh_data();
					});
					delete_modal = false;
					ImGui::CloseCurrentPopup();
				}
				ImGui::SameLine();
				if (ImGui::Button("No"))
				{
					delete_modal = false;
					ImGui::CloseCurrentPopup();
				}
				ImGui::EndPopup();
			}

			ImGui::PushItemWidth(300);
			ImGui::InputTextWithHint("###Category", "Category", &selected_category);
			ImGui::InputTextWithHint("###Location", "Location", &new_locname);
			ImGui::PopItemWidth();
			if (ImGui::Button("Save Current Location"))
				FiberPool::Push([this] {
					if (selected_category.empty() || new_locname.empty())
						Notifications::Show("Saved Teleport", "selected_category or name is empty", NotificationType::Error);
					else
					{
						SavedLocation teleportLocation;
						auto coords = Self::GetPed().GetPosition();
						teleportLocation = {new_locname, coords.x, coords.y, coords.z};
						SavedLocations::SaveNewLocation(selected_category, teleportLocation);
						selected_telloc = teleportLocation;
						refresh_data();
					}
				});
			ImGui::Spacing();
			if (ImGui::Button("Refresh List"))
				FiberPool::Push([this] {
					refresh_data();
				});
			ImGui::SameLine();
			if (ImGui::Button("TP to Selected"))
				FiberPool::Push([this] {
					if (selected_telloc.name.size())
						Self::GetPed().TeleportTo({selected_telloc.x, selected_telloc.y, selected_telloc.z});
					else
						Notifications::Show("Saved Teleport", "empty teleport", NotificationType::Error);
				});
			ImGui::SameLine();
			if (ImGui::Button("Delete Selected"))
				delete_modal = true;

			ImGui::Spacing();
			ImGui::SetNextItemWidth(300);
			ImGui::InputTextWithHint("###search", "Name", &search);
			ImGui::SameLine();
			if (ImGui::Button("Filter locations by name"))
				FiberPool::Push([this] {
					if (search.length() > 0)
					{
						categories.clear();
						telelocations = SavedLocations::SavedLocationsFilteredList(search);
					}
					else
						refresh_data();
				});

			ImGui::BeginGroup();
			{
				ImGui::Text("Categories");
				if (ImGui::BeginListBox("##categories", {400, 300}))
				{
					for (auto& l : categories)
						if (ImGui::Selectable(l.c_str(), l == selected_category))
						{
							selected_category = l;
							update_telelocations();
						}
					ImGui::EndListBox();
				}
			}
			ImGui::EndGroup();
			ImGui::SameLine();
			ImGui::BeginGroup();
			{
				ImGui::Text("Locations");
				if (ImGui::BeginListBox("##telelocations", {400, 300}))
				{
					for (const auto& l : telelocations)
						if (ImGui::Selectable(l.name.c_str(), selected_telloc.name == l.name))
							selected_telloc = l;
					ImGui::EndListBox();
				}
			}
			ImGui::EndGroup();
		}
	};
}