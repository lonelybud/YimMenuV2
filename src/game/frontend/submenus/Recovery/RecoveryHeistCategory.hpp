#pragma once
#include "core/frontend/manager/Submenu.hpp"
#include "game/frontend/components/components.hpp"
#include "core/backend/FiberPool.hpp"
#include "game/gta/ScriptFunction.hpp"
#include "game/gta/Stats.hpp"
#include "types/script/globals/GPBD_FM_2.hpp"

namespace YimMenu::Submenus
{
	const char* cayo_targets[] = {
	    "Tequila (630K)",
	    "Ruby Necklace (700K)",
	    "Bearer Bonds (770K)",
	    "Pink Diamond (1.3M)",
	    "Madrazo Files",
	    "Panther Statue (1.9M)"};
	const char* casino_targets[] = {"Money", "Gold", "Art", "Diamonds"};
	const char* casino_approach[] = {"Unselected", "Silent & Sneaky", "The Big Con", "Aggressive"};
	const char* autoshop_contracts[] = {
	    "The Union Depository",
	    "The Superdollar Deal",
	    "The Bank Contract",
	    "The ECU Job",
	    "The Prison Contract",
	    "The Agency Deal",
	    "The LOST Contract",
	    "The Data Contract"};

	class RecoveryHeistCategory : public SubmenuMenuCategory
	{
		using SubmenuMenuCategory::SubmenuMenuCategory;
		void Draw()
		{
			components::checkbox(YimMenu::Features::_PlayAllMissionsSolo);
			static int team;
			ImGui::SetNextItemWidth(150);
			ImGui::InputInt("Team", &team);
			ImGui::SameLine();
			if (ImGui::Button("DoTeamSwap"))
				FiberPool::Push([] {
					static ScriptFunction DoTeamSwap("fm_mission_controller"_J, ScriptPointer("DoTeamSwap", "2D 02 04 00 00 38 00 50"));
					DoTeamSwap.Call<void>(team, true);
				});

			components::ver_space();
			// https://www.unknowncheats.me/forum/grand-theft-auto-v/707419-lua-scripts-yimmenuv2-collection-thread-18.html#post4547669
			if (ImGui::Button("Dr. Dre Contract preps skip"))
				FiberPool::Push([] {
					Stats::SetInt("MPX_FIXER_STORY_BS", 4095);
				});

			components::ver_space();
			// https://www.unknowncheats.me/forum/grand-theft-auto-v/461672-gtahax-1-70-external-thread-3-a-214.html
			// https://github.com/SilentSalo/SilentNight/blob/1f7c02b31afa24f029a892f21d82c789fbc4189f/Yim/Silent_Night_v0.0.5.lua#L663
			if (ImGui::Button("Cluckin Bell preps skip"))
				FiberPool::Push([] {
					Stats::SetInt("MPX_SALV23_INST_PROG", 31);
				});

			components::ver_space();
			// https://www.unknowncheats.me/forum/grand-theft-auto-v/699943-stats-editor-external-enhanced-12.html
			// https://www.unknowncheats.me/forum/grand-theft-auto-v/698429-skip-cooldown-mission-selector-deguzman.html
			// https://www.unknowncheats.me/forum/4349818-post4919.html
			ImGui::Text("Do the first setup misson on hard mode...");
			if (ImGui::Button("Oscar gunzman flies again preps skip"))
				FiberPool::Push([] {
					Stats::SetInt("MPX_HACKER24_INST_BS", 31);
				});

			components::ver_space();
			// https://www.unknowncheats.me/forum/4539241-post138.html
			if (ImGui::Button("KnoWay out preps skip"))
				FiberPool::Push([] {
					Stats::SetInt("MPX_M25_AVI_MISSION_CURRENT", 4);
				});

			components::ver_space();
			// https://www.unknowncheats.me/forum/grand-theft-auto-v/699943-stats-editor-external-enhanced-12.html
			static int contract = -1;
			ImGui::Text("Select the contract on board first...");
			ImGui::SetNextItemWidth(200.f);
			if (ImGui::BeginCombo("AutoShop Contract", contract == -1 ? "unkown" : autoshop_contracts[contract]))
			{
				for (int i = 0; i < 8; ++i)
					if (ImGui::Selectable(autoshop_contracts[i], i == contract))
						contract = i;
				ImGui::EndCombo();
			}
			ImGui::SameLine();
			if (ImGui::Button("Set Contract"))
				if (contract != -1)
					FiberPool::Push([] {
						Stats::SetInt("MPX_TUNER_CURRENT", contract);
						Stats::SetInt("MPX_TUNER_GEN_BS", -1);
					});

			components::ver_space();
			// https://www.unknowncheats.me/forum/grand-theft-auto-v/368204-skip-casino-heist-preps-using-gtahax.html
			// https://github.com/YimMenu-Lua/Casino-Pacino/blob/main/CasinoPacino.lua
			ImGui::Text("Dont use for hard mode!!! Pay the setup fees first...");
			if (ImGui::Button("Casino Heist Prep Skip"))
				FiberPool::Push([] {
					Stats::SetInt("MPX_H3OPT_POI", 1023);
					Stats::SetInt("MPX_H3OPT_ACCESSPOINTS", 2047);
					Stats::SetInt("MPX_H3OPT_BITSET1", 1); // scope the vault

					auto casinoTarget = Stats::GetInt("MPX_H3OPT_TARGET");
					auto lastApproach = Stats::GetInt("MPX_H3_LAST_APPROACH"); // "Unselected", "Silent & Sneaky", "The Big Con", "Aggressive"

					LOG(VERBOSE) << "casinoTarget " << (casinoTarget == -1 ? "Unknown" : casino_targets[casinoTarget]);
					LOG(VERBOSE) << "lastApproach " << casino_approach[lastApproach];

					if (lastApproach == 1 || lastApproach == 3) // "Silent & Sneaky" ||  "Aggressive"
						Stats::SetInt("MPX_H3OPT_APPROACH", 2); // "The Big Con"
					else if (lastApproach == 2)                 // "The Big Con"
						Stats::SetInt("MPX_H3OPT_APPROACH", 1); // "Silent & Sneaky"

					auto approach = Stats::GetInt("MPX_H3OPT_APPROACH");
					if (approach == 0) // no approach selected (please select manually)
						return;

					LOG(VERBOSE) << "currApproach " << casino_approach[approach];

					Stats::SetInt("MPX_H3OPT_CREWDRIVER", 1); // Karim Denz
					Stats::SetInt("MPX_H3OPT_CREWHACKER", 5); // Paige Harris
					Stats::SetInt("MPX_H3OPT_VEHS", 3);       // Sentinel Classic
					Stats::SetInt("MPX_H3OPT_MASKS", 4);      // Emoji Set

					Stats::SetInt("MPX_H3OPT_DISRUPTSHIP", 3); // Security Strength: 1 = Strong, 2 = Medium, 3 = Weak
					Stats::SetInt("MPX_H3OPT_BODYARMORLVL", -1);
					Stats::SetInt("MPX_H3OPT_KEYLEVELS", 2); // 1 = Level1 Security Pass, 2 = Level2 Security Pass

					if (approach == 1)
					{
						Stats::SetInt("MPX_H3OPT_CREWWEAP", 1); // Karl Abolaji
						Stats::SetInt("MPX_H3OPT_WEAPS", 0);
						Stats::SetInt("MPX_H3OPT_BITSET1", 127);
						ScriptMgr::Yield(500ms);
						Stats::SetInt("MPX_H3OPT_BITSET0", 8388607); // 4456480
					}
					if (approach == 2)
					{
						Stats::SetInt("MPX_H3OPT_CREWWEAP", 1); // Karl Abolaji
						Stats::SetInt("MPX_H3OPT_WEAPS", 0);
						Stats::SetInt("MPX_H3OPT_BITSET1", 255);
						ScriptMgr::Yield(500ms);
						Stats::SetInt("MPX_H3OPT_BITSET0", 8388607); // 4468736
					}
					if (approach == 3)
					{
						Stats::SetInt("MPX_H3OPT_CREWWEAP", 5); // Patrick McReary
						Stats::SetInt("MPX_H3OPT_WEAPS", 0);
						Stats::SetInt("MPX_H3OPT_BITSET1", 1023);
						ScriptMgr::Yield(500ms);
						Stats::SetInt("MPX_H3OPT_BITSET0", 8388607); // 5767190
					}
				});

			components::ver_space();
			// https://www.unknowncheats.me/forum/grand-theft-auto-v/368204-skip-casino-heist-preps-using-gtahax.html
			// https://github.com/YimMenu-Lua/Casino-Pacino/blob/main/CasinoPacino.lua
			ImGui::Text("Select the heist first...");
			if (ImGui::Button("Apartment Heist Prep Skip"))
				FiberPool::Push([] {
					Stats::SetInt("MPX_HEIST_PLANNING_STAGE", -1);
				});

			components::ver_space();
			// https: //www.unknowncheats.me/forum/grand-theft-auto-v/431801-cayo-perico-heist-click-61.html
			static bool scope_cayo_island = false;
			ImGui::Text("Dont use for hard mode!!! Pay the setup fees first...");
			if (ImGui::Button("Cayo Perico prep skip"))
				FiberPool::Push([] {
					auto cayoTarget = Stats::GetInt("MPX_H4CNF_TARGET");
					LOG(VERBOSE) << "CayoTarget " << (cayoTarget == -1 ? "Unknown" : cayo_targets[cayoTarget]);

					if (scope_cayo_island)
					{
						Stats::SetInt("MPX_H4LOOT_CASH_I_SCOPED", Stats::GetInt("MPX_H4LOOT_CASH_I"));
						Stats::SetInt("MPX_H4LOOT_COKE_I_SCOPED", Stats::GetInt("MPX_H4LOOT_COKE_I"));
						Stats::SetInt("MPX_H4LOOT_WEED_I_SCOPED", Stats::GetInt("MPX_H4LOOT_WEED_I"));
					}

					Stats::SetInt("MPX_H4LOOT_CASH_C_SCOPED", Stats::GetInt("MPX_H4LOOT_CASH_C"));
					Stats::SetInt("MPX_H4LOOT_GOLD_C_SCOPED", Stats::GetInt("MPX_H4LOOT_GOLD_C"));
					Stats::SetInt("MPX_H4LOOT_PAINT_SCOPED", Stats::GetInt("MPX_H4LOOT_PAINT"));

					Stats::SetInt("MPX_H4CNF_APPROACH", 223);  // unlock all approach vehicles (fixed)
					Stats::SetInt("MPX_H4CNF_WEAPONS", 1);     // aggressor
					Stats::SetInt("MPX_H4CNF_BS_GEN", 196608); // 196608, all points of interest (fixed)
					Stats::SetInt("MPX_H4CNF_BS_ENTR", 63);    // 63, entries (fixed)
					Stats::SetInt("MPX_H4CNF_WEP_DISRP", 3);
					Stats::SetInt("MPX_H4CNF_ARM_DISRP", 3);
					Stats::SetInt("MPX_H4CNF_HEL_DISRP", 3);
					Stats::SetInt("MPX_H4_MISSIONS", 65027); // all prep

					ScriptMgr::Yield(500ms);
					if (cayoTarget == 2) // Bearer Bonds
						Stats::SetInt("MPX_H4_PROGRESS", 123051);
					else
						Stats::SetInt("MPX_H4_PROGRESS", 90147);

					// Stats::SetInt("MPX_H4_PLAYTHROUGH_STATUS", 25);
					// Stats::SetInt("MPX_H4CNF_BS_ABIL", 0);
					// Stats::SetInt("MPX_H4CNF_TROJAN", 5); // 2, 5 ,?

					// ScriptMgr::Yield(500ms);
					// if (auto thread = Scripts::FindScriptThread("heist_island_planning"_J))
					// 	*ScriptLocal(thread, 1570).As<int*>() = 2;
				});
			ImGui::SameLine();
			ImGui::Checkbox("Scope Island targets?", &scope_cayo_island);

			components::ver_space();
			// https://github.com/YimMenu/YimMenuV2/blob/enhanced/src/game/features/recovery/Heist/DoomsdayHeist.cpp
			constexpr auto doomsdayCategory = std::to_array({"ACT 1", "ACT 2", "ACT 3"});
			static int selectedDoomsdayCategory = 0;
			ImGui::SetNextItemWidth(300.f);
			if (ImGui::BeginCombo("DoomsdayCategory", doomsdayCategory[selectedDoomsdayCategory]))
			{
				for (int i = 0; i < doomsdayCategory.size(); ++i)
					if (ImGui::Selectable(doomsdayCategory[i], selectedDoomsdayCategory == i))
						selectedDoomsdayCategory = i;
				ImGui::EndCombo();
			}
			if (ImGui::Button("Setup Selected Doomsday Act"))
				FiberPool::Push([] {
					switch (selectedDoomsdayCategory)
					{
					case 0:
						Stats::SetInt("MPX_GANGOPS_FLOW_MISSION_PROG", 503);
						Stats::SetInt("MPX_GANGOPS_HEIST_STATUS", -229383);
						break;
					case 1:
						Stats::SetInt("MPX_GANGOPS_FLOW_MISSION_PROG", 240);
						Stats::SetInt("MPX_GANGOPS_HEIST_STATUS", -229378);
						break;
					case 2:
						Stats::SetInt("MPX_GANGOPS_FLOW_MISSION_PROG", 16368);
						Stats::SetInt("MPX_GANGOPS_HEIST_STATUS", -229380);
						break;
					default: break;
					}

					Stats::SetInt("MPX_GANGOPS_FLOW_NOTIFICATIONS", 1557);

					// ScriptMgr::Yield(500ms);
					// if (auto thread = Scripts::FindScriptThread("gb_gang_ops_planning"_J))
					// 	*ScriptLocal(thread, 211).As<int*>() = 6;
				});
			ImGui::SameLine();
			if (ImGui::Button("Forces all players Ready"))
				FiberPool::Push([] {
					if (auto gpbd_fm_2 = GPBD_FM_2::Get())
					{
						gpbd_fm_2->Entries[0].GangopsData.ArePlayersReady[0] = TRUE;
						gpbd_fm_2->Entries[1].GangopsData.ArePlayersReady[1] = TRUE;
						gpbd_fm_2->Entries[2].GangopsData.ArePlayersReady[2] = TRUE;
						gpbd_fm_2->Entries[3].GangopsData.ArePlayersReady[3] = TRUE;
					}
				});
		}
	};
}