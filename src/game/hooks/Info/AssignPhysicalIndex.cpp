#include "core/hooking/DetourHook.hpp"
#include "game/hooks/Hooks.hpp"
#include "types/network/CNetGamePlayer.hpp"

namespace YimMenu::Hooks
{
	void Info::AssignPhysicalIndex(CNetworkPlayerMgr* mgr, CNetGamePlayer* player, std::uint8_t index)
	{
		if (!g_Running)
			return BaseHook::Get<Info::AssignPhysicalIndex, DetourHook<decltype(&Info::AssignPhysicalIndex)>>()->Original()(mgr, player, index);

		if (index != 255)
		{
			if (player->m_PlayerIndex != 255)
				LOGF(WARNING, "Player {} changed their player index from {} to {}", player->GetName(), player->m_PlayerIndex, index);
			BaseHook::Get<Info::AssignPhysicalIndex, DetourHook<decltype(&Info::AssignPhysicalIndex)>>()->Original()(mgr, player, index);
			LOGF(INFO, "Player {} joined", player->GetName());
		}
		else
		{
			LOGF(INFO, "Player {} left", player->GetName());
			BaseHook::Get<Info::AssignPhysicalIndex, DetourHook<decltype(&Info::AssignPhysicalIndex)>>()->Original()(mgr, player, index);
		}
	}
}