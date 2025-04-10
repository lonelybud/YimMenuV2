#pragma once
#include "ComponentState.hpp"
#include "core/backend/FiberPool.hpp"

namespace YimMenu
{
	class BoolState : public ComponentState
	{
	protected:
		virtual void OnEnable() {};
		virtual void OnDisable() {};

	public:
		BoolState(std::string name, std::string label, std::string description) :
		    ComponentState(name, label, description)
		{
		}

		virtual void Refresh()
		{
			FiberPool::Push([this] {
				m_State ? OnEnable() : OnDisable();
			});
		}
	};
}