#pragma once
#include "BoolState.hpp"
#include "core/backend/FiberPool.hpp"
#include "core/backend/ScriptMgr.hpp"

namespace YimMenu
{
	class LoopState : public BoolState
	{
		static inline std::vector<LoopState*> all_states{};

	public:
		LoopState(std::string name, std::string label, std::string description) :
		    BoolState(name, label, description)
		{
			LoopState::all_states.push_back(this);
		}

		virtual void OnTick() = 0;

		static void RunScript()
		{
			while (g_Running)
			{
				for (auto& state : LoopState::all_states)
					if (state->m_State)
						state->OnTick();

				ScriptMgr::Yield();
			}
		}
	};
}