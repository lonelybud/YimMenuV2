#include "core/backend/FiberPool.hpp"
#include "core/backend/ScriptMgr.hpp"
#include "core/frontend/Notifications.hpp"
#include "game/backend/Self.hpp"
#include "game/gta/Natives.hpp"


namespace YimMenu::Features
{
	static void ResolveZCoordinate(Vector3& vec)
	{
		constexpr float max_ground_check = 1000.f;
		float ground_z = vec.z;
		int current_attempts = 0;

		do
		{
			STREAMING::REQUEST_COLLISION_AT_COORD(vec.x, vec.y, vec.z);
			if (MISC::GET_GROUND_Z_FOR_3D_COORD(vec.x, vec.y, max_ground_check, &ground_z, false, false))
			{
				vec.z = ground_z + 1.0f;
				return;
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
			static const auto sprites = {1, 0, 2, 38, 143, 144, 145, 146, 161, 478, 501, 514, 521, 535, 536, 537, 538, 539, 540, 541, 542, 549, 556, 568, 615, 761, 762, 763, 764, 765, 780, 817, 842, 844, 845, 850};
			Vector3 location;
			for (const auto sprite : sprites)
			{
				if (GetBlipLocationOfType(location, sprite))
				{
					Self::GetPed().TeleportTo(location);
					return;
				}
			}
		});
	}

}
