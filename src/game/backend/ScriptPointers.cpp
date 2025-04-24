#include "ScriptPointers.hpp"
#include "core/filemgr/FileMgr.hpp"
#include "core/memory/ModuleMgr.hpp"

namespace YimMenu
{
	void ScriptPointers::CachePointerImpl(joaat_t nameHash, std::uint32_t address)
	{
		m_ScriptPointers.emplace(nameHash, address);
	}

	std::uint32_t ScriptPointers::GetPointerImpl(joaat_t nameHash)
	{
		if (auto it = m_ScriptPointers.find(nameHash); it != m_ScriptPointers.end())
		{
			return it->second;
		}

		return 0;
	}
}