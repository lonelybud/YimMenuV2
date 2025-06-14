#include "core/backend/FiberPool.hpp"
#include "core/backend/ScriptMgr.hpp"
#include "core/frontend/Notifications.hpp"
#include "game/backend/Self.hpp"
#include "game/gta/Natives.hpp"
#include "types/blip/BlipSprite.hpp"


namespace YimMenu::Features
{
	static void ResolveZCoordinate(Vector3& vec)
	{
		constexpr float max_ground_check = 1000.f;
		float ground_z = vec.z;
		int current_attempts = 0;
		bool found_ground = false;

		do
		{
			STREAMING::REQUEST_COLLISION_AT_COORD(vec.x, vec.y, vec.z);
			if (MISC::GET_GROUND_Z_FOR_3D_COORD(vec.x, vec.y, max_ground_check, &ground_z, false, false))
			{
				vec.z = ground_z + 1.0f;
				found_ground = true;
				break;
			}

			if (current_attempts % 3 == 0)
			{
				ground_z += 25.f;
			}

			++current_attempts;
			ScriptMgr::Yield();
		} while (current_attempts < 20);

		float water_height;
		if (WATER::GET_WATER_HEIGHT(vec.x, vec.y, vec.z, &water_height))
		{
			vec.z = water_height;
			return;
		}

		if (!found_ground)
			vec.z = PATHFIND::GET_APPROX_HEIGHT_FOR_POINT(vec.x, vec.y); // fallback value
	}

	static bool GetBlipLocationOfType(Vector3& location, int sprite)
	{
		Blip blip = HUD::GET_CLOSEST_BLIP_INFO_ID(sprite);
		if (blip)
		{
			location = HUD::GET_BLIP_COORDS(blip);
			location.z += 1.0f;
			return true;
		}
		return false;
	}

	inline void TpToWaypoint()
	{
		FiberPool::Push([] {
			if (HUD::IS_WAYPOINT_ACTIVE())
			{
				auto coords = HUD::GET_BLIP_COORDS(HUD::GET_CLOSEST_BLIP_INFO_ID(HUD::GET_WAYPOINT_BLIP_ENUM_ID()));
				ResolveZCoordinate(coords);
				Self::GetPed().TeleportTo(coords);
				HUD::SET_WAYPOINT_OFF();
			}
		});
	}

	inline void TpToObjective()
	{
		FiberPool::Push([] {
			static constexpr BlipSprite sprites[] = {BlipSprite::RADAR_LEVEL, BlipSprite::RADAR_HIGHER, BlipSprite::RADAR_LOWER, BlipSprite::RADAR_OBJECTIVE_BLUE, BlipSprite::RADAR_OBJECTIVE_GREEN, BlipSprite::RADAR_OBJECTIVE_RED, BlipSprite::RADAR_OBJECTIVE_YELLOW, BlipSprite::RADAR_CONTRABAND, BlipSprite::RADAR_TARGET_A, BlipSprite::RADAR_TARGET_B, BlipSprite::RADAR_TARGET_C, BlipSprite::RADAR_TARGET_D, BlipSprite::RADAR_TARGET_E, BlipSprite::RADAR_TARGET_F, BlipSprite::RADAR_TARGET_G, BlipSprite::RADAR_TARGET_H, BlipSprite::RADAR_PICKUP_MACHINEGUN};
			Vector3 location;
			for (const auto sprite : sprites)
			{
				if (GetBlipLocationOfType(location, static_cast<int>(sprite)))
				{
					Self::GetPed().TeleportTo(location);
					return;
				}
			}
		});
	}

}
