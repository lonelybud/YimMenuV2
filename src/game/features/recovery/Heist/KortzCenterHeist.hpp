#pragma once
#include "game/gta/ScriptGlobal.hpp"
#include "core/componentStates/CallCode.hpp"
#include "game/gta/ScriptLocal.hpp"
#include "game/gta/Scripts.hpp"

namespace YimMenu
{
	// https://www.unknowncheats.me/forum/grand-theft-auto-v/500059-globals-locals-discussion-read-page-1-a-39.html#post4746347
	// https://www.unknowncheats.me/forum/grand-theft-auto-v/707419-lua-scripts-yimmenuv2-collection-thread-42.html#post4746547
	// https://github.com/Abdelakil/YimMenuV2/blob/personal/src/game/features/recovery/Heist/KortzCenterHeist.cpp
	namespace KortzCenterHeist
	{
		class SkipFingerprint : public CallCode
		{
			using CallCode::CallCode;

			virtual void OnCall() override
			{
				if (auto thread = Scripts::FindScriptThread("fm_mission_controller_v3"_J))
					*ScriptLocal(thread, 26866).As<int*>() = 5;
			}
		};

		class SkipSignalNodes : public CallCode
		{
			using CallCode::CallCode;

			virtual void OnCall() override
			{
				if (auto thread = Scripts::FindScriptThread("fm_mission_controller_v3"_J))
					*ScriptLocal(thread, 27914).As<int*>() = 5;
			}
		};

		class SkipDataCrack : public CallCode
		{
			using CallCode::CallCode;

			virtual void OnCall() override
			{
				if (auto thread = Scripts::FindScriptThread("fm_mission_controller_v3"_J))
				{
					for (int i = 0; i <= 7; i++)
						*ScriptLocal(thread, 1388).At(i, 4).As<int*>() = 1;
				}
			}
		};

		class CutGlass : public CallCode
		{
			using CallCode::CallCode;

			virtual void OnCall() override
			{
				if (auto thread = Scripts::FindScriptThread("fm_mission_controller_v3"_J))
				{
					for (int i = 0; i <= 4; i++)
						*ScriptLocal(thread, 32855).At(i, 13).At(3).As<float*>() = 100.0f;
				}
			}
		};

		class DisableLaserGrid : public CallCode
		{
			using CallCode::CallCode;

			virtual void OnCall() override
			{
				if (auto thread = Scripts::FindScriptThread("fm_mission_controller_v3"_J))
				{
					*ScriptLocal(thread, 70416).As<int*>() = 4294784;
					*ScriptGlobal(1935711).As<int*>() |= 1;
				}
			}
		};

		static SkipFingerprint _KortzCenterSkipFingerprint{"kortzcenterheistskipfingerprint", "Skip Fingerprint Hack", "Skips fingerprint hacking minigame in computer room"};
		static SkipSignalNodes _KortzCenterSkipSignalNodes{"kortzcenterheistskipsignalnodes", "Skip Signal Nodes", "Skips signal nodes hacking at vault keypad"};
		inline SkipDataCrack _KortzCenterSkipDataCrack{"kortzcenterheistskipdatacrack", "Skip Data Crack", "Skips data crack minigame"};
		inline CutGlass _KortzCenterCutGlass{"kortzcenterheistcutglass", "Cut Glass", "Cuts display case glass instantly"};
		inline DisableLaserGrid _KortzCenterDisableLaser{"kortzcenterheistdisablelaser", "Disable Laser Grid", "Disables laser security grid"};
	}
}