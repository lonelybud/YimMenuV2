#pragma once
#include "core/util/Joaat.hpp"
#include "game/gta/ScriptGlobal.hpp"

namespace YimMenu
{
	constexpr int TUNABLE_BASE_ADDRESS = 0x40001;

	class Tunables
	{
		static Tunables& GetInstance()
		{
			static Tunables instance;
			return instance;
		}

		bool m_Initialized = false;
		bool m_Loading = false;
		bool m_ScriptStarted = false;
		std::unordered_map<joaat_t, int> m_Tunables{};
		std::unique_ptr<uint64_t[]> m_TunablesBackup;
		int m_NumTunables = 0;
		int m_CurrentJunkVal = 0x1000000;
		std::unordered_map<int, joaat_t> m_JunkValues{};

		void RunScriptImpl();

	public:
		Tunables();

		static void RunScript()
		{
			GetInstance().RunScriptImpl();
		}

		static bool CachingTunables()
		{
			return GetInstance().m_ScriptStarted;
		}

		static bool Initialized()
		{
			return GetInstance().m_Initialized;
		}

		static void AddJunkValue(int value, joaat_t hash)
		{
			GetInstance().m_JunkValues.emplace(value, hash);
		}

		static int GetCurrentJunkVal()
		{
			return GetInstance().m_CurrentJunkVal;
		}

		static int IncrementJunkVal()
		{
			return GetInstance().m_CurrentJunkVal++;
		}

		static std::optional<ScriptGlobal> GetTunable(joaat_t hash)
		{
			if (auto it = GetInstance().m_Tunables.find(hash); it != GetInstance().m_Tunables.end())
			{
				if (ScriptGlobal(it->second).CanAccess())
					return ScriptGlobal(it->second);
			}

			return std::nullopt;
		}
	};

	class Tunable
	{
		joaat_t m_Hash;
		std::optional<ScriptGlobal> m_Global;

	public:
		constexpr Tunable(joaat_t hash) :
		    m_Hash(hash),
		    m_Global(std::nullopt)
		{
		}

		template<typename T>
		T Get()
		{
			if (m_Global == std::nullopt)
				m_Global = Tunables::GetTunable(m_Hash);
			return *m_Global->As<T*>();
		}

		template<typename T>
		void Set(T new_value)
		{
			if (m_Global == std::nullopt)
				m_Global = Tunables::GetTunable(m_Hash);
			*m_Global->As<T*>() = new_value;
		}
	};
}