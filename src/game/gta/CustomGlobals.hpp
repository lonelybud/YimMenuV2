#pragma once
#include "game/gta/ScriptGlobal.hpp"


namespace YimMenu
{
	inline void unlock_achievement_global(int i)
	{
		// https://www.unknowncheats.me/forum/grand-theft-auto-v/699311-achievement-unlocker-fo-gta-enhanced.html
		// https://www.unknowncheats.me/forum/grand-theft-auto-v/500059-globals-locals-discussion-read-page-1-a-38.html#post4740828
		*ScriptGlobal(4525223).At(1).As<int*>() = i;
	}
}