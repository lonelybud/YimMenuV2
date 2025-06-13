#include "core/componentStates/LoopState.hpp"
#include "game/backend/Tunables.hpp"

namespace YimMenu::Features
{
	class OverrideRPMultiplier : public LoopState
	{
		using LoopState::LoopState;

		Tunable m_XPMultiplier{"XP_MULTIPLIER"_J};

		virtual void OnTick() override
		{
			m_XPMultiplier.Set(_RpMultiplierInput);
		}

		virtual void OnDisable() override
		{
			m_XPMultiplier.Set(1.0f);
		}

	public:
		float _RpMultiplierInput = 1.f;
	};

	inline OverrideRPMultiplier _OverrideRPMultiplier{"overriderpmultiplier", "RP Multiplier", "Multiplies RP by the given value"};
}