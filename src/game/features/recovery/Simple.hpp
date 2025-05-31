#include "core/backend/FiberPool.hpp"
#include "game/backend/Self.hpp"
#include "game/gta/ScriptGlobal.hpp"
#include "game/pointers/Pointers.hpp"
#include "types/script/globals/GPBD_FM.hpp"

namespace YimMenu::Features
{
	enum class eAppVinewoodMenuSafe
	{
		NIGHTCLUB,
		ARCADE,
		AGENCY,
		SALVAGE_YARD,
		BAIL_OFFICE,
		GARMENT_FACTORY
	};

	inline std::vector<std::pair<eAppVinewoodMenuSafe, const char*>> businessNames = {
	    {eAppVinewoodMenuSafe::NIGHTCLUB, "Nightclub"},
	    {eAppVinewoodMenuSafe::ARCADE, "Arcade"},
	    {eAppVinewoodMenuSafe::AGENCY, "Agency"},
	    {eAppVinewoodMenuSafe::SALVAGE_YARD, "Salvage Yard"},
	    {eAppVinewoodMenuSafe::BAIL_OFFICE, "Bail Office"},
	    {eAppVinewoodMenuSafe::GARMENT_FACTORY, "Garment Factory"},
	};

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
					*ScriptGlobal(2707980).As<BOOL*>() = TRUE;
				break;
			}
			case eAppVinewoodMenuSafe::ARCADE:
			{
				if (GPBD_FM::Get()->Entries[Self::GetPlayer().GetId()].PropertyData.ArcadeData.SafeCashValue > 0)
					*ScriptGlobal(2707989).As<BOOL*>() = TRUE;
				break;
			}
			case eAppVinewoodMenuSafe::AGENCY:
			{
				if (GPBD_FM::Get()->Entries[Self::GetPlayer().GetId()].PropertyData.FixerHQData.SafeCashValue > 0)
					*ScriptGlobal(2707998).As<BOOL*>() = TRUE;
				break;
			}
			case eAppVinewoodMenuSafe::SALVAGE_YARD:
			{
				if (GPBD_FM::Get()->Entries[Self::GetPlayer().GetId()].PropertyData.SalvageYardData.TotalEarnings > 0)
					*ScriptGlobal(2708007).As<BOOL*>() = TRUE;
				break;
			}
			case eAppVinewoodMenuSafe::BAIL_OFFICE:
			{
				if (GPBD_FM::Get()->Entries[Self::GetPlayer().GetId()].PropertyData.BailShopData.SafeCashValue > 0)
					*ScriptGlobal(2708016).As<BOOL*>() = TRUE;
				break;
			}
			case eAppVinewoodMenuSafe::GARMENT_FACTORY:
			{
				if (GPBD_FM::Get()->Entries[Self::GetPlayer().GetId()].PropertyData.HackerDenData.SafeCashValue > 0)
					*ScriptGlobal(2708025).As<BOOL*>() = TRUE;
				break;
			}
			}
		});
	}

}