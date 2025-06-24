#pragma once
#include "core/componentStates/BoolState.hpp"
#include "core/componentStates/CallCode.hpp"
#include <imgui.h>

namespace YimMenu
{
	class components
	{
	public:
		static inline void ver_space()
		{
			ImGui::Dummy(ImVec2(0.0f, ImGui::GetTextLineHeight()));
		}
		static inline void hor_space()
		{
			ImGui::SameLine(0, 2.0f * ImGui::GetTextLineHeight());
		}

		static bool checkbox(BoolState& state)
		{
			bool updated;
			if ((updated = ImGui::Checkbox(state.GetLabel().data(), &state.m_State)))
				state.Refresh();
			if (ImGui::IsItemHovered())
				if (auto desc = state.GetDescription(); desc.length())
					ImGui::SetTooltip("%s", desc.c_str());

			return updated;
		}

		static void button(CallCode& code)
		{
			if (ImGui::Button(code.GetLabel().c_str()))
				code.call();
			if (ImGui::IsItemHovered())
				if (auto desc = code.GetDescription(); desc.length())
					ImGui::SetTooltip("%s", desc.c_str());
		}
	};
}
