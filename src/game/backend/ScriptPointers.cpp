#include "ScriptPointers.hpp"
#include "core/filemgr/FileMgr.hpp"
#include "core/memory/ModuleMgr.hpp"

namespace YimMenu
{
	void ScriptPointers::CachePointerImpl(joaat_t scriptHash, joaat_t nameHash, std::uint32_t address)
	{
		if (auto it = m_ScriptPointers.find(scriptHash); it != m_ScriptPointers.end())
			it->second.emplace(nameHash, address);
		else
		{
			m_ScriptPointers.emplace(scriptHash, std::unordered_map<joaat_t, std::uint32_t>({{nameHash, address}}));
		}
	}

	std::uint32_t ScriptPointers::GetPointerImpl(joaat_t scriptHash, joaat_t nameHash)
	{
		if (auto it = m_ScriptPointers.find(scriptHash); it != m_ScriptPointers.end())
		{
			if (auto it2 = it->second.find(nameHash); it2 != it->second.end())
			{
				return it2->second;
			}
		}

		return 0;
	}
}