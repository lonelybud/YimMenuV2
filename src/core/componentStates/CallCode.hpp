#pragma once
#include "ComponentState.hpp"
#include "core/backend/FiberPool.hpp"

namespace YimMenu
{
	class CallCode : public ComponentState
	{
	protected:
		virtual void OnCall() {};

	public:
		CallCode(std::string name, std::string label, std::string description) :
		    ComponentState(name, label, description)
		{
		}

		virtual void call()
		{
			FiberPool::Push([this] {
				OnCall();
			});
		}
	};
}