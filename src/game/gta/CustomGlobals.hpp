#pragma once
#include "game/gta/ScriptGlobal.hpp"
#include "game/backend/PersonalVehicles.hpp"

namespace YimMenu
{
	inline void unlock_achievement_global(int i)
	{
		// https://www.unknowncheats.me/forum/grand-theft-auto-v/699311-achievement-unlocker-fo-gta-enhanced.html
		// https://www.unknowncheats.me/forum/grand-theft-auto-v/500059-globals-locals-discussion-read-page-1-a-38.html#post4740828
		*ScriptGlobal(4525223).At(1).As<int*>() = i;
	}

	inline void delete_pv()
	{
		// https://www.unknowncheats.me/forum/grand-theft-auto-v/707419-lua-scripts-yimmenuv2-collection-thread-45.html#post4749525
		ScriptGlobal request(2733326);
		*request.At(472).As<int*>() = PersonalVehicles::GetCurrent()->GetId();
		*request.At(473).As<int*>() = 1;
		*request.At(474).As<int*>() = 0;
	}
}