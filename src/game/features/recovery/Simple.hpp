#include "core/backend/FiberPool.hpp"
#include "game/backend/Self.hpp"
#include "game/gta/ScriptGlobal.hpp"
#include "game/pointers/Pointers.hpp"
#include "types/script/globals/GPBD_FM.hpp"
#include "game/backend/Tunables.hpp"
#include "types/script/globals/GPBD_FM_2.hpp"

namespace YimMenu::Features
{
	enum class eAppVinewoodMenuSafe
	{
		NIGHTCLUB,
		ARCADE,
		AGENCY,
		SALVAGE_YARD,
		BAIL_OFFICE,
		GARMENT_FACTORY,
		HANDS_ON_CAR_WASH
	};

	inline std::vector<std::pair<eAppVinewoodMenuSafe, const char*>> businessNames = {
	    {eAppVinewoodMenuSafe::NIGHTCLUB, "Nightclub"},
	    {eAppVinewoodMenuSafe::ARCADE, "Arcade"},
	    {eAppVinewoodMenuSafe::AGENCY, "Agency"},
	    {eAppVinewoodMenuSafe::SALVAGE_YARD, "Salvage Yard"},
	    {eAppVinewoodMenuSafe::BAIL_OFFICE, "Bail Office"},
	    {eAppVinewoodMenuSafe::GARMENT_FACTORY, "Garment Factory"},
	    {eAppVinewoodMenuSafe::HANDS_ON_CAR_WASH, "Hands on Car Wash"}};

	inline constexpr auto allowedGunVanWeapons = std::to_array({"WEAPON_KNIFE",
	    "WEAPON_NIGHTSTICK",
	    "WEAPON_HAMMER",
	    "WEAPON_BOTTLE",
	    "WEAPON_DAGGER",
	    "WEAPON_KNUCKLE",
	    "WEAPON_MACHETE",
	    "WEAPON_FLASHLIGHT",
	    "WEAPON_SWITCHBLADE",
	    "WEAPON_BATTLEAXE",
	    "WEAPON_POOLCUE",
	    "WEAPON_WRENCH",
	    "WEAPON_HATCHET",
	    "WEAPON_BAT",
	    "WEAPON_CROWBAR",
	    "WEAPON_STUNROD",
	    "WEAPON_PISTOL",
	    "WEAPON_PISTOL_MK2",
	    "WEAPON_COMBATPISTOL",
	    "WEAPON_APPISTOL",
	    "WEAPON_PISTOL50",
	    "WEAPON_SNSPISTOL",
	    "WEAPON_SNSPISTOL_MK2",
	    "WEAPON_HEAVYPISTOL",
	    "WEAPON_VINTAGEPISTOL",
	    "WEAPON_FLAREGUN",
	    "WEAPON_MARKSMANPISTOL",
	    "WEAPON_REVOLVER",
	    "WEAPON_REVOLVER_MK2",
	    "WEAPON_DOUBLEACTION",
	    "WEAPON_RAYPISTOL",
	    "WEAPON_CERAMICPISTOL",
	    "WEAPON_NAVYREVOLVER",
	    "WEAPON_GADGETPISTOL",
	    "WEAPON_STUNGUN_MP",
	    "WEAPON_MICROSMG",
	    "WEAPON_SMG",
	    "WEAPON_SMG_MK2",
	    "WEAPON_ASSAULTSMG",
	    "WEAPON_COMBATPDW",
	    "WEAPON_MACHINEPISTOL",
	    "WEAPON_MINISMG",
	    "WEAPON_MG",
	    "WEAPON_COMBATMG",
	    "WEAPON_COMBATMG_MK2",
	    "WEAPON_GUSENBERG",
	    "WEAPON_RAYCARBINE",
	    "WEAPON_ASSAULTRIFLE",
	    "WEAPON_ASSAULTRIFLE_MK2",
	    "WEAPON_CARBINERIFLE",
	    "WEAPON_CARBINERIFLE_MK2",
	    "WEAPON_ADVANCEDRIFLE",
	    "WEAPON_SPECIALCARBINE",
	    "WEAPON_SPECIALCARBINE_MK2",
	    "WEAPON_BULLPUPRIFLE",
	    "WEAPON_BULLPUPRIFLE_MK2",
	    "WEAPON_COMPACTRIFLE",
	    "WEAPON_MILITARYRIFLE",
	    "WEAPON_HEAVYRIFLE",
	    "WEAPON_TACTICALRIFLE",
	    "WEAPON_PUMPSHOTGUN",
	    "WEAPON_PUMPSHOTGUN_MK2",
	    "WEAPON_SAWNOFFSHOTGUN",
	    "WEAPON_ASSAULTSHOTGUN",
	    "WEAPON_BULLPUPSHOTGUN",
	    "WEAPON_MUSKET",
	    "WEAPON_HEAVYSHOTGUN",
	    "WEAPON_DBSHOTGUN",
	    "WEAPON_AUTOSHOTGUN",
	    "WEAPON_COMBATSHOTGUN",
	    "WEAPON_SNIPERRIFLE",
	    "WEAPON_HEAVYSNIPER",
	    "WEAPON_HEAVYSNIPER_MK2",
	    "WEAPON_MARKSMANRIFLE",
	    "WEAPON_MARKSMANRIFLE_MK2",
	    "WEAPON_PRECISIONRIFLE",
	    "WEAPON_GRENADELAUNCHER",
	    "WEAPON_RPG",
	    "WEAPON_MINIGUN",
	    "WEAPON_HOMINGLAUNCHER",
	    "WEAPON_COMPACTLAUNCHER",
	    "WEAPON_RAYMINIGUN",
	    "WEAPON_EMPLAUNCHER",
	    "WEAPON_RAILGUNXM3",
	    "WEAPON_TECPISTOL",
	    "WEAPON_FIREWORK",
	    "WEAPON_BATTLERIFLE",
	    "WEAPON_SNOWLAUNCHER"});

