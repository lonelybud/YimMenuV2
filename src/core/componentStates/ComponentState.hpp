#pragma once

namespace YimMenu
{
	class ComponentState
	{
	private:
		std::string m_Name;
		std::string m_Label;
		std::string m_Description;

	public:
		bool m_State;

		ComponentState(std::string name, std::string label, std::string description) :
		    m_Name(name),
		    m_Label(label),
		    m_Description(description),
		    m_State(false)
		{
		}

		const std::string& GetName()
		{
			return m_Name;
		}

		const std::string& GetLabel()
		{
			return m_Label;
		}

		const std::string& GetDescription()
		{
			return m_Description;
		}
	};
}