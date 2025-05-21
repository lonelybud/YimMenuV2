#include "core/backend/FiberPool.hpp"
#include "game/gta/Pools.hpp"

namespace YimMenu::Features
{
	inline void KillAllPeds()
	{
		FiberPool::Push([] {
			for (auto ped : Pools::GetPeds())
				if (!ped.IsPlayer())
					ped.Kill();
		});
	}

	inline void KillAllEnemies()
	{
		FiberPool::Push([] {
			for (auto ped : Pools::GetPeds())
				if (!ped.IsPlayer() && ped.IsEnemy())
					ped.Kill();
		});
	}
}