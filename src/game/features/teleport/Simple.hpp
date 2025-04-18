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
		constexpr int max_attempts       = 20;
		float ground_z                   = vec.z;
		int current_attempts             = 0;

		do
		{
			STREAMING::REQUEST_COLLISION_AT_COORD(vec.x, vec.y, vec.z);

			float water_height;
			if (WATER::GET_WATER_HEIGHT(vec.x, vec.y, vec.z, &water_height))
			{
				vec.z = water_height;
				return;
			}

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
		} while (current_attempts < max_attempts);

		vec.z = PATHFIND::GET_APPROX_HEIGHT_FOR_POINT(vec.x, vec.y); // fallback value
	}

	inline void TpToWaypoint()
	{
		FiberPool::Push([] {
			if (HUD::IS_WAYPOINT_ACTIVE())
			{
				auto coords = HUD::GET_BLIP_COORDS(HUD::GET_CLOSEST_BLIP_INFO_ID(HUD::GET_WAYPOINT_BLIP_ENUM_ID()));
				ResolveZCoordinate(coords);
				Self::GetPed().TeleportTo(coords);
			}
		});
	}

}