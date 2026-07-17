#pragma once
#include "core/frontend/manager/Submenu.hpp"
#include "game/frontend/components/components.hpp"
#include "core/backend/FiberPool.hpp"
#include "game/gta/ScriptFunction.hpp"
#include "game/gta/Stats.hpp"
#include "types/script/globals/GPBD_FM_2.hpp"
#include <bitset>
#include <random>
#include <algorithm>
#include <numeric>

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
	const char* kortz_targets[] = {
	    "La Dernière Débauche",
	    "Hare Oneself Think",
	    "The Downfall of Rome",
	    "Brother Brother",
	    "A Cast of Characters",
	    "Gone To Seed",
	    "True Love",
	    "Breathless",
	    "Consumato",
	    "I Hear Voices",
	    "Winter, Nowhere in Particular",
	    "The Girl With the Pearl Necklace",
	    "Chat on Fruit",
	    "Pumpkin",
	    "Twindifference",
	    "Stacks Study V",
	    "I, Fruit",
	    "To Beat About the Bush",
	    "In Excess of Success",
	    "Juiced",
	    "A Winding Road Home",
	    "Teckels",
	    "Trust",
	    "Until Death",
	    "What Are Melons?",
	    "The Outcome of Endeavour",
	    "Mi O Melee"};

	// randomly put n bits in p bits
	int put_n_random_bits(int n, int p)
	{
		// Use a random device to seed the random number engine
		std::random_device rd;
		std::mt19937 rng(rd());
		// 1. Create a vector of all possible bit positions (0 to p-1)
		std::vector<int> positions(p);
		std::iota(positions.begin(), positions.end(), 0); // Fills with 0, 1, 2, ..., p-1
		// 2. Randomly shuffle the positions
		std::shuffle(positions.begin(), positions.end(), rng);
		// 3. Take the first n positions
		int result = 0;
		for (int i = 0; i < n; ++i)
			result |= (1U << positions[i]);
		return result;
	}

	class RecoveryHeistCategory : public SubmenuMenuCategory
	{
		using SubmenuMenuCategory::SubmenuMenuCategory;
		void Draw()
		{
			if (!*Pointers.IsSessionStarted)
			{
				ImGui::Text("Go online to see this view.");
				return;
			}

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
			// https://www.unknowncheats.me/forum/grand-theft-auto-v/368204-skip-casino-heist-preps-using-gtahax.html
			// https://github.com/YimMenu-Lua/Casino-Pacino/blob/main/CasinoPacino.lua
			ImGui::Text("Use \"Play All Missions Solo\" above to start heist as solo.\nThen skip the cutscene and when you see planning board click the button below\n and quit the session.");
			if (ImGui::Button("Apartment Heist Prep Skip"))
				FiberPool::Push([] {
					Stats::SetInt("MPX_HEIST_PLANNING_STAGE", -1);
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
			// https://www.unknowncheats.me/forum/grand-theft-auto-v/578963-packed-stats-int-bool-collection-thread-51.html#post4622349
			if (ImGui::Button("Cluckin Bell preps skip"))
				FiberPool::Push([] {
					Stats::SetPackedBool(42108, false);
					Stats::SetPackedInt(51019, 2);
					Stats::SetPackedInt(51021, 2);
					Stats::SetPackedInt(51023, 4);
					Stats::SetInt("MPX_SALV23_INST_PROG", 31);
				});

			components::ver_space();
			// https://www.unknowncheats.me/forum/grand-theft-auto-v/699943-stats-editor-external-enhanced-12.html
			// https://www.unknowncheats.me/forum/grand-theft-auto-v/698429-skip-cooldown-mission-selector-deguzman.html
			// https://www.unknowncheats.me/forum/4349818-post4919.html
			// https://www.unknowncheats.me/forum/grand-theft-auto-v/578963-packed-stats-int-bool-collection-thread-51.html#post4622349
			if (ImGui::Button("Oscar gunzman flies again preps skip"))
				FiberPool::Push([] {
					Stats::SetPackedBool(51272, true);
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
			ImGui::Text("Pay the setup fees first...");
			ImGui::SetNextItemWidth(200.f);
			static auto casinoTarget = 0;
			static bool casino_hard_mode = false;
			if (ImGui::BeginCombo("Target##casinoTarget", casino_targets[casinoTarget]))
			{
				for (int i = 0; i < 4; ++i)
					if (ImGui::Selectable(casino_targets[i], casinoTarget == i))
						casinoTarget = i;
				ImGui::EndCombo();
			}
			ImGui::SameLine();
			if (ImGui::Button("Get##casinoTarget"))
				FiberPool::Push([] {
					casinoTarget = Stats::GetInt("MPX_H3OPT_TARGET");
				});
			static bool bugstar = false, maintainance = false, GruppeSechs = true, yungancestor = false;
			ImGui::Text("Big Con Entry -");
			ImGui::Checkbox("bugstar##casino", &bugstar);
			ImGui::SameLine();
			ImGui::Checkbox("maintainance##casino", &maintainance);
			ImGui::SameLine();
			ImGui::Checkbox("Gruppe Sechs##casino", &GruppeSechs);
			ImGui::SameLine();
			ImGui::Checkbox("yung ancestor##casino", &yungancestor);
			ImGui::Checkbox("Hard Mode##casino", &casino_hard_mode);
			if (ImGui::Button("Casino Heist Prep Skip"))
				FiberPool::Push([] {
					Stats::SetInt("MPX_H3OPT_POI", 1023);
					Stats::SetInt("MPX_H3OPT_ACCESSPOINTS", 2047);
					Stats::SetInt("MPX_H3OPT_TARGET", casinoTarget);
					Stats::SetInt("MPX_H3OPT_BITSET1", 1); // scope the vault

					auto lastApproach = Stats::GetInt("MPX_H3_LAST_APPROACH"); // "Unselected", "Silent & Sneaky", "The Big Con", "Aggressive"
					auto approach = Stats::GetInt("MPX_H3OPT_APPROACH");

					// set approach based on last approach
					if (lastApproach == 1 || lastApproach == 3) // "Silent & Sneaky" ||  "Aggressive"
						approach = 2;                           // "The Big Con"
					else if (lastApproach == 2)                 // "The Big Con"
						approach = 1;                           // "Silent & Sneaky"

					if (approach == 0) // no last approach (select approach manually)
						return;

					Stats::SetInt("MPX_H3OPT_APPROACH", approach);
					Stats::SetInt("MPX_H3_HARD_APPROACH", casino_hard_mode ? approach : 0);

					Stats::SetInt("MPX_H3OPT_CREWDRIVER", 1); // Karim Denz
					Stats::SetInt("MPX_H3OPT_CREWHACKER", 5); // Paige Harris
					Stats::SetInt("MPX_H3OPT_VEHS", 3);       // Sentinel Classic
					Stats::SetInt("MPX_H3OPT_MASKS", 4);      // Emoji Set

					Stats::SetInt("MPX_H3OPT_DISRUPTSHIP", 3); // Security Strength: 1 = Strong, 2 = Medium, 3 = Weak
					Stats::SetInt("MPX_H3OPT_BODYARMORLVL", -1);
					Stats::SetInt("MPX_H3OPT_KEYLEVELS", 2); // 1 = Level1 Security Pass, 2 = Level2 Security Pass

					auto B0 = Stats::GetInt("MPX_H3OPT_BITSET0");
					if (approach == 1) // "Silent & Sneaky"
					{
						Stats::SetInt("MPX_H3OPT_CREWWEAP", 1); // Karl Abolaji
						Stats::SetInt("MPX_H3OPT_WEAPS", 0);
						Stats::SetInt("MPX_H3OPT_BITSET1", 127);
						ScriptMgr::Yield(500ms);
						Stats::SetInt("MPX_H3OPT_BITSET0", B0 | 4456694);
					}
					if (approach == 2) // "The Big Con"
					{
						Stats::SetInt("MPX_H3OPT_CREWWEAP", 1); // Karl Abolaji
						Stats::SetInt("MPX_H3OPT_WEAPS", 0);
						Stats::SetInt("MPX_H3OPT_BITSET1", 159);
						ScriptMgr::Yield(500ms);
						Stats::SetInt("MPX_H3OPT_BITSET0", B0 | 4522198 | (bugstar ? 768 : 0) | (maintainance ? 3072 : 0) | (GruppeSechs ? 12288 : 0) | (yungancestor ? 49152 : 0));
					}
					// if (approach == 3) //  "Aggressive"
					// {
					// 	Stats::SetInt("MPX_H3OPT_CREWWEAP", 5); // Patrick McReary
					// 	Stats::SetInt("MPX_H3OPT_WEAPS", 0);
					// 	Stats::SetInt("MPX_H3OPT_BITSET1", 1023);
					// 	ScriptMgr::Yield(500ms);
					// 	Stats::SetInt("MPX_H3OPT_BITSET0",  B0 | 8388607); // 5767190
					// }

					LOGF(VERBOSE, "CasinoTarget for char {} - {}", Stats::GetCharIndex() + 1, (casinoTarget == -1 ? "Unknown" : casino_targets[casinoTarget]));
					LOG(VERBOSE) << "lastApproach " << casino_approach[lastApproach];
					LOG(VERBOSE) << "currApproach " << casino_approach[approach];
				});

			components::ver_space();
			// https: //www.unknowncheats.me/forum/grand-theft-auto-v/431801-cayo-perico-heist-click-61.html
			// https://www.unknowncheats.me/forum/3014198-post141.html
			// https://www.unknowncheats.me/forum/grand-theft-auto-v/431801-cayo-perico-heist-click-15.html
			ImGui::SetNextItemWidth(200.f);
			static auto cayoTarget = 0;
			if (ImGui::BeginCombo("Target##cayoTarget", cayo_targets[cayoTarget]))
			{
				for (int i = 0; i < 6; ++i)
					if (ImGui::Selectable(cayo_targets[i], cayoTarget == i))
						cayoTarget = i;
				ImGui::EndCombo();
			}
			ImGui::SameLine();
			if (ImGui::Button("Get##cayoTarget"))
				FiberPool::Push([] {
					cayoTarget = Stats::GetInt("MPX_H4CNF_TARGET");
				});
			static bool scope_boat = false, scope_plane = false, cayo_hard_mode = false, scope_island = false;
			ImGui::Checkbox("Scope Boat", &scope_boat);
			// ImGui::SameLine();
			// ImGui::Checkbox("Scope Plane", &scope_plane);
			ImGui::SameLine();
			ImGui::Checkbox("Hard Mode##cayo", &cayo_hard_mode);
			static int gold_n = 1, coke_pos = 1, coke_n = 4;
			ImGui::SetNextItemWidth(150);
			ImGui::SliderInt("No of gold", &gold_n, 1, 8);
			ImGui::Checkbox("Scope Island##cayo", &scope_island);
			ImGui::SameLine();
			ImGui::SetNextItemWidth(150);
			ImGui::SliderInt("No of Coke", &coke_n, 2, 8);
			ImGui::SameLine();
			ImGui::SetNextItemWidth(150);
			ImGui::SliderInt("Coke Position", &coke_pos, 1, 3);
			ImGui::Text("Pay the setup fees first...");
			if (ImGui::Button("Cayo Perico prep skip"))
				FiberPool::Push([] {
					Stats::SetInt("MPX_H4CNF_TARGET", cayoTarget);

					if (scope_island)
					{
						auto cash_c = std::bitset<24>(Stats::GetInt("MPX_H4LOOT_CASH_I")).count();
						auto weed_c = std::bitset<24>(Stats::GetInt("MPX_H4LOOT_WEED_I")).count();
						auto coke = put_n_random_bits(coke_n, 8);
						auto cash = put_n_random_bits(cash_c > 8 ? 8 : cash_c, 8);
						auto weed = put_n_random_bits(weed_c > 8 ? 8 : weed_c, 8);
						std::random_device cash_i_rd;
						std::mt19937 cash_i_engine(cash_i_rd());
						std::uniform_int_distribution<int> cash_i_dist(1, 2);
						int cash_i_loc = cash_i_dist(cash_i_engine);
						int coke_i, weed_i, cash_i;
						if (coke_pos == 1)
						{
							coke_i = coke << 16;
							weed_i = weed << (cash_i_loc == 2 ? 8 : 0);
							cash_i = cash << (cash_i_loc == 2 ? 0 : 8);
						}
						else if (coke_pos == 2)
						{
							coke_i = coke << 8;
							weed_i = weed << (cash_i_loc == 2 ? 16 : 0);
							cash_i = cash << (cash_i_loc == 2 ? 0 : 16);
						}
						else if (coke_pos == 3)
						{
							coke_i = coke << 0;
							weed_i = weed << (cash_i_loc == 2 ? 16 : 8);
							cash_i = cash << (cash_i_loc == 2 ? 8 : 16);
						}
						Stats::SetInt("MPX_H4LOOT_COKE_I_SCOPED", coke_i);
						Stats::SetInt("MPX_H4LOOT_CASH_I_SCOPED", cash_i);
						Stats::SetInt("MPX_H4LOOT_WEED_I_SCOPED", weed_i);
						Stats::SetInt("MPX_H4LOOT_COKE_I", coke_i);
						Stats::SetInt("MPX_H4LOOT_CASH_I", cash_i);
						Stats::SetInt("MPX_H4LOOT_WEED_I", weed_i);
					}

					auto g = put_n_random_bits(gold_n, 8);
					auto c = static_cast<int>(std::bitset<8>(g).flip().to_ulong());
					auto p = put_n_random_bits(2, 7);
					Stats::SetInt("MPX_H4LOOT_CASH_C", c);
					Stats::SetInt("MPX_H4LOOT_GOLD_C", g);
					Stats::SetInt("MPX_H4LOOT_PAINT", p);
					Stats::SetInt("MPX_H4LOOT_CASH_C_SCOPED", c);
					Stats::SetInt("MPX_H4LOOT_GOLD_C_SCOPED", g);
					Stats::SetInt("MPX_H4LOOT_PAINT_SCOPED", p);

					Stats::SetInt("MPX_H4CNF_APPROACH", 223); // approach vehicles
					Stats::SetInt("MPX_H4CNF_WEAPONS", 1);    // aggressor
					Stats::SetInt("MPX_H4CNF_BS_ENTR", 63);   // entries
					Stats::SetInt("MPX_H4CNF_WEP_DISRP", 3);
					Stats::SetInt("MPX_H4CNF_ARM_DISRP", 3);
					Stats::SetInt("MPX_H4CNF_HEL_DISRP", 3);

					// points of interests
					Stats::SetInt("MPX_H4CNF_BS_GEN", 196608 | 32768 | 240); //  + scope truck + scope 4 cloths

					int h4m = 65027;
					if (scope_boat)
						h4m |= 64;
					// if (scope_plane)
					// 	h4m |= 8;
					Stats::SetInt("MPX_H4_MISSIONS", h4m); // preps

					auto progress = Stats::GetInt("MPX_H4_PROGRESS");
					Stats::SetInt("MPX_H4_PROGRESS", progress | (cayoTarget == 2 ? 126955 : 94179) | (cayo_hard_mode ? 4096 : 0));

					LOGF(VERBOSE, "CayoTarget for char {} - {}", Stats::GetCharIndex() + 1, (cayoTarget == -1 ? "Unknown" : cayo_targets[cayoTarget]));
					// https://www.reddit.com/r/gtaonline/comments/pq1gcp/how_much_can_each_persons_bag_carry_in_cayo_perico/
					LOG(VERBOSE) << "Compound Cash% : " << ((int)std::bitset<8>(c).count() * 25);
					LOG(VERBOSE) << "Compound Gold% : " << ((float)std::bitset<8>(g).count() * 66.667);
					LOG(VERBOSE) << "Compound Painting% : " << ((int)std::bitset<7>(p).count() * 50);
				});

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


			components::ver_space();
			// https://www.unknowncheats.me/forum/grand-theft-auto-v/699943-stats-editor-external-enhanced-31.html#post4742522
			ImGui::Text("Pay the setup fees first...");
			ImGui::SetNextItemWidth(200.f);
			static auto kortzTarget = 0;
			if (ImGui::BeginCombo("Target##kortzTarget", kortz_targets[kortzTarget]))
			{
				for (int i = 0; i < 27; ++i)
					if (ImGui::Selectable(kortz_targets[i], kortzTarget == i))
						kortzTarget = i;
				ImGui::EndCombo();
			}
			ImGui::SameLine();
			if (ImGui::Button("Get##kortzTarget"))
				FiberPool::Push([] {
					kortzTarget = Stats::GetInt("MPX_K26_HEIST_TARGET");
				});

			if (ImGui::Button("Kortz Heist Prep Skip"))
				FiberPool::Push([] {
					auto genBs = Stats::GetInt("MPX_K26_GENERAL_BS");
					Stats::SetInt("MPX_K26_GENERAL_BS", genBs | 32 | 64 | 128 | 256);
					Stats::SetInt("MPX_K26_ROBBERY_PROG", 65535 );
					Stats::SetInt("MPX_K26_HEIST_TARGET", kortzTarget);
					Stats::SetInt("MPX_K26_SCOPING_BS", -1);
					Stats::SetInt("MPX_K26_POI_BS", -1);

					LOGF(VERBOSE, "KortzTarget for char {} - {}", Stats::GetCharIndex() + 1, (kortzTarget == -1 ? "Unknown" : kortz_targets[kortzTarget]));
				});
		}
	};
}