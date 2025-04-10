#include "core/backend/FiberPool.hpp"
#include "game/backend/Self.hpp"
#include "game/gta/Natives.hpp"
#include "game/gta/Stats.hpp"
#include "game/gta/data/Weapons.hpp"

namespace YimMenu::Features
{
	inline void ClearSelfDamage()
	{
		FiberPool::Push([] {
			Self::GetPed().ClearDamage();
		});
	}

	inline void FillInventory()
	{
		FiberPool::Push([] {
			Stats::SetInt("MPX_NO_BOUGHT_YUM_SNACKS", 30);
			Stats::SetInt("MPX_NO_BOUGHT_HEALTH_SNACKS", 15);
			Stats::SetInt("MPX_NO_BOUGHT_EPIC_SNACKS", 5);
			Stats::SetInt("MPX_NUMBER_OF_CHAMP_BOUGHT", 5);
			Stats::SetInt("MPX_NUMBER_OF_ORANGE_BOUGHT", 10);
			Stats::SetInt("MPX_NUMBER_OF_BOURGE_BOUGHT", 10);
			Stats::SetInt("MPX_NUMBER_OF_SPRUNK_BOUGHT", 10);
			Stats::SetInt("MPX_MP_CHAR_ARMOUR_1_COUNT", 10);
			Stats::SetInt("MPX_MP_CHAR_ARMOUR_2_COUNT", 10);
			Stats::SetInt("MPX_MP_CHAR_ARMOUR_3_COUNT", 10);
			Stats::SetInt("MPX_MP_CHAR_ARMOUR_4_COUNT", 10);
			Stats::SetInt("MPX_MP_CHAR_ARMOUR_5_COUNT", 10);
			Stats::SetInt("MPX_CIGARETTES_BOUGHT", 20);
			Stats::SetInt("MPX_BREATHING_APPAR_BOUGHT", 20);
			
			// others
			Stats::SetInt("MPX_CLUB_POPULARITY", 1000);
		});
	}

	inline void GiveAllWeapons()
	{
		FiberPool::Push([] {
			for (auto weapon : Data::Weapons)
				Self::GetPed().GiveWeapon(weapon);
		});
	}
	inline void RefillAllWeapons()
	{
		FiberPool::Push([] {
			for (auto weapon : Data::Weapons)
			{
				int ammo_in;
				WEAPON::GET_MAX_AMMO(Self::GetPed().GetHandle(), weapon, &ammo_in);
				WEAPON::SET_PED_AMMO(Self::GetPed().GetHandle(), weapon, ammo_in, 0);
			}
		});
	}


	inline void Heal()
	{
		FiberPool::Push([] {
			int maxHealth = Self::GetPed().GetMaxHealth();
			int maxArmour = Self::GetPlayer().GetMaxArmour();
			Self::GetPed().SetHealth(maxHealth);
			Self::GetPed().SetArmour(maxArmour);
		});
	}

	inline void GiveParachute()
	{
		FiberPool::Push([] {
			PLAYER::SET_PLAYER_HAS_RESERVE_PARACHUTE(Self::GetPlayer().GetId());

			if (auto ped = Self::GetPed())
			{
				if (!ped.HasWeapon("GADGET_PARACHUTE"_J))
					ped.GiveWeapon("GADGET_PARACHUTE"_J);
			}
		});
	}

	inline void SkipCutscene()
	{
		FiberPool::Push([] {
			CUTSCENE::STOP_CUTSCENE_IMMEDIATELY();
		});
	}

	inline void Suicide()
	{
		FiberPool::Push([] {
			Self::GetPed().SetInvincible(false);
			Self::GetPed().SetHealth(0);
		});
	}

	inline void ClearWanted()
	{
		FiberPool::Push([] {
			Self::GetPlayer().SetWantedLevel(0);
		});
	}

}