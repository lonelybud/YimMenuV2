#include "core/componentStates/CallCode.hpp"
#include "game/backend/Self.hpp"
#include "game/gta/ScriptGlobal.hpp"
#include "game/pointers/Pointers.hpp"
#include "types/script/globals/GPBD_FM.hpp"
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

	class ClaimSafeEarnings : public CallCode
	{
		using CallCode::CallCode;

		virtual void OnCall() override
		{
			if (!*Pointers.IsSessionStarted)
				return;

			switch (selected_business.first)
			{
			case eAppVinewoodMenuSafe::NIGHTCLUB:
			{
				if (GPBD_FM::Get()->Entries[Self::GetPlayer().GetId()].PropertyData.NightclubData.SafeCashValue > 0)
					*ScriptGlobal(2708832).As<BOOL*>() = TRUE;
				break;
			}
			case eAppVinewoodMenuSafe::ARCADE:
			{
				if (GPBD_FM::Get()->Entries[Self::GetPlayer().GetId()].PropertyData.ArcadeData.SafeCashValue > 0)
					*ScriptGlobal(2708841).As<BOOL*>() = TRUE;
				break;
			}
			case eAppVinewoodMenuSafe::AGENCY:
			{
				if (GPBD_FM::Get()->Entries[Self::GetPlayer().GetId()].PropertyData.FixerHQData.SafeCashValue > 0)
					*ScriptGlobal(2708850).As<BOOL*>() = TRUE;
				break;
			}
			case eAppVinewoodMenuSafe::SALVAGE_YARD:
			{
				if (GPBD_FM::Get()->Entries[Self::GetPlayer().GetId()].PropertyData.SalvageYardData.TotalEarnings > 0)
					*ScriptGlobal(2708859).As<BOOL*>() = TRUE;
				break;
			}
			case eAppVinewoodMenuSafe::BAIL_OFFICE:
			{
				if (GPBD_FM::Get()->Entries[Self::GetPlayer().GetId()].PropertyData.BailShopData.SafeCashValue > 0)
					*ScriptGlobal(2708868).As<BOOL*>() = TRUE;
				break;
			}
			case eAppVinewoodMenuSafe::GARMENT_FACTORY:
			{
				if (GPBD_FM::Get()->Entries[Self::GetPlayer().GetId()].PropertyData.HackerDenData.SafeCashValue > 0)
					*ScriptGlobal(2708883).As<BOOL*>() = TRUE;
				break;
			}
			case eAppVinewoodMenuSafe::HANDS_ON_CAR_WASH:
			{
				if (GPBD_FM_2::Get()->Entries[Self::GetPlayer().GetId()].SYVehSaleData.HOWCData.SafeCashValue > 0)
					*ScriptGlobal(2708890).As<BOOL*>() = TRUE;
				break;
			}
			}
		}

	public:
		std::pair<Features::eAppVinewoodMenuSafe, const char*> selected_business = Features::businessNames[0];
	};

	inline ClaimSafeEarnings _ClaimSafeEarnings{"claimsafeearnings", "Claim Safe Earnings", "Claims your safe earnings from the selected business."};
}