#pragma once
#include "core/frontend/manager/Submenu.hpp"
#include "game/features/recovery/GiveVehicleReward.hpp"


namespace YimMenu::Submenus
{
	class ShoppingCategory : public SubmenuMenuCategory
	{
		using SubmenuMenuCategory::SubmenuMenuCategory;
		void Draw()
		{
			if (ImGui::Button("Save This Vehicle as Personal Vehicle"))
			{
				if (GiveVehicleReward::IsSafeToRunScript())
				{
					GiveVehicleReward::SetShouldRunScript(true);
				}
			}
		}
	};

	class RecoverySubmenu : public Submenu
	{
	public:
		RecoverySubmenu() :
		    Submenu("Recovery")
		{
			auto shopping = std::make_shared<ShoppingCategory>("Shopping");
			AddCategory(std::move(shopping));
		}
	};
}