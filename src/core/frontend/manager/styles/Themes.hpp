#pragma once

namespace YimMenu
{
	namespace Font
	{
		inline ImFont* g_DefaultFont = nullptr;
		inline float g_DefaultFontSize = 19.0f;

		inline ImFont* g_OptionsFont = nullptr;
		inline float g_OptionsFontSize = 17.0f;

		inline ImFont* g_ChildTitleFont   = nullptr;
		inline float g_ChildTitleFontSize   = 14.5f;
	}

	extern void SetupStyle();
	extern void SetupFonts();
}