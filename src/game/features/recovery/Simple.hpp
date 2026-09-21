#include "core/backend/FiberPool.hpp"
#include "game/backend/Tunables.hpp"

// https://www.unknowncheats.me/forum/grand-theft-auto-v/772902-tinkerscripts-yimmenuv2.html#post4804655
// https://github.com/YimMenu-Lua/GunVan/blob/main/gun_van.lua

namespace YimMenu::Features
{

    inline constexpr auto allowedGunVanWeapons = std::to_array<std::pair<int, const char *>>({
	    {0, ""},
	    {-1357824103, "Advanced Rifle"},
	    {-1834847097, "Antique Cavalry Dagger"},
	    {584646201, "AP Pistol"},
	    {-1074790547, "Assault Rifle"},
	    {-494615257, "Assault Shotgun"},
	    {-270015777, "Assault SMG"},
	    {-1786099057, "Baseball Bat"},
	    {-853065399, "Battle Axe"},
	    {1924557585, "Battle Rifle"},
	    {-102323637, "Bottle"},
	    {2132975508, "Bullpup Rifle"},
	    {-1654528753, "Bullpup Shotgun"},
	    {1703483498, "Candy Cane"},
	    {-2084633992, "Carbine Rifle"},
	    {727643628, "Ceramic Pistol"},
	    {2144741730, "Combat MG"},
	    {171789620, "Combat PDW"},
	    {1593441988, "Combat Pistol"},
	    {94989220, "Combat Shotgun"},
	    {-618237638, "Compact EMP Launcher"},
	    {125959754, "Compact Grenade Launcher"},
	    {1649403952, "Compact Rifle"},
	    {-2067956739, "Crowbar"},
	    {-275439685, "Double Barrel Shotgun"},
	    {-1746263880, "Double-Action Revolver"},
	    {-1916886713, "El Strickler"},
	    {2138347493, "Firework Launcher"},
	    {1198879012, "Flare Gun"},
	    {-1951375401, "Flashlight"},
	    {-1568386805, "Grenade Launcher"},
	    {1627465347, "Gusenberg Sweeper"},
	    {1317494643, "Hammer"},
	    {-102973651, "Hatchet"},
	    {-771403250, "Heavy Pistol"},
	    {-1045183535, "Heavy Revolver"},
	    {-947031628, "Heavy Rifle"},
	    {984333226, "Heavy Shotgun"},
	    {205991906, "Heavy Sniper"},
	    {1672152130, "Homing Launcher"},
	    {-1716189206, "Knife"},
	    {-656458692, "Knuckle Duster"},
	    {-581044007, "Machete"},
	    {-619010992, "Machine Pistol"},
	    {-598887786, "Marksman Pistol"},
	    {-952879014, "Marksman Rifle"},
	    {-1660422300, "MG"},
	    {324215364, "Micro SMG"},
	    {-1658906650, "Military Rifle"},
	    {-1121678507, "Mini SMG"},
	    {1119849093, "Minigun"},
	    {-1466123874, "Musket"},
	    {-1853920116, "Navy Revolver"},
	    {1737195953, "Nightstick"},
	    {1470379660, "Perico Pistol"},
	    {419712736, "Pipe Wrench"},
	    {-1716589765, "Pistol .50"},
	    {453432689, "Pistol"},
	    {-1810795771, "Pool Cue"},
	    {1853742572, "Precision Rifle"},
	    {487013001, "Pump Shotgun"},
	    {-22923932, "Railgun"},
	    {-1312131151, "RPG"},
	    {2017895192, "Sawed-Off Shotgun"},
	    {-774507221, "Service Carbine"},
	    {736523883, "SMG"},
	    {100416529, "Sniper Rifle"},
	    {62870901, "Snowball Launcher"},
	    {-1076751822, "SNS Pistol"},
	    {-1063057011, "Special Carbine"},
	    {1171102963, "Stun Gun"},
	    {317205821, "Sweeper Shotgun"},
	    {-538741184, "Switchblade"},
	    {350597077, "Tactical SMG"},
	    {-624951259, "The Shocker"},
	    {1198256469, "Unholy Hellbringer"},
	    {-1355376991, "Up-n-Atomizer"},
	    {137902532, "Vintage Pistol"},
	    {-1238556825, "Widowmaker"},
    });

	inline constexpr auto allowedGunVanSlots = std::to_array({"1", "2", "3", "4", "5", "6", "7", "8", "9", "10"});

	inline void SetGunvanWeapon(int weapon, int slot)
	{
		FiberPool::Push([weapon, slot] {
			auto slottun = "XM22_GUN_VAN_SLOT_WEAPON_TYPE_" + std::to_string(slot);
			Tunable tun{Joaat(slottun.c_str())};
			tun.Set(weapon);
		});
	}
}