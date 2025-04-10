#pragma once
#include "core/memory/Pattern.hpp"
#include "core/util/Joaat.hpp"

namespace rage
{
	class scrProgram;
}

namespace YimMenu
{
	class ScriptPatches
	{
	public:
		class Data
		{
			std::uint8_t** m_Data;
			std::uint32_t m_Pages;
			std::uint32_t m_Size;

		public:
			inline std::uint8_t** GetData() const
			{
				return m_Data;
			}

			inline std::uint32_t GetSize() const
			{
				return m_Size;
			}

			Data(rage::scrProgram* program);
			~Data();
		};

		class Patch
		{
			std::vector<uint8_t> m_OriginalBytes;
			std::vector<uint8_t> m_PatchedBytes;
			std::optional<int32_t> m_Pc;
			SimplePattern m_Pattern;
			int32_t m_Offset;
			bool m_Enabled;
			std::uint32_t m_Hash;
			std::string m_Name;

			std::optional<int32_t> GetPC();
			void Apply();
			void Restore();

		public:
			Patch(std::string name, joaat_t script, SimplePattern pattern, int32_t offset, std::vector<uint8_t> patch);
			void Enable();
			void Disable();
			void Update();
			bool InScope(std::uint32_t hash);
		};

		// add_patch
		static std::shared_ptr<Patch> AddPatch(std::string name, joaat_t script, const std::string& pattern, int32_t offset, std::vector<uint8_t> patch)
		{
			return GetInstance().AddPatchImpl(name, script, pattern, offset, patch);
		}

		static void RegisterProgram(rage::scrProgram* program)
		{
			GetInstance().RegisterProgramImpl(program);
		}

		static void UnregisterProgram(rage::scrProgram* program)
		{
			GetInstance().UnregisterProgramImpl(program);
		}

		static void OnScriptVMEnter(rage::scrProgram* program)
		{
			GetInstance().OnScriptVMEnterImpl(program);
		}

		static void OnScriptVMLeave(rage::scrProgram* program)
		{
			GetInstance().OnScriptVMLeaveImpl(program);
		}

		static inline void RegisterDefaultScriptPatches()
		{
			// Allows MP vehicles to be used in SP
			auto m_ShopPatch = ScriptPatches::AddPatch("despawnbypass", "shop_controller"_J, "2D 01 04 00 00 2C ? ? ? 56 ? ? 71", 5, {0x71, 0x2E, 0x01, 0x01});
			m_ShopPatch->Enable();
		}

	private:
		ScriptPatches();
		~ScriptPatches();

		static ScriptPatches& GetInstance()
		{
			static ScriptPatches Instance;
			return Instance;
		}

		std::shared_ptr<Patch> AddPatchImpl(std::string name, joaat_t script, const std::string& pattern, int32_t offset, std::vector<uint8_t> patch);
		void RegisterProgramImpl(rage::scrProgram* program);
		void UnregisterProgramImpl(rage::scrProgram* program);
		void OnScriptVMEnterImpl(rage::scrProgram* program);
		void OnScriptVMLeaveImpl(rage::scrProgram* program);
		Data* GetDataImpl(joaat_t script);

		std::vector<std::shared_ptr<Patch>> m_Patches;
		std::unordered_map<joaat_t, std::unique_ptr<Data>> m_Datas;
		std::uint8_t** m_CurrentlyReplacedBytecode;
	};

	using ScriptPatch = std::shared_ptr<ScriptPatches::Patch>;
}