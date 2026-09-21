#include "core/componentStates/BoolState.hpp"
#include "game/backend/Tunables.hpp"
#include "game/gta/data/tunables.hpp"

namespace YimMenu::Features
{
	class EnableIndependenceDay : public BoolState
	{
		using BoolState::BoolState;

		virtual void OnEnable() override
		{
			for (auto& pr : tunables_IndependenceDay)
			{
				Tunable tun{pr.first};
				tun.Set(pr.second);
			}
		}

		virtual void OnDisable() override
		{
			for (auto& pr : tunables_IndependenceDay)
			{
				Tunable tun{pr.first};
				tun.Set(!pr.second);
			}
		}
	};

	inline EnableIndependenceDay _EnableIndependenceDay{"enableIndependenceDay", "Enable Independence Day", "Unlocks stuff like Patriot Tire smoke etc"};
}