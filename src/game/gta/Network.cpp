#include "Network.hpp"
#include "game/gta/ScriptGlobal.hpp"
#include "game/gta/ScriptFunction.hpp"

namespace YimMenu::Network
{
	void LaunchJoinType(JoinType to_launch)
	{
		static ScriptFunction sendToClouds("shop_controller"_J, ScriptPointer("SendToClouds", "2D 00 02 00 00 72 5D ? ? ? 72"));
		static ScriptGlobal join_type_global(1575044);

		sendToClouds.Call<void>();
		*join_type_global.As<JoinType*>() = to_launch;
	}
}