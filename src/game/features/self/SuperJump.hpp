#include "core/componentStates/LoopState.hpp"
#include "game/backend/Self.hpp"
#include "game/gta/Natives.hpp"

namespace YimMenu::Features
{
	class SuperJump : public LoopState
	{
		using LoopState::LoopState;

		virtual void OnTick() override
		{
			MISC::SET_SUPER_JUMP_THIS_FRAME(Self::GetPlayer().GetId());
		}
	};

	inline SuperJump _SuperJump{"superjump", "Super Jump", "Jump higher than normal"};
}