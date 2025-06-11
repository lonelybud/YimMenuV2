#pragma once
#include "core/util/Joaat.hpp"

namespace YimMenu
{
	class ScriptPointers
	{
		static ScriptPointers& GetInstance()
		{
			static ScriptPointers instance;
			return instance;
		}

		void CachePointerImpl(joaat_t scriptHash, joaat_t nameHash, std::uint32_t address);
		std::uint32_t GetPointerImpl(joaat_t scriptHash, joaat_t nameHash);

		std::unordered_map<joaat_t, std::unordered_map<joaat_t, std::uint32_t>> m_ScriptPointers{};

	public:
		static void CachePointer(joaat_t scriptHash, joaat_t nameHash, std::uint32_t address)
		{
			GetInstance().CachePointerImpl(scriptHash, nameHash, address);
		}

		static std::uint32_t GetPointer(joaat_t scriptHash, joaat_t nameHash)
		{
			return GetInstance().GetPointerImpl(scriptHash, nameHash);
		}
	};
}