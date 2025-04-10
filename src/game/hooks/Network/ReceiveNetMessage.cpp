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
	static std::optional<rage::netMessage::Type> ReadType(rage::datBitBuffer& buffer)
	{
		if (buffer.Read<int>(14) != 0x3246)
			return std::nullopt;

		auto extended = buffer.Read<bool>(1);
		return buffer.Read<rage::netMessage::Type>(extended ? 16 : 8);
	}

	void Network::ReceiveNetMessage(void* a1, rage::netConnectionManager* mgr, rage::netEvent* event)
	{
		if (!g_Running)
			return BaseHook::Get<Network::ReceiveNetMessage, DetourHook<decltype(&Network::ReceiveNetMessage)>>()->Original()(a1, mgr, event);

		if (event->GetEventType() != rage::netEvent::Type::FrameReceived)
			return BaseHook::Get<Network::ReceiveNetMessage, DetourHook<decltype(&Network::ReceiveNetMessage)>>()->Original()(a1, mgr, event);

		// TODO: port security ID stuff from V1
		auto fr_evt = reinterpret_cast<rage::netEventFrameReceived*>(event);
		rage::datBitBuffer buffer(fr_evt->m_Data, fr_evt->m_Length, true);
		
		rage::netMessage::Type type = ReadType(buffer).value_or(rage::netMessage::Type::Invalid);

		switch (type)
		{
		case rage::netMessage::Type::KickPlayer:
		{
			if (!AnticheatBypass::IsFSLLoaded())
				return;
			break;
		}
		case rage::netMessage::Type::BattlEyeCmd:
		{
			if (!AnticheatBypass::IsFSLLoaded() && !AnticheatBypass::IsBattlEyeRunning())
			{
				char data[1028]{};
				int size = buffer.Read<int>(11);
				bool from_client = buffer.Read<bool>(1);
				buffer.Seek(4); // normalize before we read
				buffer.ReadArrayBytes(&data, size);

				if (from_client)
					break;

				Packet reply;
				char reply_buf[1028]{};
				int reply_sz = 0;

				auto op = data[0];

				if (op == 0)
				{
					char payload[] = {0x0, 0x5};
					reply_sz = sizeof(payload);
					memcpy(reply_buf, payload, reply_sz);
				}
				else if (op == 2 || op == 4)
				{
					char payload[] = {op, data[1]};
					reply_sz = sizeof(payload);
					memcpy(reply_buf, payload, reply_sz);
				}
				else if (op == 9)
				{
					reply_sz = size;
					memcpy(reply_buf, data, reply_sz);
				}

				reply.WriteMessageHeader(rage::netMessage::Type::BattlEyeCmd);
				reply.GetBuffer().Write<int>(reply_sz, 11);
				reply.GetBuffer().Write<bool>(true, 1);
				reply.GetBuffer().Seek(4);
				reply.GetBuffer().WriteArrayBytes(reply_buf, reply_sz);
				reply.Send(fr_evt->m_MsgId);
				return;
			}
			break;
		}
		default: 
			break;
		}

		BaseHook::Get<Network::ReceiveNetMessage, DetourHook<decltype(&Network::ReceiveNetMessage)>>()->Original()(a1, mgr, event);
	}
}