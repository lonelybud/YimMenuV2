#pragma once
#include <windows.h>

namespace YimMenu
{
	class GUI final
	{
	private:
		GUI();

	public:
		~GUI();

		GUI(const GUI&)                = delete;
		GUI(GUI&&) noexcept            = delete;
		GUI& operator=(const GUI&)     = delete;
		GUI& operator=(GUI&&) noexcept = delete;

		static void Init()
		{
			GetInstance().m_IsOpen = false;
		}

		static bool IsOpen()
		{
			return GetInstance().m_IsOpen;
		}

		static void Toggle()
		{
			GetInstance().m_IsOpen ^= true;
		}

		static bool IsUsingKeyboard()
		{
			return ImGui::GetIO().WantTextInput;
		}

		static void RunScript()
		{
			GetInstance().RunScriptImpl();
		}

	private:
		void WndProc(HWND hwnd, UINT msg, WPARAM wparam, LPARAM lparam);

		void RunScriptImpl();

		static void ToggleMouse();
		static GUI& GetInstance()
		{
			static GUI i{};

			return i;
		}

	private:
		bool m_IsOpen;
	};
}