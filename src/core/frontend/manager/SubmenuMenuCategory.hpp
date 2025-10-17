#pragma once

namespace YimMenu
{
	class SubmenuMenuCategory
	{
	public:
		std::string m_Name;
		SubmenuMenuCategory(std::string_view name) :
		    m_Name(name)
		{
		}

		virtual void Draw() = 0;
	};
}