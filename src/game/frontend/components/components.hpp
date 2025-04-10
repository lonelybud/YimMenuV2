#pragma once
#include "core/componentStates/BoolState.hpp"

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
			if (updated = ImGui::Checkbox(state.GetLabel().data(), &state.m_State))
				state.Refresh();
			if (ImGui::IsItemHovered())
				if (auto desc = state.GetDescription(); desc.length())
					ImGui::SetTooltip(desc.c_str());

			return updated;
		}
	};
}
