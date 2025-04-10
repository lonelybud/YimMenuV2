#pragma once
#include "core/frontend/manager/Submenu.hpp"
#include "game/features/self/Freecam.hpp"
#include "game/features/self/Godmode.hpp"
#include "game/features/self/InfiniteAmmo.hpp"
#include "game/features/self/InfiniteClip.hpp"
#include "game/features/self/NoIdleKick.hpp"
#include "game/features/self/NoRagdoll.hpp"
#include "game/features/self/Simple.hpp"
#include "game/features/self/SuperJump.hpp"
#include "game/features/self/UnlimitedOxygen.hpp"
#include "game/features/self/Wanted.hpp"
#include "game/features/teleport/Simple.hpp"
#include "game/features/vehicle/Godmode.hpp"
#include "game/features/vehicle/Seatbelt.hpp"
#include "game/features/vehicle/Simple.hpp"
#include "game/frontend/components/components.hpp"


namespace YimMenu::Submenus
{
	class SelfMainCategory : public SubmenuMenuCategory
	{
		using SubmenuMenuCategory::SubmenuMenuCategory;
		void Draw()
		{
			ImGui::BeginGroup();
			{
				components::checkbox(YimMenu::Features::_Godmode);
				components::checkbox(YimMenu::Features::_NoRagdoll);
				components::checkbox(YimMenu::Features::_NoIdleKick);
				components::checkbox(YimMenu::Features::_UnlimitedOxygen);
				components::checkbox(YimMenu::Features::_NeverWanted);
				components::checkbox(YimMenu::Features::_SuperJump);
				components::checkbox(YimMenu::Features::_Freecam);
			}
			ImGui::EndGroup();
			ImGui::SameLine();
			ImGui::BeginGroup();
			{
				if (ImGui::Button("skip cutscene"))
					YimMenu::Features::SkipCutscene();
				if (ImGui::Button("suicide"))
					YimMenu::Features::Suicide();
				if (ImGui::Button("heal"))
					YimMenu::Features::Heal();
				if (ImGui::Button("clear damage"))
					YimMenu::Features::ClearSelfDamage();
				if (ImGui::Button("fill inventory"))
					YimMenu::Features::FillInventory();
			}
			ImGui::EndGroup();
		}
	};

	class SelfWeaponCategory : public SubmenuMenuCategory
	{
		using SubmenuMenuCategory::SubmenuMenuCategory;
		void Draw()
		{
			ImGui::BeginGroup();
			{
				components::checkbox(YimMenu::Features::_InfiniteAmmo);
				components::checkbox(YimMenu::Features::_InfiniteClip);
			}
			ImGui::EndGroup();
			ImGui::SameLine();
			ImGui::BeginGroup();
			{
				if (ImGui::Button("Give Parachute"))
					YimMenu::Features::GiveParachute();
				if (ImGui::Button("Give All Weapons"))
					YimMenu::Features::GiveAllWeapons();
				if (ImGui::Button("Refill Ammo"))
					YimMenu::Features::RefillAllWeapons();
			}
			ImGui::EndGroup();
		}
	};

	class SelfVehicleCategory : public SubmenuMenuCategory
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
				if (ImGui::Button("Enter Last Vehicle"))
					YimMenu::Features::EnterLastVehicle();
			}
			ImGui::EndGroup();
		}
	};

	class SelfTeleportCategory : public SubmenuMenuCategory
	{
		using SubmenuMenuCategory::SubmenuMenuCategory;
		void Draw()
		{
			ImGui::BeginGroup();
			{
				if (ImGui::Button("Tp To Waypoint"))
					YimMenu::Features::TpToWaypoint();
			}
			ImGui::EndGroup();
		}
	};


	class Self : public Submenu
	{
	public:
		Self() :
		    Submenu("Self")
		{
			auto main     = std::make_shared<SelfMainCategory>("Main");
			auto weapon   = std::make_shared<SelfWeaponCategory>("Weapon");
			auto vehicle  = std::make_shared<SelfVehicleCategory>("Weapon");
			auto teleport = std::make_shared<SelfTeleportCategory>("Teleport");
			AddCategory(std::move(main));
			AddCategory(std::move(weapon));
			AddCategory(std::move(vehicle));
			AddCategory(std::move(teleport));
		};
	};
}