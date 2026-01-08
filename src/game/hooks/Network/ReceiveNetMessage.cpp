#include "core/hooking/DetourHook.hpp"
#include "game/backend/AnticheatBypass.hpp"

#include "game/hooks/Hooks.hpp"
#include "game/gta/Packet.hpp"
#include "game/backend/Self.hpp"
#include "types/network/netEvent.hpp"
#include "types/network/netMessage.hpp"
#include "types/rage/datBitBuffer.hpp"

namespace YimMenu::Hooks
{
	void Network::ReceiveNetMessage(void* a1, rage::netConnectionManager* mgr, rage::netEvent* event)
	{
		return;
	}
}