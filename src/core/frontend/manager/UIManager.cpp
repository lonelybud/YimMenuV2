#include "UIManager.hpp"
#include "game/frontend/components/components.hpp"

namespace YimMenu
{
	void UIManager::AddSubmenuImpl(const std::shared_ptr<Submenu>&& submenu)
	{
		if (!m_ActiveSubmenu)
			m_ActiveSubmenu = submenu;

		m_Submenus.push_back(std::move(submenu));
	}

	void UIManager::SetActiveSubmenuImpl(const std::shared_ptr<Submenu> Submenu)
	{
		m_ActiveSubmenu = Submenu;
	}

	void UIManager::DrawImpl()
	{
		if (ImGui::BeginListBox("##submenus", ImVec2(120, 400)))
		{
			for (auto& submenu : m_Submenus)
				if (ImGui::Selectable(submenu->m_Name.data(), (submenu == m_ActiveSubmenu)))
					SetActiveSubmenu(submenu);
			ImGui::EndListBox();
		}
		ImGui::SameLine();
		ImGui::BeginGroup();
		{
			if (m_ActiveSubmenu)
				m_ActiveSubmenu->DrawCategorySelectors();

			components::ver_space();

			if (m_OptionsFont)
				ImGui::PushFont(m_OptionsFont);
			if (m_ActiveSubmenu)
				m_ActiveSubmenu->Draw();
			if (m_OptionsFont)
				ImGui::PopFont();
		}
		ImGui::EndGroup();
	}

	std::shared_ptr<Submenu> UIManager::GetActiveSubmenuImpl()
	{
		if (m_ActiveSubmenu)
		{
			return m_ActiveSubmenu;
		}

		return nullptr;
	}

	std::shared_ptr<SubmenuMenuCategory> UIManager::GetActiveCategoryImpl()
	{
		if (m_ActiveSubmenu)
		{
			return m_ActiveSubmenu->GetActiveCategory();
		}

		return nullptr;
	}
}
