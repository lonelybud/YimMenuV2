#pragma once
#include "SubmenuMenuCategory.hpp"

namespace YimMenu
{
	class Submenu
	{
	public:
		constexpr Submenu(std::string name, std::string icon = "") :
		    m_Name(name),
		    m_Icon(icon)
		{
		}

		std::shared_ptr<SubmenuMenuCategory> GetActiveCategory() const
		{
			return m_ActiveCategory;
		}

		void AddCategory(std::shared_ptr<SubmenuMenuCategory>&& category);
		void DrawCategorySelectors();
		void SetActiveCategory(const std::shared_ptr<SubmenuMenuCategory> category);
		void Draw();

	private:
		std::shared_ptr<SubmenuMenuCategory> m_ActiveCategory;

	public:
		std::vector<std::shared_ptr<SubmenuMenuCategory>> m_Categories;
		std::string m_Name;
		std::string m_Icon; // currently unused
	};
}