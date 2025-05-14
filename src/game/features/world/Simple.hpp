#include "core/backend/FiberPool.hpp"
#include "game/backend/Self.hpp"
#include "game/gta/Natives.hpp"
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

	inline void BringAllPeds()
	{
		FiberPool::Push([] {
			auto pos = Self::GetPed().GetPosition();
			for (auto ped : Pools::GetPeds())
				if (!ped.IsPlayer())
				{
					ped.ForceControl();
					ped.SetPosition(pos);
				}
		});
	}

	inline void BringAllObjs()
	{
		FiberPool::Push([] {
			auto pos = Self::GetPed().GetPosition();
			for (auto ped : Pools::GetObjects())
				if (!ped.IsPlayer())
				{
					ped.ForceControl();
					ped.SetPosition(pos);
				}
		});
	}

	inline void BringAllVehs()
	{
		FiberPool::Push([] {
			auto pos = Self::GetPed().GetPosition();
			for (auto ped : Pools::GetVehicles())
				if (!ped.IsPlayer())
				{
					ped.ForceControl();
					ped.SetPosition(pos);
				}
		});
	}

}