	inline constexpr auto allowedGunVanSlots = std::to_array({"1", "2", "3", "4", "5", "6", "7", "8", "9", "10"});

	inline void ClaimSafeEarnings(eAppVinewoodMenuSafe type)
	{
		FiberPool::Push([type] {
			if (!*Pointers.IsSessionStarted)
				return;

			switch (type)
			{
			case eAppVinewoodMenuSafe::NIGHTCLUB:
			{
				if (GPBD_FM::Get()->Entries[Self::GetPlayer().GetId()].PropertyData.NightclubData.SafeCashValue > 0)
					*ScriptGlobal(2708201).As<BOOL*>() = TRUE;
				break;
			}
			case eAppVinewoodMenuSafe::ARCADE:
			{
				if (GPBD_FM::Get()->Entries[Self::GetPlayer().GetId()].PropertyData.ArcadeData.SafeCashValue > 0)
					*ScriptGlobal(2708210).As<BOOL*>() = TRUE;
				break;
			}
			case eAppVinewoodMenuSafe::AGENCY:
			{
				if (GPBD_FM::Get()->Entries[Self::GetPlayer().GetId()].PropertyData.FixerHQData.SafeCashValue > 0)
					*ScriptGlobal(2708219).As<BOOL*>() = TRUE;
				break;
			}
			case eAppVinewoodMenuSafe::SALVAGE_YARD:
			{
				if (GPBD_FM::Get()->Entries[Self::GetPlayer().GetId()].PropertyData.SalvageYardData.TotalEarnings > 0)
					*ScriptGlobal(2708228).As<BOOL*>() = TRUE;
				break;
			}
			case eAppVinewoodMenuSafe::BAIL_OFFICE:
			{
				if (GPBD_FM::Get()->Entries[Self::GetPlayer().GetId()].PropertyData.BailShopData.SafeCashValue > 0)
					*ScriptGlobal(2708237).As<BOOL*>() = TRUE;
				break;
			}
			case eAppVinewoodMenuSafe::GARMENT_FACTORY:
			{
				if (GPBD_FM::Get()->Entries[Self::GetPlayer().GetId()].PropertyData.HackerDenData.SafeCashValue > 0)
					*ScriptGlobal(2708246).As<BOOL*>() = TRUE;
				break;
			}
			case eAppVinewoodMenuSafe::HANDS_ON_CAR_WASH:
			{
				if (GPBD_FM_2::Get()->Entries[Self::GetPlayer().GetId()].SYVehSaleData.HOWCData.SafeCashValue > 0)
					*ScriptGlobal(2708259).As<BOOL*>() = TRUE;
				break;
			}
			}
		});
	}

	// https://github.com/YimMenu-Lua/GunVan
	inline void SetGunvanWeapon(const char* weapon, int slot)
	{
		FiberPool::Push([weapon, slot] {
			auto slottun = "XM22_GUN_VAN_SLOT_WEAPON_TYPE_" + std::to_string(slot);
			Tunable tun{Joaat(slottun.c_str())};
			tun.Set(Joaat(weapon));
		});
	}
}