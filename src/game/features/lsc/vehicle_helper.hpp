#pragma once
#include "types/script/types.hpp"

namespace YimMenu::Features
{
	class VehicleHelper
	{
	public:
		static bool check_mod_blacklist(Hash model, int mod_slot, int mod);
		static const char* get_mod_slot_name(Hash model, int vehicle, int mod_slot);
		static const char* get_mod_name(Hash model, int vehicle, int mod_slot, int mod, int mod_count);
	};
}
