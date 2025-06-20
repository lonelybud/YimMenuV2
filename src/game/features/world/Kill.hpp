#include "core/componentStates/CallCode.hpp"
#include "game/gta/Pools.hpp"

namespace YimMenu::Features
{
	class KillAll : public CallCode
	{
		using CallCode::CallCode;

		virtual void OnCall() override
		{
			for (auto ped : Pools::GetPeds())
			{
				if (!ped.IsPlayer())
					ped.Kill();
			}
		}
	};

	class KillAllEnemies : public CallCode
	{
		using CallCode::CallCode;

		virtual void OnCall() override
		{
			for (auto ped : Pools::GetPeds())
			{
				if (!ped.IsPlayer() && ped.IsEnemy())
					ped.Kill();
			}
		}
	};

	inline KillAll _KillAll{"killallpeds", "Kill All Peds", "Kills all peds in the game world"};
	inline KillAllEnemies _KillAllEnemies{"killallenemies", "Kill All Enemies", "Kills all enemies in the game world"};
}